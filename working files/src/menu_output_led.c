#include "header.h"

/*****************************************************/
//Формуємо екран відображення вікна відображення налаштувань виходів/світлоіндикаторів
/*****************************************************/
void make_ekran_control_output_led(void)
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
    const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_INDEX_CTRL_OUTPUT_LED][MAX_COL_LCD + 1] = 
    {
      {
        "  Норм./Триг.   ",
        "   Пост./Имп.   ",
        " Имп-Пр/Имп-Расш",
        "   Частота 1    ",
        "   Частота 2    "
      },
      {
        "  Норм./Триґ.   ",
        "   Пост./Імп.   ",
        " Імп-Пр/Імп-Росш",
        "   Частота 1    ",
        "   Частота 2    "
      },
      {
        "  Norm./Trig.   ",
        "  Const./Imp.   ",
        "  Imp-S/Imp-Ex  ",
        "   Frequency 1  ",
        "   Frequency 2  "
      },
      {
        "   Имп./Триг.   ",
        "   Норм./Имп.   ",
        " Имп-Пр/Имп-Расш",
        "   Частота 1    ",
        "   Частота 2    "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
    unsigned int position_temp = current_state_menu2.index_position;
    //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    unsigned int index_in_ekran = ((position_temp << 1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

    void *p_settings;
    if (current_state_menu2.edition == ED_VIEWING) 
    {
      if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
      {
        p_settings = &((((__LN_OUTPUT*)spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings);
      }
      else
      {
        p_settings = &((((__LN_LED*)spca_of_p_prt[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection)->settings);
      }
    }
    else if (current_state_menu2.edition == ED_CAN_BE_EDITED) 
    {
      if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
      {
        p_settings = (((__settings_for_OUTPUT*)sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      }
      else
      {
        p_settings = (((__settings_for_LED*)sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      }
    }
    else 
    {
      if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
      {
        p_settings = (((__settings_for_OUTPUT*)sca_of_p_edit[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      }
      else
      {
        p_settings = (((__settings_for_LED*)sca_of_p_edit[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      }
    }
  
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      unsigned int index_in_ekran_tmp = index_in_ekran >> 1;
    
      if (index_in_ekran_tmp < MAX_INDEX_CTRL_OUTPUT_LED)
      {
        if ((i & 0x1) == 0)
        {
          //У непарному номері рядку виводимо заголовок
          for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_in_ekran_tmp][j];
        }
        else
        {
          //У парному номері рядку виводимо значення
          if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_N_T)  
          {
            const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
            {
              {"   НОРМАЛЬНЫЙ   ", "   ТРИГГЕРНЫЙ   "},
              {"   НОРМАЛЬНИЙ   ", "   ТРИҐЕРНИЙ    "},
              {"     NORMAL     ", "    TRIGGER     "},
              {"   НОРМАЛЬНЫЙ   ", "   ТРИГГЕРНЫЙ   "}
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
            {
              {2, 2},
              {2, 2},
              {4, 3},
              {2, 2}
            };
          
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              working_ekran[i][j] = information[index_language][(((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->control : ((__settings_for_LED*)p_settings)->control) >> INDEX_CTRL_OUTPUT_LED_N_T) & 0x1][j];
            }
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][(((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->control : ((__settings_for_LED*)p_settings)->control) >> INDEX_CTRL_OUTPUT_LED_N_T) & 0x1];
            }
          }
          else if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_C_I)  
          {
            const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
            {
              {"   ПОСТОЯННЫЙ   ", "   ИМПУЛЬСНЫЙ   "},
              {"   ПОСТІЙНИЙ    ", "   ІМПУЛЬСНИЙ   "},
              {"    CONSTANT    ", "    IMPULSE     "},
              {"   ПОСТОЯННЫЙ   ", "   ИМПУЛЬСНЫЙ   "},
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
            {
              {2, 2},
              {2, 2},
              {3, 3},
              {2, 2}
            };
          
            for (size_t j = 0; j < MAX_COL_LCD; j++)
            {
              working_ekran[i][j] = information[index_language][(((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->control : ((__settings_for_LED*)p_settings)->control) >> INDEX_CTRL_OUTPUT_LED_C_I) & 0x1][j];
            }
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][(((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->control : ((__settings_for_LED*)p_settings)->control) >> INDEX_CTRL_OUTPUT_LED_C_I) & 0x1];
            }
          }
          else if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_SI_EI)  
          {
            const uint8_t information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
            {
              {"  ИМП.ПРОСТОЙ   ", " ИМП.РАСШИРЕННЫЙ"},
              {"  ІМП.ПРОСТИЙ   ", " ІМП.РОЗШИРЕНИЙ "},
              {"   IMP.SIMPLE   ", "  IMP.EXPANDED  "},
              {"  ИМП.ПРОСТОЙ   ", " ИМП.РАСШИРЕННЫЙ"},
            };
            const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
            {
              {1, 0},
              {1, 0},
              {2, 1},
              {1, 0}
            };
          
            for (size_t j = 0; j < MAX_COL_LCD; j++) 
            {
              working_ekran[i][j] = information[index_language][(((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->control : ((__settings_for_LED*)p_settings)->control) >> INDEX_CTRL_OUTPUT_LED_SI_EI) & 0x1][j];
            }
            if (position_temp == index_in_ekran_tmp)
            {
              current_state_menu2.position_cursor_x = cursor_x[index_language][(((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->control : ((__settings_for_LED*)p_settings)->control) >> INDEX_CTRL_OUTPUT_LED_SI_EI) & 0x1];
            }
          }
          else if (
                   (index_in_ekran_tmp >= INDEX_CTRL_OUTPUT_LED_MEANDER1) &&
                   (index_in_ekran_tmp <= INDEX_CTRL_OUTPUT_LED_MEANDER2)
                  )   
          {
            unsigned int param_input;
            if (index_in_ekran_tmp == INDEX_CTRL_OUTPUT_LED_MEANDER1)
              param_input = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->param[OUTPUT_MEANDER1] : ((__settings_for_LED*)p_settings)->param[LED_MEANDER1];
            else
              param_input = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings)->param[OUTPUT_MEANDER2] : ((__settings_for_LED*)p_settings)->param[LED_MEANDER2];

            if (param_input == 0)
            {
              const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
              {
                "     Пусто      ",
                "     Пусто      ",
                "     Empty      ",
                "     Пусто      "
              };
              const uint32_t cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 4, 4, 4};

              for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
              if (position_temp == index_in_ekran_tmp)
              {
                current_state_menu2.position_cursor_x = cursor_x_error[index_language];
              }
            }
            else
            {
              unsigned int id_input   = (param_input >> SFIFT_PARAM_ID ) & MASKA_PARAM_ID ;
              unsigned int n_input    = (param_input >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
              unsigned int out_input  = (param_input >> SFIFT_PARAM_OUT) & MASKA_PARAM_OUT;
            
              if ((id_input != ID_FB_MEANDER) || (out_input != (MEANDER_OUT + 1)))
              {
                const uint8_t information_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
                {
                  "     Ошибка     ",
                  "    Помилка     ",
                  "     Error      ",
                  "     Ошибка     "
                };
                const uint32_t cursor_x_error[MAX_NAMBER_LANGUAGE] = {4, 3, 4, 4};

                for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = information_error[index_language][j];
                if (position_temp == index_in_ekran_tmp)
                {
                  current_state_menu2.position_cursor_x = cursor_x_error[index_language];
                }
              }
              else
              {
                const uint8_t value_name[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
                {
                  {"ГПС             "},
                  {"ГПС             "},
                  {"MEANDER         "},
                  {"ГПС             "},
                };
                const unsigned int number_symbols_in_name[MAX_NAMBER_LANGUAGE] = {3, 3, 7, 3};
                unsigned int number_symbols_in_name_tmp = number_symbols_in_name[index_language];
          
                unsigned int number_digit = max_number_digit_in_number(n_input);
                unsigned int empty_before = (MAX_COL_LCD - number_symbols_in_name_tmp - number_digit) >> 1;

                for (size_t j = 0; j < MAX_COL_LCD; j++)
                {
                  if ((j < empty_before) || (j >= (empty_before + number_symbols_in_name_tmp + number_digit))) working_ekran[i][j] = ' ';
                  else if (j < (empty_before + number_symbols_in_name_tmp)) working_ekran[i][j] = value_name[index_language][j - empty_before];
                  else
                  {
                    /*
                    Заповнюємо значення зправа  на ліво
                    індекс = (empty_before + number_symbols_in_name_tmp) + number_digit - 1 - (j - (empty_before + number_symbols_in_name_tmp)) =
                    = (empty_before + number_symbols_in_name_tmp) + number_digit - 1 - j + (empty_before + number_symbols_in_name_tmp) =
                    = 2(empty_before + number_symbols_in_name_tmp) + number_digit - 1 - j =
                    */
                    working_ekran[i][2*(empty_before + number_symbols_in_name_tmp) + number_digit - 1 - j] = (n_input % 10) + 0x30;
                    n_input /= 10;
                  }
                }
                if (position_temp == index_in_ekran_tmp)
                {
                  current_state_menu2.position_cursor_x = empty_before - 1;
                }
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
    //Обновити повністю весь екран
  }
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Натискування Enter у вікні відображення налаштувань виходів/світлоіндикаторів
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_control_output_led(void)
{
  enum _result_pressed_enter_during_edition result = RPEDE_NONE;
  switch (current_state_menu2.edition)
  {
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      
      void *p_settings_edit;
      void *p_settings_cont;
      if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
      {
        p_settings_edit = (((__settings_for_OUTPUT*)sca_of_p_edit[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
        p_settings_cont = (((__settings_for_OUTPUT*)sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      }
      else
      {
        p_settings_edit = (((__settings_for_LED*)sca_of_p_edit[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
        p_settings_cont = (((__settings_for_LED*)sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
      }

      if (
          (
           ((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_cont)->control : ((__settings_for_LED*)p_settings_cont)->control) != 
           ((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_edit)->control : ((__settings_for_LED*)p_settings_edit)->control)
          )
          ||
          (
           ((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_cont)->param[OUTPUT_MEANDER1] : ((__settings_for_LED*)p_settings_cont)->param[LED_MEANDER1]) != 
           ((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER1] : ((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER1])
          ) 
          ||
          (
           ((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_cont)->param[OUTPUT_MEANDER2] : ((__settings_for_LED*)p_settings_cont)->param[LED_MEANDER2]) != 
           ((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER2] : ((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER2])
          ) 
         )   
      {
        if (
            ((((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_edit)->control : ((__settings_for_LED*)p_settings_edit)->control) & ((uint32_t)(~MASKA_CTRL_OUTPUT_LED_M2))) == 0) &&
            (((((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER1] : ((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER1]) >> SFIFT_PARAM_N ) & MASKA_PARAM_N) <= current_config.n_meander) &&
            (((((current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? ((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER2] : ((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER2]) >> SFIFT_PARAM_N ) & MASKA_PARAM_N) <= current_config.n_meander)
           )   
        {
          if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
          {
            ((__settings_for_OUTPUT*)p_settings_cont)->control = ((__settings_for_OUTPUT*)p_settings_edit)->control;
            ((__settings_for_OUTPUT*)p_settings_cont)->param[OUTPUT_MEANDER1] = ((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER1];
            ((__settings_for_OUTPUT*)p_settings_cont)->param[OUTPUT_MEANDER2] = ((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER2];
          }
          else
          {
            ((__settings_for_LED*)p_settings_cont)->control = ((__settings_for_LED*)p_settings_edit)->control;
            ((__settings_for_LED*)p_settings_cont)->param[LED_MEANDER1] = ((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER1];
            ((__settings_for_LED*)p_settings_cont)->param[LED_MEANDER2] = ((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER2];
          }

          
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
Натискування ESC у вікні налаштувань виходів/світлоіндикаторів
*/
/*****************************************************/
void press_esc_in_control_output_led(void)
{
  if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
  {
    __settings_for_OUTPUT *p_settings_edit = (((__settings_for_OUTPUT*)sca_of_p_edit[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    __settings_for_OUTPUT *p_settings_cont = (((__settings_for_OUTPUT*)sca_of_p[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);

    p_settings_edit->control = p_settings_cont->control;
    p_settings_edit->param[OUTPUT_MEANDER1] = p_settings_cont->param[OUTPUT_MEANDER1];
    p_settings_edit->param[OUTPUT_MEANDER2] = p_settings_cont->param[OUTPUT_MEANDER2];
  }
  else
  {
    __settings_for_LED *p_settings_edit = (((__settings_for_LED*)sca_of_p_edit[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
    __settings_for_LED *p_settings_cont = (((__settings_for_LED*)sca_of_p[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);

    p_settings_edit->control = p_settings_cont->control;
    p_settings_edit->param[LED_MEANDER1] = p_settings_cont->param[LED_MEANDER1];
    p_settings_edit->param[LED_MEANDER2] = p_settings_cont->param[LED_MEANDER2];
  }

}
/*****************************************************/

/*****************************************************/
//Зміна налаштувань бінарної інформації для виходів/світлоіндикаторів
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_control_output_led(unsigned int action)
{
  //Вводимо число у відповідне поле
  void *p_settings_edit;
  if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
  {
    p_settings_edit = (((__settings_for_OUTPUT*)sca_of_p_edit[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  }
  else
  {
    p_settings_edit = (((__settings_for_LED*)sca_of_p_edit[ID_FB_LED - _ID_FB_FIRST_VAR]) + current_state_menu2.number_selection);
  }

  if (
      ((action & (1 << BIT_KEY_LEFT )) != 0) ||
      ((action & (1 << BIT_KEY_RIGHT)) != 0)
     )   
  {
    int16_t index_position = current_state_menu2.index_position;
    if (
        (index_position == INDEX_CTRL_OUTPUT_LED_N_T) ||
        (index_position == INDEX_CTRL_OUTPUT_LED_C_I) ||
        (index_position == INDEX_CTRL_OUTPUT_LED_SI_EI)
       )  
    {
      if (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL)
      {
        ((__settings_for_OUTPUT*)p_settings_edit)->control ^= (uint32_t)(1 << index_position);
      }
      else
      {
        ((__settings_for_LED*)p_settings_edit)->control ^= (uint32_t)(1 << index_position);
      }
    }
    else 
    {
      int32_t n_meander = current_config.n_meander;
      if (n_meander > 0)
      {
        uint32_t *param_input;
        if (index_position == INDEX_CTRL_OUTPUT_LED_MEANDER1)
        {
          param_input = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? &(((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER1]) : &(((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER1]);
        }
        else
        {
          param_input = (current_state_menu2.current_level == CTRL_OUTPUT_MENU2_LEVEL) ? &(((__settings_for_OUTPUT*)p_settings_edit)->param[OUTPUT_MEANDER2]) : &(((__settings_for_LED*)p_settings_edit)->param[LED_MEANDER2]);
        }
      
        int n_input = ((*param_input) >> SFIFT_PARAM_N  ) & MASKA_PARAM_N  ;
        if ((action & (1 << BIT_KEY_RIGHT)) != 0) n_input++;
        else n_input--;
      
        if  (n_input < 1) n_input = n_meander;
        else if (n_input > n_meander) n_input = 1;
        *param_input = ((ID_FB_MEANDER & MASKA_PARAM_ID) << SFIFT_PARAM_ID) | ((n_input & MASKA_PARAM_N) << SFIFT_PARAM_N) | (((MEANDER_OUT + 1) & MASKA_PARAM_OUT) << SFIFT_PARAM_OUT);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
