#ifndef __CONST_INTERFACES__
#define __CONST_INTERFACES__

#define USB_RECUEST           0
#define RS485_RECUEST         1

enum __data_changed_bit
{
SETTINGS_DATA_CHANGED_BIT = 0,
RANGUVANNJA_DATA_CHANGED_BIT,
USER_REGISTRY_CHANGED_BIT,
NEW_PASSWORD_SET_BIT,
DEFAULT_SETTINGS_SET_BIT
};

#define BROADCAST_ADDRESS_MODBUS_RTU    0

#define BUFFER_RS485          256
#define BUFFER_USB            256

#define MAX_TIMEOUT_PACKET    5000 // 50 мс, якщо врахувати, що ТІM4 тактує з періодом 10 мкс

#define ERROR_ILLEGAL_FUNCTION                        1
#define ERROR_ILLEGAL_DATA_ADDRESS                    2 
#define ERROR_ILLEGAL_DATA_VALUE                      3 
#define ERROR_SLAVE_DEVICE_FAILURE                    4
#define ERROR_ACKNOWLEDGE                             5
#define ERROR_SLAVE_DEVICE_BUSY                       6
#define ERROR_MEMORY_PARITY_ERROR                     8
#define ERROR_GATEWAY_PATH_UNAVAILABLE                0xA
#define ERROR_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND 0xB
#define ERROR_BROADCAST_ADDRESS                       0xFF


#endif
