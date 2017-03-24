#include "header.h"

/*****************************************************/
//Формуємо екран відображення часових параметнів для ГПС
/*****************************************************/
void make_ekran_delay_meander(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
     )   
  {
    const uint8_t information_about_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "Ред.не разрешено",
      "Ред.не дозволене",
      "Ed.isn't allowed",
      "Ред.не разрешено",
    };

    const uint8_t information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " Вых.за диапазон",
      " Вих.за діапазон",
      "  Out of Limits ",
      "Вых.за диапазон "
    };

    enum _edition_stats edition = current_state_menu2.edition;
    make_ekran_about_info(((edition == ED_WARNING_EDITION_BUSY) ? false : true), ((edition == ED_WARNING_EDITION_BUSY) ? information_about_info : information_about_error));
  }
  else
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_INDEX_DELAY_MEANDER][MAX_COL_LCD + 1] = 
    {
      {
        "     Период     "
      },
      {
        "     Період     "
      },
      {
        "     Period     "
      },
      {
        "     Период     "
      }
    };
    
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
  
    __settings_for_MEANDER *p_settings_for_meander;
    if (current_state_menu2.edition == ED_VIEWING) p_settings_for_meander = &((((__LN_MEANDER*)spca_of_p_prt[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings);
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_settings_for_meander = (((__settings_for_MEANDER*)sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    else p_settings_for_meander = (((__settings_for_MEANDER*)sca_of_p_edit[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    size_t col_begin, col_end, col_comma;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_INDEX_DELAY_MEANDER)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений

          switch (index_in_ekran_tmp)
          {
          case INDEX_DELAY_MEANDER_PERIOD:
            {
              vaga = 10000; //максимальний ваговий коефіцієнт
              col_begin = COL_DELAY_MEANDER_PERIOD_BEGIN;
              col_end = COL_DELAY_MEANDER_PERIOD_END;
              col_comma = COL_DELAY_MEANDER_PERIOD_COMMA;
            
              value = p_settings_for_meander->set_delay[MEANDER_SET_DELAY_PERIOD];
            
              break;
            }
          }
        }
        else
        {
          //У парному номері рядку виводимо значення
          for (size_t j = 0; j < MAX_COL_LCD; j++)
          {
            if (
                ((j < col_begin) ||  (j > col_end )) &&
                (j != (col_end + 2))
               )working_ekran[i][j] = ' ';
            else if (j == col_comma )working_ekran[i][j] = ',';
            else if (j == (col_end + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, col_comma, 0);
          }
        }
        
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
    current_state_menu2.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);

    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      switch (current_state_menu2.index_position)
      {
      case INDEX_DELAY_MEANDER_PERIOD:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_MEANDER_PERIOD_BEGIN;
          last_position_cursor_x = COL_DELAY_MEANDER_PERIOD_END;
          break;
        }
      }

      //Підтягуємо курсор до першого символу
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x -1))
             )
      {
        current_state_menu2.position_cursor_x++;
      }

      //Курсор ставимо так, щоб він був перед числом
      if (
          ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x]) != ' ') && 
          (current_state_menu2.position_cursor_x > 0)
         )
      {
        current_state_menu2.position_cursor_x--;
      }
    }
    //Курсор видимий
    current_state_menu2.cursor_on = 1;
    //Курсор не мигає
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Натискування Enter у вікні відображення витримок ГПС
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_delay_meander(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case INDEX_DELAY_MEANDER_PERIOD:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_MEANDER_PERIOD_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      __settings_for_MEANDER *p_settings_for_meander_edit = (((__settings_for_MEANDER*)sca_of_p_edit[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      __settings_for_MEANDER *p_settings_for_meander_cont = (((__settings_for_MEANDER*)sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      switch (current_state_menu2.index_position)
      {
      case INDEX_DELAY_MEANDER_PERIOD:
        {
          if (p_settings_for_meander_cont->set_delay[MEANDER_SET_DELAY_PERIOD] != p_settings_for_meander_edit->set_delay[MEANDER_SET_DELAY_PERIOD]) 
          {
            if (check_data_setpoint(p_settings_for_meander_edit->set_delay[MEANDER_SET_DELAY_PERIOD], TIMEOUT_MEANDER_PERIOD_MIN, TIMEOUT_MEANDER_PERIOD_MAX) == 1)
            {
              p_settings_for_meander_cont->set_delay[MEANDER_SET_DELAY_PERIOD] = p_settings_for_meander_edit->set_delay[MEANDER_SET_DELAY_PERIOD];
              config_settings_modified |= MASKA_CHANGED_SETTINGS;
              result = RPEDE_DATA_CHANGED_OK;
            }
            else result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
          }

          break;
        }
      }

      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*
Натискування ESC у вікні витримок багатофункціональних таймерів
*/
/*****************************************************/
void press_esc_in_delay_meander(void)
{
  __settings_for_MEANDER *p_settings_for_meander_edit = (((__settings_for_MEANDER*)sca_of_p_edit[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  __settings_for_MEANDER *p_settings_for_meander_cont = (((__settings_for_MEANDER*)sca_of_p[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  switch (current_state_menu2.index_position)
  {
  case INDEX_DELAY_MEANDER_PERIOD:
    {
      p_settings_for_meander_edit->set_delay[MEANDER_SET_DELAY_PERIOD] = p_settings_for_meander_cont->set_delay[MEANDER_SET_DELAY_PERIOD];
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Зміна налаштування
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_DOWN) - натснуто кнопку вниз
(1 << BIT_KEY_UP)   - атиснуто кнопку вверх
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_delay_meander(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    int32_t *p_value = (((__settings_for_MEANDER*)sca_of_p_edit[ID_FB_MEANDER - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    unsigned int col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case INDEX_DELAY_MEANDER_PERIOD:
      {
        col_end = COL_DELAY_MEANDER_PERIOD_END;
        col_comma = COL_DELAY_MEANDER_PERIOD_COMMA;
        break;
      }
    }
    
    intptr_t index = current_state_menu2.index_position;
    p_value[index] = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), p_value[index], 1, col_comma, col_end, 100);
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    int col_begin, col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case INDEX_DELAY_MEANDER_PERIOD:
      {
        col_begin = COL_DELAY_MEANDER_PERIOD_BEGIN;
        col_end = COL_DELAY_MEANDER_PERIOD_END;
        col_comma = COL_DELAY_MEANDER_PERIOD_COMMA;
        break;
      }
    }
    
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if (current_state_menu2.position_cursor_x == col_comma )current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_end;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
      if (current_state_menu2.position_cursor_x == col_comma )current_state_menu2.position_cursor_x++;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_begin;
    }
    
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
