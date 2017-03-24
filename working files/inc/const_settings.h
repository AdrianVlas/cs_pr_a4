#ifndef __CONST_SETTINGS__
#define __CONST_SETTINGS__

#define BIT_CHANGED_CONFIGURATION       0
#define MASKA_CHANGED_CONFIGURATION     (1 << BIT_CHANGED_CONFIGURATION)
#define BIT_CHANGED_SETTINGS            1
#define MASKA_CHANGED_SETTINGS          (1 << BIT_CHANGED_SETTINGS)
#define BIT_MENU_LOCKS                  2
#define MASKA_MENU_LOCKS                (1 << BIT_MENU_LOCKS)
#define BIT_USB_LOCKS                   3
#define MASKA_USB_LOCKS                 (1 << BIT_USB_LOCKS)
#define BIT_RS485_LOCKS                 4
#define MASKA_RS485_LOCKS               (1 << BIT_RS485_LOCKS)

#define AND_SIGNALS_IN                  8
#define OR_SIGNALS_IN                   8

#define SFIFT_PARAM_ID                  24
#define SFIFT_PARAM_N                   16
#define SFIFT_PARAM_OUT                 0

#define MASKA_PARAM_ID                  ((1 << (8*sizeof(uint32_t) - SFIFT_PARAM_ID )) - 1)
#define MASKA_PARAM_N                   ((1 << (SFIFT_PARAM_ID     - SFIFT_PARAM_N  )) - 1)
#define MASKA_PARAM_OUT                 ((1 << (SFIFT_PARAM_N      - SFIFT_PARAM_OUT)) - 1)

enum _id_fb
{
  _ID_FB_FIRST_ALL = 1,                                                 /*1*/
  
    _ID_FB_FIRST_FIX = _ID_FB_FIRST_ALL,                                /*1*/

      ID_FB_CONTROL_BLOCK = _ID_FB_FIRST_FIX,                           /*1*/
      
    _ID_FB_LAST_FIX,                                                    /*2*/

    _ID_FB_FIRST_VAR = _ID_FB_LAST_FIX,                                 /*2*/
    
      _ID_FB_FIRST_VAR_NONE_CHANGED = _ID_FB_FIRST_VAR,                 /*2*/

        ID_FB_INPUT = _ID_FB_FIRST_VAR_NONE_CHANGED,                    /*2*/
        ID_FB_OUTPUT,                                                   /*3*/
        ID_FB_LED,                                                      /*4*/

      _ID_FB_LAST_VAR_NONE_CHANGED,                                     /*5*/

      _ID_FB_FIRST_VAR_CHANGED = _ID_FB_LAST_VAR_NONE_CHANGED,          /*5*/
      
        ID_FB_ALARM = _ID_FB_FIRST_VAR_CHANGED,                         /*5*/
        ID_FB_GROUP_ALARM,                                              /*6*/
        ID_FB_AND,                                                      /*7*/
        ID_FB_OR,                                                       /*8*/
        ID_FB_XOR,                                                      /*9*/
        ID_FB_NOT,                                                      /*10*/

        ID_FB_TIMER,                                                    /*11*/
        ID_FB_TRIGGER,                                                  /*12*/

        ID_FB_MEANDER,                                                  /*13*/
  
      _ID_FB_LAST_VAR_CHANGED,                                          /*14*/
      
    _ID_FB_LAST_VAR = _ID_FB_LAST_VAR_CHANGED,                          /*14*/

  _ID_FB_LAST_ALL = _ID_FB_LAST_VAR                                     /*14*/
};

#define NUMBER_FIX_BLOCKS       (_ID_FB_LAST_FIX - _ID_FB_FIRST_FIX)

#define NUMBER_VAR_BLOCKS_NONE_CHANGED  (_ID_FB_LAST_VAR_NONE_CHANGED - _ID_FB_FIRST_VAR_NONE_CHANGED)
#define NUMBER_VAR_BLOCKS_CHANGED       (_ID_FB_LAST_VAR_CHANGED      - _ID_FB_FIRST_VAR_CHANGED     )

#define NUMBER_VAR_BLOCKS       (NUMBER_VAR_BLOCKS_NONE_CHANGED + NUMBER_VAR_BLOCKS_CHANGED)
#define NUMBER_ALL_BLOCKS       (NUMBER_FIX_BLOCKS + NUMBER_VAR_BLOCKS)

/*
Блок загальних функцій
*/
enum _FIX_BLOCK_output_signals 
{
  FIX_BLOCK_DEFECT = 0,
  FIX_BLOCK_AVAR_DEFECT,
  FIX_BLOCK_SETTINGS_CHANGED,
  
  FIX_BLOCK_OUT
};

enum _FIX_BLOCK_input_signals
{
  FIX_BLOCK_ALARM = 0,
  FIX_BLOCK_MUTE,
  FIX_BLOCK_BLOCK,
  
  FIX_BLOCK_SIGNALS_IN
};
/***/

/*
Дискретні входи
*/
enum _settings_delay_of_INPUT
{
  INPUT_SET_DELAY_DOPUSK = 0,
  
  INPUT_SET_DELAYS
};

enum _work_delay_of_INPUT
{
  INPUT_WORK_DELAY_DOPUSK = 0,
  
  INPUT_WORK_DELAYS
};

enum __index_ctrl_input
{
  INDEX_CTRL_INPUT_TYPE_SIGNAL = 0,
  
  MAX_INDEX_CTRL_INPUT
};

enum _INPUT_output_signals
{
  INPUT_OUT = 0,
  
  INPUT_SIGNALS_OUT
    
};
/***/

/*
Дискретні виходи
*/
enum _OUTPUT_output_signals
{
  OUTPUT_OUT = 0,
  OUTPUT_BOARD,
  
  OUTPUT_SIGNALS_OUT
    
};
enum _OUTPUT_input_signals
{
  OUTPUT_LOGIC_INPUT = 0,
  OUTPUT_RESET,
  OUTPUT_MEANDER1,
  OUTPUT_MEANDER2,
  
  OUTPUT_SIGNALS_IN
};
/***/

/*
Дискретні виходи+світлоіндикатори
*/

enum __index_ctrl_output_led
{
  INDEX_CTRL_OUTPUT_LED_N_T = 0, /*N - normal; T - trigger*/
  INDEX_CTRL_OUTPUT_LED_C_I, /*C - Constant; I - impulse*/
  INDEX_CTRL_OUTPUT_LED_SI_EI, /*SI - simple impulse; EI - expanded impulse*/

  _MAX_INDEX_CTRL_OUTPUT_LED_BITS_SETTINGS,
  
  INDEX_CTRL_OUTPUT_LED_MEANDER1 = _MAX_INDEX_CTRL_OUTPUT_LED_BITS_SETTINGS,
  INDEX_CTRL_OUTPUT_LED_MEANDER2,
  
  MAX_INDEX_CTRL_OUTPUT_LED
};
/***/


/*
Світлоіндикатори
*/
enum _LED_output_signals
{
  LED_OUT = 0,
  LED_BOARD,
  
  LED_SIGNALS_OUT
    
};
enum _LED_input_signals
{
  LED_LOGIC_INPUT = 0,
  LED_RESET,
  LED_MEANDER1,
  LED_MEANDER2,
  
  LED_SIGNALS_IN
};
/***/

/*
Світлозвукова сигналізація
*/
enum _settings_delay_of_ALARM
{
  ALARM_SET_DELAY_PERIOD = 0,
  
  ALARM_SET_DELAYS
};

enum _work_delay_of_ALARM
{
  ALARM_WORK_DELAY_PERIOD = 0,
  
  ALARM_WORK_DELAYS
};

enum _ALARM_output_signals
{
  ALARM_OUT_ALARM = 0,
  ALARM_OUT_MUTE,
  ALARM_OUT_BLOCK,
  
  ALARM_SIGNALS_OUT
    
};
enum _ALARM_input_signals
{
  ALARM_LOGIC_INPUT = 0,
  ALARM_IN_MUTE,
  ALARM_IN_BLOCK,
  ALARM_RESET,
  
  ALARM_SIGNALS_IN
};

enum __index_ctrl_alarm
{
  _MAX_INDEX_CTRL_ALARM_BITS_SETTINGS = 0,
  
  INDEX_CTRL_ALARM_MODE = _MAX_INDEX_CTRL_ALARM_BITS_SETTINGS,
  
  MAX_INDEX_CTRL_ALARM
};

enum _ALARM_modes
{
  ALARM_MODE_SIMPLE = 0,
  ALARM_MODE_TRIGGER,
  ALARM_MODE_PERIOD,
  
  ALARM_MODES_NUMBER
};
/***/

/*
ШГС
*/
enum _settings_pickup_of_GROUP_ALARM
{
  GROUP_ALARM_PICKUP_DELTA_I = 0,
  
  GROUP_ALARM_PICKUPS
};

enum _settings_delay_of_GROUP_ALARM
{
  GROUP_ALARM_SET_DELAY_DELAY = 0,
  
  GROUP_ALARM_SET_DELAYS
};

enum _work_delay_of_GROUP_ALARM
{
  GROUP_ALARM_WORK_DELAY_DELAY = 0,
  
  GROUP_ALARM_WORK_DELAYS
};

enum _GROUP_ALARM_output_signals
{
  GROUP_ALARM_OUT_NNP = 0,
  GROUP_ALARM_OUT_NNM,
  GROUP_ALARM_OUT_CC,
  GROUP_ALARM_OUT_CE,
  GROUP_ALARM_OUT_OC,
  
  GROUP_ALARM_SIGNALS_OUT
    
};

enum __index_ctrl_group_alarm
{
  INDEX_CTRL_GROUP_ALARM_STATE = 0,
  INDEX_CTRL_GROUP_ALARM_CTRL_STATE,

  _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS,
  
  INDEX_CTRL_GROUP_ALARM_I = _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS,
  
  MAX_INDEX_CTRL_GROUP_ALARM
};
/***/

/*
"І"
*/
enum _AND_output_signals
{
  AND_OUT = 0,
  
  AND_SIGNALS_OUT
    
};
/***/

/*
"АБО"
*/
enum _OR_output_signals
{
  OR_OUT = 0,
  
  OR_SIGNALS_OUT
    
};
/***/

/*
"Викл.АБО"
*/
enum _XOR_output_signals
{
  XOR_OUT = 0,
  
  XOR_SIGNALS_OUT
    
};
/***/

/*
"НЕ"
*/
enum _NOT_output_signals
{
  NOT_OUT = 0,
  
  NOT_SIGNALS_OUT
    
};
/***/

/*
"БФ-Таймер"
*/
enum _settings_delay_of_TIMER
{
  TIMER_SET_DELAY_PAUSE = 0,
  TIMER_SET_DELAY_WORK,
  
  TIMER_SET_DELAYS
};

enum _work_delay_of_TIMER
{
  TIMER_WORK_DELAY_PAUSE_RISE = 0,
  TIMER_WORK_DELAY_PAUSE_FALL,
  TIMER_WORK_DELAY_WORK_IMPULSE_RISE,
  TIMER_WORK_DELAY_WORK_DELAY_RISE,
  TIMER_WORK_DELAY_WORK_IMPULSE_FALL,
  
  TIMER_WORK_DELAYS
};

enum _TIMER_output_signals
{
  TIMER_OUT = 0,
  
  TIMER_SIGNALS_OUT
    
};
enum _TIMER_input_signals
{
  TIMER_LOGIC_INPUT = 0,
  TIMER_RESET,
  
  TIMER_SIGNALS_IN
};
/***/

/*
Триґер
*/
enum _TRIGGER_output_signals
{
  TRIGGER_OUT = 0,
  TRIGGER_OUT_INV,
  
  TRIGGER_SIGNALS_OUT
    
};

enum _TRIGGER_input_signals
{
  INPUT_TRIGGER_SET = 0,
  INPUT_TRIGGER_RESET,
  INPUT_TRIGGER_D,
  INPUT_TRIGGER_C,
  
  TRIGGER_SIGNALS_IN
    
};
/***/

/*
ГПС
*/
enum _settings_delay_of_MEANDER
{
  MEANDER_SET_DELAY_PERIOD = 0,
  
  MEANDER_SET_DELAYS
};

enum _work_delay_of_MEANDER
{
  MEANDER_WORK_DELAY_PERIOD = 0,
  
  MEANDER_WORK_DELAYS
};

enum _MEANDER_output_signals
{
  MEANDER_OUT = 0,
  
  MEANDER_SIGNALS_OUT
    
};

enum __index_delay_meander
{
  INDEX_DELAY_MEANDER_PERIOD = 0,
  
  MAX_INDEX_DELAY_MEANDER
};
/***/

#endif
