#ifndef EXTERNAL_REG_DEF_h
#define EXTERNAL_REG_DEF_h


enum EXTERNAL_REG_OUTPUT_NAMES{
ADR_READ_DIN01__05 = 0x400000,
ADR_READ_DIN06__12 = 0x600000,
ADR_WRITE_RI_COLUMNS01__06 = 0x800000,

ADR_WRITE_RDO__REL_1_6__ROWS_A__D = 0xC00000,
ADR_READ_CHECK_RDO__REL_1_6       = 0xC00000,
ADR_WRITE_RDO_REL7_REL14          = 0xE00000,
ADR_READ_CHECK_RDO_REL7_REL14     = 0xE00000

};

////////////////////////////////////////////////////////////// 
enum EXTERNAL_BANK_OUTPUT_NAMES{
NOR_PSRAM_BANK1 = 0x60000000,
NOR_PSRAM_BANK2 = 0x64000000,
NOR_PSRAM_BANK3 = 0x68000000,
NOR_PSRAM_BANK4 = 0x6C000000
};

// /*
// Регістр дискретних входів DIN1–DIN5
// MC74LCX245DTG
// 8
// -
// 0xXX400000
// Читання
// */
extern char chGbl__DIN6_DIN12__RD_VAL;
// /*
// Регістр дискретних входів DIN6–DIN12
// MC74LCX245DTG
// 8
// -
// 0xXX600000
// Читання
// 
// */
extern char chGbl__LedColumns__RW_VAL;
// /*
// Регістр індикаторів РІ / стовпчиків матриці 1-8 індикаторів
// MC74LCX574DTG
// 8
// -
// 0xXX800000
// Запис
// */

extern char chGbl_REL_1_6__ROWS_A_D__RW_VAL;
// /*
// Регістр дискретних виходів REL1-REL6 / рядків матриці A-D
// MC74LCX574DTG
// 8
// -
// 0xXXC00000
// Запис
// */
extern char chGbl__REL_1_6__RD_VAL;
// /*
// Регістр контролю ДВ REL1-REL6 та DIN17
// MC74LCX245DTG
// 8
// -
// 0xXXC00000
// Читання
// */
extern char chGbl__REL7_REL14__RW_VAL;
// /*Регістр дискретних виходів REL7-REL14
// MC74LCX574DTG
// 8
// -
// 0xXXE00000
// Запис */
extern char chGbl__REL7_REL14__RD_VAL;
// /* Регістр контролю ДВ REL7-REL14
// MC74LCX245DTG
// 8
// -
// 0xXXE00000
// Читання*/



#endif

