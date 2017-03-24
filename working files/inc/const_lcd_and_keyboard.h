#ifndef __CONST_LCD_AND_KEYBOARD__
#define __CONST_LCD_AND_KEYBOARD__

#define MAX_TIME_REWRITE_EKRAN  100 //x10 - Максимальний час у мс для автоматичного обновлення екранів меню, які треба обновляти

#define MAX_NYMBER_EXTENDED_ASCII_SYMBOLS        69
#define MAX_NYMBER_EXTRA_EXTENDED_ASCII_SYMBOLS  13

#define LCD_BASE          Bank1_SRAM3_ADDR

#define POWER_MAX_COL_LCD       4
#define POWER_MAX_ROW_LCD       1
#define MAX_COL_LCD       (1<<POWER_MAX_COL_LCD)
#define MAX_ROW_LCD       (1<<POWER_MAX_ROW_LCD)

#define BF_BIT            7

#define NUMBER_KEY_KEYBOARD (4*3)
#define DEREVIACIA          8

#define BIT_KEY_ENTER           0
#define BIT_KEY_DOWN            1
#define BIT_KEY_RIGHT           2
#define BIT_KEY_ESC             3
#define BIT_KEY_LEFT            4
#define BIT_KEY_UP              5
#define BIT_KEY_1               6
#define BIT_KEY_2               7
#define BIT_KEY_3               8
#define BIT_KEY_4               9
#define BIT_KEY_5               10
#define BIT_KEY_6               11

#define BIT_REWRITE             30

#define ACTION_WITH_CARRENT_EKRANE_NONE                      0
#define ACTION_WITH_CARRENT_EKRANE_ONLY_CHANGE_CURSOR        1
#define ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE   2

#endif
