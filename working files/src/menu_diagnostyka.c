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
void move_into_diagnostics(unsigned int action, int max_row)
{
  unsigned int diagnostyka_tmp[3] = {diagnostyka[0], diagnostyka[1], (diagnostyka[2] & USED_BITS_IN_LAST_INDEX)};
  if (
      (diagnostyka_tmp[0] == 0) &&
      (diagnostyka_tmp[1] == 0) &&
      (diagnostyka_tmp[2] == 0)
     ) 
  {
    current_state_menu2.index_position = 0;
  }
  else
  {
    if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
    {
      if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
      do
      {
        if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
        while (_CHECK_SET_BIT(diagnostyka_tmp, current_state_menu2.index_position) == 0)
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
        while (_CHECK_SET_BIT(diagnostyka_tmp, current_state_menu2.index_position) == 0)
        {
          if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
        }
      }
      while (current_state_menu2.index_position < 0);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення діагностики
/*****************************************************/
void make_ekran_diagnostics(void)
{
#define NUMBER_ROW_FOR_NO_ERRORS 2
  
  unsigned int position_temp = current_state_menu2.index_position;
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][NUMBER_ROW_FOR_NO_ERRORS + MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1] = 
  {
    {
      "      Нет       ",
      "     ошибок     ",
      NAME_DIAGN_RU
    },
    {
      "     Немає      ",
      "    помилок     ",
      NAME_DIAGN_UA
    },
    {
      "       No       ",
      "     errors     ",
      NAME_DIAGN_EN
    },
    {
      "      Кате      ",
      "      жок       ",
      NAME_DIAGN_KZ
    }
  };

  int index_language = index_language_in_array(settings_fix_prt.language);
    
  if (
      (diagnostyka[0] == 0) &&
      (diagnostyka[1] == 0) &&
      (diagnostyka[2] == 0) 
     )
  {
    //Це означає, що ніякої помилки не зафіксовано
     
    //Текучу позицію в сипску переводимо на сам початок
    current_state_menu2.index_position = 0;
    position_in_current_level_menu2[current_state_menu2.current_level] = 0;

    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //Копіюємо в робочий екран інформацію, що нічого не відранжовано
      for (size_t j = 0; j < MAX_COL_LCD; j++)working_ekran[i][j] = (i < NUMBER_ROW_FOR_NO_ERRORS) ? name_string[index_language][i][j] : ' ';
    }
    //Курсор не видимий
    current_state_menu2.cursor_on = 0;
  }
  else
  {
    /************************************************************/
    //Формуємо список із помилок які реально присутні
    /************************************************************/
    uint8_t name_string_tmp[MAX_ROW_FOR_DIAGNOSTYKA][MAX_COL_LCD + 1];

    int offset = 0;
    for(intptr_t index_1 = 0; index_1 < (MAX_ROW_FOR_DIAGNOSTYKA - offset); index_1++)
    {
      while (
             (index_1 < (MAX_ROW_FOR_DIAGNOSTYKA - offset)) &&
             (_CHECK_SET_BIT(diagnostyka, (index_1 + offset)) == 0)
            )   
      {
        if (_CHECK_SET_BIT(diagnostyka, (index_1 + offset)) == 0)
        {
           if (current_state_menu2.index_position >= ((int)(index_1 + offset))) position_temp--;
          offset++;
        }
      }
      
      if (index_1 < (MAX_ROW_FOR_DIAGNOSTYKA - offset))
      {
        for(size_t index_2 = 0; index_2 < (MAX_COL_LCD + 1); index_2++)
          name_string_tmp[index_1][index_2] = name_string[index_language][NUMBER_ROW_FOR_NO_ERRORS + index_1 + offset][index_2];
      }
    }
    /************************************************************/
    
    int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i< MAX_ROW_LCD; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = (index_in_ekran < (MAX_ROW_FOR_DIAGNOSTYKA - offset)) ? name_string_tmp[index_in_ekran][j] : ' ';

      index_in_ekran++;
    }

    //Курсор видимий
    current_state_menu2.cursor_on = 1;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);

  //Курсор не мигає
  current_state_menu2.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
  
#undef NUMBER_ROW_FOR_NO_ERRORS
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
