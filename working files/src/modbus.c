#include "header.h"

/***********************************************************************************/
//��������� ����� �� CRC ����
/***********************************************************************************/
inline unsigned short int  AddCRC(unsigned char inpbyte, unsigned short int oldCRC)
{
  unsigned short int v,temp;
  int i;
  unsigned char bt,m;

  bt = inpbyte;
  v  = oldCRC;

  for (i=0; i<8;i++)
    {
      temp = v;
      v = v >> 1;
      m = bt >> i;
      if (((temp ^m) & 1)== 1) v = v ^ 0xa001;
    }
  return v;
}
/***********************************************************************************/

/***********************************************************************************/
//������� ������ �� ��������� Modbus-RTU �� �������
/***********************************************************************************/
inline void Error_modbus(unsigned int address, unsigned int function, unsigned int error, unsigned char *output_data)
  {
   unsigned short CRC_sum;

   *output_data       = address & 0xff;
   *(output_data + 1) = 0x80 | (function & 0xff);
   *(output_data + 2) = error & 0xff;

   CRC_sum = 0xffff;
   for (int index = 0; index < 3; index++) CRC_sum = AddCRC((*(output_data + index)) ,CRC_sum);
   *(output_data + 3)  = CRC_sum & 0xff;
   *(output_data + 4)  = CRC_sum >> 8;
   
  }
/***********************************************************************************/

/***********************************************************************************/
/*
���������������� ���������� ������
���� ���������� �������� ������� � ������ ��� "����������� ����� ���'��"
*/
/***********************************************************************************/
/***********************************************************************************/

/***********************************************************************************/
//��������� ���������� ������� ����������
/***********************************************************************************/
void set_previous_ranguvannja(void)
{
//  //�������� ������� ������ �������, �� ��� ����� ���� �������, � ���� ����������� �, �� ����� ���������
//  for (unsigned int i = 0; i < number_32bit_in_target; i++)
//  {
//    *(point_to_edited_rang + i) &= ~clear_array_rang[i];
//    *(point_to_edited_rang + i) |=    set_array_rang[i];
//  }
//  
//  //��������� ������� ���� � ��������� ����
//  for (unsigned int i = 0; i < N_BIG; i++)
//  {
//    clear_array_rang[i] = 0;
//    set_array_rang[i]   = 0;
//  }
  
  point_to_edited_rang = NULL;
}
/***********************************************************************************/

/***********************************************************************************/

/***********************************************************************************/
//������� �����
/***********************************************************************************/
inline unsigned int Get_data(unsigned char *data, unsigned int address_data, unsigned int type_interface)
{
  unsigned int error = 0, temp_value = 0;
  
  if(address_data <= M_ADDRESS_LAST_RO_BLOCK_1)
  {
    //������������� �������
    switch (address_data)
    {
    case MA_SERIAL_NUMBER:
      {
        temp_value = serial_number_dev;
        break;
      }
    case MA_NAME_CHAR_1_2:
      {
        temp_value = ('i' << 8) + 'K';
        break;
      }
    case MA_NAME_CHAR_3_4:
      {
        temp_value = ('v' << 8) + 'e';
        break;
      }
    case MA_NAME_CHAR_5_6:
      {
        temp_value = ('r' << 8) + 'p';
        break;
      }
    case MA_NAME_CHAR_7_8:
      {
        temp_value = ('b' << 8) + 'i';
        break;
      }
    case MA_NAME_CHAR_9_10:
      {
        temp_value = ('r' << 8) + 'o';
        break;
      }
    case MA_NAME_CHAR_11_12:
      {
        temp_value = ('R' << 8) + 'M';
        break;
      }
    case MA_NAME_CHAR_13_14:
      {
        temp_value = ('S' << 8) + 'Z';
        break;
      }
    case MA_NAME_CHAR_15_16:
      {
        temp_value = ('5' << 8) + '0';
        break;
      }
    case MA_NAME_CHAR_17_18:
      {
        temp_value = ('_' << 8) + 'L';
        break;
      }
    case MA_VERSION_SW:
      {
        temp_value = (VERSIA_PZ << 8) + MODYFIKACIA_VERSII_PZ;
        break;
      }
    case MA_DATA_COMP_1:
      {
        temp_value = (YEAR_VER << 8) + MONTH_VER;
        break;
      }
    case MA_DATA_COMP_2:
      {
        temp_value = (DAY_VER << 8);
        break;
      }
    case MA_TIME_COMP:
      {
        temp_value = (HOUR_VER << 8) + MINUTE_VER;
        break;
      }
    case MA_VERSION_GMM:
      {
        temp_value = (VERSIA_GMM << 8) + MODYFIKACIA_VERSII_GMM;
        break;
      }
    case MA_ZBIRKA_SW:
      {
        temp_value = ZBIRKA_VERSII_PZ;
        break;
      }
    default:
      {
        //�� ���� �� � ���� ������������ ���� ��������� ������
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_USER_REGISTER_DATA) && (address_data <= M_ADDRESS_LAST_USER_REGISTER_DATA))
  {
    unsigned int address_data_tmp = settings_fix_prt.user_register[address_data - M_ADDRESS_FIRST_USER_REGISTER_DATA];

    //��� �� �������� ������������ ������� ����������� �� ������� ����������� ������ �� ��������
    if ( !((address_data_tmp >= M_ADDRESS_FIRST_USER_REGISTER_DATA) && (address_data_tmp <= M_ADDRESS_LAST_USER_REGISTER_DATA)) )
    {
      unsigned char local_temp_value[2];
      unsigned local_error = Get_data(local_temp_value, address_data_tmp, type_interface);

      if (local_error == 0) temp_value = local_temp_value[1] | (local_temp_value[0] << 8);
      else error = local_error;
    }
    else error = ERROR_SLAVE_DEVICE_FAILURE;
  }
  else if (address_data == MA_OUTPUTS)
  {
  }
  else if (address_data == MA_INPUTS)
  {
    temp_value = state_inputs & ((1 << NUMBER_INPUTS) - 1);
  }
  else if (address_data == MA_LEDS)
  {
  }
//  else if (
//           (address_data >= M_ADDRESS_FIRST_CURRENT_AF ) && (address_data <= M_ADDRESS_LAST_CURRENT_AF) ||
//           (address_data >= M_ADDRESS_FIRST_GENERAL_AF ) && (address_data <= M_ADDRESS_LAST_GENERAL_AF)
//          )
//  {
//#define SIZE_OUTPUT_ARRAY       (M_ADDRESS_LAST_GENERAL_AF - M_ADDRESS_FIRST_GENERAL_AF + 1)
//    
//    //���� ������� �������� ������� ��� ��������� �������
//    unsigned int input_array[N_BIG], base_address;
//    unsigned short int output_array[SIZE_OUTPUT_ARRAY];
//    
//    //�������� ������� ���� �������� �����
//    for (unsigned int i = 0; i< SIZE_OUTPUT_ARRAY; i++ ) output_array[i] = 0;
//#undef SIZE_OUTPUT_ARRAY
//
//    //������� ������ ����������
//    if ((address_data >= M_ADDRESS_FIRST_CURRENT_AF ) && (address_data <= M_ADDRESS_LAST_CURRENT_AF))
//    {
//      for (unsigned int i = 0; i < N_BIG; i++) input_array[i] = active_functions[i];
//      
//      unsigned int password_set_tmp;
//      if (type_interface == USB_RECUEST) password_set_tmp = password_set_USB;
//      else if (type_interface == RS485_RECUEST) password_set_tmp = password_set_RS485;
//        
//      if (password_set_tmp != 0) 
//      {
//        output_array[(BIT_MA_PASSWORD_SET - BIT_MA_CURRENT_AF_BASE) >> 4] |= 
//          (0x1 << ((BIT_MA_PASSWORD_SET - BIT_MA_CURRENT_AF_BASE) & 0xf));
//      }
//        
//      base_address = M_ADDRESS_FIRST_CURRENT_AF;
//    }
//    else
//    {
//      if (type_interface == USB_RECUEST)
//      {
////        for (unsigned int i = 0; i < N_BIG; i++) input_array[i] = trigger_functions_USB[i];
//      }
//      else if (type_interface == RS485_RECUEST)
//      {
////        for (unsigned int i = 0; i < N_BIG; i++) input_array[i] = trigger_functions_RS485[i];
//      }
//      else
//      {
//          //���������� ����� ����� �� ���� � ����
//          total_error_sw_fixed(48);
//      }
//      base_address = M_ADDRESS_FIRST_GENERAL_AF;
//    }
//    
//    //���������� ��������� ��������� � ������� "����������� ����� ���'��"
////    convert_order_list_function_to_gmm(input_array, output_array);
//    /*****************************************************/
//    
//    temp_value  = output_array[address_data - base_address];
//  }
//  else if ((address_data >= M_ADDRESS_FIRST_MEASUREMENTS_1) && (address_data <= M_ADDRESS_LAST_MEASUREMENTS_1))
//  {
//    //���� ���������� ���������� ������� ������������ ���'�
//    switch (address_data)
//    {
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UA_1):
//      {
//        temp_value = measurement_low[IM_UA1] >> 3;
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UB_1):
//      {
//        temp_value = measurement_low[IM_UB1] >> 3;
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UC_1):
//      {
//        temp_value = measurement_low[IM_UC1] >> 3;
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UAB_1):
//      {
//        temp_value = measurement_low[IM_UAB1] >> 3;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UBC_1):
//      {
//        temp_value = measurement_low[IM_UBC1] >> 3;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UCA_1):
//      {
//        temp_value = measurement_low[IM_UCA1] >> 3;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UA_2):
//      {
//        temp_value = measurement_low[IM_UA1] >> 3;
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UB_2):
//      {
//        temp_value = measurement_low[IM_UB1] >> 3;
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UC_2):
//      {
//        temp_value = measurement_low[IM_UC1] >> 3;
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UAB_2):
//      {
//        temp_value = measurement_low[IM_UAB2] >> 3;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UBC_2):
//      {
//        temp_value = measurement_low[IM_UBC2] >> 3;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_UCA_2):
//      {
//        temp_value = measurement_low[IM_UCA2] >> 3;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_IA_1):
//      {
//        temp_value = measurement_low[IM_IA] >> 2;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_IB_1):
//      {
//        temp_value = measurement_low[IM_IB] >> 2;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_IC_1):
//      {
//        temp_value = measurement_low[IM_IC] >> 2;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_I1):
//      {
//        temp_value = measurement_low[IM_I1] >> 2;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_MEASUREMENT_I2):
//      {
//        temp_value = measurement_low[IM_I2] >> 2;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ACTIVE_POWER):
//      {
//        temp_value = P/50;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_REACTIVE_POWER):
//      {
//        temp_value = Q/50;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FULL_POWER):
//      {
//        temp_value = S/50;
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_COS_PHI):
//      {
//        if (S != 0)
//          temp_value = cos_phi_x1000;
//        else
//          temp_value = 0x0;
//          
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FREQUENCY_1):
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FREQUENCY_2):
//      {
//        int int_frequency;
//        if (address_data == (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_FREQUENCY_1))int_frequency = (int)(frequency_val_1*100);
//        else int_frequency = (int)(frequency_val_2*100);
//        
//        if (int_frequency > 0 /*�� ����� ������ - ������� �� ���������*/)
//          temp_value = int_frequency;
//        else
//        {
//          if (int_frequency == (-1*100))
//            temp_value = (unsigned int)(-1);
//          else if (int_frequency == (-2*100))
//            temp_value = (unsigned int)(-2);
//          else if (int_frequency == (-3*100))
//            temp_value = (unsigned int)(-3);
//          else
//            temp_value = (unsigned int)(-4);
//        }
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_BASE_CANAL_FOR_ANGLE):
//      {
//        switch (base_index_for_angle)
//        {
//        case (-1):
//          {
//            temp_value = BASE_CANAL_NONE;
//            break;
//          }
//        case FULL_ORT_Ua1:
//          {
//            temp_value = BASE_CANAL_UA_TN1;
//            break;
//          }
//        case FULL_ORT_Ub1:
//          {
//            temp_value = BASE_CANAL_UB_TN1;
//            break;
//          }
//        case FULL_ORT_Uc1:
//          {
//            temp_value = BASE_CANAL_UC_TN1;
//            break;
//          }
//        case FULL_ORT_Ua2:
//          {
//            temp_value = BASE_CANAL_UA_TN2;
//            break;
//          }
//        case FULL_ORT_Ub2:
//          {
//            temp_value = BASE_CANAL_UB_TN2;
//            break;
//          }
//        case FULL_ORT_Uc2:
//          {
//            temp_value = BASE_CANAL_UC_TN2;
//            break;
//          }
//        case FULL_ORT_Uab1:
//          {
//            temp_value = BASE_CANAL_UAB_TN1;
//            break;
//          }
//        case FULL_ORT_Ubc1:
//          {
//            temp_value = BASE_CANAL_UBC_TN1;
//            break;
//          }
//        case FULL_ORT_Uca1:
//          {
//            temp_value = BASE_CANAL_UCA_TN1;
//            break;
//          }
//        case FULL_ORT_Uab2:
//          {
//            temp_value = BASE_CANAL_UAB_TN2;
//            break;
//          }
//        case FULL_ORT_Ubc2:
//          {
//            temp_value = BASE_CANAL_UBC_TN2;
//            break;
//          }
//        case FULL_ORT_Uca2:
//          {
//            temp_value = BASE_CANAL_UCA_TN2;
//            break;
//          }
//        default:
//          {
//            //���������� ����� ����� �� ���� � ����
//            total_error_sw_fixed(72);
//          }
//        }
//
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UA_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ua1];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UB_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ub1];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UC_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Uc1];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UAB_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Uab1];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UBC_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ubc1];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UCA_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Uca1];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UA_2):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ua2];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UB_2):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ub2];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UC_2):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Uc2];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UAB_2):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Uab2];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UBC_2):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ubc2];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_UCA_2):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Uca2];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_IA_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ia];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_IB_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ib];
//        break;
//      }
//    case (M_ADDRESS_FIRST_MEASUREMENTS_1 + OFFSET_ANGLE_IC_1):
//      {
//        temp_value = (unsigned int)phi_angle[FULL_ORT_Ic];
//        break;
//      }
//    default:
//      {
//        temp_value = 0;
//        break;
//      }
//    }
//  }
//  else if ((address_data >= M_ADDRESS_FIRST_MEASUREMENTS_DR) && (address_data <= M_ADDRESS_LAST_MEASUREMENTS_DR))
//  {
//    //����������, �� ���������� �� ��� ������ ����������� ����������
//    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
//    {
//      //���������� ������ ���� �� ���� � �����
//      error = ERROR_SLAVE_DEVICE_FAILURE;
//    }
//    else if (
//             ((type_interface == USB_RECUEST  ) && (number_record_of_dr_for_USB   == 0xffff)) ||
//             ((type_interface == RS485_RECUEST) && (number_record_of_dr_for_RS485 == 0xffff))
//            )
//    {
//      //�� ������ ����������������� ����������� ���������� ������ ����������� ����������
//      error = ERROR_ILLEGAL_DATA_ADDRESS;
//    }
//    else if (
//             ((clean_rejestrators & CLEAN_DR) != 0) ||
//             (
//              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
//              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
//             ) 
//            )
//    {
//      //����� ��� ���������� ��� ���������� ������ ����������� ����������, ��� ������� ����, ���� �� �������� � ��������� �����������
//      error = ERROR_SLAVE_DEVICE_BUSY;
//    }
//    else
//    {
//      //����� ������ ���
//      int number_block, offset;
//      unsigned char *point_to_buffer;
//      number_block = (address_data - M_ADDRESS_FIRST_MEASUREMENTS_DR) / MEASUREMENTS_DR_WIDTH;
//      offset = (address_data - M_ADDRESS_FIRST_MEASUREMENTS_DR) - number_block*MEASUREMENTS_DR_WIDTH;
//      if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
//      else point_to_buffer = buffer_for_RS485_read_record_dr;
//      
//      if (
//          number_block < (
//                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_PHASE_DR  )) + 
//                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MIN_U_DR      )) + 
//                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_U_DR      )) + 
//                          (*(point_to_buffer + FIRST_INDEX_NUMBER_MAX_ZOP_DR    ))
//                         )
//         )
//      {  
//        unsigned int value, index;
//        
//        switch (offset)
//        {
//        case DR_OFFSET_MEASUREMENT_IA_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 0)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 2;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_IB_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 1)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 2;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_IC_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 2)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 2;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_I1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 4)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 2;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_I2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 3)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 2;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UAB_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 11)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UBC_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 12)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UCA_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 13)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UA_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 5)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UB_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 6)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UC_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 7)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UAB_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 14)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UBC_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 15)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UCA_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 16)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UA_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 8)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UB_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 9)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_MEASUREMENT_UC_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 10)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value >> 3;
//            break;
//          }
//        case DR_OFFSET_FREQUENCY_1:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 17)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value / 10;
//            break;
//          }
//        case DR_OFFSET_FREQUENCY_2:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 18)*sizeof(unsigned int);
//            value = *((unsigned int *)(point_to_buffer + index));
//            
//            temp_value = value / 10;
//            break;
//          }
//        case DR_OFFSET_LABEL_TIME_LSW:
//        case DR_OFFSET_LABEL_TIME_MSW:
//        case DR_OFFSET_LABEL_PROTECT:
//          {
//            index = FIRST_INDEX_FIRST_BLOCK_DR + (number_block*SIZE_ARRAY_FIX_MAX_MEASUREMENTS + 19)*sizeof(unsigned int);
//            
//            if (offset == DR_OFFSET_LABEL_TIME_LSW)
//            {
//              temp_value = (*(point_to_buffer + index + 0)) | ((*(point_to_buffer + index + 1)) << 8 );
//            }
//            else if (offset ==DR_OFFSET_LABEL_TIME_MSW)
//            {
//              temp_value =  *(point_to_buffer + index + 2);
//            }
//            else
//            {
//              value = *(point_to_buffer + index + 3);
//              switch (value)
//              {
//              case IDENTIFIER_BIT_ARRAY_MAX_CURRENT_PHASE:
//                {
//                  temp_value = BLOCK_PROTECTION_MTZ;
//                  break;
//                }
//              case IDENTIFIER_BIT_ARRAY_MIN_VOLTAGE:
//                {
//                  temp_value = BLOCK_PROTECTION_UMIN;
//                  break;
//                }
//              case IDENTIFIER_BIT_ARRAY_MAX_VOLTAGE:
//                {
//                  temp_value = BLOCK_PROTECTION_UMAX;
//                  break;
//                }
//              case IDENTIFIER_BIT_ARRAY_MAX_CURRENT_ZOP:
//                {
//                  temp_value = BLOCK_PROTECTION_ZOP;
//                  break;
//                }
//              default:
//                {
//                  //���� ���� �������, �� ���� � �������� �� ���� ��������
//                  temp_value = 0;
//                  break;
//                }
//                  
//              }
//            }
//            
//            break;
//          }
//        default:
//          {
//            temp_value = 0;
//            break;
//          }
//        }
//      }
//      else
//      {
//        if ((offset == DR_OFFSET_LABEL_TIME_LSW) || (offset == DR_OFFSET_LABEL_TIME_MSW)) temp_value = 0xffff;
//        else temp_value = 0;
//      }
//    }
//  }
  else if ((address_data >= M_ADDRESS_FIRST_USER_REGISTER) && (address_data <= M_ADDRESS_LAST_USER_REGISTER))
  {
    temp_value = settings_fix_prt.user_register[address_data - M_ADDRESS_FIRST_USER_REGISTER];
  }
  else if ((address_data >= M_ADDRESS_CONTROL_BASE) && (address_data <= M_ADDRESS_CONTROL_LAST))
  {
    switch (address_data)
    {
    case M_ADDRESS_CONTROL_EL:
      {
        temp_value = 1 << (BIT_MA_CONFIGURATION_EL - BIT_MA_CONTROL_EL_BASE);
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_PART1) && (address_data <= M_ADDRESS_LAST_SETPOINTS_PART1))
  {
    switch (address_data)
    {
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if (
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1)))/* ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4)))*/
          )
  {
    //�������, ��������, �� ����� ������� ���� �������
     unsigned int /*num_gr, */address_data_tmp = address_data;
     if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1)))
     {
//       num_gr = 0;
       address_data_tmp -= SHIFT_G1;
     }
//     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2)))
//     {
//       num_gr = 1;
//       address_data_tmp -= SHIFT_G2;
//     }
//     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3)))
//     {
//       num_gr = 2;
//       address_data_tmp -= SHIFT_G3;
//     }
//     else
//     {
//       num_gr = 3;
//       address_data_tmp -= SHIFT_G4;
//     }
        
    switch (address_data_tmp)
    {
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE) && (address_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE))
  {
    //������� � �������� (�����������), ���������
    switch (address_data)
    {
    case MA_UVV_TYPE_SIGNAL_INPUT:
      {
//        temp_value = current_settings_interfaces.type_of_input_signal & ((1 << NUMBER_INPUTS) - 1);
        break;
      }
    case MA_TYPE_DF:
      {
//        temp_value = current_settings_interfaces.type_df & ((1 << NUMBER_DEFINED_FUNCTIONS) - 1);
        break;
      }
    case MA_DOPUSK_DV_1:
    case MA_DOPUSK_DV_2:
    case MA_DOPUSK_DV_3:
    case MA_DOPUSK_DV_4:
    case MA_DOPUSK_DV_5:
    case MA_DOPUSK_DV_6:
    case MA_DOPUSK_DV_7:
    case MA_DOPUSK_DV_8:
    case MA_DOPUSK_DV_9:
    case MA_DOPUSK_DV_10:
      {
//        temp_value = current_settings_interfaces.dopusk_dv[address_data - MA_DOPUSK_DV_1];
        break;
      }
    case MA_DF_PAUSE_1:
    case MA_DF_PAUSE_2:
    case MA_DF_PAUSE_3:
    case MA_DF_PAUSE_4:
    case MA_DF_PAUSE_5:
    case MA_DF_PAUSE_6:
    case MA_DF_PAUSE_7:
    case MA_DF_PAUSE_8:
      {
//        temp_value = current_settings_interfaces.timeout_pause_df[address_data - MA_DF_PAUSE_1]/10;
        break;
      }
    case MA_DF_WORK_1:
    case MA_DF_WORK_2:
    case MA_DF_WORK_3:
    case MA_DF_WORK_4:
    case MA_DF_WORK_5:
    case MA_DF_WORK_6:
    case MA_DF_WORK_7:
    case MA_DF_WORK_8:
      {
//        temp_value = current_settings_interfaces.timeout_work_df[address_data - MA_DF_WORK_1]/10;
        break;
      }
    case MA_TO_DEACTIVATION_PASSWORD_INTERFACE:
      {
          if (type_interface == USB_RECUEST)
          {
            temp_value = settings_fix_prt.timeout_deactivation_password_interface_USB;
          }
          else if (type_interface == RS485_RECUEST)
          {
            temp_value = settings_fix_prt.timeout_deactivation_password_interface_RS485;
          }
          else error = ERROR_SLAVE_DEVICE_FAILURE;
      
          break;
      }
    case MA_TO_IDLE_NEW_SETTINGS:
      {
          temp_value = settings_fix_prt.timeout_idle_new_settings;
      
          break;
      }
    case MA_LANGUAGE_MENU:
      {
        temp_value = settings_fix_prt.language;
        break;
      }
    case MA_SPEED_RS485_1:
      {
        temp_value = settings_fix_prt.baud_RS485;
        break;
      }
    case MA_STOP_BITS_RS485_1:
      {
        temp_value = settings_fix_prt.number_stop_bit_RS485 + 1;
        break;
      }
    case MA_PARE_RS485_1:
      {
        temp_value = settings_fix_prt.pare_bit_RS485;
        break;
      }
    case MA_TIMEOUT_RS485_1:
      {
        temp_value = settings_fix_prt.time_out_1_RS485;
        break;
      }
    case MA_LOGICAL_ADDRESS:
      {
        temp_value = settings_fix_prt.address;
        break;
      }
    case MA_NAME_OF_CELL_CHARS_01_02:
    case MA_NAME_OF_CELL_CHARS_03_04:
    case MA_NAME_OF_CELL_CHARS_05_06:
    case MA_NAME_OF_CELL_CHARS_07_08:
    case MA_NAME_OF_CELL_CHARS_09_10:
    case MA_NAME_OF_CELL_CHARS_11_12:
    case MA_NAME_OF_CELL_CHARS_13_14:
    case MA_NAME_OF_CELL_CHARS_15_16:
      {
        unsigned int two_char_index = (address_data - MA_NAME_OF_CELL_CHARS_01_02) << 1;
        temp_value = settings_fix_prt.name_of_cell[two_char_index] | (settings_fix_prt.name_of_cell[two_char_index + 1] << 8);
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (address_data <= M_ADDRESS_LAST_TIME_AND_DATA))
  {
    unsigned char *label_to_time_array;
    
    if (copying_time == 0) label_to_time_array = time;
    else label_to_time_array = time_copy;
    
    switch (address_data)
    {
    case MA_YEAR:
      {
        temp_value = *(label_to_time_array + 6);
        break;
      }
    case MA_MONTH:
      {
        temp_value = *(label_to_time_array + 5);
        break;
      }
    case MA_DAY:
      {
        temp_value = *(label_to_time_array + 4);
        break;
      }
    case MA_HOUR:
      {
        temp_value = *(label_to_time_array + 3);
        break;
      }
    case MA_MINUTE:
      {
        temp_value = *(label_to_time_array + 2);
        break;
      }
    case MA_SECOND:
      {
        temp_value = *(label_to_time_array + 1);
        break;
      }
    case MA_MILISECOND:
      {
        temp_value = *(label_to_time_array + 0);
        break;
      }
    default:
      {
        temp_value = 0;
        break;
      }
    }
  }
  else if (address_data == MA_TOTAL_NUMBER_RECORDS_PR_ERR)
  {
    temp_value = info_rejestrator_pr_err.number_records;
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_PR_ERR)
  {
    if (type_interface == USB_RECUEST) temp_value = number_record_of_pr_err_into_USB;
    else if (type_interface == RS485_RECUEST) temp_value = number_record_of_pr_err_into_RS485;
    else
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
  }
  else if ((address_data >= MA_FIRST_ADR_PR_ERR_WINDOW) && (address_data <= MA_LASR_ADR_PR_ERR_WINDOW))
  {
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((type_interface == USB_RECUEST  ) && (number_record_of_pr_err_into_USB   == 0xffff)) ||
             ((type_interface == RS485_RECUEST) && (number_record_of_pr_err_into_RS485 == 0xffff))
            )
    {
      //�� ������ ����������������� ����������� ���������� ������ ���������� ���������� ����
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else if (
             ((clean_rejestrators & CLEAN_PR_ERR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) != 0))
             ) 
            )
    {
      //����� ��� ���������� ��� ���������� ������ ���������� ���������� ����, ��� ������� ����, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if (
             (
              (type_interface == USB_RECUEST)
              && 
              (
               (number_record_of_pr_err_into_USB >= info_rejestrator_pr_err.number_records) ||
               (number_record_of_pr_err_into_USB >= MAX_NUMBER_RECORDS_INTO_PR_ERR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/ 
              )   
             )
             ||   
             (
              (type_interface == RS485_RECUEST)
              && 
              (
               (number_record_of_pr_err_into_RS485 >= info_rejestrator_pr_err.number_records) ||
               (number_record_of_pr_err_into_RS485 >= MAX_NUMBER_RECORDS_INTO_PR_ERR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/ 
              )   
             )
            )    
    {
      //����������� ����������� �������
      error = ERROR_SLAVE_DEVICE_FAILURE;
      
     //�������, �� ����� ������ �� ��������
      if (type_interface == USB_RECUEST) number_record_of_pr_err_into_USB = 0xffff;
      else if (type_interface == RS485_RECUEST) number_record_of_pr_err_into_RS485 = 0xffff;
    }
    else
    {
      unsigned char *point_to_buffer;
      if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_pr_err;
      else point_to_buffer = buffer_for_RS485_read_record_pr_err;

      if ( (*(point_to_buffer + 0)) != LABEL_START_RECORD_PR_ERR)
      {
        //����������� ���������� ���
        error = ERROR_SLAVE_DEVICE_FAILURE;
      }
      else
      {
        unsigned int temp_address = address_data - MA_FIRST_ADR_PR_ERR_WINDOW;
        switch (temp_address)
        {
        case 0:
          {
            temp_value = ((*(point_to_buffer + 7))  << 8) | (*(point_to_buffer + 6));
            break;
          }
        case 1:
          {
            temp_value =  (*(point_to_buffer + 5))  << 8;
            break;
          }
        case 2:
          {
            temp_value = ((*(point_to_buffer + 4))  << 8) | (*(point_to_buffer + 3));
            break;
          }
        case 3:
          {
            temp_value = ((*(point_to_buffer + 2))  << 8) | (*(point_to_buffer + 1));
            break;
          }
        case 4:
          {
            temp_value = ((*(point_to_buffer + 10))  << 8) | (*(point_to_buffer + 9));
            break;
          }
        case 5:
          {
            temp_value = ((*(point_to_buffer + 12))  << 8) | (*(point_to_buffer + 11));
            break;
          }
        case 6:
          {
            temp_value = ((*(point_to_buffer + 14))  << 8) | (*(point_to_buffer + 13));
            break;
          }
        case 7:
          {
            temp_value = ((*(point_to_buffer + 16))  << 8) | (*(point_to_buffer + 15));
            break;
          }
        case 8:
          {
            temp_value = ((*(point_to_buffer + 18))  << 8) | (*(point_to_buffer + 17));
            break;
          }
        case 9:
          {
            temp_value = ((*(point_to_buffer + 20))  << 8) | (*(point_to_buffer + 19));
            break;
          }
        case 10:
          {
            temp_value = ((*(point_to_buffer + 22))  << 8) | (*(point_to_buffer + 21));
            break;
          }
        case 11:
          {
            temp_value = ((*(point_to_buffer + 24))  << 8) | (*(point_to_buffer + 23));
            break;
          }
        case 12:
          {
            temp_value = ((*(point_to_buffer + 26))  << 8) | (*(point_to_buffer + 25));
            break;
          }
        case 13:
          {
            temp_value = ((*(point_to_buffer + 28))  << 8) | (*(point_to_buffer + 27));
            break;
          }
        case 14:
          {
            temp_value = ((*(point_to_buffer + 30))  << 8) | (*(point_to_buffer + 29));
            break;
          }
        default:
          {
            //���� ���� �������, �� ���� � �������� �� ���� ��������
            temp_value = 0;
            break;
          }
        }
      }
    }
  }
  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    //����������� ��� ��, �� ����� ��������� ������� ���������
    /*
     0 - �������� ��������� � �����������
     1 - �������� ��������� � ����������
    */
    if (password_ustuvannja == 0x1978) temp_value = 1;
    else temp_value = 0;
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    temp_value = ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA ];
  }
//  else if ((address_data >= MA_ADDRESS_FIRST_PHI_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA))
//  {
//    temp_value = phi_ustuvannja[address_data - MA_ADDRESS_FIRST_PHI_USTUVANNJA ];
//  }
//  else if (address_data == MA_NUMBER_ITERATION_EL)
//  {
//    temp_value = settings_fix_prt.number_iteration_el;
//  }
  else if (address_data == MA_LSW_GLOBAL_RESURS_MIN)
  {
    temp_value = resurs_global_min & 0xffff;
  }
  else if (address_data == MA_MSW_GLOBAL_RESURS_MIN)
  {
    temp_value = resurs_global_min >> 16;
  }
  else if (address_data == MA_LSW_GLOBAL_RESURS_MAX)
  {
    temp_value = resurs_global_max & 0xffff;
  }
  else if (address_data == MA_MSW_GLOBAL_RESURS_MAX)
  {
    temp_value = resurs_global_max >> 16;
  }
  else if (address_data == MA_LSW_GLOBAL_RESURS)
  {
    temp_value = resurs_global & 0xffff;
  }
  else if (address_data == MA_MSW_GLOBAL_RESURS)
  {
    temp_value = resurs_global >> 16;
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_WRITE)
  {
    temp_value = registers_address_write & 0xffff;
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_WRITE)
  {
    temp_value = registers_address_write >> 16;
  }
  else if (address_data == MA_NB_REG_FROM_MEM_READ)
  {
    temp_value = number_registers_read;
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_READ)
  {
    temp_value = registers_address_read & 0xffff;
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_READ)
  {
    temp_value = registers_address_read >> 16;
  }
  else if((address_data >= M_ADDRESS_FIRST_READ_DAMP_MEM) && (address_data < M_ADDRESS_LAST_READ_DAMP_MEM))
  {
    temp_value = registers_values [address_data - M_ADDRESS_FIRST_READ_DAMP_MEM];
  }
  else if ((address_data >= M_ADDRESS_FIRST_TMP_MEASURMENTS) && (address_data < M_ADDRESS_LAST_TMP_MEASURMENTS))
  {
    if((address_data & 0x1) == 0)
    {
      temp_value = measurement_low[(address_data - M_ADDRESS_FIRST_TMP_MEASURMENTS)>>1] >> 16;
    }
    else
    {
      temp_value = measurement_low[(address_data - M_ADDRESS_FIRST_TMP_MEASURMENTS)>>1] & 0xffff;
    }
  }
  else if((address_data >= M_ADDRESS_FIRST_DIG_OSCILOGRAPH)&& (address_data < M_ADDRESS_LAST_DIG_OSCILOGRAPH))
  {
    if(action_is_continued == true) error = ERROR_SLAVE_DEVICE_BUSY;
    else
    {
      int temp_value_32bit = current_data_transmit[(part_transmit_carrent_data<<3) + ((address_data - M_ADDRESS_FIRST_DIG_OSCILOGRAPH) >> 1)];
      if ( ((address_data - M_ADDRESS_FIRST_DIG_OSCILOGRAPH) & 0x1)  == 0)
      {
        //������ �����
        temp_value = (((unsigned int)temp_value_32bit) >> 16) & 0xffff;
      }
      else
      {
        //������� �����
        temp_value = (((unsigned int)temp_value_32bit)      ) & 0xffff;
      }
    }
  }
  else
  {
    error = ERROR_ILLEGAL_DATA_ADDRESS;
  }
  
  //���������� � ����� ������ ��� � ������� ��������� ��������� ������� (��� �������. ���� ���� �����������)
  if (error == 0)
  {
    *data      = (temp_value >> 8) & 0xff;
    *(data +1) =  temp_value       & 0xff;
  }
  
  return error;
}
/***********************************************************************************/

/***********************************************************************************/
//����� �����
/***********************************************************************************/
inline unsigned int Set_data(unsigned short int data, unsigned int address_data, unsigned int method_setting, /*unsigned int to_be_continue, */unsigned int type_interface)
{
  unsigned int error = 0, temp_value;
  
  __SETTINGS_FIX *target_label;
  if (method_setting == SET_DATA_IMMEDITATE) target_label = &settings_fix;
  else target_label = &settings_fix_edit;

  password_changed = false;
  if (address_data == MA_PASSWORD_INTERFACE)
  {
    //������������/������ ������ �������
    if (type_interface == USB_RECUEST)
    {
      if (password_set_USB != 0)
      {
        if ((data == settings_fix.password_interface_USB) || (data == 0x1978)) password_set_USB = 0;
        else error = ERROR_ILLEGAL_DATA_VALUE;
      }
      else if (password_set_USB == 0)
      {
        if ((data != 0) && (data == settings_fix.password_interface_USB)) password_set_USB = 1;
        else 
        {
          target_label->password_interface_USB = data;
          password_changed = true;
        }
      }
    }
    else if (type_interface == RS485_RECUEST)
    {
      if (password_set_RS485 != 0)
      {
        if ((data == settings_fix.password_interface_RS485) || (data == 0x1978)) password_set_RS485 = 0;
        else error = ERROR_ILLEGAL_DATA_VALUE;
      }
      else if (password_set_RS485 == 0)
      {
        if ((data != 0) && (data == settings_fix.password_interface_RS485)) password_set_RS485 = 1;
        else 
        {
          target_label->password_interface_RS485 = data;
          password_changed = true;
        }
      }
    }
    else error = ERROR_SLAVE_DEVICE_FAILURE;
  }
  else if ((address_data >= M_ADDRESS_FIRST_USER_REGISTER) && (address_data <= M_ADDRESS_LAST_USER_REGISTER))
  {
    //���������� ������� �����������
    
    if ( !((data >= M_ADDRESS_FIRST_USER_REGISTER_DATA) && (data <= M_ADDRESS_LAST_USER_REGISTER_DATA)) )
    {
      //�������� ���������� ������� �����������
      target_label->user_register[address_data - M_ADDRESS_FIRST_USER_REGISTER] = data;
    }
    else error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if ((address_data >= M_ADDRESS_CONTROL_BASE) && (address_data <= M_ADDRESS_CONTROL_LAST))
  {
    switch (address_data)
    {
    case M_ADDRESS_CONTROL_EL:
      {
        //��� �� ��������� ����� �� ����� ��������
        if (((data >> (BIT_MA_CONFIGURATION_EL  - BIT_MA_CONTROL_EL_BASE)) & 0x1) == 0) error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    default: break;
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_PART1) && (address_data <= M_ADDRESS_LAST_SETPOINTS_PART1))
  {
    switch (address_data)
    {
    default: break;
    }
  }
  else if (
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1)))/* ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
           ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4)))*/
          )   
  {
    //�������, ��������, �� ����� ������� ���� �������
     unsigned int /*num_gr, */address_data_tmp = address_data;
     if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1)))
     {
//       num_gr = 0;
       address_data_tmp -= SHIFT_G1;
     }
//     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2)))
//     {
//       num_gr = 1;
//       address_data_tmp -= SHIFT_G2;
//     }
//     else if ((address_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (address_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3)))
//     {
//       num_gr = 2;
//       address_data_tmp -= SHIFT_G3;
//     }
//     else
//     {
//       num_gr = 3;
//       address_data_tmp -= SHIFT_G4;
//     }
     
    switch (address_data_tmp)
    {
    default: break;
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE) && (address_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE))
  {
    //������� � �������� (�����������), ������������
    switch (address_data)
    {
    case MA_UVV_TYPE_SIGNAL_INPUT:
      {
//        if (data <= ((1 << NUMBER_INPUTS) - 1)) 
//        {
//          target_label->type_of_input_signal = data;
//          
//          //��������� ������ �����
//          for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
//          {
//            if ((target_label->type_of_input_signal & (1 << i)) !=0)
//            {
//              if ((target_label->dopusk_dv[i] % 10) != 0)
//              {
//                target_label->dopusk_dv[i] = (target_label->dopusk_dv[i] / 10)*10;
//              }
//
//              if (target_label->dopusk_dv[i] < KOEF_DOPUSK_DV_ZMIN_MIN)
//                target_label->dopusk_dv[i] = KOEF_DOPUSK_DV_ZMIN_MIN;
//            }
//          }
//        }
//        else
//          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TYPE_DF:
      {
//        if (data <= ((1 << NUMBER_DEFINED_FUNCTIONS) - 1)) 
//          target_label->type_df = data;
//        else
//          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_DOPUSK_DV_1:
    case MA_DOPUSK_DV_2:
    case MA_DOPUSK_DV_3:
    case MA_DOPUSK_DV_4:
    case MA_DOPUSK_DV_5:
    case MA_DOPUSK_DV_6:
    case MA_DOPUSK_DV_7:
    case MA_DOPUSK_DV_8:
    case MA_DOPUSK_DV_9:
    case MA_DOPUSK_DV_10:
      {
        if (data <= KOEF_DOPUSK_DV_MAX)
        {
          //��������� ���������� ����� ���� � ������� � ����, ���� ��� ������� � ������ ������
//          if (
//              ((target_label->type_of_input_signal & (1 << (address_data - MA_DOPUSK_DV_1))) == 0) ||
//              (
//               ((target_label->type_of_input_signal & (1 << (address_data - MA_DOPUSK_DV_1))) != 0) &&
//               ( data >= KOEF_DOPUSK_DV_ZMIN_MIN)                                                   &&
//               ((data % 10) == 0)  
//              )
//             )
//          {
//            target_label->dopusk_dv[address_data - MA_DOPUSK_DV_1] = data;
//          }
//          else
//            error = ERROR_ILLEGAL_DATA_VALUE;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_DF_PAUSE_1:
    case MA_DF_PAUSE_2:
    case MA_DF_PAUSE_3:
    case MA_DF_PAUSE_4:
    case MA_DF_PAUSE_5:
    case MA_DF_PAUSE_6:
    case MA_DF_PAUSE_7:
    case MA_DF_PAUSE_8:
      {
        temp_value = data*10;
        
//#if (TIMEOUT_TIMER_PAUSE_MIN != 0)          
//        if ((temp_value >= TIMEOUT_TIMER_PAUSE_MIN) && (temp_value <= TIMEOUT_TIMER_PAUSE_MAX))
//#else
//        if (temp_value <= TIMEOUT_TIMER_PAUSE_MAX)
//#endif            
//        {
//          target_label->timeout_pause_df[address_data - MA_DF_PAUSE_1] = temp_value;
//        }
//        else
//          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_DF_WORK_1:
    case MA_DF_WORK_2:
    case MA_DF_WORK_3:
    case MA_DF_WORK_4:
    case MA_DF_WORK_5:
    case MA_DF_WORK_6:
    case MA_DF_WORK_7:
    case MA_DF_WORK_8:
      {
//        temp_value = data*10;
//        
//#if (TIMEOUT_TIMER_WORK_MIN != 0)          
//        if ((temp_value >= TIMEOUT_TIMER_WORK_MIN) && (temp_value <= TIMEOUT_TIMER_WORK_MAX))
//#else
//        if (temp_value <= TIMEOUT_TIMER_WORK_MAX)
//#endif            
//        {
//          target_label->timeout_work_df[address_data - MA_DF_WORK_1] = temp_value;
//        }
//        else
//          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_DEACTIVATION_PASSWORD_INTERFACE:
      {
        //������������ ���� �������� �����, ���� ���� ��������� �� ����������, �� �������������� ������
        temp_value = data;
        
        if(
#if (TIMEOUT_DEACTIVATION_PASSWORD_MIN != 0)          
           ((temp_value >= TIMEOUT_DEACTIVATION_PASSWORD_MIN) && (temp_value <= TIMEOUT_DEACTIVATION_PASSWORD_MAX)) ||
#else
           (temp_value <= TIMEOUT_DEACTIVATION_PASSWORD_MAX) ||
#endif   
           (temp_value == TIMEOUT_DEACTIVATION_PASSWORD_OFF)
          )   
        {
          unsigned int *point_to_timeout_deactivation_password_interface;
          if (type_interface == USB_RECUEST)
          {
            point_to_timeout_deactivation_password_interface = &target_label->timeout_deactivation_password_interface_USB;
          }
          else if (type_interface == RS485_RECUEST)
          {
            point_to_timeout_deactivation_password_interface = &target_label->timeout_deactivation_password_interface_RS485;
          }
          else error = ERROR_SLAVE_DEVICE_FAILURE;
      
          if (error == 0) *point_to_timeout_deactivation_password_interface = temp_value;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TO_IDLE_NEW_SETTINGS:
      {
        //������������ ���� �������� �����, ���� ���� ����� ��� ����������, �� �������� ���� ����������� �������������
        temp_value = data;
        
#if (TIMEOUT_DEACTIVATION_PASSWORD_MIN != 0)          
        if ((temp_value >= TIMEOUT_NEW_SETTINGS_MIN) && (temp_value <= TIMEOUT_NEW_SETTINGS_MAX))
#else
        if (temp_value <= TIMEOUT_NEW_SETTINGS_MAX)
#endif   
          target_label->timeout_idle_new_settings = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_LANGUAGE_MENU:
      {
        temp_value = data;
        
#if (VALUE_SETTING_LANGUAGE_MIN != 0)          
        if ((temp_value >= VALUE_SETTING_LANGUAGE_MIN) && (temp_value <= VALUE_SETTING_LANGUAGE_MAX))
#else
        if (temp_value <= VALUE_SETTING_LANGUAGE_MAX)
#endif            
          target_label->language = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_SPEED_RS485_1:
      {
        temp_value = data;
        
#if (VALUE_BAUD_RS485_MIN != 0)          
        if ((temp_value >= VALUE_BAUD_RS485_MIN) && (temp_value <= VALUE_BAUD_RS485_MAX))
#else
        if (temp_value <= VALUE_BAUD_RS485_MAX)
#endif            
          target_label->baud_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_STOP_BITS_RS485_1:
      {
        temp_value = data - 1;
        
#if (VALUE_STOP_BITS_RS485_MIN != 0)          
        if ((temp_value >= VALUE_STOP_BITS_RS485_MIN) && (temp_value <= VALUE_STOP_BITS_RS485_MAX))
#else
        if (temp_value <= VALUE_STOP_BITS_RS485_MAX)
#endif            
          target_label->number_stop_bit_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_PARE_RS485_1:
      {
        temp_value = data;
        
#if (VALUE_PARE_RS485_MIN != 0)          
        if ((temp_value >= VALUE_PARE_RS485_MIN) && (temp_value <= VALUE_PARE_RS485_MAX))
#else
        if (temp_value <= VALUE_PARE_RS485_MAX)
#endif            
          target_label->pare_bit_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_TIMEOUT_RS485_1:
      {
        temp_value = data;
        
#if (VALUE_TIME_OUT_1_RS485_MIN != 0)          
        if ((temp_value >= VALUE_TIME_OUT_1_RS485_MIN) && (temp_value <= VALUE_TIME_OUT_1_RS485_MAX))
#else
        if (temp_value <= VALUE_TIME_OUT_1_RS485_MAX)
#endif            
          target_label->time_out_1_RS485 = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_LOGICAL_ADDRESS:
      {
        temp_value = data;
    
        if ((temp_value >= KOEF_ADDRESS_MIN) && (temp_value <= KOEF_ADDRESS_MAX))
          target_label->address = temp_value;
        else
          error = ERROR_ILLEGAL_DATA_VALUE;

        break;
      }
    case MA_NAME_OF_CELL_CHARS_01_02:
    case MA_NAME_OF_CELL_CHARS_03_04:
    case MA_NAME_OF_CELL_CHARS_05_06:
    case MA_NAME_OF_CELL_CHARS_07_08:
    case MA_NAME_OF_CELL_CHARS_09_10:
    case MA_NAME_OF_CELL_CHARS_11_12:
    case MA_NAME_OF_CELL_CHARS_13_14:
    case MA_NAME_OF_CELL_CHARS_15_16:
      {
        
        unsigned int two_char_index = (address_data - MA_NAME_OF_CELL_CHARS_01_02) << 1;
        unsigned int byte_1 = (data & 0xff), byte_2 = (data >> 8) & 0xff;
        
        if (
            (
             (byte_1 >= 0x20) && (byte_1 <= 0x7e) || /*�������� ������� � �����*/
             (byte_1 >= 0xc0) && (byte_1 <= 0xff) || /*�������� ������� �������*/
             (byte_1 == 0xa8)                     || /*��������� ������ '�'*/  
             (byte_1 == 0xb8)                     || /*��������� ������ '�'*/  
             (
              (target_label->language == LANGUAGE_UA) &&
              (
               (byte_1 == 0xaf)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xbf)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xa5)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xb4)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xaa)                     || /*���������� ������ '�'*/  
               (byte_1 == 0xba)                        /*���������� ������ '�'*/  
              ) 
             ) 
            )
            &&  
            (
             (byte_2 >= 0x20) && (byte_2 <= 0x7e) || /*�������� ������� � �����*/
             (byte_2 >= 0xc0) && (byte_2 <= 0xff) || /*�������� ������� �������*/
             (byte_2 == 0xa8)                     || /*��������� ������ '�'*/  
             (byte_2 == 0xb8)                     ||   /*��������� ������ '�'*/  
             (
              (target_label->language == LANGUAGE_UA) &&
              (
               (byte_2 == 0xaf)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xbf)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xa5)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xb4)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xaa)                     || /*���������� ������ '�'*/  
               (byte_2 == 0xba)                        /*���������� ������ '�'*/  
              ) 
             )   
            )
           )
        {
          target_label->name_of_cell[two_char_index    ] = byte_1;
          target_label->name_of_cell[two_char_index + 1] = byte_2;
        }
        else
          error = ERROR_ILLEGAL_DATA_VALUE;
        
        break;
      }
    default: break;
    }
  }
  else if ((address_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (address_data <= M_ADDRESS_LAST_TIME_AND_DATA))
  {
    temp_value = data & 0xff;
    unsigned int tetrad_low = (temp_value & 0xf), tetrad_high = (temp_value >> 4);
    
    //����������� �����, ���������, ���� ����. ���� ��������� �� 0x10, � 10 = 0xA � �� ���� 0xA ���� ��������� � ������ ������ RTC
    if((tetrad_low <= 0x9) && (tetrad_high <= 0x9))
    {
      switch (address_data)
      {
      case MA_YEAR:
        {
          time_edit[6] = temp_value;
          break;
        }
      case MA_MONTH:
        {
          time_edit[5] = temp_value;
          break;
        }
      case MA_DAY:
        {
          time_edit[4] = temp_value;
          break;
        }
      case MA_HOUR:
        {
          time_edit[3] = temp_value;
          break;
        }
      case MA_MINUTE:
        {
          time_edit[2] = temp_value;
          break;
        }
      case MA_SECOND:
        {
          time_edit[1] = temp_value;
          break;
        }
      case MA_MILISECOND:
        {
          time_edit[0] = temp_value;
          break;
        }
      default: break;
      }
    }
    else
      error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if (address_data == MA_CLEAR_NUMBER_RECORD_PR_ERR)
  {
    if (
        /*
        (current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR )
        ||  
        (current_ekran.current_level == EKRAN_DATA_LADEL_PR_ERR         )
        ||  
        (current_ekran.current_level == EKRAN_CHANGES_DIAGNOSTICS_PR_ERR)
        ||
        */
        (
         (control_tasks_dataflash & (
                                     TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB   |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485 |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU
                                    )
         ) != 0
        )
        ||
        ((clean_rejestrators & CLEAN_PR_ERR) != 0)  
       ) 
    {
      //����� ��� ���������� ��� ���������� ������ ���������� ���������� ����, ��� ������� ���� ����������� ������, ���� �� �������� � ��������� �����������
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else
    {
      //�������, �� ����� �������� ��������� ���������� ����
      clean_rejestrators |= CLEAN_PR_ERR;
    }
  }
  else if (address_data == MA_CURRENT_NUMBER_RECORD_PR_ERR)
  {
    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
    {
      //���������� ������ ���� �� ���� � �����
      error = ERROR_SLAVE_DEVICE_FAILURE;
    }
    else if (
             ((clean_rejestrators & CLEAN_PR_ERR) != 0) ||
             (
              ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB  ) != 0)) ||
              ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) != 0))
             ) 
            )
    {
      /*
      ����� ��� ���������� ��� ���������� ������ ���������� ���������� ����, 
      ��� ������� ����, ���� �� �������� � ��������� �����������
      */
      error = ERROR_SLAVE_DEVICE_BUSY;
    }
    else if (
             (data < info_rejestrator_pr_err.number_records) &&
             (data < MAX_NUMBER_RECORDS_INTO_PR_ERR        ) /*��� ���������� �� ����� �� ������������� ������ ������ ������*/
            )
    {
      if (type_interface == USB_RECUEST)
      {
        //������������ ����� ������ ���������� ���������� ���� ��� ������� ����� ��������� USB
        number_record_of_pr_err_into_USB = data;
        //������ ������� ������� ���������� ���������� ���� ���  ���������� USB

        //������ ������� ������� ��� � ����� ���'�� ��� USB
        control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB;
      }
      else if (type_interface == RS485_RECUEST)
      {
        //������������ ����� ������ ���������� ���������� ���� ��� ������� ����� ��������� RS-485
        number_record_of_pr_err_into_RS485 = data;
        //������ ������� ������� ���������� ���������� ���� ���  ���������� RS-485

        //������ ������� ������� ��� � ����� ���'�� ��� RS-485
        control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485;
      }
      else
      {
        //���������� ������ ���� �� ���� � �����
        error = ERROR_SLAVE_DEVICE_FAILURE;
      }
    }
    else
      error = ERROR_ILLEGAL_DATA_VALUE;
  }
  else if (address_data == MA_SET_SERIAL_NUMBER)
  {
    if (password_ustuvannja == 0x1978)
    {
      //��� �������� ������
      if (method_setting == SET_DATA_IMMEDITATE)
        serial_number_dev = data;
      else
        edit_serial_number_dev = data;
    }
    else 
    {
      /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }    
  }
  else if (address_data == MA_POSSIBILITY_USTUVANNJA)
  {
    if (password_ustuvannja != 0x1978)
    {
      //������������ ������-������� ��������� ������� ����� ���� ���������� ����� 0x1978
      if (data == 0x1978) password_ustuvannja = 0x1978;
      else
      {
        /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
        error = ERROR_ILLEGAL_DATA_ADDRESS;
      }
    }
    else
    {
      //����������� ����-����� ����� (��� �����, ��� ���������� ���������) ��������� �� �������� ���������� ���������
      if (data != 0x1978) password_ustuvannja = 0;
    }
  }
  else if ((address_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_USTUVANNJA))
  {
    //���������
    if (password_ustuvannja == 0x1978)
    {
      if (method_setting == SET_DATA_IMMEDITATE)
        ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA  ]  = data;
      else
        edit_ustuvannja[address_data - MA_ADDRESS_FIRST_USTUVANNJA  ]  = data;
    }
    else 
    {
      /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
  }
//  else if ((address_data >= MA_ADDRESS_FIRST_PHI_USTUVANNJA ) && (address_data <= MA_ADDRESS_LAST_PHI_USTUVANNJA))
//  {
//    //������ ���������
//    if (password_ustuvannja == 0x1978)
//    {
//      unsigned int index = address_data - MA_ADDRESS_FIRST_PHI_USTUVANNJA; 
//      int phi_tmp = (short int)data;
//      float phi_radian_tmp = PI*((float)phi_tmp)/1800.0f; /*������� ��� �������������� � ������ �� ������� ����� ������, �� ��� ����, ��� �������� ��������� ������ - ����� ������� �� �� 180 � �� 1800= 180�10 */
//      if (method_setting == SET_DATA_IMMEDITATE)
//      {
//        phi_ustuvannja[index] = phi_tmp;
//        phi_ustuvannja_sin_cos[2*index    ] = arm_sin_f32(phi_radian_tmp);
//        phi_ustuvannja_sin_cos[2*index + 1] = arm_cos_f32(phi_radian_tmp);
//      }
//      else
//      {
//        phi_edit_ustuvannja[index] = phi_tmp;
//        phi_edit_ustuvannja_sin_cos[2*index    ] = arm_sin_f32(phi_radian_tmp);
//        phi_edit_ustuvannja_sin_cos[2*index + 1] = arm_cos_f32(phi_radian_tmp);
//      }
//    }
//    else 
//    {
//      /*� ��� ����������� ��� ������� ��� ������� ��������� ����� ��� ���� ������ ������ � �����������, ��� �������� ��������� ����������������� ������ ���������*/
//      error = ERROR_ILLEGAL_DATA_ADDRESS;
//    }
//  }
//  else if (address_data == MA_NUMBER_ITERATION_EL)
//  {
//    temp_value = data;
//    
//    if ((temp_value >= NUMBER_ITERATION_EL_MIN) && (temp_value <= NUMBER_ITERATION_EL_MAX))
//      target_label->number_iteration_el = temp_value;
//    else
//      error = ERROR_ILLEGAL_DATA_VALUE;
//  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_WRITE)
  {
    registers_address_write = (registers_address_write & 0xffff0000) + (data);
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_WRITE)
  {
   registers_address_write = (registers_address_write & 0xffff) + (data << 16);
  }
  else if (address_data == MA_LSW_DATA_MEMORY_TO_WRITE)
  {
    unsigned int *label;

    data_write_to_memory = (data_write_to_memory & 0xffff0000) + (data);
    label = (unsigned int *)(registers_address_write);
    *label = data_write_to_memory;
  }
  else if (address_data == MA_MSW_DATA_MEMORY_TO_WRITE)
  {
    data_write_to_memory = data << 16;
  }
  else if (address_data == MA_NB_REG_FROM_MEM_READ)
  {
    number_registers_read = data;
  }
  else if (address_data == MA_LSW_ADR_MEMORY_TO_READ)
  {
    unsigned int index;
    unsigned short int *label;

    registers_address_read = (registers_address_read & 0xffff0000) + (data);
    label = (unsigned short int *)(registers_address_read);
	  
    for (index = 0; index<number_registers_read; index++)
    {	
      registers_values[index] = *(label++);
    }
  }
  else if (address_data == MA_MSW_ADR_MEMORY_TO_READ)
  {
    registers_address_read = (registers_address_read & 0xffff) + (data << 16);
  }
  else if (address_data == MA_PART_RECEIVE_DIG_OSCILOGRAPH)
  {
    part_transmit_carrent_data = data;
    if(part_transmit_carrent_data == 0)
    {
      action_is_continued = true;
      command_to_receive_current_data = true;
    }
  }
  else if (address_data == MA_DEFAULT_SETTINGS)
  {
    if (data != CMD_WORD_SET_DEFAULT_SETTINGS)
    {
      //��� ������������ �������� ������������ �� ���� ��������� �� ����� ����� ��������� ����� - ������ �����������, �� ���� ������ ������ �� ���� (���������� ����� ���������� �� ����������������� ���������� ����� ���'��)
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else
    {
      //������� ��������� � "������� �������� ��������"
//      min_settings(target_label);
    }
  }
  else if (address_data == MA_TEST_WATCHDOGS)
  {
    if (data != CMD_TEST_EXTERNAL_WATCHDOG)
    {
      //��� ���������� watchdog ����� ������� ��������� ����� ���� ���������� - ������ �����������, �� ���� ������ ������ �� ���� (���������� ����� ���������� �� ����������������� ���������� ����� ���'��)
      error = ERROR_ILLEGAL_DATA_ADDRESS;
    }
    else
    {
      //�������� ������� �� ���������
      test_watchdogs = data;
    }
  }
  else if (address_data == MA_CMD_RESET_RESURS_MIN_MAX)
  {
    //������� ��������� ��� �������
    restart_resurs_count = 0xff;/*��������� �������� ����������� ���������*/
  }
  else error = ERROR_ILLEGAL_DATA_ADDRESS;

  return error;
}
/***********************************************************************************/

/***********************************************************************************/
//������� �����
/***********************************************************************************/
//inline unsigned int Get_data_file(unsigned char* input_data, unsigned char* output_data, unsigned int* total_number_answer, unsigned int type_interface)
//{
//  unsigned int error = 0;
//  if( *(input_data + 0) == 0x6)
//  {
//    unsigned int number_file, number_record, length;
//    number_file   = ((*(input_data + 1)) << 8) + (*(input_data + 2));
//    number_record = ((*(input_data + 3)) << 8) + (*(input_data + 4));
//    length        = ((*(input_data + 5)) << 8) + (*(input_data + 6));
//    
//    unsigned int number_answer_local = (length << 1) + 1;
//    
//    *total_number_answer += (number_answer_local + 1); 
//
//    if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
//    {
//      //���������� ������ ���� �� ���� � �����
//      error = ERROR_SLAVE_DEVICE_FAILURE;
//    }
//    else if (
//             (number_file == 0)
//             ||  
//             (
//              (number_file >= 5) && 
//              (number_file <= 6) && 
//              (
//               ((type_interface == USB_RECUEST  ) && (number_record_of_dr_for_USB   == 0xffff)) ||
//               ((type_interface == RS485_RECUEST) && (number_record_of_dr_for_RS485 == 0xffff))
//              )   
//             )
//             ||  
//             (number_file > 6)
//            )
//    {
//      //������� ����� �����, ��� �� ������ ������� ����������� ���������� ������
//      error = ERROR_ILLEGAL_DATA_ADDRESS;
//    }
//    else if (
//             (number_file >= 5) &&
//             (number_file <= 6) && 
//             (
//              (
//               ((type_interface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
//               ((type_interface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
//              ) 
//              ||  
//              ((clean_rejestrators & CLEAN_DR) != 0)
//             )  
//            )   
//    {
//      //����� ��� ���������� ��� ���������� ������ ����������� ����������, ���� �� �������� � ��������� �����������
//      error = ERROR_SLAVE_DEVICE_BUSY;
//    }
//    else if ((*total_number_answer + 5) < 255)
//    {
//      *(output_data + 0 ) = number_answer_local;
//      *(output_data + 1 ) = 0x6;
//      //������ ����� ��� ����� ������
//
//      int temp_data;
//      switch (number_file)
//      {
//      case 5:
//        {
//          //*************************************
//          //��������� ��� ����������� ����������
//          //*************************************
//          unsigned char *point_to_buffer;
//          if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
//          else point_to_buffer = buffer_for_RS485_read_record_dr;
//
//          switch (number_record)
//          {
//          case 0:
//            {
//              if (length <= 10)
//              {
//                unsigned int i = 0;
//                while (i < length)
//                {
//                  if (i < 8)
//                  {
//                    unsigned int index_cell;
//                    
//                    index_cell =  (i - 0)<<1;
//                    temp_data  = (*(point_to_buffer + FIRST_INDEX_NAME_OF_CELL_DR + index_cell)) | ((*(point_to_buffer + FIRST_INDEX_NAME_OF_CELL_DR + index_cell + 1))<<8);
//                  }
//                  else if (i == 8)
//                  {
//                    //������� ����� �������� ������ ���� � ��� ����� (�������������� �� �����-�����������), ���� � ���� �� ������� ��� ������ � DataFlash � ����� ��������� ����������� ����������
//                    temp_data = serial_number_dev & 0xffff;
//                  }
//                  else
//                  {
//                    temp_data = 1999;
//                  }
//                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
//                  *(output_data + 3 + 2*i) = temp_data & 0xff;
//                  i++;
//                }
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          case 1:
//            {
//              if (length <= 3)
//              {
//                unsigned int i = 0;
//                while (i < length)
//                {
//                  if (i == 0)
//                  {
//                    temp_data  = 0 + NUMBER_TOTAL_SIGNAL_FOR_RANG;
//                  }
//                  else if (i == 1)
//                  {
//                    temp_data = 0;
//                  }
//                  else
//                  {
//                    temp_data = NUMBER_TOTAL_SIGNAL_FOR_RANG;
//                  }
//                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
//                  *(output_data + 3 + 2*i) = temp_data & 0xff;
//                  i++;
//                }
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          case 2:
//          case 3:
//          case 4:
//          case 5:
//          case 6:
//          case 7:
//          case 8:
//          case 9:
//          case 10:
//          case 11:
//          case 12:
//          case 13:
//          case 14:
//          case 15:
//          case 16:
//          case 17:
//          case 18:
//          case 19:
//          case 20:
//          case 21:
//          case 22:
//          case 23:
//          case 24:
//          case 25:
//          case 26:
//          case 27:
//          case 28:
//          case 29:
//          case 30:
//          case 31:
//          case 32:
//          case 33:
//          case 34:
//          case 35:
//          case 36:
//          case 37:
//          case 38:
//          case 39:
//          case 40:
//          case 41:
//          case 42:
//          case 43:
//          case 44:
//          case 45:
//          case 46:
//          case 47:
//          case 48:
//          case 49:
//          case 50:
//          case 51:
//          case 52:
//          case 53:
//          case 54:
//          case 55:
//          case 56:
//          case 57:
//          case 58:
//          case 59:
//          case 60:
//          case 61:
//          case 62:
//          case 63:
//          case 64:
//          case 65:
//          case 66:
//          case 67:
//          case 68:
//          case 69:
//          case 70:
//          case 71:
//          case 72:
//          case 73:
//          case 74:
//          case 75:
//          case 76:
//          case 77:
//          case 78:
//          case 79:
//          case 80:
//          case 81:
//          case 82:
//          case 83:
//          case 84:
//          case 85:
//          case 86:
//          case 87:
//          case 88:
//          case 89:
//          case 90:
//          case 91:
//          case 92:
//          case 93:
//          case 94:
//            {
//              if (length <= 19)
//              {
//                unsigned int i = 0;
//                while (i < length)
//                {
//                  if (i == 0)
//                  {
//                    //����� ������
//                    temp_data = (number_record - 2) + 1;
//                  }
//                  else if ( i < 9)
//                  {
//                    //��������������� ������ - 16 ASCII �������
//                    const char idetyficator[MAX_NAMBER_LANGUAGE][NUMBER_TOTAL_SIGNAL_FOR_RANG][16] =
//                    {
//                      {NAME_RANG_RU},
//                      {NAME_RANG_UA},
//                      {NAME_RANG_EN},
//                      {NAME_RANG_KZ},
//                    };
//                    int index_language = index_language_in_array(settings_fix.language);
//                    unsigned int index_cell;
//                    
//                    index_cell =  (i - 1)<<1;
//                    temp_data  = idetyficator[index_language][number_record - 2][index_cell] | (idetyficator[index_language][number_record - 2][index_cell+1]<<8);
//                  }
//                  else if ( i == 9)
//                  {
//                    //���� ������ - 2 ASCII ������� - ����� �� ��������
//                    temp_data  = (' '<<8) | ' ';
//                  }
//                  else if ( i < 18)
//                  {
//                    //������������ ������� � ��� - 16 ASCII �������- ����� �� ��������
//                    temp_data  = (' '<<8) | ' ';
//                  }
//                  else if ( i == 18)
//                  {
//                    //���������� ����
//                    temp_data  = 0;
//                  }
//                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
//                  *(output_data + 3 + 2*i) = temp_data & 0xff;
//                  i++;
//                }
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          case ( 2 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//          case ( 3 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//            {
//              if (length <= 1)
//              {
//                
//                if (number_record == ( 2 + NUMBER_TOTAL_SIGNAL_FOR_RANG))
//                {
//                  temp_data  = MAIN_FREQUENCY*100; //������ ��
//                }
//                else
//                {
//                  temp_data  = 0; //ʳ������ ������ �������������
//                }
//                *(output_data + 2 ) = (temp_data >> 8) & 0xff;
//                *(output_data + 3 ) = temp_data & 0xff;
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          case ( 4 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//            {
//              if (length <= 2)
//              {
//                unsigned int i = 0;
//                while (i < length)
//                {
//                  if (i == 0) temp_data  = 0; //������� �������
//                  else
//                  {
//                      temp_data = *(point_to_buffer + FIRST_INDEX_NUMBER_ITEMS_DR); //������� ������� � ����������� ��������� ������� � ������� �������� ������� (� ��� ������)
//                  }
//                  
//                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
//                  *(output_data + 3 + 2*i) = temp_data & 0xff;
//                  i++;
//                }
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          case ( 5 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//          case ( 6 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//            {
//              
//              if (length <= 7)
//              {
//                //���������� ������ BCD � int
//                unsigned int time_avar_digital[7];
//
//                //���������� ������ BCD � int
//                for (unsigned int i = 0; i < 7; i++)
//                {
//                  unsigned int val = *(point_to_buffer + FIRST_INDEX_DATA_TIME_DR + i), val_l, val_m;
//                  val_l = val & 0xf;
//                  val_m = (val >> 4) & 0xf;
//                  time_avar_digital[i] = val_m*10 + val_l;
//                }
//                  
//                unsigned int i = 0;
//                while (i < length)
//                {
//                  if (i < 3)
//                  {
//                    temp_data = time_avar_digital[4 + i];
//                    if (i == 2)temp_data += 2000; //�� ������ �� ���� ������������� ������
//                  }
//                  else if (i < 5 ) temp_data = time_avar_digital[3 - (i - 3)];
//                  else if (i == 5) temp_data = time_avar_digital[1]*100 + time_avar_digital[0];
//                  else temp_data = 0;/*�������� �������� - ����� � ����� ������ �� ���������*/
//
//                  *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
//                  *(output_data + 3 + 2*i) = temp_data & 0xff;
//                  i++;
//                }
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          case ( 7 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//          case ( 8 + NUMBER_TOTAL_SIGNAL_FOR_RANG):
//            {
//              if (length <= 1)
//              {
//                
//                if (number_record == ( 7 + NUMBER_TOTAL_SIGNAL_FOR_RANG))
//                {
//                  temp_data  = 'B'; //��� - �� ����� �����
//                }
//                else temp_data  = 1000; //�������, �� ���� ��������� ������ ���� � ����� �����, ��� �������� �����������
//                *(output_data + 2 ) = (temp_data >> 8) & 0xff;
//                *(output_data + 3 ) = temp_data & 0xff;
//              }
//              else error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          default:
//            {
//              error = ERROR_ILLEGAL_DATA_ADDRESS;
//              break;
//            }
//          }
//          //*************************************
//          break;
//        }
//      case 6:
//        {
//          //*************************************
//          //��� 1 ��� ����������� ����������
//          //*************************************
//          unsigned char *point_to_buffer;
//          if (type_interface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
//          else point_to_buffer = buffer_for_RS485_read_record_dr;
//
//          if (number_record < (*(point_to_buffer + FIRST_INDEX_NUMBER_ITEMS_DR)))
//          {
//            unsigned int max_number_two_bytes = (NUMBER_TOTAL_SIGNAL_FOR_RANG >> 4);
//            if ((max_number_two_bytes << 4) != NUMBER_TOTAL_SIGNAL_FOR_RANG)
//              max_number_two_bytes++;
//              
//            if (length <= (3 + max_number_two_bytes))
//            {
//              unsigned int i = 0;
//              while (i < length)
//              {
//                if (i == 0) temp_data = number_record + 1;
//                else
//                {
//                  unsigned int offset = FIRST_INDEX_FIRST_DATA_DR + (number_record + 1)*29; //�� ��������� ����� ������ �������� �������� (�� �������� ������� ������ ����������� ����������)
//                  if (i == 1)
//                  {
//                    temp_data =  (*(point_to_buffer + offset + 0)) + ((*(point_to_buffer + offset + 1)) << 8 );
//                  }
//                  else if (i == 2)
//                  {
//                    temp_data =  *(point_to_buffer + offset + 2);
//                  }
//                  else
//                  {
//                    temp_data = (*(point_to_buffer + offset + 3 + (i - 3)*2)) + ((*(point_to_buffer + offset + 4 + (i - 3)*2)) << 8);
//                  }
//                }
//                *(output_data + 2 + 2*i) = (temp_data >> 8) & 0xff;
//                *(output_data + 3 + 2*i) = temp_data & 0xff;
//                i++;
//              }
//            }
//            else error = ERROR_ILLEGAL_DATA_ADDRESS;
//          }
//          else error = ERROR_ILLEGAL_DATA_ADDRESS;
//          //*************************************
//          break;
//        }
//      default:
//        {
//          //����������, ���� �������� ����� �� ���� ��������
//          error = ERROR_ILLEGAL_DATA_ADDRESS;
//          break;
//        }
//      }
//    }
//    else error = ERROR_ILLEGAL_DATA_ADDRESS;
//  }
//  else error = ERROR_ILLEGAL_DATA_ADDRESS;
//  return error;  
//}
/***********************************************************************************/

/***********************************************************************************/
//������ ������� ��� �������� ����� ����� ��������� RS-485
/***********************************************************************************/
inline void start_transmint_data_via_RS_485(unsigned int count)
{
  //����������, �� ����� ���������� ���
  unsigned int current_time_tim4 = TIM4->CNT;
  unsigned int delta_time;

  //���������� ���, �������� ����� ��������������� �������
  if (
      (current_time_tim4 > time_last_receive_byte) ||
      (
       (current_time_tim4 == time_last_receive_byte) &&
       (mark_current_tick_RS_485 != 0)  
      ) 
     )   
    delta_time = current_time_tim4 - time_last_receive_byte;
  else 
    delta_time = current_time_tim4 + 0xffff - time_last_receive_byte;

  if (max_reaction_time_rs_485 < delta_time) max_reaction_time_rs_485 = delta_time;
  
  if (delta_time < MAX_TIMEOUT_PACKET)
  {
    //����� ��������� �� �����

    //���������� ��������� �� ��������
    GPIO_485DE->BSRRL = GPIO_PIN_485DE;

    //������� ��, �� ��������, �� �������� ���� ���������
    USART_ClearFlag(USART_RS485, USART_FLAG_TC);

    //���������� ��������� �����������, ����  ���� �������� �� ����� �� DMA1 ����� ����� DMA1_ChannelRS485_TX
    DMA_StreamRS485_Tx->CR |= DMA_IT_TC;

    //��������� ���� DMA ���� �� ���������
    if ((DMA_StreamRS485_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
    DMA_StreamRS485_Tx->NDTR = count;
    //���������� �������� ����� DMA
    if ((USART_RS485->CR3 & USART_DMAReq_Tx) == 0) USART_RS485->CR3 |= USART_DMAReq_Tx;

    //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_TX
    DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
    //��������� ��������
    DMA_StreamRS485_Tx->CR |= (uint32_t)DMA_SxCR_EN;
  }
  else
  {
    //�� ����� ��������� �� �����, �� ������� ��������� ������ ��� �� ��������� ��� ���������� ������ - ����� ���������� �� ������ ����������� �� RS-485
    restart_monitoring_RS485();
  }
}
/***********************************************************************************/

/***********************************************************************************/
//�������� ������� ������ �� ��������� MODBUS-RTU
/***********************************************************************************/
void modbus_rountines(unsigned int type_interface)
{
 unsigned char *received_buffer, *transmited_buffer;
 int volatile *received_count;
 int *transmited_count;
 unsigned int error = 0;
  
  if(type_interface == USB_RECUEST)
  {
    received_buffer = usb_received;
    transmited_buffer = usb_transmiting;
    received_count = &usb_received_count;
    transmited_count = &usb_transmiting_count;
  }
  else if (type_interface == RS485_RECUEST)
  {
    received_buffer = RxBuffer_RS485;
    transmited_buffer = TxBuffer_RS485;
    received_count = &RxBuffer_RS485_count;
    transmited_count = &TxBuffer_RS485_count;
  }
  else
  {
    //���������� ����� ����� �� ���� � ����
    total_error_sw_fixed(45);
  }
   
  //�������� ������ ������������ �������
  unsigned int global_requect;
  if(
     (*received_count >= 3)  
     &&
     (
      ((global_requect = (*received_buffer == BROADCAST_ADDRESS_MODBUS_RTU)) != 0) ||
      (*received_buffer == settings_fix.address)
     )
    )   
  {
    unsigned short int CRC_sum;
    
    //�������� ���������� ����
    CRC_sum = 0xffff;
    for (int index = 0; index < (*received_count-2); index++) CRC_sum = AddCRC(*(received_buffer + index),CRC_sum);

    unsigned int func_modbus = *(received_buffer+1);
    if (
        ((CRC_sum & 0xff) == *(received_buffer+*received_count-2)) &&
        ((CRC_sum >> 8  ) == *(received_buffer+*received_count-1)) &&
        (
         (global_requect == 0) ||
         (func_modbus == 6 ) ||
         (func_modbus == 16)
        )
       )
    {
      //������ ������� �� �������� ��������� ���������� ������ ������ � ��������� ����������
      restart_timeout_interface |= (1 << type_interface);
      
      //������� �����
      switch (func_modbus)
      {
      case 1:
      case 2:
        {
          unsigned int add_data, number;
          unsigned int number_byte_transmit, number_word_transmit, number_word_read;
          unsigned int offset;

          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));
          
          number_byte_transmit = number >> 3;
          if((number_byte_transmit<<3) < number) number_byte_transmit++; //������� ��� ����� ������������� �� ������� ����� ��� ����� �� 8 (���� �� ��� ������� ����)

          //��������� ������� ������������� ��� (2 �����) � ������
          if ((number_byte_transmit & 0x1) == 0)
          {
            //����� ������� ����, � ������� ������ �� 2 ����� ����� ������� ���
            number_word_transmit = number_byte_transmit >> 1;
          }
          else
          {
            //������� ������� ����, � ������� ����� ������� �� 2 ����� �� ������ ���� ����, ��� �������� ������� ��� ��� ����������
            number_word_transmit = (number_byte_transmit + 1) >> 1;
          }
                   
          if(
             (number != 0                   ) &&
             (number_byte_transmit < (255-5)) &&
             (
#if (BIT_MA_OUTPUTS_LAST + 1) < BIT_MA_INPUTS_LAST
              ((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_OUTPUTS_LAST   )) ||
              ((add_data >= BIT_MA_INPUTS_BASE    ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST    )) ||
#else
              ((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST    )) ||
#endif
              ((add_data >= BIT_MA_LEDS_BASE      ) && ((add_data + number - 1) <= BIT_MA_LEDS_LAST      )) ||
              ((add_data >= BIT_MA_CONTROL_BASE   ) && ((add_data + number - 1) <= BIT_MA_CONTROL_LAST   )) ||
#if (BIT_MA_CURRENT_AF_LAST + 1) < BIT_MA_GENERAL_AF_BASE
              ((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_CURRENT_AF_LAST)) ||
              ((add_data >= BIT_MA_GENERAL_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST)) 
#else
              ((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST)) 
#endif
             )
            )
          {
            unsigned int first_address_of_word_for_function_3_or_4;

            //������� ������� ������
            *transmited_buffer = *(received_buffer);
            *(transmited_buffer + 1) = *(received_buffer + 1);
            *(transmited_buffer + 2) = number_byte_transmit;

#if (BIT_MA_OUTPUTS_LAST + 1) < BIT_MA_INPUTS_LAST            
            if((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_OUTPUTS_LAST   ))
            {
              //���� ������
              offset = add_data - BIT_MA_OUTPUTS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_OUTPUTS;
            }
            else if((add_data >= BIT_MA_INPUTS_BASE    ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST    ))
            {
              //���� �����
              offset = add_data - BIT_MA_INPUTS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_INPUTS;
            }
#else
            if((add_data >= BIT_MA_OUTPUTS_BASE   ) && ((add_data + number - 1) <= BIT_MA_INPUTS_LAST   ))
            {
              //���� ������ + �����
              offset = add_data - BIT_MA_OUTPUTS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_OUTPUTS;
            }
#endif
            else if((add_data >= BIT_MA_LEDS_BASE      ) && ((add_data + number - 1) <= BIT_MA_LEDS_LAST      ))
            {
              //���� ��������������
              offset = add_data - BIT_MA_LEDS_BASE;
              first_address_of_word_for_function_3_or_4 = MA_LEDS;
            }
            else if((add_data >= BIT_MA_CONTROL_BASE   ) && ((add_data + number - 1) <= BIT_MA_CONTROL_LAST   ))
            {
              //���� ������� �������
              offset = add_data - BIT_MA_CONTROL_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_CONTROL_BASE;
            }
#if (BIT_MA_CURRENT_AF_LAST + 1) < BIT_MA_GENERAL_AF_BASE
            else if((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_CURRENT_AF_LAST))
            {
              //���� �������� �������
              offset = add_data - BIT_MA_CURRENT_AF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_FIRST_CURRENT_AF;
            }
            else if((add_data >= BIT_MA_GENERAL_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST))
            {
              //���� �������� �������
              offset = add_data - BIT_MA_GENERAL_AF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_FIRST_GENERAL_AF;
            }
#else
            else if((add_data >= BIT_MA_CURRENT_AF_BASE) && ((add_data + number - 1) <= BIT_MA_GENERAL_AF_LAST))
            {
              //���� �������� �������
              offset = add_data - BIT_MA_CURRENT_AF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_FIRST_CURRENT_AF;
            }
#endif
            
            //���������, � ����� ����� ����� ��������� ���������� ������ �������
            first_address_of_word_for_function_3_or_4 += (offset >> 4);
            //��������� �� ������ �� ������
            offset &= 0xf;
            
            number_word_read = number_word_transmit;
            /*
            ��������� ������ ��� ����� ��������� (��������� ������ �� ������� �� 
            � � ������ �� �������� ��������� �� �����, ��� ���� ��������� �������� Get_data
            �  ������ �������, �� ���� ������ �� �� ���� �������� � ������ ������ ��� �������� ��������)
            ��� �� ��������� ������ ��� ����� ���� ��������� �������� Get_data ��� �������� ��� ��� ��������
            */
            if ((offset + number) > (number_word_transmit << 4)) number_word_read++; //�� ���� ��������� �� �������� ����� �� ������� �������
            
            //������� �������� ��� �����
            unsigned int i=0;
            while((i < number_word_read) && ((error = Get_data((transmited_buffer + 3 + 2*i), (first_address_of_word_for_function_3_or_4 + i), type_interface))==0)) i++;
          }
          else
          {
            if ((number == 0) || (number_byte_transmit >= (255-5))) error = ERROR_ILLEGAL_DATA_VALUE;
            else error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          
          //������� ����� ������ � ���� ������� � �������� MODBUS-RTU
          if (error == 0)
          {
            unsigned short int temp_value_for_offset, current_word, next_word;
            unsigned int maska = 0, max_bit_in_high_byte = (number & 0x7);
            
            for(unsigned int i = 0; i < number_word_transmit; i++)
            {
              //������� Get_data �������� ����� � ������� MSB-LSB � �.�
              current_word = (*(transmited_buffer + 3 + 2*i) << 8) | (*(transmited_buffer + 3 + 2*i + 1));
              if ((i + 1) < number_word_read) next_word = (*(transmited_buffer + 3 + 2*(i + 1)) << 8) | (*(transmited_buffer + 3 + 2*(i + 1) + 1));
              else next_word = 0;
              
              //��������� , �� ��� � ���������� ����� ����� ���������� � ���� ����� � ������ �� � ������ �������
              temp_value_for_offset = next_word << (16 - offset);
              
              //������� ����� �� ����������� �������
              temp_value_for_offset |= (current_word >> offset);
             
              if((2*i    ) < number_byte_transmit)
                *(transmited_buffer + 3 + 2*i    ) = temp_value_for_offset        & 0xff;
              if((2*i + 1) < number_byte_transmit)
                *(transmited_buffer + 3 + 2*i + 1) = (temp_value_for_offset >> 8) & 0xff;
            }
            
            //� ���������� ���� ����� ���� ��� ���������
            if (max_bit_in_high_byte != 0)
            {
              for(unsigned int i = 0; i < max_bit_in_high_byte; i++) maska = (maska << 1) + 0x1;
              *(transmited_buffer + 3 + number_byte_transmit - 1 ) &= maska;
            }
              
            CRC_sum = 0xffff;
            for (int index = 0; index < ((int)(number_byte_transmit + 3)); index++) CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            *(transmited_buffer + 3 + number_byte_transmit + 0) = CRC_sum & 0xff;
            *(transmited_buffer + 3 + number_byte_transmit + 1) = CRC_sum >> 8;

            *transmited_count = number_byte_transmit + 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          else
          {
            //³�������� ��� �������
            Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          
          break;
        }//ʳ���� ��� ������� ������� 1 � 2
      case 3:
      case 4:
        {
          unsigned int add_data, number;
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));
          
          if ((number == 0) || (number > ((255-5)>>1)))
          {
            //������� ������ ������� �������
            error = ERROR_ILLEGAL_DATA_VALUE;
          }
          else
          {
            *transmited_buffer = *(received_buffer);
            *(transmited_buffer + 1) = *(received_buffer + 1) ;
            *(transmited_buffer + 2) = number*2;

            add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));

            if (
                /*((add_data >= M_ADDRESS_FIRST_MEASUREMENTS_1 ) && (add_data <= M_ADDRESS_LAST_MEASUREMENTS_1)) ||
                ((add_data >= M_ADDRESS_FIRST_MEASUREMENTS_2 ) && (add_data <= M_ADDRESS_LAST_MEASUREMENTS_2)) ||*/
                ((add_data >= M_ADDRESS_FIRST_TMP_MEASURMENTS) && (add_data <  M_ADDRESS_LAST_TMP_MEASURMENTS))  
               )
            {
              //������� ����������
              semaphore_measure_values_low1 = 1;
              for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++ ) 
              {
                measurement_low[i] = measurement_middle[i];
              }
              semaphore_measure_values_low1 = 0;
            }

            unsigned int i=0;
            while((i<number) && ((error = Get_data((transmited_buffer+3+2*i),(add_data+i), type_interface))==0))i++;
          }

          if (error == 0)
          {
            CRC_sum = 0xffff;
            for (int index = 0; index < ((int)(3+2*number)); index++) CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            *(transmited_buffer+3+2*number) = CRC_sum & 0xff;
            *(transmited_buffer+4+2*number) = CRC_sum >> 8;

            *transmited_count = 5+2*number;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          else
          {
            Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }

          break;
        }//ʳ���� ��� ������� ������� 3 � 4
      case 5:
        {
          unsigned int add_data;
          unsigned short int value, temp_value = 0;
          unsigned int offset;
          
          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          value    = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
          {
            //���������� ������ ���� �� ���� � �����
            error = ERROR_SLAVE_DEVICE_FAILURE;
          }
          else if(
                  (
                   ((value == 0 ) || (value == 0xff00)) && 
                   (
                    ((add_data >= BIT_MA_CONTROL_BASE) && (add_data <= BIT_MA_CONTROL_LAST)) || /*��������� �������*/
                    (add_data == BIT_MA_NEW_SETTINGS_SET) /*������� ��������� �������� ��� � ������������ ������� ����� ���������*/ 
                   )
                  )   
                  || 
                  (
                   (value == 0xff00) 
                   &&
                   (
                    (add_data == BIT_MA_RESET_GENERAL_AF) /*�������� ��������� �������*/
                    ||
                    (  
                     ((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8)) || /*����� ������������ �������*/
                     ((add_data >= BIT_MA_DT1_SET  ) && (add_data <= BIT_MA_DT4_RESET))/* ||*/ /*������������ ��������*/
//                     ( add_data == BIT_MA_RESET_LEDS                                  ) || /*�������� ���������*/
//                     ( add_data == BIT_MA_RESET_RELES                                 )    /*�������� ����*/
                    )
                   )   
                  )
                 )
          {
            unsigned int first_address_of_word_for_function_3_or_4;
           
            //��������� ���������� ������� ������ � ������� ������� ���� ������� ���
            if ((add_data >= BIT_MA_CONTROL_BASE) && (add_data <= BIT_MA_CONTROL_LAST))
            {
              //���� ������� �������
              offset = add_data - BIT_MA_CONTROL_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_CONTROL_BASE;
            }
            else if ((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8))
            {
              offset = add_data - BIT_MA_DF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DF;
            }
            else if (( add_data >= BIT_MA_DT1_SET) && (add_data <= BIT_MA_DT4_RESET ))
            {
              offset = add_data - BIT_MA_DT_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DT;
            }
            else if(
//                    (add_data == BIT_MA_RESET_LEDS            ) || /*�������� ���������*/
//                    (add_data == BIT_MA_RESET_RELES           ) || /*�������� ����*/
                    (add_data == BIT_MA_RESET_GENERAL_AF      ) || /*�������� ��������� �������*/
                    (add_data == BIT_MA_NEW_SETTINGS_SET      )    /*������� ��������� �������� ��� � ������������ ������� ����� ���������*/
                   )
            {
              offset = add_data - BIT_MA_COMMAND_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_COMMAND_BASE;
            }
            
            //�������� ��
            if (first_address_of_word_for_function_3_or_4 == M_ADDRESS_CONTROL_BASE)
            {
              //��� ��������� ������ ��������� �������
              
              ///����������, �� ������ ������� ������ � �� ������� ���� �� � � ���� �����������
              if (
                  (
                   ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                   ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                  )
                  &&  
                  (current_state_menu2.edition == ED_VIEWING)
                 )
              {
                //����� ��������� ����� ���, ���� ������ ������ � ������� ���� �� � ����� �����������, ��� ��� ������� ���������
            
                //���������, � ����� ����� ����� ��������� ���������� ������ �������
                first_address_of_word_for_function_3_or_4 += (offset >> 4);

                //��������� �� ������ ������� ���������� � ���������� ����
                offset &= 0xf;
            
                //������� �������� ���� �����
                unsigned char temp_value_in_char[2];
                error = Get_data(temp_value_in_char, first_address_of_word_for_function_3_or_4, type_interface);
                temp_value = temp_value_in_char[1];
                temp_value |= temp_value_in_char[0] << 8;

                if (error == 0)
                {
                  //���� ������ ���������� �����, �� ������� ����, ���� ����� �������� 
                  if (value == 0xff00) temp_value |=   (1 << offset); //����������
                  else if (value == 0x0)temp_value &= ~(1 << offset); //�����
                  else error = ERROR_ILLEGAL_DATA_VALUE;              //����������� ��������, ��� ���������� ����� �� ���� ������� �� ���������� �� �� ����� ��� �������� � �� �������� �������� �� �����������

                  if (error == 0)
                  {
                    error = Set_data(temp_value,first_address_of_word_for_function_3_or_4, SET_DATA_IMMEDITATE, /*false,*/ type_interface);
                    if (error == 0)
                    {
                      //ĳ���� �������� ���� ���������
//                      _SET_BIT(active_functions, RANG_SETTINGS_CHANGED);
                      restart_timeout_idle_new_settings = true;
                      type_of_settings_changed_from_interface |= (1 << SETTINGS_DATA_CHANGED_BIT);
                    }
                  }
                }
              }
              else
              {
                if (current_state_menu2.edition != ED_VIEWING) error = ERROR_SLAVE_DEVICE_BUSY;
                else error = ERROR_ILLEGAL_DATA_ADDRESS;
              }
            }
            else if (
                     (
                      ((first_address_of_word_for_function_3_or_4 == M_ADDRESS_DF) || (first_address_of_word_for_function_3_or_4 == M_ADDRESS_DT))
                      &&
                      (
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                      ) 
                     )
                     ||  
                     (
                      (first_address_of_word_for_function_3_or_4 == M_ADDRESS_COMMAND_BASE)
                      &&
                      (
                       (add_data != BIT_MA_NEW_SETTINGS_SET) ||
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                      )   
                     )   
                    )
            {
              //��� ������ ��������� �������
              
              /*
              ��� �� ������������� ���������� ��������� ������� � ��������� �-������, �� ������� ������� ��������� �� ���������
              ������� � �-������, �� ��������� ������� � ���������
              */
              /*     if  (add_data == BIT_MA_RESET_LEDS                       ) activation_function_from_interface |= 1 << RANG_TU_RESET_LEDS;
              else if  (add_data == BIT_MA_RESET_RELES                      ) activation_function_from_interface |= 1 << RANG_TU_RESET_RELES;
              else*/ if  (add_data == BIT_MA_RESET_GENERAL_AF) 
              {
                //�������� ��������� ������� 
                reset_trigger_function_from_interface |= (1 << type_interface);
              }
              else if  (add_data == BIT_MA_NEW_SETTINGS_SET) 
              {
                /*������� ��������� �������� ��� � ������������ ������� ����� ���������*/ 
                if (value == 0xff00)
                {
                  //��������� ��������� ���
                  unsigned int source = MENU_PARAMS_FIX_CHANGES;
                  if(type_interface == USB_RECUEST) source = USB_PARAMS_FIX_CHANGES;
                  else if(type_interface ==  RS485_RECUEST) source = RS485_PARAMS_FIX_CHANGES;

                  unsigned int result = set_config_and_settings(1, source);
                  if (result != 0)
                  {
                    error = ERROR_SLAVE_DEVICE_FAILURE;
                    if (result == 2)
                    {
                      //����������� ��� �������� �������
                      current_state_menu2.edition = ED_ERROR;
                    }
                  }
                }
                else
                {
                  //³���� ��������� ���
                  unsigned int result = set_config_and_settings(0, NO_MATTER_PARAMS_FIX_CHANGES);
                  if (result != 0)
                  {
                    //����������� ��� �������� �������
                    current_state_menu2.edition = ED_ERROR;
                  }
                }
                config_settings_modified = 0;
                type_of_settings_changed_from_interface = 0;
//                _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
              }
            }
            else
            {
              //���������� ���� �������� ����� �� ����� �����
              
              error = ERROR_ILLEGAL_DATA_ADDRESS;
            }
          }
          else
          {
            if (
                ((value != 0x0) && (value != 0xff00)) ||
                (
                 (value == 0x0) 
                 &&
                 (add_data != BIT_MA_NEW_SETTINGS_SET) /*������� ��������� �������� ��� � ������������ ������� ����� ���������*/
                 &&
                 (  
                  (add_data == BIT_MA_RESET_GENERAL_AF) /*�������� ��������� �������*/
                  ||
                  (  
                   ((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8)) || /*����� ������������ �������*/
                   ((add_data >= BIT_MA_DT1_SET ) && (add_data <= BIT_MA_DT4_RESET ))/* ||*/ /*�����. ������*/
//                   ( add_data == BIT_MA_RESET_LEDS                                  ) || /*�������� ���������*/
//                   ( add_data == BIT_MA_RESET_RELES                                 )    /*�������� ����*/
                  )
                 )   
                )
               ) error = ERROR_ILLEGAL_DATA_VALUE;
            else error = ERROR_ILLEGAL_DATA_ADDRESS;
          }
          
          if (error == 0)
          {
            for (int index = 0; index < 8; index++) *(transmited_buffer + index ) = *(received_buffer + index );
            *transmited_count = 8;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          else
          {
            //³�������� ��� �������
            Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          break;
        }//ʳ���� ��� ������� ������� 5        
      case 6:
        {
          unsigned int add_data;
          unsigned short int data;
          unsigned int changing_ustuvannja = 0;

          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          data     = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
          {
            //���������� ������ ���� �� ���� � �����
            error = ERROR_SLAVE_DEVICE_FAILURE;
          }
          else if (
                   (global_requect != 0) && /*����� �� ����� BROADCAST_ADDRESS_MODBUS_RTU ��������� Modbus-RTU*/
                   (
                    !(
                      ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA))
                     )
                   )     
                  )
          {
            /*
            �� �������� ����� ����� �������� ����� ��� � ����
            */
            error = ERROR_BROADCAST_ADDRESS;
          }
          else if (
                   (current_state_menu2.edition == ED_VIEWING                     ) ||
                   (add_data                    == MA_CURRENT_NUMBER_RECORD_PR_ERR)  
                  )
          {
            /*****/
            //�������� �� ����������� ������ ������� ��� ������
            /*****/
            if (
                (
                 ((type_interface == USB_RECUEST  ) && (password_set_USB   != 0)) ||
                 ((type_interface == RS485_RECUEST) && (password_set_RS485 != 0))
                )
                &&
                (
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )                                       ) || /*������� � ��������*/
                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))                                       ) || /*������� � �������� ����� �����*/
//                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))                                       ) || /*������� � �������� ����� �����*/
//                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))                                       ) || /*������� � �������� ������ �����*/
//                 ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))                                       ) || /*������� � �������� �������� �����*/
                 ((add_data >= M_ADDRESS_CONTROL_BASE                          ) && (add_data <= M_ADDRESS_CONTROL_LAST                         )                                       ) || /*������������ �������*/
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              ) && (add_data != MA_PASSWORD_INTERFACE)) || /*������� � �������� (�����������) ��� ������ �������*/
                 ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA                   ) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA                   )                                       ) || /*���*/
                 ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )                                       ) || /*����������*/
                  (add_data == MA_CLEAR_NUMBER_RECORD_PR_ERR                   )                                                                                                          || /*�������� ���������� ���������� ����*/        
                  (add_data == MA_DEFAULT_SETTINGS                             )                                                                                                          || /*������������ �������� ������������*/        
                  (add_data == MA_TEST_WATCHDOGS                               )                                                                                                        /*||*//*���������� ����������� � ���������� watchdog*/        
//                  (add_data == MA_NUMBER_ITERATION_EL                          )                                                                                                             /*����������������������� ������� ����������� ��������� �����*/        
                )   
               )
            {
              //�� ����� ����� �������� ��� ������, �� ����� �������� ����� ������ �������
              error = ERROR_ILLEGAL_DATA_ADDRESS;
            }
            else
            {
              unsigned int changed_ustuvannja_tmp; /*���� �������������� �����*/
              
              if ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA))
              {
                if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) == 0)
                {  
                  //��� ��������� ���������� ����� ���-����, ���� ������ ���� ����
                  unsigned char *label_to_time_array, *label_calibration;
                  if (copying_time == 0)
                  {
                    label_to_time_array = time;
                    label_calibration = &calibration;
                  }
                  else
                  {
                    label_to_time_array = time_copy;
                    label_calibration = &calibration_copy;
                  }
                  for(unsigned int index = 0; index < 7; index++) time_edit[index] = *(label_to_time_array + index);
                  calibration_edit = *label_calibration;
                }
                else
                {
                  /*
                  �� ���������� ��������� ������� ������ ����, � ���� ���� ������ 
                  ���������� ������ ��� ��� �������� �������� ���� (��� ���� ������� ����� ����)
                  ���� �� �������� � ��������� �����������
                  */
                  error = ERROR_SLAVE_DEVICE_BUSY;
                }
              }
              else if(
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG   ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG   )) /*����������*/
                     ) 
              {
                //���������� ��� ����, �� ����� ���� ���������� ����������, �� ������� �������� �� ��������� ���� � 0
                point_to_edited_rang = NULL;
//                for (unsigned int i = 0; i < N_BIG; i++)
//                {
//                  clear_array_rang[i] = 0;
//                  set_array_rang[i]   = 0;
//                }
              }
              else if((add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_USTUVANNJA))/*�������� � ���� ������� �����������*/ 
              {
                //������� ���������� ���������, �� ��� ��������� ������ ������� �����������
                changing_ustuvannja = 0xff;
                
                /*
                ������ ���� ����� changed_ustuvannja, ��� ��� �������� �����
                ���� ����������� ��������� �������� �������� ��������. ������� � ��������� ����
                ������� ���� CHANGED_ETAP_ENDED -> CHANGED_ETAP_NONE,
                �� � ����� ����� "�������������" �� ���������, ���� �� ��������� 
                ���� ��������� CHANGED_ETAP_ENDED, ���� ���� ���������� ������
                ����������� ������� ������ ����������� ��������� � ����� ����� � 
                CHANGED_ETAP_NONE, � ���� ���������� �������� ������
                ������ ���� ���� � � ����� ���������, �� ������� �� ����, �� �� � ���� �������
                �������� �������� �������� (�� ���� ������������ ��������) CHANGED_ETAP_ENDED.
                �� � �����, �������� ����� ���� ���� ����� �������� ��������� ������ ���������.
                */
                changed_ustuvannja_tmp = changed_ustuvannja;

                //�������, �� �����, �������, ������� ��������� ���� �������
                changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              }

              if (error == 0)
              {
                error = Set_data(data,add_data, SET_DATA_IMMEDITATE, /*false,*/ type_interface);
                if (error != 0)
                {
                  if (changing_ustuvannja != 0)
                  {
                    /*
                    ���� ����������� ��������� �� ��������, ���� ���������� �������� ��������
                    ����� changed_ustuvannja, ��� ���� �� �� ������������ � ��������
                    CHANGED_ETAP_EXECUTION
                    */
                    changed_ustuvannja = changed_ustuvannja_tmp;
                  }
                }
              }
            }
          }
          else error = ERROR_SLAVE_DEVICE_BUSY;
             
          /*****/
          //���� � ������ ���������� ���, �� ������ ���� ��������, �� ��� �� ���� �������� �� �������� ���
          /*****/
          if ((error == 0) && (add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA))
          {
            //������������ ������ ����-����

            //���������� ����������� �����
            if (check_data_for_data_time_menu() == 1)
            {
              //��� ��������
              //����������� ����������� ������ ���� � RTC
              //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ����������������� � ������� ����������� �������
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
              _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
            }
            else error = ERROR_ILLEGAL_DATA_VALUE;
          }
          /*****/
           
          if(error == 0)
          {
            if  (global_requect == 0)
            {
              for (int index = 0; index < 8; index++) *(transmited_buffer + index ) = *(received_buffer + index );
              *transmited_count = 8;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }
            
            /*****/
            //��� ����������� �������� ���������� � EEPROM
            /*****/
            if (
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )) ||
                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) ||
//                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
//                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
//                ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))) ||
                ((add_data >= M_ADDRESS_CONTROL_BASE                          ) && (add_data <= M_ADDRESS_CONTROL_LAST                         )) ||
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              )) ||
                ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  ))/*||*/
//                (add_data == MA_NUMBER_ITERATION_EL)
               )
            {
              //�������� ���������, ��� ���������� �� ���������
              
              if (
                  ((add_data == MA_PASSWORD_INTERFACE) && (password_changed == true))
                  ||  
                  ( add_data != MA_PASSWORD_INTERFACE) /*������������ ��� ����� ���������� �� ���������� (�� ����������� ������ �������)*/ 
                 )   
              {
                //��������� ��� �������, ���� �������� ������ ������ �������
                   
                //ĳ���� �������� ���� ���������
//                _SET_BIT(active_functions, RANG_SETTINGS_CHANGED);
                restart_timeout_idle_new_settings = true;
                    
                if (
                    ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG   ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG   ))
                   )
                {
                  if  ( !((add_data >= M_ADDRESS_FIRST_USER_REGISTER   ) && (add_data <= M_ADDRESS_LAST_USER_REGISTER)) )
                  {
                    //�� ��� ���������� ������� �����������
                    
                    if (point_to_edited_rang != NULL)
                    {
                      //������ �������� �� �� ������ � �������� ����� ��� �������� ����������
                      //(�� ������� �������� ������ ��������� ����� �������� ������)
                      set_previous_ranguvannja();
                    }
                    
                    //�������� ��������� �� ����������
                    type_of_settings_changed_from_interface |= (1 << RANGUVANNJA_DATA_CHANGED_BIT);
                  }
                  else
                  {
                    //��� ���������� ������� �����������
                    type_of_settings_changed_from_interface |= (1 << USER_REGISTRY_CHANGED_BIT);
                  }
                }
                else
                {
                  if (add_data == MA_PASSWORD_INTERFACE) 
                  {
                    //�������� �������� ������ ������� �������
                    type_of_settings_changed_from_interface |= (1 << NEW_PASSWORD_SET_BIT);
                  }
                  else
                  {
                    //�������� ��������� ���������� (��� ����������)
                    type_of_settings_changed_from_interface |= (1 << SETTINGS_DATA_CHANGED_BIT);
                  }
                }
              }
            }
            else if (
                     ((add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_USTUVANNJA)) ||
                     ( add_data == MA_SET_SERIAL_NUMBER)  
                    )
            {
              if (
                  ((add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_USTUVANNJA))
                 )   
              {
                //�������, �� ������������ �������� ����� ������� ��� ����������� ���������
                changed_ustuvannja = CHANGED_ETAP_ENDED;
              }
              //����� �������� �����������
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
            }
            else if (add_data == MA_DEFAULT_SETTINGS)
            {
                   
              //ĳ���� �������� ���� ���������
//              _SET_BIT(active_functions, RANG_SETTINGS_CHANGED);
              restart_timeout_idle_new_settings = true;
              
              //³������� ������ ������� �������� � �������� ������������
              type_of_settings_changed_from_interface = (1 << DEFAULT_SETTINGS_SET_BIT);
            }
            /*****/
          }
          else 
          {
            if (global_requect == 0)
            {
              Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
              *transmited_count = 5;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }
          }
          break;
        }//ʳ���� ��� ������� ������� 6
      case 15:
        {
          unsigned int add_data, number, reinit_settings = 0;       
        
          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          unsigned int number_bytes = number >> 3;
          if ((number_bytes << 3) != number) number_bytes++;
        
          if ((type_interface != USB_RECUEST) && (type_interface != RS485_RECUEST))
          {
            //���������� ������ ���� �� ���� � �����
            error = ERROR_SLAVE_DEVICE_FAILURE;
          }
          else if ((number < 1) || (number > 0x7B0) || (number_bytes != *(received_buffer + 6)))
              error= ERROR_ILLEGAL_DATA_VALUE;
          else if (
                   ((add_data >= BIT_MA_CONTROL_BASE) && ((add_data + number - 1) <= BIT_MA_CONTROL_LAST))
                   ||
                   ((add_data >= BIT_MA_RESET_GENERAL_AF) && ((add_data + number - 1) <= BIT_MA_RESET_GENERAL_AF))
                   ||
                   ((add_data >= BIT_MA_NEW_SETTINGS_SET) && ((add_data + number - 1) <= BIT_MA_NEW_SETTINGS_SET))
                   ||
                   (
                    ((add_data >= BIT_MA_INPUT_DF1          ) && ((add_data + number - 1) <= BIT_MA_INPUT_DF8             )) || 
                    ((add_data >= BIT_MA_DT1_SET            ) && ((add_data + number - 1) <= BIT_MA_DT4_RESET             ))/* ||
                    ((add_data >= BIT_MA_RESET_LEDS         ) && ((add_data + number - 1) <= BIT_MA_RESET_GENERAL_AF      ))*/
                   ) 
                  )
          {
            unsigned int first_address_of_word_for_function_3_or_4;
            unsigned int offset;

            if((add_data >= BIT_MA_CONTROL_BASE) && (add_data <= BIT_MA_CONTROL_LAST))
            {
              //���� ������� �������
              offset = add_data - BIT_MA_CONTROL_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_CONTROL_BASE;
            }
            else if((add_data >= BIT_MA_INPUT_DF1) && (add_data <= BIT_MA_INPUT_DF8)) /*���������� �������*/
            {
              offset = add_data - BIT_MA_DF_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DF;
            }
            else if((add_data >= BIT_MA_DT1_SET) && (add_data <= BIT_MA_DT4_RESET)) /*�����. ������*/
            {
              offset = add_data - BIT_MA_DT_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_DT;
            }
            else if(
                    /*((add_data >= BIT_MA_RESET_LEDS                       ) && (add_data <= BIT_MA_RESET_GENERAL_AF      ))*/(add_data == BIT_MA_RESET_GENERAL_AF) ||
                    ( add_data == BIT_MA_NEW_SETTINGS_SET                 )
                   )
            {
              //������� �������
              offset = add_data - BIT_MA_COMMAND_BASE;
              first_address_of_word_for_function_3_or_4 = M_ADDRESS_COMMAND_BASE;
            }

            if (
                (first_address_of_word_for_function_3_or_4 >= M_ADDRESS_CONTROL_BASE) &&
                (first_address_of_word_for_function_3_or_4 <= M_ADDRESS_CONTROL_LAST)
               )
            {
              //��� ��������� ������ ����������, ��� ���������� �� ���������
              
              //���������� �� ������ �� �� �������� ����� ��������
              if (
                  (
                   ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                   ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                  )   
                  &&
                  (current_state_menu2.edition == ED_VIEWING)
                 )
              {
                //�������� ������ � ���������

                //������ ���� ������� ���������
//                edition_settings = current_settings_interfaces;

                //��������� ��������� ������ �������/������ ������ �������
                first_address_of_word_for_function_3_or_4 += (offset >> 4);
                //��������� ������� � ���������� ����
                offset &= 0xf;
                
                //������� �������� ���� �����
                unsigned short int temp_value;
                unsigned char temp_value_in_char[2];
                error = Get_data(temp_value_in_char,first_address_of_word_for_function_3_or_4, type_interface);
                temp_value = temp_value_in_char[1];
                temp_value |= temp_value_in_char[0] << 8;

                unsigned int index_byte = 0, index_bit, index_of_bit_in_target_word;
                unsigned char temp_data;
                unsigned int i = 0;
                index_of_bit_in_target_word = offset;//���������� ����� ���
                while ((i < number) && (error == 0))
                {
                  //������� ���� ���������� �� �������� �������������, � �� ������� ��������� ��������, �� � ��� ����� �������� ��-������
                  index_bit  = i &  0x7; //�������� ����� �������� �� ��������� �������� ������ ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ��� � �������� "������" �������
            
                  //����� ���� ������� ����� ���� ����� ��� � 0, �� ������ ���� ��� � ��������
                  if (index_bit == 0)
                  {
                    index_byte = i >> 3  ; //������� �� ��� ������� ������ ��������� �������� ���� ������� ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ����� � �������� "������" �������
                    temp_data = *(received_buffer + 7 + index_byte);
                  }
            
                  //�������� �������� ���, ��� ����� ����������
                  unsigned int value_of_bit;
                  value_of_bit = ((temp_data << (7 - index_bit)) >> 7) & 0x1;
            
                  //� ����, ��� ������� �������� ������� � ���� ��, ���� �� �������
                  //�� ������ ����� ��� ��� �������, �� ����� ������� - ��� ��� ����� �� �������� �� ��������!!!
                  temp_value &= (unsigned short)(~(1 << index_of_bit_in_target_word));

                  //����� ����������� �������� ��
                  temp_value |=  (value_of_bit << index_of_bit_in_target_word);
  
                  //�������� ����� ���
                  i++;
                  //���������� ����� ���������� ���, ���� ����� ������
                  index_of_bit_in_target_word = ((offset + i) & 0xf);//�������� ������ �������� �� ��������� �������� ������ ��� ����� ����� ����� �� 16 - ����� �� ���������� ������ ��� � ��������� ����
            
                  /*
                  � ���, ���� ������ ���������� �������� ��� � ���� ��� ���� �� �������� ������� ��,
                  �� ������� ����� �������� �������� ������������ ����� � ���� � �� ��� ��� ������, �� ������� ���� �����
                  */
                  if ((index_of_bit_in_target_word == 0) || (i == number))
                  {
                    //�������� �������� ���� ��������
                    error = Set_data(temp_value, first_address_of_word_for_function_3_or_4, SET_DATA_INTO_EDIT_TABLE, /*(i < number),*/ type_interface); /*��� � ��� ��������� �� �������, ���� �������� ����������� (i) � (number)*/
                    if (error == 0)
                    {
                      if (reinit_settings == 0) reinit_settings = 1; //�������, �� ����� ���� �������� ����� ����� ��������� � EEPROM

                      //���� � �� ��� ��� ������, �� ������� ���� �����
                      if (i < number)
                      {
                        //�������� ������ ����� � ����� ����� ����������� ����
                        first_address_of_word_for_function_3_or_4++;
  
                        //������� ���� �����
                        error = Get_data(temp_value_in_char,first_address_of_word_for_function_3_or_4, type_interface);
                        temp_value = temp_value_in_char[1];
                        temp_value |= temp_value_in_char[0] << 8;
                      }
                    }
                  }
                }
              }
              else
              {
                if (current_state_menu2.edition != ED_VIEWING) error = ERROR_SLAVE_DEVICE_BUSY;
                else error = ERROR_ILLEGAL_DATA_ADDRESS;
              }
            }
            else if (
                     (
                      (
                       (first_address_of_word_for_function_3_or_4 == M_ADDRESS_DF) || 
                       (first_address_of_word_for_function_3_or_4 == M_ADDRESS_DT)
                      )
                      &&
                      (
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                      ) 
                     )
                     ||  
                     (
                      (first_address_of_word_for_function_3_or_4 == M_ADDRESS_COMMAND_BASE)
                      &&
                      (
                       (!((add_data >= BIT_MA_NEW_SETTINGS_SET) && ((add_data + number - 1) <= BIT_MA_NEW_SETTINGS_SET))) ||
                       ((type_interface == USB_RECUEST  ) && (password_set_USB   == 0)) ||
                       ((type_interface == RS485_RECUEST) && (password_set_RS485 == 0))
                      )   
                     )   
                    )
            {
              //��� ������ ��������� ������ �������������
              
              /*
              ��� �� ������������� ��������� ��������� ������� � ��������� �-������, �� ������� ������� ��������� �� ���������
              ������� � �-������, �� ��������� ������� � ���������
              */
              
              unsigned int index_byte = 0, index_bit, number_activated_function;
              unsigned char temp_data;
              unsigned int i = 0;
              unsigned int activation_function_from_interface_tmp = 0, reset_trigger_functions = 0;
              int set_new_settings = -1;
              while ((i < number) && (error == 0))
              {
                //������� ���� ���������� �� �������� ������������� ��������� ��������, �� � ��� ����� �������� ��-������
                index_bit  = i &  0x7; //�������� ����� �������� �� ��������� �������� ������ ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ��� � �������� "������" �������
            
                //����� ���� ������� ����� ���� ����� ��� � 0, �� ������ ���� ��� � ��������
                if (index_bit == 0)
                {
                  index_byte = i >> 3  ; //������� �� ��� ������� ������ ��������� �������� ���� ������� ��� ����� ����� ����� �� 8 - ����� �� ���������� ������ ����� � �������� "������" �������
                  temp_data = *(received_buffer + 7 + index_byte);
                }
            
                //�������� �������� ���, ��� ����� ����������
                unsigned int value_of_bit;
                value_of_bit = ((temp_data << (7 - index_bit)) >> 7) & 0x1;
                
                number_activated_function = add_data + i;
                if (value_of_bit != 0)
                {
                  /*     if  (number_activated_function == BIT_MA_RESET_LEDS                       )
                    activation_function_from_interface_tmp |= 1 << RANG_TU_RESET_LEDS;
                  else if  (number_activated_function == BIT_MA_RESET_RELES                      )
                    activation_function_from_interface_tmp |= 1 << RANG_TU_RESET_RELES;
                  else*/ if  (number_activated_function == BIT_MA_RESET_GENERAL_AF                 ) 
                  {
                    //�������� ��������� ������� 
                    reset_trigger_functions = 0xff; /*��������� �������� ������, �� ����� ������� ������� �������*/
                  }
                  else if  (number_activated_function == BIT_MA_NEW_SETTINGS_SET) 
                  {
                    /*������� ��������� �������� ��� � ������������ ������� ����� ���������*/ 
                    set_new_settings = true;
                  }
                  else 
                  {
                    //���������� ���� �������� ����� �� ����� �����
                    error = ERROR_ILLEGAL_DATA_ADDRESS;
                  }
                }
                else
                {
                  if  (number_activated_function == BIT_MA_NEW_SETTINGS_SET) 
                  {
                    /*������� ����������� �������� ��� � ������������ ������� ����� ���������*/ 
                    set_new_settings = false;
                  }
                }
                
                i++;
              }

              if (error == 0)
              {
                if (activation_function_from_interface_tmp != 0)
                {
                  activation_function_from_interface |= activation_function_from_interface_tmp;
                }
                if (reset_trigger_functions != 0)
                {
                  reset_trigger_function_from_interface |= (1 << type_interface);
                }
                if (set_new_settings != -1)
                {
                  if (set_new_settings == true)
                  {
                    //��������� ��������� ���
                    unsigned int source = MENU_PARAMS_FIX_CHANGES;
                    if(type_interface == USB_RECUEST) source = USB_PARAMS_FIX_CHANGES;
                    else if(type_interface ==  RS485_RECUEST) source = RS485_PARAMS_FIX_CHANGES;

                    unsigned int result = set_config_and_settings(1, source);
                    if (result != 0)
                    {
                      error = ERROR_SLAVE_DEVICE_FAILURE;
                      if (result == 2)
                      {
                        //����������� ��� �������� �������
                        current_state_menu2.edition = ED_ERROR;
                      }
                    }
                  }
                  else
                  {
                    //³���� ��������� ���
                    unsigned int result = set_config_and_settings(0, NO_MATTER_PARAMS_FIX_CHANGES);
                    if (result != 0)
                    {
                      //����������� ��� �������� �������
                      current_state_menu2.edition = ED_ERROR;
                    }
                  }
                  config_settings_modified = 0;
                  type_of_settings_changed_from_interface = 0;
//                  _CLEAR_BIT(active_functions, RANG_SETTINGS_CHANGED);
                }
              }
            }
            else
            {
              //���������� ���� �������� ����� �� ����� �����
              error = ERROR_ILLEGAL_DATA_ADDRESS;
            }
          }
          else
            error = ERROR_ILLEGAL_DATA_ADDRESS;

          if (error == 0)
          {
            CRC_sum = 0xffff;
            for (int index = 0; index < 6; index++)
            {
              *(transmited_buffer + index ) = *(received_buffer + index );
              CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
            }
            *(transmited_buffer + 6) = CRC_sum & 0xff;
            *(transmited_buffer + 7) = CRC_sum >> 8;

            *transmited_count = 8;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          
            if (reinit_settings != 0)
            {
              //������� ������ ���� � ������ ���������
//              current_settings_interfaces = edition_settings;

              //³������� ���� ���������
//              _SET_BIT(active_functions, RANG_SETTINGS_CHANGED);
              restart_timeout_idle_new_settings = true;
              type_of_settings_changed_from_interface |= (1 << SETTINGS_DATA_CHANGED_BIT);
            }
          }
          else
          {
            //³�������� ��� �������
            Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
            *transmited_count = 5;
            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
          }
          break;
        }//ʳ���� ��� ������� ������� 15        
      case 16:
        {
          unsigned int add_data, number;
          unsigned int reinit_ustuvannja = 0, reinit_settings = 0, set_new_password = 0, reinit_ranguvannja = 0, set_min_param = 0;
          unsigned int reinit_user_register = 0;
          unsigned int setting_new_rtc = 0;
            
          add_data = (*(received_buffer + 2))<<8 | (*(received_buffer + 3));
          number   = (*(received_buffer + 4))<<8 | (*(received_buffer + 5));

          //������ ������������/�������������� ������ �������
          unsigned int before_password_set;
          if (type_interface == USB_RECUEST) before_password_set = password_set_USB;
          else if (type_interface == RS485_RECUEST) before_password_set = password_set_RS485;
          else error= ERROR_SLAVE_DEVICE_FAILURE;

          if ((number < 1) || (number > 0x7B) || ((*(received_buffer + 6)) != ( number <<1)))
            error= ERROR_ILLEGAL_DATA_VALUE;
          else if (
                   (global_requect != 0) && /*����� �� ����� BROADCAST_ADDRESS_MODBUS_RTU ��������� Modbus-RTU*/
                   (
                    !(
                      ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && ((add_data + number - 1) <= M_ADDRESS_LAST_TIME_AND_DATA))
                     )
                   )     
                  )
          {
            /*
            �� �������� ����� ����� �������� ����� ��� � ����
            */
            error = ERROR_BROADCAST_ADDRESS;
          }

          //�������� ������� ������� ���
          unsigned int i = 0;
          while((i < number) && (error == 0 ))
          {
            unsigned short int data = (*(received_buffer+7+2*i))<<8 | (*(received_buffer+8+2*i));

            if (
                (current_state_menu2.edition == ED_VIEWING                     ) ||
                (add_data                    == MA_CURRENT_NUMBER_RECORD_PR_ERR)  
               )
            {
              /*****/
              //�������� �� ����������� ������ ������� ��� ������
              /*****/
              if (
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )) || /*������� � ��������*/
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) || /*������� � �������� ����� �����*/
//                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) || /*������� � �������� ����� �����*/
//                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) || /*������� � �������� ������ �����*/
//                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))) || /*������� � �������� �������� �����*/
                  ((add_data >= M_ADDRESS_CONTROL_BASE                          ) && (add_data <= M_ADDRESS_CONTROL_LAST                         )) || /*������������ �������*/
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              )) || /*������� � �������� (�����������) ��� ������ �������*/
                  ((add_data >= M_ADDRESS_FIRST_TIME_AND_DATA                   ) && (add_data <= M_ADDRESS_LAST_TIME_AND_DATA                   )) || /*���*/
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  )) || /*����������*/
                   (add_data == MA_CLEAR_NUMBER_RECORD_PR_ERR                   )                                                                   || /*�������� ���������� ���������� ����*/
                   (add_data == MA_DEFAULT_SETTINGS                             )                                                                   || /*������������ �������� ������������*/        
                   (add_data == MA_TEST_WATCHDOGS                               )                                                                 /*||*/ /*���������� ����������� � ���������� watchdog*/        
//                   (add_data == MA_NUMBER_ITERATION_EL                          )                                                                      /*����������������������� ������� ����������� ��������� �����*/        
                 )
              {
                if (
                    (add_data != MA_PASSWORD_INTERFACE) &&
                    (
                     ((type_interface == USB_RECUEST  ) && (password_set_USB != 0  )) ||
                     ((type_interface == RS485_RECUEST) && (password_set_RS485 != 0))
                    )   
                   )
                {
                  //�� ����� ����� �������� ��� ������, �� ����� �������� ����� ������ �������
                  error = ERROR_ILLEGAL_DATA_ADDRESS;
                }
                else if (
                         (number != 1)
                         &&
                         (  
                          (add_data == MA_CLEAR_NUMBER_RECORD_PR_ERR) || /*�������� ���������� ���������� ����*/
                          (add_data == MA_DEFAULT_SETTINGS          ) || /*������������ �������� ������������*/        
                          (add_data == MA_TEST_WATCHDOGS            )    /*���������� ����������� � ���������� watchdog*/        
                         )   
                        )
                {
                  //ֳ ������� ������ ���������� �������� ����� �� ���� ������ - ������ ����������� ��� �������
                  error = ERROR_ILLEGAL_DATA_ADDRESS;
                }
                else
                {
                  //����� ���������� ��� ��� ��� ���������
                
                  //���� � ���� ���������� �� ������ ��� ������ ���� �������� �� ��������� (��� ����) �� ������ ���� ��������� ���������
                  if (
                      (
                       (reinit_settings      == 0) && 
                       (reinit_ranguvannja   == 0) &&
                       (reinit_user_register == 0)
                      )/*�� �� ���������� ����� ����������, ���� �� �� �������� ���� ������� ���������*/ 
                      &&  
                      ( 
                       !(
                         (add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) && 
                         (add_data <= M_ADDRESS_LAST_TIME_AND_DATA ) 
                        )/*���� ������� ��������� �� ����� ������ ���� �� ������������ ���*/
                      )    
                     )
                  {
                    //������ ���� ������� ���������
//                    edition_settings  = current_settings_interfaces;

                    //���������� ��� ����, �� ���� ����� ���������� ����������, �� ������� �������� �� ��������� ���� � 0
                    point_to_edited_rang = NULL;
//                    for (unsigned int j = 0; j < N_BIG; j++)
//                    {
//                      clear_array_rang[j] = 0;
//                      set_array_rang[j]   = 0;
//                    }
                  }

                  if (
                      (add_data >= M_ADDRESS_FIRST_TIME_AND_DATA) &&
                      (add_data <= M_ADDRESS_LAST_TIME_AND_DATA ) &&
                      (setting_new_rtc == 0                     )
                     )
                  {
                    if (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT) == 0)
                    {  
                      //�������, �� ����� ������ ����� ��������� ���
                      setting_new_rtc = 1;

                      //������ ���� ����, ���� � ��������� �� ��� �� ��������� ����, ��������� �� �� ����������� � ����, ���� ������� ������ �����, �� �������� �� � ��������� RTC
                      unsigned char *label_to_time_array, *label_calibration;
                      if (copying_time == 0)
                      {
                        label_to_time_array = time;
                        label_calibration = &calibration;
                      }
                      else
                      {
                        label_to_time_array = time_copy;
                        label_calibration = &calibration_copy;
                      }
                      for(unsigned int index = 0; index < 7; index++) time_edit[index] = *(label_to_time_array + index);
                      calibration_edit = *label_calibration;
                    }
                    else
                    {
                      /*
                      �� ���������� ��������� ������� ������ ����, � ���� ���� ������ 
                      ���������� ������ ��� ��� �������� �������� ���� (��� ���� ������� ����� ����)
                      ���� �� �������� � ��������� �����������
                      */
                      error = ERROR_SLAVE_DEVICE_BUSY;
                    }
                  }
                
                  if (error == 0)
                  {
                    //������� ��� �������� ����� ��������� ���������
                    error = Set_data(data, add_data, SET_DATA_INTO_EDIT_TABLE, /*((i + 1) < number),*/ type_interface); /*��� � �� �� ��������� �� �������, ���� �������� �����������(i + 1) � (number)*/
                  }
                }
              }
              else
              {
                //ֳ ��� �� ���������� �������� �� ������
              
                if (
                    (add_data >= MA_ADDRESS_FIRST_USTUVANNJA) && (add_data <= MA_ADDRESS_LAST_USTUVANNJA) || /*������� �������� � ����� �����������*/
                    (add_data == MA_SET_SERIAL_NUMBER                                                       )    /*������� �����*/  
                   )
                {
                  //��������� ��� ��� ��� ��������� ��� ������� �����
              
                  //���� � ���� ���������� �� ������ ��� ������ ���� �������� �� ��������� �� ������ ���� ������ ���������
                  if (reinit_ustuvannja == 0)
                  {
                    for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
                    {
                      edit_ustuvannja[k] = ustuvannja[k];
                    }
                    edit_serial_number_dev = serial_number_dev;
                  }
                }
                //������� ��� �������� ����� ���������� ����� (��� �������� �� ��������������� ����� ��� ���������, � ��� ��� ����� ������� ��� ���� ���� ������ ��������� ��������� �������)
                error = Set_data(data, add_data, SET_DATA_INTO_EDIT_TABLE, /*((i + 1) < number),*/ type_interface); /*��� � �� �� ��������� �� �������, ���� �������� �����������(i + 1) � (number)*/
              }
            }
            else error = ERROR_SLAVE_DEVICE_BUSY;
              
            if (error == 0)
            {
              if (
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_PART1                 ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_PART1                 )) ||
                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G1)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G1))) ||
//                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G2)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G2))) ||
//                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G3)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G3))) ||
//                  ((add_data >= (M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV + SHIFT_G4)) && (add_data <= (M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV + SHIFT_G4))) ||
                  ((add_data >= M_ADDRESS_CONTROL_BASE                          ) && (add_data <= M_ADDRESS_CONTROL_LAST                         )) ||  
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_CONTINUE              ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_CONTINUE              )) ||
                  ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG                  ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG                  ))/* ||*/
//                  (add_data == MA_NUMBER_ITERATION_EL)
                 )
              {
                //�������� ���������, ��� ���������� �� ���������
                
                if (
                    ((add_data == MA_PASSWORD_INTERFACE) && (password_changed == true))
                    ||  
                    ( add_data != MA_PASSWORD_INTERFACE) /*������������ ��� ����� ���������� �� ���������� (�� ����������� ������ �������)*/ 
                   )   
                {
                  //��������� ��� �������, ���� �������� ������ ������ �������
                  //�������� ���������
                  if (
                      ((add_data >= M_ADDRESS_FIRST_SETPOINTS_RANG   ) && (add_data <= M_ADDRESS_LAST_SETPOINTS_RANG   ))
                     )
                  {
                    if  ( !((add_data >= M_ADDRESS_FIRST_USER_REGISTER) && (add_data <= M_ADDRESS_LAST_USER_REGISTER)) )
                    {
                      //�� ��� ���������� ������� �����������
                      
                      //�������, �� ����� �������� ��������� �� ����������
                      reinit_ranguvannja = 1;
                    }
                    else
                    {
                      //��� ���������� ������� �����������
                      reinit_user_register = 1;
                    }
                  }
                  else
                  {
                    //�������, �� ����� �������� ��������� �� ���������� (��� ����������)
                    if (add_data == MA_PASSWORD_INTERFACE)
                    {
                      set_new_password = 1;
                    }
                    else
                    {
                      reinit_settings = 1;
                    }
                  }
                }
              }
              else if (
                       ((add_data >= MA_ADDRESS_FIRST_USTUVANNJA ) && (add_data <= MA_ADDRESS_LAST_USTUVANNJA)) ||
                       ( add_data == MA_SET_SERIAL_NUMBER)  
                      )
              {
                //�������, �� ����� �������� ������� �����������
                reinit_ustuvannja = 1;
              }
              else if (add_data == MA_DEFAULT_SETTINGS)
              {
                //�������� � �������� ������������
                set_min_param = 1;
              }
            }
            add_data++;
            i++;
          } 

          /*****/
          //���� ���� ������ ���������� ���-����, �� �������� ����� � ��������� RTC, �� ��� �� ���� �������� �� �������� ���
          /*****/
          if ((error == 0) && (setting_new_rtc != 0))
          {
            //������������ ������ ����-����

            //���������� ����������� �����
            if (check_data_for_data_time_menu() == 1)
            {
              //��� ��������
              //����������� ����������� ������ ���� � RTC
              //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ����������������� � ������� ����������� �������
              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
              _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
            }
            else error = ERROR_ILLEGAL_DATA_VALUE;
          }
          /*****/

          /*****/
          if ((error == 0) && (reinit_ranguvannja != 0))
          {
            //���������� �� ������ ���� ��� ������ � �������� �����
            if(point_to_edited_rang != NULL)
            {
              //������ �������� �� �� ������ � �������� ����� ��� �������� ����������
              //(�� ������� �������� ������ ��������� ����� �������� ������)
              set_previous_ranguvannja();
            }
          }
          /*****/
          
          if (error == 0)
          {
            if  (global_requect == 0)
            {
              CRC_sum = 0xffff;
              for (int index = 0; index < 6; index++)
              {
                *(transmited_buffer + index ) = *(received_buffer + index );
                CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
              }
              *(transmited_buffer +6 ) = CRC_sum & 0xff;
              *(transmited_buffer +7 ) = CRC_sum >> 8;

              *transmited_count = 8;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }

            /*****/
            //��� ����������� �������� ���������� � EEPROM
            /*****/
            if (reinit_ustuvannja != 0)
            {
              //���������� ������� ��� �������� � ��
              //�������, �� �������� ������ ��������� ����� ������ �����
              changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
              {
                ustuvannja[k] = edit_ustuvannja[k];
              }
              //�������, �� �������� ������ ��������� ����� � ����� ��� ����������� � ����������� �������
              changed_ustuvannja = CHANGED_ETAP_ENDED;
              serial_number_dev = edit_serial_number_dev;

              _SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
            }
            if (
                (reinit_settings      != 0) ||
                (set_new_password     != 0) ||  
                (reinit_ranguvannja   != 0) ||
                (set_min_param        != 0) ||
                (reinit_user_register != 0)  
               )
            {
              //������� ������ ���� � ������ ���������
//              current_settings_interfaces = edition_settings;

              //³������� ���� ���������
//              _SET_BIT(active_functions, RANG_SETTINGS_CHANGED);
              restart_timeout_idle_new_settings = true;
              
              if (set_min_param != 0)
              {
                type_of_settings_changed_from_interface = (1 << DEFAULT_SETTINGS_SET_BIT);
              }
              
              if (reinit_settings != 0)
              {
                type_of_settings_changed_from_interface |= (1 << SETTINGS_DATA_CHANGED_BIT);
              }

              if (set_new_password != 0)
              {
                type_of_settings_changed_from_interface |= (1 << NEW_PASSWORD_SET_BIT);
              }

              if (reinit_ranguvannja != 0)
              {
                type_of_settings_changed_from_interface |= (1 << RANGUVANNJA_DATA_CHANGED_BIT);
              }

              if (reinit_user_register != 0)
              {
                type_of_settings_changed_from_interface |= (1 << USER_REGISTRY_CHANGED_BIT);
              }
            }
            /*****/
          }
          else 
          {
            //������������ ��������� ���� ������� �� ������
            if (type_interface == USB_RECUEST) password_set_USB = before_password_set;
            else if (type_interface == RS485_RECUEST) password_set_RS485 = before_password_set;

            if  (global_requect == 0)
            {
              Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
              *transmited_count = 5;
              if(type_interface == USB_RECUEST) data_usb_transmiting = true;
              else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
            }
            else
            {
              if(type_interface == RS485_RECUEST)
              {
                //������������� ��������� �� RS-485
                restart_monitoring_RS485();
              }
            }
          }

          break;
        }//ʳ���� ��� ������� ������� 16
//      case 20:
//        {
//          *transmited_buffer = *(received_buffer);
//          *(transmited_buffer + 1) = *(received_buffer + 1) ;
//
//          unsigned int number_requests = *(received_buffer + 2);
//          unsigned int total_number_answer = 0;
//
//          if ((number_requests >= 0x7) && (number_requests <= 0xF5))
//          {
//            unsigned int i = 0; 
//            while ((i < number_requests) && ((error = Get_data_file((received_buffer + 3 + i), (transmited_buffer + 3 + total_number_answer), &total_number_answer, type_interface)) == 0))
//            {
//              i += 7;
//            }
//         
//          }
//          else error = ERROR_ILLEGAL_DATA_VALUE;
//        
//          if (error == 0)
//          {
//            *(transmited_buffer + 2) = total_number_answer ;
//
//            CRC_sum = 0xffff;
//            for (int index = 0; index < ((int)(total_number_answer + 3)); index++) CRC_sum = AddCRC(*(transmited_buffer + index),CRC_sum);
//            *(transmited_buffer+3+total_number_answer) = CRC_sum & 0xff;
//            *(transmited_buffer+4+total_number_answer) = CRC_sum >> 8;
//            
//            *transmited_count = 5+total_number_answer;
//            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
//            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
//          }
//          else
//          {
//            
//            Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), error, transmited_buffer);
//            *transmited_count = 5;
//            if(type_interface == USB_RECUEST) data_usb_transmiting = true;
//            else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
//          }
//
//          break;
//        }//ʳ���� ��� ������� ������� 20        
      default:
        {
          Error_modbus((unsigned char)settings_fix.address, *(received_buffer+1), ERROR_ILLEGAL_FUNCTION, transmited_buffer);
          *transmited_count = 5;
          if(type_interface == USB_RECUEST) data_usb_transmiting = true;
          else if(type_interface ==  RS485_RECUEST) start_transmint_data_via_RS_485(*transmited_count);
        }
      }
    }
    else
    {
      if(type_interface == RS485_RECUEST)
      {
        //������������� ��������� �� RS-485
        restart_monitoring_RS485();
      }
    }
  }
  else
  {
    if(type_interface == RS485_RECUEST)
    {
      //������������� ��������� �� RS-485
      restart_monitoring_RS485();
    }
  }
  *received_count = 0;
}
/***********************************************************************************/
