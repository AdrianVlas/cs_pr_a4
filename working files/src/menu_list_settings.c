#include "header.h"

/*****************************************************/
/*
������� ���������� �� ����

����� ���������
(1 << BIT_REWRITE) - ������������ ����
(1 << BIT_KEY_DOWN) - �������� ����
(1 << BIT_KEY_UP) - �������� �����
*/
/*****************************************************/
void move_into_list_settings(unsigned int action, int max_row)
{
  __CONFIG *p_current_config;
  p_current_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
      
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
    do
    {
      if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      while (
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_BIOS) &&
              (p_current_config->n_input == 0) &&
              (p_current_config->n_output == 0) &&
              (p_current_config->n_led == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_ALARMS) &&
              (p_current_config->n_alarm == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_GROUP_ALARMS) &&
              (p_current_config->n_group_alarm == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_TIMERS) &&
              (p_current_config->n_timer == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_MEANDER) &&
              (p_current_config->n_meander == 0)
             )
            )
      {
        if(++current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      }
    }
    while ((action & (1 << BIT_KEY_DOWN)) && (current_state_menu2.index_position >= max_row));
  }
  else if (action & (1 << BIT_KEY_UP))
  {
    current_state_menu2.index_position--;
    do
    {
      if(current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
      while (
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_BIOS) &&
              (p_current_config->n_input == 0) &&
              (p_current_config->n_output == 0) &&
              (p_current_config->n_led == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_ALARMS) &&
              (p_current_config->n_alarm == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_GROUP_ALARMS) &&
              (p_current_config->n_group_alarm == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_TIMERS) &&
              (p_current_config->n_timer == 0)
             )
             ||
             (
              (current_state_menu2.index_position == INDEX_LIST_SETTINGS_M2_MEANDER) &&
              (p_current_config->n_meander == 0)
             )
            )
      {
        if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
      }
    }
    while (current_state_menu2.index_position < 0);
  }
}
/*****************************************************/

/*****************************************************/
//������� ����� ����������� ��������� ���������
/*****************************************************/
void make_ekran_list_settings(void)
{
  if (current_state_menu2.edition == ED_CONFIRM_CHANGES)
  {
    make_ekran_ask_rewrite();

    //����������� �� ���������� ������
    new_state_keyboard |= (1<<BIT_REWRITE);
  }
  else if (
           (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
           (current_state_menu2.edition == ED_INFO)
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
      " ���.���.������.",
      " ���.���.������.",
      " ���.���.������.",
      " ���.���.������."
    };

    make_ekran_about_info(false, ((current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_M2][MAX_COL_LCD + 1] = 
    {
      {
        " ������������   ",
        " ���            ",
        " C��            ",
        " ���            ",
        " ��-�������     ",
        " ���            ",
        " ������������.  ",
        " ����           ",
        " ������������   ",
        " ������         "
      },
      {
        " ������������   ",
        " ���            ",
        " ���            ",
        " ���            ",
        " ��-�������     ",
        " ���            ",
        " �������������� ",
        " ����           ",
        " ����������    ",
        " �����         "
      },
      {
        " Configuration  ",
        " BIOS           ",
        " Alarms         ",
        " Gr.Alarms      ",
        " MF-Timer       ",
        " PSG            ",
        " Parametrization",
        " Language       ",
        " Communication  ",
        " Passwords      "
      },
      {
        " ������������   ",
        " ���            ",
        " C��            ",
        " ���            ",
        " ��-�������     ",
        " ���            ",
        " ������������.  ",
        " ����           ",
        " ������������   ",
        " ������         "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);

    unsigned int additional_current = 0;
    unsigned int position_temp = current_state_menu2.index_position;

    __CONFIG *p_current_config;
    p_current_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
    
    uint8_t name_string_tmp[MAX_ROW_LIST_SETTINGS_M2][MAX_COL_LCD + 1];
    for(size_t index_1 = 0; index_1 < MAX_ROW_LIST_SETTINGS_M2; index_1++)
    {
      if (
          (
           (index_1 == INDEX_LIST_SETTINGS_M2_BIOS) &&
           (p_current_config->n_input == 0) &&
           (p_current_config->n_output == 0) &&
           (p_current_config->n_led == 0)
          )
          ||
          (
           (index_1 == INDEX_LIST_SETTINGS_M2_ALARMS) &&
           (p_current_config->n_alarm == 0)
          )
          ||
          (
           (index_1 == INDEX_LIST_SETTINGS_M2_GROUP_ALARMS) &&
           (p_current_config->n_group_alarm == 0)
          )
          ||
          (
           (index_1 == INDEX_LIST_SETTINGS_M2_TIMERS) &&
           (p_current_config->n_timer == 0)
          )
          ||
          (
           (index_1 == INDEX_LIST_SETTINGS_M2_MEANDER) &&
           (p_current_config->n_meander == 0)
          )
         )
      {
        if ((index_1 - additional_current) < position_temp) position_temp--;
        additional_current++;

        for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
        {
          name_string_tmp[MAX_ROW_LIST_SETTINGS_M2 - additional_current][index_2] = ' ';
        }
        name_string_tmp[MAX_ROW_LIST_SETTINGS_M2 - additional_current][MAX_COL_LCD] = '\0';
      }
      else
      {
        for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
        {
          name_string_tmp[index_1 - additional_current][index_2] = name_string[index_language][index_1][index_2];
        }
      }
    }
    unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;;
  
    //�������  ����� � ������� �����
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
      for (size_t j = 0; j < MAX_COL_LCD; j++) 
      {
        working_ekran[i][j] = (index_in_ekran < (MAX_ROW_LIST_SETTINGS_M2 - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
      }
      index_in_ekran++;
    }

    /*
    ��� �� ������� �� ���� � �������� �� �����������, �� ��������� ���� � �����, ���� ����� ������ �����������
    ��� ����� ���� ����, ��� � ���� ��� �� �� ����, �� ������� �� ����� �� ���� �������� �������� ������
    */
    if (current_state_menu2.edition == ED_EDITION )
    {
      current_state_menu2.edition = ED_CAN_BE_EDITED;
    }
  
    //������ �� ���������� ������������ �� ������ �������
    current_state_menu2.position_cursor_x = 0;
    //³���������� ������ �� ��������
    current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    //������ �������
    current_state_menu2.cursor_on = 1;
    //������ �� ����
    current_state_menu2.cursor_blinking_on = 0;
  }
  
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
������������ ESC � ��� ������������
*/
/*****************************************************/
void press_esc_in_list_settings(void)
{
  if ((config_settings_modified & MASKA_MENU_LOCKS) != 0)
  {
    if ((config_settings_modified & (MASKA_CHANGED_CONFIGURATION | MASKA_CHANGED_SETTINGS)) != 0)
    {
      if (current_state_menu2.edition == ED_CAN_BE_EDITED)
      {
        //����� ��������� ����� �� �������� ���
        current_state_menu2.edition = ED_CONFIRM_CHANGES;
      }
      else if (current_state_menu2.edition == ED_CONFIRM_CHANGES)
      {
        //����� ������ �������� ����� �����������
        unsigned int result = set_config_and_settings(0, NO_MATTER_PARAMS_FIX_CHANGES);
        if (result == 0)
        {
          //������� ����� �����������
          current_state_menu2.edition = ED_VIEWING;
        }
        else
        {
          //����������� ��� �������� �������
          current_state_menu2.edition = ED_ERROR;
        }
      
        config_settings_modified = 0;
      }
    }
    else
    {
      config_settings_modified = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
