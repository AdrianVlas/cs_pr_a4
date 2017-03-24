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
void move_into_param_list_logical_nodes(unsigned int action, int max_row)
{
  __CONFIG *p_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
  unsigned int logical_node_shown[NUMBER_ALL_BLOCKS] = 
  {
    true,
    ((p_config->n_input*0                   ) != 0),
    ((p_config->n_output*OUTPUT_SIGNALS_IN  ) != 0),
    ((p_config->n_led*LED_SIGNALS_IN        ) != 0),
    ((p_config->n_alarm*ALARM_SIGNALS_IN    ) != 0),
    ((p_config->n_group_alarm*0             ) != 0),
    ((p_config->n_and*AND_SIGNALS_IN        ) != 0),
    ((p_config->n_or*OR_SIGNALS_IN          ) != 0),
    ((p_config->n_xor*2                     ) != 0),
    ((p_config->n_not*1                     ) != 0),
    ((p_config->n_timer*TIMER_SIGNALS_IN    ) != 0),
    ((p_config->n_trigger*TRIGGER_SIGNALS_IN) != 0),
    ((p_config->n_meander*0                 ) != 0)
  };
  
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position++;
    do
    {
      if (current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
      while (logical_node_shown[current_state_menu2.index_position] != true)
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
      while (logical_node_shown[current_state_menu2.index_position] != true)
      {
        if(--current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - 1;
      }
    }
    while (current_state_menu2.index_position < 0);
  }
}
/*****************************************************/

/*****************************************************/
//Формуємо екран
/*****************************************************/
void make_ekran_param_list_logical_node(void)
{
  __CONFIG *p_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
  unsigned int logical_node_shown[NUMBER_ALL_BLOCKS] = 
  {
    true,
    ((p_config->n_input*0                   ) != 0),
    ((p_config->n_output*OUTPUT_SIGNALS_IN  ) != 0),
    ((p_config->n_led*LED_SIGNALS_IN        ) != 0),
    ((p_config->n_alarm*ALARM_SIGNALS_IN    ) != 0),
    ((p_config->n_group_alarm*0             ) != 0),
    ((p_config->n_and*AND_SIGNALS_IN        ) != 0),
    ((p_config->n_or*OR_SIGNALS_IN          ) != 0),
    ((p_config->n_xor*2                     ) != 0),
    ((p_config->n_not*1                     ) != 0),
    ((p_config->n_timer*TIMER_SIGNALS_IN    ) != 0),
    ((p_config->n_trigger*TRIGGER_SIGNALS_IN) != 0),
    ((p_config->n_meander*0                 ) != 0)
  };
  
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES][MAX_COL_LCD + 1] = 
  {
    {
      " Общий блок     ",
      " Д.Входы        ",
      " В.Реле         ",
      " Светоиндикаторы",
      " СЗС            ",
      " ШГС            ",
      " И              ",
      " ИЛИ            ",
      " Искл.ИЛИ       ",
      " НЕ             ",
      " МФ-Таймер      ",
      " D-Триггер      ",
      " ГПС            "
    },
    {
      " Загальний блок ",
      " Д.Входи        ",
      " В.Реле         ",
      " Світоіндикатори",
      " СЗС            ",
      " ШГС            ",
      " І              ",
      " АБО            ",
      " Викл.АБО       ",
      " НЕ             ",
      " МФ-Таймер      ",
      " D-Триґер       ",
      " ГПС            "
    },
    {
      " General block  ",
      " D.Inputs       ",
      " O.Relays       ",
      " LEDs           ",
      " СЗС            ",
      " ШГС            ",
      " AND            ",
      " OR             ",
      " XOR            ",
      " NOT            ",
      " MF-Timer       ",
      " D-Trigger      ",
      " PSG            "
    },
    {
      " Общий блок     ",
      " Д.Входы        ",
      " В.Реле         ",
      " Светоиндикаторы",
      " СЗС            ",
      " ШГС            ",
      " И              ",
      " ИЛИ            ",
      " Искл.ИЛИ       ",
      " НЕ             ",
      " МФ-Таймер      ",
      " D-Триггер      ",
      " ГПС            "
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  unsigned int additional_current = 0;
  unsigned int position_temp = current_state_menu2.index_position;

  uint8_t name_string_tmp[MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES][MAX_COL_LCD + 1];
  for(size_t index_1 = 0; index_1 < MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES; index_1++)
  {
    if (logical_node_shown[index_1] != true)
    {
      if ((index_1 - additional_current) < position_temp) position_temp--;
      additional_current++;

      for(size_t index_2 = 0; index_2 < MAX_COL_LCD; index_2++)
      {
        name_string_tmp[MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES - additional_current][index_2] = ' ';
      }
      name_string_tmp[MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES - additional_current][MAX_COL_LCD] = '\0';
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
      working_ekran[i][j] = (index_in_ekran < (MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES - additional_current)) ? name_string_tmp[index_in_ekran][j] : ' ';
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
//
/*****************************************************/
/*****************************************************/
