#ifndef __CONST_MESUREMENT__
#define __CONST_MESUREMENT__

#define USTUVANNJA_VAGA 12
#define DEFAULT_USTUVANNJA_VALUE ((1<<USTUVANNJA_VAGA) - 1)

#define MEASUREMENT_TIM_FREQUENCY       60000000 //МГц

#define MAIN_FREQUENCY  50      //Гц

#define NUMBER_ADCs                     1
#define NUMBER_CANALs_ADC               16
#define NUMBER_INPUTs_ADCs              (NUMBER_ADCs*NUMBER_CANALs_ADC)

#define VAGA_NUMBER_POINT                5
#define NUMBER_POINT                     (1 << VAGA_NUMBER_POINT)

#define NUMBER_PERIOD_TRANSMIT           10

/*
Коефіцієнт, який переводить число з АЦП у мА
          K*2500
Koef = ------------
        R*1*0xFFF
де:
K - коефіцієнт трансформації і він рівний 500 для 3I0, або 2500 для фазних струмів
2500 - максимальне значення напруги у мілівольтах, яке може оцифрувати АЦП (у нас це є 2,5 В = 2500 мВ)
R - резистор, який перетворює трансформований струм у напругу. Зараз стоїть 12,7 Ом
1 - після перетворення струму в напругу як мінімум раз сигнвал проходить через підсилювач на операційному підсилювачі з коефіцієнтом підсилення "1"
0xFFF - максимальне число, яке може видати АЦП

Koef = 120,17728553161624027765760049225 для фазних струмів (7691/64 = 120,171875) 

Множення на ці коефіцієнти переводять одиниці АЦП у мА

Але коли ми проводимо розрахунки з допомогою перетворення Фур'є, то результатом є амплітуда 1-ої  агмоніки (або інших гармонік. якщо розрахунок би йшов по них)
Тому крім цього коефіцієнта треба ще поділити на корінб з двох.
для простоти зробимо узагальнений коефіцієнт, що є результатом Koef_1 = Koef/sqrt(2)

Koef_1 = 84,978173543997808495193432804655 для фазних струмів (5439/64 = 84,984375)
*/

#define MNOGNYK_I                     7691           
#define VAGA_DILENNJA_I               6
#define MNOGNYK_I_DIJUCHE             5439          
#define VAGA_DILENNJA_I_DIJUCHE       6
#define MNOGNYK_I_DIJUCHE_FLOAT       84.984375f

/*
Коефіцієнт, який переводить число з АЦП у мB
          Ku*2500*R1
Koef = --------------
        R2*1*0xFFF
де:
Ku - коефіцієнт трансформації і він рівний 1
2500 - максимальне значення напруги у мілівольтах, яке може оцифрувати АЦП (у нас це є 2,5 В = 2500 мВ)
R1 -  резистор, який визначає струм у первинній обмотці трансвформатора струму. Зараз стоїть 86.5(75) кОм
R2 - резистор, який перетворює трансформований струм у напругу. Зараз стоїть 499 Ом
1 - після перетворення струму в напругу як мінімум раз сигнвал проходить через підсилювач на операційному підсилювачі з коефіцієнтом підсилення "1"
0xFFF - максимальне число, яке може видати АЦП

Koef = 105.82826214088739138839339240141 (6773/64 = 105.828125)

Множення на ці коефіцієнти переводять одиниці АЦП у мВ

Але коли ми проводимо розрахунки з допомогою перетворення Фур'є, то результатом є амплітуда 1-ої  агмоніки (або інших гармонік. якщо розрахунок би йшов по них)
Тому крім цього коефіцієнта треба ще поділити на корінь з двох.
для простоти зробимо узагальнений коефіцієнт, що є результатом Koef_1 = Koef/sqrt(2)

Koef_1 = 74.831881801009052122160116719483 (4790/64 = 74.84375)
*/
#define MNOGNYK_U                     6773           
#define VAGA_DILENNJA_U               6
#define MNOGNYK_U_DIJUCHE             4790           
#define VAGA_DILENNJA_U_DIJUCHE       6
#define MNOGNYK_U_DIJUCHE_FLOAT       74.831881801009052122160116719483f


#define GND_NORMAL_VALUE                0x0
#define VREF_NORMAL_VALUE               0x800
#define VDD_NORMAL_VALUE                0xb00

//Канали
#define C_GND_ADC_1             0
#define C_I1_1                  1
#define C_I1_16                 2
#define C_I2_1                  3
#define C_I2_16                 4
#define C_I3_1                  5
#define C_I3_16                 6
#define C_U_1                   7
#define C_U_16                  8
#define C_U_256                 9
#define C_GND_ADC_2             10
#define C_GND_ADC_3             11
#define C_GND_ADC_4             12
#define C_GND_ADC_5             13
#define C_VREF_ADC              14
#define C_VDD_ADC               15

#define READ_AIN   (                            \
                    (1 << C_I1_1   ) |          \
                    (1 << C_I1_16  ) |          \
                    (1 << C_I2_1   ) |          \
                    (1 << C_I2_16  ) |          \
                    (1 << C_I3_1   ) |          \
                    (1 << C_I3_16  ) |          \
                    (1 << C_U_1    ) |          \
                    (1 << C_U_16   )            \
                   )

#define READ_DATA_VAL  (            \
                         READ_AIN   \
                       )

#define READ_TEST_VAL  (                                 \
                        (1 << C_GND_ADC_1)             | \
                        (1 << C_GND_ADC_2)             | \
                        (1 << C_GND_ADC_3)             | \
                        (1 << C_GND_ADC_4)             | \
                        (1 << C_GND_ADC_5)             | \
                        (1 << C_VREF_ADC )             | \
                        (1 << C_VDD_ADC  )               \
                       )

#define DATA_VAL_READ_BIT         0
#define DATA_VAL_READ             (1 << DATA_VAL_READ_BIT)
#define TEST_VAL_READ_BIT         1
#define TEST_VAL_READ             (1 << TEST_VAL_READ_BIT)

#define NUMBER_GND_ADC          5

#define I_I1          0
#define I_I2          1
#define I_I3          2
#define I_I4          3
#define I_U           4

#define IM_I1         0
#define IM_I2         1
#define IM_I3         2
#define IM_I4         3
#define IM_U          4

#endif
