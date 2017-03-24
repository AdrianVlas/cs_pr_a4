#include "header.h"

/*****************************************************/
//Формуємо екран конфігурації
/*****************************************************/
void make_ekran_configuration(void)
{
  if (
      (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
      (current_state_menu2.edition == ED_WARNING_ENTER_ESC) ||
      (current_state_menu2.edition == ED_WARNING_ENTER)
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
      " Дин.пам.недост.",
      " Дин.пам.недост.",
      " Дин.пам.недост.",
      " Дин.пам.недост."
    };
    
    const uint8_t information_about_out_of_range[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " Вых.за диапазон",
      " Вих.за діапазон",
      "  Out of Limits ",
      "Вых.за диапазон "
    };
    
    const uint8_t (*p_information)[MAX_COL_LCD + 1];
    
    enum _edition_stats edition = current_state_menu2.edition;
    if (edition == ED_WARNING_EDITION_BUSY) p_information = information_about_info;
    else if (edition == ED_WARNING_ENTER_ESC) p_information = information_about_out_of_range;
    else p_information = information_about_error;
    make_ekran_about_info( ((edition == ED_WARNING_ENTER_ESC) ? true : false), p_information);
  }
  else 
  {
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONFIGURATION][MAX_COL_LCD + 1] = 
    {
      {
        "      СЗС       ",
        "      ШГС       ",
        "       И        ",
        "      ИЛИ       ",
        "    Искл.ИЛИ    ",
        "       НЕ       ",
        "   МФ-Таймер    ",
        "   D-Триггер    ",
        "      ГПС       "
      },
      {
        "      СЗС       ",
        "      ШГС       ",
        "       І        ",
        "      АБО       ",
        "    Викл.АБО    ",
        "       НЕ       ",
        "   БФ-Таймер    ",
        "    D-Триґер    ",
        "      ГПС       "
      },
      {
        "      СЗС       ",
        "      ШГС       ",
        "      AND       ",
        "       OR       ",
        "      XOR       ",
        "      NOT       ",
        "    MF-Timer    ",
        "   D-Trigger    ",
        "      PSG       "
      },
      {
        "      СЗС       ",
        "      ШГС       ",
        "       И        ",
        "      ИЛИ       ",
        "    Искл.ИЛИ    ",
        "       НЕ       ",
        "   МФ-Таймер    ",
        "   D-Триггер    ",
        "      ГПС       "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);

    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    unsigned int first_symbol;
    uint32_t vaga, value;
  
    __CONFIG *p_current_config;
    if (current_state_menu2.edition == ED_VIEWING) p_current_config = &current_config_prt;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_current_config = &current_config;
    else p_current_config = &current_config_edit;
    size_t col_begin, col_end;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_ROW_FOR_CONFIGURATION)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений

          switch (index_in_ekran_tmp)
          {
          case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_alarm;

              break;
            }
          case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
            {
              unsigned int max_number_digit = max_number_digit_in_number(NUMBER_ANALOG_CANALES - 1);
              vaga = 1; //максимальний ваговий коефіцієнт
              for (unsigned int j = 0; j < (max_number_digit - 1); j++) vaga *= 10;
              col_begin = (MAX_COL_LCD - max_number_digit) >> 1;
              col_end = col_begin + max_number_digit - 1;

              value = p_current_config->n_group_alarm;

              break;
            }
          case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_and;

              break;
            }
          case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_or;

              break;
            }
          case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_xor;

              break;
            }
          case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_not;

              break;
            }
          case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_timer;

              break;
            }
          case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_trigger;

              break;
            }
          case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
            {
              vaga = 100; //максимальний ваговий коефіцієнт
              col_begin = COL_CONF_3DIGIT_BEGIN;
              col_end = COL_CONF_3DIGIT_END;

              value = p_current_config->n_meander;

              break;
            }
          default:
            {
              //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
              total_error_sw_fixed(77);
            }
          }
        }
        else
        {
          for (size_t j = 0; j < MAX_COL_LCD; j++)
          {
            if ((j < col_begin) || (j > col_end )) working_ekran[i][j] = ' ';
            else calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol);
          }
        }
      }
      else
        for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

      index_in_ekran++;
    }

    //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням
    current_state_menu2.position_cursor_y = ((position_temp << 1) + 1) & (MAX_ROW_LCD - 1);
    //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена користувачем
    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      int last_position_cursor_x = MAX_COL_LCD;
      switch (current_state_menu2.index_position)
      {
      case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
        {
          current_state_menu2.position_cursor_x = COL_CONF_3DIGIT_BEGIN;
          last_position_cursor_x = COL_CONF_3DIGIT_END;
          break;
        }
      case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
        {
          unsigned int max_number_digit = max_number_digit_in_number(NUMBER_ANALOG_CANALES - 1);
          col_begin = (MAX_COL_LCD - max_number_digit) >> 1;
          col_end = col_begin + max_number_digit - 1;

          current_state_menu2.position_cursor_x = col_begin;
          last_position_cursor_x = col_end;
          break;
        }
      default:
        {
          //Якщо сюди дійшла програма, значить відбулася недопустива помилка, тому треба зациклити програму, щоб вона пішла на перезагрузку
          total_error_sw_fixed(82);
        }
      }

      //Підтягуємо курсор до першого символу
      while (
             ((working_ekran[current_state_menu2.position_cursor_y][current_state_menu2.position_cursor_x + 1]) == ' ') && 
             (current_state_menu2.position_cursor_x < (last_position_cursor_x - 1))
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
    //Курсор мигає/не мигає
    if(current_state_menu2.edition <= ED_CAN_BE_EDITED) current_state_menu2.cursor_blinking_on = 0;
    else current_state_menu2.cursor_blinking_on = 1;
  }
  
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Натискування Enter у вікні Конфігурації
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_configuration(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
      case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
        {
          current_state_menu2.position_cursor_x = COL_CONF_3DIGIT_BEGIN;
          break;
        }
      case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
        {
          unsigned int max_number_digit = max_number_digit_in_number(NUMBER_ANALOG_CANALES - 1);
          int col_begin = (MAX_COL_LCD - max_number_digit) >> 1;

          current_state_menu2.position_cursor_x = col_begin;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      switch (current_state_menu2.index_position)
      {
      case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_alarm != current_config.n_alarm) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_group_alarm != current_config.n_group_alarm) 
          {
            if (check_data_setpoint(current_config_edit.n_group_alarm, 0, (NUMBER_ANALOG_CANALES - 1)) == 1)
              result = RPEDE_DATA_CHANGED_OK;
            else
              result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
          }
          break;
        }
      case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_and != current_config.n_and) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_or != current_config.n_or) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_xor != current_config.n_xor) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_not != current_config.n_not) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_timer != current_config.n_timer) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_trigger != current_config.n_trigger) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
        {
          if (current_config_edit.n_meander != current_config.n_meander) result = RPEDE_DATA_CHANGED_OK;
          break;
        }
      }
      
      if (result == RPEDE_DATA_CHANGED_OK)
      {
        //Треба виконати дії по зміні конфігурації
        __result_dym_mem_select result_1 = action_after_changing_of_configuration();
        if (result_1 == DYN_MEM_SELECT_OK) config_settings_modified |= MASKA_CHANGED_CONFIGURATION | MASKA_CHANGED_SETTINGS;
        else
        {
        
          result = (result_1 == DYN_MEM_NO_ENOUGH_MEM) ? RPEDE_DATA_CHANGED_WRONG_RETURN_OK : RPEDE_DATA_CHANGED_WRONG_RETURN_BAD;
          
          if (result == RPEDE_DATA_CHANGED_WRONG_RETURN_BAD) _SET_BIT(set_diagnostyka, ERROR_NO_FREE_DYNAMIC_MEMORY_BIT);
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
Натискування ESC у вікні Конфігурації
*/
/*****************************************************/
void press_esc_in_configuration(void)
{
  switch (current_state_menu2.index_position)
  {
  case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_alarm = current_config.n_alarm;
      break;
    }
  case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_group_alarm = current_config.n_group_alarm;
      break;
    }
  case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_and = current_config.n_and;
      break;
    }
  case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_or = current_config.n_or;
      break;
    }
  case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_xor = current_config.n_xor;
      break;
    }
  case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_not = current_config.n_not;
      break;
    }
  case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_timer = current_config.n_timer;
      break;
    }
  case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_trigger = current_config.n_trigger;
      break;
    }
  case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
    {
      current_config_edit.n_meander = current_config.n_meander;
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//Зміна Конфігурації
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_DOWN) - натснуто кнопку вниз
(1 << BIT_KEY_UP)   - атиснуто кнопку вверх
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_configuration(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    uint32_t *p_value = NULL;
    unsigned int col_end;
    switch (current_state_menu2.index_position)
    {
    case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_alarm;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_group_alarm;
        unsigned int max_number_digit = max_number_digit_in_number(NUMBER_ANALOG_CANALES - 1);
        col_end = ((MAX_COL_LCD + max_number_digit) >> 1) - 1;/*після спрощення цього виразу ((MAX_COL_LCD - max_number_digit) >> 1) + max_number_digit - 1*/
        break;
      }
    case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_and;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_or;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_xor;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_not;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_timer;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_trigger;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
      {
        p_value = &current_config_edit.n_meander;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    }
    
    if (p_value != NULL)
    {
      *p_value = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), *p_value, 0, 0, col_end, 1);
    }
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    int col_begin, col_end;
    switch (current_state_menu2.index_position)
    {
    case (ID_FB_ALARM - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_AND - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_OR - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_XOR - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_NOT - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_TIMER - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_TRIGGER - _ID_FB_FIRST_VAR_CHANGED):
    case (ID_FB_MEANDER - _ID_FB_FIRST_VAR_CHANGED):
      {
        col_begin = COL_CONF_3DIGIT_BEGIN;
        col_end = COL_CONF_3DIGIT_END;
        break;
      }
    case (ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR_CHANGED):
      {
        unsigned int max_number_digit = max_number_digit_in_number(NUMBER_ANALOG_CANALES - 1);
        col_begin = (MAX_COL_LCD - max_number_digit) >> 1;
        col_end = col_begin + max_number_digit - 1;
        break;
      }
    }
    
    if (action & (1 << BIT_KEY_LEFT ))
    {
      current_state_menu2.position_cursor_x--;
      if ((current_state_menu2.position_cursor_x < col_begin) ||
          (current_state_menu2.position_cursor_x > col_end))
        current_state_menu2.position_cursor_x = col_end;
    }
    else
    {
      current_state_menu2.position_cursor_x++;
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
