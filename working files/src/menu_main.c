#include "header.h"

/*****************************************************/
/*
Функція переміщення по меню

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_main(unsigned int action, int max_row)
{
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
    do
    {
      if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      while (
             (current_state_menu2.index_position == INDEX_MAIN_M2_MEASURMENTS) &&
             (current_config_prt.n_group_alarm == 0)
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
             (current_state_menu2.index_position == INDEX_MAIN_M2_MEASURMENTS) &&
             (current_config_prt.n_group_alarm == 0)
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
//Формуємо екран головного меню
/*****************************************************/
void make_ekran_main(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_MAIN_M2][MAX_COL_LCD + 1] = 
  {
    {
     " Часы           ",
     " Измерения      ",
     " Входы-Выходы   ",
     " Регистраторы   ",
     " Настройки      ",
     " Диагностика    ",
     " Метка настроек ",
     " Версия ПО и КП "
    },
    {
     " Годинник       ",
     " Вимірювання    ",
     " Входи-Виходи   ",
     " Реєстратори    ",
     " Налаштування   ",
     " Діагностика    ",
     " Мітка налашт.  ",
     " Версія ПЗ і КП "
    },
    {
     " Clock          ",
     " Measurement    ",
     " Inputs-Outputs ",
     " Recorders      ",
     " Settings       ",
     " Diagnostic     ",
     " Settings Mark  ",
     " VER.of F/W & MM"
    },
    {
     " Саfат          ",
     " Љлшем          ",
     " Кіріс-Шыfыс    ",
     " Тіркегіштер    ",
     " Реттегіш       ",
     " Диагностика    ",
     " Метка настроек ",
     " Версия ПО и КП "
    }
  };

  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int additional_current = 0;
  unsigned int position_temp = current_state_menu2.index_position;

  uint8_t name_string_tmp[MAX_ROW_MAIN_M2][MAX_COL_LCD + 1];
  for(size_t index_1 = 0; index_1 < MAX_ROW_MAIN_M2; index_1++)
  {
    if (
        (index_1 == INDEX_MAIN_M2_MEASURMENTS) &&
        (current_config_prt.n_group_alarm == 0)
       )
    {
      if ((index_1 - additional_current) < position_temp) position_temp--;
      additional_current++;

      for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      {
        name_string_tmp[MAX_ROW_MAIN_M2 - additional_current][index_2] = ' ';
      }
      name_string_tmp[MAX_ROW_MAIN_M2 - additional_current][MAX_COL_LCD] = '\0';
    }
    else
    {
      for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
      {
        name_string_tmp[index_1 - additional_current][index_2] = name_string[index_language][index_1][index_2];
      }
    }
  }
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    for (size_t j = 0; j < MAX_COL_LCD; j++) 
    {
      working_ekran[i][j] = (index_in_ekran < (MAX_ROW_MAIN_M2 - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
    }
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
/*
Функція обробки натискування кнопки Enter
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_main_and_list_passwords(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  
  enum _menu2_levels new_level = *((enum _menu2_levels*)p_menu_param_1);
  if (
      (new_level != current_state_menu2.current_level)
      &&  
      (
       (new_level == LIST_SETTINGS_MENU2_LEVEL)
       ||  
       (
        (new_level == SET_NEW_PASSWORD_MENU2_LEVEL) &&
        (current_state_menu2.edition == ED_VIEWING)
       )
      )   
     )   
  {
    //Є спроба перейти у вікно списку налаштувань
    if (settings_fix_prt.password_2 == 0)
    {
      if (config_settings_modified == 0)
      {
        //Входимо з правом подальшого редагування
        current_state_menu2.edition = ED_CAN_BE_EDITED;

        //Фіксуємо, що система меню захопила "монополію" на зміну конфігурації і налаштувань
        config_settings_modified = MASKA_MENU_LOCKS;
      }
      else
      {
        //Повідомляємо про те, що режим редагування зараз недоступний
        current_state_menu2.edition = ED_WARNING_EDITION_BUSY;
        if (new_level == SET_NEW_PASSWORD_MENU2_LEVEL)
        {
          //Не дозволяємо заходити у ті вікна, у які без дозволу редагування заходити неможна
          *((enum _menu2_levels*)p_menu_param_1) = current_state_menu2.current_level;
          
          //Виставляємо команду на обновлекння екрану
          new_state_keyboard |= (1<<BIT_REWRITE);

        }
      }
    }
    else if (
             (new_level == SET_NEW_PASSWORD_MENU2_LEVEL) ||
             (settings_fix_prt.password_1 != 0)
            )   
    {
      //Переходимо на меню запиту паролю
      next_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = new_level;
      *((enum _menu2_levels*)p_menu_param_1) = PASSWORD_MENU2_LEVEL;
    }
  }
                  
  return result;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
