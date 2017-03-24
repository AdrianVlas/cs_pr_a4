#include "header.h"

/*****************************************************/
//������� ���� � ��� ����������� �� ���� ��������
/*****************************************************/
void main_manu_function_ver2(void)
{
  //���������� �� ����� ������ ���������
  if (current_state_menu2.edition == ED_ERROR) 
  {
    const uint8_t name_string_error[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
    {
      {
        " ���.���.������.",
        " �������.������ "
      },
      {
        " ���.���.������.",
        " �������.������ "
        ""
      },
      {
        " ���.���.������.",
        " Restart device "
      },
      {
        " ���.���.������.",
        " �������.������ "
      }
    };
    int index_language = index_language_in_array(select_struct_settings_fix()->language);
    
    //�������  ����� � ������� �����
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i < 2) ? name_string_error[index_language][i][j] : ' ';
    }
  
    //������ ���������
    current_state_menu2.cursor_on = 0;
    //������ �� ����
    current_state_menu2.cursor_blinking_on = 0;
    //�������� ������� ���� �����
    current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
  }
  else if (new_state_keyboard !=0)
  {
//    static enum _edition_stats prev_edit;
    
    unsigned int max_row;
    if (current_state_menu2.p_max_row == NULL) max_row = current_state_menu2.max_row;
    else
    {
      if (current_state_menu2.max_row == 0) max_row = *current_state_menu2.p_max_row;
      else 
      {
        int number_ln =  *current_state_menu2.p_max_row;
        max_row = ((number_ln != 0) && (current_state_menu2.number_selection < number_ln))*current_state_menu2.max_row;
      }
    }

    if (max_row == 0) 
    {
      /*
      ���� ��� ������ ������������ (�� ������� ���� ������������ � ��������� ����) 
      ������� ����� ��������� ���� ����� ��� 0, �� ��������� � �������� ���� 
      (����� �� ��������� ������ ESC) � �� ���� ����, ���� �� �� ������� � ���� ����, 
      �� ����� ���������� ���� ����
      */
      new_state_keyboard = (1<<BIT_KEY_ESC);
    }
    
    unsigned int action;
    switch (current_state_menu2.current_level)
    {
    case PASSWORD_MENU2_LEVEL:
      {
        //����� ��� �������� ����� ������� � ����������� ���� ����
        static __PREVIOUS_STATE_CURSOR previous_state_cursor;
        //���� ��� �������� ��������� ������
        static unsigned int new_password;
        static unsigned int number_symbols;
        
        //������� �� ��� ���� �����������
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_KEY_RIGHT)|(1<<BIT_KEY_LEFT)|(1<<BIT_REWRITE);

        if (new_state_keyboard !=0)
        {
          //�������� ����� �� �������� ������
          if ( (action = (new_state_keyboard & (1<<BIT_REWRITE ))) !=0)
          {
            previous_state_cursor.position_cursor_x = current_state_menu2.position_cursor_x;              
            previous_state_cursor.cursor_on = current_state_menu2.cursor_on;
            previous_state_cursor.cursor_blinking_on = current_state_menu2.cursor_blinking_on;
            current_state_menu2.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
            position_in_current_level_menu2[current_state_menu2.current_level] = 1;
            //������� ����� ������ � ���� � ������� ������� �������� �������
            new_password = 0;
            number_symbols = 0;
            
            //������� ����� �����������
            p_menu_param_1 = &new_password;
            unsigned int view = false;
            p_menu_param_2 = &view;
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(100);
            }
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_UP   ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_DOWN ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_RIGHT))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_LEFT ))) !=0)
                  )   
          {
            unsigned int chosen_number;
            if      (action & (1<<BIT_KEY_UP   )) chosen_number = 1;
            else if (action & (1<<BIT_KEY_RIGHT)) chosen_number = 2;
            else if (action & (1<<BIT_KEY_DOWN )) chosen_number = 3;
            else if (action & (1<<BIT_KEY_LEFT )) chosen_number = 4;
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(44);
            }
              
            new_password = new_password*10 + chosen_number;
            number_symbols++;
            current_state_menu2.position_cursor_x++;
              
            //������� ����� �����������
            unsigned int view = true;
            p_menu_param_2 = &view;
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(101);
            }
              
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
              
            //���������� �� �� ��������� ����������� ������� ������� ��� ������ (4) � ���� �� ���, �� ����������� �������� ����
            if (number_symbols >= MAX_NUMBER_OF_SYMPOLS_IN_PASSWORD) new_state_keyboard |= (1<<BIT_KEY_ENTER);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) !=0)
          {
            //��������� ������ ENTER

            if (
                (new_password == settings_fix_prt.password_2) ||
                (
                 (new_password == settings_fix_prt.password_1) &&
                 (
                  (next_level_in_current_level_menu2[current_state_menu2.current_level] != SET_NEW_PASSWORD_MENU2_LEVEL)
                 ) 
                )   
               )   
            {
              //������ �������
              //������� ������ ���������� � ������ ���� � ��� �� ����� ��������� �� ���� � ����� ��� ���������� ����� �� ������
              if (next_level_in_current_level_menu2[current_state_menu2.current_level] != previous_level_in_current_level_menu2[current_state_menu2.current_level])
              {
                previous_level_in_current_level_menu2[next_level_in_current_level_menu2[current_state_menu2.current_level]] = previous_level_in_current_level_menu2[current_state_menu2.current_level];
              }
              current_state_menu2.current_level = next_level_in_current_level_menu2[current_state_menu2.current_level];

              if (new_password == settings_fix_prt.password_2)
              {
                if (
                    (current_state_menu2.current_level == TIME_MANU2_LEVEL) ||
                    (config_settings_modified == 0)
                   )   
                {
                  current_state_menu2.edition = ED_EDITION;
                  if (current_state_menu2.current_level != TIME_MANU2_LEVEL) 
                  {
                    //Գ�����, �� ������� ���� �������� "��������" �� ���� ������������ � �����������
                    config_settings_modified = MASKA_MENU_LOCKS;
                  }
                }
                else 
                {
                  if (current_state_menu2.current_level == SET_NEW_PASSWORD_MENU2_LEVEL)
                  {
                    current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
                  }
                  current_state_menu2.edition = ED_WARNING_EDITION_BUSY;
                }
              }
              else current_state_menu2.edition = ED_VIEWING;
            }
            else
            {
              //������ �� �������, ��� �� ������1 � �� ���� �������� �� ����� (��������� ���� "���� ������")
              enum _menu2_levels temp_value_level = current_state_menu2.current_level;
              do
              {
                temp_value_level = previous_level_in_current_level_menu2[temp_value_level];
              }
              while(
                    (new_password != settings_fix_prt.password_1) &&
                    (temp_value_level >= __BEGIN_SETTINGS_MENU2_LEVEL) &&
                    (temp_value_level <  __NEXT_AFTER_SETTINGS_MENU2_LEVEL)
                   );
              current_state_menu2.current_level = temp_value_level;
              
              current_state_menu2.edition = /*prev_edit*/ED_VIEWING;
              
              if ((config_settings_modified & MASKA_MENU_LOCKS) != 0 ) 
              {
                /*
                ���, ����������, ����� ������� ��� �� ����� �� ���� � ����, ��, 
                ���� �� ��� �������� "��������" �� ���� �����������+ ������������,
                 �� ����� �� ������ �� ��� �� �'��������
                */
                config_settings_modified = 0;
              }
            }
            current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.position_cursor_x = previous_state_cursor.position_cursor_x;
            current_state_menu2.cursor_on = previous_state_cursor.cursor_on;
            current_state_menu2.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
            new_level_menu();
              
            //����������� �� ���������� ������
            new_state_keyboard |= (1<<BIT_REWRITE);

            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //��������� ������ ESC

            //���������� � �������� ���� � ��������� ������� �����������
            current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
            current_state_menu2.position_cursor_x = previous_state_cursor.position_cursor_x;
            current_state_menu2.cursor_on = previous_state_cursor.cursor_on;
            current_state_menu2.cursor_blinking_on = previous_state_cursor.cursor_blinking_on;
            current_state_menu2.edition = /*prev_edit*/ED_VIEWING;
            new_level_menu();
              
            //����������� �� ���������� ������
            new_state_keyboard |= (1<<BIT_REWRITE);

            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
        break;
      }
    case SET_NEW_PASSWORD_MENU2_LEVEL:
      {
        //���� ��� �������� ��������� ������
        static int number_symbols;
        
        //������� �� ��� ���� �����������
        new_state_keyboard &= (1<<BIT_KEY_ENTER)|(1<<BIT_KEY_ESC)|(1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN)|(1<<BIT_KEY_RIGHT)|(1<<BIT_KEY_LEFT)|(1<<BIT_REWRITE);

        uint32_t *p_password_cont, *p_password_edit;
        switch (current_state_menu2.number_selection)
        {
        case INDEX_LIST_PASSWORDS_M2_1:
          {
            p_password_cont = &settings_fix.password_1;
            p_password_edit = &settings_fix_edit.password_1;
            break;
          }
        case INDEX_LIST_PASSWORDS_M2_2:
          {
            p_password_cont = &settings_fix.password_2;
            p_password_edit = &settings_fix_edit.password_2;
            break;
          }
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(108);
          }
        }
          
        if (
            ((action = (new_state_keyboard & (1 << BIT_KEY_ENTER))) !=0) ||
            ((action = (new_state_keyboard & (1 << BIT_KEY_ESC  ))) !=0)
           )   
        {
          if (action == (1 << BIT_KEY_ENTER))
          {
            if (*p_password_edit != *p_password_cont)
            {
              *p_password_cont = *p_password_edit;
              config_settings_modified |= MASKA_CHANGED_SETTINGS;
            }
          }
          else
          {
            *p_password_edit = *p_password_cont;
          }
            
          current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
          current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
          current_state_menu2.edition = ED_CAN_BE_EDITED;
          new_level_menu();
              
          //����������� �� ���������� ������
          new_state_keyboard |= (1<<BIT_REWRITE);

          //�������� �����������, �� ��������� ������ 
          new_state_keyboard &= (unsigned int)(~action);
        }
        else
        {
          if ((action = (new_state_keyboard & (1<<BIT_REWRITE ))) !=0)
          {
            current_state_menu2.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
            position_in_current_level_menu2[current_state_menu2.current_level] = 1;
            //������� ����� ������ � ���� � ������� ������� �������� �������

            number_symbols = 0;
            unsigned int temp_value = *p_password_edit;
            while (temp_value != 0)
            {
              number_symbols++;
              temp_value /= 10;
            }
            if (number_symbols == 0) number_symbols = 1; //�� ������� ���� password = 0, ��� ������� ������� ���� 0, �� ����� � "0"
          }
          else if ((action = (new_state_keyboard & (1<<BIT_KEY_UP))) !=0)
          {
            unsigned int vaga = 1, temp_value, ostacha, vyshchi_rozrjady;
            int edit_rozrjad;
              
            for (intptr_t i = (current_state_menu2.position_cursor_x - COL_NEW_PASSWORD_BEGIN + 1); i < number_symbols; i++) vaga *= 10;
            ostacha = *p_password_edit % vaga;
            temp_value = (*p_password_edit / vaga);
            edit_rozrjad = temp_value % 10;
            vyshchi_rozrjady = temp_value / 10;
          
            if (++edit_rozrjad > MAX_VALUE_DIGIT_PASSWORD) 
            {
              if (ostacha == 0)
              {
                edit_rozrjad = 0;
                if (number_symbols > 1)
                {
                  number_symbols--;
                  current_state_menu2.position_cursor_x--;
                  *p_password_edit = vyshchi_rozrjady*vaga;
                }
                else
                {
                  if (
                      (current_state_menu2.number_selection != INDEX_LIST_PASSWORDS_M2_1) && 
                      (current_state_menu2.number_selection != INDEX_LIST_PASSWORDS_M2_2)
                     )
                  {
                    edit_rozrjad = 1;
                  }
                  *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga; 
                }
              }
              else
              {
                edit_rozrjad = 1;
                *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga + ostacha;
              }
            }
            else
            {
              *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga + ostacha;
            }
          }
          else if ((action = (new_state_keyboard & (1<<BIT_KEY_DOWN))) !=0)
          {
            unsigned int vaga = 1, temp_value, ostacha, vyshchi_rozrjady;
            int edit_rozrjad;
              
            for (intptr_t i = (current_state_menu2.position_cursor_x - COL_NEW_PASSWORD_BEGIN + 1); i < number_symbols; i++) vaga *= 10;
            ostacha = *p_password_edit % vaga;
            temp_value = (*p_password_edit / vaga);
            edit_rozrjad = temp_value % 10;
            vyshchi_rozrjady = temp_value / 10;
          
            if (--edit_rozrjad < 0) 
            {
              edit_rozrjad = MAX_VALUE_DIGIT_PASSWORD;
              *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga + ostacha;
            }
            else if (edit_rozrjad == 0)
            {
              if ((vyshchi_rozrjady != 0) || (ostacha != 0))
              {
                if (ostacha == 0)
                {
                  edit_rozrjad = 0;
                  if (number_symbols > 1)
                  {
                    number_symbols--;
                    current_state_menu2.position_cursor_x--;
                    *p_password_edit = vyshchi_rozrjady*vaga;
                  }
                  else
                  {
                    if (
                        (current_state_menu2.number_selection != INDEX_LIST_PASSWORDS_M2_1) && 
                        (current_state_menu2.number_selection != INDEX_LIST_PASSWORDS_M2_2)
                       )
                    {
                      edit_rozrjad = MAX_VALUE_DIGIT_PASSWORD;
                    }
                    *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga;
                  }
                }
                else
                {
                  edit_rozrjad = MAX_VALUE_DIGIT_PASSWORD;
                  *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga + ostacha;
                }
              }
              else
              {
                if (
                    (current_state_menu2.number_selection != INDEX_LIST_PASSWORDS_M2_1) && 
                    (current_state_menu2.number_selection != INDEX_LIST_PASSWORDS_M2_2)
                   )
                {
                  *p_password_edit = MAX_VALUE_DIGIT_PASSWORD;
                }
                else *p_password_edit = 0;
              }
                  
            }
            else
            {
              *p_password_edit = (vyshchi_rozrjady*10 + edit_rozrjad)*vaga + ostacha;
            }
          }
          else if ((action = (new_state_keyboard & (1<<BIT_KEY_RIGHT))) !=0)
          {
            //��������� ������ RIGHT
            if (*p_password_edit != 0)
            {
              if (++current_state_menu2.position_cursor_x > COL_NEW_PASSWORD_END) current_state_menu2.position_cursor_x = COL_NEW_PASSWORD_BEGIN;
              if (number_symbols < (current_state_menu2.position_cursor_x - COL_NEW_PASSWORD_BEGIN + 1))
              {
                *p_password_edit = (*p_password_edit)*10 + 1;
                number_symbols++;
              }
            }
          }
          else if ((action = (new_state_keyboard & (1<<BIT_KEY_LEFT))) !=0)
          {
            //��������� ������ RIGHT
            if (*p_password_edit != 0)
            {
              if (--current_state_menu2.position_cursor_x < COL_NEW_PASSWORD_BEGIN) current_state_menu2.position_cursor_x = COL_NEW_PASSWORD_BEGIN + number_symbols - 1;
            }
          }
        
          //������� ����� �����������
          p_menu_param_1 = p_password_edit;
          unsigned int view = true;
          p_menu_param_2 = &view;
          if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
          else
          {
            //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
            total_error_sw_fixed(109);
          }
          //������� �� ���������� ������
          new_state_keyboard &= (unsigned int)(~action);
        }
        
        break;
      }
    case MAIN_MANU2_LEVEL:
    case MEASUREMENT_MENU2_LEVEL:
    case INPUTS_OUTPUTS_MENU2_LEVEL:
    case INPUTS_MENU2_LEVEL:
    case OUTPUTS_MENU2_LEVEL:
    case REGISTRATORS_MENU2_LEVEL:
    case LIST_SETTINGS_MENU2_LEVEL:
    case LIST_SETTINGS_BIOS_MENU2_LEVEL:
    case LIST_INPUTS_MENU2_LEVEL:
    case LIST_SETTINGS_INPUT_MENU2_LEVEL:
    case LIST_OUTPUTS_MENU2_LEVEL:
    case LIST_SETTINGS_OUTPUT_MENU2_LEVEL:
    case LIST_LEDS_MENU2_LEVEL:
    case LIST_SETTINGS_LED_MENU2_LEVEL:
    case LIST_ALARMS_MENU2_LEVEL:
    case LIST_SETTINGS_ALARM_MENU2_LEVEL:
    case LIST_GROUP_ALARMS_MENU2_LEVEL:
    case LIST_SETTINGS_GROUP_ALARM_MENU2_LEVEL:
    case LIST_TIMERS_MENU2_LEVEL:
    case LIST_SETTINGS_TIMER_MENU2_LEVEL:
    case LIST_MEANDERS_MENU2_LEVEL:
    case LIST_SETTINGS_MEANDER_MENU2_LEVEL:
    case PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL:
    case PARAM_LIST_SELECTED_LOGICAL_NODES_MENU2_LEVEL:
    case LIST_SETTINGS_COMMUNIACATION_PARAMETERS_MENU2_LEVEL:
    case NAME_OF_CELL_MENU2_LEVEL:
    case SETTINGS_RS485_MENU2_LEVEL:
    case LIST_PASSWORDS_MENU2_LEVEL:
    case DIAGNOSTICS_MENU2_LEVEL:
    case LABELS_MENU2_LEVEL:
    case CONFIG_LABEL_MENU2_LEVEL:
    case SETTINGS_LABEL_MENU2_LEVEL:
    case INFO_MENU2_LEVEL:
    case DATE_TIME_INFO_MENU2_LEVEL:
      {
        //������� ����� ������, �� ������ ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_REWRITE) | (1<<BIT_KEY_ENTER);
        
        if (current_state_menu2.edition == ED_CONFIRM_CHANGES) 
          maska_keyboard_bits |= (1<<BIT_KEY_ESC);
        else if (current_state_menu2.edition <= ED_EDITION) 
          maska_keyboard_bits |= (1<<BIT_KEY_ESC) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);

        //������� �� ��� ���� �����������
        new_state_keyboard &= maska_keyboard_bits;

        if (new_state_keyboard !=0)
        {
          //�������� ����� �� �������� ������
          if (
              ( (action = (new_state_keyboard & (1<<BIT_REWRITE ))) !=0) ||
              ( (action = (new_state_keyboard & (1<<BIT_KEY_UP  ))) !=0) ||
              ( (action = (new_state_keyboard & (1<<BIT_KEY_DOWN))) !=0)
             )   
          {
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(84);
            }
            position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
            //������� ����� �����������
            unsigned int menu_param_1;
            if (
                (current_state_menu2.current_level == CONFIG_LABEL_MENU2_LEVEL) ||
                (current_state_menu2.current_level == SETTINGS_LABEL_MENU2_LEVEL)
               )
            {
              if (current_state_menu2.current_level == CONFIG_LABEL_MENU2_LEVEL) menu_param_1 = 0;
              else menu_param_1 = 1;
              p_menu_param_1 = &menu_param_1; 
            }
            
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(65);
            }
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) !=0)
          {
            //��������� ������ ENTER
            if (current_state_menu2.edition == ED_CONFIRM_CHANGES)
            {
              /*
              ������������ ENTER � ����� ������������ 䳿 �� �������� �� ��.
              � ��������� �� ���������� ��������� ���� 䳿 ����� ��� ������� �����������
              ��� �����������, ������� ��� ������� � ����� ����������� (� ���������) � �� ����
              � ��� �������������� ���� ����� ��������� ��, �� ����� ������ ������������
              */
              //����� ������ � �� ������ ����
              if (current_state_menu2.current_level == LIST_SETTINGS_MENU2_LEVEL)
              {
                //����� ���������� ��� �����������
                unsigned int result = set_config_and_settings(1, MENU_PARAMS_FIX_CHANGES);
                if (result == 0)
                {
                  //������ ����� �����������
                  current_state_menu2.edition = ED_VIEWING;
                }
                else if (result == 1)
                {
                  //����������� ��� ����������� ���������� ���� ������������
                  current_state_menu2.edition = ED_INFO;
                }
                else
                {
                  //����������� ��� �������� �������
                  current_state_menu2.edition = ED_ERROR;
                }
                  
                config_settings_modified = 0;
              }
              else
              {
                //������� ����� ����������� (���� �� �� �������� �� ���������������. �������� �� �������)
                current_state_menu2.edition = ED_VIEWING;
              }
              
              if (current_state_menu2.edition == ED_VIEWING)
              {
                //�������� ������ ������� �� �����
                new_state_keyboard |= (1<<BIT_KEY_ESC);
              }
              else
              {
                //�������� ������ ������� �� ���������� ������
                new_state_keyboard |= (1<<BIT_REWRITE);
              }
            }
            else if (
                     (current_state_menu2.edition == ED_WARNING_EDITION_BUSY) ||
                     (current_state_menu2.edition == ED_WARNING_ENTER_ESC) ||
                     (current_state_menu2.edition == ED_WARNING_ENTER)
                    )   
            {
              /*
              ������������ ENTER � ����� ������ ������������ �� ������� �����
              ������������ � �������� ����� � ����� �� ����������� ���������
              */
              
              //������� ��� ���� ���������� �����������
              current_state_menu2.edition = ED_VIEWING;
              
              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (current_state_menu2.edition == ED_INFO)
            {
              /*
              ������������ ENTER � ����� ������ ����������� ��� �������� �� 
              �� ������� ����� ����������� ��� �������� �� � ������� � �����,
              ���� �������� ������������ ���� � �� ��������� �������� ���� 䳿
              (�������, ����� ������������+����������� ��� ����� � �����������)
              */
              
              //�������� � ����� ������ ����
              current_state_menu2.edition = ED_VIEWING;

              //�������� ������ ������� �� �����
              new_state_keyboard |= (1<<BIT_KEY_ESC);
            }
            else
            {
              const enum _menu2_levels next_for_main_menu2[MAX_ROW_MAIN_M2] = {TIME_MANU2_LEVEL, MEASUREMENT_MENU2_LEVEL, INPUTS_OUTPUTS_MENU2_LEVEL, REGISTRATORS_MENU2_LEVEL, LIST_SETTINGS_MENU2_LEVEL, DIAGNOSTICS_MENU2_LEVEL, LABELS_MENU2_LEVEL, INFO_MENU2_LEVEL};
              const enum _menu2_levels next_for_input_output_menu2[MAX_ROW_INPUT_OUTPUT_M2] = {INPUTS_MENU2_LEVEL, OUTPUTS_MENU2_LEVEL};
              const enum _menu2_levels next_for_labels_menu2[MAX_ROW_LABELS_M2] = {CONFIG_LABEL_MENU2_LEVEL, SETTINGS_LABEL_MENU2_LEVEL};
              const enum _menu2_levels next_for_info_menu2[MAX_ROW_INFO_M2] = {DATE_TIME_INFO_MENU2_LEVEL, INFO_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_settings_menu2[MAX_ROW_LIST_SETTINGS_M2] = {CONFIGURATION_MENU2_LEVEL, LIST_SETTINGS_BIOS_MENU2_LEVEL, LIST_ALARMS_MENU2_LEVEL, LIST_GROUP_ALARMS_MENU2_LEVEL, LIST_TIMERS_MENU2_LEVEL, LIST_MEANDERS_MENU2_LEVEL, PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL, LANGUAGE_MENU2_LEVEL, LIST_SETTINGS_COMMUNIACATION_PARAMETERS_MENU2_LEVEL, LIST_PASSWORDS_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_settings_bios_menu2[MAX_ROW_LIST_SETTINGS_BIOS_M2] = {LIST_INPUTS_MENU2_LEVEL, LIST_OUTPUTS_MENU2_LEVEL, LIST_LEDS_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_inputs_menu2 = LIST_SETTINGS_INPUT_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_input_menu2[MAX_ROW_LIST_SETTINGS_DC_M2] = {DELAY_INPUT_MENU2_LEVEL, CTRL_INPUT_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_outputs_menu2 = LIST_SETTINGS_OUTPUT_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_output_menu2[MAX_ROW_LIST_SETTINGS_C_M2] = {CTRL_OUTPUT_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_leds_menu2 = LIST_SETTINGS_LED_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_led_menu2[MAX_ROW_LIST_SETTINGS_C_M2] = {CTRL_LED_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_alarms_menu2 = LIST_SETTINGS_ALARM_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_alarm_menu2[MAX_ROW_LIST_SETTINGS_DC_M2] = {DELAY_ALARM_MENU2_LEVEL, CTRL_ALARM_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_group_alarms_menu2 = LIST_SETTINGS_GROUP_ALARM_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_group_alarm_menu2[MAX_ROW_LIST_SETTINGS_PDC_M2] = {PICKUP_GROUP_ALARM_MENU2_LEVEL, DELAY_GROUP_ALARM_MENU2_LEVEL, CTRL_GROUP_ALARM_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_timers_menu2 = LIST_SETTINGS_TIMER_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_timer_menu2[MAX_ROW_LIST_SETTINGS_D_M2] = {DELAY_TIMER_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_meanders_menu2 = LIST_SETTINGS_MEANDER_MENU2_LEVEL;
              const enum _menu2_levels next_for_list_settings_meander_menu2[MAX_ROW_LIST_SETTINGS_D_M2] = {DELAY_MEANDER_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_settings_communication_parameters_menu2[MAX_ROW_CHCP_M2] = {NAME_OF_CELL_MENU2_LEVEL, ADDRESS_MENU2_LEVEL, SETTINGS_RS485_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_settings_RS485_menu2[MAX_ROW_SETTING_RS485_M2] = {BAUD_RS485_MENU2_LEVEL, PARE_RS485_MENU2_LEVEL, STOP_BITS_RS485_MENU2_LEVEL, TIMEOUT_RS485_MENU2_LEVEL};
              const enum _menu2_levels next_for_list_passwords_menu2[MAX_ROW_LIST_PASSWORDS_M2] = {SET_NEW_PASSWORD_MENU2_LEVEL, SET_NEW_PASSWORD_MENU2_LEVEL};
              const enum _menu2_levels next_for_param_list_logical_nodes[MAX_ROW_PARAM_LIST_LOGICAL_NODES_M2] = {PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL, PARAM_LIST_SELECTED_LOGICAL_NODES_MENU2_LEVEL};

              const enum _menu2_levels *p = NULL;
              
              switch (current_state_menu2.current_level)
              {
              case MAIN_MANU2_LEVEL:
                {
                  p = &next_for_main_menu2[current_state_menu2.index_position];
                  break;
                }
              case MEASUREMENT_MENU2_LEVEL:
                {
                  break;
                }
              case INPUTS_OUTPUTS_MENU2_LEVEL:
                {
                  p = &next_for_input_output_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_SETTINGS_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_SETTINGS_BIOS_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_bios_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_INPUTS_MENU2_LEVEL:
                {
                  p = &next_for_list_inputs_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[DELAY_INPUT_MENU2_LEVEL]         = 
                  position_in_current_level_menu2[CTRL_INPUT_MENU2_LEVEL]          = 0;
                  
                  break;
                }
              case LIST_SETTINGS_INPUT_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_input_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_OUTPUTS_MENU2_LEVEL:
                {
                  p = &next_for_list_outputs_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[CTRL_OUTPUT_MENU2_LEVEL]          = 0;
                  
                  break;
                }
              case LIST_SETTINGS_OUTPUT_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_output_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_LEDS_MENU2_LEVEL:
                {
                  p = &next_for_list_leds_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[CTRL_LED_MENU2_LEVEL]          = 0;
                  
                  break;
                }
              case LIST_SETTINGS_LED_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_led_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_ALARMS_MENU2_LEVEL:
                {
                  p = &next_for_list_alarms_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[DELAY_ALARM_MENU2_LEVEL]         = 
                  position_in_current_level_menu2[CTRL_ALARM_MENU2_LEVEL]          = 0;
                  
                  break;
                }
              case LIST_SETTINGS_ALARM_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_alarm_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_GROUP_ALARMS_MENU2_LEVEL:
                {
                  p = &next_for_list_group_alarms_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[PICKUP_GROUP_ALARM_MENU2_LEVEL]        = 
                  position_in_current_level_menu2[DELAY_GROUP_ALARM_MENU2_LEVEL]         = 
                  position_in_current_level_menu2[CTRL_GROUP_ALARM_MENU2_LEVEL]          = 0;
                  
                  break;
                }
              case LIST_SETTINGS_GROUP_ALARM_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_group_alarm_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_TIMERS_MENU2_LEVEL:
                {
                  p = &next_for_list_timers_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[DELAY_TIMER_MENU2_LEVEL]         = 0;
                  
                  break;
                }
              case LIST_SETTINGS_TIMER_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_timer_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_MEANDERS_MENU2_LEVEL:
                {
                  p = &next_for_list_meanders_menu2;
                  current_state_menu2.number_selection = current_state_menu2.index_position;
                  
                  position_in_current_level_menu2[DELAY_MEANDER_MENU2_LEVEL]         = 0;
                  
                  break;
                }
              case LIST_SETTINGS_MEANDER_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_meander_menu2[current_state_menu2.index_position];
                  break;
                }
              case PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL:
                {
                  p = &next_for_param_list_logical_nodes[(current_state_menu2.index_position != INDEX_PARAM_LIST_LOGICAL_NODES_M2_GENERAL_BLOCK)];
                  break;
                }
              case LIST_SETTINGS_COMMUNIACATION_PARAMETERS_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_communication_parameters_menu2[current_state_menu2.index_position];
                  break;
                }
              case SETTINGS_RS485_MENU2_LEVEL:
                {
                  p = &next_for_list_settings_RS485_menu2[current_state_menu2.index_position];
                  break;
                }
              case LIST_PASSWORDS_MENU2_LEVEL:
                {
                  current_state_menu2.number_selection = current_state_menu2.index_position;

                  p = &next_for_list_passwords_menu2[current_state_menu2.index_position];
                  break;
                }
              case LABELS_MENU2_LEVEL:
                {
                  p = &next_for_labels_menu2[current_state_menu2.index_position];
                  break;
                }
              case INFO_MENU2_LEVEL:
                {
                  p = &next_for_info_menu2[current_state_menu2.index_position];
                  break;
                }
              }
              
              if (p != NULL)
              {
                enum _menu2_levels temp_current_level = *p;
                if (current_state_menu2.func_press_enter != NULL) 
                {
                  p_menu_param_1 = &temp_current_level;
                  current_state_menu2.func_press_enter();
                }
                if (current_state_menu2.current_level != temp_current_level) 
                {
                
                  previous_level_in_current_level_menu2[temp_current_level] = current_state_menu2.current_level;
                
                  current_state_menu2.current_level = temp_current_level;
                  current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
                  new_level_menu();

                  //����������� ������� �� ����������� ������ ������
                  new_state_keyboard |= (1<<BIT_REWRITE);
                }
              }
            }
              
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //��������� ������ ESC

            if (current_state_menu2.current_level != MAIN_MANU2_LEVEL)
            {
              if (current_state_menu2.func_press_esc != NULL) current_state_menu2.func_press_esc();
              
              if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
              {
                //���������� � �������� ����
                current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
                current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
                new_level_menu();
              }

              //����������� ������� �� ����������� ������ ������
              new_state_keyboard |= (1<<BIT_REWRITE);
            }

            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
          
        break;
      }
    case TIME_MANU2_LEVEL:
      {
        //������� ����� ������. �� ������ ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_KEY_ENTER)| (1<<BIT_KEY_ESC) | (1<<BIT_REWRITE);
        
        if (current_state_menu2.edition <= ED_EDITION)
        {
          maska_keyboard_bits |= (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);
          
          if (current_state_menu2.edition == ED_EDITION)
            maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT);
        }
        
        //������� �� ��� ���� �����������
        new_state_keyboard &= maska_keyboard_bits;
        //������ �������� 䳿, ���� ��������� ������ �� ��� ����� ��������, ��� ����� ������� �������� �����
        if (new_state_keyboard !=0)
        {
          //�������� ����� �� �������� ������
          if( (action = (new_state_keyboard & (1<<BIT_REWRITE))) != 0)
          {
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(87);
            }
            position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;

            //������� ����� �����������
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(68);
            }
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_UP  ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_DOWN))) !=0)
                  )
          {
            //��������� ������ UP
            if(current_state_menu2.edition <= ED_CAN_BE_EDITED)
            {
              //���������� � ����� ������������
              if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
              else
              {
                //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
                total_error_sw_fixed(88);
              }
              position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
            }
            else
            {
              //����������� �����
              if (current_state_menu2.func_change != NULL) current_state_menu2.func_change(action); 
              else
              {
                //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
                total_error_sw_fixed(77);
              }
            }

            //������� �����
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(69);
            }
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_RIGHT))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_LEFT ))) !=0)
                  )
          {
            if (current_state_menu2.func_change != NULL) current_state_menu2.func_change(action); 
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(81);
            }
                
            //������� �����
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(73);
            }
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) != 0)
          {
            //��������� ������ ENTER
            enum _result_pressed_enter_during_edition result;
            if (current_state_menu2.func_press_enter != NULL) result = current_state_menu2.func_press_enter();

            if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
            {
//              prev_edit = current_state_menu2.edition;
               
              if ((current_state_menu2.edition == ED_VIEWING) && (settings_fix_prt.password_2 != 0))
              {
                //���������� �� ���� ������ ������
                next_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = previous_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = current_state_menu2.current_level;
                current_state_menu2.current_level = PASSWORD_MENU2_LEVEL;
                current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
                new_level_menu();
              }
              else
              {
                //���������� � ����� �����������
                current_state_menu2.edition = ED_EDITION;
              }
            }
            else if (current_state_menu2.edition == ED_EDITION)
            {
              //��������� ����� ��� ������������ ������
              switch (result)
              {
              case RPEDE_DATA_NOT_CHANGED:
                {
                  //��� �� ������� ���
                  current_state_menu2.edition = /*prev_edit*/ED_VIEWING;
                  break;
                }
              case RPEDE_DATA_CHANGED_OK:
                {
                  //��� ������� ��� � � � �������
                  current_state_menu2.edition = ED_CONFIRM_CHANGES;
                  break;
                }
              case RPEDE_DATA_CHANGED_OUT_OF_RANGE:
                {
                  //��� ������� ��� ��� �� � � �������
                  current_state_menu2.edition = ED_WARNING_ENTER_ESC;
                  break;
                }
              }
            }
            else if (current_state_menu2.edition == ED_CONFIRM_CHANGES)
            {
              current_state_menu2.edition = /*prev_edit*/ED_VIEWING;
            }
            else if (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
            {
              current_state_menu2.edition = ED_EDITION;
            }

            //����������� �� ���������� ������
            new_state_keyboard |= (1<<BIT_REWRITE);
              
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //��������� ������ ESC
            if (current_state_menu2.func_press_esc != NULL) current_state_menu2.func_press_esc();

            if(current_state_menu2.edition <= ED_CAN_BE_EDITED)
            {
              //����� � ����� ������������
              //���������� � �������� ����
              current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
              current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
              new_level_menu();
            }
            else
            {
              //����� � ����� ����������� ��� �������� ���
              current_state_menu2.edition = /*prev_edit*/ED_VIEWING;
            }

            //����������� ������� �� ����������� ������ ������
            new_state_keyboard |= (1<<BIT_REWRITE);

            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
        break;
      }
    case CONFIGURATION_MENU2_LEVEL:
    case DELAY_ALARM_MENU2_LEVEL:
    case CTRL_ALARM_MENU2_LEVEL:
    case PICKUP_GROUP_ALARM_MENU2_LEVEL:
    case DELAY_GROUP_ALARM_MENU2_LEVEL:
    case CTRL_GROUP_ALARM_MENU2_LEVEL:
    case DELAY_TIMER_MENU2_LEVEL:
    case DELAY_MEANDER_MENU2_LEVEL:
    case DELAY_INPUT_MENU2_LEVEL:
    case CTRL_INPUT_MENU2_LEVEL:
    case CTRL_OUTPUT_MENU2_LEVEL:
    case CTRL_LED_MENU2_LEVEL:
    case LANGUAGE_MENU2_LEVEL:
    case ADDRESS_MENU2_LEVEL:
    case BAUD_RS485_MENU2_LEVEL:
    case PARE_RS485_MENU2_LEVEL:
    case STOP_BITS_RS485_MENU2_LEVEL:
    case TIMEOUT_RS485_MENU2_LEVEL:
      {
        //������� ����� ������, �� ������ ���� �����������
        unsigned int maska_keyboard_bits = (1<<BIT_REWRITE) | (1<<BIT_KEY_ENTER);
        
        if (
            (current_state_menu2.edition == ED_CONFIRM_CHANGES) ||
            (current_state_menu2.edition == ED_WARNING_ENTER_ESC) 
           )  
        {
          maska_keyboard_bits |= (1<<BIT_KEY_ESC);
        }
        else if (current_state_menu2.edition <= ED_EDITION) 
        {
          maska_keyboard_bits |= (1<<BIT_KEY_ESC) | (1<<BIT_KEY_UP)|(1<<BIT_KEY_DOWN);

          if (current_state_menu2.edition == ED_EDITION)
            maska_keyboard_bits |= (1<<BIT_KEY_RIGHT) | (1<<BIT_KEY_LEFT);
        }

        //������� �� ��� ���� �����������
        new_state_keyboard &= maska_keyboard_bits;

        if (new_state_keyboard !=0)
        {
          //�������� ����� �� �������� ������
          if( (action = (new_state_keyboard & (1<<BIT_REWRITE))) != 0)   
          {
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(67);
            }
            position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;

            //������� ����� �����������
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(70);
            }
            //������� �� ���������� ������
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_UP  ))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_DOWN))) !=0)
                  )
          {
            //��������� ������ UP
            if(
               (current_state_menu2.edition <= ED_CAN_BE_EDITED) ||
               (current_state_menu2.binary_data == true)
              )   
            {
              //���������� � ����� ������������
              if (current_state_menu2.func_show != NULL) current_state_menu2.func_move(action, max_row);
              else
              {
                //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
                total_error_sw_fixed(74);
              }
              position_in_current_level_menu2[current_state_menu2.current_level] = current_state_menu2.index_position;
            }
            else
            {
              //����������� �����
              if (current_state_menu2.func_change != NULL) current_state_menu2.func_change(action); 
              else
              {
                //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
                total_error_sw_fixed(86);
              }
            }

            //������� �����
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(89);
            }
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if (
                   ((action = (new_state_keyboard & (1<<BIT_KEY_RIGHT))) !=0) ||
                   ((action = (new_state_keyboard & (1<<BIT_KEY_LEFT ))) !=0)
                  )
          {
            if (current_state_menu2.func_change != NULL) current_state_menu2.func_change(action); 
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(102);
            }
                
            //������� �����
            if (current_state_menu2.func_show != NULL) current_state_menu2.func_show();
            else
            {
              //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
              total_error_sw_fixed(103);
            }
            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ENTER))) !=0)
          {
            //��������� ������ ENTER
            enum _result_pressed_enter_during_edition result;
            if (current_state_menu2.func_press_enter != NULL) result = current_state_menu2.func_press_enter();

            if(current_state_menu2.edition == ED_VIEWING)
            {
              if (settings_fix_prt.password_2 != 0)
              {
                //���������� �� ���� ������ ������
//                prev_edit = current_state_menu2.edition;
                next_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = previous_level_in_current_level_menu2[PASSWORD_MENU2_LEVEL] = current_state_menu2.current_level;
                current_state_menu2.current_level = PASSWORD_MENU2_LEVEL;
                current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
                new_level_menu();
              }
              else if (config_settings_modified == 0)
              {
                //���������� � ����� �����������
                current_state_menu2.edition = ED_EDITION;

                //Գ�����, �� ������� ���� �������� "��������" �� ���� ������������ � �����������
                config_settings_modified = MASKA_MENU_LOCKS;
              }
              else
              {
                //����������� ��� ��, �� ����� ����������� ����� �����������
                current_state_menu2.edition = ED_WARNING_EDITION_BUSY;
              }
            }
            else if(current_state_menu2.edition == ED_CAN_BE_EDITED)
            {
              //���������� � ����� �����������
              current_state_menu2.edition = ED_EDITION;
            }
            else if (current_state_menu2.edition == ED_EDITION)
            {
              //��������� ����� ��� ������������ ������
              switch (result)
              {
              case RPEDE_DATA_NOT_CHANGED:
                {
                  //��� �� ������� ���
                  current_state_menu2.edition = ED_CAN_BE_EDITED;
                  break;
                }
              case RPEDE_DATA_CHANGED_OK:
                {
                  //��� ������� ��� � � � �������
                  current_state_menu2.edition = ED_CAN_BE_EDITED;
                  break;
                }
              case RPEDE_DATA_CHANGED_OUT_OF_RANGE:
                {
                  //��� ������� ��� ��� �� � � �������
                  current_state_menu2.edition = ED_WARNING_ENTER_ESC;
                  break;
                }
              case RPEDE_DATA_CHANGED_WRONG_RETURN_OK:
                {
                  //��������� ������ ������������ �������, ��� ������� �������� ��������� ������������
                  current_state_menu2.edition = ED_WARNING_ENTER;
                  break;
                }
              }
            }
            else if (current_state_menu2.edition == ED_CONFIRM_CHANGES)
            {
              current_state_menu2.edition = /*prev_edit*/ED_CAN_BE_EDITED;
            }
            else if (current_state_menu2.edition == ED_WARNING_EDITION_BUSY)
            {
              current_state_menu2.edition = ED_VIEWING;
            }
            else if (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
            {
              current_state_menu2.edition = ED_EDITION;
            }
            else if (current_state_menu2.edition == ED_WARNING_ENTER)
            {
              current_state_menu2.edition = ED_CAN_BE_EDITED;
            }

            //����������� �� ���������� ������
            new_state_keyboard |= (1<<BIT_REWRITE);

            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else if ( (action = (new_state_keyboard & (1<<BIT_KEY_ESC))) !=0)
          {
            //��������� ������ ESC
            if (current_state_menu2.func_press_esc != NULL) current_state_menu2.func_press_esc();

            if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
            {
              //���������� � �������� ����
              current_state_menu2.current_level = previous_level_in_current_level_menu2[current_state_menu2.current_level];
              current_state_menu2.index_position = position_in_current_level_menu2[current_state_menu2.current_level];
              new_level_menu();
            }
            else
            {
              //����� � ����� ����������� ��� �������� ���
              current_state_menu2.edition = ED_CAN_BE_EDITED;
            }

            //����������� ������� �� ����������� ������ ������
            new_state_keyboard |= (1<<BIT_REWRITE);

            //�������� �����������, �� ��������� ������ 
            new_state_keyboard &= (unsigned int)(~action);
          }
          else
          {
            //��������� ����� ������� ������ - �� � ����������� ��������, ���� ������� ����������� ��� �������� ������ � ������ �����
            unsigned int temp_data = new_state_keyboard;
            new_state_keyboard &= ~temp_data;
          }
        }
          
        break;
      }
    default:
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(63);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
/*
������� ���������� �� ���� (��� ������� � ���������� ���������)

����� ���������
(1 << BIT_REWRITE) - ������������ ����
(1 << BIT_KEY_DOWN) - �������� ����
(1 << BIT_KEY_UP) - �������� �����
*/
/*****************************************************/
void move_into_ekran_simple(unsigned int action, int max_row)
{
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
//������ ����������� ��� �� �� ����� ��� ���� ������ ����
/*****************************************************/
void make_ekran_ask_rewrite(void)
{
  const uint8_t name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD + 1] = 
  {
    {
     "������ ���������",
     "��-ENTER ���-ESC"
    },
    {
     "  ������ ����  ",
     "���-ENTER ͳ-ESC"
    },
    {
     " Enter changes  ",
     "Yes-ENTER No-ESC"
    },
    {
     "������ ���������",
     "��-ENTER ���-ESC"
    }
  };
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i < MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
  }
  
  //������ �� �������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
}
/*****************************************************/


/*****************************************************/
//���������� ���� ��� �������
/*****************************************************/
void make_ekran_about_info(unsigned int info_error, const uint8_t information[][MAX_COL_LCD + 1])
{
  const uint8_t name_string_info[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    "����������:Enter",
    "����������:Enter",
    " Continue: Enter",
    "����������:Enter"
  };

  const uint8_t name_string_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
  {
    "������?Enter/Esc",
    "������?Enter/Esc",
    "Repeat?Enter/Esc",
    "������?Enter/Esc"
  };
  const uint8_t (*p_name_string)[MAX_COL_LCD + 1];
  if (info_error == false ) p_name_string = name_string_info;
  else p_name_string = name_string_error;
  
  int index_language = index_language_in_array(select_struct_settings_fix()->language);
  
  //�������  ����� � ������� �����
  for (size_t i = 0; i< MAX_ROW_LCD; i++)
  {
    for (size_t j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = (i == 0) ? information[index_language][j] : p_name_string[index_language][j];
  }
  
  //������ ���������
  current_state_menu2.cursor_on = 0;
  //������ �� ����
  current_state_menu2.cursor_blinking_on = 0;
}
/*****************************************************/

/*****************************************************/
//������������ ������� � �������� ���� � ������� �����
/*****************************************************/
void calc_symbol_and_put_into_working_ekran(uint8_t* point_in_working_ekran, void* point_value, void* point_vaga, unsigned int* point_first_symbol, unsigned int current_position_x, unsigned int position_comma, unsigned int v_32_64)
{
  unsigned int temp_data;
  if (v_32_64 == 0)
  {
    temp_data = (*((uint32_t*)point_value)) / (*((uint32_t*)point_vaga)); //�������� �����, ��� ����� ����������� � ������ � �������� � ���� ������� ������
    *((uint32_t*)point_value) %= *((uint32_t*)point_vaga); //���������� ����� ��� �������, ���� �� ����� ������ �������� �� �����
    *((uint32_t*)point_vaga) /=10; //�������� ������� ���������� � 10 ����
  }
  else
  {
    temp_data = (*((uint64_t*)point_value)) / (*((uint64_t*)point_vaga)); //�������� �����, ��� ����� ����������� � ������ � �������� � ���� ������� ������
    *((uint64_t*)point_value) %= *((unsigned long long*)point_vaga); //���������� ����� ��� �������, ���� �� ����� ������ �������� �� �����
    *((uint64_t*)point_vaga) /=10; //�������� ������� ���������� � 10 ����
  }
  
  if(current_state_menu2.edition == ED_EDITION) *point_in_working_ekran = temp_data + 0x30;
  else
  {
    //� �������, ���� �� �� � ����� �����������, �� ��� ����� ����� (�� �������� ����������, ���� ����� �) ���������
    if ((temp_data !=0) || ((*point_first_symbol) != 0))
    {
      *point_in_working_ekran = temp_data + 0x30;
      if ((*point_first_symbol) == 0) *point_first_symbol = 1;
    }
    else
    {
      if (current_position_x < (position_comma - 1) ) *point_in_working_ekran = ' ';
      else
      {
        *point_in_working_ekran = temp_data + 0x30;
        if ((*point_first_symbol) == 0) *point_first_symbol = 1;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//������������ ������ ������� � �������� ���� � ������� �����
/*****************************************************/
void calc_int_symbol_and_put_into_working_ekran(uint8_t* point_in_working_ekran, uint32_t* point_value, uint32_t* point_vaga, unsigned int* point_first_symbol)
{
  unsigned int temp_data;
  temp_data = (*point_value) / (*point_vaga); //�������� �����, ��� ����� ����������� � ������ � �������� � ���� ������� ������
  *point_value %= *(point_vaga); //���������� ����� ��� �������, ���� �� ����� ������ �������� �� �����
  *point_vaga /=10; //�������� ������� ���������� � 10 ����
  if(current_state_menu2.edition >= ED_EDITION) *point_in_working_ekran = temp_data + 0x30;
  else
  {
    //� �������, ���� �� �� � ����� �����������, �� ��� ����� ���������� �������� ������ ���������
    if ((temp_data !=0) || ((*point_first_symbol) != 0))
    {
      *point_in_working_ekran = temp_data + 0x30;
      if ((*point_first_symbol) == 0) *point_first_symbol = 1;
    }
    else
    {
      //���� �������� ����� � ���� �������, ���� �� � ������ ������� ����� (������ ���� ����� ���� 1)
      if ((*point_vaga) >= 1 ) *point_in_working_ekran = ' ';
      else
      {
        *point_in_working_ekran = temp_data + 0x30;
        if ((*point_first_symbol) == 0) *point_first_symbol = 1;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������� �������� �������
/*****************************************************
����� ���������
  0 - �������� ������ ����
  1 - ��������� ������ �����
����� ���������
  ����
*****************************************************/
unsigned int edit_setpoint(unsigned int action, uint32_t value, unsigned int floating_value, int comma, unsigned int end, unsigned int min_step)
{
  unsigned int rozrjad, vaga = min_step, temp_value, data_return;
  //���������� ������ ����� �� ���� ����� ����� ������
  rozrjad = end - current_state_menu2.position_cursor_x;
  
  //� ��� ���� ���������� ����� � ������ � �����, �� ��������� ������� ����
  if (floating_value != 0)
    if (current_state_menu2.position_cursor_x < comma) rozrjad--;
      
  for(size_t i = 0; i < rozrjad; i++)  vaga *= 10;
  
  //�������� ����� , ��� ���� ������
  temp_value = (value / vaga) % 10;
  
  //� �������� ����, ���� ��� �������� ����������� ������ ������� � ���� ���������
  data_return = value - temp_value*vaga;
  
  //������� �������� ������
  inc_or_dec_value(&temp_value, action);
  
  //������� ������ ������ � ������� ���������
  data_return += temp_value*vaga;
  
  return data_return;
}
/*****************************************************/

/*****************************************************/
//��������� ��� ��������� ����� ��� ��������� ������
/*
  ����� ���������
  label_value - �������� �� ��������  �����
  inc_dec 
    0 - �������� �� �������
    1 - �������� �� �������
*/
/*****************************************************/
void inc_or_dec_value(unsigned int *label_value, unsigned int inc_dec)
{
  int temp_value = *label_value;
  
  if(inc_dec == 0) temp_value--;
  else if(inc_dec == 1) temp_value++;
  
  if(temp_value > 9) temp_value = 0;
  else if(temp_value < 0) temp_value = 9;
  
  *label_value = temp_value;
}
/*****************************************************/

/*****************************************************/
//���������� ����������� �����
/*
���������
  1 - ��� ��������
  0 - ��� ����������
*/
/*****************************************************/
unsigned int check_data_setpoint(unsigned int current_value, unsigned int min_value, unsigned int max_value)
{
  if ((current_value < min_value) || (current_value > max_value)) return 0;

  //����� � ������������, �� ������� � ����� �������
  return 1;
}
/*****************************************************/

/*****************************************************/
//���� ����� ��� ��� �������� ������
/*****************************************************/
void new_level_menu(void)
{
  switch (current_state_menu2.current_level)
  {
  case MAIN_MANU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_MAIN_M2;
      current_state_menu2.func_move = move_into_main;
      current_state_menu2.func_show = make_ekran_main;
      current_state_menu2.func_press_enter = press_enter_in_main_and_list_passwords;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;

      break;
    }
  case TIME_MANU2_LEVEL:
    {
      time_rewrite = 0;
      
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_TIME_CALIBRATION_M2;
      current_state_menu2.func_move = move_into_time;
      current_state_menu2.func_show = make_ekran_time;
      current_state_menu2.func_press_enter = press_enter_in_time;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = change_time;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case MEASUREMENT_MENU2_LEVEL:
    {
      time_rewrite = 0;
      
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_MEASURMENT_ANALOG_INPUT;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_measurement;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case INPUTS_OUTPUTS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_INPUT_OUTPUT_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_list_inputs_outputs;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case INPUTS_MENU2_LEVEL:
  case OUTPUTS_MENU2_LEVEL:
    {
      time_rewrite = 0;
      
      if (current_state_menu2.current_level == INPUTS_MENU2_LEVEL) current_state_menu2.p_max_row = (int*)&current_config_prt.n_input;
      else current_state_menu2.p_max_row = (int*)&current_config_prt.n_output;
      current_state_menu2.max_row = 0;
      current_state_menu2.func_move = move_into_ekran_input_or_output;
      current_state_menu2.func_show = make_ekran_state_inputs_or_outputs;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case REGISTRATORS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_LIST_REGISTRATORS_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_list_registrators;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case LIST_SETTINGS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_LIST_SETTINGS_M2;
      current_state_menu2.func_move = move_into_list_settings;
      current_state_menu2.func_show = make_ekran_list_settings;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = press_esc_in_list_settings;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case CONFIGURATION_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_CONFIGURATION;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_configuration;
      current_state_menu2.func_press_enter = press_enter_in_configuration;
      current_state_menu2.func_press_esc = press_esc_in_configuration;
      current_state_menu2.func_change = change_configuration;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_INPUTS_MENU2_LEVEL:
  case LIST_OUTPUTS_MENU2_LEVEL:
  case LIST_LEDS_MENU2_LEVEL:
  case LIST_ALARMS_MENU2_LEVEL:
  case LIST_GROUP_ALARMS_MENU2_LEVEL:
  case LIST_TIMERS_MENU2_LEVEL:
  case LIST_MEANDERS_MENU2_LEVEL:
  case PARAM_LIST_SELECTED_LOGICAL_NODES_MENU2_LEVEL:
    {
      __CONFIG *p_config = (current_state_menu2.edition == ED_VIEWING) ? &current_config_prt : &current_config;
      if (current_state_menu2.current_level == PARAM_LIST_SELECTED_LOGICAL_NODES_MENU2_LEVEL)
      {
        int *p_number[NUMBER_VAR_BLOCKS] = 
        {
          (int*)&p_config->n_input, 
          (int*)&p_config->n_output,
          (int*)&p_config->n_led, 
          (int*)&p_config->n_alarm,
          (int*)&p_config->n_group_alarm,
          (int*)&p_config->n_and,
          (int*)&p_config->n_or,
          (int*)&p_config->n_xor,
          (int*)&p_config->n_not,
          (int*)&p_config->n_timer,
          (int*)&p_config->n_trigger,
          (int*)&p_config->n_meander
        };

        intptr_t index = position_in_current_level_menu2[previous_level_in_current_level_menu2[current_state_menu2.current_level]] - NUMBER_FIX_BLOCKS; 
        current_state_menu2.p_max_row = p_number[index];
        
        current_state_menu2.index_position = 0;
      }
      else
      {
        switch (current_state_menu2.current_level)
        {
        case LIST_INPUTS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row =(int*)&p_config->n_input;
            break;
          }
        case LIST_OUTPUTS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (int*)&p_config->n_output;
            break;
          }
        case LIST_LEDS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (int*)&p_config->n_led;
            break;
          }
        case LIST_ALARMS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (int*)&p_config->n_alarm;
            break;
          }
        case LIST_GROUP_ALARMS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (int*)&p_config->n_group_alarm;
            break;
          }
        case LIST_TIMERS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (int*)&p_config->n_timer;
            break;
          }
        case LIST_MEANDERS_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (int*)&p_config->n_meander;
            break;
          }
        default:
          {
            //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
            total_error_sw_fixed(104);
          }
        }
      }
      current_state_menu2.max_row = 0;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_list_logical_nodes;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_SETTINGS_GROUP_ALARM_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_group_alarm : (int*)&current_config.n_group_alarm;
      current_state_menu2.max_row = MAX_ROW_LIST_SETTINGS_PDC_M2;
      current_state_menu2.index_position = 0;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_pickup_delay_control;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_SETTINGS_INPUT_MENU2_LEVEL:
  case LIST_SETTINGS_ALARM_MENU2_LEVEL:
    {
      switch (current_state_menu2.current_level)
      {
        case LIST_SETTINGS_INPUT_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_input : (int*)&current_config.n_input;
            break;
          }
        case LIST_SETTINGS_ALARM_MENU2_LEVEL:
          {
            current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_alarm : (int*)&current_config.n_alarm;
            break;
          }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(47);
        }
      }
      current_state_menu2.max_row = MAX_ROW_LIST_SETTINGS_DC_M2;
      current_state_menu2.index_position = 0;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_delay_control;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_SETTINGS_TIMER_MENU2_LEVEL:
  case LIST_SETTINGS_MEANDER_MENU2_LEVEL:
    {
      switch (current_state_menu2.current_level)
      {
      case LIST_SETTINGS_TIMER_MENU2_LEVEL:
        {
          current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_timer : (int*)&current_config.n_timer;
          break;
        }
      case LIST_SETTINGS_MEANDER_MENU2_LEVEL:
        {
          current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_meander : (int*)&current_config.n_meander;
          break;
        }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(105);
        }
      }
      current_state_menu2.max_row = MAX_ROW_LIST_SETTINGS_D_M2;
      current_state_menu2.index_position = 0;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_delay;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_SETTINGS_OUTPUT_MENU2_LEVEL:
  case LIST_SETTINGS_LED_MENU2_LEVEL:
    {
      switch (current_state_menu2.current_level)
      {
      case LIST_SETTINGS_OUTPUT_MENU2_LEVEL:
        {
          current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_output : (int*)&current_config.n_output;
          break;
        }
      case LIST_SETTINGS_LED_MENU2_LEVEL:
        {
          current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_led : (int*)&current_config.n_led;
          break;
        }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(106);
        }
      }
      current_state_menu2.max_row = MAX_ROW_LIST_SETTINGS_C_M2;
      current_state_menu2.index_position = 0;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_control;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case DELAY_ALARM_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_alarm : (int*)&current_config.n_alarm;
      current_state_menu2.max_row = ALARM_SET_DELAYS;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_delay_alarm;
      current_state_menu2.func_press_enter = press_enter_in_delay_alarm;
      current_state_menu2.func_press_esc = press_esc_in_delay_alarm;
      current_state_menu2.func_change = change_delay_alarm;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case CTRL_ALARM_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_alarm : (int*)&current_config.n_alarm;
      current_state_menu2.max_row = MAX_INDEX_CTRL_ALARM;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_control_alarm;
      current_state_menu2.func_press_enter = press_enter_in_control_alarm;
      current_state_menu2.func_press_esc = press_esc_in_control_alarm;
      current_state_menu2.func_change = change_control_alarm;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case PICKUP_GROUP_ALARM_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_group_alarm : (int*)&current_config.n_group_alarm;
      current_state_menu2.max_row = GROUP_ALARM_PICKUPS;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_pickup_group_alarm;
      current_state_menu2.func_press_enter = press_enter_in_pickup_group_alarm;
      current_state_menu2.func_press_esc = press_esc_in_pickup_group_alarm;
      current_state_menu2.func_change = change_pickup_group_alarm;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case DELAY_GROUP_ALARM_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_group_alarm : (int*)&current_config.n_group_alarm;
      current_state_menu2.max_row = GROUP_ALARM_SET_DELAYS;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_delay_group_alarm;
      current_state_menu2.func_press_enter = press_enter_in_delay_group_alarm;
      current_state_menu2.func_press_esc = press_esc_in_delay_group_alarm;
      current_state_menu2.func_change = change_delay_group_alarm;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case CTRL_GROUP_ALARM_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_group_alarm : (int*)&current_config.n_group_alarm;
      current_state_menu2.max_row = MAX_INDEX_CTRL_GROUP_ALARM;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_control_group_alarm;
      current_state_menu2.func_press_enter = press_enter_in_control_group_alarm;
      current_state_menu2.func_press_esc = press_esc_in_control_group_alarm;
      current_state_menu2.func_change = change_control_group_alarm;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case DELAY_TIMER_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_timer : (int*)&current_config.n_timer;
      current_state_menu2.max_row = TIMER_SET_DELAYS;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_delay_timer;
      current_state_menu2.func_press_enter = press_enter_in_delay_timer;
      current_state_menu2.func_press_esc = press_esc_in_delay_timer;
      current_state_menu2.func_change = change_delay_timer;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case DELAY_MEANDER_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_meander : (int*)&current_config.n_meander;
      current_state_menu2.max_row = MAX_INDEX_DELAY_MEANDER;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_delay_meander;
      current_state_menu2.func_press_enter = press_enter_in_delay_meander;
      current_state_menu2.func_press_esc = press_esc_in_delay_meander;
      current_state_menu2.func_change = change_delay_meander;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_SETTINGS_BIOS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_LIST_SETTINGS_BIOS_M2;
      current_state_menu2.func_move = move_into_list_settings_bios;
      current_state_menu2.func_show = make_ekran_list_settings_bios;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case DELAY_INPUT_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_input : (int*)&current_config.n_input;
      current_state_menu2.max_row = INPUT_SET_DELAYS;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_delay_input;
      current_state_menu2.func_press_enter = press_enter_in_delay_input;
      current_state_menu2.func_press_esc = press_esc_in_delay_input;
      current_state_menu2.func_change = change_delay_input;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case CTRL_INPUT_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_input : (int*)&current_config.n_input;
      current_state_menu2.max_row = MAX_INDEX_CTRL_INPUT;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_control_input;
      current_state_menu2.func_press_enter = press_enter_in_control_input;
      current_state_menu2.func_press_esc = press_esc_in_control_input;
      current_state_menu2.func_change = change_control_input;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case CTRL_OUTPUT_MENU2_LEVEL:
  case CTRL_LED_MENU2_LEVEL:
    {
      switch (current_state_menu2.current_level)
      {
      case CTRL_OUTPUT_MENU2_LEVEL:
        {
          current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_output : (int*)&current_config.n_output;
          break;
        }
      case CTRL_LED_MENU2_LEVEL:
        {
          current_state_menu2.p_max_row = (current_state_menu2.edition == ED_VIEWING) ? (int*)&current_config_prt.n_led : (int*)&current_config.n_led;
          break;
        }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(107);
        }
      }
      current_state_menu2.max_row = MAX_INDEX_CTRL_OUTPUT_LED;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_control_output_led;
      current_state_menu2.func_press_enter = press_enter_in_control_output_led;
      current_state_menu2.func_press_esc = press_esc_in_control_output_led;
      current_state_menu2.func_change = change_control_output_led;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case PARAM_LIST_LOGICAL_NODES_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_PARAM_LIST_LOGICAL_NODES;
      current_state_menu2.func_move = move_into_param_list_logical_nodes;
      current_state_menu2.func_show = make_ekran_param_list_logical_node;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LANGUAGE_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_VIEW_SETTING_LANGUAGE;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_setting_language;
      current_state_menu2.func_press_enter = press_enter_in_setting_language;
      current_state_menu2.func_press_esc = press_esc_in_setting_language;
      current_state_menu2.func_change = change_setting_language;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_SETTINGS_COMMUNIACATION_PARAMETERS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_CHCP_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_communication_parameters;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case NAME_OF_CELL_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_VIEW_NAME_OF_CELL;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_name_of_cell;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case ADDRESS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_ADDRESS_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_address;
      current_state_menu2.func_press_enter = press_enter_in_address;
      current_state_menu2.func_press_esc = press_esc_in_address;
      current_state_menu2.func_change = change_address;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case SETTINGS_RS485_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_SETTING_RS485_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_setting_RS485;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case BAUD_RS485_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_VIEW_BAUD_RS485;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_baud_RS485;
      current_state_menu2.func_press_enter = press_enter_in_baud_RS485;
      current_state_menu2.func_press_esc = press_esc_in_baud_RS485;
      current_state_menu2.func_change = change_baud_RS485;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case PARE_RS485_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_VIEW_PARE_RS485;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_pare_RS485;
      current_state_menu2.func_press_enter = press_enter_in_pare_RS485;
      current_state_menu2.func_press_esc = press_esc_in_pare_RS485;
      current_state_menu2.func_change = change_pare_RS485;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case STOP_BITS_RS485_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_VIEW_STOP_BITS_RS485;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_stopbits_RS485;
      current_state_menu2.func_press_enter = press_enter_in_stopbits_RS485;
      current_state_menu2.func_press_esc = press_esc_in_stopbits_RS485;
      current_state_menu2.func_change = change_stopbits_RS485;
      current_state_menu2.binary_data = true;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case TIMEOUT_RS485_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_VIEW_TIMEOUT_RS485;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_timeout_RS485;
      current_state_menu2.func_press_enter = press_enter_in_timeout_RS485;
      current_state_menu2.func_press_esc = press_esc_in_timeout_RS485;
      current_state_menu2.func_change = change_timeout_RS485;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case LIST_PASSWORDS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_LIST_PASSWORDS_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_choose_passwords;
      current_state_menu2.func_press_enter = press_enter_in_main_and_list_passwords;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  case DIAGNOSTICS_MENU2_LEVEL:
    {
      time_rewrite = 0;
      
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_DIAGNOSTYKA;
      current_state_menu2.func_move = move_into_diagnostics;
      current_state_menu2.func_show = make_ekran_diagnostics;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case LABELS_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_LABELS_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_list_labels;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case CONFIG_LABEL_MENU2_LEVEL:
  case SETTINGS_LABEL_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_TIME_CONFIG_OR_SETTINGS;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_time_config_or_settings;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case INFO_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_INFO_M2;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_info;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case DATE_TIME_INFO_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_FOR_DATE_TIME_PZ;
      current_state_menu2.func_move = move_into_ekran_simple;
      current_state_menu2.func_show = make_ekran_date_time_pz;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      current_state_menu2.edition = ED_VIEWING;
      break;
    }
  case PASSWORD_MENU2_LEVEL:
  case SET_NEW_PASSWORD_MENU2_LEVEL:
    {
      current_state_menu2.p_max_row = NULL;
      current_state_menu2.max_row = MAX_ROW_PASSWORD_M2;
      current_state_menu2.func_move = NULL;
      current_state_menu2.func_show = make_ekran_password;
      current_state_menu2.func_press_enter = NULL;
      current_state_menu2.func_press_esc = NULL;
      current_state_menu2.func_change = NULL;
      current_state_menu2.binary_data = false;
      /*
      current_state_menu2.edition �� ������������ �� �� �������� �� ����������� 
      ��������� ����
      */
      break;
    }
  default:
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(64);
    }
  }
}
/*****************************************************/
