#include "header.h"

/*****************************************************/
//Формуємо екран відображення вікна відображення налаштувувань для дискретного вхроду
/*****************************************************/
void make_ekran_control_group_alarm(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_GROUP_ALARM][MAX_COL_LCD + 1] = 
    {
      {
        "   Состояние    ",
        "  Контроль ШГС  ",
        "      Ток       "
      },
      {
        "      Стан      ",
        "  Контроль ШГС  ",
        "     Струм      "
      },
      {
        "      Стан      ",
        "  Контроль ШГС  ",
        "    Current     "
      },
      {
        "   Состояние    ",
        "  Контроль ШГС  ",
        "      Ток       "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    __settings_for_GROUP_ALARM *p_settings;
    if (current_state_menu2.edition == ED_VIEWING) p_settings = &((((__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings);
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_settings = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    else p_settings = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < MAX_INDEX_CTRL_GROUP_ALARM)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          //У парному номері рядку виводимо значення
          if (
              (index_in_ekran_tmp == INDEX_CTRL_GROUP_ALARM_STATE) ||
              (index_in_ekran_tmp == INDEX_CTRL_GROUP_ALARM_CTRL_STATE)  
             ) 
          {
            const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
            {
              {"     Откл.      ", "      Вкл.      "},
              {"     Вимк.      ", "     Ввімк.     "},
              {"      Off       ", "       On       "},
              {"     Сљнд.      ", "     Косу.      "}
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
            {
              {4, 5},
              {4, 4},
              {5, 6},
              {4, 4}
            };
          
            for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(p_settings->control >> index_in_ekran_tmp) & 0x1][j];
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][(p_settings->control >> index_in_ekran_tmp) & 0x1];
            }
          }
          else if (index_in_ekran_tmp == INDEX_CTRL_GROUP_ALARM_I)
          {
            uint32_t I_number = (p_settings->analog_input_control >> group_alarm_analog_ctrl_patten[index_in_ekran_tmp - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0]) & ((1 << group_alarm_analog_ctrl_patten[index_in_ekran_tmp - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1);
            if (I_number == 0)
            {
              const uint8_t information_empty[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
              {
                "      Нет       ",
                "      Нема      ",
                "      None      ",
                "      Нет       "
              };
              const uint32_t cursor_x_empty[MAX_NAMBER_LANGUAGE] = {5, 5, 5, 5};

              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_empty[index_language][j];
              if (position_temp == index_in_ekran_tmp)
              {
                current_state_menu2.position_cursor_x = cursor_x_empty[index_language];
              }
            }
            else
            {
              unsigned int max_number_digit = max_number_digit_in_number(I_number);
              unsigned int first_symbol = 0;
              uint32_t vaga = 1; //максимальний ваговий коефіцієнт
              for (unsigned int j = 0; j < (max_number_digit - 1); j++) vaga *= 10;
              intptr_t col_begin = (MAX_COL_LCD - 1/*I*/ - max_number_digit) >> 1;
              intptr_t col_end = col_begin + 1/*I*/ + max_number_digit - 1;

              for (intptr_t j = 0; j < MAX_COL_LCD; j++)
              {
                if ((j < col_begin) || (j > col_end))  working_ekran[i][j] = ' ';
                else if (j == col_begin)  working_ekran[i][j] = 'I';
                else calc_int_symbol_and_put_into_working_ekran((working_ekran[i] + j), &I_number, &vaga, &first_symbol);
              }

              if (position_temp == index_in_ekran_tmp)
              {
                current_state_menu2.position_cursor_x = col_begin - 1;
              }
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
enum _result_pressed_enter_during_edition press_enter_in_control_group_alarm(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      __settings_for_GROUP_ALARM *p_settings_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      __settings_for_GROUP_ALARM *p_settings_cont = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      if (
          (p_settings_cont->control != p_settings_edit->control) ||
          (p_settings_cont->analog_input_control != p_settings_edit->analog_input_control) 
         )   
      {
        if (
            ((p_settings_edit->control & ((uint32_t)(~MASKA_CTRL_GROUP_ALARM_M2))) == 0) &&
#if NUMBER_ANALOG_CANALES <= 1
            (p_settings_edit->analog_input_control == 0) 
#else
            (p_settings_edit->analog_input_control <= (NUMBER_ANALOG_CANALES - 1))  
#endif
           )   
        {
          p_settings_cont->control = p_settings_edit->control;
          p_settings_cont->analog_input_control = p_settings_edit->analog_input_control;
          
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
Натискування ESC
*/
/*****************************************************/
void press_esc_in_control_group_alarm(void)
{
  __settings_for_GROUP_ALARM *p_settings_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  __settings_for_GROUP_ALARM *p_settings_cont = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  p_settings_edit->control = p_settings_cont->control;
  p_settings_edit->analog_input_control = p_settings_cont->analog_input_control;
}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань бінарної інформації
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_control_group_alarm(unsigned int action)
{
  //Вводимо число у відповідне поле
  __settings_for_GROUP_ALARM *p_control_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int index_position = current_state_menu2.index_position;
    if (
        (index_position == INDEX_CTRL_GROUP_ALARM_STATE) ||
        (index_position == INDEX_CTRL_GROUP_ALARM_CTRL_STATE)  
       ) 
    {
      p_control_edit->control ^= (uint32_t)(1 << index_position);
    }
    else if  (index_position == INDEX_CTRL_GROUP_ALARM_I)
    {
      uint32_t maska = (1 << group_alarm_analog_ctrl_patten[index_position - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][1]) - 1;
      uint32_t shift = group_alarm_analog_ctrl_patten[index_position - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][0];

      int32_t data_tmp = (p_control_edit->analog_input_control >> shift) & maska;
      if ((action & (1 << BIT_KEY_RIGHT)) != 0) data_tmp++;
      else data_tmp--;
    
      int32_t min_data, max_data;
#if NUMBER_ANALOG_CANALES <= 1
      min_data = max_data = 0;
#else
      min_data = 1;
      max_data = NUMBER_ANALOG_CANALES - 1;
#endif

      if (data_tmp < min_data) data_tmp = max_data;
      else if (data_tmp > max_data) data_tmp = min_data;
    
      p_control_edit->analog_input_control = (p_control_edit->analog_input_control & ((uint32_t)(~(maska << shift)))) | (data_tmp << shift);
    }
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення часових параметнів для дискретного входу
/*****************************************************/
void make_ekran_delay_group_alarm(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][GROUP_ALARM_SET_DELAYS][MAX_COL_LCD + 1] = 
    {
      {
        "   T Задержки   ",
      },
      {
        "   T Затримки   ",
      },
      {
        "   T Задержки   ",
      },
      {
        "   T Задержки   ",
      }
    };
    
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
  
    int32_t *p_set_delay;
    if (current_state_menu2.edition == ED_VIEWING) p_set_delay = (((__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings.set_delay;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_set_delay = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    else p_set_delay = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    size_t col_begin, col_end, col_comma;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < GROUP_ALARM_SET_DELAYS)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений

          switch (index_in_ekran_tmp)
          {
          case GROUP_ALARM_SET_DELAY_DELAY:
            {
              vaga = 10000; //максимальний ваговий коефіцієнт
              col_begin = COL_DELAY_GROUP_ALARM_DELAY_BEGIN;
              col_end = COL_DELAY_GROUP_ALARM_DELAY_END;
              col_comma = COL_DELAY_GROUP_ALARM_DELAY_COMMA;
            
              value = p_set_delay[GROUP_ALARM_SET_DELAY_DELAY];
            
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
      case GROUP_ALARM_SET_DELAY_DELAY:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_GROUP_ALARM_DELAY_BEGIN;
          last_position_cursor_x = COL_DELAY_GROUP_ALARM_DELAY_END;
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
enum _result_pressed_enter_during_edition press_enter_in_delay_group_alarm(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case GROUP_ALARM_SET_DELAY_DELAY:
        {
          current_state_menu2.position_cursor_x = COL_DELAY_GROUP_ALARM_DELAY_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_set_delay_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
      int32_t *p_set_delay_cont = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
      switch (current_state_menu2.index_position)
      {
      case GROUP_ALARM_SET_DELAY_DELAY:
        {
          if (p_set_delay_cont[GROUP_ALARM_SET_DELAY_DELAY] != p_set_delay_edit[GROUP_ALARM_SET_DELAY_DELAY]) 
          {
            if (check_data_setpoint(p_set_delay_edit[GROUP_ALARM_SET_DELAY_DELAY], TIMEOUT_GROUP_ALARM_DELAY_MIN, TIMEOUT_GROUP_ALARM_DELAY_MAX) == 1)
            {
              p_set_delay_cont[GROUP_ALARM_SET_DELAY_DELAY] = p_set_delay_edit[GROUP_ALARM_SET_DELAY_DELAY];
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
void press_esc_in_delay_group_alarm(void)
{
  int32_t *p_set_delay_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
  int32_t *p_set_delay_cont = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;

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
void change_delay_group_alarm(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    int32_t *p_value = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->set_delay;
    unsigned int col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case GROUP_ALARM_SET_DELAY_DELAY:
      {
        col_end = COL_DELAY_GROUP_ALARM_DELAY_END;
        col_comma = COL_DELAY_GROUP_ALARM_DELAY_COMMA;
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
    case GROUP_ALARM_SET_DELAY_DELAY:
      {
        col_begin = COL_DELAY_GROUP_ALARM_DELAY_BEGIN;
        col_end = COL_DELAY_GROUP_ALARM_DELAY_END;
        col_comma = COL_DELAY_GROUP_ALARM_DELAY_COMMA;
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
//Формуємо екран відображення уставок для ШГС
/*****************************************************/
void make_ekran_pickup_group_alarm(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][GROUP_ALARM_PICKUPS][MAX_COL_LCD + 1] = 
    {
      {
        "       ‰I       "
      },
      {
        "       ‰I       "
      },
      {
        "       ‰I       "
      },
      {
        "       ‰I       "
      }
    };
    
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
    unsigned int first_symbol;
    uint32_t vaga, value;
  
    int32_t *p_set_pickup;
    if (current_state_menu2.edition == ED_VIEWING) p_set_pickup = (((__LN_GROUP_ALARM*)spca_of_p_prt[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings.pickup;
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) p_set_pickup = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;
    else p_set_pickup = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;
    size_t col_begin, col_end, col_comma;
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
      if (index_in_ekran_tmp < GROUP_ALARM_PICKUPS)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений

          switch (index_in_ekran_tmp)
          {
          case GROUP_ALARM_SET_DELAY_DELAY:
            {
              vaga = 1000; //максимальний ваговий коефіцієнт
              col_begin = COL_PICKUP_GROUP_ALARM_DELTA_I_BEGIN;
              col_end = COL_PICKUP_GROUP_ALARM_DELTA_I_END;
              col_comma = COL_PICKUP_GROUP_ALARM_DELTA_I_COMMA;
            
              value = p_set_pickup[GROUP_ALARM_PICKUP_DELTA_I];
            
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
            else if (j == (col_end + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_A];
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
      case GROUP_ALARM_SET_DELAY_DELAY:
        {
          current_state_menu2.position_cursor_x = COL_PICKUP_GROUP_ALARM_DELTA_I_BEGIN;
          last_position_cursor_x = COL_PICKUP_GROUP_ALARM_DELTA_I_END;
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
Натискування Enter у вікні відображення уставок для ШГС
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_pickup_group_alarm(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
  case ED_CAN_BE_EDITED:
    {
      switch (current_state_menu2.index_position)
      {
      case GROUP_ALARM_PICKUP_DELTA_I:
        {
          current_state_menu2.position_cursor_x = COL_PICKUP_GROUP_ALARM_DELTA_I_BEGIN;
          break;
        }
      }
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      int32_t *p_set_pickup_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;
      int32_t *p_set_pickup_cont = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;
      switch (current_state_menu2.index_position)
      {
      case GROUP_ALARM_PICKUP_DELTA_I:
        {
          if (p_set_pickup_cont[GROUP_ALARM_PICKUP_DELTA_I] != p_set_pickup_edit[GROUP_ALARM_PICKUP_DELTA_I]) 
          {
            if (check_data_setpoint(p_set_pickup_edit[GROUP_ALARM_PICKUP_DELTA_I], PICKUP_ALARM_DELTA_I_MIN, PICKUP_ALARM_DELTA_I_MAX) == 1)
            {
              p_set_pickup_cont[GROUP_ALARM_PICKUP_DELTA_I] = p_set_pickup_edit[GROUP_ALARM_PICKUP_DELTA_I];
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
Натискування ESC у вікні уставок для ШГС
*/
/*****************************************************/
void press_esc_in_pickup_group_alarm(void)
{
  int32_t *p_set_pickup_edit = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;
  int32_t *p_set_pickup_cont = (((__settings_for_GROUP_ALARM*)sca_of_p[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;

  int index = current_state_menu2.index_position;
  p_set_pickup_edit[index] = p_set_pickup_cont[index];
}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань уставок для ШГС
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_DOWN) - натснуто кнопку вниз
(1 << BIT_KEY_UP)   - атиснуто кнопку вверх
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_pickup_group_alarm(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    int32_t *p_value = (((__settings_for_GROUP_ALARM*)sca_of_p_edit[ID_FB_GROUP_ALARM - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->pickup;
    unsigned int col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case GROUP_ALARM_PICKUP_DELTA_I:
      {
        col_end = COL_PICKUP_GROUP_ALARM_DELTA_I_END;
        col_comma = COL_PICKUP_GROUP_ALARM_DELTA_I_COMMA;
        break;
      }
    }
    
    intptr_t index = current_state_menu2.index_position;
    p_value[index] = edit_setpoint(((action & (1 << BIT_KEY_UP)) != 0), p_value[index], 1, col_comma, col_end, 1);
  }
  else if (
           ((action & (1 << BIT_KEY_LEFT )) != 0) ||
           ((action & (1 << BIT_KEY_RIGHT)) != 0)
          )   
  {
    int col_begin, col_end, col_comma;
    switch (current_state_menu2.index_position)
    {
    case GROUP_ALARM_PICKUP_DELTA_I:
      {
        col_begin = COL_PICKUP_GROUP_ALARM_DELTA_I_BEGIN;
        col_end = COL_PICKUP_GROUP_ALARM_DELTA_I_END;
        col_comma = COL_PICKUP_GROUP_ALARM_DELTA_I_COMMA;
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
