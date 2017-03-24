#include "header.h"

/*****************************************************/
/*
Функція переміщення

Вхідні параметри
(1 << BIT_REWRITE) - перемалювати меню
(1 << BIT_KEY_DOWN) - рухатися вниз
(1 << BIT_KEY_UP) - рухатися вверх
*/
/*****************************************************/
void move_into_time(unsigned int action, int max_row)
{
  if (action & ((1 << BIT_REWRITE) | (1 << BIT_KEY_DOWN)))
  {
    if (action & (1 << BIT_KEY_DOWN)) current_state_menu2.index_position += MAX_ROW_LCD;
    if(current_state_menu2.index_position >= max_row) current_state_menu2.index_position = 0;
  }
  else if (action & (1 << BIT_KEY_UP))
  {
    current_state_menu2.index_position -= MAX_ROW_LCD;
    if(current_state_menu2.index_position < 0) current_state_menu2.index_position = max_row - MAX_ROW_LCD;
  }
  
  /**************************************************/
  //Курсор має бути на першому символі рядка з даними
  /**************************************************/
  if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_TIME)
  {
    current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_DATE;
  }
  else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_NAME_CALIBRATION)
  {
    current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION;
  }

  if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_DATE)
  {
    current_state_menu2.position_cursor_x = COL_DY1;
  }
  else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION)
  {
    current_state_menu2.position_cursor_x = COL_SK1;
  }
  /**************************************************/
}
/*****************************************************/

/*****************************************************/
//Формуємо екран година-час
/*****************************************************/
void make_ekran_time(void)
{
  if (current_state_menu2.edition == ED_CONFIRM_CHANGES)
  {
    make_ekran_ask_rewrite();
  }
  else if (current_state_menu2.edition == ED_WARNING_ENTER_ESC)
  {
    const unsigned char information_about_error[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      " Вых.за диапазон",
      " Вих.за діапазон",
      "  Out of Limits ",
      "Вых.за диапазон "
    };
    make_ekran_about_info(true, information_about_error);
  }
  else
  {
    uint8_t name_string[MAX_ROW_TIME_CALIBRATION_M2][MAX_COL_LCD + 1] = 
    {
      "   XX-XX-20XX   ",
      "    XX:XX:XX    ",
      "                ",
      "      X XX      "
    };
  
    const uint8_t calibrating[MAX_NAMBER_LANGUAGE][MAX_COL_LCD + 1] = 
    {
      "   Калибровка   ",
      "  Калібрування  ",
      "  Calibration   ",
      "   Калибровка   "
    };
  
    int index_language = index_language_in_array(settings_fix_prt.language);
    
    for(size_t index_1 = 0; index_1 < (MAX_COL_LCD + 1); index_1++)
      name_string[INDEX_TIME_CALIBRATION_M2_NAME_CALIBRATION][index_1] = calibrating[index_language][index_1];
  
    unsigned int position_temp = current_state_menu2.index_position;
    unsigned int index_in_ekran;
  
    /******************************************/
    //Заповнюємо поля відповідними цифрами
    /******************************************/
    /*використовувати time_copy і calibration_copy не треба бо ф-ції main_manu_function_ver2() і make_ekran_time() викликаються з найнижчого рівня*/ 
    uint8_t *time_tmp = (current_state_menu2.edition <= ED_CAN_BE_EDITED) ? time : time_edit;
    uint8_t *calibration_tmp = (current_state_menu2.edition <= ED_CAN_BE_EDITED) ? &calibration : &calibration_edit;
    //День
    name_string[INDEX_TIME_CALIBRATION_M2_DATE][COL_DY1] = (time_tmp[4] >>  4) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_DATE][COL_DY2] = (time_tmp[4] & 0xf) + 0x30;

    //Місяць
    name_string[INDEX_TIME_CALIBRATION_M2_DATE][COL_MY1] = (time_tmp[5] >>  4) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_DATE][COL_MY2] = (time_tmp[5] & 0xf) + 0x30;

    //Рік
    name_string[INDEX_TIME_CALIBRATION_M2_DATE][COL_SY1] = (time_tmp[6] >>  4) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_DATE][COL_SY2] = (time_tmp[6] & 0xf) + 0x30;

    //Година
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][COL_HT1] = (time_tmp[3] >>  4) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][COL_HT2] = (time_tmp[3] & 0xf) + 0x30;

    //Хвилини
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][COL_MT1] = (time_tmp[2] >>  4) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][COL_MT2] = (time_tmp[2] & 0xf) + 0x30;

    //Секунди
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][COL_ST1] = (time_tmp[1] >>  4) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_TIME][COL_ST2] = (time_tmp[1] & 0xf) + 0x30;

    //Калібровка
    if((*calibration_tmp & (1<<5)) == 0) name_string[INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION][COL_SK1] = '-';
    else name_string[INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION][COL_SK1] = '+';
   
    name_string[INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION][COL_VK2] =((*calibration_tmp & 0x1f) % 10) + 0x30;
    name_string[INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION][COL_VK1] =((*calibration_tmp & 0x1f) / 10) + 0x30;
    /******************************************/
  
    index_in_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
    //Копіюємо  рядки у робочий екран
    for (size_t i = 0; i < MAX_ROW_LCD; i++)
    {
      //Наступні рядки треба перевірити, чи їх требе відображати
      for (size_t j = 0; j < MAX_COL_LCD; j++)
      {
        working_ekran[i][j] = (index_in_ekran < MAX_ROW_TIME_CALIBRATION_M2) ? name_string[index_in_ekran][j] : ' ';
      }
      index_in_ekran++;
    }

    //Відображення курору по вертикалі
    current_state_menu2.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
    if (current_state_menu2.edition <= ED_CAN_BE_EDITED)
    {
      //Курсор невидимий
      current_state_menu2.cursor_on = 0;
      current_state_menu2.cursor_blinking_on = 0;
    }
    else
    {
      //Курсор видимий
      current_state_menu2.cursor_on = 1;
      //Курсор мигає
      current_state_menu2.cursor_blinking_on = 1;
    }
  }
  
  //Обновити повністю весь екран
  current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
/*
Редагування дати і часу
*/
/*****************************************************/
enum _result_pressed_enter_during_edition press_enter_in_time(void)
{
  enum _result_pressed_enter_during_edition result;
  switch (current_state_menu2.edition)
  {
  case ED_VIEWING:
    {
      //Копіюємо дані для редагування
      for(size_t i = 0; i < 7; i++) time_edit[i] = time[i]; /*використовувати time_copy і calibration_copy не треба бо ф-ції main_manu_function_ver2() і main_routines_for_i2c() викликаються з найнижчого рівня*/ 
      calibration_edit = calibration;
      
      result = RPEDE_NONE;
      
      break;
    }
  case ED_EDITION:
    {
      //Перевіряємо, чи дані рельно змінилися
      result = RPEDE_DATA_NOT_CHANGED;
      for(size_t i = 0; ((i < 7) && (result == RPEDE_DATA_NOT_CHANGED)); i++)
      {
        if (time[i] != time_edit[i]) result = RPEDE_DATA_CHANGED_OK;
      }
      if (result == RPEDE_DATA_NOT_CHANGED)
      {
        if (calibration != calibration_edit) result = RPEDE_DATA_CHANGED_OK;
      }
      
      if (result == RPEDE_DATA_CHANGED_OK)
      {
        if (check_data_for_data_time_menu() != 1) result = RPEDE_DATA_CHANGED_OUT_OF_RANGE;
      }
      break;
    }
  case ED_CONFIRM_CHANGES:
    {
      //Копіюємо дані після редагування
      for(size_t i = 0; i < 7; i++) time[i] = time_edit[i]; /*використовувати time_copy і calibration_copy не треба бо ф-ції main_manu_function_ver2() і main_routines_for_i2c() викликаються з найнижчого рівня*/ 
      calibration = calibration_edit;
      
      //Виставляємо повідомлення запису часу в RTC
      //При цьому виставляємо біт блокування негайного запуску операції, щоб засинхронізуватися з роботою вимірювальної системи
      _SET_BIT(control_i2c_taskes, TASK_START_WRITE_RTC_BIT);
      _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      
      result = RPEDE_NONE;
      
      break;
    }
  case ED_CAN_BE_EDITED:
  case ED_WARNING_ENTER_ESC:
    {
      result = RPEDE_NONE;
      break;
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//Зміна часу з системи меню
/*****************************************************
Вхідні параметри
(1 << BIT_KEY_DOWN) - натснуто кнопку вниз
(1 << BIT_KEY_UP)   - атиснуто кнопку вверх
(1 << BIT_KEY_RIGHT)- натснуто кнопку праворуч
(1 << BIT_KEY_LEFT) - атиснуто кнопку ліворуч

Вхідні параметри
  Немає
*****************************************************/
void change_time(unsigned int action)
{
  //Вводимо число у відповідне поле
  if (action & ((1 << BIT_KEY_DOWN) | (1 << BIT_KEY_UP)))
  {
    if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_DATE)
    {
      if(current_state_menu2.position_cursor_x == COL_DY1)
      {
        unsigned int temp_value = time_edit[4] >> 4;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));
      
        time_edit[4] &= 0xf;
        time_edit[4] |= (temp_value << 4);
      }
      else if(current_state_menu2.position_cursor_x == COL_DY2)
      {
        unsigned int temp_value = time_edit[4] & 0xf;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[4] &= 0xf0;
        time_edit[4] |= temp_value;
      }
      else if(current_state_menu2.position_cursor_x == COL_MY1)
      {
        unsigned int temp_value = time_edit[5] >> 4;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[5] &= 0xf;
        time_edit[5] |= (temp_value << 4);
      }
      else if(current_state_menu2.position_cursor_x == COL_MY2)
      {
        unsigned int temp_value = time_edit[5] & 0xf;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[5] &= 0xf0;
        time_edit[5] |= temp_value;
      }
      else if(current_state_menu2.position_cursor_x == COL_SY1)
      {
        unsigned int temp_value = time_edit[6] >> 4;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[6] &= 0xf;
        time_edit[6] |= (temp_value << 4);
      }
      else if(current_state_menu2.position_cursor_x == COL_SY2)
      {
        unsigned int temp_value = time_edit[6] & 0xf;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[6] &= 0xf0;
        time_edit[6] |= temp_value;
      }
    }
    else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_TIME)
    {
      if(current_state_menu2.position_cursor_x == COL_HT1)
      {
        unsigned int temp_value = time_edit[3] >> 4;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[3] &= 0xf;
        time_edit[3] |= (temp_value << 4);
      }
      else if(current_state_menu2.position_cursor_x == COL_HT2)
      {
        unsigned int temp_value = time_edit[3] & 0xf;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[3] &= 0xf0;
        time_edit[3] |= temp_value;
      }
      else if(current_state_menu2.position_cursor_x == COL_MT1)
      {
        unsigned int temp_value = time_edit[2] >> 4;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[2] &= 0xf;
        time_edit[2] |= (temp_value << 4);
      }
      else if(current_state_menu2.position_cursor_x == COL_MT2)
      {
        unsigned int temp_value = time_edit[2] & 0xf;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[2] &= 0xf0;
        time_edit[2] |= temp_value;
      }
      else if(current_state_menu2.position_cursor_x == COL_ST1)
      {
        unsigned int temp_value = time_edit[1] >> 4;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[1] &= 0xf;
        time_edit[1] |= (temp_value << 4);
      }
      else if(current_state_menu2.position_cursor_x == COL_ST2)
      {
        unsigned int temp_value = time_edit[1] & 0xf;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        time_edit[1] &= 0xf0;
        time_edit[1] |= temp_value;
      }
    }
    else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION)
    {
      if(current_state_menu2.position_cursor_x == COL_SK1) 
      {
        if ((calibration_edit & 0x20) != 0) calibration_edit &= 0x1f;
        else calibration_edit |= 0x20;
      }
      else if(current_state_menu2.position_cursor_x == COL_VK1)
      {
        unsigned char temp_1 = calibration_edit & 0x20, temp_2 = calibration_edit & 0x1f;
        unsigned int temp_value = temp_2 / 10;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        temp_2 %= 10;
        temp_2 += temp_value*10;
        if (temp_2 > 31) temp_2 = 31;
        calibration_edit = temp_1 | temp_2;
                
      }
      else if(current_state_menu2.position_cursor_x == COL_VK2)
      {
        unsigned char temp_1 = calibration_edit & 0x20, temp_2 = calibration_edit & 0x1f;
        unsigned int temp_value = temp_2 % 10;
        inc_or_dec_value(&temp_value, ((action & (1 << BIT_KEY_UP)) != 0));

        temp_2 = (temp_2 / 10) *10;
        temp_2 += temp_value;
        if (temp_2 > 31) temp_2 = 31;
        calibration_edit = temp_1 | temp_2;
      }
    }
  }
  else if (action & (1 << BIT_KEY_LEFT))
  {
    if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_DATE)
    {
      if(current_state_menu2.position_cursor_x == COL_SY2) current_state_menu2.position_cursor_x = COL_SY1;
      else if(current_state_menu2.position_cursor_x == COL_SY1) current_state_menu2.position_cursor_x = COL_MY2;
      else if(current_state_menu2.position_cursor_x == COL_MY2) current_state_menu2.position_cursor_x = COL_MY1;
      else if(current_state_menu2.position_cursor_x == COL_MY1) current_state_menu2.position_cursor_x = COL_DY2;
      else if(current_state_menu2.position_cursor_x == COL_DY2) current_state_menu2.position_cursor_x = COL_DY1;
      else if(current_state_menu2.position_cursor_x == COL_DY1)
      {
        current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION;
        current_state_menu2.position_cursor_x = COL_VK2;
      }
    }
    else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_TIME)
    {
      if(current_state_menu2.position_cursor_x == COL_ST2) current_state_menu2.position_cursor_x = COL_ST1;
      else if(current_state_menu2.position_cursor_x == COL_ST1) current_state_menu2.position_cursor_x = COL_MT2;
      else if(current_state_menu2.position_cursor_x == COL_MT2) current_state_menu2.position_cursor_x = COL_MT1;
      else if(current_state_menu2.position_cursor_x == COL_MT1) current_state_menu2.position_cursor_x = COL_HT2;
      else if(current_state_menu2.position_cursor_x == COL_HT2) current_state_menu2.position_cursor_x = COL_HT1;
      else if(current_state_menu2.position_cursor_x == COL_HT1)
      {
        current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_DATE;
        current_state_menu2.position_cursor_x = COL_SY2;
      }
    }
    else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION)
    {
      if(current_state_menu2.position_cursor_x == COL_VK2) current_state_menu2.position_cursor_x = COL_VK1;
      else if(current_state_menu2.position_cursor_x == COL_VK1) current_state_menu2.position_cursor_x = COL_SK1;
      else if(current_state_menu2.position_cursor_x == COL_SK1)
      {
        current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_TIME;
        current_state_menu2.position_cursor_x = COL_ST2;
      }
    }
  }
  else if (action & (1 << BIT_KEY_RIGHT))
  {
    if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_DATE)
    {
      if(current_state_menu2.position_cursor_x == COL_DY1) current_state_menu2.position_cursor_x = COL_DY2;
      else if(current_state_menu2.position_cursor_x == COL_DY2) current_state_menu2.position_cursor_x = COL_MY1;
      else if(current_state_menu2.position_cursor_x == COL_MY1) current_state_menu2.position_cursor_x = COL_MY2;
      else if(current_state_menu2.position_cursor_x == COL_MY2) current_state_menu2.position_cursor_x = COL_SY1;
      else if(current_state_menu2.position_cursor_x == COL_SY1) current_state_menu2.position_cursor_x = COL_SY2;
      else if(current_state_menu2.position_cursor_x == COL_SY2)
      {
        current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_TIME;
        current_state_menu2.position_cursor_x = COL_HT1;
      }
    }
    else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_TIME)
    {
      if(current_state_menu2.position_cursor_x == COL_HT1) current_state_menu2.position_cursor_x = COL_HT2;
      else if(current_state_menu2.position_cursor_x == COL_HT2) current_state_menu2.position_cursor_x = COL_MT1;
      else if(current_state_menu2.position_cursor_x == COL_MT1) current_state_menu2.position_cursor_x = COL_MT2;
      else if(current_state_menu2.position_cursor_x == COL_MT2) current_state_menu2.position_cursor_x = COL_ST1;
      else if(current_state_menu2.position_cursor_x == COL_ST1) current_state_menu2.position_cursor_x = COL_ST2;
      else if(current_state_menu2.position_cursor_x == COL_ST2)
      {
        current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION;
        current_state_menu2.position_cursor_x = COL_SK1;
      }
    }
    else if(current_state_menu2.index_position == INDEX_TIME_CALIBRATION_M2_VALUE_CALIBRATION)
    {
      if(current_state_menu2.position_cursor_x == COL_SK1) current_state_menu2.position_cursor_x = COL_VK1;
      else if(current_state_menu2.position_cursor_x == COL_VK1) current_state_menu2.position_cursor_x = COL_VK2;
      else if(current_state_menu2.position_cursor_x == COL_VK2)
      {
        current_state_menu2.index_position = INDEX_TIME_CALIBRATION_M2_DATE;
        current_state_menu2.position_cursor_x = COL_DY1;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//Перевіряємо достовірність даних
/*
Результат
  1 - дані достовірні
  0 - дані недостовірні
*/
/*****************************************************/
unsigned int check_data_for_data_time_menu(void)
{
  unsigned int temp_data_1, temp_data_2;
  
  /*******/
  //Рік
  /*******/
  temp_data_1 = bcd_to_int(time_edit[6]);
  if( temp_data_1 > 99 ) return 0;

  /*******/
  //Місяць
  /*******/
  temp_data_1 = bcd_to_int(time_edit[5]);
  if( (temp_data_1 == 0) || (temp_data_1 > 12)) return 0;
  
  /*******/
  //День місяця
  /*******/
  temp_data_2 = bcd_to_int(time_edit[4]);
  if((temp_data_2 == 0) || (temp_data_2 > 31)) return 0;
  //Додатков перевірка на місяць у якого є тільки 30 днів
  if (((temp_data_1 == 4) || (temp_data_1 == 6) || (temp_data_1 == 9) || (temp_data_1 == 11)) &&
      (temp_data_2 > 30)) return 0;

  //Додатков перевірка на місяць місяць лютий з врахування року високосного чи не високосного
  if((temp_data_1 == 2) && (temp_data_2 > 29)) return 0;
  else if ((temp_data_1 == 2) && (temp_data_2 == 29))
  {
    //Змінну temp_data_1 визначаємо, як номер року, бо вже надалі номер місяця нам не буде потрібен
    temp_data_1 = bcd_to_int(time_edit[6]);
    if ((temp_data_1 % 4) !=0) return 0;
  }
  /*******/

  /*******/
  //Година
  /*******/
  temp_data_2 = bcd_to_int(time_edit[3]);
  if(temp_data_2 > 23) return 0;
  /*******/

  /*******/
  //Хвилини
  /*******/
  temp_data_2 = bcd_to_int(time_edit[2]);
  if(temp_data_2 > 59) return 0;
  /*******/

  /*******/
  //Секунди
  /*******/
  temp_data_2 = bcd_to_int(time_edit[1]);
  if(temp_data_2 > 59) return 0;
  /*******/

  /*******/
  //Соті секунди
  /*******/
  temp_data_1 = bcd_to_int(time_edit[0]);
  if( temp_data_1 > 99 ) return 0;

  //Вихід з повідомленням, що всі параметри у  межах допуску
  return 1;
}
/*****************************************************/


/*****************************************************/
//Перевід числа з формату BCD в int 
/*****************************************************/
unsigned int bcd_to_int(unsigned char input)
{
  unsigned int output, temp_data;
  
  temp_data = input >> 4;
  output = temp_data*10;
  output +=input & 0xf;
  
  return output;
}
/*****************************************************/


/*****************************************************/
// 
/*****************************************************/
/*****************************************************/
