#ifndef __CONST_DRIVER_SERIAL_FLASH__
#define __CONST_DRIVER_SERIAL_FLASH__

#define NUMBER_DATAFLASH_CHIP      2

#define INDEX_DATAFLASH_1           0
#define INDEX_DATAFLASH_2           1

#define VAGA_SIZE_PAGE_DATAFLASH_1      8 //ця константа потрібна тільки для того, щоб можна було легко множити на 256 і ділити на 256
#define SIZE_PAGE_DATAFLASH_1           (1 << VAGA_SIZE_PAGE_DATAFLASH_1) //256 байт
#define NUMBER_PAGES_INTO_DATAFLASH_1   512

#define VAGA_SIZE_PAGE_DATAFLASH_2      9 //ця константа потрібна тільки для того, щоб можна було легко множити на 512 і ділити на 512
#define SIZE_PAGE_DATAFLASH_2           (1 << VAGA_SIZE_PAGE_DATAFLASH_2) //512 байт
#define NUMBER_PAGES_INTO_DATAFLASH_2   4096

#if SIZE_PAGE_DATAFLASH_2 >= SIZE_PAGE_DATAFLASH_1
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_2
#else
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_1
#endif

#define NUMBER_PAGES_INTO_DR            480
#define NUMBER_PAGES_INTO_PR_ERR        (NUMBER_PAGES_INTO_DATAFLASH_1 - NUMBER_PAGES_INTO_DR)

#define MIN_ADDRESS_DR_AREA                   0x0
#define SIZE_DR_AREA                          (NUMBER_PAGES_INTO_DR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_DR_AREA                   (MIN_ADDRESS_DR_AREA + SIZE_DR_AREA - 1)

#define VAGA_SIZE_ONE_RECORD_PR_ERR           5
#define SIZE_ONE_RECORD_PR_ERR                (1<<VAGA_SIZE_ONE_RECORD_PR_ERR)
#define NUMBER_RECORDS_PR_ERR_INTO_PAGE       (SIZE_PAGE_DATAFLASH_1>>VAGA_SIZE_ONE_RECORD_PR_ERR) //кількість записів програмних подій у одній строрінці мікросхеми послідовної DataFlash
#define MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER 32 //максимальнакількість записів в буфері типу FIFO, які чекають на запису DataFlash
#define SIZE_BUFFER_FOR_PR_ERR                (SIZE_ONE_RECORD_PR_ERR*MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER)
#define MAX_NUMBER_RECORDS_INTO_PR_ERR        (NUMBER_PAGES_INTO_PR_ERR*NUMBER_RECORDS_PR_ERR_INTO_PAGE)
#define MIN_ADDRESS_PR_ERR_AREA               (MAX_ADDRESS_DR_AREA + 1)
#define SIZE_PR_ERR_AREA                      (NUMBER_PAGES_INTO_PR_ERR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_PR_ERR_AREA               (MIN_ADDRESS_PR_ERR_AREA + SIZE_PR_ERR_AREA - 1)

#define TRANSACTION_EXECUTING_NONE              0
#define TRANSACTION_EXECUTING                   1
#define TRANSACTION_EXECUTED_WAIT_ANALIZE       2

#define CODE_OPERATION_NONE                                 0
#define CODE_OPERATION_STATUS_READ                          1
#define CODE_OPERATION_PAGESIZE_256                         2
#define CODE_OPERATION_ERASE                                3
#define CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER            4
#define CODE_OPERATION_READ_HIGH_FREQ                       5
#define CODE_OPERATION_READ_PAGE_INTO_BUFFER                6
#define CODE_OPERATION_WRITE_BUFFER                         7
#define CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE  8

/*Біти 0-15 відносять до мікросхеми DataFlash дискретного реєстратора і реєстратора програмних подій*/
#define TASK_ERASE_DATAFLASH_1_BIT                                          0
#define TASK_ERASE_DATAFLASH_1                                              (1<<TASK_ERASE_DATAFLASH_1_BIT)
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT                        1
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH                            (1<<TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT        2
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT                      3
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU                          (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT                       4
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB                           (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT                     5
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485                         (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT)

#define  SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2                16

/*Біти 16-31 відносять до мікросхеми DataFlash аналогового реєстратора*/
#define TASK_ERASE_DATAFLASH_2_BIT                                          (0 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_ERASE_DATAFLASH_2                                              (1<<TASK_ERASE_DATAFLASH_2_BIT)

#define READING_PR_ERR_FOR_MENU         1
#define READING_PR_ERR_FOR_USB          2
#define READING_PR_ERR_FOR_RS485        3

#define LABEL_START_RECORD_PR_ERR       0x5A

#define ETAP_NONE                                 0
#define ETAP_READ_MEMORY_INTO_BUFFER              1
#define ETAP_HAVE_READ_MEMORY_INTO_BUFFER         2
#define ETAP_MODIFY_AND_WRITE_BUFFER              3
#define ETAP_MODIFIED_AND_WRITTEN_BUFFER          4
#define ETAP_WRITE_BUFFER_INTO_MEMORY             5
#define ETAP_ERROR_BEFALLEN                       6

#define CLEAN_PR_ERR_BIT      0
#define CLEAN_PR_ERR          (1 << CLEAN_PR_ERR_BIT)

#endif
