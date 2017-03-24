/* Includes ------------------------------------------------------------------*/
#include "constants.h"
#include "libraries.h"
#include "variables_global.h"
#include "functions_global.h"
#include "../v_A_shm/I_Shm.h"
#include <intrinsics.h.>

/*******************************************************************************/
//Робота з Wotchdog
/*******************************************************************************/
inline void watchdog_routine(void)
{
  time_1_watchdog_input = time_2_watchdog_input;
  time_2_watchdog_input = TIM4->CNT;
  unsigned int delta_time;
  if (time_2_watchdog_input >= time_1_watchdog_input) delta_time = time_2_watchdog_input - time_1_watchdog_input;
  else delta_time = time_2_watchdog_input + 0xffff - time_1_watchdog_input;
  time_delta_watchdog_input = delta_time* 10;
  
  //Робота з watchdogs з контролем всіх інших систем
  if((control_word_of_watchdog & UNITED_BITS_WATCHDOG) == UNITED_BITS_WATCHDOG)
  {
    //Змінюємо стан біту зовнішнього Watchdog на протилежний
    if (test_watchdogs != CMD_TEST_EXTERNAL_WATCHDOG)
    {
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );

      time_1_watchdog_output = time_2_watchdog_output;
      time_2_watchdog_output = TIM4->CNT;
      if (time_2_watchdog_output >= time_1_watchdog_output) delta_time = time_2_watchdog_output - time_1_watchdog_output;
      else delta_time = time_2_watchdog_output + 0xffff - time_1_watchdog_output;
      time_delta_watchdog_output = delta_time* 10;
    }

    control_word_of_watchdog =  0;
  }
#ifdef DEBUG_TEST
  else
  {
    unsigned int time_1_watchdog_output_tmp = time_2_watchdog_output;
    unsigned int time_2_watchdog_output_tmp = TIM4->CNT;
    if (time_2_watchdog_output_tmp >= time_1_watchdog_output_tmp) delta_time = time_2_watchdog_output_tmp - time_1_watchdog_output_tmp;
    else delta_time = time_2_watchdog_output_tmp + 0xffff - time_1_watchdog_output_tmp;
    unsigned int time_delta_watchdog_output_tmp = delta_time* 10;
    
    if (time_delta_watchdog_output_tmp > 100000)
    {
      while(time_delta_watchdog_output_tmp != 0);
    }
  }
#endif

  if (restart_timing_watchdog == 0)
  {
    if (time_delta_watchdog_input < time_delta_watchdog_input_min) time_delta_watchdog_input_min = time_delta_watchdog_input;
    if (time_delta_watchdog_input > time_delta_watchdog_input_max) time_delta_watchdog_input_max = time_delta_watchdog_input;

    if (time_delta_watchdog_output < time_delta_watchdog_output_min) time_delta_watchdog_output_min = time_delta_watchdog_output;
    if (time_delta_watchdog_output > time_delta_watchdog_output_max) time_delta_watchdog_output_max = time_delta_watchdog_output;
  }
  else
  {
    restart_timing_watchdog = 0;
        
    time_delta_watchdog_input = 0;
    time_delta_watchdog_input_min = 0xffff*10;
    time_delta_watchdog_input_max = 0;
        
    time_delta_watchdog_output = 0;
    time_delta_watchdog_output_min = 0xffff*10;
    time_delta_watchdog_output_max = 0;
  }
}
/*******************************************************************************/

/*************************************************************************
Періодичні низькопріоритетні задачі
*************************************************************************/
inline void periodical_operations(void)
{
  //Обміну через I2C
  if (
      (control_i2c_taskes[0]     != 0) || 
      (control_i2c_taskes[1]     != 0) || 
      (driver_i2c.state_execution > 0)
     )
    main_routines_for_i2c();

  //Обробка дій системи меню
  main_manu_function_ver2();
  //Обновляємо інформацію на екрані
  view_whole_ekran();
    
  //Робота з Watchdog
  watchdog_routine();

  //Робота з таймером очікування нових змін налаштувань
  if ((timeout_idle_new_settings >= settings_fix.timeout_idle_new_settings) && (restart_timeout_idle_new_settings == 0))
  {
    unsigned int result = set_config_and_settings(0, NO_MATTER_PARAMS_FIX_CHANGES);
    if (result != 0)
    {
      //Повідомляємо про критичну помилку
      current_state_menu2.edition = ED_ERROR;
    }
    config_settings_modified = 0;
    type_of_settings_changed_from_interface = 0;
  }
  //Фіксація сигналу про те що налаштуванння/конфігурація змінені чи ні
  if ((config_settings_modified & (MASKA_CHANGED_CONFIGURATION | MASKA_CHANGED_SETTINGS)) != 0) 
  {
    _SET_BIT(fix_block_active_state, FIX_BLOCK_SETTINGS_CHANGED);
  }
  else
  {
    _CLEAR_BIT(fix_block_active_state, FIX_BLOCK_SETTINGS_CHANGED);
  }
  
  //Обмін по USB
  if (settings_fix.password_interface_USB)
  {
    unsigned int timeout = settings_fix.timeout_deactivation_password_interface_USB;
    if ((timeout != 0) && (timeout_idle_USB >= timeout) && ((restart_timeout_interface & (1 << USB_RECUEST)) == 0)) password_set_USB = 1;
  }
  Usb_routines();

  //Обмін по RS-485
  if (settings_fix.password_interface_RS485)
  {
    unsigned int timeout = settings_fix.timeout_deactivation_password_interface_RS485;
    if ((timeout != 0) && (timeout_idle_RS485 >= timeout) && ((restart_timeout_interface & (1 << RS485_RECUEST)) == 0)) password_set_RS485 = 1;
  }
  if(
     ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) == 0) &&
     (RxBuffer_RS485_count != 0) &&
     (make_reconfiguration_RS_485 == 0)
    )
  {
    //Це є умовою, що дані стоять у черзі  на обробку
      
    //Робота з Watchdog
    watchdog_routine();

    //Обробляємо запит
    modbus_rountines(RS485_RECUEST);
  }
  else if (make_reconfiguration_RS_485 != 0)
  {
    //Стоїть умова переконфігурувати RS-485
      
    //Перевіряємо чи на даний моент не іде передача даних на верхній рівень
    if (GPIO_ReadOutputDataBit(GPIO_485DE, GPIO_PIN_485DE) == Bit_RESET)
    {

      //Переконфігуровуємо USART для RS-485
      USART_RS485_Configure();

      //Відновлюємо моніторинг каналу RS-485
      restart_monitoring_RS485();
      
      //Знімаємо індикацю про невикану переконфігупацію інтерфейсу RS-485
      make_reconfiguration_RS_485 = 0;
    }
  }

  /*******************/
  //Контроль достовірності важливих даних
  /*******************/
  /*
  Я перевіряю поставлені задачі через
  if ()
  else if()
  else if()
  ...
  else if ()
  Щоб за один оберт виконувалася тільки одна перевірка, тобто щоб в одному оберті
  не було надто довга затримка на фонову перевірку, хоч і важливу.
  */
  if (periodical_tasks_TEST_CONFIG != 0)
  {
    //Стоїть у черзі активна задача самоконтролю конфігурації
    if ((state_i2c_task & STATE_CONFIG_EEPROM_GOOD) != 0)
    {
      //Перевірку здійснюємо тільки тоді, коли конфігурація була успішно прочитана
      if (
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_CONFIG_EEPROM_BIT) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_CONFIG_EEPROM_BIT    ) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_CONFIG_EEPROM_BIT ) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_CONFIG_EEPROM_BIT    ) == 0)
         ) 
      {
        //На даний моммент не іде читання-запис конфігурації, тому можна здійснити контроль достовірності
        control_config(config_settings_modified);

        //Скидаємо активну задачу самоконтролю конфігурації
        periodical_tasks_TEST_CONFIG = false;
      }
    }
    else
    {
      //Скидаємо активну задачу самоконтролю таблиці конфігурації, бо не було її успішне зчитування
      periodical_tasks_TEST_CONFIG = false;
    }
  }
  else if (periodical_tasks_TEST_SETTINGS != 0)
  {
    //Стоїть у черзі активна задача самоконтролю таблиці настройок
    if ((state_i2c_task & STATE_SETTINGS_EEPROM_GOOD) != 0)
    {
      //Перевірку здійснюємо тільки тоді, коли таблиця настройок була успішно прочитана
      if (
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT    ) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT ) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_SETTINGS_EEPROM_BIT    ) == 0)
         ) 
      {
        //На даний моммент не іде читання-запис таблиці настройок, тому можна здійснити контроль достовірності
        control_settings(config_settings_modified);

        //Скидаємо активну задачу самоконтролю таблиці настройок
        periodical_tasks_TEST_SETTINGS = false;
      }
    }
    else
    {
      //Скидаємо активну задачу самоконтролю таблиці настройок, бо не було її успішне зчитування
      periodical_tasks_TEST_SETTINGS = false;
    }
  }
  else if (periodical_tasks_TEST_USTUVANNJA != 0)
  {
    //Стоїть у черзі активна задача самоконтролю юстування (і щоб не ускладнювати задачу і серійного номеру пристрою)
    if ((state_i2c_task & STATE_USTUVANNJA_EEPROM_GOOD) != 0)
    {
      //Перевірку здійснюємо тільки тоді, коли юстування було успішно прочитане
      if (
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT    ) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT ) == 0) &&
          (_CHECK_SET_BIT(control_i2c_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT    ) == 0) &&
          (changed_ustuvannja == CHANGED_ETAP_NONE)  
         ) 
      {
        //На даний моммент не іде читання-запис юстування, тому можна здійснити контроль достовірності
        control_ustuvannja();

        //Скидаємо активну задачу самоконтролю юстування
        periodical_tasks_TEST_USTUVANNJA = false;
      }
    }
    else
    {
      //Скидаємо активну задачу самоконтролю таблиці настройок, бо не було її успішне зчитування
      periodical_tasks_TEST_USTUVANNJA = false;
    }
  }
//  else if (periodical_tasks_TEST_TRG_FUNC_LOCK != 0)
//  {
//    //Стоїть у черзі активна задача самоконтролю по резервній копії для триґерної інформації
//    //Виконуємо її
//    control_trg_func();
//      
//    //Скидаємо активну задачу самоконтролю по резервній копії для триґерної інформації
//    periodical_tasks_TEST_TRG_FUNC_LOCK = false;
//  }
  else if (periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK != 0)
  {
    //Стоїть у черзі активна задача самоконтролю по резервній копії для реєстратора програмних подій
    //Виконуємо її
    unsigned int result;
    result = control_info_rejestrator(&info_rejestrator_pr_err_ctrl, crc_info_rejestrator_pr_err_ctrl);
      
    if (result == 1)
    {
      //Контроль достовірності реєстратора пройшов успішно
    
      //Скидаємо повідомлення у слові діагностики
      _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT);
    }
    else
    {
      //Контроль достовірності реєстратора не пройшов

      //Виствляємо повідомлення у слові діагностики
      _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT);
    }

    //Скидаємо активну задачу самоконтролю по резервній копії для аналогового реєстратора
    periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = false;
  }
  /*******************/

  /*******************/
  //Копіювання даних миттєвого масиву для передавання у інші системи
  /*******************/
  if(command_to_receive_current_data == true)
  {
    unsigned int i, index;
    //Виставляємо очікування останнього виходу з вимірювальної системи для синохронізації подій
    wait_of_receiving_current_data  = true;
    while(wait_of_receiving_current_data  == true);
    index = index_array_of_current_data_value;
    for (i = 0; i < (NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT); i++)
    {
      current_data_transmit[i] = current_data[index++];
      if (index == (NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT)) index = 0;
    }
    //Сигналізуємо про завершення процесу копіювання
    action_is_continued = false;
    command_to_receive_current_data = false;
  }
  /*******************/
    
  //Підрахунок вільного ресуру процесор-програма
  if(resurs_temp < 0xfffffffe) resurs_temp++;

  watchdog_routine();
}
/*************************************************************************/

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
//  /************************************************************/
//  //Перевірка контрольної суми програми
//  /************************************************************/
//  {
//    unsigned short sum = 0;
//    unsigned char *point = ((unsigned char *)&__checksum_begin);
//    for (unsigned int i = ((unsigned int)&__checksum_end -(unsigned int)&__checksum_begin +1); i > 0; i--)
//      sum += *point++;
//    if (sum != (unsigned short)__checksum)
//    {
//      while(1);
//    }
//  }
//  /************************************************************/
  
  /************************************************************/
  //Стартова ініціалізація
  /************************************************************/
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_Conf();            /* Configure and initialize SystemView  */
#endif
  
  //Виставляємо подію про зупинку пристрою у попередньому сеансі роботи, а час встановиться пізніше, RTC запм'ятовує час пропадання живлення
  _SET_BIT(set_diagnostyka, EVENT_STOP_SYSTEM_BIT);
  changing_diagnostyka_state();//Підготовлюємо новий запис для реєстратора програмних подій
  
  //Перевіряємо, що відбулося: запуск приладу, чи перезапуск (перезапуск роботи приладу без зняття оперативного живлення) 
  if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != SET)
  {
    //Виставляємо подію про перезапуск пристрою (бо не зафіксовано подію Power-on/Power-down)
    _SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT);
  }
  else
  {
    //Виставляємо подію про запуск пристрою 
    _SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT);
  }
  //Очищаємо прапорці
  RCC->CSR |= RCC_CSR_RMVF;
  changing_diagnostyka_state();//Підготовлюємо новий запис для реєстратора програмних подій

  //Стартова настройка периферії процесора
  start_settings_peripherals();
  
  if(
     ((state_i2c_task & STATE_CONFIG_EEPROM_GOOD  ) != 0) &&
     ((state_i2c_task & STATE_SETTINGS_EEPROM_GOOD) != 0)/* &&
     ((state_i2c_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)*/
    )   
  {
    //Випадок, якщо настройки успішно зчитані
          
    //Дозволяєм роботу таймера вимірювальної системи
    TIM_Cmd(TIM5, ENABLE);
    // Дозволяєм роботу таймера системи захистів
    TIM_Cmd(TIM2, ENABLE);

    //Ініціалізація LCD
    lcd_init();
    changing_diagnostyka_state();//Підготовлюємо новий потенційно можливий запис для реєстратора програмних подій
  }
  else
  {
    //Випадок, якщо настройки успішно не зчитані, або їх взагалі немає
    
    //Ініціалізація LCD
    lcd_init();
    changing_diagnostyka_state();//Підготовлюємо новий потенційно можливий запис для реєстратора програмних подій
  
    //Якщо настройки не зчитані успішно з EEPROM, то спочатку виводимо на екран повідомлення про це
    while (
           ((state_i2c_task & STATE_CONFIG_EEPROM_GOOD  ) == 0) ||
           ((state_i2c_task & STATE_SETTINGS_EEPROM_GOOD) == 0)/* ||
           ((state_i2c_task & STATE_TRG_FUNC_EEPROM_GOOD) == 0)*/
          )   
    {
      error_reading_with_eeprom();
    }

    //Дозволяєм роботу таймера вимірювальної системи
    TIM_Cmd(TIM5, ENABLE);
    //Дозволяєм роботу таймера системи захистів
    TIM_Cmd(TIM2, ENABLE);
  }
  changing_diagnostyka_state();//Підготовлюємо новий потенційно можливий запис для реєстратора програмних подій

  //Визначаємо, чи стоїть дозвіл запису через інтерфейси з паролем
  if (settings_fix.password_interface_RS485 == 0) password_set_RS485 = 0;
  else password_set_RS485 = 1;
  timeout_idle_RS485 = settings_fix.timeout_deactivation_password_interface_RS485;
  
  if (settings_fix.password_interface_USB   == 0) password_set_USB   = 0;
  else password_set_USB   = 1;
  timeout_idle_USB = settings_fix.timeout_deactivation_password_interface_USB;
  
  //Перевірка параметрування мікросхем DataFlash
  start_checking_dataflash();
  
  //Запускаємо генерацію переривань кожну кожну 1 мс від каналу 2 таймеру 4 для виконання періодичних низькопріоритетних задач
  start_tim4_canal2_for_interrupt_1mc();
  
  //Підраховуємо величину затримки у бітах, яка допускається між байтами у RS-485 згідно з визначеними настройками
  calculate_namber_bit_waiting_for_rs_485();
  //Запускаємо генерацію переривань з плаваючим періодом (час очікування наступного символа) від каналу 3 таймеру 4 для RS-485
  start_tim4_canal3_for_interrupt_10mkc();
  //Настроюємо USART на роботу з RS-485
  USART_RS485_Configure();
  //Починаємо моніторинг каналу RS-485
  restart_monitoring_RS485();
  /************************************************************/

  //Виставляємо признак, що на екрані треба обновити стартову інформацію
  new_state_keyboard |= (1<<BIT_REWRITE);
  
  //Виставляємо признак, що требаа прочитати всі регістри RTC, а потім, при потребі відкоректувати його поля
  //При цьому виставляємо біт блокування негайного запуску операції, щоб засинхронізуватися з роботою вимірювальної системи
  _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
  _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
  
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
  restart_resurs_count = 0xff;/*Ненульове значення перезапускає лічильники*/
  
  time_2_watchdog_input = time_2_watchdog_output = TIM4->CNT;
  restart_timing_watchdog = 0xff;
   asm(
       "bkpt 1"
       );
  long res = InitSchematic();

  /* Періодичні задачі */
  while (1)
  {
    if (periodical_tasks_TEST_FLASH_MEMORY != 0)
    {
      /************************************************************/
      //Перевірка контрольної суми програми
      /************************************************************/
      unsigned short sum = 0;
      unsigned char *point = ((unsigned char *)&__checksum_begin);
      for (unsigned int i = ((unsigned int)&__checksum_end -(unsigned int)&__checksum_begin +1); i > 0; i--)
      {
        sum += *point++;
        periodical_operations();
      }
      if (sum != (unsigned short)__checksum) _SET_BIT(set_diagnostyka, ERROR_INTERNAL_FLASH_BIT);
      else _SET_BIT(clear_diagnostyka, ERROR_INTERNAL_FLASH_BIT);
      /************************************************************/

      periodical_tasks_TEST_FLASH_MEMORY = false;
    }
    else periodical_operations();
  }
}
/*******************************************************************************/

/*******************************************************************************/
//Глобальна помилка програмного забеспечення
/*******************************************************************************/
void total_error_sw_fixed(unsigned int number)
{
  total_error = number;
  while (1);
}
/*******************************************************************************/

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
