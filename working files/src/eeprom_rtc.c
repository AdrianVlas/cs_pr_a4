#include "header.h"


/*****************************************************/
//Старт  запису буферу по I2C
/*
  Результат
  0 - почався новий обмін
  1 - покищо лінія зайнята
  2 - не запущений обмін через помилки на i2C
*/
/*****************************************************/
unsigned int start_write_buffer_via_I2C(uint32_t device_id, uint16_t WriteAddr,  uint8_t volatile* pBuffer, uint32_t number)
{
  unsigned int error = 0; //0 - успішно виконано; 1 - лінія зайнята; 2 - інші помилки
  //Перевіряємо чи у процесі аналізу попередньої транзакції скинуті попередні помилки
  if (type_error_of_exchanging_via_i2c != 0)
  {
    type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
    error = 2;
  }
  else
  {
    /*Перевіряємо чи лінія є зайнятою на момент запуску цієї функції*/
    if (I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY))
    {
      if (number_busy_state < MAX_NUMBER_BUSY_STATE)
      {
        error = 1;
        number_busy_state++;
      }
      else
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
          
      /***/
      //Перевірка, чи є непрочитані дані
      /***/
      unsigned int temp_value = 0;
      while (((I2C_GetLastEvent(I2C) & I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY) !=0) && (temp_value < 100 ))
      {
        I2C_AcknowledgeConfig(I2C, DISABLE);
        I2C_GenerateSTOP(I2C, ENABLE);
        I2C_ReceiveData(I2C);
        temp_value++;
      }
      if (temp_value >= 100 )
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
      /***/
    }
    else
    {
      //Очищаємо кількість BUSY станів
      number_busy_state = 0;

      //Заповнюємо структуру драйверу обміну через I2C
      driver_i2c.state_execution = 0;
      driver_i2c.device_id = device_id;
      driver_i2c.action = 2;
      driver_i2c.internal_address = WriteAddr;
      driver_i2c.number_bytes = number;
      driver_i2c.point_buffer = pBuffer;
      
      //Виставляємо генерацію ACK операції читання (хоч при операції запису цей біт не мав би впливати)
      I2C_AcknowledgeConfig(I2C, ENABLE);

      /*Стираємо можливі помилки, які можуть бути виставленими у регістрі статусу*/
      I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
      
      /* Дозволяємо для I2C генерацію переривань по подіях */
      I2C_ITConfig(I2C, I2C_IT_EVT, ENABLE);
      
      /* Посилаємо STRAT*/
      I2C_GenerateSTART(I2C, ENABLE);
    }
  }
  
  return error;      
}
/*****************************************************/

/*****************************************************/
//Старт  читання буферу по I2C
/*
  Результат
  0 - почався новий обмін
  1 - покищо лінія зайнята
  2 - не запущений обмін через помилки на i2C
*/
/*****************************************************/
unsigned int start_read_buffer_via_I2C(uint32_t device_id, uint16_t ReadAddr, uint8_t volatile* pBuffer, uint32_t number)
{
  unsigned int error = 0; //0 - успішно виконано; 1 - лінія зайнята; 2 - інші помилки
  //Перевіряємо чи у процесі аналізу попередньої транзакції скинуті попередні помилки
  if (type_error_of_exchanging_via_i2c != 0)
  {
    type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
    error = 2;
  }
  else
  {
    /*Перевіряємо чи лінія є зайнятою на момент запуску цієї функції*/
    if (I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY))
    {
      if (number_busy_state < MAX_NUMBER_BUSY_STATE)
      {
        error = 1;
        number_busy_state++;
      }
      else
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
          
      /***/
      //Перевірка, чи є непрочитані дані
      /***/
      unsigned int temp_value = 0;
      while (((I2C_GetLastEvent(I2C) & I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY) !=0) && (temp_value < 100 ))
      {
        I2C_AcknowledgeConfig(I2C, DISABLE);
        I2C_GenerateSTOP(I2C, ENABLE);
        I2C_ReceiveData(I2C);
        temp_value++;
      }
      if (temp_value >= 100 )
      {
        type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
        error = 2;
      }
      /***/
    }
    else
    {
      //Очищаємо кількість BUSY станів
      number_busy_state = 0;
      
      //Заповнюэмо структуру драйверу обміну через I2C
      driver_i2c.state_execution = 0;
      driver_i2c.device_id = device_id;
      driver_i2c.action = 0;
      driver_i2c.internal_address = ReadAddr;
      driver_i2c.number_bytes = number;
      driver_i2c.point_buffer = pBuffer;
      
      //Виставляємо генерацію ACK операції читання
      I2C_AcknowledgeConfig(I2C, ENABLE);

      /*Стираємо можливі помилки, які можуть бути виставленими у регістрі статусу*/
      I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
      
      /* Дозволяємо для I2C генерацію переривань по подіях */
      I2C_ITConfig(I2C, I2C_IT_EVT, ENABLE);
      
      /* Посилаємо STRAT*/
      I2C_GenerateSTART(I2C, ENABLE);
    }
  }
  
  return error;      
}
/*****************************************************/

/*****************************************************/
//Управління обміном через I2C
/*****************************************************/
void main_routines_for_i2c(void)
{
  //Статична змінна, яка вказує який блок конфігурації треба записувати у EEPROM
  static unsigned int number_block_config_write_to_eeprom;
  //Статична змінна, яка вказує який блок настройок треба записувати у EEPROM
  static unsigned int number_block_settings_write_to_eeprom;
  //Статична змінна, яка вказує з якої адреси треба почати записувати налаштування у EEPROM
  static size_t shift_from_start_address_settings_in_eeprom;
  //Статична змінна, яка вказує скільки байт налаштувань підготовлено для запису у EEPROM
  static size_t size_settings;
  //Статична змінна, яка вказує який блок юстування треба записувати у EEPROM
  static unsigned int number_block_ustuvannja_write_to_eeprom;
  //Статична змінна, яка вказує який блок триґерної інформації треба записувати у EEPROM
//  static unsigned int number_block_trg_func_write_to_eeprom;
  //Статична змінна, яка вказує який блок інформації по реєстраторі програмних подій треба записувати у EEPROM
  static unsigned int number_block_info_rejestrator_pr_err_write_to_eeprom;
  
  static unsigned int temp_value_for_rtc;
  
  //Статичні змінні для контролю коректності запису
  static __CONFIG current_config_comp;
  static unsigned int ustuvannja_comp[NUMBER_ANALOG_CANALES], serial_number_dev_comp;
//  static unsigned int trigger_active_functions_comp[N_BIG];
  static __INFO_REJESTRATOR info_rejestrator_pr_err_comp;
  
  if (driver_i2c.state_execution < 0)
  {
    /*************************************************/
    //Зараз можна ініціювати нову трансакцію через I2C
    /*************************************************/
    
    if(_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0)
    {
      unsigned int rez;
      
      //Виставляння регістрів RTC у потрібні стартові значення для того, щоб на виході мати 1 Гц
      if (etap_settings_test_frequency == 0)
      {
        read_write_i2c_buffer[0] = temp_register_rtc[0];
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0xC, read_write_i2c_buffer, 1);
      }
      else if (etap_settings_test_frequency == 1)
      {
        read_write_i2c_buffer[0] = 0xf0;
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0x13, read_write_i2c_buffer, 1);
      }
      else
      {
        read_write_i2c_buffer[0] = temp_register_rtc[1];
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0xA, read_write_i2c_buffer, 1);
      }
      
      //Аналізуємо успішність запуску нового запису
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
    }
    else if((_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0) || (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT) !=0))
    {
      unsigned int rez;
      
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0)
      {
        //Скидання OF-біт в RTC
        if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_STOP)
          read_write_i2c_buffer[0] = time[1] | (1<<7); //ST = 1
        else if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_CLEAR)
          read_write_i2c_buffer[0] = time[1] & (~(1<<7)) ; //ST = 0
        else
          read_write_i2c_buffer[0] = (unsigned char)(temp_value_for_rtc) & (~(1<<2)) ; //OF = 0
      }
      else
      {
        read_write_i2c_buffer[0] = time[1] & (~(1<<7)) ; //ST = 0
      }
      if ((_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0) && (etap_reset_of_bit != ETAP_CLEAR_OF_ST_STOP) &&(etap_reset_of_bit != ETAP_CLEAR_OF_ST_CLEAR))
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0xF, read_write_i2c_buffer, 1);
      else 
        rez = start_write_buffer_via_I2C(RTC_ADDRESS, 0x1, read_write_i2c_buffer, 1);
      
      //Аналізуємо успішність запуску нового запису
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
    }
    else if(
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT) !=0) ||
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT)      !=0)
           )
    {
      //Зараз треба зачекати з початною опрерацією, тому просто виходимо з цієї підпрограми
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT) !=0)
    {
      //Стоїть умова запису блоку у EEPROM конфігурації

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //Визначаємо з якого місця треба почати записувати
      offset_from_start = number_block_config_write_to_eeprom*SIZE_PAGE_EEPROM;

      //Кількість байт до кінця буферу 
      size_to_end = (sizeof(__CONFIG) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_CONFIG_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_CONFIG_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //Аналізуємо успішність запуску нового запису
        if (rez > 1)
        {
          error_start_i2c();          
          
          //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //Весь масив конфігурації вже записаний
        
        //Виставляємо команду контрольного читання для перевідрки достовірності записаної інформації
        comparison_writing |= COMPARISON_WRITING_CONFIG;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        
        //Скидаємо умову запису конфігурації у EEPROM
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT) !=0)
    {
      //Стоїть умова запису блоку у EEPROM настройок

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //Визначаємо з якого місця треба почати записувати
      offset_from_start = number_block_settings_write_to_eeprom*SIZE_PAGE_EEPROM;

      //Кількість байт до кінця буферу 
      size_to_end = size_settings - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_SETTINGS_IN_EEPROM + shift_from_start_address_settings_in_eeprom + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_SETTINGS_IN_EEPROM + shift_from_start_address_settings_in_eeprom + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //Аналізуємо успішність запуску нового запису
        if (rez > 1)
        {
          error_start_i2c();          
          
          //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //Порція масиву налаштувань вже записана
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //Стоїть умова запису блоку у EEPROM юстування

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //Визначаємо з якого місця треба почати записувати
      offset_from_start = number_block_ustuvannja_write_to_eeprom*SIZE_PAGE_EEPROM;

      //Кількість байт до кінця буферу 
      size_to_end = (SIZE_USTUVANNJA + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_USTUVANNJA_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_USTUVANNJA_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //Аналізуємо успішність запуску нового запису
        if (rez > 1)
        {
          error_start_i2c();          
          
          //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //Весь масив юстування вже записаний

        //Виставляємо команду контрольного читання для перевідрки достовірності записаної інформації
        comparison_writing |= COMPARISON_WRITING_USTUVANNJA;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        
        //Скидаємо умову запису юстування у EEPROM
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT);
      }
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //Стоїть умова запису блоку триґерної інформації
//
//      int size_to_end;
//      unsigned int rez, offset_from_start;
//      
//      //Визначаємо з якого місця треба почати записувати
//      offset_from_start = number_block_trg_func_write_to_eeprom*SIZE_PAGE_EEPROM;
//
//      //Кількість байт до кінця буферу 
//      size_to_end = (sizeof(trigger_active_functions) + 1) - offset_from_start; 
//      
//      if (size_to_end > 0)
//      {
//        if (size_to_end < SIZE_PAGE_EEPROM)
//          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_TRG_FUNC + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
//        else
//          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_TRG_FUNC + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
//        
//        //Аналізуємо успішність запуску нового запису
//        if (rez > 1)
//        {
//          error_start_i2c();          
//          
//          //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
//          type_error_of_exchanging_via_i2c = 0;
//        }
//        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
//      }
//      else
//      {
//        //Весь масив вже записаний
//       
//        //Виставляємо команду контрольного читання для перевідрки достовірності записаної інформації
//        comparison_writing |= COMPARISON_WRITING_TRG_FUNC;
//        _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
//        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
//
//        //Cкидаємо умову запису інформації аналогового реєстратора у EEPROM
//        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT);
//      }
//      
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //Стоїть умова запису блоку інформації реєстратора програмних подій у EEPROM

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //Визначаємо з якого місця треба почати записувати
      offset_from_start = number_block_info_rejestrator_pr_err_write_to_eeprom*SIZE_PAGE_EEPROM;

      //Кількість байт до кінця буферу 
      size_to_end = (sizeof(info_rejestrator_pr_err) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_INFO_REJESTRATORS_PR_ERR + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_INFO_REJESTRATORS_PR_ERR + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //Аналізуємо успішність запуску нового запису
        if (rez > 1)
        {
          error_start_i2c();          
          
          //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //Весь масив вже записаний
       
        //Виставляємо команду контрольного читання для перевідрки достовірності записаної інформації
        comparison_writing |= COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        

        //Cкидаємо умову запису інформації реєстратора програмних подій у EEPROM
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT) !=0)
    {
      unsigned int rez;

      //Запускаємо процес читання конфігурації
      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_CONFIG_IN_EEPROM, read_write_i2c_buffer, (sizeof(__CONFIG) + 1));
      
      //Аналізуємо успішність запуску нового запису
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //При успішнопу запуску читання скидаємо біт запуску читання конфігурації і виставляємо біт процесу читання конфігурації
        _SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT) !=0)
    {
      //Запускаємо процес читання настройок
      static enum _id_fb block;
      static unsigned int shift;

      if (
          (shift_from_start_address_settings_in_eeprom == 0) &&
          (size_settings == 0)  
         )   
      {
        block = _ID_FB_FIRST_ALL;
        shift = 0;
      }
      
      if (size_settings == 0)
      {
        //Якщо ця статична змінна size_setting рівна нулю, то це ознаає що прочитані дані вже оброблені і можна читати наступний блок
        size_t size_of_block = 0;
        size_t size = 0;
        while(
              (size < SIZE_BUFFER_FOR_EEPROM_EXCHNGE) &&
              (block < _ID_FB_LAST_ALL)
             )
        {
          //Визначаємо розмір нового блоку
          switch (block)
          {
          case ID_FB_CONTROL_BLOCK:
            {
              size_of_block = sizeof(__SETTINGS_FIX);
              break;
            }
          case ID_FB_INPUT:
            {
              size_of_block = current_config.n_input*sizeof(__settings_for_INPUT);
              break;
            }
          case ID_FB_OUTPUT:
            {
              size_of_block = current_config.n_output*sizeof(__settings_for_OUTPUT);
              break;
            }
          case ID_FB_LED:
            {
              size_of_block = current_config.n_led*sizeof(__settings_for_LED);
              break;
            }
          case ID_FB_ALARM:
            {
              size_of_block = current_config.n_alarm*sizeof(__settings_for_ALARM);
              break;
            }
          case ID_FB_GROUP_ALARM:
            {
              size_of_block = current_config.n_group_alarm*sizeof(__settings_for_GROUP_ALARM);
              break;
            }
          case ID_FB_AND:
            {
              size_of_block = current_config.n_and*sizeof(__settings_for_AND);
              break;
            }
          case ID_FB_OR:
            {
              size_of_block = current_config.n_or*sizeof(__settings_for_OR);
              break;
            }
          case ID_FB_XOR:
            {
              size_of_block = current_config.n_xor*sizeof(__settings_for_XOR);
              break;
            }
          case ID_FB_NOT:
            {
              size_of_block = current_config.n_not*sizeof(__settings_for_NOT);
              break;
            }
          case ID_FB_TIMER:
            {
              size_of_block = current_config.n_timer*sizeof(__settings_for_TIMER);
              break;
            }
          case ID_FB_TRIGGER:
            {
              size_of_block = current_config.n_trigger*sizeof(__settings_for_TRIGGER);
              break;
            }
          case ID_FB_MEANDER:
            {
              size_of_block = current_config.n_meander*sizeof(__settings_for_MEANDER);
              break;
            }
          default:
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(53);
            }
          }
      
          size_t size_tmp = size + (size_of_block - shift);
          if (size_tmp <= SIZE_BUFFER_FOR_EEPROM_EXCHNGE) 
          {
            shift = 0;
            block++;
            size = size_tmp;
          }
          else
          {
            shift += SIZE_BUFFER_FOR_EEPROM_EXCHNGE - size;
            size = SIZE_BUFFER_FOR_EEPROM_EXCHNGE;
          }
        }
        size_settings = size;
      }
      
      if (
          (size_settings < SIZE_BUFFER_FOR_EEPROM_EXCHNGE) &&
          (block == _ID_FB_LAST_ALL)
         )   
      {
        //Додаємо ще контрольу суму для читання
        size_settings++;
        block++; /*це робимо для того, щоб коли наступний раз попадемо у цю частину програми, то не додавти ще один байтт для читання, а скинути всі статичні змінні і завршити процедуру читання*/

      }
      
      if (size_settings != 0) 
      {
        /*Тепер вже нерівність нулю цієї статичної змінної означає, що є що читати*/
        unsigned int rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_SETTINGS_IN_EEPROM + shift_from_start_address_settings_in_eeprom, read_write_i2c_buffer, size_settings);
        //Аналізуємо успішність запуску нового запису
        if (rez > 1)
        {
          error_start_i2c();
        
          //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0)
        {
          _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

          //При успішнопу запуску читання виставляємо біт процесу читання настройок
          _SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
          _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        }
      }
      else
      {
        //Скидаємо всі статичні змінні, які використовуютья при записі налаштувань
        block = _ID_FB_FIRST_ALL;
        shift = 0;

        shift_from_start_address_settings_in_eeprom = 0;
        size_settings = 0;

        //Знімаємо можливу сигналізацію, що виконувалося порівнняння
        comparison_writing &= (unsigned int)(~COMPARISON_WRITING_SETTINGS);
        //Скидаємо біт команди читання налаштувань
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT) !=0)
    {
      unsigned int rez;
      
      //Запускаємо процес читання юстування
      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_USTUVANNJA_IN_EEPROM, read_write_i2c_buffer, (SIZE_USTUVANNJA + 1));
      
      //Аналізуємо успішність запуску
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //При успішнопу запуску читання скидаємо біт запуску читання юстування і виставляємо біт процесу читання юстування
        _SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
      }
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      unsigned int rez;
//
//      //Запускаємо процес читання
//      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_TRG_FUNC, read_write_i2c_buffer, (sizeof(trigger_active_functions) + 1));
//      
//      //Аналізуємо успішність запуску
//      if (rez > 1)
//      {
//        error_start_i2c();
//        
//        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
//        type_error_of_exchanging_via_i2c = 0;
//      }
//      else if (rez == 0)
//      {
//        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
//
//        //При успішнопу запуску читання скидаємо біт запуску читання і виставляємо біт процесу читання
//        _SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
//        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
//        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
//      }
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      unsigned int rez;

      //Запускаємо процес читання
      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_INFO_REJESTRATORS_PR_ERR, read_write_i2c_buffer, (sizeof(info_rejestrator_pr_err) + 1));
      
      //Аналізуємо успішність запуску нового запису
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //При успішнопу запуску читання скидаємо біт запуску читання і виставляємо біт процесу читання
        _SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT) !=0)
    {
      //Стоїть умова початку нового запису у EEPROM конфігурації пристрою
      
      //Скидаємо біт запуску нового запису і виставляємо біт запису блоків у EEPROM з блокуванням, щоб запуск почався з синхронізацією
      _SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT);
      
      //Робимо копію записуваної інформації для контролю

      //Готуємо буфер для запису настройок (зкопійоманих) у EEPROM разом з контрольною сумою
      unsigned char crc_eeprom_config = 0, temp_value;
      unsigned char  *point_1 = (unsigned char*)(&current_config); 
      unsigned char  *point_2 = (unsigned char*)(&current_config_comp); 
      for (unsigned int i = 0; i < sizeof(__CONFIG); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        read_write_i2c_buffer[i] = temp_value;
        crc_eeprom_config += temp_value;
      }
      //Добавляємо інвертовану контрольну суму у кінець масиву
      read_write_i2c_buffer[sizeof(__CONFIG)] = (unsigned char)((~(unsigned int)crc_eeprom_config) & 0xff);
      
      //Виставляємо перший блок конфігурації запису у EEPROM
      number_block_config_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT) !=0)
    {
      //Стоїть умова початку запису нової порції інформації по налаштуваннях у EEPROM
      static enum _id_fb block;
      static unsigned int shift;
      static uint8_t crc_eeprom_settings;

      if (
          (shift_from_start_address_settings_in_eeprom == 0) &&
          (size_settings == 0)  
         )   
      {
        block = _ID_FB_FIRST_ALL;
        shift = 0;
        crc_eeprom_settings = 0;
      }
      
      //Робимо копію записуваної інформації для контролю

      //Готуємо буфер для запису настройок (зкопійоманих) у EEPROM разом з контрольною сумою
      uint8_t temp_value;
      uint8_t *point_1, *point_2; 
      size_t size_of_block = 0;
      
      size_t index = 0;
      while(
            (index < SIZE_BUFFER_FOR_EEPROM_EXCHNGE) &&
            (block < _ID_FB_LAST_ALL)
           )
      {
        if (size_of_block == 0)
        {
          //Визначаємо розмір нового блоку
          switch (block)
          {
          case ID_FB_CONTROL_BLOCK:
            {
              size_of_block = sizeof(__SETTINGS_FIX);
              break;
            }
          case ID_FB_INPUT:
            {
              size_of_block = current_config.n_input*sizeof(__settings_for_INPUT);
              break;
            }
          case ID_FB_OUTPUT:
            {
              size_of_block = current_config.n_output*sizeof(__settings_for_OUTPUT);
              break;
            }
          case ID_FB_LED:
            {
              size_of_block = current_config.n_led*sizeof(__settings_for_LED);
              break;
            }
          case ID_FB_ALARM:
            {
              size_of_block = current_config.n_alarm*sizeof(__settings_for_ALARM);
              break;
            }
          case ID_FB_GROUP_ALARM:
            {
              size_of_block = current_config.n_group_alarm*sizeof(__settings_for_GROUP_ALARM);
              break;
            }
          case ID_FB_AND:
            {
              size_of_block = current_config.n_and*sizeof(__settings_for_AND);
              break;
            }
          case ID_FB_OR:
            {
              size_of_block = current_config.n_or*sizeof(__settings_for_OR);
              break;
            }
          case ID_FB_XOR:
            {
              size_of_block = current_config.n_xor*sizeof(__settings_for_XOR);
              break;
            }
          case ID_FB_NOT:
            {
              size_of_block = current_config.n_not*sizeof(__settings_for_NOT);
              break;
            }
          case ID_FB_TIMER:
            {
              size_of_block = current_config.n_timer*sizeof(__settings_for_TIMER);
              break;
            }
          case ID_FB_TRIGGER:
            {
              size_of_block = current_config.n_trigger*sizeof(__settings_for_TRIGGER);
              break;
            }
          case ID_FB_MEANDER:
            {
              size_of_block = current_config.n_meander*sizeof(__settings_for_MEANDER);
              break;
            }
          default:
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(51);
            }
          }

          //Визначаємо вказівник на початок блоку
          if (size_of_block != 0)
          {
            if (block == ID_FB_CONTROL_BLOCK)
            {
              point_1 = (uint8_t *)(&settings_fix);
              point_2 = (uint8_t *)(&settings_fix_edit);
            }
            else
            {
              point_1 = (uint8_t *)(sca_of_p     [block - _ID_FB_FIRST_VAR]);
              point_2 = (uint8_t *)(sca_of_p_edit[block - _ID_FB_FIRST_VAR]);
            }
          }
        }
      
        if (size_of_block != 0)
        {
          temp_value = *(point_1 + shift);
          *(point_2 + shift) = temp_value;
          read_write_i2c_buffer[index++] = temp_value;
          crc_eeprom_settings += temp_value;
          
          if ((++shift) >= size_of_block)
          {
            shift = 0;
            block++;
            size_of_block = 0;
          }
        }
        else 
        {
          shift = 0;
          block++;
        }
      }
      
      if (
          (index < SIZE_BUFFER_FOR_EEPROM_EXCHNGE) &&
          (block == _ID_FB_LAST_ALL)
         )   
      {
        //Додаємо ще контрольу суму
        read_write_i2c_buffer[index++] = (uint8_t)((~(unsigned int)crc_eeprom_settings) & 0xff);
        block++; /*це робимо для того, щоб коли наступний раз попадемо у цю частину програми, то не додавти контрольну суму, а скинути всі статичні змінні і завршити процедузу запису*/

      }

      //Виставляємо перший блок настройок запису у EEPROM
      number_block_settings_write_to_eeprom = 0;
      
      if (index == 0)
      {
        //Весь масив настройок вже записаний
        
        //Скидаємо всі статичні змінні, які використовуютья при записі налаштувань
        block = _ID_FB_FIRST_ALL;
        shift = 0;
        crc_eeprom_settings = 0;
        
        shift_from_start_address_settings_in_eeprom = 0;
        size_settings = 0;

        //Виставляємо команду контрольного читання для перевідрки достовірності записаної інформації
        comparison_writing |= COMPARISON_WRITING_SETTINGS;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        

        //Скидаємо біт команди запису налаштувань
        _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
      }
      else
      {
        //Виставляємо біт запису блоків у EEPROM з блокуванням (щоб запуск почався з синхронізацією) тільки утому випадку, якщо є підготовлені дані до запису
        _SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      
        //Фіксуємо з якого зміщення треба продовжити писати
        shift_from_start_address_settings_in_eeprom += size_settings;
        
        //Виставляємо скільки байт підготовлено до запису
        size_settings = index;
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //Стоїть умова початку нового запису у EEPROM юстування
      
      //Скидаємо біт запуску нового запису і виставляємо біт запису блоків у EEPROM з блокуванням, щоб запуск почався з синхронізацією
      _SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);

      //Робимо копію записуваної інформації для контролю
      
      //Готуємо буфер для запису настройок у EEPROM разом з контрольноюсумою
      unsigned char crc_eeprom_ustuvannja = 0, temp_value;
      unsigned char  *point_1; 
      unsigned char  *point_2;
      unsigned int offset = 0;

      //Додаємо ідентифікатор типу нобору юстуючих коефіцієнтів
      unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
      point_1 = (unsigned char*)(&adjustment_id_tmp); 
      for (unsigned int i = 0; i < sizeof(unsigned int); i++)
      {
        temp_value = *(point_1++);
        read_write_i2c_buffer[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(unsigned int);
      
      //Додаємо юстуючі коефіцієнти
      point_1 = (unsigned char*)(&ustuvannja); 
      point_2 = (unsigned char*)(&ustuvannja_comp);
      for (unsigned int i =0; i < sizeof(ustuvannja); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        read_write_i2c_buffer[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(ustuvannja);

      //Додаємо ще серійний номер пристрою
      point_1 = (unsigned char*)(&serial_number_dev); 
      point_2 = (unsigned char*)(&serial_number_dev_comp); 
      for (unsigned int i = 0; i < sizeof(serial_number_dev); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        read_write_i2c_buffer[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(serial_number_dev);
      
      //Добавляємо інвертовану контрольну суму у кінець масиву
      read_write_i2c_buffer[offset] = (unsigned char)((~(unsigned int)crc_eeprom_ustuvannja) & 0xff);
      
      //Виставляємо перший блок юстування запису у EEPROM
      number_block_ustuvannja_write_to_eeprom = 0;
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //Стоїть умова початку нового запису у EEPROM по триґерній інформації
//      
//      //Скидаємо біт запуску нового запису і виставляємо біт запису блоків у EEPROM з блокуванням, щоб запуск почався з синхронізацією
//      _SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT);
//      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
//      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
//      
//      //Робимо копію записуваної інформації для контролю
//
//      //Готуємо буфер для запису настройок у EEPROM разом з контрольноюсумою
//      unsigned char crc_eeprom_trg_func = 0, temp_value;
//      unsigned char  *point_1; 
//      unsigned char  *point_2;
//      unsigned int offset = 0;
//
//      //Додаємо триґерні функції
//      point_1 = (unsigned char*)(&trigger_active_functions); 
//      point_2 = (unsigned char*)(&trigger_active_functions_comp);
//      for (unsigned int i =0; i < sizeof(trigger_active_functions); i++)
//      {
//        temp_value = *(point_1);
//        *(point_2) = temp_value;
//        point_1++;
//        point_2++;
//        read_write_i2c_buffer[offset + i] = temp_value;
//        crc_eeprom_trg_func += temp_value;
//      }
//      offset += sizeof(trigger_active_functions);
//
//      //Добавляємо інвертовану контрольну суму у кінець масиву
//      read_write_i2c_buffer[offset] = (unsigned char)((~(unsigned int)crc_eeprom_trg_func) & 0xff);
//      
//      //Виставляємо перший блок запису у EEPROM
//      number_block_trg_func_write_to_eeprom = 0;
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //Стоїть умова початку нового запису у EEPROM по інформації реєстратора програмних подій
      
      //Скидаємо біт запуску нового запису і виставляємо біт запису блоків у EEPROM з блокуванням, щоб запуск почався з синхронізацією
      _SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      
      //Робимо копію записуваної інформації для контролю

      //Готуємо буфер для запису у EEPROM разом з контрольною сумою
      unsigned char crc_eeprom_info_rejestrator_pr_err = 0, temp_value;
      unsigned char  *point_1 = (unsigned char*)(&info_rejestrator_pr_err); 
      unsigned char  *point_2 = (unsigned char*)(&info_rejestrator_pr_err_comp); 
      for (unsigned int i = 0; i < sizeof(__INFO_REJESTRATOR); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        read_write_i2c_buffer[i] = temp_value;
        crc_eeprom_info_rejestrator_pr_err += temp_value;
      }

      //Добавляємо інвертовану контрольну суму у кінець масиву
      read_write_i2c_buffer[sizeof(info_rejestrator_pr_err)] = (unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_pr_err) & 0xff);
      
      //Виставляємо перший блок запису у EEPROM
      number_block_info_rejestrator_pr_err_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT) !=0)
    {
      unsigned int rez;

      //Запускаємо процес читання RTC
      rez = start_read_buffer_via_I2C(RTC_ADDRESS, START_ADDRESS_TIME_REGISTERS, read_write_i2c_buffer, MAX_NUMBER_REGISTERS_RTC);
      
      //Аналізуємо успішність запуску нового запису
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //При успішнопу запуску читання скидаємо біт запуску читання RTC і виставляємо біт процесу читання RTC
        _SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) !=0)
    {
      unsigned int rez;

      copying_time = 1; //Помічаємо, що зараз  ще також обновляємо масив часу
      //Запускаємо процес запису часу в RTC
      read_write_i2c_buffer[0] = time[0] = 0;
      read_write_i2c_buffer[1] = time[1] = time_edit[1] & 0x7F;
      read_write_i2c_buffer[2] = time[2] = time_edit[2] & 0x7F;
      read_write_i2c_buffer[3] = time[3] = time_edit[3] & 0x3F;
      read_write_i2c_buffer[4] = 7;
      read_write_i2c_buffer[5] = time[4] = time_edit[4] & 0x3F;
      read_write_i2c_buffer[6] = time[5] = time_edit[5] & 0x1F;
      read_write_i2c_buffer[7] = time[6] = time_edit[6] & 0xFF;
      
      calibration = calibration_edit & 0x3f;
      read_write_i2c_buffer[8] = calibration | (copy_register8_RTC & 0xC0);

      copying_time = 0; //Помічаємо, що обновлення масив часу завершене
      //Робимо копію масиву часу для того, щоб коли основний масив буде обновлятися можна було іншим модулям взяти попереднє, але достовірне значення часу і дати з цього масиву
      for(unsigned int i = 0; i < 7; i++) time_copy[i] = time[i];
      calibration_copy = calibration;
      
      rez = start_write_buffer_via_I2C(RTC_ADDRESS, START_ADDRESS_TIME_REGISTERS, read_write_i2c_buffer, 9);
      
      //Аналізуємо успішність запуску нового запису
      if (rez > 1)
      {
        error_start_i2c();
        
        //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //При успішнопу запуску читання скидаємо біт запуску читання RTC і виставляємо біт процесу читання RTC
        _SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
        _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
      }
    }
    
    /*************************************************/
  }
  else if (driver_i2c.state_execution == 1)
  {
    /*************************************************/
    //Обмін завершився без помилок
    /*************************************************/
    //Виставляємо повідомлення, що I2C готовий до нової транзакції 
    driver_i2c.state_execution = -1;

    if (
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT                 ) != 0) || 
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT               ) != 0) || 
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT             ) != 0) ||
//        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT               ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
       )
    {
      //Стоїть умова запису блоку у EEPROM

      if(_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT) !=0)
      {
        //Виставляємо наступний блок конфігурації запису у EEPROM
        number_block_config_write_to_eeprom++;
      }
      else if(_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT) !=0)
      {
        //Виставляємо наступний блок настройок запису у EEPROM
        number_block_settings_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT) !=0)
      {
        //Виставляємо наступний блок юстування запису у EEPROM
        number_block_ustuvannja_write_to_eeprom++;
      }
//      else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT) != 0)
//      {
//        //Виставляємо наступний блок триґерної інформаціїзапису у EEPROM
//        number_block_trg_func_write_to_eeprom++;
//      }
      else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
      {
        //Виставляємо наступний блок інформації по реєстраторах запису у EEPROM
        number_block_info_rejestrator_pr_err_write_to_eeprom++;
      }
      else
      {
        //Відбулася невизначена помилка, тому треба піти на перезавантаження
        total_error_sw_fixed(25);
      }

      //Виставляємо біт тимчасового блокування запису, щоб витримати певну павзу і запустити запис після більш пріоритетних завдвнь  
      //Згідно документації операція запису відбувається до 5 мс
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT) !=0)
    {
      //Аналізуємо прочитані дані
      //Спочатку аналізуємо, чи прийнятий блок є пустим, чи вже попередньо записаним
      unsigned int empty_block = 1, i = 0; 
      __CONFIG current_config_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__CONFIG) + 1)))
      {
        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //Помічаємо, що блок конфігурації не є пустим
        state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_EMPTY);
        //Скидаємо повідомлення у слові діагностики
        _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_EMPTY_BIT);
        
        //Перевіряємо контрольну суму і переписуємо прочитані дані у структуру управління
        unsigned char crc_eeprom_config = 0, temp_value;
        unsigned char  *point = (unsigned char*)(&current_config_tmp); 
        for (i = 0; i < sizeof(__CONFIG); i++)
        {
          temp_value = read_write_i2c_buffer[i];
          *(point) = temp_value;
          crc_eeprom_config += temp_value;
          point++;
        }
        if (read_write_i2c_buffer[sizeof(__CONFIG)]  == ((unsigned char)((~(unsigned int)crc_eeprom_config) & 0xff)))
        {
          //Контролдьна сума сходиться

          //Скидаємо повідомлення у слові діагностики
          _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_BIT);

          if (current_config_tmp.device_id == VERSIA_PZ)
          {
            //Таблиця конфігурації відповідає типу даного приладу
            state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_FAIL);
            state_i2c_task |= STATE_CONFIG_EEPROM_GOOD;
          
            //Скидаємо повідомлення у слові діагностики
            _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
            
            //Зберігаємо контрольну суму (не інвертовану)
            crc_config = crc_eeprom_config;

            if ((comparison_writing & COMPARISON_WRITING_CONFIG) == 0)
            {
              //Виконувалося зчитування конфігурації у таблицю конфігурації
            
              /*
              Забороняємо генерацію переривань, під час обновлення конфігурації для структури з якою працюють захисти
              */
              //Єдине поле, яке не змінюється з функції allocate_dynamic_memory_for_settings
              current_config_prt.device_id = current_config.device_id = current_config_edit.device_id = current_config_tmp.device_id;
              __disable_interrupt();

              __result_dym_mem_select result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, true, spca_of_p_prt, NULL, &current_config_prt, &current_config_tmp, NULL);
              
              /*
              Дозволяємо генерацію переривань
              */
              __enable_interrupt();
              
              //Робимо зміни у динамічній пам'яті для налаштувань
              if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, false, sca_of_p     , spca_of_p_prt, &current_config     , &current_config_tmp, &current_config_prt);
              if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, false, sca_of_p_edit, sca_of_p     , &current_config_edit, &current_config_tmp, &current_config    );
              for (size_t t = 0; t < (7 + 1); t++) current_config_edit.time_config[t] = current_config.time_config[t] = current_config_prt.time_config[t] = current_config_tmp.time_config[t];
              
              if (result == DYN_MEM_SELECT_OK) 
              {
                state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_NO_FREE_MEMORY);

                //Скидаємо повідомлення у слові діагностики
                _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
              }
              else
              {
                state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
                state_i2c_task |= STATE_CONFIG_EEPROM_NO_FREE_MEMORY;

                //Виствляємо повідомлення у слові діагностики
                _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
                
                //Звільняємо всю пам'ять
                for (enum _id_fb index_1 = _ID_FB_FIRST_VAR; index_1 < _ID_FB_LAST_VAR; index_1++)
                {
                  free(sca_of_p_edit[index_1 - _ID_FB_FIRST_VAR]);
                  free(sca_of_p[index_1 - _ID_FB_FIRST_VAR]);
                  free(spca_of_p_prt[index_1 - _ID_FB_FIRST_VAR]);
                }
              }
            }
            else
            {
              //Виконувалося контроль достовірності записаної інформації у EEPROM з записуваною
            
              unsigned char  *point_to_read  = (unsigned char*)(&current_config_tmp );
              unsigned char  *point_to_write = (unsigned char*)(&current_config_comp);
              unsigned int difference = 0;

              i = 0;
              while ((difference == 0) && ( i < sizeof(__CONFIG)))
              {
                if (*point_to_write != *point_to_read) difference = 0xff;
                else
                {
                  point_to_write++;
                  point_to_read++;
                  i++;
                }
              }
              if (difference == 0)
              {
                //Контроль порівнняння пройшов успішно

                //Скидаємо повідомлення у слові діагностики
                _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_COMPARISON_BIT);
              }
              else
              {
                //Контроль порівнняння зафіксував розбіжності між записаною і записуваною інформацією

                //Виствляємо повідомлення у слові діагностики
                _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_COMPARISON_BIT);
              }
            }
          }
          else
          {
            //Таблиця конфігурації не відповідає типу даного приладу

            //Помічаємо, що прочитаний блок конфігурації є пустим
            state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_FAIL);
            state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
            state_i2c_task |= STATE_CONFIG_EEPROM_EMPTY; /*Не відповідність типу настройок це то саме що їх немає взагалі*/
        
            //Виствляємо повідомлення у слові діагностики
            _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
          }
        }
        else
        {
          //Контрольна сума не сходиться
          state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
          state_i2c_task |= STATE_CONFIG_EEPROM_FAIL;
          
          //Виствляємо повідомлення у слові діагностики
          _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
          _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_BIT);
        }
      }
      else
      {
        //Помічаємо, що прочитаний блок конфігурації є пустим
        state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_FAIL);
        state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
        state_i2c_task |= STATE_CONFIG_EEPROM_EMPTY;
        
        //Виствляємо повідомлення у слові діагностики
        _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
        _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_EMPTY_BIT);
      }
            
      //Знімаємо можливу сигналізацію, що виконувалося порівнняння
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_CONFIG);
      //Скидаємо повідомлення про читання даних
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //Аналізуємо прочитані дані

      //Статична змінна, яка визначає блок для налаштувань є пустим
      static unsigned int empty_block, difference;
      static uint8_t crc_eeprom_settings;
      if (shift_from_start_address_settings_in_eeprom == 0) 
      {
        empty_block = true;
        difference = false;
        crc_eeprom_settings = 0;
      }
      
      size_t new_shift = shift_from_start_address_settings_in_eeprom + size_settings;
      size_settings = 0; /*Цим повідомляємо інші блоки, що читання успішно даного блоку відбувся*/

      //Спочатку аналізуємо скільки і який блок налаштування прочитано
      enum _id_fb block = _ID_FB_FIRST_ALL;
      unsigned int shift = 0;
      
      size_t size_of_block = 0;
      size_t index = 0;
      uint8_t *p;
      while(
            (index < new_shift) &&
            (block < _ID_FB_LAST_ALL)
           )
      {
        //Визначаємо розмір нового блоку
        if (size_of_block == 0)
        {
          switch (block)
          {
          case ID_FB_CONTROL_BLOCK:
            {
              size_of_block = sizeof(__SETTINGS_FIX);
              break;
            }
          case ID_FB_INPUT:
            {
              size_of_block = current_config.n_input*sizeof(__settings_for_INPUT);
              break;
            }
          case ID_FB_OUTPUT:
            {
              size_of_block = current_config.n_output*sizeof(__settings_for_OUTPUT);
              break;
            }
          case ID_FB_LED:
            {
              size_of_block = current_config.n_led*sizeof(__settings_for_LED);
              break;
            }
          case ID_FB_ALARM:
            {
              size_of_block = current_config.n_alarm*sizeof(__settings_for_ALARM);
              break;
            }
          case ID_FB_GROUP_ALARM:
            {
              size_of_block = current_config.n_group_alarm*sizeof(__settings_for_GROUP_ALARM);
              break;
            }
          case ID_FB_AND:
            {
              size_of_block = current_config.n_and*sizeof(__settings_for_AND);
              break;
            }
          case ID_FB_OR:
            {
              size_of_block = current_config.n_or*sizeof(__settings_for_OR);
              break;
            }
          case ID_FB_XOR:
            {
              size_of_block = current_config.n_xor*sizeof(__settings_for_XOR);
              break;
            }
          case ID_FB_NOT:
            {
              size_of_block = current_config.n_not*sizeof(__settings_for_NOT);
              break;
            }
          case ID_FB_TIMER:
            {
              size_of_block = current_config.n_timer*sizeof(__settings_for_TIMER);
              break;
            }
          case ID_FB_TRIGGER:
            {
              size_of_block = current_config.n_trigger*sizeof(__settings_for_TRIGGER);
              break;
            }
          case ID_FB_MEANDER:
            {
              size_of_block = current_config.n_meander*sizeof(__settings_for_MEANDER);
              break;
            }
          default:
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(54);
            }
          }
          
          if (block == ID_FB_CONTROL_BLOCK) p = (uint8_t *)(&settings_fix_edit);
          else p = (uint8_t *)(sca_of_p_edit[block - _ID_FB_FIRST_VAR]);
        }

        if (index < shift_from_start_address_settings_in_eeprom)
        {
          size_t index_tmp = index + size_of_block;
          if (index_tmp <= shift_from_start_address_settings_in_eeprom) 
          {
            block++;
            index = index_tmp;
            
            size_of_block = 0;
          }
          else
          {
            shift = shift_from_start_address_settings_in_eeprom - index;
            index = shift_from_start_address_settings_in_eeprom;
          }
        }
        else
        {
          if (size_of_block != 0)
          {
            intptr_t i = (index++) - shift_from_start_address_settings_in_eeprom;
            uint8_t temp_value = read_write_i2c_buffer[i];
            if (temp_value != 0xff) empty_block = 0;
            crc_eeprom_settings += temp_value;
            if (p != NULL) 
            {
              if ((comparison_writing & COMPARISON_WRITING_SETTINGS) == 0) 
              {
                //Виконувалося зчитування настройок у таблиці настройок
                *(p + shift) = temp_value;
              }
              else
              {
                //Відбувалося контрольне читання після запису
                if (*(p + shift) != temp_value) difference = true;
              }
            }
            else
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(55);
            }
          
            if ((++shift) >= size_of_block)
            {
              shift = 0;
              block++;
              size_of_block = 0;
            }
          }
          else 
          {
            shift = 0;
            block++;
          }
        }
      }
      
      if (
          (index < new_shift) &&
          (block == _ID_FB_LAST_ALL)
         )   
      {
        uint8_t crc_eeprom_settings_remote = read_write_i2c_buffer[(index++) - shift_from_start_address_settings_in_eeprom];
        if (index == new_shift)
        {
          //Це нормальна ситуація коли вичитано останньоб контрольна сума і можна приступити до аналізу всіх прочитаних даних

          if(empty_block == 0)
          {
            //Помічаємо, що блок настроювання не є пустим
            state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_EMPTY);
            //Скидаємо повідомлення у слові діагностики
            _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);
        
            //Перевіряємо контрольну суму і переписуємо прочитані дані у структуру управління
            if (crc_eeprom_settings_remote  == ((uint8_t)((~(unsigned int)crc_eeprom_settings) & 0xff)))
            {
              //Контролдьна сума сходиться

              //Скидаємо повідомлення у слові діагностики
              _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);

              //Зберігаємо контрольну суму (не інвертовану)
              crc_settings = crc_eeprom_settings;

              if ((comparison_writing & COMPARISON_WRITING_SETTINGS) == 0)
              {
                //Виконувалося зчитування настройок у таблицю настройок
            
                /*
                Копіюємо у контейнер і структуру для захистів (prt) з структури у якії йшло зчитування з EEPROM
                */
                copy_settings(&current_config_edit, &settings_fix, &settings_fix_edit, sca_of_p, sca_of_p_edit);

                __disable_interrupt();
                copy_settings(&current_config_edit, &settings_fix_prt, &settings_fix_edit, spca_of_p_prt, sca_of_p_edit);
                __enable_interrupt();
                /***/

              }
              else
              {
                //Виконувалося контроль достовірності записаної інформації у EEPROM з записуваною
            
                if (difference == false)
                {
                  //Контроль порівнняння пройшов успішно
    
                  //Скидаємо повідомлення у слові діагностики
                  _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_COMPARISON_BIT);
                }
                else
                {
                  //Контроль порівнняння зафіксував розбіжності між записаною і записуваною інформацією

                  //Виствляємо повідомлення у слові діагностики
                  _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_COMPARISON_BIT);
                }
              }

              state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
              state_i2c_task |= STATE_SETTINGS_EEPROM_GOOD;
            }
            else
            {
              //Контрольна сума не сходиться
              /*
              Повертаємо у структури у які йшло зчитування з EEPROM (edit) з контейнера
              */
              copy_settings(&current_config, &settings_fix_edit, &settings_fix, sca_of_p_edit, sca_of_p);
              /***/

              state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
              state_i2c_task |= STATE_SETTINGS_EEPROM_FAIL;
          
              //Виствляємо повідомлення у слові діагностики
              _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
            }
          }
          else
          {
            //Зчитаний блок налаштувань виявився пустим
            /*
            Повертаємо у структури у які йшло зчитування з EEPROM (edit) з контейнера
            */
            copy_settings(&current_config, &settings_fix_edit, &settings_fix, sca_of_p_edit, sca_of_p);
            /***/
            
            //Помічаємо, що прочитаний блок настройок є пустим
            state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
            state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
            state_i2c_task |= STATE_SETTINGS_EEPROM_EMPTY;
        
            //Виствляємо повідомлення у слові діагностики
            _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
            _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);
          }
        }
        else
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(55);
        }
      }
      shift_from_start_address_settings_in_eeprom = new_shift; /*У статичній змінній визначаємо з якого зміщення треба буде продовжувати читати*/
      
      //Скидаємо повідомлення про читання даних
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //Аналізуємо прочитані дані
      //Спочатку аналізуємо, чи прояитаний блок є пустим, чи вже попередньо записаним
      unsigned int empty_block = 1, i = 0; 
      unsigned int adjustment_id_tmp, ustuvannja_tmp[NUMBER_ANALOG_CANALES], serial_number_dev_tmp;

      while ((empty_block != 0) && ( i < (SIZE_USTUVANNJA + 1)))
      {
        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //Помічаємо, що блок настроювання не є пустим
        state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_EMPTY);
        //Скидаємо повідомлення у слові діагностики
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_EMPTY_BIT);
        
        //Перевіряємо контрольну суму і переписуємо прочитані дані у масив юстування з серійним номером
        unsigned char crc_eeprom_ustuvannja = 0, temp_value;
        unsigned char  *point;
        unsigned int offset = 0;

        point = (unsigned char*)(&adjustment_id_tmp); 
        for (i =0; i < sizeof(unsigned int); i++)
        {
          temp_value = read_write_i2c_buffer[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset += sizeof(unsigned int);
        
        point = (unsigned char*)(&ustuvannja_tmp); 
        for (i =0; i < sizeof(ustuvannja_tmp); i++)
        {
          temp_value = read_write_i2c_buffer[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset +=  sizeof(ustuvannja_tmp);
        
        point = (unsigned char*)(&serial_number_dev_tmp); 
        for (i =0; i < sizeof(serial_number_dev_tmp); i++)
        {
          temp_value = read_write_i2c_buffer[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset += sizeof(serial_number_dev_tmp);

        if (read_write_i2c_buffer[offset]  == ((unsigned char)((~(unsigned int)crc_eeprom_ustuvannja) & 0xff)))
        {
          //Контролдьна сума сходиться

          //Скидаємо повідомлення у слові діагностики
          _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
          
          if (adjustment_id_tmp == ADJUSTMENT_ID)
          {
            //Тип набору юстуючих коефіцієнтів відповідає даному програмному забезпеченню

            //Зберігаємо контрольну суму (не інвертовану)
            crc_ustuvannja = crc_eeprom_ustuvannja;
          
            if ((comparison_writing & COMPARISON_WRITING_USTUVANNJA) == 0)
            {
              //Виконувалося зчитування юстування у масив юстування
            
              //Помічаємо, що юстування зараз буде змінюватися і їх треба буде з вимірювальної системи зкопіювати у таблицю з якою працює вимірювальна система
              changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              //Перекидаємо масив юстування з тимчасового масиву у робочий масив
              for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
              {
                ustuvannja[k] = ustuvannja_tmp[k];
              }
              serial_number_dev = serial_number_dev_tmp;
              //Помічаємо, що юстування змінилася і її треба буде з вимірювальної системи зкопіювати у масив з яким працює вимірювальна система
              changed_ustuvannja = CHANGED_ETAP_ENDED;
            }
            else
            {
              //Виконувалося контроль достовірності записаної інформації у EEPROM з записуваною
            
              unsigned int difference = 0;
  
              i = 0;
              while ((difference == 0) && (i < NUMBER_ANALOG_CANALES))
              {
                //Перевірка запису юстуючих коефіцієнтів
                if (
                    (ustuvannja_comp[i] != ustuvannja_tmp[i])
                   )
                {
                  difference = 0xff;
                }
                else
                {
                  i++;
                }
              }
              if (difference == 0) 
              {
                //Перевірка запису серійного номеру (якщо до того не зафіксовано вже помилки)
                if (serial_number_dev_comp != serial_number_dev_tmp) difference = 0xff;
              }
            
              if (difference == 0)
              {
                //Контроль порівнняння пройшов успішно
  
                //Скидаємо повідомлення у слові діагностики
                _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT);
              }
              else
              {
                //Контроль порівнняння зафіксував розбіжності між записаною і записуваною інформацією

                //Виствляємо повідомлення у слові діагностики
                _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT);
              }
            }

            state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
            state_i2c_task |= STATE_USTUVANNJA_EEPROM_GOOD;
          
            //Скидаємо повідомлення у слові діагностики
            _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          }
          else
          {
            //Тип набору юстуючих коефіцієнтів не відповідає даному програмному забезпеченню

            //Помічаємо, що прочитаний блок юстування є пустим
            state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
            state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
            state_i2c_task |= STATE_USTUVANNJA_EEPROM_EMPTY;/*Не відповідність типу юстуючих коефіцієнтів -  це то саме що їх немає взагалі*/
        
            //Виствляємо повідомлення у слові діагностики
            _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          }
        }
        else
        {
          //Контрольна сума не сходиться
          state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
          state_i2c_task |= STATE_USTUVANNJA_EEPROM_FAIL;
          
          //Виствляємо повідомлення у слові діагностики
          _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
        }
      }
      else
      {
        //Помічаємо, що прочитаний блок юстування є пустим
        state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
        state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
        state_i2c_task |= STATE_USTUVANNJA_EEPROM_EMPTY;
        
        //Виствляємо повідомлення у слові діагностики
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
        _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_EMPTY_BIT);
      }
            
      //Знімаємо можливу сигналізацію, що виконувалося порівнняння
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_USTUVANNJA);
      //Скидаємо повідомлення про читання даних
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //Аналізуємо прочитані дані
//      //Спочатку аналізуємо, чи прояитаний блок є пустим, чи вже попередньо записаним
//      unsigned int empty_block = 1, i = 0; 
//      unsigned int trigger_active_functions_tmp[N_BIG];
//
//      while ((empty_block != 0) && ( i < (1 + sizeof(trigger_active_functions_tmp) + 1)))
//      {
//        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
//        i++;
//      }
//      
//      if(empty_block == 0)
//      {
//        //Помічаємо, що блок не є пустим
//        state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_EMPTY);
//        //Скидаємо повідомлення у слові діагностики
//        _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
//        
//        //Перевіряємо контрольну суму і переписуємо прочитані дані у тимчасові змінні
//        unsigned char crc_eeprom_trg_func = 0, temp_value;
//        unsigned char  *point;
//        unsigned int offset = 0;
//
//        point = (unsigned char*)(&trigger_active_functions_tmp); 
//        for (i =0; i < sizeof(trigger_active_functions_tmp); i++)
//        {
//          temp_value = read_write_i2c_buffer[offset + i];
//          *(point) = temp_value;
//          crc_eeprom_trg_func += temp_value;
//          point++;
//        }
//        offset +=  sizeof(trigger_active_functions_tmp);
//        
//        if (read_write_i2c_buffer[offset]  == ((unsigned char)((~(unsigned int)crc_eeprom_trg_func) & 0xff)))
//        {
//          //Контролдьна сума сходиться
//
//          //Скидаємо повідомлення у слові діагностики
//          _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
//          
//          //Зберігаємо контрольну суму (не інвертовану)
//          crc_trg_func = crc_eeprom_trg_func;
//          
//          if ((comparison_writing & COMPARISON_WRITING_TRG_FUNC) == 0)
//          {
//            //Виконувалося зчитування триґерної інформації
//            
//            //Перекидаємо триґерну інформацію у робочі змінні
//            for(unsigned int k = 0; k < N_BIG; k++) trigger_active_functions[k] = trigger_active_functions_tmp[k];
////            restore_trigger_functions(trigger_active_functions);
//          }
//          else
//          {
//            //Виконувалося контроль достовірності записаної інформації у EEPROM з записуваною
//            
//            unsigned int difference = 0;
//  
//            i = 0;
//            while ((difference == 0) && (i < N_BIG))
//            {
//              //Перевірка запису функцій значення яких зберігається у енергонезалежній пам'яті
//              if (trigger_active_functions_comp[i] != trigger_active_functions_tmp[i]) difference = 0xff;
//              else
//              {
//                i++;
//              }
//            }
//            
//            if (difference == 0)
//            {
//              //Контроль порівнняння пройшов успішно
//  
//              //Скидаємо повідомлення у слові діагностики
//              _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT);
//            }
//            else
//            {
//              //Контроль порівнняння зафіксував розбіжності між записаною і записуваною інформацією
//
//              //Виствляємо повідомлення у слові діагностики
//              _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT);
//            }
//          }
//
//          state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_FAIL);
//          state_i2c_task |= STATE_TRG_FUNC_EEPROM_GOOD;
//        }
//        else
//        {
//          //Контрольна сума не сходиться
//          state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_GOOD);
//          state_i2c_task |= STATE_TRG_FUNC_EEPROM_FAIL;
//          
//          //Виствляємо повідомлення у слові діагностики
//          _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
//        }
//      }
//      else
//      {
//        //Помічаємо, що прочитаний блок є пустим
//        state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_FAIL);
//        state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_GOOD);
//        state_i2c_task |= STATE_TRG_FUNC_EEPROM_EMPTY;
//        
//        //Виствляємо повідомлення у слові діагностики
//        _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
//        _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
//      }
//            
//      //Знімаємо можливу сигналізацію, що виконувалося порівнняння
//      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_TRG_FUNC);
//      //Скидаємо повідомлення про читання даних
//      _CLEAR_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //Аналізуємо прочитані дані
      //Спочатку аналізуємо, чи прояитаний блок є пустим, чи вже попередньо записаним
      unsigned int empty_block = 1, i = 0; 
      __INFO_REJESTRATOR info_rejestrator_pr_err_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__INFO_REJESTRATOR) + 1)))
      {
        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //Помічаємо, що блок не є пустим
        state_i2c_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY);
        //Скидаємо повідомлення у слові діагностики
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT);
        
        //Перевіряємо контрольну суму і переписуємо прочитані дані у структуру
        unsigned char crc_eeprom_info_rejestrator_pr_err = 0, temp_value;
        unsigned char  *point = (unsigned char*)(&info_rejestrator_pr_err_tmp); 
        for (i =0; i < sizeof(__INFO_REJESTRATOR); i++)
        {
          temp_value = read_write_i2c_buffer[i];
          *(point) = temp_value;
          crc_eeprom_info_rejestrator_pr_err += temp_value;
          point++;
        }
        if (read_write_i2c_buffer[sizeof(__INFO_REJESTRATOR)]  == ((unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_pr_err) & 0xff)))
        {
          //Контролдьна сума сходиться
          
          //Зберігаємо контрольну суму (не інвертовану)
          crc_info_rejestrator_pr_err = crc_eeprom_info_rejestrator_pr_err;

          state_i2c_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL);
          state_i2c_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD;
          
          //Скидаємо повідомлення у слові діагностики
          _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
          {
            //Виконувалося зчитування інформації по реєстратору програмних подій у робочу структуру
            
            //Перекидаємо інформації по реєстратору програмних подій з тимчасової структури у робочу структуру
            info_rejestrator_pr_err = info_rejestrator_pr_err_tmp;

            //Перевіряємо чи всі поляу у своїх допустимих межах
            if(
               (info_rejestrator_pr_err.next_address   >= MIN_ADDRESS_PR_ERR_AREA) && 
               (info_rejestrator_pr_err.next_address   <= MAX_ADDRESS_PR_ERR_AREA) &&
               (info_rejestrator_pr_err.number_records <= MAX_NUMBER_RECORDS_INTO_PR_ERR)  
              )
            {
              //Всі величину мають допустимі значення

              //Перевіряємо, чи у процесі запису останньої аварії не відбувся перезапуск/запуск приладу.
              //Тоді останій запис може бути пошкодженим, якщо вже свя флешка є заповнена
              //Тоді помічаємо, що у нашій флешці на один запис є менше
              //Перевіряємо, чи у процесі запису програмної події не відбувся перезапуск/запуск приладу.
              //Тоді записи у сторінці, яку записували може бути пошкодженими
              if (info_rejestrator_pr_err.saving_execution !=0 )
              {
                //Виставляємо повідомлення про цю подію
                _SET_BIT(set_diagnostyka, ERROR_PR_ERR_LOSS_INFORMATION_BIT);

                //Виставляємо команду запису цієї структури у EEPROM
                /*
                Команду виставляємо скоріше, а потім робимо зміни у полях, які треба змінити,
                бо по вимозі проконтролювати достовірність даних інформації по реєстратору
                програмних подій відбувається копіювання з переривання обслуговування DataFlash структури
                info_rejestrator_pr_err у резервну копію. Це копіювання блокується у випадку 
                "читання з"/"запису в" EEPROM цієї інформації. Тому виставлення спочатку команди
                запису заблокує копіювання.
                З другої сторони не можливо, щоб почався запис до модифікації, 
                бо запис ініціюється функцією main_routines_for_i2c - в якій ми зараз знаходимося.
                Тобто спочатку треба з цієї функції вийти і при наступних входженнях у цю функцію
                можливе виконання команди, яку ми виставили перед зміною даних, яку 
                ми зараз гарантовано зробимо (до виходу з цієї функції)
                */
                _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

                info_rejestrator_pr_err.saving_execution = 0;
                
                
              }   
            }
            else
            {
              //Виствляємо повідомлення у слові діагностики
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          
              //Виставляємо команду запису цієї структури у EEPROM
              /*
              Команду виставляємо скоріше, а потім робимо зміни у полях, які треба змінити,
              бо по вимозі проконтролювати достовірність даних інформації по реєстратору
              програмних подій відбувається копіювання з переривання обслуговування DataFlash структури
              info_rejestrator_pr_err у резервну копію. Це копіювання блокується у випадку 
              "читання з"/"запису в" EEPROM цієї інформації. Тому виставлення спочатку команди
              запису заблокує копіювання.
              З другої сторони не можливо, щоб почався запис до модифікації, 
              бо запис ініціюється функцією main_routines_for_i2c - в якій ми зараз знаходимося.
              Тобто спочатку треба з цієї функції вийти і при наступних входженнях у цю функцію
              можливе виконання команди, яку ми виставили перед зміною даних, яку 
              ми зараз гарантовано зробимо (до виходу з цієї функції)
              */
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

              //Очищаємо структуру інформації по реєстраторі програмних подій
              info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
              info_rejestrator_pr_err.saving_execution = 0;
              info_rejestrator_pr_err.number_records = 0;
            }
          }
          else
          {
            //Виконувалося контроль достовірності записаної інформації у EEPROM з записуваною
            
            unsigned char  *point_to_read  = (unsigned char*)(&info_rejestrator_pr_err_tmp );
            unsigned char  *point_to_write = (unsigned char*)(&info_rejestrator_pr_err_comp);
            unsigned int difference = 0;

            i = 0;
            while ((difference == 0) && ( i < sizeof(__INFO_REJESTRATOR)))
            {
              if (*point_to_write != *point_to_read) difference = 0xff;
              else
              {
                point_to_write++;
                point_to_read++;
                i++;
              }
            }
            if (difference == 0)
            {
              //Контроль порівнняння пройшов успішно

              //Скидаємо повідомлення у слові діагностики
              _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT);
            }
            else
            {
              //Контроль порівнняння зафіксував розбіжності між записаною і записуваною інформацією

              //Виствляємо повідомлення у слові діагностики
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT);
            }
          }
        }
        else
        {
          //Контрольна сума не сходиться
          state_i2c_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD);
          state_i2c_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL;
          
          //Виствляємо повідомлення у слові діагностики
          _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          
          /*
          Виставляємо повідомлення про те, що в EEPROM треба записати нові значення
          структури тільки тоді, коли ми зчитуємо збережені дані для відновлення 
          їх у оперативній пам'яті, а не коли ми проводимо контроль запису.
          Бо для контролю запису нам важливо знати чи успішно записалися дані, які є у 
          оперативній пам'яті і при цьому, навіть, якщо запис відбувся невдало, то,
          оскільки ми працюємо зі змінними з оперативної пам'яті,  які є у нас достовірні,
          бо ми їх якраз і записували, то на роботу до перезавантаження програмного забезперечння 
          збій запису у EEPROM не мав би вплинути
          */
          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
          {
            //Виконувалося зчитування інформації по дискретному реєстратору у робочу структуру

            //Виставляємо команду запису цієї структури у EEPROM
            /*
            Команду виставляємо скоріше, а потім робимо зміни у полях, які треба змінити,
            бо по вимозі проконтролювати достовірність даних інформації по реєстратору
            програмних подій відбувається копіювання з переривання обслуговування DataFlash структури
            info_rejestrator_pr_err у резервну копію. Це копіювання блокується у випадку 
            "читання з"/"запису в" EEPROM цієї інформації. Тому виставлення спочатку команди
            запису заблокує копіювання.
            З другої сторони не можливо, щоб почався запис до модифікації, 
            бо запис ініціюється функцією main_routines_for_i2c - в якій ми зараз знаходимося.
            Тобто спочатку треба з цієї функції вийти і при наступних входженнях у цю функцію
            можливе виконання команди, яку ми виставили перед зміною даних, яку 
            ми зараз гарантовано зробимо (до виходу з цієї функції)
            */
            _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

            //Очищаємо структуру інформації по реєстраторі програмних подій
            info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
            info_rejestrator_pr_err.saving_execution = 0;
            info_rejestrator_pr_err.number_records = 0;
          }
        }
      }
      else
      {
        //Помічаємо, що прочитаний блок є пустим
        state_i2c_task &= (unsigned int)(~(STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL | STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD));
        state_i2c_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY;
        
        //Виствляємо повідомлення у слові діагностики
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT);

        /*
        Виставляємо повідомлення про те, що в EEPROM треба записати нові значення
        структури тільки тоді, коли ми зчитуємо збережені дані для відновлення 
        їх у оперативній пам'яті, а не коли ми проводимо контроль запису.
        Бо для контролю запису нам важливо знати чи успішно записалися дані, які є у 
        оперативній пам'яті і при цьому, навіть, якщо запис відбувся невдало, то,
        оскільки ми працюємо зі змінними з оперативної пам'яті,  які є у нас достовірні,
        бо ми їх якраз і записували, то на роботу до перезавантаження програмного забезперечння 
        збій запису у EEPROM не мав би вплинути
        */
        if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
        {
          //Виконувалося зчитування інформації по дискретному реєстратору у робочу структуру

          //Виставляємо команду запису цієї структури у EEPROM
          /*
          Команду виставляємо скоріше, а потім робимо зміни у полях, які треба змінити,
          бо по вимозі проконтролювати достовірність даних інформації по реєстратору
          програмних подій відбувається копіювання з переривання обслуговування DataFlash структури
          info_rejestrator_pr_err у резервну копію. Це копіювання блокується у випадку 
          "читання з"/"запису в" EEPROM цієї інформації. Тому виставлення спочатку команди
          запису заблокує копіювання.
          З другої сторони не можливо, щоб почався запис до модифікації, 
          бо запис ініціюється функцією main_routines_for_i2c - в якій ми зараз знаходимося.
          Тобто спочатку треба з цієї функції вийти і при наступних входженнях у цю функцію
          можливе виконання команди, яку ми виставили перед зміною даних, яку 
          ми зараз гарантовано зробимо (до виходу з цієї функції)
          */
          _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

          //Очищаємо структуру інформації по реєстраторі програмних подій
          info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
          info_rejestrator_pr_err.saving_execution = 0;
          info_rejestrator_pr_err.number_records = 0;
        }
      }

      //Знімаємо можливу сигналізацію, що виконувалося порівнняння
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR);
      //Скидаємо повідомлення про читання даних
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT) !=0)
    {
      //Аналізуємо прочитані дані
      if (
          ((read_write_i2c_buffer[0xA ] & (1<< 6)) == 0 ) /*SQWE = 0*/ ||
          ((read_write_i2c_buffer[0xC] &  (1<< 6)) != 0 ) /*HT  = 1 */ ||
          ((read_write_i2c_buffer[0x13]          ) != 0xf0) /*Потрібна частота*/ 
         )
      {
        //Треба потрібні біти  і слова виставити у робочі значення, щоб на виході отримати 1гц
        temp_register_rtc[0] = read_write_i2c_buffer[0xC ] & (unsigned char)(~ (1<< 6));
        temp_register_rtc[1] = read_write_i2c_buffer[0xA ] | (1<< 6);

        //Повідомлення про цю несправність виставляємо, коли не йде тільки-но перше зчитування
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 ) _SET_BIT(set_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
        else _SET_BIT(clear_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
        
        etap_settings_test_frequency = 0;
        _SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT);
      } 
      else
        _SET_BIT(clear_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
      
      if ((read_write_i2c_buffer[0x1] &  (1<< 7)) != 0) /*ST = 1 */
      {
        //Треба запустиити осцилятор для RTC
        _SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT);
      }
      else if ((etap_reset_of_bit < ETAP_CLEAR_OF_ST_STOP) && ((read_write_i2c_buffer[0xf] & (1<<2)) != 0))
      {
        _SET_BIT(set_diagnostyka, RTC_OSCILLATOR_FAIL_BIT);
        //Треба ST-біт виставити в 1 і негайно скинути його в 0. Почекати через 5 секунд він має скинутися
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 )
        {
          etap_reset_of_bit = ETAP_CLEAR_OF_ST_STOP;
          _SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
        }
        else
          etap_reset_of_bit = ETAP_CLEAR_OF_ST_START_WAITING_5S;
      }
      else if (etap_reset_of_bit == ETAP_CLEAR_OF_WRITE_OF_0)
      {
        //Треба очистити OF-біт
        temp_value_for_rtc = read_write_i2c_buffer[0xf];
        _SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
      
      if ((read_write_i2c_buffer[0xC] & (1<< 6)) != 0)
      {
        //Повідомлення про цю несправність виставляємо, коли не йде тільки-но перше зчитування
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 )_SET_BIT(set_diagnostyka, RTC_UPDATING_HALTED_BIT);
        else _SET_BIT(clear_diagnostyka, RTC_UPDATING_HALTED_BIT);
      }
      else _SET_BIT(clear_diagnostyka, RTC_UPDATING_HALTED_BIT);
      if ((read_write_i2c_buffer[0x1] &  (1<< 7)) != 0) _SET_BIT(set_diagnostyka, RTC_OSCILLATOR_STOPED_BIT);
      else _SET_BIT(clear_diagnostyka, RTC_OSCILLATOR_STOPED_BIT);
      if ((read_write_i2c_buffer[0xF] &  (1<< 4)) != 0) _SET_BIT(set_diagnostyka, RTC_BATTERY_LOW_BIT);
      else _SET_BIT(clear_diagnostyka, RTC_BATTERY_LOW_BIT);
      if ((read_write_i2c_buffer[0xF] &  (1<< 2)) == 0) _SET_BIT(clear_diagnostyka, RTC_OSCILLATOR_FAIL_BIT);
      
      if((state_i2c_task & STATE_FIRST_READING_RTC) !=0)
      {
        //Зараз відбувається перше зчитування даних з RTC - скидаємо біт першого читання
        state_i2c_task &= (unsigned int)(~STATE_FIRST_READING_RTC);
      }

      //Обновлюємо час
      copying_time = 1; //Помічаємо, що зараз обновляємо масив часу
      time[0] = read_write_i2c_buffer[0] & 0xff;
      time[1] = read_write_i2c_buffer[1] & 0x7f;
      time[2] = read_write_i2c_buffer[2] & 0x7f;
      time[3] = read_write_i2c_buffer[3] & 0x3f;
      time[4] = read_write_i2c_buffer[5] & 0x3f;
      time[5] = read_write_i2c_buffer[6] & 0x1f;
      time[6] = read_write_i2c_buffer[7] & 0xff;
      copy_register8_RTC = read_write_i2c_buffer[8];
      calibration = copy_register8_RTC & 0x3f;

      copying_time = 0; //Помічаємо, що обновлення масив часу завершене
      //Робимо копію масиву часу для того, щоб коли основний масив буде обновлятися можна було іншим модулям взяти попереднє, але достовірне значення часу і дати з цього масиву
      for(unsigned int i = 0; i < 7; i++) time_copy[i] = time[i];
      calibration_copy = calibration;
      
      if(
         (_CHECK_SET_BIT(    diagnostyka, EVENT_START_SYSTEM_BIT  ) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT  ) != 0) ||
         (_CHECK_SET_BIT(    diagnostyka, EVENT_RESTART_SYSTEM_BIT) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT) != 0)
        )
      {
        //До цього часу ще не зчитано першої реальної часової мітки
        if((read_write_i2c_buffer[0xC] & (1<< 6)) != 0)
        {
          //Зчитано час, коли пропало живлення з RTC внаслідок виключення пристрою
          fixed_power_down_into_RTC = 1; //Виставляємо повідомлення про те, що було зафіксовано пропадання живлення на годиннику RTC до того, як програма стартувала спочатку

          if ((head_fifo_buffer_pr_err_records > 1) && (tail_fifo_buffer_pr_err_records == 0))
          {
            //Це перестраховка, бо завжди у цьому місці має бути як мінімум два записи в буфері FIFO подія про зупинку роботи приладу і старт/рестарт системи, а запис у мікросхему dataFlash ще  є забороненй
            unsigned int local_point_for_time = tail_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR + 1 ; //Індекс першого числа часу у вже першому записі (перший запис відподає за подію - зупинку роботи приладу) (tail_fifo_buffer_pr_err_records має дорівнювати 0 у ціьому місці програми)
            //Час, який зараз прочитаний з RTC до моменту скидання біту HT вказує на час до пропадання живлення з годинника RTC
            for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[local_point_for_time + i] = time[i]; /*використовувати time_copy і calibration_copy не треба бо іде обробка одної функції main_routines_for_i2c*/ 
          }
        }
        else
        {
          //Зчитано першу часову мітку з моменту запуску/перезапуску програми
          unsigned int local_point_for_time;

          if (fixed_power_down_into_RTC == 0)
          {
            //Це означає, що програма не зафікусала факт пропадання живлення на годиннику RTC до моменту запуску/перезапуску програми
            /*
            Тому подію про зупинку пристрою трбе очистити із очікуваних на запис
            шляхом встановлення "хвоста" буферу FIF0  в значення 1
            (індес 0 до моменту розблокування запису в реєстратор програмних подій,
            згідно розробленого програмного забезпечення  - це подія про зупинку роботи приладу,
            а 1 - це наступна подія)
            */
            if ((head_fifo_buffer_pr_err_records > 0) && (tail_fifo_buffer_pr_err_records == 0))
            {
              //Це перестраховка, бо завжди у цьому місці має бути як мінімум два записи в буфері FIFO подія про зупинку роботи приладу і старт/рестарт системи, а запис у мікросхему dataFlash ще  є забороненй
              /*
              Якби перша половина цієї умови (head_fifo_buffer_pr_err_records > 0)
              по незрозумілій причині для мене не виконувалася то тоді ми нічого не міняємо, і тоді 
              head_fifo_buffer_pr_err_records = 0 і tail_fifo_buffer_pr_err_records = 0,
              а це буде означати. що немає нових записів у черзі до запису і тому я думаю. що нічого 
              надзвичайного не мало б статися. Хоч це і неможливо, на мій погляд, і з точки зору ідеології
              розробленого програмного забезпечення.
              
              Якби ця умова по незрозумілій причині для мене не виконувалася повністю.
              То я з нову ж таки не можу зрозуміти, чого така виникла ситтуація, але думю. що тоді ніяких корекцій
              не варта робити, бо хоч це і неможливо, на мій погляд, і з точки зору ідеології
              розробленого програмного забезпечення  - аде я не думаю, що це б привело до неправильної 
              роботи "основної" частини програмного забезпечення
              */
              tail_fifo_buffer_pr_err_records += 1;
              while(tail_fifo_buffer_pr_err_records >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail_fifo_buffer_pr_err_records -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
            }

            local_point_for_time = tail_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR + 1; //Індекс першого числа часу у першому записі, який чекає на запис у DataFlash
          }
          else
          {
            local_point_for_time = (tail_fifo_buffer_pr_err_records + 1)*SIZE_ONE_RECORD_PR_ERR + 1; //Індекс першого числа часу у другому записі, який чекає на запис у DataFlash
          }

          //Встановлюємо часові мітки для тих подій, які мали місце до зчитування першої реальної часової мітки
          /*
          Змінна local_point_for_time зараз вказує на перше число часу другого запису (якщо була фіксація виключення живлення перед стартом),
          або першого запису (якщо пропадання живлення на RTC перед стартом програми не було зафіксовано)
          */
          
          //Блокуємо початок записування підготовлених записів до моменту гарантованого розставляння всіх часових міток
          temporary_block_writing_records_pr_err_into_DataFlash = 1;
          /*Цикл у циклі з однаковою умовою завершення я зробив для того, що 
          ця частина коду може у будь-який момент часу буде перервана вищепріоритетною
          роботою, яка сформує новий запис (але часову мітку ставить тоді,
          коли зняті події про запуск/перезапуск ). Крім того тут я знімаю в діагностіиці
          подію про запуск/перезапуск програми, що є також умовою блокування старту
          записування у мікросхему DataFlash і, саме головне, встановлення часових міток
          з модуля формування запису.
          Тому, теоретично може бути, що часові мітки жве всі виставлені, але до моменту
          зняття події запуску/перезапуску, сформувався новий запис у якого не буде часової мітки.
          Тому повторна перевірка після зняття заборони встановлення часових міток у модулі 
          формування запису, мала б повторно перейти до довстановлення часових міток
          у такоих записах.
          Аж після успішного повторного підтвердження розставляння часових міток буде розблоковно
          записування записів у мікросхему DataFlash.
          При цьому не треба боятися, що у такий момент, що часові сітки дозволені 
          і з модуля формування запису і дорозставляння часових міток з цієї частини програми
          буде втачена достовірність часової мітки, бо поки ми не вийдемо з цієї
          частини програми, то не буде запущено читання нового значення часу. Тобто
          на цей момент часу не боже бути "свіжішої" часової мітки, ніж та що є зараз. 
          І старшою часовою часовоюміткою може бути тільки мітка вимкнення приладу.
          */
          do
          {
            while (
                   (local_point_for_time < (head_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR)) &&
                   (local_point_for_time <  SIZE_BUFFER_FOR_PR_ERR)
                  )
            {
              for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[local_point_for_time + i] = time[i]; /*використовувати time_copy і calibration_copy не треба бо іде обробка одної функції main_routines_for_i2c*/ 
              local_point_for_time += SIZE_ONE_RECORD_PR_ERR;
            }

            //Скидаємо біти запуску програми або її перезапуску
            _SET_BIT(clear_diagnostyka, EVENT_START_SYSTEM_BIT);
            _SET_BIT(clear_diagnostyka, EVENT_RESTART_SYSTEM_BIT);
          }
          while (
                 (local_point_for_time < (head_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR)) &&
                 (local_point_for_time <  SIZE_BUFFER_FOR_PR_ERR)
                );
          //Розблоковуємо початок записування підготовлених записів, бо я вважаю, що часові мітки я вже гарантовано розставив
          temporary_block_writing_records_pr_err_into_DataFlash = 0;
        }
      }

      //Скидаємо повідомлення про читання системного часу
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT) !=0)
    {
      //Виставляємо команду читання системного часу 
      _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);

      _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0)
    {
      etap_settings_test_frequency++;
      if (etap_settings_test_frequency > 2)
      {
        etap_settings_test_frequency = -1;

        //Повторно запускаємо читання регістрів RTC
        _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);

        //Скидаємо біт виставляння бітів і полів у потрібні значення, якщо всі поля записані
        _CLEAR_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT) !=0)
    {
      //Скидаємо біт запуску осцилятора RTC
      _CLEAR_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0)
    {
      etap_reset_of_bit++;
      if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_START_WAITING_5S)
      {
        //Скидаємо запущені операції попереднього  скидання OF-біту, але ще маємо витримати 5с для остаточного скидання OF-біту
        _CLEAR_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
      else if (etap_reset_of_bit >= ETAP_CLEAR_OF_WRITE_OF_0)
      {
        //Скидаємо запущені операції скидання OF-біту
        etap_reset_of_bit = ETAP_CLEAR_OF_NONE;
        _CLEAR_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
    }
    else
    {
      //Сюди, теоретично, ніколи не мала б дійти
      //У всіх інакших випадках нічого не робимо
    }
    /*************************************************/
  }
  else if (driver_i2c.state_execution == 2)
  {
    /*************************************************/
    //Обмін завершився з помилкою
    /*************************************************/

    //Покищо просто очищаємо змінну, яка конкретизуєм помилку, у майбутньому її можна буде конкретизувати
    type_error_of_exchanging_via_i2c = 0;
    
    //Виставляємо повідомлення, що I2C готовий до нової транзакції 
    driver_i2c.state_execution = -1;

    //Визначаємося з наступними діями
    if (
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT                 ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT               ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT             ) != 0) ||
//        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT               ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
       )
    {
      //Стоїть умова запису блоку у EEPROM
      //Залишаємо номер блоку для запису в EEPROM той самий, бо немає підтвердження, що він записався
      //Виставляємо біт тимчасового блокування запису, щоб витримати певну павзу і запустити запис після більш пріоритетних завдвнь  
      //Згідно документації операція запису відбувається до 5 мс
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT) !=0)
    {
      //Стоїть умова читання блоку у EEPROM конфігурації
      
      //Повторно запускаємо процес читання
      _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //Стоїть умова читання блоку у EEPROM настройок
      
      //Повторно запускаємо процес читання
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //Стоїть умова читання блоку у EEPROM юстування
      
      //Повторно запускаємо процес читання
      _SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //Стоїть умова читання блоку у EEPROM стану тригерної інформації
//      
//      //Повторно запускаємо процес читання
//      _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
//      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
//      _CLEAR_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //Стоїть умова читання блоку у EEPROM по реєстраторі програмнихподій
      
      //Повторно запускаємо процес читання
      _SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT) !=0)
    {
      //Стоїть умова читання RTC
      
      //Повторно запускаємо процес читання RTC
      _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT) !=0)
    {
      //Стоїть умова запису RTC
      
      //Повторно запускаємо процес запису RTC
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
    }
    else if (
             (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT          ) !=0) ||
             (_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0) ||
             (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT          ) !=0)
            )
    {
      //Повторно запускаємо операцію з того самого місця, яка не вийшла
    }
    else
    {
      //У всіх інакших випадках нічого не робимо
    }
    /*************************************************/
  }
}
/*****************************************************/

/*****************************************************/
//Перенастроювання I2C при періодичному неуспішному запуску трансакції
/*****************************************************/
void error_start_i2c(void)
{
  _SET_BIT(set_diagnostyka, ERROR_START_VIA_I2C_BIT);
          
  /**************/
  //Переконфігуровуємо I2C
  /**************/
  //Зупиняємо геренацію переривань від I2C
  I2C_ITConfig(I2C, I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF, DISABLE);
           
  //Зупиняємо потоки DMA якщо вони запущені
  if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
          
  //Переконфігуровуємо I2C
  Configure_I2C(I2C);
  /**************/
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/

