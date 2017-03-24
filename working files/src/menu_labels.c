#include "header.h"

/*****************************************************/
//Формуємо екран відображення списку міток настроювання
/*****************************************************/
void make_ekran_list_labels(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LABELS_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Метка конфиг.  ",
      " Метка настроек "
    },
    {
      " Мітка конфіг.  ",
      " Мітка налашт.  "
    },
    {
      " Configur.Mark  ",
      " Settings Mark  "
    },
    {
      " Метка конфиг.  ",
      " Метка настроек "
    }
  };
  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < MAX_ROW_LABELS_M2) ? name_string[index_language][index_in_ekran][j] : ' ';

    index_in_ekran++;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_state_menu2.cursor_on = 1;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран мітки часу останніх змін у настроюванні
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
  //Заповнюємо поля відповідними цифрами
  /******************************************/
  //День
  name_string[0][0 ] = ((*(point_to_target + 4)) >>  4) + 0x30;
  name_string[0][1 ] = ((*(point_to_target + 4)) & 0xf) + 0x30;

  //Місяць
  name_string[0][3 ] = ((*(point_to_target + 5)) >>  4) + 0x30;
  name_string[0][4 ] = ((*(point_to_target + 5)) & 0xf) + 0x30;

  //Рік
  name_string[0][8 ] = ((*(point_to_target + 6)) >>  4) + 0x30;
  name_string[0][9 ] = ((*(point_to_target + 6)) & 0xf) + 0x30;

  //Година
  name_string[1][0 ] = ((*(point_to_target + 3)) >>  4) + 0x30;
  name_string[1][1 ] = ((*(point_to_target + 3)) & 0xf) + 0x30;

  //Хвилини
  name_string[1][3 ] = ((*(point_to_target + 2)) >>  4) + 0x30;
  name_string[1][4 ] = ((*(point_to_target + 2)) & 0xf) + 0x30;

  //Секунди
  name_string[1][6 ] = ((*(point_to_target + 1)) >>  4) + 0x30;
  name_string[1][7 ] = ((*(point_to_target + 1)) & 0xf) + 0x30;

  //Повідомлення про джерело змін
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
    //теоретично ми сюди б не мали ніколи заходити, але якщо ми сюди зайшли, то виводимо сигналізацію про помилку на екран
    const uint8_t error_meas[MAX_NAMBER_LANGUAGE][7 + 1] = 
    {
      " Ошибка",
      "Помилка",
      "  Error",
      " Ошибка"
    };
    int index_language = index_language_in_array(settings_fix_prt.language);
      
    for (size_t i = 0; i < 7; i++) name_string[INDEX_TIME_CALIBRATION_M2_TIME][9 + i] = error_meas[index_language][i];
  }
  
  /******************************************/
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати
    for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < (2*MAX_ROW_TIME_CONFIG_OR_SETTINGS)) ? name_string[index_in_ekran][j] : ' ';

    index_in_ekran++;
  }

  //Курсор по горизонталі поміщаємо на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі в 0
  current_state_menu2.position_cursor_y = 0;
  //Курсор невидимий
  current_state_menu2.cursor_on = 0;
  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
