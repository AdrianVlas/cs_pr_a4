#ifndef __TYPE_DEFINITION__
#define __TYPE_DEFINITION__

#define SRAM1 _Pragma("location=\"variables_RAM1\"")

enum _edition_stats
{
  ED_VIEWING = 0,               /* 0 - ���� ����� �� � ����� ����������  */
  ED_CAN_BE_EDITED,             /* 1 - ���� ����� �� � ����� ���������� ��� � ������ �������� � ����� ����������� ��� ������� �������� ������  */
  ED_EDITION,                   /* 2 - ���� ����� � ����� �����������  */
  ED_CONFIRM_CHANGES,           /* 3 - ���� ���� ������������ �����������  */ 
  ED_WARNING_EDITION_BUSY,      /* 4 - � ������ ��������� ��������� �������  ��� ����������� �������� � ����� ����������� (���������� ���� ��� ������� � ������ ������� Enter �������� make_ekran_about_info. �� ����������� Enter ���������� � ���� ������ ���)*/
  ED_WARNING_ENTER_ESC,         /* 5 - � ������ ��������� ��������� �������  (���������� ���� ��� ������� � ����� Enter/Esc �������� �������� make_ekran_about_info. �� ����������� Enter ���������� � ���� ������ ���)*/
  ED_WARNING_ENTER,             /* 6 - � ������ ��������� ��������� �������  (���������� ���� ��� ������� � ������ ������� Enter �������� make_ekran_about_info. �� ����������� Enter ���������� � ���� ������ ���)*/
  ED_INFO,                      /* 7 - � ������ ��������� ��������� ����������� ������������� �� ����� ����� �����������  (���������� ���� ���������� � ������ ������� Enter �������� make_ekran_about_info) �� ����������� Enter ����������� � �������� ����*/
  ED_ERROR                      /* 8 - � ������ ��������� ��������� �������� �������  (�������� ���������� ��� ����-��� ��������� ��������� ����-��� ������)*/
};

enum _result_pressed_enter_during_edition
{
  RPEDE_NONE = 0,
  RPEDE_DATA_NOT_CHANGED,
  RPEDE_DATA_CHANGED_OK,
  RPEDE_DATA_CHANGED_OUT_OF_RANGE,
  RPEDE_DATA_CHANGED_WRONG_RETURN_OK,
  RPEDE_DATA_CHANGED_WRONG_RETURN_BAD,
};

typedef struct
{
  enum _menu2_levels current_level;   //������� ����� �������������� ������
  uint16_t number_selection;          //����� ��������� �������� (��������������� �����, ������...)
  
  int16_t index_position;             //����� �� ��� �� ����� � �������

  int16_t position_cursor_x;          //X - ���������� �������
  int16_t position_cursor_y;          //Y - ���������� �������
  
  int *p_max_row;                     //�������� �� ����������� ������� �����
  int max_row;                        //����������� ������� �����
  
  void (*func_move)(unsigned int, int);                                 //�������� �� �������, ��� ���������� �� ��������� ����  
  void (*func_show)(void);                                              //�������� �� �������, ��� ����������� ��������� ����  
  enum _result_pressed_enter_during_edition (*func_press_enter)(void);  //�������� �� �������, ��� ��������� 䳿 �� ����������� ������ Enter
  void (*func_press_esc)(void);                                         //�������� �� �������, ��� ��������� 䳿 �� ����������� ������ Esc
  void (*func_change)(unsigned int);                                    //�������� �� �������, ��� ���� �������� ������� ������� � ��������� ����
  
  unsigned int binary_data;           //1 - ����� ����������� ������ ����������/0 - ����� ����������� �������� ����������
  
  enum _edition_stats edition;
  
  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
  
  unsigned int current_action;        //ĳ� ��� ����� �������� � ������� �������
                                      //0 - ͳ���� �� ����������
                                      //1 - ���������� ������, �/��� ������ ���� ���� �����������
                                      //2 - ������� �������� ����������
}__CURRENT_STATE_MENU2;

typedef struct
{
  int position_cursor_x;              //X - ���������� �������

  unsigned int cursor_on;             //1 - ������ ������������/ 0 - ������ �� ������������
  unsigned int cursor_blinking_on;    //1 - ������ ����/ 0 - ������ �� ����
} __PREVIOUS_STATE_CURSOR;

/**********
���������� ����
**********/
typedef struct
{
  
  int32_t set_delay[INPUT_SET_DELAYS];
  uint32_t control;
  
} __settings_for_INPUT;

typedef struct
{
  __settings_for_INPUT settings;
  
  int32_t work_delay[INPUT_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(INPUT_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(INPUT_SIGNALS_OUT, 8)];

} __LN_INPUT;
/**********/

/**********
���������� ���� (����)
**********/
typedef struct
{
  
  uint32_t control;
  uint32_t param[OUTPUT_SIGNALS_IN];
  
} __settings_for_OUTPUT;

typedef struct
{
  __settings_for_OUTPUT settings;

  uint8_t active_state[DIV_TO_HIGHER(OUTPUT_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(OUTPUT_SIGNALS_OUT, 8)];

} __LN_OUTPUT;
/**********/

/**********
�������������
**********/

typedef struct
{
  
  uint32_t control;
  uint32_t param[LED_SIGNALS_IN];
  
} __settings_for_LED;

typedef struct
{
  __settings_for_LED settings;

  uint8_t active_state[DIV_TO_HIGHER(LED_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(LED_SIGNALS_OUT, 8)];

} __LN_LED;
/**********/

/**********
������������ �����������
**********/
typedef struct
{
  int32_t set_delay[ALARM_SET_DELAYS];
  uint32_t control;
  uint32_t param[ALARM_SIGNALS_IN];
  
} __settings_for_ALARM;

typedef struct
{
  __settings_for_ALARM settings;

  int32_t work_delay[ALARM_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(ALARM_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(ALARM_SIGNALS_OUT, 8)];

} __LN_ALARM;
/**********/

/**********
���
**********/
typedef struct
{
  int32_t pickup[GROUP_ALARM_PICKUPS];
  int32_t set_delay[GROUP_ALARM_SET_DELAYS];
  uint32_t control;
  uint32_t analog_input_control;
  
} __settings_for_GROUP_ALARM;

typedef struct
{
  __settings_for_GROUP_ALARM settings;

  int32_t work_delay[GROUP_ALARM_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(GROUP_ALARM_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(GROUP_ALARM_SIGNALS_OUT, 8)];
  uint32_t NNC; /*New number of Curcuit*/

} __LN_GROUP_ALARM;
/**********/

/**********
������� ���������� ����� "�"
**********/
typedef struct
{
  
  uint32_t param[AND_SIGNALS_IN];
  
} __settings_for_AND;

typedef struct
{
  __settings_for_AND settings;

  uint8_t active_state[DIV_TO_HIGHER(AND_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(AND_SIGNALS_OUT, 8)];

} __LN_AND;
/**********/

/**********
������� ���������� ����� "���"
**********/
typedef struct
{
  
  uint32_t param[OR_SIGNALS_IN];
  
} __settings_for_OR;

typedef struct
{
  
  __settings_for_OR settings;

  uint8_t active_state[DIV_TO_HIGHER(OR_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(OR_SIGNALS_OUT, 8)];
  
} __LN_OR;
/**********/

/**********
������� ���������� ����� "����.���"
**********/
typedef struct
{
  
  uint32_t param[2];
  
} __settings_for_XOR;

typedef struct
{
  __settings_for_XOR settings;
  
  uint8_t active_state[DIV_TO_HIGHER(XOR_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(XOR_SIGNALS_OUT, 8)];
  
} __LN_XOR;
/**********/

/**********
������� ���������� ����� "��"
**********/
typedef struct
{
  
  uint32_t param;
  
} __settings_for_NOT;

typedef struct
{
  
  __settings_for_NOT settings;
  
  uint8_t active_state[DIV_TO_HIGHER(NOT_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(NOT_SIGNALS_OUT, 8)];
  
} __LN_NOT;
/**********/

/**********
�������������������� ������
**********/
typedef struct
{
  
  int32_t set_delay[TIMER_SET_DELAYS];
  uint32_t param[TIMER_SIGNALS_IN];
  
} __settings_for_TIMER;

typedef struct
{
  
  __settings_for_TIMER settings;
  
  int32_t work_delay[TIMER_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(TIMER_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(TIMER_SIGNALS_OUT, 8)];
  
} __LN_TIMER;
/**********/

/**********
�����
**********/
typedef struct
{
  
  uint32_t param[TRIGGER_SIGNALS_IN];
  
} __settings_for_TRIGGER;

typedef struct
{
  
  __settings_for_TRIGGER settings;
  
  uint8_t active_state[DIV_TO_HIGHER(TRIGGER_SIGNALS_OUT, 8)];
  uint8_t trigger_state[DIV_TO_HIGHER(TRIGGER_SIGNALS_OUT, 8)];
  
} __LN_TRIGGER;
/**********/

/**********
�������������� ���� "��������� ����������� �������"
**********/
typedef struct
{
  
  int32_t set_delay[MEANDER_SET_DELAYS];
  
} __settings_for_MEANDER;

typedef struct
{
  
  __settings_for_MEANDER settings;
  
  int32_t work_delay[MEANDER_WORK_DELAYS];
  uint8_t active_state[DIV_TO_HIGHER(MEANDER_SIGNALS_OUT, 8)];
  
} __LN_MEANDER;
/**********/

typedef enum _action_dyn_mem_select
{
  MAKE_DYN_MEM = 0,
  REMAKE_DYN_MEM,
  RESTORE_DYN_MEM
    
} __action_dym_mem_select;

typedef enum _result_dyn_mem_select
{
  DYN_MEM_TOTAL_ERROR = 0,
  DYN_MEM_NO_ENOUGH_MEM,
  DYN_MEM_SELECT_OK
    
} __result_dym_mem_select;

/**********
������������
**********/
typedef struct
{
  uint32_t device_id;                   //��� ��������
  
  uint32_t n_input;                     //ʳ������ ���������� �����
  uint32_t n_output;                    //ʳ������ ���������� ������
  uint32_t n_led;                       //ʳ������ ���������� ��������������
  
  uint32_t n_alarm;                     //ʳ������ ����� �����������
  uint32_t n_group_alarm;               //����./����. �������� �������� ������
  uint32_t n_and;                       //ʳ������ �������� "�"
  uint32_t n_or;                        //ʳ������ �������� "���"
  uint32_t n_xor;                       //ʳ������ �������� "����.���"
  uint32_t n_not;                       //ʳ������ �������� "��"
  uint32_t n_timer;                     //ʳ������ �������
  uint32_t n_trigger;                   //ʳ������ ������

  uint32_t n_meander;                   //ʳ������ ���������� �������


  uint8_t time_config[7+1];       //��� ������� ��� �������-��������-���������
                                        //������� ���� ������ �������� ���� ����� ���� ���� ��������
                                        //0 - ������� ���������
                                        //1 - ���������
                                        //2 - USB
                                        //3 - RS-485
  
} __CONFIG;
/**********/

/**********
������������, �� ������ ������� � ������ ��� ��������
**********/
typedef struct
{
  uint32_t password_1;                                          //������ ��� ����������� � ����
  uint32_t password_2;                                          //������ ��� ����������� � ����
  uint32_t timeout_deactivation_password_interface_USB;         //��� ����������� ������ ��� ����������� � ���������� USB
  uint32_t password_interface_USB;                              //������ ��� ����������� � ���������� USB
  uint32_t timeout_deactivation_password_interface_RS485;       //��� ����������� ������ ��� ����������� � ���������� RS485
  uint32_t password_interface_RS485;                             //������ ��� ����������� � ���������� RS485
  
  uint32_t timeout_idle_new_settings;
  
  //����������
  uint8_t name_of_cell[MAX_CHAR_IN_NAME_OF_CELL];              //�'�� ������
  uint16_t user_register[(M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1]; //������� �����������
  uint32_t address;                                             //������
  int32_t baud_RS485;                                           //�������� �����
                                                                // 0 - 9600
                                                                // 1 - 14400
                                                                // 2 - 19200
                                                                // 3 - 28800
                                                                // 4 - 38400
                                                                // 5 - 57600
                                                                // 6 - 115200
  int32_t pare_bit_RS485;                                       //�������
                                                                // 0 - NONE
                                                                // 1 - ODD
                                                                // 2 - EVEN
  int32_t number_stop_bit_RS485;                                //������� ����-��
                                                                // 0 - 1 stop-bit
                                                                // 1 - 2 stop-bits
  uint32_t time_out_1_RS485;                                    //time-out ���������� ������� = X/10 �������
  
  int32_t language;                                             //���� ����  0= ����� ��� �� �����������; 1=RU; 2=UA; 3=EN; 4=KZ; 5=��.
  
  unsigned char time_setpoints[7+1];                            //��� ������� ��� �������-��������-���������
                                                                //������� ���� ������ �������� ���� ����� ���� ���� ��������
                                                                //0 - ������� ���������
                                                                //1 - ���������
                                                                //2 - USB
                                                                //3 - RS-485
  
} __SETTINGS_FIX;
/**********/

typedef struct
{
  //���� �����
  int16_t state_execution;        //-1 - ������� ������� �� ������� ����� ����������
                              // 0 - ���������� ����
                              // 1 - ���� ���������� ��� �������
                              // 2 - ���� ���������� � ���������
  
  
  //������������� ��������, � ���� ������������
  int16_t device_id;              //-1 - ������� �� ����������
                              // EEPROM_ADDRESS - EEPROM
                              // RTC_ADDRESS - RTC
  //��� ��������
  int16_t action;                 //-1 - �� ����������
                              // 0 - ����� ������ ��� ���������� ����������
                              // 1 - ����������
                              // 2 - ����� ������ � ����� �����
  

  //�������� ������ �� ��� ���� ��� ���������
  uint16_t internal_address;

  //ʳ������ ���� ��� �������/������ (��������)
  unsigned int number_bytes;
  
  //�������� �� ����� (��������)
  uint8_t volatile* point_buffer;

} __DRIVER_I2C;

typedef struct
{
  unsigned int next_address;
  unsigned int saving_execution;
  unsigned int number_records;
} __INFO_REJESTRATOR;

typedef struct
{
  unsigned int state_execution;     //���� ���������� �������������
  
  unsigned int code_operation;      //��� ���������� ��������

} __DRIVER_SPI_DF;

typedef enum __STATE_READING_ADCs 
{
  STATE_READING_ADCs_NONE = 0,
  STATE_READING_WRITE,
  STATE_READING_WRITE_READ,
  STATE_READING_READ
} STATE_READING_ADCs;

typedef struct
{
  uint32_t tick;
  unsigned int value;

} EXTENDED_OUTPUT_DATA;

typedef struct
{
  uint32_t tick;
  int value;
} EXTENDED_SAMPLE;


#endif
