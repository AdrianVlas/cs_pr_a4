#ifndef __CONST_GLOBAL__
#define __CONST_GLOBAL__

//Величина, яка необхідна для періодичної (період 1  мс   ) генерації переривань каналом 1 таймеру 2 з прескаллером 2000 = (1999 + 1)
#define TIM2_CCR1_VAL                   30
//Величина, яка необхідна для періодичної (період 10 мс   ) генерації переривань каналом 1 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR1_VAL                   1000
//Величина, яка необхідна для періодичної (період 1 мс   ) генерації переривань каналом 2 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR2_VAL                   100
//Величина, яка необхідна для періодичної (як мінімум, період 10 мкс   ) генерації переривань каналом 3 таймеру 4 з прескаллером 600 = (599 + 1)
#define TIM4_CCR3_VAL                   1
//Величина, яка необхідна для періодичної (період 0,625 мс) генерації переривань каналом 1 таймеру 3 з прескаллером 1 = (0 + 1)
#define TIM5_CCR1_VAL                   37500

#define MAX_NUMBER_LINES_VMP            8

#define DELTA_TIME_FOR_TIMERS           1

#define NUMBER_ANALOG_CANALES_VAL_1     5

#define NUMBER_ANALOG_CANALES           (                               \
                                         NUMBER_ANALOG_CANALES_VAL_1    \
                                        )

#define NUMBER_INPUTS_1                 5
#define NUMBER_INPUTS_2                 5
#define NUMBER_INPUTS                   (NUMBER_INPUTS_1 + NUMBER_INPUTS_2)
#define NUMBER_OUTPUTS_1                6
#define NUMBER_OUTPUTS_2                4
#define NUMBER_OUTPUTS                  (NUMBER_OUTPUTS_1 + NUMBER_OUTPUTS_2)

#define NUMBER_LEDS                     8

/*****************************************/
//Константи для фіксації звідки були введені останні зміни
/*****************************************/
enum __source_fix_changes
{
  DEFAULT_PARAMS_FIX_CHANGES = 0,
  MENU_PARAMS_FIX_CHANGES,
  USB_PARAMS_FIX_CHANGES,
  RS485_PARAMS_FIX_CHANGES,

  NO_MATTER_PARAMS_FIX_CHANGES,
};
/*****************************************/

/*****************************************/
//Константи для комунікації
/*****************************************/
#define MAX_CHAR_IN_NAME_OF_CELL                              32
/*****************************************/

/*****************************************/
//Константи для фіксації зміни настройок
/*****************************************/
#define CHANGED_ETAP_NONE                                     0
#define CHANGED_ETAP_EXECUTION                                1
#define CHANGED_ETAP_ENDED                                    2
/*****************************************/

/*****************************************/
//Константи для ранжування функціональних кнопок
/*****************************************/
enum __odynyci_vymirjuvannja {
INDEX_A = 0,
INDEX_V,
INDEX_SECOND,

NUMBER_ODYNYCI_VYMIRJUVANNJA
};
/*****************************************/

/*****************************************/
//Індетифікатор типу набору юстуючих коефіцієнтів
/*****************************************/
//#define ADJUSTMENT_3I0_IA_IB_IC                             1
//#define ADJUSTMENT_3I0_IA_IC_3U0                            2
//#define ADJUSTMENT_3I0_IA_IB_IC_UA_UB_UC_UABTN2             3
//#define ADJUSTMENT_3I0_IA_IB_IC_UA_UB_UC_3U0                4
//#define ADJUSTMENT_IA_IB_IC_UA1_UB1_UC1_UA2_UB2_UC2         5
#define ADJUSTMENT_1_U_4_I                                  6
#define ADJUSTMENT_ID                                         ADJUSTMENT_1_U_4_I
/*****************************************/

/*****************************************/
//Версія програмного забезпечення
/*****************************************/
#define VERSIA_PZ                                             12
#define MODYFIKACIA_VERSII_PZ                                 0
#define ZBIRKA_VERSII_PZ                                      0
/*****************************************/

/*****************************************/
//Час компіляції
/*****************************************/

#define YEAR_VER                                              ((__DATE__[9] != ' ') ? (((__DATE__[9] - 0x30) << 4) | (__DATE__[10] - 0x30)) : (__DATE__[10] - 0x30))
#define MONTH_VER                                             str_to_int_DATE_Mmm()
#define DAY_VER                                               ((__DATE__[4] != ' ') ? (((__DATE__[4] - 0x30) << 4) | (__DATE__[5] - 0x30)) : (__DATE__[5] - 0x30))
#define HOUR_VER                                              (((__TIME__[0] - 0x30) << 4) | (__TIME__[1] - 0x30))
#define MINUTE_VER                                            (((__TIME__[3] - 0x30) << 4) | (__TIME__[4] - 0x30))
#define SECOND_VER                                            (((__TIME__[6] - 0x30) << 4) | (__TIME__[7] - 0x30))
/*****************************************/

/*****************************************/
//Версія універсальної карти памяті
/*****************************************/
#define VERSIA_GMM                                             7
#define MODYFIKACIA_VERSII_GMM                                 0
/*****************************************/
#endif
