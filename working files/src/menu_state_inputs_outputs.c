#include "header.h"

#define ROWS_ONE_PART   2

/*****************************************************/
//Функція визначення, скільки розрядів є у числі
/*****************************************************/
unsigned int max_number_digit_in_number(int max_item)
{
  unsigned int number_digit = 1;
  while (max_item  >= 10)
  {
    number_digit++;
    max_item /= 10;
  }
  
  return number_digit;
}
/*****************************************************/


/*****************************************************/
/*
Функція переміщення по меню (без винятків і додаткових алгоритмів)

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_ekran_input_or_output(unsigned int action, int max_row_tmp)
{
  int max_row = DIV_TO_HIGHER(max_row_tmp, (MAX_COL_LCD/(max_number_digit_in_number(max_row_tmp) + 1))*(MAX_ROW_LCD/ROWS_ONE_PART));
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
    if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
  }
  else if (action & (1 << BIT_KEY_UP))
  {
    if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення заголовків станів входів-виходів
/*****************************************************/
void make_ekran_list_inputs_outputs(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_INPUT_OUTPUT_M2][MAX_COL_LCD + 1] = 
  {
    {
      " Сост.входов    ",
      " Сост.выходов   "
    },
    {
      " Стан входів    ",
      " Стан виходів   "
    },
    {
      " Inputs  state  ",
      " Outputs state  "
    },
    {
      " Кіріс жаfдайы  ",
      " Шыfыс жаfдайы  "
    }
  };
  int index_language = index_language_in_array(settings_fix_prt.language);
  
  unsigned int position_temp = current_state_menu2.index_position;
  unsigned int index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  //Копіюємо  рядки у робочий екран
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    for (size_t j = 0; j < MAX_COL_LCD; j++) 
    {
      working_ekran[i][j] =  (index_in_ekran < MAX_ROW_INPUT_OUTPUT_M2) ? name_string[index_language][index_in_ekran][j] : ' ';
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

/*******************************************************/
//Формуємо екрвн станів входів або виходів
/*******************************************************/
void make_ekran_state_inputs_or_outputs(void)
{
  unsigned int max_number_digit = max_number_digit_in_number(*current_state_menu2.p_max_row); 
  unsigned int number_inputs_or_outputs_in_row = MAX_COL_LCD/(max_number_digit + 1);
  
  unsigned int in_out = current_state_menu2.index_position*number_inputs_or_outputs_in_row*(MAX_ROW_LCD/ROWS_ONE_PART) + 1;
  unsigned int row = 0;
  while (row < MAX_ROW_LCD)
  {
    uint8_t name_string[ROWS_ONE_PART][MAX_COL_LCD + 1] = 
    {
      "                ",
      "                "
    };
  
    for (size_t i = 0; i < number_inputs_or_outputs_in_row; i++)
    {
      unsigned int value = in_out + i;
      for (size_t j = 0; j < max_number_digit; j++)
      {
        unsigned int digit = value % 10;
        value /= 10;
      
        name_string[0][i*(max_number_digit + 1) + (max_number_digit + 1 - 1) - j] = digit + 0x30;
        if (value == 0) break;
      }
    
      int _n = in_out + i - 1;
      if (current_state_menu2.current_level == INPUTS_MENU2_LEVEL)
      {
        __LN_INPUT *arr = (__LN_INPUT*)(spca_of_p_prt[ID_FB_INPUT - _ID_FB_FIRST_VAR]);
        value = arr[_n].active_state[INPUT_OUT >> 3] & (1 << (INPUT_OUT & ((1 << 3) - 1)));
      }
      else
      {
        __LN_OUTPUT *arr = (__LN_OUTPUT*)(spca_of_p_prt[ID_FB_OUTPUT - _ID_FB_FIRST_VAR]);
        value = arr[_n].active_state[OUTPUT_OUT >> 3] & (1 << (OUTPUT_OUT & ((1 << 3) - 1)));
      }
      name_string[1][i*(max_number_digit + 1) + (max_number_digit + 1 - 1)] = (value != 0) +  + 0x30;
      if ((_n + 1) >= *current_state_menu2.p_max_row ) break;
    }
  
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < ROWS_ONE_PART; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати
      for (size_t j = 0; j < MAX_COL_LCD; j++)
      {
        working_ekran[row + i][j] = name_string[i][j];
      }
    }
    
    in_out += number_inputs_or_outputs_in_row*(MAX_ROW_LCD/ROWS_ONE_PART);
    row += ROWS_ONE_PART;
  }

  //Відображення курору по вертикалі
  current_state_menu2.position_cursor_x = 0;
  //Відображення курору по вертикалі
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

#undef ROWS_ONE_PART  
