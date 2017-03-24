#include "header.h"

/*****************************************************/
//Управління читанням даних з АЦП
/*****************************************************/
void control_reading_ADCs(void)
{
  //Обновляємо робоче командне слово і вибираємо які канали треба оцифровувати
  if (adc_DATA_VAL_read != 0)
  {
    adc_DATA_VAL_read = false;
    status_adc_read_work |= DATA_VAL_READ;
      
    command_word_adc |= READ_DATA_VAL;
  }
  if (adc_TEST_VAL_read != 0) 
  {
    adc_TEST_VAL_read = false;
    status_adc_read_work |= TEST_VAL_READ;
      
    command_word_adc |= READ_TEST_VAL;
  }
  
  unsigned int command_word_adc_diff = command_word_adc ^ command_word_adc_work;
  if (command_word_adc_diff != 0)
  {
    /*
    Є канали, які чекають на оцифровку
    */
    while ((command_word_adc_diff & (1 << active_index_command_word_adc)) == 0)
    {
      /*
      Ще не знайдено каналу, який треба оцифровувати
      */
      active_index_command_word_adc = (active_index_command_word_adc + 1) % NUMBER_INPUTs_ADCs;
    }
      
    /*
    Зараз active_index_command_word_adc вказує у масиві input_adc на канал, 
    який треба оцифрувати
    */
      
//    /*
//    Визначаємо, який зараз активний АЦП
//    */
//    unsigned int active_adc_old = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 1 : 2;
//
    /*
    Визначаємо, який зараз треба активовувати АЦП і які дані треба передати
    */
//    unsigned int active_adc_new = input_adc[active_index_command_word_adc][0];
    unsigned int command_word = input_adc[active_index_command_word_adc][1];
    
    //Визначаємо наступний стан
    if (
        (state_reading_ADCs == STATE_READING_ADCs_NONE) ||
        (state_reading_ADCs == STATE_READING_READ     )
       )
    {
      state_reading_ADCs = STATE_READING_WRITE;
//      /*
//      Вибирваємо відповідний АЦП
//      */
//      switch (active_adc_new)
//      {
//      case 1:
//        {
//          //АЦП1
//          GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
//          break;
//        }
//      default:
//        {
//          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
//          total_error_sw_fixed(50);
//        } 
//      }
    }
    else
    {
//      if (active_adc_old == active_adc_new)
//      {
        state_reading_ADCs = STATE_READING_WRITE_READ;
//      }
//      else
//      {
//        state_reading_ADCs = STATE_READING_READ;
//        command_word = 0;
//      }
    }
    
    if (command_word != 0)
    {
      /*
      Помічаємо, що зараз будемо нове командне слово передавати
      */
      command_word_adc_work |= (1 << active_index_command_word_adc);
    }

    //Передаємо командне слово
    while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //Очікуємо, поки SPI стане вільним
    GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //Виставляємо chip_select
    SPI_ADC->DR = (uint16_t)command_word;                   //Відправляємо командне число
  }
  else 
  {
    if (
        (state_reading_ADCs == STATE_READING_READ     ) ||
        (state_reading_ADCs == STATE_READING_ADCs_NONE)
       )
    {
      //Усі канали вже оцифровані
      state_reading_ADCs = STATE_READING_ADCs_NONE;

      command_word_adc = 0;
      command_word_adc_work = 0;
      active_index_command_word_adc = 0;
    }
    else
    {
      /*
      Треба ще отримати значення з останнього каналуна, який зараз тільки
      щоно оцифровувався
      */
      state_reading_ADCs = STATE_READING_READ;
      while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //Очікуємо, поки SPI стане вільним
      GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //Виставляємо chip_select
      SPI_ADC->DR = 0;                                        //Відправляємо число (але так, щоб нове контрольне слово не записувалося)
    }
  }
}
/*****************************************************/

/*************************************************************************
Опрацьовуємо інтеграільні величини
 *************************************************************************/
void operate_test_ADCs(void)
{
  /*******************************************************
  Вираховування середнього значення контрольних точок
  *******************************************************/
  unsigned int temp;

  //GND для АЦП
  unsigned int gnd_tmp = 0;
  for (unsigned int i = 0; i < NUMBER_GND_ADC; i++)
  {
    temp = output_adc[index_GND_ADC[i]].value;
    gnd_adc_averange_sum[i] += temp;
    gnd_adc_averange_sum[i] -= gnd_adc_moment_value[i][index_array_of_one_value];
    gnd_adc_moment_value[i][index_array_of_one_value] = temp;
    gnd_tmp += gnd_adc_averange[i] = gnd_adc_averange_sum[i] >> VAGA_NUMBER_POINT;
    if (temp > 0xA1) _SET_BIT(set_diagnostyka, ERROR_GND_ADC_TEST_COARSE_BIT);
    else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC_TEST_COARSE_BIT);
  }
  gnd_adc = gnd_tmp / NUMBER_GND_ADC;
  
  //VREF для АЦП
  temp = output_adc[C_VREF_ADC].value;
  vref_adc_averange_sum += temp;
  vref_adc_averange_sum -= vref_adc_moment_value[index_array_of_one_value];
  vref_adc_moment_value[index_array_of_one_value] = temp;
  vref_adc = vref_adc_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp < 0x614) || (temp > 0x9EB)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC_TEST_COARSE_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VREF_ADC_TEST_COARSE_BIT);
  
  //VDD для АЦП
  temp = output_adc[C_VDD_ADC].value; 
  vdd_adc_averange_sum += temp;
  vdd_adc_averange_sum -= vdd_adc_moment_value[index_array_of_one_value];
  vdd_adc_moment_value[index_array_of_one_value] = temp;
  vdd_adc = vdd_adc_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp <0x6F2) || (temp > 0xD48)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC_TEST_COARSE_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC_TEST_COARSE_BIT);

  //Всі масиви одної величини ми вже опрацювали  
  if((++index_array_of_one_value) == NUMBER_POINT)
    index_array_of_one_value = 0;
  else if (index_array_of_one_value > NUMBER_POINT)
  {
    //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
    total_error_sw_fixed(21);
  }
  /*******************************************************/
}
/*************************************************************************/

/*************************************************************************
Опрацьовуємо дані для методу суми квадратів миттєвих значень
 *************************************************************************/
void method_sum_sqr_data(void)
{
  uint32_t index_array_of_sqr_current_data_tmp = index_array_of_sqr_current_data;
  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    int32_t data = ADCs_data[i];
    uint32_t square_data = data*data;
    
    sum_sqr_data_irq[i] += square_data;
    sum_sqr_data_irq[i] -= sqr_current_data[index_array_of_sqr_current_data_tmp][i];
    sqr_current_data[index_array_of_sqr_current_data_tmp][i] = square_data;
  }
    
  if((++index_array_of_sqr_current_data_tmp) == NUMBER_POINT)
    index_array_of_sqr_current_data = 0;
  else if (index_array_of_sqr_current_data_tmp > NUMBER_POINT)
  {
    //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
    total_error_sw_fixed(58);
  }

  //Копіювання для інших систем
  unsigned int bank_sum_sqr_data_tmp = bank_sum_sqr_data;
  for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++ ) sum_sqr_data[bank_sum_sqr_data_tmp][i] = sum_sqr_data_irq[i];
}
/*************************************************************************/

/*****************************************************/
//Переривання від прийнятого байту по канаду SPI, який обслуговує вимірювальну систему
/*****************************************************/
void SPI_ADC_IRQHandler(void)
{
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordEnterISR();
//#endif

  //Фіксуємо вхід у переривання обробки даних від АЦП
  semaphore_adc_irq  = true;
  
  //Фіксуємо час оцифровки
  uint32_t tick_output_adc_tmp = TIM5->CNT;
  
  //На самому початку знімаємо chip_select
  GPIO_SPI_ADC->BSRRL = GPIO_NSSPin_ADC;
  uint16_t read_value = SPI_ADC->DR;

  static uint32_t tick_output_adc_p;
  /*
  Аналізуємо прийняті дані
  */
  if (
      (state_reading_ADCs == STATE_READING_WRITE_READ) ||
      (state_reading_ADCs == STATE_READING_READ)
     )
  {
//    unsigned int shift = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 0 : NUMBER_CANALs_ADC;
    unsigned int number_canal = /*shift* + */((read_value >> 12) & 0xf);

    output_adc[number_canal].tick = tick_output_adc_p;
    output_adc[number_canal].value = read_value & 0xfff;
  }
  tick_output_adc_p = tick_output_adc_tmp;
  /***/
  
  //Виконуємо операції з читання АЦП
  control_reading_ADCs();
  
  /*
  Подальші діх виконуємо тільки тоді, коли всі канали вже оцифровані
  */
  if (state_reading_ADCs == STATE_READING_ADCs_NONE)
  {
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
    /*******************************************************/
    //Перевіряємо, чи відбувалися зміни юстування
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*Це є умова, що нові дані підготовлені для передачі їх у роботу вимірювальною системою (і при цьому зараз дані не змінюються)*/
    {
      //Копіюємо масив юстування у копію цього масиву але з яким працює (читає і змінює) тільки вимірювальна захистема
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        ustuvannja_meas[k] = ustuvannja[k];
      }
    }
    /*****************************************************/

    /*
    Формуємо значення оцифровуваних каналів
    */
    unsigned int command_word = 0;
    if ((status_adc_read_work & DATA_VAL_READ) != 0)
    {
      command_word |= (1 << I_I1 ) | (1 << I_I2 ) | (1 << I_I3 )/*  | (1 << I_I4 )*/  | (1 << I_U);
    }
      
    uint32_t _x1, _x2, _DX, _dx;
    int _y1, _y2;
    long long _y;
      
    unsigned int gnd_adc_tmp  = gnd_adc; 
    unsigned int vref_adc_tmp = vref_adc; 

    uint32_t _x = previous_tick_VAL;
    /*****/
    //Формуємо значення I1
    /*****/
    if ((command_word & (1 << I_I1)) != 0)
    {
      _x1 = ADCs_data_raw[I_I1].tick;
      _y1 = ADCs_data_raw[I_I1].value;
        
      _y2 = output_adc[C_I1_1].value - gnd_adc_tmp - vref_adc_tmp;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_I1_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_I1])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_I1_16].value - gnd_adc_tmp - vref_adc_tmp;

        _x2 = output_adc[C_I1_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_I1])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_I1] = _y;
      
      ADCs_data_raw[I_I1].tick = _x2;
      ADCs_data_raw[I_I1].value = _y2;
    }
    /*****/

    /*****/
    //Формуємо значення I2
    /*****/
    if ((command_word & (1 << I_I2)) != 0)
    {
      _x1 = ADCs_data_raw[I_I2].tick;
      _y1 = ADCs_data_raw[I_I2].value;
        
      _y2 = output_adc[C_I2_1].value - gnd_adc_tmp - vref_adc_tmp;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_I2_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_I2])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_I2_16].value - gnd_adc_tmp - vref_adc_tmp;

        _x2 = output_adc[C_I2_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_I2])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_I2] = _y;
      
      ADCs_data_raw[I_I2].tick = _x2;
      ADCs_data_raw[I_I2].value = _y2;
    }
    /*****/
    
    /*****/
    //Формуємо значення I3
    /*****/
    if ((command_word & (1 << I_I3)) != 0)
    {
      _x1 = ADCs_data_raw[I_I3].tick;
      _y1 = ADCs_data_raw[I_I3].value;
        
      _y2 = output_adc[C_I3_1].value - gnd_adc_tmp - vref_adc_tmp;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_I3_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_I3])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_I3_16].value - gnd_adc_tmp - vref_adc_tmp;

        _x2 = output_adc[C_I3_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_I3])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_I3] = _y;
      
      ADCs_data_raw[I_I3].tick = _x2;
      ADCs_data_raw[I_I3].value = _y2;
    }
    /*****/

    /*****/
    //Формуємо значення U
    /*****/
    if ((command_word & (1 << I_U)) != 0)
    {
      _x1 = ADCs_data_raw[I_U].tick;
      _y1 = ADCs_data_raw[I_U].value;
        
      _y2 = output_adc[C_U_1].value - gnd_adc_tmp - vref_adc_tmp;
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_U_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_U])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_U_16].value - gnd_adc_tmp - vref_adc_tmp;

        _x2 = output_adc[C_U_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_U])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_U] = _y;
      
      ADCs_data_raw[I_U].tick = _x2;
      ADCs_data_raw[I_U].value = _y2;
    }
    /*****/

    if ((status_adc_read_work & DATA_VAL_READ) != 0)
    {
      method_sum_sqr_data();
        
      status_adc_read_work &= (unsigned int)(~DATA_VAL_READ);

      /**************************************************/
      //Виставляємо повідомлення про завершення оброки першої групи вимірювальних величин
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_VAL;
      /**************************************************/
    }
    
    /********************************************************
    Формуємо масив миттєвих значень
    ********************************************************/
    for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
    {
      //Цифровий осцилограф
      current_data[index_array_of_current_data_value++] = ADCs_data[i];
    }
    //Індекс цифрового осцилографа
    if (index_array_of_current_data_value >= (NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT)) index_array_of_current_data_value = 0;/*Умова мал аб бути ==, але щоб перестахуватися на невизначену помилку я поставив >=*/
    /**************************************************/

    /**************************************************/
    //При необхідності повідомляємо про вихід з формування миттєвих значень
    /**************************************************/
    if (wait_of_receiving_current_data  == true) wait_of_receiving_current_data  = false;
    /**************************************************/

    if ((status_adc_read_work & TEST_VAL_READ) != 0)
    {
      //Треба опрацювати інтегральні величини
      operate_test_ADCs();
    
      status_adc_read_work &= (unsigned int)(~TEST_VAL_READ);

      /**************************************************/
      //Виставляємо повідомлення про завершення тестових величин
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_TEST_VAL;
      /**************************************************/
      
      /**************************************************/
      //Якщо зараз стоїть блокування то його знімаємо
      /**************************************************/
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //Повне роозблоковування обміну з мікросхемами для драйверу I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
      /**************************************************/
    }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
  }

  if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)
  {
    //Новий обмін не почався функцією control_reading_ADCs
    
    /*
    Можливо з часу останнього виклику функції control_reading_ADCs до даного
    моментк переривання від таймера поставило нові задачі на оцифровку
    */
    
    /*
    Забороняємо генерацію переривань, щоб поки ми аналізуємо чяи немає нових даних
    на оцифровку ще новіші не появилися
    */
    __disable_interrupt();
    
    /*
    Аналізуємо, чи немає нових даних на оцифровку і якщо до даного моменту нових
    даних не появилося, то розблоковуємо можливість початку оцифровки з переривання
    таймеру ( chip select виставлений у 1)
    */
    if (
        (adc_DATA_VAL_read == false) &&
        (adc_TEST_VAL_read == false)
       )
    {
      semaphore_adc_irq  = false;
    }
    
    /*
    Дозволяємо генерацію переривань
    */
     __enable_interrupt();
  }
  else semaphore_adc_irq  = false;

  
  if (semaphore_adc_irq  != false)
  {
    /*
    Ця умова може бути тільки у одному випадку: якщо при аналізі на нові дані на оцифровку
    з моменту отаннього запуску функції control_reading_ADCs до заборони переривань
    функцією __disable_interrupt дані всетаки появилися.
    
    Модемо і маємо запусти функцію control_reading_ADCs. Конфлікту не буде, бо
    chip_select покищо виставлений у високий стан (це дає остання перевірка 
    if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)) і змінна semaphore_adc_irq ще
    не рівна false, а тим чином блокує запуск оцифровки х переривання таймеру
    */
    
    control_reading_ADCs();
    
    /*
    Скидаємо прапорець. який сигналізує що ми у перериванні обробки оцифрованих даних, які прийшли по SPI
    інтерфейсу. Але цей прапорець вже нічого не блокує, бо запуск функції control_reading_ADCs
    при гарантованій умові, що дані на оцифровку "стоять у черзі"  мусить почати
    оцифровку - а це можливе тільки тоді, коли chip_select цією функцією буде вустановлено у низький рівень
    
    А встановиться chip_select назад у високий рівень тільки коли знову згенерується переривання від
    каналі SPI
    */
    semaphore_adc_irq  = false;
  }
  
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordExitISR();
//#endif
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
