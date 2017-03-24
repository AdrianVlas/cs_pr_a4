#include "header.h"

/*****************************************************/
//Очікування, поки контролер LCD буде вільним
/*****************************************************/
inline unsigned int wait_lcd_ready(void)
{
  uint16_t current_count_tim4, new_count_tim4;
  unsigned int delta;
  unsigned int error_LCD = 0;
  
  unsigned char temp_data;
  //Виставляємо лінію LCD_RS = 0
  GPIO_ResetBits(LCD_RS, LCD_RS_PIN);

  //Виставляємо лінію LCD_RW = 1
  GPIO_SetBits(LCD_RW, LCD_RW_PIN);
  
  /*
  Витримаємо павзу максимум 10,01 мс (найдовша затримка може бути, згідно документації, порядку одиниць мілісекунд)
  Тому коли буде встановлено, що затримка становить 10,01 мс - то це означає, LCD несправне
  */
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;

  //Читаємо IR-регістр і поки біь BF буде рівним 0
  unsigned int count = 0;
  do
  {
    //Затримка на неменше ніж 40 нс
    _DELAY_ABOUT_40NS();
    temp_data =  *((unsigned char *) LCD_BASE);
    //Затримка на неменше ніж 10 нс
    _DELAY_ABOUT_10NS();

    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - це повний період таймера, бо ми настроїли його тактуватиу інтервалі [0; 65535]
    
    if (delta >= 1001) //(1000 + 1)* 0,01(мс) = 10,01(мс)
    {
      error_LCD = 1; //Пройшов час більше 10,01 мс з а який LCD не підтвердив операцію

      //Виставляємо повідомлення про цю подію
      _SET_BIT(set_diagnostyka, ERROR_LCD_BIT);
    }
    
    if ((temp_data & (1<<BF_BIT)) != 0) count = 0;
    else count++;
  }
  while (
         (count      < 2) &&
         (error_LCD == 0) 
        );
  
  return error_LCD;
  
}
/*****************************************************/

/*****************************************************/
//Запис даних у контролер LCD
/*****************************************************/
inline unsigned int write_data_to_lcd(unsigned char letter)
{
  //Очікуємо поки LCD будк вільним
  unsigned int error_LCD = wait_lcd_ready();
  if (error_LCD == 0)
  {
    //Виставляємо лінію LCD_RS = 1
    GPIO_SetBits(LCD_RS, LCD_RS_PIN);
    //Виставляємо лінію LCD_RW = 0
    GPIO_ResetBits(LCD_RW, LCD_RW_PIN);
    //Затримка на неменше ніж 40 нс
    _DELAY_ABOUT_40NS();
    *((unsigned char *) LCD_BASE) = letter;
    //Затримка на неменше ніж 10 нс
    _DELAY_ABOUT_10NS();
  }
  
  return error_LCD;
}
/*****************************************************/


/*****************************************************/
//Конвертмація ASCII у код LCD
/*****************************************************/
inline unsigned int Win1251toHd44780 (unsigned int win1251Letter)
{ 
  if ( win1251Letter < 128 )
  return win1251Letter;

  //Підбір коду символу з стандартного кириличного набору CGRAM
  for (unsigned int i = 0; i < MAX_NYMBER_EXTENDED_ASCII_SYMBOLS; i ++ )
  {
    if ( letters [i] [0] == win1251Letter )
    return letters [i][1];
  }
  
  //Підбір коду символу з створеного символу в CGRAM
  if ((current_language >= LANGUAGE_RU) && (current_language <= LANGUAGE_KZ))
  {
    //Ця умова мала б виконуватися завжди
    for (unsigned int i = 0; i < MAX_NYMBER_EXTRA_EXTENDED_ASCII_SYMBOLS; i ++ )
    {
      if ( extra_letters[i][0] == win1251Letter )
      return extra_letters[i][current_language];
    }
  }

  return 0xff;
}
/*****************************************************/


/*****************************************************/
//Запис команди у контролер LCD
/*****************************************************/
inline unsigned int write_command_to_lcd(unsigned char command)
{
  //Очікуємо поки LCD будк вільним
  unsigned int error_LCD = wait_lcd_ready();
  if (error_LCD == 0)
  {
    //Виставляємо лінію LCD_RS = 0
    GPIO_ResetBits(LCD_RS, LCD_RS_PIN);
    //Виставляємо лінію LCD_RW = 0
    GPIO_ResetBits(LCD_RW, LCD_RW_PIN);
    //Затримка на неменше ніж 40 нс
    _DELAY_ABOUT_40NS();
    *((unsigned char *) LCD_BASE) = command;
    //Затримка на неменше ніж 10 нс
    _DELAY_ABOUT_10NS();
  }
  
  return error_LCD;
}
/*****************************************************/

/*****************************************************/
//Стартова ініціалізація
/*****************************************************/
void lcd_init(void)
{
  uint16_t current_count_tim4, new_count_tim4;
  unsigned int delta;
  //Враховуємо той факт, що TIM4 тактує з чатотою 100кГц - тобто 10мкс = 0,01 мс
  
  //Витримаємо павзу 15 мс
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 1501) //(1500 + 1)* 0,01(мс) = 15,01(мс)
  {
    //Робота з watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //Змінюємо стан біту зовнішнього Watchdog на протилежний
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
    }
    
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - це повний період таймера, бо ми настроїли його тактуватиу інтервалі [0; 65535]
  }
  //Затримка на неменше ніж 40 нс
  _DELAY_ABOUT_40NS();
  //Вводимо в контролер LCD число 0x3A (2 рядки і розмір шрифту 5*7 і таблицю символів з кириличними символами)
  *((unsigned char *) LCD_BASE) = 0x3A;
  //Затримка на неменше ніж 10 нс
  _DELAY_ABOUT_10NS();

  //Витримаємо павзу 4,1 мс
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 411) //(410 + 1)* 0,01(мс) = 4,11(мс)
  {
    //Робота з watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //Змінюємо стан біту зовнішнього Watchdog на протилежний
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
    }
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - це повний період таймера, бо ми настроїли його тактуватиу інтервалі [0; 65535]
  }
  //Затримка на неменше ніж 40 нс
  _DELAY_ABOUT_40NS();
  //Повторно вводимо в контролер LCD число 0x3A (2 рядки і розмір шрифту 5*7 і таблицю символів з кириличними символами)
  *((unsigned char *) LCD_BASE) = 0x3A;
  //Затримка на неменше ніж 10 нс
  _DELAY_ABOUT_10NS();

  //Витримаємо павзу 100 мкс 
  current_count_tim4 = ((uint16_t)TIM4->CNT);
  delta = 0;
  while (delta < 11) //(10 + 1)* 10(мкс) = 110(мкс)
  {
    //Робота з watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //Змінюємо стан біту зовнішнього Watchdog на протилежний
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
    }
    new_count_tim4 = ((uint16_t)TIM4->CNT);
    if (new_count_tim4 >= current_count_tim4) delta = new_count_tim4 - current_count_tim4;
    else delta = (0x10000 - current_count_tim4) + new_count_tim4; //0x10000 - це повний період таймера, бо ми настроїли його тактуватиу інтервалі [0; 65535]
  }
  //Затримка на неменше ніж 40 нс
  _DELAY_ABOUT_40NS();
  //Третій раз вводимо в контролер LCD число 0x3A (2 рядки і розмір шрифту 5*7 і таблицю символів з кириличними символами)
  *((unsigned char *) LCD_BASE) = 0x3A;
  //Затримка на неменше ніж 10 нс
  _DELAY_ABOUT_10NS();

  //Робота з watchdogs
  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
  {
    //Змінюємо стан біту зовнішнього Watchdog на протилежний
    GPIO_WriteBit(
                  GPIO_EXTERNAL_WATCHDOG,
                  GPIO_PIN_EXTERNAL_WATCHDOG,
                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                 );
  }

  //Встановлюємо 2 рядки і розмір шрифту 5*7 і таблицю символів з кириличними символами
  unsigned int error_LCD = write_command_to_lcd(0x3A);

  //Відключаємо LCD
  if (error_LCD == 0) write_command_to_lcd(0x08);

  //Очищаємо LCD
  if (error_LCD == 0) write_command_to_lcd(0x01);

  //Виконуємо команду "Return Home"
  if (error_LCD == 0) write_command_to_lcd(0x02);

  //Встановлюємо режим LCD: лічильник збільшується, екран не зміщується
  if (error_LCD == 0) write_command_to_lcd(0x06);

  //Відображення включено, курсор є і не мигає
  if (error_LCD == 0) write_command_to_lcd(0x0E);

  //Робота з watchdogs
  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
  {
    //Змінюємо стан біту зовнішнього Watchdog на протилежний
    GPIO_WriteBit(
                  GPIO_EXTERNAL_WATCHDOG,
                  GPIO_PIN_EXTERNAL_WATCHDOG,
                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                 );
  }
}
/*****************************************************/


/*****************************************************/
//Очистка LCD
/*****************************************************/
unsigned int clear_lcd(void)
{
  unsigned int error_LCD = write_command_to_lcd(0x1);
  
  return error_LCD;
}
/*****************************************************/

/*****************************************************/
//Режим відображення
/*****************************************************/
unsigned int mode_viewing(unsigned int ecran_on, unsigned int cursor_on, unsigned int cursor_blinking)
{
  unsigned char temp_data = 0x8;

  //Формуємо командне слово
  if(ecran_on != 0) temp_data |= (1<<2);
  if(cursor_on != 0) temp_data |= (1<<1);
  if(cursor_blinking != 0) temp_data |= (1<<0);

  unsigned int error_LCD = write_command_to_lcd(temp_data);
  
  return error_LCD;
}
/*****************************************************/

/*****************************************************/
//Вивід рядка на LCD
/*****************************************************/
unsigned int hd44780_puts (unsigned char *s, unsigned int len)
{
  unsigned int letter, error_LCD = 0;
  
  unsigned int i = 0;
  while(
        (i < len       ) &&
        (error_LCD == 0)  
       )
  { 
    letter = Win1251toHd44780 (s [i++]); // байт даних
    error_LCD = write_data_to_lcd(letter);
  }
  
  return error_LCD;
} 
/*****************************************************/

/*****************************************************/
//Перенос курсору у вказану позицію
/*****************************************************/
unsigned int hd44780_gotoxy(unsigned char x, unsigned char y)
{
  unsigned char address, writeValue;

  //Вирахувати адрес курсору (0x40 - адрес початку другого рядка)
  // address = y * 0x40 + x;
  address = 0; // default
  switch (y)
  { 
    case 0: // 0-ий рядок
      { 
        address = 0x00;
        break;
      }

    case 1: // 1-ий рядок
      {
        address = 0x40;
        break;
      }
  }

  // додати стовбець
  if ( x < MAX_COL_LCD ) address += x; 

  //Кінцева команда
  writeValue = 0x80 | ( address & 0x7F );

  unsigned int error_LCD = write_command_to_lcd(writeValue);
  
  return error_LCD;
}
/*****************************************************/

/*****************************************************/
//Вивід рядка у вказану позицію
/*****************************************************/
unsigned int hd44780_puts_xy (unsigned char x, unsigned char y, unsigned char *s)
{
  unsigned int error_LCD = hd44780_gotoxy (x,y);
  if (error_LCD == 0) error_LCD = hd44780_puts (s, MAX_COL_LCD);
  
  return error_LCD;
}
/*****************************************************/

/*****************************************************/
//Відображення всього екрану
/*****************************************************/
void view_whole_ekran(void)
{
  if (current_state_menu2.current_action != ACTION_WITH_CARRENT_EKRANE_NONE)
  {
    if (
        (_CHECK_SET_BIT(    diagnostyka, ERROR_LCD_BIT) == 0) ||
        (_CHECK_SET_BIT(set_diagnostyka, ERROR_LCD_BIT) == 0)
       )   
    {
      unsigned int error_LCD = 0;
      
      if(current_state_menu2.current_action == ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE)
      {
        //Виводимо інформацію
        unsigned int i = 0;
        while (
               (i < MAX_ROW_LCD) &&
               (error_LCD == 0 )  
              )
        {
          error_LCD = hd44780_puts_xy(0,i, working_ekran[i]); 
          i++;
        }
      }
    
      //Переводимо курсор у вказану позицю
      if (error_LCD == 0) error_LCD = hd44780_gotoxy ((current_state_menu2.position_cursor_x & (MAX_COL_LCD -1)),(current_state_menu2.position_cursor_y & (MAX_ROW_LCD -1)));
      //Виставляємо стан курсора: включено-виключено; мигає- не мигає
      if (error_LCD == 0) error_LCD = mode_viewing(1, current_state_menu2.cursor_on, current_state_menu2.cursor_blinking_on);
    }
    
    //Знімаємо повідомлення, що екран требе зараз обновити
    current_state_menu2.current_action = ACTION_WITH_CARRENT_EKRANE_NONE;
  }
}
/*****************************************************/

/*****************************************************/
//Вибір з якої структури брати налаштування для мови
/*****************************************************/
__SETTINGS_FIX* select_struct_settings_fix(void)
{
  __SETTINGS_FIX *result;
  if (current_state_menu2.edition == ED_VIEWING) result = &settings_fix_prt;
  else if (
           (current_state_menu2.edition == ED_EDITION) ||
           (current_state_menu2.edition == ED_CONFIRM_CHANGES)
          )  
  {
    result = &settings_fix_edit;
  }
  else
  {
    result = &settings_fix;
  }
  return result;
}
/*****************************************************/

/*****************************************************/
//Вибір індексу для вибраної мови
/*****************************************************/
int index_language_in_array(int language)
{
  int language_tmp = language, result;
  
  if ((language_tmp < LANGUAGE_ABSENT) || (language_tmp > LANGUAGE_KZ))
  {
    language_tmp = LANGUAGE_ABSENT;
  }
    
  switch (language_tmp)
  {
    case LANGUAGE_RU:
      {
        result = INDEX_LANGUAGE_RU;
        break;
      }
    case LANGUAGE_UA:
      {
        result = INDEX_LANGUAGE_UA;
        break;
      }
    case LANGUAGE_EN:
      {
        result = INDEX_LANGUAGE_EN;
        break;
      }
    case LANGUAGE_KZ:
      {
        result = INDEX_LANGUAGE_KZ;
        break;
      }
  default:
    {
      result = INDEX_LANGUAGE_EN;
      break;
    }
  }

        
  //Перевіряємо чи не треба догрузити особливі символи особливої мови
  if (
      (current_language == LANGUAGE_ABSENT) ||
      (current_language != language_tmp   )
     )
  {
    unsigned int error_LCD = 0;
    //Очищаємо екран
    error_LCD = clear_lcd();

    current_language = language_tmp;
          
    const unsigned char matrix[16][8] = {
                                         {0x0A, 0x00, 0x0E, 0x04, 0x04, 0x04, 0x0E, 0x00}, // Ї
                                         {0x00, 0x0A, 0x00, 0x0C, 0x04, 0x04, 0x0E, 0x00}, // ї
                                         {0x01, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00}, // Ґ
                                         {0x00, 0x00, 0x01, 0x1F, 0x10, 0x10, 0x10, 0x00}, // ґ
                                         {0x0E, 0x11, 0x10, 0x1C, 0x10, 0x11, 0x0E, 0x00}, // Є
                                         {0x00, 0x00, 0x0E, 0x11, 0x1C, 0x11, 0x0E, 0x00}, // є
                                         {0x00, 0x00, 0x00, 0x04, 0x0A, 0x11, 0x1F, 0x00}, // ‰, як замінник грецької літери "дельта"
                                         {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x0E, 0x00}, // Љ - замінний символ з даним кодом для WIN1251 для казазської мови
                                         {0x00, 0x00, 0x0E, 0x11, 0x1F, 0x11, 0x0E, 0x00}, // љ - замінний символ з даним кодом для WIN1251 для казазської мови
                                         {0x0E, 0x11, 0x01, 0x1F, 0x11, 0x11, 0x0E, 0x00}, // Ѕ - замінний символ з даним кодом для WIN1251 для казазської мови
                                         {0x00, 0x00, 0x0E, 0x01, 0x1F, 0x11, 0x0E, 0x00}, // ѕ - замінний символ з даним кодом для WIN1251 для казазської мови
                                         {0x11, 0x11, 0x0A, 0x04, 0x1F, 0x04, 0x04, 0x00}, // Ђ - замінний символ з даним кодом для WIN1251 для казазської мови
                                         {0x00, 0x00, 0x11, 0x0A, 0x04, 0x1F, 0x04, 0x04},  // ђ - замінний символ з даним кодом для WIN1251 для казазської мови
                                         {0x00, 0x00, 0x00, 0x04, 0x0A, 0x11, 0x1F, 0x00}, // ‰, як замінник грецької літери "дельта"
                                         {0x0E, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x1B, 0x00}, // Ї, як замынник  великоъ букви Омега для англійської розкладки клавіатури
                                         {0x00, 0x00, 0x00, 0x04, 0x0A, 0x11, 0x1F, 0x00}  // ‰, як замінник грецької літери "дельта"
                                        }; 
            
    unsigned int number_new_extra_symbols = 0, index_for_symbol;
            
    if (current_language == LANGUAGE_EN)
    {
      number_new_extra_symbols = 2;
      index_for_symbol = 14;
    }
    else if (current_language == LANGUAGE_UA)
    {
      number_new_extra_symbols = 3*2 + 1;
      index_for_symbol = 0;
    }
    else if (current_language == LANGUAGE_KZ)
    {
      number_new_extra_symbols = 3*2 + 1;
      index_for_symbol = 7;
    }
    else if (current_language == LANGUAGE_RU)
    {
      number_new_extra_symbols = 1;
      index_for_symbol = 15;
    }
      
    if (number_new_extra_symbols != 0)
    {
      //Встановлюємо адресу AC в 0x00 CGRAM
      error_LCD = write_command_to_lcd(0x40 | 0x00);
  
      //Записуємо маттрицю символа
      unsigned int i = 0, j = index_for_symbol, k = 0;
      while(
            (i < number_new_extra_symbols) &&
            (error_LCD == 0)  
           )
      { 
        error_LCD = write_data_to_lcd(matrix[j][k++]);
        if (k >= 8)
        {
          k = 0;
          j++;
          i++;
        }
      }
    }
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
/*****************************************************/
