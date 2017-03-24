#ifndef __CONST_DIAGNOSTYKA_MENU2__
#define __CONST_DIAGNOSTYKA_MENU2__

#define MAX_ROW_FOR_DIAGNOSTYKA              (8*(4 + 4 + 3))  /*2 слова типу unsigned int + ще одне слово але з трьох байт. щоб розмір одного запису реєстратора програмних подій не був більшим 32 байти. А коли треба - то змінимо*/  

#define USED_BITS_IN_LAST_INDEX  0x00ffffff  

enum _error_id {
ERROR_START_VIA_I2C_BIT = 0,
ERROR_USTUVANNJA_EEPROM_BIT,
ERROR_USTUVANNJA_EEPROM_EMPTY_BIT,
ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT,
ERROR_USTUVANNJA_EEPROM_CONTROL_BIT,
ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT,
ERROR_CONFIG_EEPROM_DEVICE_ID_FAIL_BIT,
ERROR_CONFIG_EEPROM_BIT,
ERROR_CONFIG_EEPROM_EMPTY_BIT,
ERROR_CONFIG_EEPROM_COMPARISON_BIT,
ERROR_CONFIG_EEPROM_CONTROL_BIT,
ERROR_NO_FREE_DYNAMIC_MEMORY_BIT,
ERROR_SETTINGS_EEPROM_BIT,
ERROR_SETTINGS_EEPROM_EMPTY_BIT,
ERROR_SETTINGS_EEPROM_COMPARISON_BIT,
ERROR_SETTINGS_EEPROM_CONTROL_BIT,
ERROR_TRG_FUNC_EEPROM_BIT,
ERROR_TRG_FUNC_EEPROM_EMPTY_BIT,
ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT,
ERROR_TRG_FUNC_EEPROM_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_DR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_DR_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT,

RTC_BATTERY_LOW_BIT,
RTC_OSCILLATOR_STOPED_BIT,
RTC_OSCILLATOR_FAIL_BIT,
RTC_UPDATING_HALTED_BIT,
RTC_WORK_FIELD_NOT_SET_BIT,

ERROR_GND_ADC_TEST_BIT,
ERROR_VREF_ADC_TEST_BIT,
ERROR_VDD_ADC_TEST_BIT,
ERROR_GND_ADC_TEST_COARSE_BIT,
ERROR_VREF_ADC_TEST_COARSE_BIT,
ERROR_VDD_ADC_TEST_COARSE_BIT,

ERROR_DIGITAL_OUTPUTS_BIT,

ERROR_PR_ERR_OVERLOAD_BIT,
ERROR_PR_ERR_LOSS_INFORMATION_BIT,

EVENT_START_SYSTEM_BIT,
EVENT_RESTART_SYSTEM_BIT,
EVENT_STOP_SYSTEM_BIT,
EVENT_DROP_POWER_BIT,

ERROR_LCD_BIT,
ERROR_SPI_DF_BIT,
ERROR_EXTERNAL_SRAM_BIT,
ERROR_INTERNAL_FLASH_BIT,


};

#define MASKA_AVAR_ERROR_0        (unsigned int)(               \
    (1 << (ERROR_CONFIG_EEPROM_BIT))                            \
  | (1 << (ERROR_CONFIG_EEPROM_EMPTY_BIT))                      \
  | (1 << (ERROR_CONFIG_EEPROM_COMPARISON_BIT) )                \
  | (1 << (ERROR_CONFIG_EEPROM_CONTROL_BIT))                    \
  | (1 << (ERROR_SETTINGS_EEPROM_BIT))                          \
  | (1 << (ERROR_SETTINGS_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_SETTINGS_EEPROM_COMPARISON_BIT) )              \
  | (1 << (ERROR_SETTINGS_EEPROM_CONTROL_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_BIT) )                       \
  | (1 << (ERROR_USTUVANNJA_EEPROM_EMPTY_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT))             \
  | (1 << (ERROR_USTUVANNJA_EEPROM_CONTROL_BIT))                \
  | (1 << (ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT))     \
  | (1 << (ERROR_TRG_FUNC_EEPROM_BIT))                          \
  | (1 << (ERROR_TRG_FUNC_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT))               \
  | (1 << (ERROR_TRG_FUNC_EEPROM_CONTROL_BIT))                  \
)

#define MASKA_AVAR_ERROR_1        (unsigned int)(               \
    (1 << (ERROR_GND_ADC_TEST_BIT - 32))                        \
  | (1 << (ERROR_VREF_ADC_TEST_BIT - 32))                       \
  | (1 << (ERROR_VDD_ADC_TEST_BIT - 32))                        \
  | (1 << (ERROR_GND_ADC_TEST_COARSE_BIT - 32))                 \
  | (1 << (ERROR_VREF_ADC_TEST_COARSE_BIT - 32))                \
  | (1 << (ERROR_VDD_ADC_TEST_COARSE_BIT - 32))                 \
  | (1 << (ERROR_DIGITAL_OUTPUTS_BIT + 0 - 32))                 \
  | (1 << (ERROR_INTERNAL_FLASH_BIT - 32))                      \
)

#define MASKA_AVAR_ERROR_2              0


# define NAME_DIAGN_RU  \
  " Ош.I2C         ",   \
  " Ош.юстирования ",   \
  " Юстирования нет",   \
  " Ош.зап.юстир.  ",   \
  " Ош.контр.юстир.",   \
  " Ош.юстир.набора",   \
  " Ош.типа конф.  ",   \
  " Ош.конфигурации",   \
  "Конфигурации нет",   \
  "  Ош.зап.конф.  ",   \
  " Ош.конф.настр. ",   \
  " Недост.динам.п.",   \
  " Ош.настроек    ",   \
  " Настроек нет   ",   \
  " Ош.зап.настр.  ",   \
  " Ош.контр.настр.",   \
  " Ош.воcст.тр.св ",   \
  " Ош.воcст.с.вых ",   \
  "Инф.вых./св.нет ",   \
  " Ош.зап.вых./св.",   \
  " Ош.триг.инф.   ",   \
  " Триг.инф.нет   ",   \
  "Ош.зап.триг.инф.",   \
  "Ош.контр.триг.и.",   \
  " Ош.инф.д.рег.  ",   \
  " Инф.д.рег.нет  ",   \
  " Ош.зап.и.д.рег.",   \
  " Ош.контр.д.рег.",   \
  "Ош.инф.рег.пр.с.",   \
  "Инф.рег.пр.с.нет",   \
  "Ош.зап.и.р.пр.с.",   \
  "Ош.контр.р.пр.с.",   \
  " Ош.инф.сч.рес. ",   \
  " Инф.сч.рес.нет ",   \
  " Ош.зап.сч.рес. ",   \
  "Ош.контр.сч.рес.",   \
  " Ош.к.с.энергий ",   \
  " Энергий нет    ",   \
  " Ош.зап.энергий ",   \
  " Батарея разряж.",   \
  "Осцилятор остан.",   \
  "Отказ Осцилятора",   \
  " Ост.обновл.RTC ",   \
  " Не уст.поля RTC",   \
  " Тест GND АЦП   ",   \
  " Тест VREF АЦП  ",   \
  " Тест VDD АЦП   ",   \
  "Тест GND АЦП гр.",   \
  "Тест VREF АЦП гр",   \
  "Тест VDD АЦП гр.",   \
  " Ош.вых.реле    ",   \
  "Переп.буф.пр.ош.",   \
  " Потеря д.пр.ош.",   \
  " Старт устр.    ",   \
  " Рестарт устр.  ",   \
  " Останов.устр.  ",   \
  " Пропад.питания ",   \
  " Отказ ЖКИ      ",   \
  " Ош.SPI_DF      ",   \
  " Ош.внешней SRAM",   \
  " Ош.внутр.FLASH ",   \
  " Ошибка 62      ",   \
  " Ошибка 63      ",   \
  " Ошибка 64      ",   \
  " Ошибка 65      ",   \
  " Ошибка 66      ",   \
  " Ошибка 67      ",   \
  " Ошибка 68      ",   \
  " Ошибка 69      ",   \
  " Ошибка 70      ",   \
  " Ошибка 71      ",   \
  " Ошибка 72      ",   \
  " Ошибка 73      ",   \
  " Ошибка 74      ",   \
  " Ошибка 75      ",   \
  " Ошибка 76      ",   \
  " Ошибка 77      ",   \
  " Ошибка 78      ",   \
  " Ошибка 79      ",   \
  " Ошибка 80      ",   \
  " Ошибка 81      ",   \
  " Ошибка 82      ",   \
  " Ошибка 83      ",   \
  " Ошибка 84      ",   \
  " Ошибка 85      ",   \
  " Ошибка 86      ",   \
  " Ошибка 87      ",   \
  " Ошибка 88      "

# define NAME_DIAGN_UA  \
  " Пом.I2C        ",   \
  " Пом.юстування  ",   \
  " Юстування нема ",   \
  " Пом.зап.юст.   ",   \
  " Пом.контр.юст. ",   \
  " Пом.юст.набору ",   \
  " Пом.типу конф. ",   \
  "Пом.конфігурації",   \
  " Конф.нема      ",   \
  " Пом.зап.конф.  ",   \
  " Пом.контр.конф.",   \
  " Недост.динам.п.",   \
  " Пом.налаштувань",   \
  "Налаштувань нема",   \
  " Пом.зап.налашт.",   \
  "Пом.контр.налашт",   \
  " Пом.відн.тр.св.",   \
  " Пом.відн.с.вих.",   \
  "Інф.вих./св.нема",   \
  "Пом.зап.вих./св.",   \
  " Пом.триґ.інф.  ",   \
  " Триґ.інф.нема  ",   \
  " Пом.зап.триґ.і.",   \
  "Пом.контр.триґ.і",   \
  " Пом.інф.д.р.   ",   \
  " Інф.д.р.нема   ",   \
  " Пом.зап.і.д.р. ",   \
  " Пом.контр.д.р. ",   \
  " Пом.інф.р.пр.п.",   \
  " Інф.р.пр.п.нема",   \
  "Пом.зап.і.р.пр.п",   \
  "Пом.контр.р.пр.п",   \
  " Пом.інф.ліч.р. ",   \
  " Інф.ліч.р.нема ",   \
  " Пом.зап.ліч.р. ",   \
  "Пом.контр.ліч.р.",   \
  " Пом.к.с.енергій",   \
  " Енергій нема   ",   \
  " Пом.зап.енергій",   \
  "Батарея разрядж.",   \
  " Осцилятор зуп. ",   \
  " Відм.Осцилятора",   \
  " Зуп.обновл.RTC ",   \
  " Не вст.поля RTC",   \
  " Тест GND АЦП   ",   \
  " Тест VREF АЦП  ",   \
  " Тест VDD АЦП   ",   \
  "Тест GND АЦП гр.",   \
  "Тест VREF АЦП гр",   \
  "Тест VDD АЦП гр.",   \
  " Пом.вих.реле   ",   \
  "Переп.буф.р.пр.п",   \
  " Втрата д.р.пр.п",   \
  " Старт пристр.  ",   \
  " Рестарт пристр.",   \
  " Зуп.пристр.    ",   \
  " Пропад.живлення",   \
  " Відмова РКІ    ",   \
  " Пом.SPI_DF     ",   \
  " Пом.зовн.SRAM  ",   \
  " Пом.внутр.FLASH",   \
  " Помилка 62     ",   \
  " Помилка 63     ",   \
  " Помилка 64     ",   \
  " Помилка 65     ",   \
  " Помилка 66     ",   \
  " Помилка 67     ",   \
  " Помилка 68     ",   \
  " Помилка 69     ",   \
  " Помилка 70     ",   \
  " Помилка 71     ",   \
  " Помилка 72     ",   \
  " Помилка 73     ",   \
  " Помилка 74     ",   \
  " Помилка 75     ",   \
  " Помилка 76     ",   \
  " Помилка 77     ",   \
  " Помилка 78     ",   \
  " Помилка 79     ",   \
  " Помилка 80     ",   \
  " Помилка 81     ",   \
  " Помилка 82     ",   \
  " Помилка 83     ",   \
  " Помилка 84     ",   \
  " Помилка 85     ",   \
  " Помилка 86     ",   \
  " Помилка 87     ",   \
  " Помилка 88     "

# define NAME_DIAGN_EN  \
  " I2C Err.       ",   \
  " Adjust Err.    ",   \
  " No adjust      ",   \
  " Adjust W.Err.  ",   \
  "Adjust Ctrl.Err.",   \
  " Adjust-Set Err.",   \
  " Conf.Type Err. ",   \
  " Conf.Err.      ",   \
  " No Conf.       ",   \
  " Conf.W.Err.    ",   \
  " Conf.Ctrl.Err. ",   \
  "No enough dyn.m.",   \
  " Settings Err.  ",   \
  " No settings    ",   \
  " Sett.W.Err.    ",   \
  " Sett.Ctrl.Err. ",   \
  "Tr.LED Rest Err.",   \
  "Sign DO Rest Err",   \
  " No DO/LED Inf. ",   \
  " DO/LED W Err.  ",   \
  " Ош.триг.инф.   ",   \
  " Триг.инф.нет   ",   \
  "Ош.зап.триг.инф.",   \
  "Ош.контр.триг.и.",   \
  " D.Rec.Inf.Err. ",   \
  " No D.Rec.Inf.  ",   \
  "Inf.D.Rec.W.Err.",   \
  " D.Rec.Ctrl.Err.",   \
  " PER Inf.Err.   ",   \
  " No Inf.of PER  ",   \
  "Inf.W.Err.of PER",   \
  " PER Ctrl.Err.  ",   \
  " Res.C.Inf.Err. ",   \
  " No Res.C.Inf.  ",   \
  "Inf.Res.C.W.Err.",   \
  " Res.C.Ctrl.Err.",   \
  " Ош.к.с.энергий ",   \
  " Энергий нет    ",   \
  " Ош.зап.энергий ",   \
  " RTC:Battery low",   \
  " RTC:Osc.stop   ",   \
  " RTC:Osc.fail   ",   \
  " RTC:Halt update",   \
  "RTC:No def.sett.",   \
  " ADC:GND fail   ",   \
  " ADC:VREF fail  ",   \
  " ADC:VDD fail   ",   \
  " ADC:GND Test R.",   \
  " ADC:VREF Test R",   \
  " ADC:VDD Test R.",   \
  " DO Ctrl.Err.   ",   \
  "OVF of PER buff.",   \
  " PER Data lost  ",   \
  " Device Start   ",   \
  " Device Restart ",   \
  " Device Stop    ",   \
  " Пропад.питания ",   \
  " LCD Fail       ",   \
  " DF SPI Err.    ",   \
  " Ext.SRAM Err.  ",   \
  " Int.FLASH Err. ",   \
  " Error 62       ",   \
  " Error 63       ",   \
  " Error 64       ",   \
  " Error 65       ",   \
  " Error 66       ",   \
  " Error 67       ",   \
  " Error 68       ",   \
  " Error 69       ",   \
  " Error 70       ",   \
  " Error 71       ",   \
  " Error 72       ",   \
  " Error 73       ",   \
  " Error 74       ",   \
  " Error 75       ",   \
  " Error 76       ",   \
  " Error 77       ",   \
  " Error 78       ",   \
  " Error 79       ",   \
  " Error 80       ",   \
  " Error 81       ",   \
  " Error 82       ",   \
  " Error 83       ",   \
  " Error 84       ",   \
  " Error 85       ",   \
  " Error 86       ",   \
  " Error 87       ",   \
  " Error 88       "

# define NAME_DIAGN_KZ  \
  " Ош.I2C         ",   \
  " Ош.юстирования ",   \
  " Юстирования нет",   \
  " Ош.зап.юстир.  ",   \
  " Ош.контр.юстир.",   \
  " Ош.юстир.набора",   \
  " Ош.типа конф.  ",   \
  " Ош.конфигурации",   \
  "Конфигурации нет",   \
  " Ош.зап.конф.   ",   \
  " Ош.конф.настр. ",   \
  " Недост.динам.п.",   \
  " Ош.настроек    ",   \
  " Настроек нет   ",   \
  " Ош.зап.настр.  ",   \
  " Ош.контр.настр.",   \
  " Ош.воcст.тр.св ",   \
  " Ош.воcст.с.вых ",   \
  "Инф.вых./св.нет ",   \
  " Ош.зап.вых./св.",   \
  " Ош.триг.инф.   ",   \
  " Триг.инф.нет   ",   \
  "Ош.зап.триг.инф.",   \
  "Ош.контр.триг.и.",   \
  " Ош.инф.д.рег.  ",   \
  " Инф.д.рег.нет  ",   \
  " Ош.зап.и.д.рег.",   \
  " Ош.контр.д.рег.",   \
  "Ош.инф.рег.пр.с.",   \
  "Инф.рег.пр.с.нет",   \
  "Ош.зап.и.р.пр.с.",   \
  "Ош.контр.р.пр.с.",   \
  " Ош.инф.сч.рес. ",   \
  " Инф.сч.рес.нет ",   \
  " Ош.зап.сч.рес. ",   \
  "Ош.контр.сч.рес.",   \
  " Ош.к.с.энергий ",   \
  " Энергий нет    ",   \
  " Ош.зап.энергий ",   \
  " Батарея разряж.",   \
  "Осцилятор остан.",   \
  "Отказ Осцилятора",   \
  " Ост.обновл.RTC ",   \
  " Не уст.поля RTC",   \
  " Тест GND АЦП   ",   \
  " Тест VREF АЦП  ",   \
  " Тест VDD АЦП   ",   \
  "Тест GND АЦП гр.",   \
  "Тест VREF АЦП гр",   \
  "Тест VDD АЦП гр.",   \
  " Ош.вых.реле    ",   \
  "Переп.буф.пр.ош.",   \
  " Потеря д.пр.ош.",   \
  " Старт устр.    ",   \
  " Рестарт устр.  ",   \
  " Останов.устр.  ",   \
  " Пропад.питания ",   \
  " Отказ ЖКИ      ",   \
  " Ош.SPI_DF      ",   \
  " Ош.внешней SRAM",   \
  " Ош.внутр.FLASH ",   \
  " Ошибка 62      ",   \
  " Ошибка 63      ",   \
  " Ошибка 64      ",   \
  " Ошибка 65      ",   \
  " Ошибка 66      ",   \
  " Ошибка 67      ",   \
  " Ошибка 68      ",   \
  " Ошибка 69      ",   \
  " Ошибка 70      ",   \
  " Ошибка 71      ",   \
  " Ошибка 72      ",   \
  " Ошибка 73      ",   \
  " Ошибка 74      ",   \
  " Ошибка 75      ",   \
  " Ошибка 76      ",   \
  " Ошибка 77      ",   \
  " Ошибка 78      ",   \
  " Ошибка 79      ",   \
  " Ошибка 80      ",   \
  " Ошибка 81      ",   \
  " Ошибка 82      ",   \
  " Ошибка 83      ",   \
  " Ошибка 84      ",   \
  " Ошибка 85      ",   \
  " Ошибка 86      ",   \
  " Ошибка 87      ",   \
  " Ошибка 88      "


#endif
