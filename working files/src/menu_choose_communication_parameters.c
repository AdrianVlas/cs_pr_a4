#include "header.h"

/*****************************************************/
//������� ����� ����������� ��������� ������������ ����������
/*****************************************************/
void make_ekran_choose_communication_parameters(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_CHCP_M2][MAX_COL_LCD + 1] = 
  {
    {
      " ��� ������     ",
      " ����� ������   ",
      " �����.RS-485   "
    },
    {
      " ��'� ������   ",
      " ������ ������ ",
      " ������.RS-485  "
    },
    {
      " Bay name       ",
      " Bay Address    ",
      " RS-485 Settings"
    },
    {
      " ��� ������     ",
      " ����� ������   ",
      " �����.RS-485   "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);

  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) 
    {
      working_ekran[i][j] = (index_in_ekran < MAX_ROW_CHCP_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
    }
    index_in_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_state_menu2.cursor_on = 1;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ���� ������
/*****************************************************/
void make_ekran_name_of_cell(void)
{
  //������� ����� ���� ������  ��� ������� ��� ��� ���� ���� ��������
  index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    uint8_t *p_name_of_cell;
    p_name_of_cell = (current_state_menu2.edition == ED_VIEWING) ? settings_fix_prt.name_of_cell : settings_fix.name_of_cell;
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j<MAX_COL_LCD; j++)
    {
       uint8_t symbol = (((index_in_ekran << POWER_MAX_COL_LCD) + j) < MAX_CHAR_IN_NAME_OF_CELL) ? p_name_of_cell[(index_in_ekran << POWER_MAX_COL_LCD) + j] : ' ';
       working_ekran[i][j] = (symbol >= 0x20) ? symbol : ' ';
    }

    index_in_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������  �� �������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ������ ��� ���������� � ������ �����
/*****************************************************/
void make_ekran_address(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "���.�� ���������",
      "���.�� ���������",
      "Ed.isn't allowed",
      "���.�� ���������",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_ADDRESS_M2][MAX_COL_LCD + 1] = 
    {
      "     �����      ",
      "     ������     ",
      "    Address     ",
      "     �����      "
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    uint32_t *p_address;
    if (current_state_menu2.edition == ED_VIEWING) p_address = &settings_fix_prt.address;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_address = &settings_fix.address;
    else p_address = &settings_fix_edit.address;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_ADDRESS_M2)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];

          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
          vaga = 100; //������������ ������� ����������
          value = *p_address;
        }
        else
        {
          //� ������� ����� ����� �������� �������� �������
          for (size_t j = 0; j < MAX_COL_LCD; j++)
          {
            if ((j < COL_ADDRESS_BEGIN) ||  (j > COL_ADDRESS_END ))working_ekran[i][j] = ' ';
            else
              calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol);
          }
        }
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      current_state_menu2.position_cursor_x = COL_ADDRESS_BEGIN;
      last_position_cursor_x = COL_ADDRESS_END;

      //ϳ������� ������ �� ������� �������
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))
            )
      {
        current_state_menu2.position_cursor_x++;
      }

      //������ ������� ���, ��� �� ��� ����� ������
      if (
          ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
          (current_state_menu2.position_cursor_x > 0)
         )
      {
        current_state_menu2.position_cursor_x--;
      }
    }
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� ������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_address(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      current_state_menu2.position_cursor_x = COL_ADDRESS_BEGIN;
      break;
    }
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      uint32_t *p_value_edit = &settings_fix_edit.address;
      uint32_t *p_value_cont = &settings_fix.address;

      if (*p_value_cont != *p_value_edit) 
      {
        if (check_data_setpoint(*p_value_edit, KOEF_ADDRESS_MIN, KOEF_ADDRESS_MAX) == 1)
        {
          *p_value_cont = *p_value_edit;
              
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� �������� ����������� �����
*/
/*****************************************************/
void press_esc_in_address(void)
{
  uint32_t *p_value_edit = &settings_fix_edit.address;
  uint32_t *p_value_cont = &settings_fix.address;

  *p_value_edit = *p_value_cont;
}
/*****************************************************/

/*****************************************************/
//���� ����������� ������� ����������� �����
/*****************************************************
����� ���������
(1 << BIT_KEY_DOWN) - �������� ������ ����
(1 << BIT_KEY_UP)   - �������� ������ �����
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_address(unsigned int action)
{
  //������� ����� � �������� ����
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    settings_fix_edit.address = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), settings_fix_edit.address, 0, 0, COL_ADDRESS_END, 1);
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < COL_ADDRESS_BEGIN) ||
          (current_state_menu2.position_cursor_x > COL_ADDRESS_END))
        current_state_menu2.position_cursor_x = COL_ADDRESS_END;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
      if ((current_state_menu2.position_cursor_x < COL_ADDRESS_BEGIN) ||
          (current_state_menu2.position_cursor_x > COL_ADDRESS_END))
        current_state_menu2.position_cursor_x = COL_ADDRESS_BEGIN;
    }
    
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��������� ������������ ����������
/*****************************************************/
void make_ekran_choose_setting_RS485(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_SETTING_RS485_M2][MAX_COL_LCD + 1] = 
  {
    {
      " �������� ������",
      " �����.�������� ",
      " �����.����-��� ",
      " ����� �����   "
    },
    {
      " �������� ���. ",
      " �����.������� ",
      "ʳ���.����-��  ",
      "ʳ���� ���������"
    },
    {
      " Baud rate      ",
      " Parity         ",
      " Stop Bits      ",
      "End of Reception"
    },
    {
      " �������� ������",
      " �����.�������� ",
      " �����.����-��� ",
      " ����� �����   "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) 
    {
      working_ekran[i][j] = (index_in_ekran < MAX_ROW_SETTING_RS485_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
    }
    index_in_ekran++;
  }

  //������ �� ���������� ������������ �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� ��������
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //������ �������
  current_state_menu2.cursor_on = 1;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ������������� ��� ����������
/*****************************************************/
void make_ekran_baud_RS485(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "���.�� ���������",
      "���.�� ���������",
      "Ed.isn't allowed",
      "���.�� ���������",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_BAUD_RS485][MAX_COL_LCD + 1] = 
    {
      " �������� ������",
      " �������� ���. ",
      "   Baud rate    ",
      " �������� ������"
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    uint32_t value;
    if (current_state_menu2.edition == ED_VIEWING) value = settings_fix_prt.baud_RS485;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) value = settings_fix.baud_RS485;
    else value = settings_fix_edit.baud_RS485;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_FOR_VIEW_BAUD_RS485)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          //� ������� ����� ����� �������� �������� �������
          if (value < MAX_NUMBER_BAUD_RS485)
          {
            const uint8_t information[MAX_NUMBER_BAUD_RS485][MAX_COL_LCD + 1] = 
            {
              "      9600      ",
              "     14400      ",
              "     19200      ",
              "     28800      ",
              "     38400      ",
              "     57600      ",
              "     115200     "
            };
            const unsigned int cursor_x[MAX_NUMBER_BAUD_RS485] = {5, 4, 4, 4, 4, 4, 4};

            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[value][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[value];
            }
          }
          else
          {
            const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
            {
              "     ������     ",
              "    �������     ",
              "     Error      ",
              "     ������     "
            };
            const unsigned int cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_error[index_language];
            }
          }
        }
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
    //�������� ������� ���� �����
  }
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� ����������� ��������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_baud_RS485(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_value_edit = &settings_fix_edit.baud_RS485;
      int32_t *p_value_cont = &settings_fix.baud_RS485;
      if (*p_value_cont != *p_value_edit) 
      {
        if (check_data_setpoint(*p_value_edit, VALUE_BAUD_RS485_MIN, VALUE_BAUD_RS485_MAX) == 1)
        {
          *p_value_cont = *p_value_edit;
          
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� ����������� ��������
*/
/*****************************************************/
void press_esc_in_baud_RS485(void)
{
  settings_fix_edit.baud_RS485 = settings_fix.baud_RS485; 
}
/*****************************************************/

/*****************************************************/
//���� ����������� ��������
/*****************************************************
����� ���������
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_baud_RS485(unsigned int action)
{
  //������� ����� � �������� ����
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int32_t value = settings_fix_edit.baud_RS485;
    if ((action & (1 << BIT_KEY_RIGHT)) != 0) 
    {
      if ((++value) > VALUE_BAUD_RS485_MAX)
        value = VALUE_BAUD_RS485_MIN;
    }
    else 
    {
      if ((--value) < VALUE_BAUD_RS485_MIN)
        value = VALUE_BAUD_RS485_MAX;
    }
    settings_fix_edit.baud_RS485 = value;
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� �������� ������� ��� ����������
/*****************************************************/
void make_ekran_pare_RS485()
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "���.�� ���������",
      "���.�� ���������",
      "Ed.isn't allowed",
      "���.�� ���������",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_PARE_RS485][MAX_COL_LCD + 1] = 
    {
      " �����.�������� ",
      " �����.������� ",
      "     Parity     ",
      " �����.�������� "
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    uint32_t value;
    if (current_state_menu2.edition == ED_VIEWING) value = settings_fix_prt.pare_bit_RS485;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) value = settings_fix.pare_bit_RS485;
    else value = settings_fix_edit.pare_bit_RS485;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_FOR_VIEW_PARE_RS485)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          if (value < MAX_NUMBER_PARE_RS485)
          {
            const uint8_t information[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485][MAX_COL_LCD + 1] = 
            {
              {"      ���       ", "     �����.     ", "      ���.      "},
              {"      ����      ", "    ������.     ", "      ����.     "},
              {"      None      ", "      Odd       ", "      Even      "},
              {"      ���       ", "     �����.     ", "      ���.      "}
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][MAX_NUMBER_PARE_RS485 + 1] = 
            {
              {5, 4, 5, 4},
              {5, 3, 5, 3},
              {5, 5, 5, 4},
              {5, 4, 5, 4}
            };

            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][value][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][value];
            }
          }
          else
          {
            const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
            {
              "     ������     ",
              "    �������     ",
              "     Error      ",
              "     ������     "
            };
            const unsigned int cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_error[index_language];
            }
          }
        }
      }
      else
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� �������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_pare_RS485(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_value_edit = &settings_fix_edit.pare_bit_RS485;
      int32_t *p_value_cont = &settings_fix.pare_bit_RS485;
      if (*p_value_cont != *p_value_edit) 
      {
        if (check_data_setpoint(*p_value_edit, VALUE_PARE_RS485_MIN, VALUE_PARE_RS485_MAX) == 1)
        {
          *p_value_cont = *p_value_edit;
          
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� ����������� �������
*/
/*****************************************************/
void press_esc_in_pare_RS485(void)
{
  settings_fix_edit.pare_bit_RS485 = settings_fix.pare_bit_RS485; 
}
/*****************************************************/

/*****************************************************/
//���� ����������� �������
/*****************************************************
����� ���������
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_pare_RS485(unsigned int action)
{
  //������� ����� � �������� ����
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int32_t value = settings_fix_edit.pare_bit_RS485;
    if ((action & (1 << BIT_KEY_RIGHT)) != 0) 
    {
      if ((++value) > VALUE_PARE_RS485_MAX)
        value = VALUE_PARE_RS485_MIN;
    }
    else 
    {
      if ((--value) < VALUE_PARE_RS485_MIN)
        value = VALUE_PARE_RS485_MAX;
    }
    settings_fix_edit.pare_bit_RS485 = value;
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� stop-bit ��� ����������
/*****************************************************/
void make_ekran_stopbits_RS485()
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "���.�� ���������",
      "���.�� ���������",
      "Ed.isn't allowed",
      "���.�� ���������",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_STOP_BITS_RS485][MAX_COL_LCD + 1] = 
    {
      " �����.����-��� ",
      "ʳ���.����-��  ",
      "   Stop Bits    ",
      " �����.����-��� "
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    uint32_t value;
    if (current_state_menu2.edition == ED_VIEWING) value = settings_fix_prt.number_stop_bit_RS485;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) value = settings_fix.number_stop_bit_RS485;
    else value = settings_fix_edit.number_stop_bit_RS485;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_FOR_VIEW_STOP_BITS_RS485)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          if (value < MAX_NUMBER_STOP_BITS_RS485)
          {
            const unsigned char information[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485][MAX_COL_LCD + 1] = 
            {
              {"      ����      ", "      ���       "},
              {"      ����      ", "      ���       "},
              {"      One       ", "      Two       "},
              {"      ����      ", "      ���       "}
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][MAX_NUMBER_STOP_BITS_RS485] = 
            {
              {5, 5},
              {5, 5},
              {5, 5},
              {5, 5}
            };

            for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][value][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][value];
            }
          }
          else
          {
            const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
            {
              "     ������     ",
              "    �������     ",
              "     Error      ",
              "     ������     "
            };
            const unsigned int cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x_error[index_language];
            }
          }
        }
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }

  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� ����-���
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_stopbits_RS485(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_value_edit = &settings_fix_edit.number_stop_bit_RS485;
      int32_t *p_value_cont = &settings_fix.number_stop_bit_RS485;
      if (*p_value_cont != *p_value_edit) 
      {
        if (check_data_setpoint(*p_value_edit, VALUE_STOP_BITS_RS485_MIN, VALUE_STOP_BITS_RS485_MAX) == 1)
        {
          *p_value_cont = *p_value_edit;
          
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� ����������� ����-���
*/
/*****************************************************/
void press_esc_in_stopbits_RS485(void)
{
  settings_fix_edit.number_stop_bit_RS485 = settings_fix.number_stop_bit_RS485; 
}
/*****************************************************/

/*****************************************************/
//���� ����������� ����-���
/*****************************************************
����� ���������
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_stopbits_RS485(unsigned int action)
{
  //������� ����� � �������� ����
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int32_t value = settings_fix_edit.number_stop_bit_RS485;
    if ((action & (1 << BIT_KEY_RIGHT)) != 0) 
    {
      if ((++value) > VALUE_STOP_BITS_RS485_MAX)
        value = VALUE_STOP_BITS_RS485_MIN;
    }
    else 
    {
      if ((--value) < VALUE_STOP_BITS_RS485_MIN)
        value = VALUE_STOP_BITS_RS485_MAX;
    }
    settings_fix_edit.number_stop_bit_RS485 = value;
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� time-out ���������� ������� ��� ����������
/*****************************************************/
void make_ekran_timeout_RS485(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "���.�� ���������",
      "���.�� ���������",
      "Ed.isn't allowed",
      "���.�� ���������",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " ���.�� ��������",
      " ���.�� �������",
      "  Out of Limits ",
      "���.�� �������� "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_TIMEOUT_RS485][MAX_COL_LCD + 1] = 
    {
      "  ����� �����  ",
      "ʳ���� ���������",
      "End of Reception",
      "  ����� �����  "
    };
    const uint8_t symbols[MAX_NAMBER_LANGUAGE][5 + 1] = {"����.", "����.", "symb.", "����."};
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
    if (current_state_menu2.edition == ED_VIEWING) value = settings_fix_prt.time_out_1_RS485;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) value = settings_fix.time_out_1_RS485;
    else value = settings_fix_edit.time_out_1_RS485;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_FOR_VIEW_TIMEOUT_RS485)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];

          first_symbol = 0; //�������, �� �� ����� �������� ������ �� ���������
          vaga = 100; //������������ ������� ���������� ��� �������� �������� �������
        }
        else
        {
          //� ������� ����� ����� �������� �������� �������
          for (size_t j = 0; j<MAX_COL_LCD; j++)
          {
            if (
                ((j < COL_TIMEOUT_RS485_BEGIN) ||  (j > COL_TIMEOUT_RS485_END )) &&
                (
                 !((j >= (COL_TIMEOUT_RS485_END + 2)) && (j <= (COL_TIMEOUT_RS485_END + 6)))
                )    
               )working_ekran[i][j] = ' ';
            else if (j == COL_TIMEOUT_RS485_COMMA )working_ekran[i][j] = ',';
            else if ((j >= (COL_TIMEOUT_RS485_END + 2)) && (j <= (COL_TIMEOUT_RS485_END + 6)))
              working_ekran[i][j] = symbols[index_language][j - (COL_TIMEOUT_RS485_END + 2)];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TIMEOUT_RS485_COMMA, 0);
          }
        }
      }
      else
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = COL_TIMEOUT_RS485_END;
      current_state_menu2.position_cursor_x = COL_TIMEOUT_RS485_BEGIN;

      //ϳ������� ������ �� ������� �������
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))
             )
      {
        current_state_menu2.position_cursor_x++;
      }

      //������ ������� ���, ��� �� ��� ����� ������
      if (
          ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
          (current_state_menu2.position_cursor_x > 0)
         )
      {
        current_state_menu2.position_cursor_x--;
      }
    }
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� time-out ���������� ������� ��� ����������
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_timeout_RS485(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      current_state_menu2.position_cursor_x = COL_TIMEOUT_RS485_BEGIN;
    }
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      uint32_t *p_value_edit = &settings_fix_edit.time_out_1_RS485;
      uint32_t *p_value_cont = &settings_fix.time_out_1_RS485;

      if (*p_value_cont != *p_value_edit) 
      {
        if (check_data_setpoint(*p_value_edit, VALUE_TIME_OUT_1_RS485_MIN, VALUE_TIME_OUT_1_RS485_MAX) == 1)
        {
          *p_value_cont = *p_value_edit;
          config_settings_modified |= MASKA_CHANGED_SETTINGS;
          result = RPEDE_DATA_CHANGED_OK;
        }
        else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� ����������� time-out ���������� ������� ��� ����������
*/
/*****************************************************/
void press_esc_in_timeout_RS485(void)
{
  settings_fix_edit.time_out_1_RS485 = settings_fix.time_out_1_RS485;
}
/*****************************************************/

/*****************************************************/
//���� time-out ���������� ������� ��� ����������
/*****************************************************
����� ���������
(1 << BIT_KEY_DOWN) - �������� ������ ����
(1 << BIT_KEY_UP)   - �������� ������ �����
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_timeout_RS485(unsigned int action)
{
  //������� ����� � �������� ����
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    settings_fix_edit.time_out_1_RS485 = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), settings_fix_edit.time_out_1_RS485, 1, COL_TIMEOUT_RS485_COMMA, COL_TIMEOUT_RS485_END, 1);
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if (current_state_menu2.position_cursor_x == COL_TIMEOUT_RS485_COMMA )current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < COL_TIMEOUT_RS485_BEGIN) ||
          (current_state_menu2.position_cursor_x > COL_TIMEOUT_RS485_END))
        current_state_menu2.position_cursor_x = COL_TIMEOUT_RS485_END;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
      if (current_state_menu2.position_cursor_x == COL_TIMEOUT_RS485_COMMA )current_state_menu2.position_cursor_x++;
      if ((current_state_menu2.position_cursor_x < COL_TIMEOUT_RS485_BEGIN) ||
          (current_state_menu2.position_cursor_x > COL_TIMEOUT_RS485_END))
        current_state_menu2.position_cursor_x = COL_TIMEOUT_RS485_BEGIN;
    }
    
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
