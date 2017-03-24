#include "header.h"

/*****************************************************/
//Формуємо екран відображення вікна відображення налаштувувань для дискретного вхроду
/*****************************************************/
void make_ekran_control_alarm(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_ALARM][MAX_COL_LCD + 1] = 
    {
      {
        "     Режим      "
      },
      {
        "     Режим      "
      },
      {
        "      Mode      "
      },
      {
        "     Режим      "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    uint32_t *p_control;
    if (current_state_menu2.edition == ED_VIEWING) p_control = &((((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings.control);
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_control = &((((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->control);
    else p_control = &((((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->control);
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_INDEX_CTRL_ALARM)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          //У парному номері рядку виводимо значення
          if (index_in_ekran_tmp == INDEX_CTRL_ALARM_MODE)  
          {
            const uint8_t information[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER][MAX_COL_LCD + 1] = 
            {
              {"    ПРОСТОЙ     ", "   ТРИГГЕНЫЙ    ", "    ЗАД.ВР.     "},
              {"    ПРОСТИЙ     ", "    ТРИҐЕНЫЙ    ", "    ЗАД.ЧАС     "},
              {"     SIMPLE     ", "    TRIGGER     ", "    ЗАД.ВР.     "},
              {"    ПРОСТИЙ     ", "   ТРИГГЕНЫЙ    ", "    ЗАД.ВР.     "}
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][ALARM_MODES_NUMBER] = 
            {
              {3, 2, 3},
              {3, 3, 3},
              {4, 3, 3},
              {3, 2, 3}
            };
          
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][((*p_control) >> alarm_ctrl_patten[index_in_ekran_tmp][0]) & ((1 << alarm_ctrl_patten[index_in_ekran_tmp][1]) - 1)][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][((*p_control) >> index_in_ekran_tmp) & 0x1];
            }
          }
        }
      }
      else
        for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
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
Натискування Enter у вікні відображення налаштувань дискретного входу
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_control_alarm(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      __settings_for_ALARM *p_settings_edit = (((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      __settings_for_ALARM *p_settings_cont = (((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      if (p_settings_cont->control != p_settings_edit->control) 
      {
        if ((p_settings_edit->control & ((uint32_t)(~MASKA_CTRL_ALARM_M2))) == 0)
        {
          p_settings_cont->control = p_settings_edit->control;
          
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
Натискування ESC у вікні налаштувань дискретного входу
*/
/*****************************************************/
void press_esc_in_control_alarm(void)
{
  uint32_t *p_control_edit = &((((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->control);
  uint32_t *p_control_cont = &((((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->control);
  *p_control_edit = *p_control_cont;
}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань бінарної інформації для дискретних входів
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_control_alarm(unsigned int action)
{
  //Вводимо число у відповідне поле
  uint32_t *p_control_edit = &((((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->control);
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    uint32_t maska = (1 << alarm_ctrl_patten[current_state_menu2.index_position][1]) - 1;
    uint32_t shift = alarm_ctrl_patten[current_state_menu2.index_position][0];

    int32_t data_tmp = ((*p_control_edit) >> shift) & maska;
    if ((action & (1 << BIT_KEY_RIGHT)) != 0) data_tmp++;
    else data_tmp--;
    if (data_tmp < ALARM_MODE_SIMPLE) data_tmp = ALARM_MODES_NUMBER - 1;
    else if (data_tmp >= ALARM_MODES_NUMBER) data_tmp = ALARM_MODE_SIMPLE;
    
    *p_control_edit = ((*p_control_edit) & ((uint32_t)(~(maska << shift)))) | (data_tmp << shift);
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення часових параметнів для дискретного входу
/*****************************************************/
void make_ekran_delay_alarm(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
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
  
    int32_t *p_set_delay;
    if (current_state_menu2.edition == ED_VIEWING) p_set_delay = (((__LN_ALARM*)spca_of_p_prt[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings.set_delay;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_set_delay = (((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    else p_set_delay = (((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    size_t col_begin, col_end, col_comma;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < ALARM_SET_DELAYS)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений

          switch (index_in_ekran_tmp)
          {
          case ALARM_SET_DELAY_PERIOD:
            {
              vaga = 10000; //максимальний ваговий коефіцієнт
              col_begin = COL_DELAY_ALARM_PERIOD_BEGIN;
              col_end = COL_DELAY_ALARM_PERIOD_END;
              col_comma = COL_DELAY_ALARM_PERIOD_COMMA;
            
              value = p_set_delay[ALARM_SET_DELAY_PERIOD];
            
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
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);

    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      switch (current_state_menu2.index_position)
      {
      case ALARM_SET_DELAY_PERIOD:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_ALARM_PERIOD_BEGIN;
          last_position_cursor_x = COL_DELAY_ALARM_PERIOD_END;
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
Натискування Enter у вікні відображення витримок дискретного входу
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_delay_alarm(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case ALARM_SET_DELAY_PERIOD:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_ALARM_PERIOD_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_set_delay_edit = (((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
      int32_t *p_set_delay_cont = (((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
      switch (current_state_menu2.index_position)
      {
      case ALARM_SET_DELAY_PERIOD:
        {
          if (p_set_delay_cont[ALARM_SET_DELAY_PERIOD] != p_set_delay_edit[ALARM_SET_DELAY_PERIOD]) 
          {
            if (check_data_setpoint(p_set_delay_edit[ALARM_SET_DELAY_PERIOD], TIMEOUT_ALARM_PERIOD_MIN, TIMEOUT_ALARM_PERIOD_MAX) == 1)
            {
              p_set_delay_cont[ALARM_SET_DELAY_PERIOD] = p_set_delay_edit[ALARM_SET_DELAY_PERIOD];
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
Натискування ESC у вікні витримок дискретного входу
*/
/*****************************************************/
void press_esc_in_delay_alarm(void)
{
  int32_t *p_set_delay_edit = (((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
  int32_t *p_set_delay_cont = (((__settings_for_ALARM*)sca_of_p[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;

  int index = current_state_menu2.index_position;
  p_set_delay_edit[index] = p_set_delay_cont[index];
}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань допуску дискретного входу
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_DOWN) - натснуто кнопку вниз
(1 << BIT_KEY_UP)   - атиснуто кнопку вверх
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_delay_alarm(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    int32_t *p_value = (((__settings_for_ALARM*)sca_of_p_edit[ID_FB_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    unsigned int col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case ALARM_SET_DELAY_PERIOD:
      {
        col_end = COL_DELAY_ALARM_PERIOD_END;
        col_comma = COL_DELAY_ALARM_PERIOD_COMMA;
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
    case ALARM_SET_DELAY_PERIOD:
      {
        col_begin = COL_DELAY_ALARM_PERIOD_BEGIN;
        col_end = COL_DELAY_ALARM_PERIOD_END;
        col_comma = COL_DELAY_ALARM_PERIOD_COMMA;
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
