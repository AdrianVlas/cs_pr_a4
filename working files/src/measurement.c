#include "header.h"

/*****************************************************/
//��������� �������� ����� � ���
/*****************************************************/
void control_reading_ADCs(void)
{
  //���������� ������ �������� ����� � �������� �� ������ ����� ������������
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
    � ������, �� ������� �� ���������
    */
    while ((command_word_adc_diff & (1 << active_index_command_word_adc)) == 0)
    {
      /*
      �� �� �������� ������, ���� ����� ������������
      */
      active_index_command_word_adc = (active_index_command_word_adc + 1) % NUMBER_INPUTs_ADCs;
    }
      
    /*
    ����� active_index_command_word_adc ����� � ����� input_adc �� �����, 
    ���� ����� ����������
    */
      
//    /*
//    ���������, ���� ����� �������� ���
//    */
//    unsigned int active_adc_old = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 1 : 2;
//
    /*
    ���������, ���� ����� ����� ������������ ��� � �� ��� ����� ��������
    */
//    unsigned int active_adc_new = input_adc[active_index_command_word_adc][0];
    unsigned int command_word = input_adc[active_index_command_word_adc][1];
    
    //��������� ��������� ����
    if (
        (state_reading_ADCs == STATE_READING_ADCs_NONE) ||
        (state_reading_ADCs == STATE_READING_READ     )
       )
    {
      state_reading_ADCs = STATE_READING_WRITE;
//      /*
//      ��������� ��������� ���
//      */
//      switch (active_adc_new)
//      {
//      case 1:
//        {
//          //���1
//          GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
//          break;
//        }
//      default:
//        {
//          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
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
      �������, �� ����� ������ ���� �������� ����� ����������
      */
      command_word_adc_work |= (1 << active_index_command_word_adc);
    }

    //�������� �������� �����
    while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
    GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
    SPI_ADC->DR = (uint16_t)command_word;                   //³���������� �������� �����
  }
  else 
  {
    if (
        (state_reading_ADCs == STATE_READING_READ     ) ||
        (state_reading_ADCs == STATE_READING_ADCs_NONE)
       )
    {
      //�� ������ ��� ���������
      state_reading_ADCs = STATE_READING_ADCs_NONE;

      command_word_adc = 0;
      command_word_adc_work = 0;
      active_index_command_word_adc = 0;
    }
    else
    {
      /*
      ����� �� �������� �������� � ���������� ��������, ���� ����� �����
      ���� �������������
      */
      state_reading_ADCs = STATE_READING_READ;
      while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
      GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
      SPI_ADC->DR = 0;                                        //³���������� ����� (��� ���, ��� ���� ���������� ����� �� ������������)
    }
  }
}
/*****************************************************/

/*************************************************************************
����������� ���������� ��������
 *************************************************************************/
void operate_test_ADCs(void)
{
  /*******************************************************
  ������������� ���������� �������� ����������� �����
  *******************************************************/
  unsigned int temp;

  //GND ��� ���
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
  
  //VREF ��� ���
  temp = output_adc[C_VREF_ADC].value;
  vref_adc_averange_sum += temp;
  vref_adc_averange_sum -= vref_adc_moment_value[index_array_of_one_value];
  vref_adc_moment_value[index_array_of_one_value] = temp;
  vref_adc = vref_adc_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp < 0x614) || (temp > 0x9EB)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC_TEST_COARSE_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VREF_ADC_TEST_COARSE_BIT);
  
  //VDD ��� ���
  temp = output_adc[C_VDD_ADC].value; 
  vdd_adc_averange_sum += temp;
  vdd_adc_averange_sum -= vdd_adc_moment_value[index_array_of_one_value];
  vdd_adc_moment_value[index_array_of_one_value] = temp;
  vdd_adc = vdd_adc_averange_sum >> VAGA_NUMBER_POINT;
  if ((temp <0x6F2) || (temp > 0xD48)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC_TEST_COARSE_BIT);
  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC_TEST_COARSE_BIT);

  //�� ������ ���� �������� �� ��� ����������  
  if((++index_array_of_one_value) == NUMBER_POINT)
    index_array_of_one_value = 0;
  else if (index_array_of_one_value > NUMBER_POINT)
  {
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(21);
  }
  /*******************************************************/
}
/*************************************************************************/

/*************************************************************************
����������� ��� ��� ������ ���� �������� ������� �������
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
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(58);
  }

  //��������� ��� ����� ������
  unsigned int bank_sum_sqr_data_tmp = bank_sum_sqr_data;
  for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++ ) sum_sqr_data[bank_sum_sqr_data_tmp][i] = sum_sqr_data_irq[i];
}
/*************************************************************************/

/*****************************************************/
//����������� �� ���������� ����� �� ������ SPI, ���� ��������� ����������� �������
/*****************************************************/
void SPI_ADC_IRQHandler(void)
{
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordEnterISR();
//#endif

  //Գ����� ���� � ����������� ������� ����� �� ���
  semaphore_adc_irq  = true;
  
  //Գ����� ��� ���������
  uint32_t tick_output_adc_tmp = TIM5->CNT;
  
  //�� ������ ������� ������ chip_select
  GPIO_SPI_ADC->BSRRL = GPIO_NSSPin_ADC;
  uint16_t read_value = SPI_ADC->DR;

  static uint32_t tick_output_adc_p;
  /*
  �������� ������� ���
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
  
  //�������� �������� � ������� ���
  control_reading_ADCs();
  
  /*
  �������� �� �������� ����� ���, ���� �� ������ ��� ���������
  */
  if (state_reading_ADCs == STATE_READING_ADCs_NONE)
  {
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
    /*******************************************************/
    //����������, �� ���������� ���� ���������
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ ������������ �������� (� ��� ����� ����� ��� �� ���������)*/
    {
      //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        ustuvannja_meas[k] = ustuvannja[k];
      }
    }
    /*****************************************************/

    /*
    ������� �������� ������������� ������
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
    //������� �������� I1
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
    //������� �������� I2
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
    //������� �������� I3
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
    //������� �������� U
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
      //����������� ����������� ��� ���������� ������ ����� ����� ������������ �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_VAL;
      /**************************************************/
    }
    
    /********************************************************
    ������� ����� ������� �������
    ********************************************************/
    for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
    {
      //�������� ����������
      current_data[index_array_of_current_data_value++] = ADCs_data[i];
    }
    //������ ��������� �����������
    if (index_array_of_current_data_value >= (NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT)) index_array_of_current_data_value = 0;/*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
    /**************************************************/

    /**************************************************/
    //��� ����������� ����������� ��� ����� � ���������� ������� �������
    /**************************************************/
    if (wait_of_receiving_current_data  == true) wait_of_receiving_current_data  = false;
    /**************************************************/

    if ((status_adc_read_work & TEST_VAL_READ) != 0)
    {
      //����� ���������� ���������� ��������
      operate_test_ADCs();
    
      status_adc_read_work &= (unsigned int)(~TEST_VAL_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� �������� �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_TEST_VAL;
      /**************************************************/
      
      /**************************************************/
      //���� ����� ����� ���������� �� ���� ������
      /**************************************************/
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ����� � ����������� ��� �������� I2C
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
    //����� ���� �� ������� �������� control_reading_ADCs
    
    /*
    ������� � ���� ���������� ������� ������� control_reading_ADCs �� ������
    ������� ����������� �� ������� ��������� ��� ������ �� ���������
    */
    
    /*
    ����������� ��������� ����������, ��� ���� �� �������� ��� ���� ����� �����
    �� ��������� �� ����� �� ���������
    */
    __disable_interrupt();
    
    /*
    ��������, �� ���� ����� ����� �� ��������� � ���� �� ������ ������� �����
    ����� �� ���������, �� ������������ ��������� ������� ��������� � �����������
    ������� ( chip select ����������� � 1)
    */
    if (
        (adc_DATA_VAL_read == false) &&
        (adc_TEST_VAL_read == false)
       )
    {
      semaphore_adc_irq  = false;
    }
    
    /*
    ���������� ��������� ����������
    */
     __enable_interrupt();
  }
  else semaphore_adc_irq  = false;

  
  if (semaphore_adc_irq  != false)
  {
    /*
    �� ����� ���� ���� ����� � ������ �������: ���� ��� ����� �� ��� ��� �� ���������
    � ������� ��������� ������� ������� control_reading_ADCs �� �������� ����������
    �������� __disable_interrupt ��� ������� ���������.
    
    ������ � ���� ������� ������� control_reading_ADCs. �������� �� ����, ��
    chip_select ������ ����������� � ������� ���� (�� �� ������� �������� 
    if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)) � ����� semaphore_adc_irq ��
    �� ���� false, � ��� ����� ����� ������ ��������� � ����������� �������
    */
    
    control_reading_ADCs();
    
    /*
    ������� ���������. ���� �������� �� �� � ���������� ������� ����������� �����, �� ������� �� SPI
    ����������. ��� ��� ��������� ��� ����� �� �����, �� ������ ������� control_reading_ADCs
    ��� ����������� ����, �� ��� �� ��������� "������ � ����"  ������ ������
    ��������� - � �� ������� ����� ���, ���� chip_select ���� �������� ���� ������������ � ������� �����
    
    � ������������ chip_select ����� � ������� ����� ����� ���� ����� ����������� ����������� ��
    ����� SPI
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
