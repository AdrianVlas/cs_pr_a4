#include "header.h"

/*****************************************************/
//������� ����� ����������� ���� ����
/*****************************************************/
void make_ekran_setting_language(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_VIEW_SETTING_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "      ����      ",
      "      ����      ",
      "    Language    ",
      "      ����      "
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //�������� �� ��� �������� position_temp ������� ��� ����, �� �� ���� ������� �� ������������� ��� ����� (����� + ��������)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_FOR_VIEW_SETTING_LANGUAGE)
      {
        if ((i & 0x1) == 0)
        {
          //� ��������� ����� ����� �������� ���������
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          //� ������� ����� ����� �������� �������� �������
          uint8_t information[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
          {
            "    �������     ",
            "   ���������   ",
            "    English     ",
            "     �����      "
          };
          const unsigned int cursor_x[MAX_NAMBER_LANGUAGE] = {3, 2, 3, 4};
          
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][j];
          if (position_temp == index_in_ekran_tmp)
          {
            current_state_menu2.position_cursor_x = cursor_x[index_language];
          }
        }
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //³���������� ������ �� �������� � ������ ������ �� ���� � ��� �� ��������� ������
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

    //������ + ��������
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) 
    {
      current_state_menu2.cursor_on = 0;
      current_state_menu2.cursor_blinking_on = 0;
    }
    else 
    {
      current_state_menu2.cursor_on = 1;
      current_state_menu2.cursor_blinking_on = 1;
    }
  }

  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ Enter � ��� ����������� ����������� ���� ����
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_setting_language(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //����������, �� ��� ������ ��������
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_language_edit = &(settings_fix_edit.language);
      int32_t *p_language_cont = &(settings_fix.language);
      if (*p_language_cont != *p_language_edit) 
      {
        if (check_data_setpoint(*p_language_edit, VALUE_SETTING_LANGUAGE_MIN, VALUE_SETTING_LANGUAGE_MAX) == 1)
        {
          *p_language_cont = *p_language_edit;
          
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
������������ ESC � ��� ����������� ���� ����
*/
/*****************************************************/
void press_esc_in_setting_language(void)
{
  settings_fix_edit.language = settings_fix.language; 
}
/*****************************************************/

/*****************************************************/
//���� ����������� ���� ����
/*****************************************************
����� ���������
(1 << BIT_KEY_RIGHT)- �������� ������ ��������
(1 << BIT_KEY_LEFT) - �������� ������ ������

����� ���������
  ����
*****************************************************/
void change_setting_language(unsigned int action)
{
  //������� ����� � �������� ����
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int32_t value = settings_fix_edit.language;
    if ((action & (1 << BIT_KEY_RIGHT)) != 0) 
    {
      if ((++value) > VALUE_SETTING_LANGUAGE_MAX)
        value = VALUE_SETTING_LANGUAGE_MIN;
    }
    else 
    {
      if ((--value) < VALUE_SETTING_LANGUAGE_MIN)
        value = VALUE_SETTING_LANGUAGE_MAX;
    }
    settings_fix_edit.language = value;
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
