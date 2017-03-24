#include "header.h"


/*****************************************************/
//�����  ������ ������ �� I2C
/*
  ���������
  0 - ������� ����� ����
  1 - ������ ��� �������
  2 - �� ��������� ���� ����� ������� �� i2C
*/
/*****************************************************/
unsigned int start_write_buffer_via_I2C(uint32_t device_id, uint16_t WriteAddr,  uint8_t volatile* pBuffer, uint32_t number)
{
  unsigned int error = 0; //0 - ������ ��������; 1 - ��� �������; 2 - ���� �������
  //���������� �� � ������ ������ ���������� ���������� ������ �������� �������
  if (type_error_of_exchanging_via_i2c != 0)
  {
    type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
    error = 2;
  }
  else
  {
    /*���������� �� ��� � �������� �� ������ ������� ���� �������*/
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
      //��������, �� � ���������� ���
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
      //������� ������� BUSY �����
      number_busy_state = 0;

      //���������� ��������� �������� ����� ����� I2C
      driver_i2c.state_execution = 0;
      driver_i2c.device_id = device_id;
      driver_i2c.action = 2;
      driver_i2c.internal_address = WriteAddr;
      driver_i2c.number_bytes = number;
      driver_i2c.point_buffer = pBuffer;
      
      //����������� ��������� ACK �������� ������� (��� ��� �������� ������ ��� �� �� ��� �� ��������)
      I2C_AcknowledgeConfig(I2C, ENABLE);

      /*������� ������ �������, �� ������ ���� ������������ � ������ �������*/
      I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
      
      /* ���������� ��� I2C ��������� ���������� �� ����� */
      I2C_ITConfig(I2C, I2C_IT_EVT, ENABLE);
      
      /* �������� STRAT*/
      I2C_GenerateSTART(I2C, ENABLE);
    }
  }
  
  return error;      
}
/*****************************************************/

/*****************************************************/
//�����  ������� ������ �� I2C
/*
  ���������
  0 - ������� ����� ����
  1 - ������ ��� �������
  2 - �� ��������� ���� ����� ������� �� i2C
*/
/*****************************************************/
unsigned int start_read_buffer_via_I2C(uint32_t device_id, uint16_t ReadAddr, uint8_t volatile* pBuffer, uint32_t number)
{
  unsigned int error = 0; //0 - ������ ��������; 1 - ��� �������; 2 - ���� �������
  //���������� �� � ������ ������ ���������� ���������� ������ �������� �������
  if (type_error_of_exchanging_via_i2c != 0)
  {
    type_error_of_exchanging_via_i2c |= (1<<ERROR_TOTAL_BIT);
    error = 2;
  }
  else
  {
    /*���������� �� ��� � �������� �� ������ ������� ���� �������*/
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
      //��������, �� � ���������� ���
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
      //������� ������� BUSY �����
      number_busy_state = 0;
      
      //���������� ��������� �������� ����� ����� I2C
      driver_i2c.state_execution = 0;
      driver_i2c.device_id = device_id;
      driver_i2c.action = 0;
      driver_i2c.internal_address = ReadAddr;
      driver_i2c.number_bytes = number;
      driver_i2c.point_buffer = pBuffer;
      
      //����������� ��������� ACK �������� �������
      I2C_AcknowledgeConfig(I2C, ENABLE);

      /*������� ������ �������, �� ������ ���� ������������ � ������ �������*/
      I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
      
      /* ���������� ��� I2C ��������� ���������� �� ����� */
      I2C_ITConfig(I2C, I2C_IT_EVT, ENABLE);
      
      /* �������� STRAT*/
      I2C_GenerateSTART(I2C, ENABLE);
    }
  }
  
  return error;      
}
/*****************************************************/

/*****************************************************/
//��������� ������ ����� I2C
/*****************************************************/
void main_routines_for_i2c(void)
{
  //�������� �����, ��� ����� ���� ���� ������������ ����� ���������� � EEPROM
  static unsigned int number_block_config_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ��������� ����� ���������� � EEPROM
  static unsigned int number_block_settings_write_to_eeprom;
  //�������� �����, ��� ����� � ��� ������ ����� ������ ���������� ������������ � EEPROM
  static size_t shift_from_start_address_settings_in_eeprom;
  //�������� �����, ��� ����� ������ ���� ����������� ����������� ��� ������ � EEPROM
  static size_t size_settings;
  //�������� �����, ��� ����� ���� ���� ��������� ����� ���������� � EEPROM
  static unsigned int number_block_ustuvannja_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ������� ���������� ����� ���������� � EEPROM
//  static unsigned int number_block_trg_func_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ���������� �� ��������� ���������� ���� ����� ���������� � EEPROM
  static unsigned int number_block_info_rejestrator_pr_err_write_to_eeprom;
  
  static unsigned int temp_value_for_rtc;
  
  //������� ���� ��� �������� ���������� ������
  static __CONFIG current_config_comp;
  static unsigned int ustuvannja_comp[NUMBER_ANALOG_CANALES], serial_number_dev_comp;
//  static unsigned int trigger_active_functions_comp[N_BIG];
  static __INFO_REJESTRATOR info_rejestrator_pr_err_comp;
  
  if (driver_i2c.state_execution < 0)
  {
    /*************************************************/
    //����� ����� ��������� ���� ���������� ����� I2C
    /*************************************************/
    
    if(_CHECK_SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT) !=0)
    {
      unsigned int rez;
      
      //����������� ������� RTC � ������ ������� �������� ��� ����, ��� �� ����� ���� 1 ��
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
      
      //�������� �������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
    }
    else if((_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0) || (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT) !=0))
    {
      unsigned int rez;
      
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0)
      {
        //�������� OF-�� � RTC
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
      
      //�������� �������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
    }
    else if(
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT) !=0) ||
            (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT)      !=0)
           )
    {
      //����� ����� �������� � �������� ����������, ���� ������ �������� � ���� ����������
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ������������

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_config_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(__CONFIG) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_CONFIG_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_CONFIG_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //�������� �������� ������� ������ ������
        if (rez > 1)
        {
          error_start_i2c();          
          
          //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //���� ����� ������������ ��� ���������
        
        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_CONFIG;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        
        //������� ����� ������ ������������ � EEPROM
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ���������

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_settings_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = size_settings - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_SETTINGS_IN_EEPROM + shift_from_start_address_settings_in_eeprom + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_SETTINGS_IN_EEPROM + shift_from_start_address_settings_in_eeprom + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //�������� �������� ������� ������ ������
        if (rez > 1)
        {
          error_start_i2c();          
          
          //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //������ ������ ����������� ��� ��������
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ���������

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_ustuvannja_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (SIZE_USTUVANNJA + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_USTUVANNJA_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_USTUVANNJA_IN_EEPROM + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //�������� �������� ������� ������ ������
        if (rez > 1)
        {
          error_start_i2c();          
          
          //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //���� ����� ��������� ��� ���������

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_USTUVANNJA;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        
        //������� ����� ������ ��������� � EEPROM
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT);
      }
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //����� ����� ������ ����� ������� ����������
//
//      int size_to_end;
//      unsigned int rez, offset_from_start;
//      
//      //��������� � ����� ���� ����� ������ ����������
//      offset_from_start = number_block_trg_func_write_to_eeprom*SIZE_PAGE_EEPROM;
//
//      //ʳ������ ���� �� ���� ������ 
//      size_to_end = (sizeof(trigger_active_functions) + 1) - offset_from_start; 
//      
//      if (size_to_end > 0)
//      {
//        if (size_to_end < SIZE_PAGE_EEPROM)
//          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_TRG_FUNC + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
//        else
//          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_TRG_FUNC + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
//        
//        //�������� �������� ������� ������ ������
//        if (rez > 1)
//        {
//          error_start_i2c();          
//          
//          //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
//          type_error_of_exchanging_via_i2c = 0;
//        }
//        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
//      }
//      else
//      {
//        //���� ����� ��� ���������
//       
//        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
//        comparison_writing |= COMPARISON_WRITING_TRG_FUNC;
//        _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
//        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
//
//        //C������ ����� ������ ���������� ����������� ���������� � EEPROM
//        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT);
//      }
//      
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� ���������� ���������� ���������� ���� � EEPROM

      int size_to_end;
      unsigned int rez, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_info_rejestrator_pr_err_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(info_rejestrator_pr_err) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        if (size_to_end < SIZE_PAGE_EEPROM)
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_INFO_REJESTRATORS_PR_ERR + offset_from_start), (read_write_i2c_buffer + offset_from_start), size_to_end);
        else
          rez = start_write_buffer_via_I2C(EEPROM_ADDRESS, (START_ADDRESS_INFO_REJESTRATORS_PR_ERR + offset_from_start), (read_write_i2c_buffer + offset_from_start), SIZE_PAGE_EEPROM);
        
        //�������� �������� ������� ������ ������
        if (rez > 1)
        {
          error_start_i2c();          
          
          //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0) _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
      }
      else
      {
        //���� ����� ��� ���������
       
        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        

        //C������ ����� ������ ���������� ���������� ���������� ���� � EEPROM
        _CLEAR_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT) !=0)
    {
      unsigned int rez;

      //��������� ������ ������� ������������
      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_CONFIG_IN_EEPROM, read_write_i2c_buffer, (sizeof(__CONFIG) + 1));
      
      //�������� �������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� ������������ � ����������� �� ������� ������� ������������
        _SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ���������
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
        //���� �� �������� ����� size_setting ���� ����, �� �� ����� �� �������� ��� ��� �������� � ����� ������ ��������� ����
        size_t size_of_block = 0;
        size_t size = 0;
        while(
              (size < SIZE_BUFFER_FOR_EEPROM_EXCHNGE) &&
              (block < _ID_FB_LAST_ALL)
             )
        {
          //��������� ����� ������ �����
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
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
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
        //������ �� ��������� ���� ��� �������
        size_settings++;
        block++; /*�� ������ ��� ����, ��� ���� ��������� ��� �������� � �� ������� ��������, �� �� ������� �� ���� ����� ��� �������, � ������� �� ������� ���� � �������� ��������� �������*/

      }
      
      if (size_settings != 0) 
      {
        /*����� ��� �������� ���� ���� �������� ����� ������, �� � �� ������*/
        unsigned int rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_SETTINGS_IN_EEPROM + shift_from_start_address_settings_in_eeprom, read_write_i2c_buffer, size_settings);
        //�������� �������� ������� ������ ������
        if (rez > 1)
        {
          error_start_i2c();
        
          //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
          type_error_of_exchanging_via_i2c = 0;
        }
        else if (rez == 0)
        {
          _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

          //��� �������� ������� ������� ����������� �� ������� ������� ���������
          _SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
          _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        }
      }
      else
      {
        //������� �� ������� ����, �� ��������������� ��� ����� �����������
        block = _ID_FB_FIRST_ALL;
        shift = 0;

        shift_from_start_address_settings_in_eeprom = 0;
        size_settings = 0;

        //������ ������� �����������, �� ������������ ����������
        comparison_writing &= (unsigned int)(~COMPARISON_WRITING_SETTINGS);
        //������� �� ������� ������� �����������
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT) !=0)
    {
      unsigned int rez;
      
      //��������� ������ ������� ���������
      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_USTUVANNJA_IN_EEPROM, read_write_i2c_buffer, (SIZE_USTUVANNJA + 1));
      
      //�������� �������� �������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� ��������� � ����������� �� ������� ������� ���������
        _SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
      }
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      unsigned int rez;
//
//      //��������� ������ �������
//      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_TRG_FUNC, read_write_i2c_buffer, (sizeof(trigger_active_functions) + 1));
//      
//      //�������� �������� �������
//      if (rez > 1)
//      {
//        error_start_i2c();
//        
//        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
//        type_error_of_exchanging_via_i2c = 0;
//      }
//      else if (rez == 0)
//      {
//        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);
//
//        //��� �������� ������� ������� ������� �� ������� ������� � ����������� �� ������� �������
//        _SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
//        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
//        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
//      }
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      unsigned int rez;

      //��������� ������ �������
      rez = start_read_buffer_via_I2C(EEPROM_ADDRESS, START_ADDRESS_INFO_REJESTRATORS_PR_ERR, read_write_i2c_buffer, (sizeof(info_rejestrator_pr_err) + 1));
      
      //�������� �������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� � ����������� �� ������� �������
        _SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ������������ ��������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � �����������, ��� ������ ������� � �������������
      _SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT);
      
      //������ ���� ���������� ���������� ��� ��������

      //������ ����� ��� ������ ��������� (�����������) � EEPROM ����� � ����������� �����
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
      //���������� ����������� ���������� ���� � ����� ������
      read_write_i2c_buffer[sizeof(__CONFIG)] = (unsigned char)((~(unsigned int)crc_eeprom_config) & 0xff);
      
      //����������� ������ ���� ������������ ������ � EEPROM
      number_block_config_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ���� ������ ���������� �� ������������� � EEPROM
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
      
      //������ ���� ���������� ���������� ��� ��������

      //������ ����� ��� ������ ��������� (�����������) � EEPROM ����� � ����������� �����
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
          //��������� ����� ������ �����
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
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(51);
            }
          }

          //��������� �������� �� ������� �����
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
        //������ �� ��������� ����
        read_write_i2c_buffer[index++] = (uint8_t)((~(unsigned int)crc_eeprom_settings) & 0xff);
        block++; /*�� ������ ��� ����, ��� ���� ��������� ��� �������� � �� ������� ��������, �� �� ������� ���������� ����, � ������� �� ������� ���� � �������� ��������� ������*/

      }

      //����������� ������ ���� ��������� ������ � EEPROM
      number_block_settings_write_to_eeprom = 0;
      
      if (index == 0)
      {
        //���� ����� ��������� ��� ���������
        
        //������� �� ������� ����, �� ��������������� ��� ����� �����������
        block = _ID_FB_FIRST_ALL;
        shift = 0;
        crc_eeprom_settings = 0;
        
        shift_from_start_address_settings_in_eeprom = 0;
        size_settings = 0;

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_SETTINGS;
        _SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        

        //������� �� ������� ������ �����������
        _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
      }
      else
      {
        //����������� �� ������ ����� � EEPROM � ����������� (��� ������ ������� � �������������) ����� ����� �������, ���� � ���������� ��� �� ������
        _SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      
        //Գ����� � ����� ������� ����� ���������� ������
        shift_from_start_address_settings_in_eeprom += size_settings;
        
        //����������� ������ ���� ����������� �� ������
        size_settings = index;
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ���������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � �����������, ��� ������ ������� � �������������
      _SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);

      //������ ���� ���������� ���������� ��� ��������
      
      //������ ����� ��� ������ ��������� � EEPROM ����� � ����������������
      unsigned char crc_eeprom_ustuvannja = 0, temp_value;
      unsigned char  *point_1; 
      unsigned char  *point_2;
      unsigned int offset = 0;

      //������ ������������� ���� ������ �������� �����������
      unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
      point_1 = (unsigned char*)(&adjustment_id_tmp); 
      for (unsigned int i = 0; i < sizeof(unsigned int); i++)
      {
        temp_value = *(point_1++);
        read_write_i2c_buffer[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(unsigned int);
      
      //������ ������� �����������
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

      //������ �� ������� ����� ��������
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
      
      //���������� ����������� ���������� ���� � ����� ������
      read_write_i2c_buffer[offset] = (unsigned char)((~(unsigned int)crc_eeprom_ustuvannja) & 0xff);
      
      //����������� ������ ���� ��������� ������ � EEPROM
      number_block_ustuvannja_write_to_eeprom = 0;
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //����� ����� ������� ������ ������ � EEPROM �� ������� ����������
//      
//      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � �����������, ��� ������ ������� � �������������
//      _SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT);
//      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
//      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
//      
//      //������ ���� ���������� ���������� ��� ��������
//
//      //������ ����� ��� ������ ��������� � EEPROM ����� � ����������������
//      unsigned char crc_eeprom_trg_func = 0, temp_value;
//      unsigned char  *point_1; 
//      unsigned char  *point_2;
//      unsigned int offset = 0;
//
//      //������ ������ �������
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
//      //���������� ����������� ���������� ���� � ����� ������
//      read_write_i2c_buffer[offset] = (unsigned char)((~(unsigned int)crc_eeprom_trg_func) & 0xff);
//      
//      //����������� ������ ���� ������ � EEPROM
//      number_block_trg_func_write_to_eeprom = 0;
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM �� ���������� ���������� ���������� ����
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � �����������, ��� ������ ������� � �������������
      _SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      
      //������ ���� ���������� ���������� ��� ��������

      //������ ����� ��� ������ � EEPROM ����� � ����������� �����
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

      //���������� ����������� ���������� ���� � ����� ������
      read_write_i2c_buffer[sizeof(info_rejestrator_pr_err)] = (unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_pr_err) & 0xff);
      
      //����������� ������ ���� ������ � EEPROM
      number_block_info_rejestrator_pr_err_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT) !=0)
    {
      unsigned int rez;

      //��������� ������ ������� RTC
      rez = start_read_buffer_via_I2C(RTC_ADDRESS, START_ADDRESS_TIME_REGISTERS, read_write_i2c_buffer, MAX_NUMBER_REGISTERS_RTC);
      
      //�������� �������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� RTC � ����������� �� ������� ������� RTC
        _SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
        _CLEAR_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) !=0)
    {
      unsigned int rez;

      copying_time = 1; //�������, �� �����  �� ����� ���������� ����� ����
      //��������� ������ ������ ���� � RTC
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

      copying_time = 0; //�������, �� ���������� ����� ���� ���������
      //������ ���� ������ ���� ��� ����, ��� ���� �������� ����� ���� ����������� ����� ���� ����� ������� ����� ��������, ��� ��������� �������� ���� � ���� � ����� ������
      for(unsigned int i = 0; i < 7; i++) time_copy[i] = time[i];
      calibration_copy = calibration;
      
      rez = start_write_buffer_via_I2C(RTC_ADDRESS, START_ADDRESS_TIME_REGISTERS, read_write_i2c_buffer, 9);
      
      //�������� �������� ������� ������ ������
      if (rez > 1)
      {
        error_start_i2c();
        
        //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
        type_error_of_exchanging_via_i2c = 0;
      }
      else if (rez == 0)
      {
        _SET_BIT(clear_diagnostyka, ERROR_START_VIA_I2C_BIT);

        //��� �������� ������� ������� ������� �� ������� ������� RTC � ����������� �� ������� ������� RTC
        _SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT);
        _CLEAR_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
      }
    }
    
    /*************************************************/
  }
  else if (driver_i2c.state_execution == 1)
  {
    /*************************************************/
    //���� ���������� ��� �������
    /*************************************************/
    //����������� �����������, �� I2C ������� �� ���� ���������� 
    driver_i2c.state_execution = -1;

    if (
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT                 ) != 0) || 
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT               ) != 0) || 
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT             ) != 0) ||
//        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT               ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
       )
    {
      //����� ����� ������ ����� � EEPROM

      if(_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT) !=0)
      {
        //����������� ��������� ���� ������������ ������ � EEPROM
        number_block_config_write_to_eeprom++;
      }
      else if(_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT) !=0)
      {
        //����������� ��������� ���� ��������� ������ � EEPROM
        number_block_settings_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT) !=0)
      {
        //����������� ��������� ���� ��������� ������ � EEPROM
        number_block_ustuvannja_write_to_eeprom++;
      }
//      else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT) != 0)
//      {
//        //����������� ��������� ���� ������� ���������������� � EEPROM
//        number_block_trg_func_write_to_eeprom++;
//      }
      else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
      {
        //����������� ��������� ���� ���������� �� ����������� ������ � EEPROM
        number_block_info_rejestrator_pr_err_write_to_eeprom++;
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(25);
      }

      //����������� �� ����������� ���������� ������, ��� ��������� ����� ����� � ��������� ����� ���� ���� ����������� �������  
      //����� ������������ �������� ������ ���������� �� 5 ��
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ��������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      __CONFIG current_config_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__CONFIG) + 1)))
      {
        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� ������������ �� � ������
        state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ��������� ���������
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
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_BIT);

          if (current_config_tmp.device_id == VERSIA_PZ)
          {
            //������� ������������ ������� ���� ������ �������
            state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_FAIL);
            state_i2c_task |= STATE_CONFIG_EEPROM_GOOD;
          
            //������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
            
            //�������� ���������� ���� (�� �����������)
            crc_config = crc_eeprom_config;

            if ((comparison_writing & COMPARISON_WRITING_CONFIG) == 0)
            {
              //������������ ���������� ������������ � ������� ������������
            
              /*
              ����������� ��������� ����������, �� ��� ���������� ������������ ��� ��������� � ���� �������� �������
              */
              //����� ����, ��� �� ��������� � ������� allocate_dynamic_memory_for_settings
              current_config_prt.device_id = current_config.device_id = current_config_edit.device_id = current_config_tmp.device_id;
              __disable_interrupt();

              __result_dym_mem_select result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, true, spca_of_p_prt, NULL, &current_config_prt, &current_config_tmp, NULL);
              
              /*
              ���������� ��������� ����������
              */
              __enable_interrupt();
              
              //������ ���� � �������� ���'�� ��� �����������
              if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, false, sca_of_p     , spca_of_p_prt, &current_config     , &current_config_tmp, &current_config_prt);
              if (result == DYN_MEM_SELECT_OK) result = allocate_dynamic_memory_for_settings(MAKE_DYN_MEM, false, sca_of_p_edit, sca_of_p     , &current_config_edit, &current_config_tmp, &current_config    );
              for (size_t t = 0; t < (7 + 1); t++) current_config_edit.time_config[t] = current_config.time_config[t] = current_config_prt.time_config[t] = current_config_tmp.time_config[t];
              
              if (result == DYN_MEM_SELECT_OK) 
              {
                state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_NO_FREE_MEMORY);

                //������� ����������� � ���� ����������
                _SET_BIT(clear_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
              }
              else
              {
                state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
                state_i2c_task |= STATE_CONFIG_EEPROM_NO_FREE_MEMORY;

                //���������� ����������� � ���� ����������
                _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
                
                //��������� ��� ���'���
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
              //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
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
                //�������� ���������� ������� ������

                //������� ����������� � ���� ����������
                _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_COMPARISON_BIT);
              }
              else
              {
                //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

                //���������� ����������� � ���� ����������
                _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_COMPARISON_BIT);
              }
            }
          }
          else
          {
            //������� ������������ �� ������� ���� ������ �������

            //�������, �� ���������� ���� ������������ � ������
            state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_FAIL);
            state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
            state_i2c_task |= STATE_CONFIG_EEPROM_EMPTY; /*�� ���������� ���� ��������� �� �� ���� �� �� ���� ������*/
        
            //���������� ����������� � ���� ����������
            _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
          state_i2c_task |= STATE_CONFIG_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
          _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� ������������ � ������
        state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_FAIL);
        state_i2c_task &= (unsigned int)(~STATE_CONFIG_EEPROM_GOOD);
        state_i2c_task |= STATE_CONFIG_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT);
        _SET_BIT(set_diagnostyka, ERROR_CONFIG_EEPROM_EMPTY_BIT);
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_CONFIG);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //�������� �������� ���

      //�������� �����, ��� ������� ���� ��� ����������� � ������
      static unsigned int empty_block, difference;
      static uint8_t crc_eeprom_settings;
      if (shift_from_start_address_settings_in_eeprom == 0) 
      {
        empty_block = true;
        difference = false;
        crc_eeprom_settings = 0;
      }
      
      size_t new_shift = shift_from_start_address_settings_in_eeprom + size_settings;
      size_settings = 0; /*��� ����������� ���� �����, �� ������� ������ ������ ����� �������*/

      //�������� �������� ������ � ���� ���� ������������ ���������
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
        //��������� ����� ������ �����
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
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
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
                //������������ ���������� ��������� � ������� ���������
                *(p + shift) = temp_value;
              }
              else
              {
                //³��������� ���������� ������� ���� ������
                if (*(p + shift) != temp_value) difference = true;
              }
            }
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
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
          //�� ��������� �������� ���� �������� ��������� ���������� ���� � ����� ���������� �� ������ ��� ���������� �����

          if(empty_block == 0)
          {
            //�������, �� ���� ������������ �� � ������
            state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_EMPTY);
            //������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);
        
            //���������� ���������� ���� � ���������� �������� ��� � ��������� ���������
            if (crc_eeprom_settings_remote  == ((uint8_t)((~(unsigned int)crc_eeprom_settings) & 0xff)))
            {
              //����������� ���� ���������

              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);

              //�������� ���������� ���� (�� �����������)
              crc_settings = crc_eeprom_settings;

              if ((comparison_writing & COMPARISON_WRITING_SETTINGS) == 0)
              {
                //������������ ���������� ��������� � ������� ���������
            
                /*
                ������� � ��������� � ��������� ��� ������� (prt) � ��������� � �곿 ���� ���������� � EEPROM
                */
                copy_settings(&current_config_edit, &settings_fix, &settings_fix_edit, sca_of_p, sca_of_p_edit);

                __disable_interrupt();
                copy_settings(&current_config_edit, &settings_fix_prt, &settings_fix_edit, spca_of_p_prt, sca_of_p_edit);
                __enable_interrupt();
                /***/

              }
              else
              {
                //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
                if (difference == false)
                {
                  //�������� ���������� ������� ������
    
                  //������� ����������� � ���� ����������
                  _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_COMPARISON_BIT);
                }
                else
                {
                  //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

                  //���������� ����������� � ���� ����������
                  _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_COMPARISON_BIT);
                }
              }

              state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
              state_i2c_task |= STATE_SETTINGS_EEPROM_GOOD;
            }
            else
            {
              //���������� ���� �� ���������
              /*
              ��������� � ��������� � �� ���� ���������� � EEPROM (edit) � ����������
              */
              copy_settings(&current_config, &settings_fix_edit, &settings_fix, sca_of_p_edit, sca_of_p);
              /***/

              state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
              state_i2c_task |= STATE_SETTINGS_EEPROM_FAIL;
          
              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
            }
          }
          else
          {
            //�������� ���� ����������� �������� ������
            /*
            ��������� � ��������� � �� ���� ���������� � EEPROM (edit) � ����������
            */
            copy_settings(&current_config, &settings_fix_edit, &settings_fix, sca_of_p_edit, sca_of_p);
            /***/
            
            //�������, �� ���������� ���� ��������� � ������
            state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
            state_i2c_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
            state_i2c_task |= STATE_SETTINGS_EEPROM_EMPTY;
        
            //���������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
            _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);
          }
        }
        else
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(55);
        }
      }
      shift_from_start_address_settings_in_eeprom = new_shift; /*� �������� ����� ��������� � ����� ������� ����� ���� ������������ ������*/
      
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      unsigned int adjustment_id_tmp, ustuvannja_tmp[NUMBER_ANALOG_CANALES], serial_number_dev_tmp;

      while ((empty_block != 0) && ( i < (SIZE_USTUVANNJA + 1)))
      {
        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� ������������ �� � ������
        state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ����� ��������� � ������� �������
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
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
          
          if (adjustment_id_tmp == ADJUSTMENT_ID)
          {
            //��� ������ �������� ����������� ������� ������ ����������� ������������

            //�������� ���������� ���� (�� �����������)
            crc_ustuvannja = crc_eeprom_ustuvannja;
          
            if ((comparison_writing & COMPARISON_WRITING_USTUVANNJA) == 0)
            {
              //������������ ���������� ��������� � ����� ���������
            
              //�������, �� ��������� ����� ���� ���������� � �� ����� ���� � ����������� ������� ��������� � ������� � ���� ������ ����������� �������
              changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              //���������� ����� ��������� � ����������� ������ � ������� �����
              for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
              {
                ustuvannja[k] = ustuvannja_tmp[k];
              }
              serial_number_dev = serial_number_dev_tmp;
              //�������, �� ��������� �������� � �� ����� ���� � ����������� ������� ��������� � ����� � ���� ������ ����������� �������
              changed_ustuvannja = CHANGED_ETAP_ENDED;
            }
            else
            {
              //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
              unsigned int difference = 0;
  
              i = 0;
              while ((difference == 0) && (i < NUMBER_ANALOG_CANALES))
              {
                //�������� ������ �������� �����������
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
                //�������� ������ �������� ������ (���� �� ���� �� ����������� ��� �������)
                if (serial_number_dev_comp != serial_number_dev_tmp) difference = 0xff;
              }
            
              if (difference == 0)
              {
                //�������� ���������� ������� ������
  
                //������� ����������� � ���� ����������
                _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT);
              }
              else
              {
                //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

                //���������� ����������� � ���� ����������
                _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT);
              }
            }

            state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
            state_i2c_task |= STATE_USTUVANNJA_EEPROM_GOOD;
          
            //������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          }
          else
          {
            //��� ������ �������� ����������� �� ������� ������ ����������� ������������

            //�������, �� ���������� ���� ��������� � ������
            state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
            state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
            state_i2c_task |= STATE_USTUVANNJA_EEPROM_EMPTY;/*�� ���������� ���� �������� ����������� -  �� �� ���� �� �� ���� ������*/
        
            //���������� ����������� � ���� ����������
            _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
          state_i2c_task |= STATE_USTUVANNJA_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� ��������� � ������
        state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
        state_i2c_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
        state_i2c_task |= STATE_USTUVANNJA_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
        _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_EMPTY_BIT);
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_USTUVANNJA);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //�������� �������� ���
//      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
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
//        //�������, �� ���� �� � ������
//        state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_EMPTY);
//        //������� ����������� � ���� ����������
//        _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
//        
//        //���������� ���������� ���� � ���������� �������� ��� � �������� ����
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
//          //����������� ���� ���������
//
//          //������� ����������� � ���� ����������
//          _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
//          
//          //�������� ���������� ���� (�� �����������)
//          crc_trg_func = crc_eeprom_trg_func;
//          
//          if ((comparison_writing & COMPARISON_WRITING_TRG_FUNC) == 0)
//          {
//            //������������ ���������� ������� ����������
//            
//            //���������� ������� ���������� � ������ ����
//            for(unsigned int k = 0; k < N_BIG; k++) trigger_active_functions[k] = trigger_active_functions_tmp[k];
////            restore_trigger_functions(trigger_active_functions);
//          }
//          else
//          {
//            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
//            
//            unsigned int difference = 0;
//  
//            i = 0;
//            while ((difference == 0) && (i < N_BIG))
//            {
//              //�������� ������ ������� �������� ���� ���������� � ��������������� ���'��
//              if (trigger_active_functions_comp[i] != trigger_active_functions_tmp[i]) difference = 0xff;
//              else
//              {
//                i++;
//              }
//            }
//            
//            if (difference == 0)
//            {
//              //�������� ���������� ������� ������
//  
//              //������� ����������� � ���� ����������
//              _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT);
//            }
//            else
//            {
//              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������
//
//              //���������� ����������� � ���� ����������
//              _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT);
//            }
//          }
//
//          state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_FAIL);
//          state_i2c_task |= STATE_TRG_FUNC_EEPROM_GOOD;
//        }
//        else
//        {
//          //���������� ���� �� ���������
//          state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_GOOD);
//          state_i2c_task |= STATE_TRG_FUNC_EEPROM_FAIL;
//          
//          //���������� ����������� � ���� ����������
//          _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
//        }
//      }
//      else
//      {
//        //�������, �� ���������� ���� � ������
//        state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_FAIL);
//        state_i2c_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_GOOD);
//        state_i2c_task |= STATE_TRG_FUNC_EEPROM_EMPTY;
//        
//        //���������� ����������� � ���� ����������
//        _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
//        _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
//      }
//            
//      //������ ������� �����������, �� ������������ ����������
//      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_TRG_FUNC);
//      //������� ����������� ��� ������� �����
//      _CLEAR_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      __INFO_REJESTRATOR info_rejestrator_pr_err_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__INFO_REJESTRATOR) + 1)))
      {
        if (read_write_i2c_buffer[i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_i2c_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ���������
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
          //����������� ���� ���������
          
          //�������� ���������� ���� (�� �����������)
          crc_info_rejestrator_pr_err = crc_eeprom_info_rejestrator_pr_err;

          state_i2c_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL);
          state_i2c_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD;
          
          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
          {
            //������������ ���������� ���������� �� ���������� ���������� ���� � ������ ���������
            
            //���������� ���������� �� ���������� ���������� ���� � ��������� ��������� � ������ ���������
            info_rejestrator_pr_err = info_rejestrator_pr_err_tmp;

            //���������� �� �� ����� � ���� ���������� �����
            if(
               (info_rejestrator_pr_err.next_address   >= MIN_ADDRESS_PR_ERR_AREA) && 
               (info_rejestrator_pr_err.next_address   <= MAX_ADDRESS_PR_ERR_AREA) &&
               (info_rejestrator_pr_err.number_records <= MAX_NUMBER_RECORDS_INTO_PR_ERR)  
              )
            {
              //�� �������� ����� �������� ��������

              //����������, �� � ������ ������ �������� ���� �� ������� ����������/������ �������.
              //��� ������ ����� ���� ���� �����������, ���� ��� ��� ������ � ���������
              //��� �������, �� � ����� ������ �� ���� ����� � �����
              //����������, �� � ������ ������ ��������� ��䳿 �� ������� ����������/������ �������.
              //��� ������ � �������, ��� ���������� ���� ���� ������������
              if (info_rejestrator_pr_err.saving_execution !=0 )
              {
                //����������� ����������� ��� �� ����
                _SET_BIT(set_diagnostyka, ERROR_PR_ERR_LOSS_INFORMATION_BIT);

                //����������� ������� ������ ���� ��������� � EEPROM
                /*
                ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
                �� �� ����� ��������������� ����������� ����� ���������� �� ����������
                ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
                info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
                "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
                ������ ������� ���������.
                � ����� ������� �� �������, ��� ������� ����� �� �����������, 
                �� ����� ���������� �������� main_routines_for_i2c - � ��� �� ����� �����������.
                ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
                ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
                �� ����� ����������� ������� (�� ������ � ���� �������)
                */
                _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

                info_rejestrator_pr_err.saving_execution = 0;
                
                
              }   
            }
            else
            {
              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          
              //����������� ������� ������ ���� ��������� � EEPROM
              /*
              ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
              �� �� ����� ��������������� ����������� ����� ���������� �� ����������
              ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
              info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
              "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
              ������ ������� ���������.
              � ����� ������� �� �������, ��� ������� ����� �� �����������, 
              �� ����� ���������� �������� main_routines_for_i2c - � ��� �� ����� �����������.
              ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
              ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
              �� ����� ����������� ������� (�� ������ � ���� �������)
              */
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

              //������� ��������� ���������� �� ��������� ���������� ����
              info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
              info_rejestrator_pr_err.saving_execution = 0;
              info_rejestrator_pr_err.number_records = 0;
            }
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
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
              //�������� ���������� ������� ������

              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT);
            }
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_i2c_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD);
          state_i2c_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          
          /*
          ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
          ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
          �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
          �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
          ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
          ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
          �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
          ��� ������ � EEPROM �� ��� �� ��������
          */
          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
          {
            //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

            //����������� ������� ������ ���� ��������� � EEPROM
            /*
            ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
            �� �� ����� ��������������� ����������� ����� ���������� �� ����������
            ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
            info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
            "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
            ������ ������� ���������.
            � ����� ������� �� �������, ��� ������� ����� �� �����������, 
            �� ����� ���������� �������� main_routines_for_i2c - � ��� �� ����� �����������.
            ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
            ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
            �� ����� ����������� ������� (�� ������ � ���� �������)
            */
            _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

            //������� ��������� ���������� �� ��������� ���������� ����
            info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
            info_rejestrator_pr_err.saving_execution = 0;
            info_rejestrator_pr_err.number_records = 0;
          }
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_i2c_task &= (unsigned int)(~(STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL | STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD));
        state_i2c_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT);

        /*
        ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
        ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
        �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
        �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
        ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
        ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
        �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
        ��� ������ � EEPROM �� ��� �� ��������
        */
        if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
        {
          //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

          //����������� ������� ������ ���� ��������� � EEPROM
          /*
          ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
          �� �� ����� ��������������� ����������� ����� ���������� �� ����������
          ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
          info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
          "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
          ������ ������� ���������.
          � ����� ������� �� �������, ��� ������� ����� �� �����������, 
          �� ����� ���������� �������� main_routines_for_i2c - � ��� �� ����� �����������.
          ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
          ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
          �� ����� ����������� ������� (�� ������ � ���� �������)
          */
          _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

          //������� ��������� ���������� �� ��������� ���������� ����
          info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
          info_rejestrator_pr_err.saving_execution = 0;
          info_rejestrator_pr_err.number_records = 0;
        }
      }

      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT) !=0)
    {
      //�������� �������� ���
      if (
          ((read_write_i2c_buffer[0xA ] & (1<< 6)) == 0 ) /*SQWE = 0*/ ||
          ((read_write_i2c_buffer[0xC] &  (1<< 6)) != 0 ) /*HT  = 1 */ ||
          ((read_write_i2c_buffer[0x13]          ) != 0xf0) /*������� �������*/ 
         )
      {
        //����� ������ ���  � ����� ��������� � ������ ��������, ��� �� ����� �������� 1��
        temp_register_rtc[0] = read_write_i2c_buffer[0xC ] & (unsigned char)(~ (1<< 6));
        temp_register_rtc[1] = read_write_i2c_buffer[0xA ] | (1<< 6);

        //����������� ��� �� ����������� �����������, ���� �� ��� �����-�� ����� ����������
        if((state_i2c_task & STATE_FIRST_READING_RTC) == 0 ) _SET_BIT(set_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
        else _SET_BIT(clear_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
        
        etap_settings_test_frequency = 0;
        _SET_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT);
      } 
      else
        _SET_BIT(clear_diagnostyka, RTC_WORK_FIELD_NOT_SET_BIT);
      
      if ((read_write_i2c_buffer[0x1] &  (1<< 7)) != 0) /*ST = 1 */
      {
        //����� ���������� ��������� ��� RTC
        _SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT);
      }
      else if ((etap_reset_of_bit < ETAP_CLEAR_OF_ST_STOP) && ((read_write_i2c_buffer[0xf] & (1<<2)) != 0))
      {
        _SET_BIT(set_diagnostyka, RTC_OSCILLATOR_FAIL_BIT);
        //����� ST-�� ��������� � 1 � ������� ������� ���� � 0. �������� ����� 5 ������ �� �� ���������
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
        //����� �������� OF-��
        temp_value_for_rtc = read_write_i2c_buffer[0xf];
        _SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
      
      if ((read_write_i2c_buffer[0xC] & (1<< 6)) != 0)
      {
        //����������� ��� �� ����������� �����������, ���� �� ��� �����-�� ����� ����������
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
        //����� ���������� ����� ���������� ����� � RTC - ������� �� ������� �������
        state_i2c_task &= (unsigned int)(~STATE_FIRST_READING_RTC);
      }

      //���������� ���
      copying_time = 1; //�������, �� ����� ���������� ����� ����
      time[0] = read_write_i2c_buffer[0] & 0xff;
      time[1] = read_write_i2c_buffer[1] & 0x7f;
      time[2] = read_write_i2c_buffer[2] & 0x7f;
      time[3] = read_write_i2c_buffer[3] & 0x3f;
      time[4] = read_write_i2c_buffer[5] & 0x3f;
      time[5] = read_write_i2c_buffer[6] & 0x1f;
      time[6] = read_write_i2c_buffer[7] & 0xff;
      copy_register8_RTC = read_write_i2c_buffer[8];
      calibration = copy_register8_RTC & 0x3f;

      copying_time = 0; //�������, �� ���������� ����� ���� ���������
      //������ ���� ������ ���� ��� ����, ��� ���� �������� ����� ���� ����������� ����� ���� ����� ������� ����� ��������, ��� ��������� �������� ���� � ���� � ����� ������
      for(unsigned int i = 0; i < 7; i++) time_copy[i] = time[i];
      calibration_copy = calibration;
      
      if(
         (_CHECK_SET_BIT(    diagnostyka, EVENT_START_SYSTEM_BIT  ) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT  ) != 0) ||
         (_CHECK_SET_BIT(    diagnostyka, EVENT_RESTART_SYSTEM_BIT) != 0) ||
         (_CHECK_SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT) != 0)
        )
      {
        //�� ����� ���� �� �� ������� ����� ������� ������ ����
        if((read_write_i2c_buffer[0xC] & (1<< 6)) != 0)
        {
          //������� ���, ���� ������� �������� � RTC �������� ���������� ��������
          fixed_power_down_into_RTC = 1; //����������� ����������� ��� ��, �� ���� ����������� ���������� �������� �� ��������� RTC �� ����, �� �������� ���������� ��������

          if ((head_fifo_buffer_pr_err_records > 1) && (tail_fifo_buffer_pr_err_records == 0))
          {
            //�� �������������, �� ������ � ����� ���� �� ���� �� ����� ��� ������ � ����� FIFO ���� ��� ������� ������ ������� � �����/������� �������, � ����� � ��������� dataFlash ��  � ����������
            unsigned int local_point_for_time = tail_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR + 1 ; //������ ������� ����� ���� � ��� ������� ����� (������ ����� ������ �� ���� - ������� ������ �������) (tail_fifo_buffer_pr_err_records �� ���������� 0 � ������ ���� ��������)
            //���, ���� ����� ���������� � RTC �� ������� �������� ��� HT ����� �� ��� �� ���������� �������� � ��������� RTC
            for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[local_point_for_time + i] = time[i]; /*��������������� time_copy � calibration_copy �� ����� �� ��� ������� ���� ������� main_routines_for_i2c*/ 
          }
        }
        else
        {
          //������� ����� ������ ���� � ������� �������/����������� ��������
          unsigned int local_point_for_time;

          if (fixed_power_down_into_RTC == 0)
          {
            //�� ������, �� �������� �� ���������� ���� ���������� �������� �� ��������� RTC �� ������� �������/����������� ��������
            /*
            ���� ���� ��� ������� �������� ���� �������� �� ���������� �� �����
            ������ ������������ "������" ������ FIF0  � �������� 1
            (����� 0 �� ������� ������������� ������ � ��������� ���������� ����,
            ����� ������������ ����������� ������������  - �� ���� ��� ������� ������ �������,
            � 1 - �� �������� ����)
            */
            if ((head_fifo_buffer_pr_err_records > 0) && (tail_fifo_buffer_pr_err_records == 0))
            {
              //�� �������������, �� ������ � ����� ���� �� ���� �� ����� ��� ������ � ����� FIFO ���� ��� ������� ������ ������� � �����/������� �������, � ����� � ��������� dataFlash ��  � ����������
              /*
              ���� ����� �������� ���� ����� (head_fifo_buffer_pr_err_records > 0)
              �� ���������� ������ ��� ���� �� ������������ �� ��� �� ����� �� ������, � ��� 
              head_fifo_buffer_pr_err_records = 0 � tail_fifo_buffer_pr_err_records = 0,
              � �� ���� ��������. �� ���� ����� ������ � ���� �� ������ � ���� � �����. �� ����� 
              ������������� �� ���� � �������. ��� �� � ���������, �� �� ������, � � ����� ���� ������㳿
              ������������ ����������� ������������.
              
              ���� �� ����� �� ���������� ������ ��� ���� �� ������������ �������.
              �� � � ���� � ���� �� ���� ��������, ���� ���� ������� ���������, ��� ����. �� ��� ����� ��������
              �� ����� ������, �� ��� �� � ���������, �� �� ������, � � ����� ���� ������㳿
              ������������ ����������� ������������  - ��� � �� �����, �� �� � ������� �� ����������� 
              ������ "�������" ������� ����������� ������������
              */
              tail_fifo_buffer_pr_err_records += 1;
              while(tail_fifo_buffer_pr_err_records >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail_fifo_buffer_pr_err_records -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
            }

            local_point_for_time = tail_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR + 1; //������ ������� ����� ���� � ������� �����, ���� ���� �� ����� � DataFlash
          }
          else
          {
            local_point_for_time = (tail_fifo_buffer_pr_err_records + 1)*SIZE_ONE_RECORD_PR_ERR + 1; //������ ������� ����� ���� � ������� �����, ���� ���� �� ����� � DataFlash
          }

          //������������ ����� ���� ��� ��� ����, �� ���� ���� �� ���������� ����� ������� ������ ����
          /*
          ����� local_point_for_time ����� ����� �� ����� ����� ���� ������� ������ (���� ���� �������� ���������� �������� ����� �������),
          ��� ������� ������ (���� ���������� �������� �� RTC ����� ������� �������� �� ���� �����������)
          */
          
          //������� ������� ����������� ������������ ������ �� ������� ������������� ������������ ��� ������� ����
          temporary_block_writing_records_pr_err_into_DataFlash = 1;
          /*���� � ���� � ��������� ������ ���������� � ������ ��� ����, �� 
          �� ������� ���� ���� � ����-���� ������ ���� ���� ��������� ���������������
          �������, ��� ������ ����� ����� (��� ������ ���� ������� ���,
          ���� ���� ��䳿 ��� ������/���������� ). ��� ���� ��� � ����� � ����������
          ���� ��� ������/���������� ��������, �� � ����� ������ ���������� ������
          ����������� � ��������� DataFlash �, ���� �������, ������������ ������� ����
          � ������ ���������� ������.
          ����, ���������� ���� ����, �� ����� ���� ��� �� ���������, ��� �� �������
          ������ ��䳿 �������/�����������, ����������� ����� ����� � ����� �� ���� ������ ����.
          ���� �������� �������� ���� ������ �������� ������������ ������� ���� � ����� 
          ���������� ������, ���� � �������� ������� �� �������������� ������� ����
          � ������ �������.
          �� ���� �������� ���������� ������������ ������������ ������� ���� ���� �����������
          ����������� ������ � ��������� DataFlash.
          ��� ����� �� ����� �������, �� � ����� ������, �� ����� ���� �������� 
          � � ������ ���������� ������ � �������������� ������� ���� � ���� ������� ��������
          ���� ������� ����������� ������ ����, �� ���� �� �� ������� � ����
          ������� ��������, �� �� ���� �������� ������� ������ �������� ����. �����
          �� ��� ������ ���� �� ���� ���� "�����" ������ ����, �� �� �� � �����. 
          � ������� ������� ������������ ���� ���� ����� ���� ��������� �������.
          */
          do
          {
            while (
                   (local_point_for_time < (head_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR)) &&
                   (local_point_for_time <  SIZE_BUFFER_FOR_PR_ERR)
                  )
            {
              for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[local_point_for_time + i] = time[i]; /*��������������� time_copy � calibration_copy �� ����� �� ��� ������� ���� ������� main_routines_for_i2c*/ 
              local_point_for_time += SIZE_ONE_RECORD_PR_ERR;
            }

            //������� ��� ������� �������� ��� �� �����������
            _SET_BIT(clear_diagnostyka, EVENT_START_SYSTEM_BIT);
            _SET_BIT(clear_diagnostyka, EVENT_RESTART_SYSTEM_BIT);
          }
          while (
                 (local_point_for_time < (head_fifo_buffer_pr_err_records*SIZE_ONE_RECORD_PR_ERR)) &&
                 (local_point_for_time <  SIZE_BUFFER_FOR_PR_ERR)
                );
          //������������ ������� ����������� ������������ ������, �� � ������, �� ����� ���� � ��� ����������� ���������
          temporary_block_writing_records_pr_err_into_DataFlash = 0;
        }
      }

      //������� ����������� ��� ������� ���������� ����
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT) !=0)
    {
      //����������� ������� ������� ���������� ���� 
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

        //�������� ��������� ������� ������� RTC
        _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);

        //������� �� ����������� ��� � ���� � ������ ��������, ���� �� ���� �������
        _CLEAR_BIT(control_i2c_taskes, TASK_SET_START_SETTINGS_RTC_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT) !=0)
    {
      //������� �� ������� ���������� RTC
      _CLEAR_BIT(control_i2c_taskes, TASK_RESET_ST_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT) !=0)
    {
      etap_reset_of_bit++;
      if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_START_WAITING_5S)
      {
        //������� ������� �������� ������������  �������� OF-���, ��� �� ���� ��������� 5� ��� ����������� �������� OF-���
        _CLEAR_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
      else if (etap_reset_of_bit >= ETAP_CLEAR_OF_WRITE_OF_0)
      {
        //������� ������� �������� �������� OF-���
        etap_reset_of_bit = ETAP_CLEAR_OF_NONE;
        _CLEAR_BIT(control_i2c_taskes, TASK_RESET_OF_RTC_BIT);
      }
    }
    else
    {
      //����, ����������, ����� �� ���� � ����
      //� ��� ������� �������� ����� �� ������
    }
    /*************************************************/
  }
  else if (driver_i2c.state_execution == 2)
  {
    /*************************************************/
    //���� ���������� � ��������
    /*************************************************/

    //������ ������ ������� �����, ��� ����������� �������, � ����������� �� ����� ���� ��������������
    type_error_of_exchanging_via_i2c = 0;
    
    //����������� �����������, �� I2C ������� �� ���� ���������� 
    driver_i2c.state_execution = -1;

    //����������� � ���������� ����
    if (
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT                 ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT               ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT             ) != 0) ||
//        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT               ) != 0) ||
        (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
       )
    {
      //����� ����� ������ ����� � EEPROM
      //�������� ����� ����� ��� ������ � EEPROM ��� �����, �� ���� ������������, �� �� ���������
      //����������� �� ����������� ���������� ������, ��� ��������� ����� ����� � ��������� ����� ���� ���� ����������� �������  
      //����� ������������ �������� ������ ���������� �� 5 ��
      _SET_BIT(control_i2c_taskes, TASK_BLK_WRITING_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ������������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ���������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ���������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
    }
//    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
//    {
//      //����� ����� ������� ����� � EEPROM ����� �������� ����������
//      
//      //�������� ��������� ������ �������
//      _SET_BIT(control_i2c_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
//      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
//      _CLEAR_BIT(control_i2c_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
//    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM �� ��������� ��������������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_i2c_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);        
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_RTC_BIT) !=0)
    {
      //����� ����� ������� RTC
      
      //�������� ��������� ������ ������� RTC
      _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      _CLEAR_BIT(control_i2c_taskes, TASK_READING_RTC_BIT);
    }
    else if (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_RTC_BIT) !=0)
    {
      //����� ����� ������ RTC
      
      //�������� ��������� ������ ������ RTC
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
      //�������� ��������� �������� � ���� ������ ����, ��� �� ������
    }
    else
    {
      //� ��� ������� �������� ����� �� ������
    }
    /*************************************************/
  }
}
/*****************************************************/

/*****************************************************/
//���������������� I2C ��� ����������� ���������� ������� ����������
/*****************************************************/
void error_start_i2c(void)
{
  _SET_BIT(set_diagnostyka, ERROR_START_VIA_I2C_BIT);
          
  /**************/
  //����������������� I2C
  /**************/
  //��������� ��������� ���������� �� I2C
  I2C_ITConfig(I2C, I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF, DISABLE);
           
  //��������� ������ DMA ���� ���� �������
  if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
          
  //����������������� I2C
  Configure_I2C(I2C);
  /**************/
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/

