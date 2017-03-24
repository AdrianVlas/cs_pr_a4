#include "header.h"

/*****************************************************/
//Формуємо екран відображення заголовків налаштувань де є тільки витримки
/*****************************************************/
void make_ekran_choose_delay(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_D_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Выдержки       "
    },
    {
      " Витримки       "
    },
    {
      " Delay          "
    },
    {
      " Беріктік       "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < MAX_ROW_LIST_SETTINGS_D_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
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
//Формуємо екран відображення заголовків налаштувань де є тільки налаштування
/*****************************************************/
void make_ekran_choose_control(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_C_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Управление     "
    },
    {
      " Управління     "
    },
    {
      " Control        "
    },
    {
      " Баскару        "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < MAX_ROW_LIST_SETTINGS_C_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
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
//Формуємо екран відображення заголовків настроювання де є витримки і управління
/*****************************************************/
void make_ekran_choose_delay_control(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_DC_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Выдержки       ",
      " Управление     "
    },
    {
      " Витримки       ",
      " Управління     "
    },
    {
      " Delay          ",
      " Control        "
    },
    {
      " Беріктік       ",
      " Баскару        "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < MAX_ROW_LIST_SETTINGS_DC_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
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
//Формуємо екран відображення заголовків настроювання де є витримки і управління
/*****************************************************/
void make_ekran_choose_pickup_delay_control(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_LIST_SETTINGS_PDC_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Уставки        ",
      " Выдержки       ",
      " Управление     "
    },
    {
      " Уставки        ",
      " Витримки       ",
      " Управління     "
    },
    {
      " Pickups        ",
      " Delay          ",
      " Control        "
    },
    {
      " Баскару        ",
      " Кyрулар        ",
      " Беріктік       "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < MAX_ROW_LIST_SETTINGS_PDC_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
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
//
/*****************************************************/
/*****************************************************/
