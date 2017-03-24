#ifndef __CONST_MODBUS_MEMORY_MAP__
#define __CONST_MODBUS_MEMORY_MAP__

#define SET_DATA_INTO_EDIT_TABLE          0
#define SET_DATA_IMMEDITATE               1

/*****************************************************/
/* Адресний простір тільки для читання (Блок 1) */
/*****************************************************/
#define M_ADDRESS_FIRST_RO_BLOCK_1        0

#define MA_SERIAL_NUMBER                  0
#define MA_NAME_CHAR_1_2                  1
#define MA_NAME_CHAR_3_4                  2
#define MA_NAME_CHAR_5_6                  3
#define MA_NAME_CHAR_7_8                  4
#define MA_NAME_CHAR_9_10                 5
#define MA_NAME_CHAR_11_12                6
#define MA_NAME_CHAR_13_14                7
#define MA_NAME_CHAR_15_16                8
#define MA_NAME_CHAR_17_18                9
#define MA_VERSION_SW                     10
#define MA_DATA_COMP_1                    11
#define MA_DATA_COMP_2                    12
#define MA_TIME_COMP                      13
#define MA_VERSION_GMM                    14
#define MA_ZBIRKA_SW                      15

#define M_ADDRESS_LAST_RO_BLOCK_1         15
/*****************************************************/

/*****************************************************/
/* Регістри користувача */
/*****************************************************/
#define M_ADDRESS_FIRST_USER_REGISTER_DATA      16
#define M_ADDRESS_LAST_USER_REGISTER_DATA       99
/*****************************************************/

/*****************************************************/
/* Адресний простір виходів  */
/*****************************************************/
#define MA_OUTPUTS                        100
#define BIT_MA_OUTPUTS_BASE                   100
#define BIT_MA_OUTPUTS_FIRST                  100
#define BIT_MA_OUTPUTS_LAST                   (BIT_MA_OUTPUTS_FIRST + NUMBER_OUTPUTS - 1)
/*****************************************************/

/*****************************************************/
/* Адресний простір входів  */
/*****************************************************/
#define MA_INPUTS                         200
#define BIT_MA_INPUTS_BASE                    200
#define BIT_MA_INPUTS_FIRST                   200
#define BIT_MA_INPUTS_LAST                    (BIT_MA_INPUTS_FIRST + NUMBER_INPUTS - 1)
/*****************************************************/

/*****************************************************/
/* Адресний простір світлоіндикаторів  */
/*****************************************************/
#define MA_LEDS                           232
#define BIT_MA_LEDS_BASE                      232
#define BIT_MA_LEDS_FIRST                     232
#define BIT_MA_LEDS_LAST                      (BIT_MA_LEDS_FIRST + NUMBER_LEDS - 1)
/*****************************************************/

/*****************************************************/
/* Текучі активні функції */
/*****************************************************/
#define M_ADDRESS_FIRST_CURRENT_AF            256
#define BIT_MA_CURRENT_AF_BASE                  50000

//#define BIT_MA_1_GRUPA_USTAVOK                  50000
//#define BIT_MA_2_GRUPA_USTAVOK                  50001
//#define BIT_MA_3_GRUPA_USTAVOK                  50002
//#define BIT_MA_4_GRUPA_USTAVOK                  50003

//#define BIT_MA_BLOCK_MTZ1                       50016
//#define BIT_MA_MTZ1                             50017
//#define BIT_MA_PO_MTZ1                          50018
//#define BIT_MA_PO_MTZPN1                        50019
//#define BIT_MA_PO_MTZN1_VPERED                  50020
//#define BIT_MA_PO_MTZN1_NAZAD                   50021
//#define BIT_MA_SECTOR_VPERED_MTZN1              50022
//#define BIT_MA_SECTOR_NAZAD_MTZN1               50023
//#define BIT_MA_PO_U_MTZPN1                      50024

//#define BIT_MA_BLOCK_MTZ2                       50032
//#define BIT_MA_MTZ2                             50033
//#define BIT_MA_PO_MTZ2                          50034
//#define BIT_MA_PO_MTZPN2                        50035
//#define BIT_MA_PO_MTZN2_VPERED                  50036
//#define BIT_MA_PO_MTZN2_NAZAD                   50037
//#define BIT_MA_SECTOR_VPERED_MTZN2              50038
//#define BIT_MA_SECTOR_NAZAD_MTZN2               50039
//#define BIT_MA_PO_U_MTZPN2                      50040
//#define BIT_MA_BLOCK_USK_MTZ2                   50041

//#define BIT_MA_BLOCK_MTZ3                       50048
//#define BIT_MA_MTZ3                             50049
//#define BIT_MA_PO_MTZ3                          50050
//#define BIT_MA_PO_MTZPN3                        50051
//#define BIT_MA_PO_MTZN3_VPERED                  50052
//#define BIT_MA_PO_MTZN3_NAZAD                   50053
//#define BIT_MA_SECTOR_VPERED_MTZN3              50054
//#define BIT_MA_SECTOR_NAZAD_MTZN3               50055
//#define BIT_MA_PO_U_MTZPN3                      50056
//#define BIT_MA_BLOCK_USK_MTZ3                   50057

//#define BIT_MA_BLOCK_MTZ4                       50064
//#define BIT_MA_MTZ4                             50065
//#define BIT_MA_PO_MTZ4                          50066
//#define BIT_MA_PO_MTZPN4                        50067
//#define BIT_MA_PO_MTZN4_VPERED                  50068
//#define BIT_MA_PO_MTZN4_NAZAD                   50069
//#define BIT_MA_SECTOR_VPERED_MTZN4              50070
//#define BIT_MA_SECTOR_NAZAD_MTZN4               50071
//#define BIT_MA_PO_U_MTZPN4                      50072

//#define BIT_MA_BLOCK_MTZ04_1                    50080
//#define BIT_MA_MTZ04_1                          50081
//#define BIT_MA_PO_MTZ04_1                       50082
//#define BIT_MA_BLOCK_MTZ04_2                    50083
//#define BIT_MA_MTZ04_2                          50084
//#define BIT_MA_PO_MTZ04_2                       50085
//#define BIT_MA_BLOCK_USK_MTZ04_2                50086

//#define BIT_MA_NCN_MTZ                          50088
//#define BIT_MA_PO_BLOCK_U_MTZN                  50089

//#define BIT_MA_PUSK_ZDZ_VID_DV                  50096
//#define BIT_MA_ZDZ                              50097

//#define BIT_MA_BLOCK_NZZ                        50112
//#define BIT_MA_PO_NZZ                           50113
//#define BIT_MA_NZZ                              50114
//#define BIT_MA_PO_ZZ1_3I0                       50115
//#define BIT_MA_ZZ1_3I0                          50116

//#define BIT_MA_PO_ZZ_3U0                        50119
//#define BIT_MA_ZZ_3U0                           50120
//#define BIT_MA_SECTOR_NZZ                       50121

//#define BIT_MA_BLOCK_TZNP1                      50128
//#define BIT_MA_PO_3I0_TZNP1_VPERED              50129
//#define BIT_MA_PO_3I0_TZNP1_NAZAD               50130
//#define BIT_MA_PO_3U0_TZNP1_VPERED              50131
//#define BIT_MA_PO_3U0_TZNP1_NAZAD               50132
//#define BIT_MA_PO_TZNP1_VPERED                  50133
//#define BIT_MA_PO_TZNP1_NAZAD                   50134
//#define BIT_MA_SECTOR_TZNP1_VPERED              50135
//#define BIT_MA_SECTOR_TZNP1_NAZAD               50136
//#define BIT_MA_TZNP1                            50137
//#define BIT_MA_BLOCK_TZNP2                      50138
//#define BIT_MA_PO_3I0_TZNP2_VPERED              50139
//#define BIT_MA_PO_3I0_TZNP2_NAZAD               50140
//#define BIT_MA_PO_3U0_TZNP2_VPERED              50141
//#define BIT_MA_PO_3U0_TZNP2_NAZAD               50142
//#define BIT_MA_PO_TZNP2_VPERED                  50143
//#define BIT_MA_PO_TZNP2_NAZAD                   50144
//#define BIT_MA_SECTOR_TZNP2_VPERED              50145
//#define BIT_MA_SECTOR_TZNP2_NAZAD               50146
//#define BIT_MA_TZNP2                            50147
//#define BIT_MA_BLOCK_TZNP3                      50148
//#define BIT_MA_PO_3I0_TZNP3_VPERED              50149
//#define BIT_MA_PO_3I0_TZNP3_NAZAD               50150
//#define BIT_MA_PO_3U0_TZNP3_VPERED              50151
//#define BIT_MA_PO_3U0_TZNP3_NAZAD               50152
//#define BIT_MA_PO_TZNP3_VPERED                  50153
//#define BIT_MA_PO_TZNP3_NAZAD                   50154
//#define BIT_MA_SECTOR_TZNP3_VPERED              50155
//#define BIT_MA_SECTOR_TZNP3_NAZAD               50156
//#define BIT_MA_TZNP3                            50157

//#define BIT_MA_BLOCK_ZOP                        50160
//#define BIT_MA_ZOP                              50161
//#define BIT_MA_PO_ZOP                           50162

//#define BIT_MA_BLOCK_UMIN1                      50176
//#define BIT_MA_PO_UBLK_UMIN1                    50177
//#define BIT_MA_PO_IBLK_UMIN1                    50178
//#define BIT_MA_UMIN1                            50179
//#define BIT_MA_PO_UMIN1                         50180
//#define BIT_MA_BLOCK_UMIN2                      50181
//#define BIT_MA_PO_UBLK_UMIN2                    50182
//#define BIT_MA_PO_IBLK_UMIN2                    50183
//#define BIT_MA_UMIN2                            50184
//#define BIT_MA_PO_UMIN2                         50185
//#define BIT_MA_START_UMIN1                      50186
//#define BIT_MA_START_UMIN2                      50187

//#define BIT_MA_BLOCK_UMAX1                      50192
//#define BIT_MA_UMAX1                            50193
//#define BIT_MA_PO_UMAX1                         50194
//#define BIT_MA_BLOCK_UMAX2                      50195
//#define BIT_MA_UMAX2                            50196
//#define BIT_MA_PO_UMAX2                         50197

//#define M_ADDRESS_APV_ZMN                     270
//#define BIT_MA_APV_ZMN_BASE                     50224
//#define BIT_MA_RESET_BLOCK_APV_ZMN              50224
//#define BIT_MA_BLOCK_APV_ZMN                    50225
//#define BIT_MA_PO_UAPV_ZMN1                     50226
//#define BIT_MA_PO_UAPV_ZMN2                     50227
//#define BIT_MA_PO_APV_ZMN                       50228
//#define BIT_MA_APV_ZMN                          50229
//#define BIT_MA_BLOCK_KRATN_APV_ZMN              50230
//#define BIT_MA_BLOCK_APV_ZMN_VID_ZAKHYSTIV      50231

//#define BIT_MA_PO_U_OL                          50240
//#define BIT_MA_U_OL                             50241
//#define BIT_MA_PO_U_RL                          50242
//#define BIT_MA_U_RL                             50243

//#define BIT_MA_STAT_BLK_APV                     50272
//#define BIT_MA_APV                              50273
//#define BIT_MA_APV2                             50274
//#define BIT_MA_APV3                             50275
//#define BIT_MA_APV4                             50276
//#define BIT_MA_APV_WORK                         50277

//#define BIT_MA_PUSK_UROV_VID_DV                 50288
//#define BIT_MA_UROV1                            50289
//#define BIT_MA_UROV2                            50290
//#define BIT_MA_PO_UROV                          50291

//#define M_ADDRESS_AVR                         275
//#define BIT_MA_AVR_BASE                         50304
//#define BIT_MA_OTKL_AVR                         50304
//#define BIT_MA_SBROS_BLOCK_AVR                  50305
//#define BIT_MA_STAT_BLOCK_AVR_1                 50306
//#define BIT_MA_STAT_BLOCK_AVR_2                 50307
//#define BIT_MA_PO_AVR_TN1_U1_MIN                50308
//#define BIT_MA_PO_AVR_TN1_U2_LOW_WORK           50309
//#define BIT_MA_PO_AVR_TN2_U2_MIN                50310
//#define BIT_MA_PO_AVR_TN2_U1_LOW_WORK           50311
//#define BIT_MA_BLOCK_AVR                        50312
////#define BIT_MA_BLOCK_KRATN_AVR                  50313
////#define BIT_MA_PUSK_AVR                         50314
//#define BIT_MA_OZT_AVR_1                        50315
//#define BIT_MA_OZT_AVR_2                        50316
//#define BIT_MA_PO_AVR_K1                        50317
//#define BIT_MA_KOM1_ON_AVR                      50318
//#define BIT_MA_KOM1_OFF_AVR                     50319
//#define BIT_MA_KOM3_ON_AVR                      50320
//#define BIT_MA_PO_AVR_K2                        50321
//#define BIT_MA_KOM2_ON_AVR                      50322
//#define BIT_MA_KOM2_OFF_AVR                     50323
//#define BIT_MA_KOM4_ON_AVR                      50324

#define BIT_MA_ERROR_DELTA_U_CTRL_PHASE         50336
#define BIT_MA_ERROR_DELTA_PHI_CTRL_PHASE       50337
#define BIT_MA_ERROR_DELTA_F_CTRL_PHASE         50338
#define BIT_MA_ERROR_SEC_TN1_CTRL_PHASE         50339
#define BIT_MA_ERROR_SEC_TN2_CTRL_PHASE         50340


//#define BIT_MA_ACHR_CHAPV_VID_DV                50352
//#define BIT_MA_BLOCK_ACHR1                      50353
//#define BIT_MA_BLOCK_ACHR2                      50354
//#define BIT_MA_VN_BLOCK_CHAPV                   50355
//#define BIT_MA_PO_ACHR1                         50356
//#define BIT_MA_PO_ACHR2                         50357
//#define BIT_MA_ACHR_CHAPV1                      50358
//#define BIT_MA_ACHR_CHAPV2                      50359
//#define BIT_MA_RAZR_CHAPV                       50360
//#define BIT_MA_PO_CHAPV1                        50361
//#define BIT_MA_PO_CHAPV2                        50362

#define M_ADDRESS_DF                          279
#define BIT_MA_DF_BASE                          50368
#define BIT_MA_INPUT_DF1                        50368
#define BIT_MA_INPUT_DF2                        50369
#define BIT_MA_INPUT_DF3                        50370
#define BIT_MA_INPUT_DF4                        50371
#define BIT_MA_INPUT_DF5                        50372
#define BIT_MA_INPUT_DF6                        50373
#define BIT_MA_INPUT_DF7                        50374
#define BIT_MA_INPUT_DF8                        50375

#define BIT_MA_OUTPUT_DF1                       50384
#define BIT_MA_OUTPUT_DF2                       50385
#define BIT_MA_OUTPUT_DF3                       50386
#define BIT_MA_OUTPUT_DF4                       50387
#define BIT_MA_OUTPUT_DF5                       50388
#define BIT_MA_OUTPUT_DF6                       50389
#define BIT_MA_OUTPUT_DF7                       50390
#define BIT_MA_OUTPUT_DF8                       50391

#define M_ADDRESS_DT                          281
#define BIT_MA_DT_BASE                          50400
#define BIT_MA_DT1_SET                          50400
#define BIT_MA_DT1_RESET                        50401
#define BIT_MA_DT2_SET                          50402
#define BIT_MA_DT2_RESET                        50403
#define BIT_MA_DT3_SET                          50404
#define BIT_MA_DT3_RESET                        50405
#define BIT_MA_DT4_SET                          50406
#define BIT_MA_DT4_RESET                        50407
#define BIT_MA_DT1_OUT                          50408
#define BIT_MA_DT2_OUT                          50409
#define BIT_MA_DT3_OUT                          50410
#define BIT_MA_DT4_OUT                          50411

#define BIT_MA_D_AND1                           50416
#define BIT_MA_D_AND2                           50417
#define BIT_MA_D_AND3                           50418
#define BIT_MA_D_AND4                           50419
#define BIT_MA_D_AND5                           50420
#define BIT_MA_D_AND6                           50421
#define BIT_MA_D_AND7                           50422
#define BIT_MA_D_AND8                           50423
#define BIT_MA_D_OR1                            50424
#define BIT_MA_D_OR2                            50425
#define BIT_MA_D_OR3                            50426
#define BIT_MA_D_OR4                            50427
#define BIT_MA_D_OR5                            50428
#define BIT_MA_D_OR6                            50429
#define BIT_MA_D_OR7                            50430
#define BIT_MA_D_OR8                            50431
#define BIT_MA_D_NOT1                           50432
#define BIT_MA_D_NOT2                           50433
#define BIT_MA_D_NOT3                           50434
#define BIT_MA_D_NOT4                           50435
#define BIT_MA_D_NOT5                           50436
#define BIT_MA_D_NOT6                           50437
#define BIT_MA_D_NOT7                           50438
#define BIT_MA_D_NOT8                           50439
#define BIT_MA_D_NOT9                           50440
#define BIT_MA_D_NOT10                          50441
#define BIT_MA_D_NOT11                          50442
#define BIT_MA_D_NOT12                          50443
#define BIT_MA_D_NOT13                          50444
#define BIT_MA_D_NOT14                          50445
#define BIT_MA_D_NOT15                          50446
#define BIT_MA_D_NOT16                          50447
#define BIT_MA_D_XOR1                           50448
#define BIT_MA_D_XOR2                           50449
#define BIT_MA_D_XOR3                           50450
#define BIT_MA_D_XOR4                           50451
#define BIT_MA_D_XOR5                           50452
#define BIT_MA_D_XOR6                           50453
#define BIT_MA_D_XOR7                           50454
#define BIT_MA_D_XOR8                           50455

#define M_ADDRESS_COMMAND_BASE                285
#define BIT_MA_COMMAND_BASE                     50464
//#define BIT_MA_VKL_VV                           50464
//#define BIT_MA_OTKL_VV                          50465
//#define BIT_MA_BLOCK_VKL_VV                     50466

//#define BIT_MA_WORK_BO                          50468
//#define BIT_MA_WORK_BV                          50469
//#define BIT_MA_STATE_VV                         50470
//#define BIT_MA_GEAR_VV                          50471
//#define BIT_MA_CONTROL_VKL                      50472
//#define BIT_MA_CONTROL_VIDKL                    50473
//#define BIT_MA_PEREVYSHCHENNJA_Inom_VYMK        50474
//#define BIT_MA_KRYTYCHNYJ_RESURS_VYMYKACHA      50475
//#define BIT_MA_VYCHERPANYJ_RESURS_VYMYKACHA     50476
#define BIT_MA_DEFECT                           50477
#define BIT_MA_AVAR_DEFECT                      50478
//#define BIT_MA_RESET_LEDS                       50479
//#define BIT_MA_RESET_RELES                      50480
#define BIT_MA_RESET_GENERAL_AF                 50481
//#define BIT_MA_RESET_RESURS_VYMYKACHA           50482
#define BIT_MA_SETTINGS_CHANGED                 50483
#define BIT_MA_NEW_SETTINGS_SET                 50484
#define BIT_MA_PASSWORD_SET                     50485
//#define BIT_MA_MISCEVE_DYSTANCIJNE              50486
#define BIT_MA_WORK_A_REJESTRATOR               50487
#define BIT_MA_WORK_D_REJESTRATOR               50488

//#define BIT_MA_OTKL_VID_ZOVN_ZAHYSTIV           50493                         
#define BIT_MA_ERROR_CONF_EL                    50494


//#define BIT_MA_DVERI_SHAFY_UPR_VIDKR            50496
//#define BIT_MA_ACUMUL_BATAREJA_ROZRJADGENA      50497
//#define BIT_MA_REZERVTE_GYVLENNJA               50498
//#define BIT_MA_VIDKL_VID_ZAKHYSTIV              50499
//#define BIT_MA_BLK_GRUP_USTAVOK_VID_ZACHYSTIV   50500
//#define BIT_MA_INVERS_DV_GRUPA_USTAVOK          50501
//#define BIT_MA_READY_TU                         50502
//#define BIT_MA_RESET_BLOCK_READY_TU_VID_ZAHYSTIV 50503

#define M_ADDRESS_LAST_CURRENT_AF             287
#define BIT_MA_CURRENT_AF_LAST                  (BIT_MA_CURRENT_AF_BASE + ((M_ADDRESS_LAST_CURRENT_AF - M_ADDRESS_FIRST_CURRENT_AF + 1) << 4) - 1)
/*****************************************************/

/*****************************************************/
/* Загальні активні функції */
/*****************************************************/
#define M_ADDRESS_FIRST_GENERAL_AF            288
#define BIT_MA_GENERAL_AF_BASE                  50512

#define M_ADDRESS_LAST_GENERAL_AF             319
#define BIT_MA_GENERAL_AF_LAST                  (BIT_MA_GENERAL_AF_BASE + ((M_ADDRESS_LAST_GENERAL_AF - M_ADDRESS_FIRST_GENERAL_AF + 1) << 4) - 1)
/*****************************************************/

///*****************************************************/
///* Митєві вимірювання розраховані фетодом перетворення Фур'є */
///*****************************************************/
//#define M_ADDRESS_FIRST_MEASUREMENTS_1        320
//
//#define OFFSET_MEASUREMENT_UA_1                 0
//#define OFFSET_MEASUREMENT_UB_1                 1
//#define OFFSET_MEASUREMENT_UC_1                 2
//#define OFFSET_MEASUREMENT_IA_1                 3
//#define OFFSET_MEASUREMENT_IB_1                 4
//#define OFFSET_MEASUREMENT_IC_1                 5
////#define OFFSET_MEASUREMENT_I04_1                6
//#define OFFSET_ACTIVE_POWER                     7
//#define OFFSET_REACTIVE_POWER                   8
//#define OFFSET_FULL_POWER                       9
//#define OFFSET_COS_PHI                          10
////#define OFFSET_MEASUREMENT_3I0                  11
//#define OFFSET_FREQUENCY_1                      12
//#define OFFSET_EA_PLUS_LWB                      13
//#define OFFSET_EA_PLUS_MWB                      14
//#define OFFSET_EA_MINUS_LWB                     15
//#define OFFSET_EA_MINUS_MWB                     16
//#define OFFSET_ER_1_LWB                         17
//#define OFFSET_ER_1_MWB                         18
//#define OFFSET_ER_2_LWB                         19
//#define OFFSET_ER_2_MWB                         20
//#define OFFSET_ER_3_LWB                         21
//#define OFFSET_ER_3_MWB                         22
//#define OFFSET_ER_4_LWB                         23
//#define OFFSET_ER_4_MWB                         24
//#define OFFSET_MEASUREMENT_UAB_1                25
//#define OFFSET_MEASUREMENT_UBC_1                26
//#define OFFSET_MEASUREMENT_UCA_1                27
////#define OFFSET_MEASUREMENT_3U0_1                28
////#define OFFSET_MEASUREMENT_3I0_r                29
////#define OFFSET_MEASUREMENT_3I0_HIGH_GARM        30
//#define OFFSET_MEASUREMENT_I1                   31
//#define OFFSET_MEASUREMENT_I2                   32
//
//
//#define OFFSET_MEASUREMENT_UA_2                 35
//#define OFFSET_MEASUREMENT_UB_2                 36
//#define OFFSET_MEASUREMENT_UC_2                 37
//#define OFFSET_MEASUREMENT_UAB_2                38
//#define OFFSET_MEASUREMENT_UBC_2                39
//#define OFFSET_MEASUREMENT_UCA_2                40
//
//#define OFFSET_FREQUENCY_2                      42
//
//#define OFFSET_BASE_CANAL_FOR_ANGLE             44
//
//#define BASE_CANAL_NONE                                 0
//#define BASE_CANAL_UA_TN1                               1
//#define BASE_CANAL_UB_TN1                               2
//#define BASE_CANAL_UC_TN1                               3
//#define BASE_CANAL_UAB_TN1                              4
//#define BASE_CANAL_UBC_TN1                              5
//#define BASE_CANAL_UCA_TN1                              6
//#define BASE_CANAL_3U0                                  7
//#define BASE_CANAL_UA_TN2                               8
//#define BASE_CANAL_UB_TN2                               9
//#define BASE_CANAL_UC_TN2                               10
//#define BASE_CANAL_UAB_TN2                              11
//#define BASE_CANAL_UBC_TN2                              12
//#define BASE_CANAL_UCA_TN2                              13
//
//#define OFFSET_ANGLE_UA_1                       45
//#define OFFSET_ANGLE_UB_1                       46
//#define OFFSET_ANGLE_UC_1                       47
//#define OFFSET_ANGLE_UAB_1                      48
//#define OFFSET_ANGLE_UBC_1                      49
//#define OFFSET_ANGLE_UCA_1                      50
////#define OFFSET_ANGLE_3U0_1                      51
//#define OFFSET_ANGLE_UA_2                       52
//#define OFFSET_ANGLE_UB_2                       53
//#define OFFSET_ANGLE_UC_2                       54
//#define OFFSET_ANGLE_UAB_2                      55
//#define OFFSET_ANGLE_UBC_2                      56
//#define OFFSET_ANGLE_UCA_2                      57
//#define OFFSET_ANGLE_IA_1                       58
//#define OFFSET_ANGLE_IB_1                       59
//#define OFFSET_ANGLE_IC_1                       60
////#define OFFSET_ANGLE_I04_1                      61
////#define OFFSET_ANGLE_3I0                        62
////#define OFFSET_ANGLE_3I0_r                      63
//
//#define M_ADDRESS_LAST_MEASUREMENTS_1         388
///*****************************************************/

/**************Лічильник ресурсів********************/
#define M_COUNTER_FIRST                       389

#define MA_COUNTER_VIDKLJUCHENNJA_LSW         389
#define MA_COUNTER_VIDKLJUCHENNJA_MSW         390
#define MA_COUNTER_VYMYKACHA_LSW              391
#define MA_COUNTER_VYMYKACHA_MSW              392

#define M_COUNTER_LAST                        392

/*****************************************************/

/*****************************************************/
/* Вимірювання в момент роботи дискретного реєстратора*/
/*****************************************************/
#define MEASUREMENTS_DR_WIDTH                 32 
#define M_ADDRESS_FIRST_MEASUREMENTS_DR       393

#define DR_OFFSET_MEASUREMENT_UA_1            0
#define DR_OFFSET_MEASUREMENT_UB_1            1
#define DR_OFFSET_MEASUREMENT_UC_1            2
#define DR_OFFSET_MEASUREMENT_IA_1            3
#define DR_OFFSET_MEASUREMENT_IB_1            4
#define DR_OFFSET_MEASUREMENT_IC_1            5
//#define DR_OFFSET_MEASUREMENT_I04_1           6
#define DR_OFFSET_MEASUREMENT_UAB_1           7
#define DR_OFFSET_MEASUREMENT_UBC_1           8
#define DR_OFFSET_MEASUREMENT_UCA_1           9
//#define DR_OFFSET_MEASUREMENT_3U0_1           10
//#define DR_OFFSET_MEASUREMENT_3I0             11
//#define DR_OFFSET_MEASUREMENT_3I0_r           12
//#define DR_OFFSET_MEASUREMENT_3I0_HIGH_GARM   13
#define DR_OFFSET_MEASUREMENT_I1              14
#define DR_OFFSET_MEASUREMENT_I2              15
#define DR_OFFSET_FREQUENCY_1                 16

#define DR_OFFSET_MEASUREMENT_UA_2            19
#define DR_OFFSET_MEASUREMENT_UB_2            20
#define DR_OFFSET_MEASUREMENT_UC_2            21
#define DR_OFFSET_MEASUREMENT_UAB_2           22
#define DR_OFFSET_MEASUREMENT_UBC_2           23
#define DR_OFFSET_MEASUREMENT_UCA_2           24

#define DR_OFFSET_FREQUENCY_2                 26

//#define DR_OFFSET_VMP                         28
#define DR_OFFSET_LABEL_TIME_LSW              29
#define DR_OFFSET_LABEL_TIME_MSW              30
#define DR_OFFSET_LABEL_PROTECT               31

#define BLOCK_PROTECTION_MTZ                  1
//#define BLOCK_PROTECTION_3I0                  2
//#define BLOCK_PROTECTION_3U0                  3
#define BLOCK_PROTECTION_UMIN                 4
#define BLOCK_PROTECTION_UMAX                 5
#define BLOCK_PROTECTION_ZOP                  6

//#define BLOCK_PROTECTION_FREQUENCY_1_ACHR     9
//#define BLOCK_PROTECTION_FREQUENCY_1_CAPV     10
//#define BLOCK_PROTECTION_FREQUENCY_2_ACHR     11
//#define BLOCK_PROTECTION_FREQUENCY_2_CAPV     12
//#define BLOCK_PROTECTION_MTZ04                13

#define M_ADDRESS_LAST_MEASUREMENTS_DR        712
/*****************************************************/

/*****************************************************/
/* Адресний простір вcтановлення ранжування (крім реєстраторів) */
/*****************************************************/
#define M_ADDRESS_FIRST_SETPOINTS_RANG        1016

#define M_ADDRESS_FIRST_USER_REGISTER         1016
#define M_ADDRESS_LAST_USER_REGISTER          1099

//#define M_ADDRESS_FIRST_DO_RANG               1100
//#define M_ADDRESS_LAST_DO_RANG                1355
//
//#define M_ADDRESS_FIRST_DI_RANG               1356
//#define M_ADDRESS_LAST_DI_RANG                1483
//
//#define M_ADDRESS_FIRST_LED_RANG              1484
//#define M_ADDRESS_LAST_LED_RANG               1547
//
//#define M_ADDRESS_FIRST_DF_RANG               1548
//#define M_ADDRESS_LAST_DF_RANG                2027
//
//#define M_ADDRESS_FIRST_DB_RANG               2028
//#define M_ADDRESS_LAST_DB_RANG                2091
//
//#define M_ADDRESS_FIRST_DT_RANG               2092
//#define M_ADDRESS_LAST_DT_RANG                2187

//#define M_ADDRESS_FIRST_ON_CB_RANG            2188
//#define M_ADDRESS_LAST_ON_CB_RANG             2219
//
//#define M_ADDRESS_FIRST_OFF_CB_RANG           2220
//#define M_ADDRESS_LAST_OFF_CB_RANG            2251

//#define M_ADDRESS_FIRST_D_AND_RANG            2252
//#define M_ADDRESS_LAST_D_AND_RANG             2315
//
//#define M_ADDRESS_FIRST_D_OR_RANG             2316
//#define M_ADDRESS_LAST_D_OR_RANG              2379
//
//#define M_ADDRESS_FIRST_D_XOR_RANG            2380
//#define M_ADDRESS_LAST_D_XOR_RANG             2395
//
//#define M_ADDRESS_FIRST_D_NOT_RANG            2396
//#define M_ADDRESS_LAST_D_NOT_RANG             2411

#define M_ADDRESS_LAST_SETPOINTS_RANG         2411
/*****************************************************/

/*****************************************************/
/*Налаштування*/
/*****************************************************/
#define M_ADDRESS_CONTROL_BASE            10000
#define BIT_MA_CONTROL_BASE                   55000

#define M_ADDRESS_CONTROL_MTZ_PART1       10000
#define BIT_MA_CONTROL_MTZ_BASE_PART1         55000
#define BIT_MA_CONFIGURATION_MTZ              55000  
#define BIT_MA_CONTROL_MTZ1                   55001
#define BIT_MA_CONTROL_MTZ1_N_VPERED          55002
#define BIT_MA_CONTROL_MTZ1_N_NAZAD           55003
#define BIT_MA_CONTROL_MTZ2                   55004
#define BIT_MA_CONTROL_MTZ2_N_VPERED          55005
#define BIT_MA_CONTROL_MTZ2_N_NAZAD           55006
#define BIT_MA_CONTROL_MTZ2_PRYSKORENNJA      55007
#define BIT_MA_CONTROL_MTZ2_PRYSKORENA        55008
#define BIT_MA_CONTROL_MTZ3                   55009
#define BIT_MA_CONTROL_MTZ3_N_VPERED          55010
#define BIT_MA_CONTROL_MTZ3_N_NAZAD           55011
#define BIT_MA_CONTROL_MTZ3_PRYSKORENNJA      55012
#define BIT_MA_CONTROL_MTZ3_PRYSKORENA        55013
#define BIT_MA_CONTROL_MTZ4                   55014
#define BIT_MA_CONTROL_MTZ4_N_VPERED          55015

#define M_ADDRESS_CONTROL_MTZ_PART2       10001
#define BIT_MA_CONTROL_MTZ_BASE_PART2         55016
#define BIT_MA_CONTROL_MTZ4_N_NAZAD           55016
#define BIT_MA_CONTROL_MTZ_NESPR_KIL_NAPR     55017     

//#define M_ADDRESS_CONTROL_MTZ04           10002
//#define BIT_MA_CONTROL_MTZ04_BASE             55032
//#define BIT_MA_CONFIGURATION_MTZ04            55032
//#define BIT_MA_CONTROL_MTZ04_1                55033
//#define BIT_MA_CONTROL_MTZ04_2                55034
//#define BIT_MA_CONTROL_MTZ04_2_PRYSKORENNJA   55035
//#define BIT_MA_CONTROL_MTZ04_2_PRYSKORENA     55036

#define M_ADDRESS_CONTROL_ZDZ             10003
#define BIT_MA_CONTROL_ZDZ_BASE               55048
#define BIT_MA_CONFIGURATION_ZDZ              55048  
#define BIT_MA_CONTROL_ZDZ                    55049
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ1  55050
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ2  55051
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ3  55052
#define BIT_MA_CONTROL_ZDZ_STARTED_FROM_MTZ4  55053

//#define M_ADDRESS_CONTROL_NZZ             10004
//#define BIT_MA_CONTROL_NZZ_BASE               55064
//#define BIT_MA_CONFIGURATION_ZZ               55064  
//#define BIT_MA_CONTROL_NZZ_3I0                55065

//#define BIT_MA_CONTROL_NZZ_SECTOR             55067
//#define BIT_MA_CONTROL_NZZ                    55068
//#define BIT_MA_CONTROL_NZZ_3U0                55069
//#define BIT_MA_CONTROL_NZZ_TYPE               55070

//#define M_ADDRESS_CONTROL_TZNP            10005
//#define BIT_MA_CONTROL_TZNP_BASE              55080
//#define BIT_MA_CONFIGURATION_TZNP             55080  
//#define BIT_MA_CONTROL_TZNP1                  55081
//#define BIT_MA_CONTROL_TZNP1_VPERED           55082
//#define BIT_MA_CONTROL_TZNP1_NAZAD            55083
//#define BIT_MA_CONTROL_TZNP2                  55084
//#define BIT_MA_CONTROL_TZNP2_VPERED           55085
//#define BIT_MA_CONTROL_TZNP2_NAZAD            55086
//#define BIT_MA_CONTROL_TZNP3                  55087
//#define BIT_MA_CONTROL_TZNP3_VPERED           55088
//#define BIT_MA_CONTROL_TZNP3_NAZAD            55089

#define M_ADDRESS_CONTROL_ZOP             10006
#define BIT_MA_CONTROL_ZOP_BASE               55096
#define BIT_MA_CONFIGURATION_ZOP              55096  
#define BIT_MA_CONTROL_ZOP1                   55097

//#define M_ADDRESS_CONTROL_ACHR_CHAPV      10007
//#define BIT_MA_CONTROL_ACHR_CHAPV_BASE        55112
//#define BIT_MA_CONFIGURATION_ACHR_CHAPV       55112  
//#define BIT_MA_CONTROL_ACHR1_STATE            55113
//#define BIT_MA_CONTROL_ACHR2_STATE            55114
//#define BIT_MA_CONTROL_CHAPV1_STATE           55115
//#define BIT_MA_CONTROL_CHAPV2_STATE           55116
//#define BIT_MA_CONTROL_CHAPV_VID_DV_STATE     55117

#define M_ADDRESS_CONTROL_UMIN            10008
#define BIT_MA_CONTROL_UMIN_BASE              55128
#define BIT_MA_CONFIGURATION_UMIN             55128  
#define BIT_MA_CONTROL_UMIN1                  55129
#define BIT_MA_CONTROL_UMIN2                  55130
#define BIT_MA_CONTROL_PO_UMIN1_AND_OR        55131
#define BIT_MA_CONTROL_PO_UMIN2_AND_OR        55132
#define BIT_MA_CONTROL_BLK_UMIN1_BY_U         55133
#define BIT_MA_CONTROL_BLK_UMIN2_BY_U         55134
#define BIT_MA_CONTROL_BLK_UMIN1_BY_I         55135
#define BIT_MA_CONTROL_BLK_UMIN2_BY_I         55136

#define M_ADDRESS_CONTROL_UMAX            10009
#define BIT_MA_CONTROL_UMAX_BASE              55144
#define BIT_MA_CONFIGURATION_UMAX             55144  
#define BIT_MA_CONTROL_UMAX1                  55145
#define BIT_MA_CONTROL_UMAX2                  55146
#define BIT_MA_CONTROL_PO_UMAX1_AND_OR        55147
#define BIT_MA_CONTROL_PO_UMAX2_AND_OR        55148

#define M_ADDRESS_CONTROL_EXTRA_SETTINGS 10011
#define BIT_MA_CONTROL_EXTRA_SETTINGS_BASE    55176

#define BIT_MA_CONTROL_PHASE_LINE             55177
//#define BIT_MA_CONTROL_3U0_Ubc_TN2            55178
//#define BIT_MA_CONTROL_IB_I04                 55179

//#define BIT_MA_CONTROL_APV_ZMN                55193

//#define BIT_MA_CONTROL_U_OL                   55209
//#define BIT_MA_CONTROL_U_RL                   55210

#define M_ADDRESS_CONTROL_APV             10015
#define BIT_MA_CONTROL_APV_BASE               55240
#define BIT_MA_CONFIGURATION_APV              55240  
#define BIT_MA_CONTROL_APV_CYCLE1             55241
#define BIT_MA_CONTROL_APV_CYCLE2             55242
#define BIT_MA_CONTROL_APV_CYCLE3             55243
#define BIT_MA_CONTROL_APV_CYCLE4             55244
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ1  55245
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ2  55246
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ3  55247
#define BIT_MA_CONTROL_APV_STARTED_FROM_MTZ4  55248

#define M_ADDRESS_CONTROL_UROV_PART1      10016
#define BIT_MA_CONTROL_UROV_BASE_PART1           55256
#define BIT_MA_CONFIGURATION_UROV                55256  
#define BIT_MA_CONTROL_UROV_STATE                55257
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ1    55258
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ2    55259
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ3    55260
#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ4    55261
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ04_1 55262
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_MTZ04_2 55263
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX1   55264
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMAX2   55265
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN1   55266
#define BIT_MA_CONTROL_UROV_STARTED_FROM_UMIN2   55267
#define BIT_MA_CONTROL_UROV_STARTED_FROM_ZOP1    55268

//#define BIT_MA_CONTROL_UROV_STARTED_FROM_NZZ     55270
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_3I0     55271


#define M_ADDRESS_CONTROL_UROV_PART2      10017
#define BIT_MA_CONTROL_UROV_BASE_PART2         55272
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_3U0   55273
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_TZNP1 55274
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_TZNP2 55275
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_TZNP3 55276
#define BIT_MA_CONTROL_UROV_STARTED_FROM_ZDZ   55277
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_ACHR1 55278
//#define BIT_MA_CONTROL_UROV_STARTED_FROM_ACHR2 55279

#define M_ADDRESS_CONTROL_AVR             10018
#define BIT_MA_CONTROL_AVR_BASE               55288
#define BIT_MA_CONFIGURATION_AVR              55288  
#define BIT_MA_CONTROL_AVR                    55289
#define BIT_MA_CONTROL_AVR_BLK                55290

#define M_ADDRESS_CONTROL_CTRL_VV         10019
#define BIT_MA_CONTROL_CTRL_VV_BASE            55304
#define BIT_MA_CONTROL_CTRL_VV_STATE           55304

#define BIT_MA_CONTROL_CTRL_BLK_ON_CB_MISCEVE  55307
#define BIT_MA_CONTROL_CTRL_BLK_OFF_CB_MISCEVE 55308
#define BIT_MA_CONTROL_CTRL_FB_ACTIVATION      55309
#define BIT_MA_CONTROL_CTRL_RESURS_VV          55310
#define BIT_MA_CONTROL_CTRL_READY_TU           55311
#define BIT_MA_CONTROL_CTRL_WINDOW_OFF_CB      55312

//#define M_ADDRESS_CONTROL_VMP             10020
//#define BIT_MA_CONTROL_VMP_BASE                55320
//#define BIT_MA_CONFIGURATION_VMP               55320  
//#define BIT_MA_CONTROL_VMP_STATE               55321

//#define M_ADDRESS_CONTROL_CTRL_PHASE      10021
//#define BIT_MA_CONTROL_CTRL_PHASE_BASE         55336
//#define BIT_MA_CONFIGURATION_CTRL_PHASE        55336  
//#define BIT_MA_CONTROL_CTRL_PHASE_U            55337
//#define BIT_MA_CONTROL_CTRL_PHASE_PHI          55338
//#define BIT_MA_CONTROL_CTRL_PHASE_F            55339
//#define BIT_MA_CONTROL_CTRL_PHASE_SEQ_TN1      55340
//#define BIT_MA_CONTROL_CTRL_PHASE_SEQ_TN2      55341

#define M_ADDRESS_CONTROL_EL              10022
#define BIT_MA_CONTROL_EL_BASE                55352
#define BIT_MA_CONFIGURATION_EL               55352  

#define M_ADDRESS_CONTROL_LAST            10022
#define BIT_MA_CONTROL_LAST                   (BIT_MA_CONTROL_BASE + ((M_ADDRESS_CONTROL_LAST - M_ADDRESS_CONTROL_BASE + 1) << 4) - 1)
/*****************************************************/


/*****************************************************/
/* Адресний простір встановлення уставок і витримок */
/*****************************************************/
#define M_ADDRESS_FIRST_SETPOINTS_PART1 10300

//#define MA_GROUP_USTAVOK                  10300

//#define MA_TYPE_MTZ1                      10301
//#define MA_TYPE_MTZ2                      10302
//#define MA_TYPE_MTZ3                      10303
//#define MA_TYPE_MTZ4                      10304

//#define MA_TYPE_MTZ04_2                   10306

#define M_ADDRESS_LAST_SETPOINTS_PART1    10306

#define M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV 10307
#define SHIFT_G1        0
//#define SHIFT_G2        (10482 - M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV)
//#define SHIFT_G3        (10657 - M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV)
//#define SHIFT_G4        (10832 - M_ADDRESS_FIRST_SETPOINTS_ZACHYSTIV)

//#define MA_STP_MTZ1                       10307
//#define MA_STP_MTZ1_N_VPERED              10308
//#define MA_STP_MTZ1_N_NAZAD               10309
//#define MA_STP_MTZ1_PO_NAPRUZI            10310
//#define MA_STP_MTZ1_U                     10311
//#define MA_STP_MTZ1_ANGLE                 10312
//#define MA_TO_MTZ1                        10313
//#define MA_TO_MTZ1_N_VPERED               10314
//#define MA_TO_MTZ1_N_NAZAD                10315
//#define MA_TO_MTZ1_PO_NAPRUZI             10316
//#define MA_STP_MTZ2                       10317
//#define MA_STP_MTZ2_N_VPERED              10318
//#define MA_STP_MTZ2_N_NAZAD               10319
//#define MA_STP_MTZ2_PO_NAPRUZI            10320
//#define MA_STP_MTZ2_U                     10321
//#define MA_STP_MTZ2_ANGLE                 10322
//#define MA_TO_MTZ2                        10323
//#define MA_TO_MTZ2_N_VPERED               10324
//#define MA_TO_MTZ2_N_NAZAD                10325
//#define MA_TO_MTZ2_PO_NAPRUZI             10326
//#define MA_TO_MTZ2_VVID_PR                10327
//#define MA_TO_MTZ2_PR                     10328
//#define MA_TO_MTZ2_N_VPERED_PR            10329
//#define MA_TO_MTZ2_N_NAZAD_PR             10330
//#define MA_TO_MTZ2_PO_NAPRUZI_PR          10331
//#define MA_STP_MTZ3                       10332
//#define MA_STP_MTZ3_N_VPERED              10333
//#define MA_STP_MTZ3_N_NAZAD               10334
//#define MA_STP_MTZ3_PO_NAPRUZI            10335
//#define MA_STP_MTZ3_U                     10336
//#define MA_STP_MTZ3_ANGLE                 10337
//#define MA_TO_MTZ3                        10338
//#define MA_TO_MTZ3_N_VPERED               10339
//#define MA_TO_MTZ3_N_NAZAD                10340
//#define MA_TO_MTZ3_PO_NAPRUZI             10341
//#define MA_TO_MTZ3_VVID_PR                10342
//#define MA_TO_MTZ3_PR                     10343
//#define MA_TO_MTZ3_N_VPERED_PR            10344
//#define MA_TO_MTZ3_N_NAZAD_PR             10345
//#define MA_TO_MTZ3_PO_NAPRUZI_PR          10346
//#define MA_STP_MTZ4                       10347
//#define MA_STP_MTZ4_N_VPERED              10348
//#define MA_STP_MTZ4_N_NAZAD               10349
//#define MA_STP_MTZ4_PO_NAPRUZI            10350
//#define MA_STP_MTZ4_U                     10351
//#define MA_STP_MTZ4_ANGLE                 10352
//#define MA_TO_MTZ4                        10353
//#define MA_TO_MTZ4_N_VPERED               10354
//#define MA_TO_MTZ4_N_NAZAD                10355
//#define MA_TO_MTZ4_PO_NAPRUZI             10356
//#define MA_STP_MTZ04_1                    10357
//#define MA_TO_MTZ04_1                     10358
//#define MA_STP_MTZ04_2                    10359
//#define MA_TO_MTZ04_2                     10360
//#define MA_TO_MTZ04_2_VVID_PR             10361
//#define MA_TO_MTZ04_2_PR                  10362

//#define MA_STP_NZZ1_3I0                   10363
//#define MA_TO_NZZ1_3I0                    10364

//#define MA_STP_NZZ1_3U0                   10367
//#define MA_TO_NZZ1_3U0                    10368

//#define MA_TO_NZZ1                        10370

//#define MA_STP_TZNP1_3I0_VPERED           10371
//#define MA_STP_TZNP1_3U0_VPERED           10372
//#define MA_TO_TZNP1_VPERED                10373
//#define MA_STP_TZNP1_3I0_NAZAD            10374
//#define MA_STP_TZNP1_3U0_NAZAD            10375
//#define MA_TO_TZNP1_NAZAD                 10376
//#define MA_STP_TZNP1_ANGLE                10377
//#define MA_STP_TZNP2_3I0_VPERED           10378
//#define MA_STP_TZNP2_3U0_VPERED           10379
//#define MA_TO_TZNP2_VPERED                10380
//#define MA_STP_TZNP2_3I0_NAZAD            10381
//#define MA_STP_TZNP2_3U0_NAZAD            10382
//#define MA_TO_TZNP2_NAZAD                 10383
//#define MA_STP_TZNP2_ANGLE                10384
//#define MA_STP_TZNP3_3I0_VPERED           10385
//#define MA_STP_TZNP3_3U0_VPERED           10386
//#define MA_TO_TZNP3_VPERED                10387
//#define MA_STP_TZNP3_3I0_NAZAD            10388
//#define MA_STP_TZNP3_3U0_NAZAD            10389
//#define MA_TO_TZNP3_NAZAD                 10390
//#define MA_STP_TZNP3_ANGLE                10391

//#define MA_STP_ZOP1                       10392
//#define MA_TO_ZOP1                        10383

//#define MA_STP_UMIN1                      10398
//#define MA_TO_UMIN1                       10399
//#define MA_STP_UMIN2                      10400
//#define MA_TO_UMIN2                       10401
//#define MA_STP_BLK_UMIN1_BY_I             10402
//#define MA_STP_BLK_UMIN2_BY_I             10403

//#define MA_STP_UMAX1                      10404
//#define MA_TO_UMAX1                       10405
//#define MA_STP_UMAX2                      10406
//#define MA_TO_UMAX2                       10407

//#define MA_STP_U_OL                       10411
//#define MA_STP_U_RL                       10412
//#define MA_TO_U_OL                        10413
//#define MA_TO_U_RL                        10414

//#define MA_STP_UROV                       10423
//#define MA_TO_UROV1                       10424
//#define MA_TO_UROV2                       10425

//#define MA_STP_AVR_TN1_U1_UMIN            10426
//#define MA_STP_AVR_TN1_U2_LOW_WORK        10427
//#define MA_STP_AVR_TN2_U2_UMIN            10428
//#define MA_STP_AVR_TN2_U1_LOW_WORK        10429
////#define MA_TO_AVR_RL                      10430
//#define MA_TO_AVR_OL                      10431
//#define MA_STP_KRATN_AVR                  10432
//#define MA_TO_AVR_ZAVERSHENNJA            10433
//#define MA_TO_AVR_RESET_BLK               10434
//#define MA_TO_AVR_GENERAL_BLK_K1          10435
//#define MA_TO_AVR_GENERAL_PUSK_K1         10436
//#define MA_TO_AVR_GENERAL_D_DIJI_K1       10437
//#define MA_TO_AVR_GENERAL_VVIMK_REZ_K1    10438
//#define MA_TO_AVR_GENERAL_VVIMK_K1        10439
//#define MA_TO_AVR_GENERAL_VYMK_ROB_K1     10440
//#define MA_TO_AVR_GENERAL_VYMK_K1         10441
//#define MA_TO_AVR_GENERAL_BLK_K2          10442
//#define MA_TO_AVR_GENERAL_PUSK_K2         10443
//#define MA_TO_AVR_GENERAL_D_DIJI_K2       10444
//#define MA_TO_AVR_GENERAL_VVIMK_REZ_K2    10445
//#define MA_TO_AVR_GENERAL_VVIMK_K2        10446
//#define MA_TO_AVR_GENERAL_VYMK_ROB_K2     10447
//#define MA_TO_AVR_GENERAL_VYMK_K2         10448

//#define MA_TO_APV_BLOCK_VID_VV            10449
//#define MA_TO_APV_CYCLE_1                 10450
//#define MA_TO_APV_CYCLE_2                 10451
//#define MA_TO_APV_CYCLE_3                 10452
//#define MA_TO_APV_CYCLE_4                 10453
//#define MA_TO_APV_BLOCK_VID_APV1          10454
//#define MA_TO_APV_BLOCK_VID_APV2          10455
//#define MA_TO_APV_BLOCK_VID_APV3          10456
//#define MA_TO_APV_BLOCK_VID_APV4          10457

//#define MA_STP_APV_ZMN1                   10458
//#define MA_STP_APV_ZMN2                   10459
//#define MA_TO_APV_ZMN1                    10460
//#define MA_TO_APV_ZMN2                    10461
//#define MA_STP_KRATN_APV_ZMN              10462
//#define MA_TO_APV_ZMN_ZAVERSHENNJA        10463

//#define MA_STP_ACHR1_F_RAB                10464
//#define MA_STP_ACHR2_F_RAB                10465
//#define MA_STP_CHAPV1_F_RAB               10466
//#define MA_STP_CHAPV2_F_RAB               10467
//#define MA_STP_ACHR_CHAPV_UF              10468
//#define MA_TO_ACHR_1                      10469
//#define MA_TO_ACHR_2                      10470
//#define MA_TO_CHAPV_1                     10471
//#define MA_TO_CHAPV_2                     10472

//#define MA_STP_CTRL_PHASE_U               10473
//#define MA_STP_CTRL_PHASE_PHI             10474
//#define MA_STP_CTRL_PHASE_F               10475
//#define MA_TO_CTRL_PHASE_U                10476
//#define MA_TO_CTRL_PHASE_U_D              10477
//#define MA_TO_CTRL_PHASE_PHI              10478
//#define MA_TO_CTRL_PHASE_PHI_D            10479
//#define MA_TO_CTRL_PHASE_F                10480
//#define MA_TO_CTRL_PHASE_F_D              10481


#define M_ADDRESS_LAST_SETPOINTS_ZACHYSTIV 10481

#define M_ADDRESS_FIRST_SETPOINTS_CONTINUE 11107

//#define MA_LINE_1                         11107
//#define MA_DOVGYNA_1_1                    11108
//#define MA_OPIR_1_1                       11109
//#define MA_DOVGYNA_1_2                    11110
//#define MA_OPIR_1_2                       11111
//#define MA_DOVGYNA_1_3                    11112
//#define MA_OPIR_1_3                       11113
//#define MA_DOVGYNA_1_4                    11114
//#define MA_OPIR_1_4                       11115
//#define MA_DOVGYNA_1_5                    11116
//#define MA_OPIR_1_5                       11117
//#define MA_DOVGYNA_1_6                    11118
//#define MA_OPIR_1_6                       11119
//#define MA_DOVGYNA_1_7                    11020
//#define MA_OPIR_1_7                       11021
//#define MA_DOVGYNA_1_8                    11022
//#define MA_OPIR_1_8                       11023
//#define MA_LINE_2                         11024
//#define MA_DOVGYNA_2_1                    11025
//#define MA_OPIR_2_1                       11026
//#define MA_DOVGYNA_2_2                    11027
//#define MA_OPIR_2_2                       11028
//#define MA_DOVGYNA_2_3                    11029
//#define MA_OPIR_2_3                       11030
//#define MA_DOVGYNA_2_4                    11031
//#define MA_OPIR_2_4                       11032
//#define MA_DOVGYNA_2_5                    11033
//#define MA_OPIR_2_5                       11034
//#define MA_DOVGYNA_2_6                    11035
//#define MA_OPIR_2_6                       11036
//#define MA_DOVGYNA_2_7                    11037
//#define MA_OPIR_2_7                       11038
//#define MA_DOVGYNA_2_8                    11039
//#define MA_OPIR_2_8                       11040

//#define MA_TN1                            11041

//#define MA_TT                             11043
//#define MA_T0                             11044
//#define MA_TT04                           11045

//#define MA_TO_SWCH_UDL_BLK_ON             11046
//#define MA_TO_SWCH_ON                     11047
//#define MA_TO_SWCH_OFF                    11048
//#define MA_TO_FAULT_CONTROL_CIRCUIT       11049

//#define MA_STP_Inom                       11051
//#define MA_STP_RKS_Inom                   11052
//#define MA_STP_Inom_vymk                  11053
//#define MA_STP_RKS_Inom_vymk              11054
//#define MA_STP_POCHATKOVYJ_RESURS_LSW     11055
//#define MA_STP_POCHATKOVYJ_RESURS_MSW     11056
//#define MA_STP_KRYTYCHNYJ_RESURS          11057
//#define MA_POCHATKOVA_K_VYMK_LSW          11058
//#define MA_POCHATKOVA_K_VYMK_MSW          11059

#define MA_UVV_TYPE_SIGNAL_INPUT          11064
//#define MA_UVV_TYPE_INPUT                 11065
//#define MA_UVV_TYPE_OUTPUT                11066
//#define MA_UVV_TYPE_OUTPUT_MODIF          11067
#define MA_TYPE_DF                        11068
//#define MA_UVV_TYPE_LED                   11069

#define MA_DOPUSK_DV_1                    11070
#define MA_DOPUSK_DV_2                    11071
#define MA_DOPUSK_DV_3                    11072
#define MA_DOPUSK_DV_4                    11073
#define MA_DOPUSK_DV_5                    11074
#define MA_DOPUSK_DV_6                    11075
#define MA_DOPUSK_DV_7                    11076
#define MA_DOPUSK_DV_8                    11077
#define MA_DOPUSK_DV_9                    11078
#define MA_DOPUSK_DV_10                   11079

#define MA_DF_PAUSE_1                     11086
#define MA_DF_PAUSE_2                     11087
#define MA_DF_PAUSE_3                     11088
#define MA_DF_PAUSE_4                     11089
#define MA_DF_PAUSE_5                     11090
#define MA_DF_PAUSE_6                     11091
#define MA_DF_PAUSE_7                     11092
#define MA_DF_PAUSE_8                     11093

#define MA_DF_WORK_1                      11096
#define MA_DF_WORK_2                      11097
#define MA_DF_WORK_3                      11098
#define MA_DF_WORK_4                      11099
#define MA_DF_WORK_5                      11100
#define MA_DF_WORK_6                      11101
#define MA_DF_WORK_7                      11102
#define MA_DF_WORK_8                      11103


/***/
#define MA_TO_DEACTIVATION_PASSWORD_INTERFACE 12000
#define MA_PASSWORD_INTERFACE                 12001
#define MA_TO_IDLE_NEW_SETTINGS               12002
/***/

#define MA_LANGUAGE_MENU                      12003


#define MA_SPEED_RS485_1                      12005
#define MA_STOP_BITS_RS485_1                  12006
#define MA_PARE_RS485_1                       12007
#define MA_TIMEOUT_RS485_1                    12008

#define MA_LOGICAL_ADDRESS                    12013

#define MA_NAME_OF_CELL_CHARS_01_02           12016
#define MA_NAME_OF_CELL_CHARS_03_04           12017
#define MA_NAME_OF_CELL_CHARS_05_06           12018
#define MA_NAME_OF_CELL_CHARS_07_08           12019
#define MA_NAME_OF_CELL_CHARS_09_10           12020
#define MA_NAME_OF_CELL_CHARS_11_12           12021
#define MA_NAME_OF_CELL_CHARS_13_14           12022
#define MA_NAME_OF_CELL_CHARS_15_16           12023

#define M_ADDRESS_LAST_SETPOINTS_CONTINUE     12023
/*****************************************************/

/*****************************************************/
/* Адресний простір дати і часу */
/*****************************************************/
#define M_ADDRESS_FIRST_TIME_AND_DATA         12024

#define MA_YEAR                               12024
#define MA_MONTH                              12025
#define MA_DAY                                12026
#define MA_HOUR                               12027
#define MA_MINUTE                             12028
#define MA_SECOND                             12029
#define MA_MILISECOND                         12030

#define M_ADDRESS_LAST_TIME_AND_DATA          12030
/*****************************************************/

/*****************************************************/
/* Адресний простір настроювання аналогового реєстратора */
/*****************************************************/
//#define M_ADDRESS_FIRST_SETPOINTS_RANG_AR     13000
//#define M_ADDRESS_LAST_SETPOINTS_RANG_AR      (M_ADDRESS_FIRST_SETPOINTS_RANG_AR + MAX_FUNCTIONS_IN_AREG - 1)
//
//#define MA_PREFAULT_INTERVAL_AR               13032
//#define MA_POSTFAULT_INTERVAL_AR              13033
//#define MA_TOTAL_NUMBER_RECORDS_AR            13034
//#define MA_CURRENT_NUMBER_RECORD_AR           13035
/*****************************************************/

/*****************************************************/
/* Адресний простір настроювання дискретного реєстратора */
/*****************************************************/
//#define M_ADDRESS_FIRST_SETPOINTS_RANG_DR     13036
//#define M_ADDRESS_LAST_SETPOINTS_RANG_DR      (M_ADDRESS_FIRST_SETPOINTS_RANG_DR + MAX_FUNCTIONS_IN_DREG - 1)
//
//#define MA_TOTAL_NUMBER_RECORDS_DR            13070
//#define MA_CURRENT_NUMBER_RECORD_DR           13071
/*****************************************************/

/*****************************************************/
/* Адресний простір очистки аналогового і дискретного реєстраторів */
/*****************************************************/
//#define MA_CLEAR_NUMBER_RECORD_AR     13074
//#define CMD_WORD_CLEAR_AR                     0x1312
//#define MA_CLEAR_NUMBER_RECORD_DR     13075
//#define CMD_WORD_CLEAR_DR                     0x1012
/*****************************************************/

/*****************************************************/
/* Адресний простір реєстратора програмних подій     */
/*****************************************************/
#define MA_CLEAR_NUMBER_RECORD_PR_ERR         61800
#define MA_CURRENT_NUMBER_RECORD_PR_ERR       61801
#define MA_TOTAL_NUMBER_RECORDS_PR_ERR        61802
#define MA_FIRST_ADR_PR_ERR_WINDOW            61803
#define MA_LASR_ADR_PR_ERR_WINDOW             61818
/*****************************************************/

/*****************************************************/
/* Митєві вимірювання розраховані фетодом квадратного кореня суми квадратів миттєвих значень за період */
/*****************************************************/
//#define M_ADDRESS_FIRST_MEASUREMENTS_2        61904
//
//#define OFFSET_MEASUREMENT_3I0_I              3
//
//#define M_ADDRESS_LAST_MEASUREMENTS_2         61921
/*****************************************************/

/*****************************************************/
/* Адрексний простір вводу серійного номеру          */
/*****************************************************/
#define MA_SET_SERIAL_NUMBER                  61948
/*****************************************************/

/*****************************************************/
/* Адрексний простір внутрішнього користування       */
/*****************************************************/
#define MA_POSSIBILITY_USTUVANNJA             61967
#define MA_ADDRESS_FIRST_USTUVANNJA           61968
#define MA_ADDRESS_LAST_USTUVANNJA            (MA_ADDRESS_FIRST_USTUVANNJA  + NUMBER_ANALOG_CANALES - 1)
/*****************************************************/

///*****************************************************/
///* Адреса установки максимальної кількості ітерацій для розширеної логіки */
///*****************************************************/
//#define MA_NUMBER_ITERATION_EL                62000
///*****************************************************/

/*****************************************************/
/* Адреса подачі команди скинути настройки у мінімальні параметри */
/*****************************************************/
#define MA_DEFAULT_SETTINGS                   62100
#define CMD_WORD_SET_DEFAULT_SETTINGS         0x1111
/*****************************************************/

#define MA_CMD_RESET_RESURS_MIN_MAX           63002
#define MA_LSW_GLOBAL_RESURS_MIN              63003
#define MA_MSW_GLOBAL_RESURS_MIN              63004
#define MA_LSW_GLOBAL_RESURS_MAX              63005
#define MA_MSW_GLOBAL_RESURS_MAX              63006
#define MA_LSW_GLOBAL_RESURS                  63007
#define MA_MSW_GLOBAL_RESURS                  63008
#define MA_LSW_ADR_MEMORY_TO_WRITE            63009
#define MA_MSW_ADR_MEMORY_TO_WRITE            63010
#define MA_LSW_DATA_MEMORY_TO_WRITE           63011
#define MA_MSW_DATA_MEMORY_TO_WRITE           63012
#define MA_NB_REG_FROM_MEM_READ               63013
#define MA_LSW_ADR_MEMORY_TO_READ             63014
#define MA_MSW_ADR_MEMORY_TO_READ             63015

#define M_ADDRESS_FIRST_READ_DAMP_MEM         63016
#define NUMBER_REGISTER_IN_DUMP_MEMORY        128
#define M_ADDRESS_LAST_READ_DAMP_MEM          (M_ADDRESS_FIRST_READ_DAMP_MEM + NUMBER_REGISTER_IN_DUMP_MEMORY)

#define M_ADDRESS_FIRST_TMP_MEASURMENTS       63256
#define NUMBER_REGISTER_TMP_MEASURMENTS       ((NUMBER_ANALOG_CANALES)<<1)
#define M_ADDRESS_LAST_TMP_MEASURMENTS        (M_ADDRESS_FIRST_TMP_MEASURMENTS + NUMBER_REGISTER_TMP_MEASURMENTS)

#define MA_PART_RECEIVE_DIG_OSCILOGRAPH       63303
#define M_ADDRESS_FIRST_DIG_OSCILOGRAPH       63304
#define NUMBER_REGISTER_DIG_OSCILOGRAPH       16
#define M_ADDRESS_LAST_DIG_OSCILOGRAPH        (M_ADDRESS_FIRST_DIG_OSCILOGRAPH + NUMBER_REGISTER_DIG_OSCILOGRAPH)

#define MA_TEST_WATCHDOGS                     63472
#define CMD_TEST_EXTERNAL_WATCHDOG            0xCDEF
/*****************************************************/

#define SOURCE_OUTPUTS_RANG                   0
#define SOURCE_LEDS_RANG                      1
#define SOURCE_DF                             2
#define SOURCE_AR_RANG                        3
#define SOURCE_DR_RANG                        4
#define SOURCE_SET_DT                         5
#define SOURCE_D_AND_RANG                     6
#define SOURCE_D_OR_RANG                      7
#define SOURCE_D_XOR_RANG                     8
#define SOURCE_D_NOT_RANG                     9
#define SOURCE_ALARMS_RANG                    10

#endif
