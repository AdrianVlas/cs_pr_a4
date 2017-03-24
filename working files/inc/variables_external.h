extern volatile unsigned int semaphore_adc_irq;
extern volatile unsigned int adc_DATA_VAL_read;
extern volatile unsigned int adc_TEST_VAL_read;
extern volatile unsigned int status_adc_read_work;
extern const unsigned int input_adc[NUMBER_INPUTs_ADCs][2];
extern EXTENDED_OUTPUT_DATA output_adc[NUMBER_INPUTs_ADCs];

extern unsigned int command_word_adc, command_word_adc_work, active_index_command_word_adc;
extern unsigned int state_reading_ADCs;

extern uint32_t previous_tick_VAL;

extern const unsigned int index_GND_ADC[NUMBER_GND_ADC];
extern unsigned int gnd_adc_moment_value[NUMBER_GND_ADC][NUMBER_POINT];
extern unsigned int gnd_adc_averange_sum[NUMBER_GND_ADC];
extern unsigned int gnd_adc_averange[NUMBER_GND_ADC];
extern unsigned int gnd_adc;

extern unsigned int vref_adc_moment_value[NUMBER_POINT];
extern unsigned int vref_adc_averange_sum;
extern unsigned int vref_adc;

extern unsigned int vdd_adc_moment_value[NUMBER_POINT];
extern unsigned int vdd_adc_averange_sum;
extern unsigned int vdd_adc;

extern unsigned int index_array_of_one_value;

extern EXTENDED_SAMPLE ADCs_data_raw[NUMBER_ANALOG_CANALES];
extern int ADCs_data[NUMBER_ANALOG_CANALES];
extern int current_data[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT];
extern unsigned int index_array_of_current_data_value;

extern volatile unsigned int changed_ustuvannja; 
extern unsigned char crc_ustuvannja;
extern unsigned int ustuvannja_meas[NUMBER_ANALOG_CANALES], ustuvannja[NUMBER_ANALOG_CANALES], edit_ustuvannja[NUMBER_ANALOG_CANALES];

extern uint32_t sqr_current_data[NUMBER_POINT][NUMBER_ANALOG_CANALES];
extern uint32_t index_array_of_sqr_current_data;
extern uint32_t bank_sum_sqr_data;
extern uint64_t sum_sqr_data_irq[NUMBER_ANALOG_CANALES];
extern uint64_t sum_sqr_data[2][NUMBER_ANALOG_CANALES];

extern volatile unsigned int semaphore_measure_values_low1;

extern unsigned int number_inputs_for_fix_one_second;
extern volatile unsigned int measurement[NUMBER_ANALOG_CANALES];
extern unsigned int measurement_high[2][NUMBER_ANALOG_CANALES], bank_measurement_high;
extern unsigned int measurement_middle[NUMBER_ANALOG_CANALES]; 
extern unsigned int measurement_low[NUMBER_ANALOG_CANALES]; 

extern const uint32_t alarm_ctrl_patten[MAX_INDEX_CTRL_ALARM][2];
extern const uint32_t group_alarm_analog_ctrl_patten[MAX_INDEX_CTRL_GROUP_ALARM - _MAX_INDEX_CTRL_GROUP_ALARM_BITS_SETTINGS][2];
extern volatile unsigned int state_inputs;
extern uint8_t fix_block_active_state[DIV_TO_HIGHER(FIX_BLOCK_OUT, 8)];
extern uint8_t fix_block_trigger_state[DIV_TO_HIGHER(FIX_BLOCK_OUT, 8)];
//extern uint8_t trigger_active_functions[DIV_TO_HIGHER(FIX_BLOCK_OUT, 8)], trigger_active_functions_ctrl[DIV_TO_HIGHER(FIX_BLOCK_OUT, 8)];
//extern unsigned char crc_trg_func, crc_trg_func_ctrl;
extern unsigned int pressed_buttons;
extern volatile unsigned int activation_function_from_interface;
extern volatile unsigned int reset_trigger_function_from_interface;
extern unsigned int diagnostyka_before[3];
extern volatile unsigned int diagnostyka[3];
extern volatile unsigned int set_diagnostyka[3];
extern volatile unsigned int clear_diagnostyka[3];

extern int global_timers[MAX_NUMBER_GLOBAL_TIMERS];

extern unsigned int start_restart;

extern unsigned char working_ekran[MAX_ROW_LCD][MAX_COL_LCD];
extern uint16_t rewrite_ekran_once_more;

extern volatile unsigned int new_state_keyboard;
extern unsigned char time_set_keyboard[NUMBER_KEY_KEYBOARD];

extern uint16_t time_rewrite;

//Меню версії 2
extern __CURRENT_STATE_MENU2 current_state_menu2;
extern int16_t position_in_current_level_menu2[MAX_NUMBER_MENU2_LEVEL]; //Масив у якому збкрігається індекс текучої позиції
extern enum _menu2_levels previous_level_in_current_level_menu2[MAX_NUMBER_MENU2_LEVEL];
extern enum _menu2_levels next_level_in_current_level_menu2[MAX_NUMBER_MENU2_LEVEL];    //Масив у якому збкрігається занчення екранів куди ми хочемо перейти з поточного екрану
extern void *p_menu_param_1, *p_menu_param_2;

extern volatile unsigned int periodical_tasks_TEST_CONFIG;
extern volatile unsigned int periodical_tasks_TEST_SETTINGS;
extern volatile unsigned int periodical_tasks_TEST_USTUVANNJA;
//extern volatile unsigned int periodical_tasks_TEST_TRG_FUNC;
//extern volatile unsigned int periodical_tasks_TEST_TRG_FUNC_LOCK;
extern volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR;
extern volatile unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK;
extern volatile unsigned int periodical_tasks_TEST_FLASH_MEMORY;

extern const unsigned char odynyci_vymirjuvannja[MAX_NAMBER_LANGUAGE][NUMBER_ODYNYCI_VYMIRJUVANNJA];

extern uint16_t fixed_power_down_into_RTC; 
extern unsigned char time[7]; 
extern unsigned char time_copy[7]; 
extern unsigned char calibration;
extern unsigned char calibration_copy;
extern uint16_t copying_time;
extern unsigned char time_edit[7]; 
extern unsigned char calibration_edit;
extern uint16_t copy_register8_RTC;
extern int16_t etap_reset_of_bit;
extern int16_t etap_settings_test_frequency;
extern unsigned char temp_register_rtc[2];

//Конфігурація і Налаштування
extern __CONFIG current_config_prt, current_config, current_config_edit;
extern uintptr_t *spca_of_p_prt[NUMBER_VAR_BLOCKS], *sca_of_p[NUMBER_VAR_BLOCKS], *sca_of_p_edit[NUMBER_VAR_BLOCKS]; /*spca_of_p_prt = settings & protection control array of point for protection; sca_of_p = settings control array of point*/
extern unsigned char crc_config;

extern __SETTINGS_FIX settings_fix_prt, settings_fix, settings_fix_edit;
extern uint8_t crc_settings;
extern unsigned int config_settings_modified;

//Змінні для визначеня ресурсу процесора-програми
extern volatile unsigned int restart_resurs_count;
extern unsigned int resurs_temp;
extern unsigned int resurs_global;
extern unsigned int resurs_global_min;
extern unsigned int resurs_global_max;

extern unsigned int restart_timing_watchdog;
extern unsigned int time_1_watchdog_input;
extern unsigned int time_2_watchdog_input;
extern unsigned int time_delta_watchdog_input;
extern unsigned int time_delta_watchdog_input_min;
extern unsigned int time_delta_watchdog_input_max;

extern unsigned int time_1_watchdog_output;
extern unsigned int time_2_watchdog_output;
extern unsigned int time_delta_watchdog_output;
extern unsigned int time_delta_watchdog_output_min;
extern unsigned int time_delta_watchdog_output_max;

extern short int word_SRAM1;

extern unsigned char Temporaty_I2C_Buffer[SIZE_PAGE_EEPROM + 2];
extern uint16_t number_busy_state;
extern uint16_t type_error_of_exchanging_via_i2c;
extern uint16_t low_speed_i2c;
extern __DRIVER_I2C driver_i2c;
extern uint32_t control_i2c_taskes[2];
extern uint16_t comparison_writing;
extern uint32_t state_i2c_task;
extern unsigned char read_write_i2c_buffer[SIZE_BUFFER_FOR_EEPROM_EXCHNGE];

//DataFlash
extern unsigned char RxBuffer_SPI_DF[SIZE_PAGE_DATAFLASH_MAX + 10];
extern unsigned char TxBuffer_SPI_DF[SIZE_PAGE_DATAFLASH_MAX + 10];
extern unsigned int number_bytes_transfer_spi_df;
extern unsigned int number_bytes_transfer_spi_df_copy;
extern unsigned char TxBuffer_SPI_DF_copy[SIZE_PAGE_DATAFLASH_MAX + 10];
extern unsigned int code_operation_copy;
extern int number_chip_dataflsh_exchange;
extern __DRIVER_SPI_DF driver_spi_df[NUMBER_DATAFLASH_CHIP];
extern volatile unsigned int error_into_spi_df;
extern unsigned int dataflash_not_busy;
extern volatile unsigned int control_tasks_dataflash;
extern unsigned char buffer_for_manu_read_record[SIZE_ONE_RECORD_PR_ERR];
extern unsigned char buffer_for_USB_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];
extern unsigned char buffer_for_RS485_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];

extern unsigned int what_we_are_reading_from_dataflash_1;
extern unsigned int what_we_are_reading_from_dataflash_2;

//Реєстратор програмних помилок
extern unsigned char crc_info_rejestrator_pr_err;
extern volatile __INFO_REJESTRATOR info_rejestrator_pr_err;
extern unsigned char crc_info_rejestrator_pr_err_ctrl;
extern __INFO_REJESTRATOR info_rejestrator_pr_err_ctrl;
extern unsigned char buffer_pr_err_records[SIZE_BUFFER_FOR_PR_ERR];
extern volatile unsigned int head_fifo_buffer_pr_err_records;
extern volatile unsigned int tail_fifo_buffer_pr_err_records;
extern volatile unsigned int temporary_block_writing_records_pr_err_into_DataFlash;
extern unsigned int etap_writing_pr_err_into_dataflash;
extern unsigned int number_recods_writing_into_dataflash_now;
extern unsigned int number_record_of_pr_err_into_menu;
extern unsigned int number_record_of_pr_err_into_USB;
extern unsigned int number_record_of_pr_err_into_RS485;

//Очистка інформації по реєстраторах
extern volatile unsigned int clean_rejestrators;

extern const uint8_t letters[MAX_NYMBER_EXTENDED_ASCII_SYMBOLS][2];
extern const uint8_t extra_letters[MAX_NYMBER_EXTRA_EXTENDED_ASCII_SYMBOLS][1 + MAX_NAMBER_LANGUAGE];

extern int current_language;

//RS-485
extern unsigned char TxBuffer_RS485[BUFFER_RS485];
extern unsigned char RxBuffer_RS485[BUFFER_RS485];
extern int TxBuffer_RS485_count;
extern int volatile RxBuffer_RS485_count;
extern int RxBuffer_RS485_count_previous;
extern uint32_t time_last_receive_byte;
extern uint32_t max_reaction_time_rs_485;
extern uint16_t make_reconfiguration_RS_485;
extern volatile uint16_t number_bits_rs_485_waiting;
extern uint16_t mark_current_tick_RS_485;
extern unsigned int timeout_idle_RS485;

//USB
extern uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE]; 
extern uint32_t USART_Rx_ptr_in;
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;

extern uint8_t  USB_Tx_State;

//Для UDP
extern volatile u32 count_out;
extern u32 count_out_previous;
extern uint16_t previous_count_tim4_USB;
extern u8 buffer_out[BUFFER_USB];
extern unsigned char usb_received[BUFFER_USB];
extern unsigned char usb_transmiting[BUFFER_USB];
extern int usb_received_count;
extern int usb_transmiting_count;
extern unsigned char data_usb_transmiting;
extern unsigned int timeout_idle_USB;

//MODBUS-RTU
extern uint32_t registers_address_read;
extern uint32_t registers_address_write;
extern uint32_t data_write_to_memory;
extern uint16_t number_registers_read;
extern uint16_t registers_values[64] /*@ "variables_RAM1"*/;
extern uint16_t action_is_continued;
extern uint16_t part_transmit_carrent_data;
extern uint16_t command_to_receive_current_data;
extern int16_t current_data_transmit[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT] /*@ "variables_RAM1"*/;
extern volatile uint16_t wait_of_receiving_current_data; 
extern uint16_t password_set_USB, password_set_RS485;
extern uint16_t password_changed;
extern uint16_t password_ustuvannja;
extern uint32_t *point_to_edited_rang;
extern uint16_t number_32bit_in_target;
//extern uint32_t clear_array_rang[N_BIG];
//extern uint32_t set_array_rang[N_BIG];
extern uint16_t restart_timeout_interface;
extern unsigned int timeout_idle_new_settings;
extern uint16_t restart_timeout_idle_new_settings;
extern uint16_t type_of_settings_changed_from_interface;

extern unsigned int serial_number_dev;
extern unsigned int edit_serial_number_dev;

extern volatile unsigned int control_word_of_watchdog;
extern unsigned int test_watchdogs;

//Змінна глобальної помилки
extern unsigned int total_error;

extern unsigned short const __checksum;
extern unsigned int __checksum_begin;
extern unsigned int __checksum_end;

extern unsigned int __ICFEDIT_region_RAM1_start__;
extern unsigned int __ICFEDIT_region_RAM1_size__;


#ifdef DEBUG_TEST
//extern unsigned int time_1, time_2, max_delay;

//Тимчасові змінні
//extern unsigned int temp_value_for_debbuging_1;
//extern unsigned int temp_value_for_debbuging_2;
//extern unsigned int temp_value_for_debbuging_3;


#endif
