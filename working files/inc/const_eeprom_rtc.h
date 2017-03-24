#ifndef __CONST_EEPROM_RTC__
#define __CONST_EEPROM_RTC__

#define I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY            ((uint32_t)0x00000040)  /* RxNE */

#define MAX_NUMBER_BUSY_STATE     10

#define ERROR_TOTAL_BIT           0
#define ERROR_UNEXPECTED_BIT      1
#define ERROR_FIX_ERRORS_BIT      2

#define CLOCKSPEED_1MBIT      1000000
#define CLOCKSPEED            400000
#define SIZE_PAGE_EEPROM      64
#define EEPROM_ADDRESS        0xA2
#define RTC_ADDRESS           0xD0

#define SIZE_USTUVANNJA         (sizeof(unsigned int) + sizeof(ustuvannja) + sizeof(serial_number_dev))
#define SIZE_CONFIG              sizeof(__CONFIG)
#define SIZE_SETTINGS            size_all_settings()

#define START_ADDRESS_USTUVANNJA_IN_EEPROM              0x0
#define START_ADDRESS_INFO_REJESTRATORS_PR_ERR          (((START_ADDRESS_USTUVANNJA_IN_EEPROM     + (SIZE_USTUVANNJA                 + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_CONFIG_IN_EEPROM                  (((START_ADDRESS_INFO_REJESTRATORS_PR_ERR + (sizeof(info_rejestrator_pr_err) + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_SETTINGS_IN_EEPROM                (((START_ADDRESS_CONFIG_IN_EEPROM         + (SIZE_CONFIG                     + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)
#define START_ADDRESS_TRG_FUNC                          (((START_ADDRESS_SETTINGS_IN_EEPROM       + (SIZE_SETTINGS                   + 1)) & (unsigned int)(~(SIZE_PAGE_EEPROM - 1))) + SIZE_PAGE_EEPROM)

#define START_ADDRESS_TIME_REGISTERS              0x0
#define MAX_NUMBER_REGISTERS_RTC                  20

#define SIZE_BUFFER_FOR_EEPROM_EXCHNGE 256

#define COMPARISON_WRITING_CONFIG_BIT                                   0
#define COMPARISON_WRITING_CONFIG                                       (1 << COMPARISON_WRITING_CONFIG_BIT)
#define COMPARISON_WRITING_SETTINGS_BIT                                 1
#define COMPARISON_WRITING_SETTINGS                                     (1 << COMPARISON_WRITING_SETTINGS_BIT)
#define COMPARISON_WRITING_USTUVANNJA_BIT                               2
#define COMPARISON_WRITING_USTUVANNJA                                   (1 << COMPARISON_WRITING_USTUVANNJA_BIT)
#define COMPARISON_WRITING_TRG_FUNC_BIT                                 3
#define COMPARISON_WRITING_TRG_FUNC                                     (1 << COMPARISON_WRITING_TRG_FUNC_BIT)
#define COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR_BIT                  4
#define COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR                      (1 << COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR_BIT)

enum
{
  TASK_BLK_OPERATION_BIT = 0,
  TASK_BLK_WRITING_EEPROM_BIT,

  TASK_START_WRITE_USTUVANNJA_EEPROM_BIT,
  TASK_WRITING_USTUVANNJA_EEPROM_BIT,

  TASK_START_READ_USTUVANNJA_EEPROM_BIT,
  TASK_READING_USTUVANNJA_EEPROM_BIT,

  TASK_START_WRITE_CONFIG_EEPROM_BIT,
  TASK_WRITING_CONFIG_EEPROM_BIT,

  TASK_START_READ_CONFIG_EEPROM_BIT,
  TASK_READING_CONFIG_EEPROM_BIT,

  TASK_START_WRITE_SETTINGS_EEPROM_BIT,
  TASK_WRITING_SETTINGS_EEPROM_BIT,

  TASK_START_READ_SETTINGS_EEPROM_BIT,
  TASK_READING_SETTINGS_EEPROM_BIT,

//  TASK_START_WRITE_TRG_FUNC_EEPROM_BIT,
//  TASK_WRITING_TRG_FUNC_EEPROM_BIT,

//  TASK_START_READ_TRG_FUNC_EEPROM_BIT,
//  TASK_READING_TRG_FUNC_EEPROM_BIT,

  TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,
  TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,

  TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,
  TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,

  TASK_START_READ_RTC_BIT,
  TASK_READING_RTC_BIT,

  TASK_START_WRITE_RTC_BIT,
  TASK_WRITING_RTC_BIT,

  TASK_SET_START_SETTINGS_RTC_BIT,
  TASK_RESET_ST_RTC_BIT,
  TASK_RESET_OF_RTC_BIT,
};


#define STATE_CONFIG_EEPROM_EMPTY_BIT                                   0      
#define STATE_CONFIG_EEPROM_EMPTY                                       (1<<STATE_CONFIG_EEPROM_EMPTY_BIT)      
#define STATE_CONFIG_EEPROM_FAIL_BIT                                    1      
#define STATE_CONFIG_EEPROM_FAIL                                        (1<<STATE_CONFIG_EEPROM_FAIL_BIT)      
#define STATE_CONFIG_EEPROM_NO_FREE_MEMORY_BIT                          2      
#define STATE_CONFIG_EEPROM_NO_FREE_MEMORY                              (1<<STATE_CONFIG_EEPROM_NO_FREE_MEMORY_BIT)      
#define STATE_CONFIG_EEPROM_GOOD_BIT                                    3      
#define STATE_CONFIG_EEPROM_GOOD                                        (1<<STATE_CONFIG_EEPROM_GOOD_BIT)      

#define STATE_SETTINGS_EEPROM_EMPTY_BIT                                 4      
#define STATE_SETTINGS_EEPROM_EMPTY                                     (1<<STATE_SETTINGS_EEPROM_EMPTY_BIT)      
#define STATE_SETTINGS_EEPROM_FAIL_BIT                                  5      
#define STATE_SETTINGS_EEPROM_FAIL                                      (1<<STATE_SETTINGS_EEPROM_FAIL_BIT)      
#define STATE_SETTINGS_EEPROM_GOOD_BIT                                  6      
#define STATE_SETTINGS_EEPROM_GOOD                                      (1<<STATE_SETTINGS_EEPROM_GOOD_BIT)      

#define STATE_USTUVANNJA_EEPROM_EMPTY_BIT                               7      
#define STATE_USTUVANNJA_EEPROM_EMPTY                                   (1<<STATE_USTUVANNJA_EEPROM_EMPTY_BIT)      
#define STATE_USTUVANNJA_EEPROM_FAIL_BIT                                8      
#define STATE_USTUVANNJA_EEPROM_FAIL                                    (1<<STATE_USTUVANNJA_EEPROM_FAIL_BIT)      
#define STATE_USTUVANNJA_EEPROM_GOOD_BIT                                9      
#define STATE_USTUVANNJA_EEPROM_GOOD                                    (1<<STATE_USTUVANNJA_EEPROM_GOOD_BIT)      

//#define STATE_TRG_FUNC_EEPROM_EMPTY_BIT                                 10      
//#define STATE_TRG_FUNC_EEPROM_EMPTY                                     (1<<STATE_TRG_FUNC_EEPROM_EMPTY_BIT)      
//#define STATE_TRG_FUNC_EEPROM_FAIL_BIT                                  11      
//#define STATE_TRG_FUNC_EEPROM_FAIL                                      (1<<STATE_TRG_FUNC_EEPROM_FAIL_BIT)      
//#define STATE_TRG_FUNC_EEPROM_GOOD_BIT                                  12      
//#define STATE_TRG_FUNC_EEPROM_GOOD                                      (1<<STATE_TRG_FUNC_EEPROM_GOOD_BIT)      

#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT                  13      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY                      (1<<STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT)      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL_BIT                   14      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL                       (1<<STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL_BIT)      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD_BIT                   15      
#define STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD                       (1<<STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD_BIT)      

#define STATE_FIRST_READING_RTC_BIT                                     30      
#define STATE_FIRST_READING_RTC                                         (1<<STATE_FIRST_READING_RTC_BIT)    

#define ETAP_CLEAR_OF_NONE                                      -1                                            //-1
#define ETAP_CLEAR_OF_ST_STOP                                   0                                             //0
#define ETAP_CLEAR_OF_ST_CLEAR                                  (ETAP_CLEAR_OF_ST_STOP + 1)                   //1
#define ETAP_CLEAR_OF_ST_START_WAITING_5S                       (ETAP_CLEAR_OF_ST_CLEAR + 1)                  //2
#define ETAP_CLEAR_OF_ST_WAITING_5S                             (ETAP_CLEAR_OF_ST_START_WAITING_5S + 1)       //3
#define ETAP_CLEAR_OF_WRITE_OF_0                                (ETAP_CLEAR_OF_ST_WAITING_5S + 1)             //4

#endif
