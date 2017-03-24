#ifndef __GLOBAL_FUNCTIONS_H
#define __GLOBAL_FUNCTIONS_H

#include "stm32f2xx_it.h"

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
   
__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;

void Configure_I2C(I2C_TypeDef*);
void FSMC_SRAM_Init(void);

int main(void);
void periodical_operations(void);
void global_vareiables_installation(void);
void start_settings_peripherals(void);
void start_tim4_canal2_for_interrupt_1mc(void);
void start_tim4_canal3_for_interrupt_10mkc(void);
void min_config(__CONFIG *);
void min_settings(__SETTINGS_FIX *);
void min_settings_INPUT(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_INPUT(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_OUTPUT(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_OUTPUT(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_LED(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_LED(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_ALARM(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_ALARM(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_GROUP_ALARM(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_GROUP_ALARM(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_AND(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_AND(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_OR(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_OR(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_XOR(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_XOR(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_NOT(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_NOT(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_TIMER(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_TIMER(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_TRIGGER(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_TRIGGER(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
void min_settings_MEANDER(unsigned int, uintptr_t *, size_t, size_t);
void copy_settings_MEANDER(unsigned int, unsigned int, uintptr_t *, uintptr_t *, size_t, size_t);
size_t size_all_settings(void);
void copy_settings(__CONFIG *, __SETTINGS_FIX *, __SETTINGS_FIX *, uintptr_t *[], uintptr_t *[]);
unsigned int set_config_and_settings(unsigned int, unsigned int);
void error_reading_with_eeprom(void);

void Interrupts_Config(void);

void lcd_init(void);
unsigned int wait_lcd_ready(void);
unsigned int clear_lcd(void);
unsigned int mode_viewing(unsigned int, unsigned int, unsigned int);
unsigned int hd44780_puts(unsigned char *, unsigned int);
unsigned int Win1251toHd44780 (unsigned int);
unsigned int write_data_to_lcd(unsigned char);
unsigned int write_command_to_lcd(unsigned char);
unsigned int hd44780_gotoxy(unsigned char, unsigned char);
unsigned int hd44780_puts_xy (unsigned char, unsigned char, unsigned char *);
void view_whole_ekran(void);
void check_state_key(GPIO_TypeDef*, uint16_t, unsigned int);
__SETTINGS_FIX* select_struct_settings_fix(void);
int index_language_in_array(int);
void make_ekran_choose_communication_parameters(void);
void make_ekran_name_of_cell(void);
void make_ekran_address(void);
enum _result_pressed_enter_during_edition press_enter_in_address(void);
void press_esc_in_address(void);
void change_address(unsigned int);
void make_ekran_choose_setting_RS485(void);
void make_ekran_baud_RS485(void);
enum _result_pressed_enter_during_edition press_enter_in_baud_RS485(void);
void press_esc_in_baud_RS485(void);
void change_baud_RS485(unsigned int);
void make_ekran_pare_RS485(void);
enum _result_pressed_enter_during_edition press_enter_in_pare_RS485(void);
void press_esc_in_pare_RS485(void);
void change_pare_RS485(unsigned int);
void make_ekran_stopbits_RS485(void);
enum _result_pressed_enter_during_edition press_enter_in_stopbits_RS485(void);
void press_esc_in_stopbits_RS485(void);
void change_stopbits_RS485(unsigned int);
void make_ekran_timeout_RS485(void);
enum _result_pressed_enter_during_edition press_enter_in_timeout_RS485(void);
void press_esc_in_timeout_RS485(void);
void change_timeout_RS485(unsigned int);
void make_ekran_choose_passwords(void);
void make_ekran_password(void);
void move_into_param_list_logical_nodes(unsigned int, int);
void make_ekran_param_list_logical_node(void);

void inc_or_dec_value(unsigned int *, unsigned int);
unsigned int bcd_to_int(unsigned char);

void main_manu_function_ver2(void);
void new_level_menu(void);
void make_ekran_main(void);
void move_into_main(unsigned int, int);
enum _result_pressed_enter_during_edition press_enter_in_main_and_list_passwords(void);
void make_ekran_time(void);
void move_into_time(unsigned int, int);
void change_time(unsigned int);
enum _result_pressed_enter_during_edition press_enter_in_time(void);
void make_ekran_ask_rewrite(void);
unsigned int check_data_for_data_time_menu(void);
void make_ekran_about_info(unsigned int, const uint8_t [][MAX_COL_LCD + 1]);
void make_ekran_configuration(void);
enum _result_pressed_enter_during_edition press_enter_in_configuration(void);
void change_configuration(unsigned int);
void make_ekran_measurement(void);
void move_into_ekran_simple(unsigned int, int);
void convert_and_insert_char_for_measurement(unsigned int, unsigned int, unsigned int, unsigned int, unsigned char *, unsigned int);
void make_ekran_choose_pickup_delay_control(void);
void make_ekran_choose_delay_control(void);
void make_ekran_choose_delay(void);
void make_ekran_choose_control(void);
void move_into_list_settings(unsigned int, int);
void make_ekran_list_settings(void);
void press_esc_in_list_settings(void);
void move_into_list_settings_bios(unsigned int, int);
void make_ekran_list_settings_bios(void);
void press_esc_in_configuration(void);
void make_ekran_list_logical_nodes(void);
void calc_symbol_and_put_into_working_ekran(uint8_t*, void*, void*, unsigned int*, unsigned int, unsigned int, unsigned int);
void calc_int_symbol_and_put_into_working_ekran(uint8_t*, uint32_t*, uint32_t*, unsigned int*);
unsigned int edit_setpoint(unsigned int,  uint32_t, unsigned int, int, unsigned int, unsigned int);
unsigned int check_data_setpoint(unsigned int, unsigned int, unsigned int);
void make_ekran_delay_timer(void);
enum _result_pressed_enter_during_edition press_enter_in_delay_timer(void);
void press_esc_in_delay_timer(void);
void change_delay_timer(unsigned int);
void make_ekran_delay_meander(void);
enum _result_pressed_enter_during_edition press_enter_in_delay_meander(void);
void press_esc_in_delay_meander(void);
void change_delay_meander(unsigned int);
void make_ekran_control_alarm(void);
enum _result_pressed_enter_during_edition press_enter_in_control_alarm(void);
void press_esc_in_control_alarm(void);
void change_control_alarm(unsigned int);
void make_ekran_delay_alarm(void);
enum _result_pressed_enter_during_edition press_enter_in_delay_alarm(void);
void press_esc_in_delay_alarm(void);
void change_delay_alarm(unsigned int);
void make_ekran_control_group_alarm(void);
enum _result_pressed_enter_during_edition press_enter_in_control_group_alarm(void);
void press_esc_in_control_group_alarm(void);
void change_control_group_alarm(unsigned int);
void make_ekran_pickup_group_alarm(void);
enum _result_pressed_enter_during_edition press_enter_in_pickup_group_alarm(void);
void press_esc_in_pickup_group_alarm(void);
void change_pickup_group_alarm(unsigned int);
void make_ekran_delay_group_alarm(void);
enum _result_pressed_enter_during_edition press_enter_in_delay_group_alarm(void);
void press_esc_in_delay_group_alarm(void);
void change_delay_group_alarm(unsigned int);
void make_ekran_control_input(void);
enum _result_pressed_enter_during_edition press_enter_in_control_input(void);
void press_esc_in_control_input(void);
void change_control_input(unsigned int);
void make_ekran_delay_input(void);
enum _result_pressed_enter_during_edition press_enter_in_delay_input(void);
void press_esc_in_delay_input(void);
void change_delay_input(unsigned int);
void make_ekran_control_output_led(void);
enum _result_pressed_enter_during_edition press_enter_in_control_output_led(void);
void press_esc_in_control_output_led(void);
void change_control_output_led(unsigned int);
void make_ekran_setting_language(void);
enum _result_pressed_enter_during_edition press_enter_in_setting_language(void);
void press_esc_in_setting_language(void);
void change_setting_language(unsigned int);
void make_ekran_info(void);
void make_ekran_date_time_pz(void);
void make_ekran_list_labels(void);
void make_ekran_time_config_or_settings(void);
void move_into_diagnostics(unsigned int, int);
void make_ekran_diagnostics(void);
void make_ekran_list_inputs_outputs(void);
void make_ekran_state_inputs_or_outputs(void);
unsigned int max_number_digit_in_number(int);
void move_into_ekran_input_or_output(unsigned int, int);
void make_ekran_list_registrators(void);

__result_dym_mem_select allocate_dynamic_memory_for_settings(__action_dym_mem_select, unsigned int, uintptr_t *[], uintptr_t *[], __CONFIG *, __CONFIG *, __CONFIG *);
__result_dym_mem_select action_after_changing_of_configuration(void);
void calculate_namber_bit_waiting_for_rs_485(void);
void restore_trigger_functions(unsigned int*);
void changing_diagnostyka_state(void);
unsigned int count_number_set_bit(unsigned int*, unsigned int);

void input_scan(void);
void clocking_global_timers(void);
void main_protection(void);
void diagnostyca_adc_execution(void);

void Usb_routines(void);
void USART_RS485_Configure(void);
void restart_monitoring_RS485(void);
void start_transmint_data_via_RS_485(unsigned int);
unsigned short int  AddCRC(unsigned char, unsigned short int);
void modbus_rountines(unsigned int);
void Error_modbus(unsigned char, unsigned char, unsigned char, unsigned char *);
unsigned int Get_data(unsigned char *, unsigned int, unsigned int);
unsigned int Set_data(unsigned short int, unsigned int, unsigned int, /*unsigned int,*/ unsigned int);
//unsigned int Get_data_file(unsigned char*, unsigned char*, unsigned int*, unsigned int);
void set_previous_ranguvannja(void);

ErrorStatus check_errors_i2c(void);
unsigned int start_write_buffer_via_I2C(uint32_t, uint16_t, uint8_t volatile*, uint32_t);
unsigned int start_read_buffer_via_I2C(uint32_t, uint16_t, uint8_t volatile*, uint32_t);
void main_routines_for_i2c(void);
void error_start_i2c(void);

void control_reading_ADCs(void);
void operate_test_ADCs(void);
void method_sum_sqr_data(void);
void calc_measurement(void);
unsigned int norma_value(unsigned long long);
unsigned int sqrt_32(unsigned int);
unsigned int sqrt_64(unsigned long long);
unsigned int get_order(int);

void main_function_for_dataflash_resp(int);
void main_function_for_dataflash_req(int);
void start_checking_dataflash(void);
void start_exchange_via_spi(int, unsigned int);
void dataflash_status_read(int);
void dataflash_set_pagesize_256(int);
void dataflash_erase(int);
void dataflash_mamory_page_program_through_buffer(int);
void dataflash_mamory_read(int);
void dataflash_mamory_page_into_buffer(int);
void dataflash_mamory_write_buffer(int);
void dataflash_mamory_buffer_into_memory(int);
void analize_received_data_dataflash(int);

void control_config(unsigned int);
void control_settings(unsigned int);
void control_ustuvannja(void);
//void control_trg_func(void);
unsigned int control_info_rejestrator(__INFO_REJESTRATOR*, unsigned char);

void test_external_SRAM(void);

void watchdog_routine(void);
void total_error_sw_fixed(unsigned int);

int str_to_int_DATE_Mmm(void);

#endif

