#include "header.h"

/*****************************************************/
//������� ����� ����������� ������ ���� ������������
/*****************************************************/
void make_ekran_list_labels(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LABELS_M2][MAX_COL_LCD + 1] = 
  {
    {
      " ����� ������.  ",
      " ����� �������� "
    },
    {
      " ̳��� ������.  ",
      " ̳��� ������.  "
    },
    {
      " Configur.Mark  ",
      " Settings Mark  "
    },
    {
      " ����� ������.  ",
      " ����� �������� "
    }
  };
  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ���������� � ������� ������������
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < MAX_ROW_LABELS_M2) ? name_string[index_language][index_in_ekran][j] : ' ';

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
//������� ����� ���� ���� ������� ��� � �����������
/*
*/
/*****************************************************/
void make_ekran_time_config_or_settings(void)
{
  uint8_t name_string[2*MAX_ROW_TIME_CONFIG_OR_SETTINGS][MAX_COL_LCD + 1] = 
  {
    "XX-XX-20XX      ",
    "XX:XX:XX XXXXXXX"
  };
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  uint8_t *point_to_target;

  if (*((unsigned int*)p_menu_param_1) == 0) point_to_target = (&current_config_prt)->time_config;
  else point_to_target = (&settings_fix_prt)->time_setpoints;
  
  /******************************************/
  //���������� ���� ���������� �������
  /******************************************/
  //����
  name_string[0][0 ] = ((*(point_to_target + 4)) >>  4) + 0x30;
  name_string[0][1 ] = ((*(point_to_target + 4)) & 0xf) + 0x30;

  //̳����
  name_string[0][3 ] = ((*(point_to_target + 5)) >>  4) + 0x30;
  name_string[0][4 ] = ((*(point_to_target + 5)) & 0xf) + 0x30;

  //г�
  name_string[0][8 ] = ((*(point_to_target + 6)) >>  4) + 0x30;
  name_string[0][9 ] = ((*(point_to_target + 6)) & 0xf) + 0x30;

  //������
  name_string[1][0 ] = ((*(point_to_target + 3)) >>  4) + 0x30;
  name_string[1][1 ] = ((*(point_to_target + 3)) & 0xf) + 0x30;

  //�������
  name_string[1][3 ] = ((*(point_to_target + 2)) >>  4) + 0x30;
  name_string[1][4 ] = ((*(point_to_target + 2)) & 0xf) + 0x30;

  //�������
  name_string[1][6 ] = ((*(point_to_target + 1)) >>  4) + 0x30;
  name_string[1][7 ] = ((*(point_to_target + 1)) & 0xf) + 0x30;

  //����������� ��� ������� ���
  if((*(point_to_target + 7)) == DEFAULT_PARAMS_FIX_CHANGES)
  {
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 7] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 6] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 5] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 4] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 3] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 2] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 1] = '0';
  }
  else if((*(point_to_target + 7)) == MENU_PARAMS_FIX_CHANGES)
  {
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 7] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 6] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 5] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 4] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 3] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 2] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 1] = 'K';
  }
  else if((*(point_to_target + 7)) == USB_PARAMS_FIX_CHANGES)
  {
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 7] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 6] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 5] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 4] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 3] = 'U';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 2] = 'S';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 1] = 'B';
  }
  else if((*(point_to_target + 7)) == RS485_PARAMS_FIX_CHANGES)
  {
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 7] = ' ';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 6] = 'R';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 5] = 'S';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 4] = '-';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 3] = '4';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 2] = '8';
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][MAX_COL_LCD - 1] = '5';
  }
  else
  {
    //���������� �� ���� � �� ���� ����� ��������, ��� ���� �� ���� ������, �� �������� ����������� ��� ������� �� �����
    const uint8_t error_meas[MAX_NAMBER_LANGUAGE][7 + 1] = 
    {
      " ������",
      "�������",
      "  Error",
      " ������"
    };
    int index_language = index_language_in_array(settings_fix_prt.language);
      
    for (size_t i = 0; i < 7; i++) name_string[INDEX_TIME_CALIBRATION_M2_TIME][9 + i] = error_meas[index_language][i];
  }
  
  /******************************************/
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //������� ����� ����� ���������, �� �� ����� ����������
    for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < (2*MAX_ROW_TIME_CONFIG_OR_SETTINGS)) ? name_string[index_in_ekran][j] : ' ';

    index_in_ekran++;
  }

  //������ �� ���������� ������� �� ������ �������
  current_state_menu2.position_cursor_x = 0;
  //³���������� ������ �� �������� � 0
  current_state_menu2.position_cursor_y = 0;
  //������ ���������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
  //�������� ������� ���� �����
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
