/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */


  /********************************************/
  //Піни для LCD
  /********************************************/
  //LCD-R/W
#define LCD_RW                       GPIOB  
#define LCD_RW_PIN                   GPIO_Pin_11
#define RCC_AHB1Periph_GPIO_LCD_RW   RCC_AHB1Periph_GPIOB

  //LCD-RS
#define LCD_RS                       GPIOB  
#define LCD_RS_PIN                   GPIO_Pin_10
#define RCC_AHB1Periph_GPIO_LCD_RS   RCC_AHB1Periph_GPIOB

  //Підсвітка BL
#define LCD_BL                       GPIOD  
#define LCD_BL_PIN                   GPIO_Pin_6
#define RCC_AHB1Periph_GPIO_LCD_BL   RCC_AHB1Periph_GPIOD
  /********************************************/

  /********************************************/
  //Клавіатура
  /********************************************/
#ifdef KEYBOARD_VER_1

#define KEYBOARD                        GPIOC  
#define KEYBOARD_SW_1_PIN               GPIO_Pin_11
#define KEYBOARD_SW_2_PIN               GPIO_Pin_8
#define KEYBOARD_SW_3_PIN               GPIO_Pin_9
#define KEYBOARD_SW_4_PIN               GPIO_Pin_10
#define RCC_AHB1Periph_GPIO_KEYBOARD    RCC_AHB1Periph_GPIOC

#define KEYBOARD_SW_A                           GPIOB
#define KEYBOARD_SW_A_PIN                       GPIO_Pin_6
#define RCC_AHB1Periph_GPIO_KEYBOARD_SW_A       RCC_AHB1Periph_GPIOB

#define KEYBOARD_SW_B                           GPIOB
#define KEYBOARD_SW_B_PIN                       GPIO_Pin_7
#define RCC_AHB1Periph_GPIO_KEYBOARD_SW_B       RCC_AHB1Periph_GPIOB

#define KEYBOARD_SW_C                           GPIOG
#define KEYBOARD_SW_C_PIN                       GPIO_Pin_15
#define RCC_AHB1Periph_GPIO_KEYBOARD_SW_C       RCC_AHB1Periph_GPIOG

#else

#define KEYBOARD                        GPIOC  
#define KEYBOARD_SW_1_PIN               GPIO_Pin_7
#define KEYBOARD_SW_2_PIN               GPIO_Pin_8
#define KEYBOARD_SW_3_PIN               GPIO_Pin_9
#define KEYBOARD_SW_4_PIN               GPIO_Pin_6
#define RCC_AHB1Periph_GPIO_KEYBOARD    RCC_AHB1Periph_GPIOC

#define KEYBOARD_SW_A                           GPIOC
#define KEYBOARD_SW_A_PIN                       GPIO_Pin_10
#define RCC_AHB1Periph_GPIO_KEYBOARD_SW_A       RCC_AHB1Periph_GPIOC

#define KEYBOARD_SW_B                           GPIOC
#define KEYBOARD_SW_B_PIN                       GPIO_Pin_11
#define RCC_AHB1Periph_GPIO_KEYBOARD_SW_B       RCC_AHB1Periph_GPIOC

#define KEYBOARD_SW_C                           GPIOC
#define KEYBOARD_SW_C_PIN                       GPIO_Pin_12
#define RCC_AHB1Periph_GPIO_KEYBOARD_SW_C       RCC_AHB1Periph_GPIOC


#endif

  /********************************************/

  /********************************************/
  //Контроль наявності живлення
  /********************************************/
#define POWER_CTRL                      GPIOC  
#define POWER_CTRL_PIN                  GPIO_Pin_0
#define RCC_AHB1Periph_GPIO_POWER_CTRL  RCC_AHB1Periph_GPIOC
#define EXTI_PortSource_POWER           EXTI_PortSourceGPIOC
#define EXTI_PinSource_POWER            EXTI_PinSource0
#define EXTI_Line_POWER                 EXTI_Line0
#define EXITI_POWER_IRQn                EXTI0_IRQn
#define EXITI_POWER_IRQHandler          EXTI0_IRQHandler
  /********************************************/

  /********************************************/
  //Дозвіл роботи світлоіндикаторів
  /********************************************/
#define CON_L                       GPIOD  
#define CON_L_PIN                   GPIO_Pin_3
#define RCC_AHB1Periph_GPIO_CON_L   RCC_AHB1Periph_GPIOD
  /********************************************/

  /********************************************/
  //Дозвіл роботи виходів
  /********************************************/
#define CON_OUTPUTS                     GPIOG  
#define CON_1_OUTPUTS_PIN               GPIO_Pin_6
#define CON_2_OUTPUTS_PIN               GPIO_Pin_7
#define CON_3_OUTPUTS_PIN               GPIO_Pin_8
#define RCC_AHB1Periph_GPIO_CON_OUTPUTS RCC_AHB1Periph_GPIOG
  /********************************************/

  /********************************************/
  /* I2C*/
  /********************************************/
#define I2C                           I2C1
#define RCC_APB1Periph_I2C            RCC_APB1Periph_I2C1
#define I2C_DR_Address                ((uint32_t)0x40005410)
#define I2C_EV_IRQHandler             I2C1_EV_IRQHandler
#define I2C_EV_IRQn                   I2C1_EV_IRQn
#define I2C_ER_IRQHandler             I2C1_ER_IRQHandler
#define I2C_ER_IRQn                   I2C1_ER_IRQn

#define GPIO_AF_I2C                   GPIO_AF_I2C1

#define DMA_StreamI2C_Tx_IRQn         /*DMA1_Stream6_IRQn*/DMA1_Stream7_IRQn
#define DMA_StreamI2C_Tx_IRQHandler   /*DMA1_Stream6_IRQHandler*/DMA1_Stream7_IRQHandler
#define DMA_ChannelI2C_Tx             DMA_Channel_1
#define DMA_StreamI2C_Tx              /*DMA1_Stream6*/DMA1_Stream7
#define DMA_FLAG_TCI2C_Tx             /*DMA_FLAG_TCIF6*/DMA_FLAG_TCIF7
#define DMA_FLAG_HTI2C_Tx             /*DMA_FLAG_HTIF6*/DMA_FLAG_HTIF7
#define DMA_FLAG_TEII2C_Tx            /*DMA_FLAG_TEIF6*/DMA_FLAG_TEIF7
#define DMA_FLAG_DMEII2C_Tx           /*DMA_FLAG_DMEIF6*/DMA_FLAG_DMEIF7
#define DMA_FLAG_FEII2C_Tx            /*DMA_FLAG_FEIF6*/DMA_FLAG_FEIF7

#define DMA_StreamI2C_Rx_IRQn         DMA1_Stream0_IRQn
#define DMA_StreamI2C_Rx_IRQHandler   DMA1_Stream0_IRQHandler
#define DMA_ChannelI2C_Rx             DMA_Channel_1
#define DMA_StreamI2C_Rx              DMA1_Stream0
#define DMA_FLAG_TCI2C_Rx             DMA_FLAG_TCIF0
#define DMA_FLAG_HTI2C_Rx             DMA_FLAG_HTIF0
#define DMA_FLAG_TEII2C_Rx            DMA_FLAG_TEIF0
#define DMA_FLAG_DMEII2C_Rx           DMA_FLAG_DMEIF0
#define DMA_FLAG_FEII2C_Rx            DMA_FLAG_FEIF0

#define GPIO_I2C                      GPIOB
#define GPIO_I2C_SCL                  GPIO_Pin_8
#define GPIO_I2C_SCLSource            GPIO_PinSource8
#define GPIO_I2C_SDA                  GPIO_Pin_9
#define GPIO_I2C_SDASource            GPIO_PinSource9
#define RCC_AHB1Periph_GPIO_I2C      RCC_AHB1Periph_GPIOB
/********************************************/

  /********************************************/
  /* SPI для ADC*/
  /********************************************/
#define GPIO_SPI_ADC                GPIOB
#define RCC_AHB1Periph_GPIO_SPI_ADC RCC_AHB1Periph_GPIOB
#define GPIO_NSSPin_ADC             GPIO_Pin_12
#define GPIO_SCKPin_ADC             GPIO_Pin_13
#define GPIO_SCKPin_ADCSource       GPIO_PinSource13
#define GPIO_MISOPin_ADC            GPIO_Pin_14
#define GPIO_MISOPin_ADCSource       GPIO_PinSource14
#define GPIO_MOSIPin_ADC            GPIO_Pin_15
#define GPIO_MOSIPin_ADCSource      GPIO_PinSource15

#define GPIO_SELECT_ADC                 GPIOC
#define RCC_AHB1Periph_GPIO_SELECT_ADC  RCC_AHB1Periph_GPIOC
#define GPIO_SELECTPin_ADC              GPIO_Pin_1

#define SPI_ADC                   SPI2
#define RCC_APB1Periph_SPI_ADC    RCC_APB1Periph_SPI2
#define SPI_ADC_IRQHandler        SPI2_IRQHandler
#define SPI_ADC_IRQn              SPI2_IRQn

#define GPIO_AF_SPI_ADC           GPIO_AF_SPI2
  /********************************************/

  /********************************************/
  /* SPI для DATAFLASH*/
  /********************************************/
#define GPIO_SPI_DF                 GPIOA
#define RCC_AHB1Periph_GPIO_SPI_DF  RCC_AHB1Periph_GPIOA
#define SPI_DF_IRQHandler           SPI1_IRQHandler
#define SPI_DF_IRQn                 SPI1_IRQn
#define GPIO_NSSPin_DF              GPIO_Pin_4
#define GPIO_SCKPin_DF              GPIO_Pin_5
#define GPIO_SCKPin_DFSource        GPIO_PinSource5
#define GPIO_MISOPin_DF             GPIO_Pin_6
#define GPIO_MISOPin_DFSource       GPIO_PinSource6
#define GPIO_MOSIPin_DF             GPIO_Pin_7
#define GPIO_MOSIPin_DFSource       GPIO_PinSource7

#define GPIO_SPI_DF_TOGGLE          GPIOG
#define RCC_AHB1Periph_GPIO_SPI_DF_TOGGLE  RCC_AHB1Periph_GPIOG
#define GPIO_SPI_DF_TOGGLE_Pin      GPIO_Pin_13


#define SPI_DF                      SPI1
#define RCC_APB2Periph_SPI_DF       RCC_APB2Periph_SPI1
#define SPI_DF_DR_Address           ((uint32_t)0x4001300C)

#define GPIO_AF_SPI_DF              GPIO_AF_SPI1

#define DMA_StreamSPI_DF_Tx_IRQn         DMA2_Stream3_IRQn
#define DMA_StreamSPI_DF_Tx_IRQHandler   DMA2_Stream3_IRQHandler
#define DMA_ChannelSPI_DF_Tx             DMA_Channel_3
#define DMA_StreamSPI_DF_Tx              DMA2_Stream3
#define DMA_FLAG_TCSPI_DF_Tx             DMA_FLAG_TCIF3
#define DMA_FLAG_HTSPI_DF_Tx             DMA_FLAG_HTIF3
#define DMA_FLAG_TEISPI_DF_Tx            DMA_FLAG_TEIF3
#define DMA_FLAG_DMEISPI_DF_Tx           DMA_FLAG_DMEIF3
#define DMA_FLAG_FEISPI_DF_Tx            DMA_FLAG_FEIF3

#define DMA_StreamSPI_DF_Rx_IRQn         DMA2_Stream0_IRQn
#define DMA_StreamSPI_DF_Rx_IRQHandler   DMA2_Stream0_IRQHandler
#define DMA_ChannelSPI_DF_Rx             DMA_Channel_3
#define DMA_StreamSPI_DF_Rx              DMA2_Stream0
#define DMA_FLAG_TCSPI_DF_Rx             DMA_FLAG_TCIF0
#define DMA_FLAG_HTSPI_DF_Rx             DMA_FLAG_HTIF0
#define DMA_FLAG_TEISPI_DF_Rx            DMA_FLAG_TEIF0
#define DMA_FLAG_DMEISPI_DF_Rx           DMA_FLAG_DMEIF0
#define DMA_FLAG_FEISPI_DF_Rx            DMA_FLAG_FEIF0
  /********************************************/

  /********************************************/
  /* USART для RS-485*/
  /********************************************/
#define GPIO_USART_RS485                  GPIOA
#define RCC_AHB1Periph_GPIO_USART_RS485   RCC_AHB1Periph_GPIOA

#define GPIO_TxPin_RS485                  /*GPIO_Pin_9*/GPIO_Pin_2
#define GPIO_TxPin_RS485Source            /*GPIO_PinSource9*/GPIO_PinSource2
#define GPIO_RxPin_RS485                  /*GPIO_Pin_10*/GPIO_Pin_3
#define GPIO_RxPin_RS485Source            /*GPIO_PinSource10*/GPIO_PinSource3

  //Сигнал 485DE - PA.8
#define GPIO_485DE                        GPIOA
#define RCC_AHB1Periph_GPIO_485DE         RCC_AHB1Periph_GPIOA
#define GPIO_PIN_485DE                    GPIO_Pin_8

#define USART_RS485                       /*USART1*/USART2
#define RCC_USARTRS_485                   /*RCC_APB2Periph_USART1*/RCC_APB1Periph_USART2
#define USARTRS485_DR_Base                /*((uint32_t)0x40011004)*/((uint32_t)0x40004404)

#define GPIO_AF_USART_RS_485              /*GPIO_AF_USART1*/GPIO_AF_USART2

#define USARTRS485_IRQn                   /*USART1_IRQn*/USART2_IRQn
#define USARTRS485_IRQHandler             /*USART1_IRQHandler*/USART2_IRQHandler

#define DMA_StreamRS485_Tx_IRQn           /*DMA2_Stream7_IRQn*/DMA1_Stream6_IRQn
#define DMA_StreamRS485_Tx_IRQHandler     /*DMA2_Stream7_IRQHandler*/DMA1_Stream6_IRQHandler
#define DMA_ChannelRS485_Tx               DMA_Channel_4
#define DMA_StreamRS485_Tx                /*DMA2_Stream7*/DMA1_Stream6
#define DMA_FLAG_TCRS485_Tx               /*DMA_FLAG_TCIF7*/DMA_FLAG_TCIF6
#define DMA_FLAG_HTRS485_Tx               /*DMA_FLAG_HTIF7*/DMA_FLAG_HTIF6
#define DMA_FLAG_TEIRS485_Tx              /*DMA_FLAG_TEIF7*/DMA_FLAG_TEIF6
#define DMA_FLAG_DMEIRS485_Tx             /*DMA_FLAG_DMEIF7*/DMA_FLAG_DMEIF6
#define DMA_FLAG_FEIRS485_Tx              /*DMA_FLAG_FEIF7*/DMA_FLAG_FEIF6

#define DMA_ChannelRS485_Rx               DMA_Channel_4
#define DMA_StreamRS485_Rx                /*DMA2_Stream2*/DMA1_Stream5
#define DMA_FLAG_TCRS485_Rx               /*DMA_FLAG_TCIF2*/DMA_FLAG_TCIF5
#define DMA_FLAG_HTRS485_Rx               /*DMA_FLAG_HTIF2*/DMA_FLAG_HTIF5
#define DMA_FLAG_TEIRS485_Rx              /*DMA_FLAG_TEIF2*/DMA_FLAG_TEIF5
#define DMA_FLAG_DMEIRS485_Rx             /*DMA_FLAG_DMEIF2*/DMA_FLAG_DMEIF5
#define DMA_FLAG_FEIRS485_Rx              /*DMA_FLAG_FEIF2*/DMA_FLAG_FEIF5
  /********************************************/

  /********************************************/
  /* Зовнішній Watchdog*/
  /********************************************/
#define GPIO_EXTERNAL_WATCHDOG                  GPIOC  
#define GPIO_PIN_EXTERNAL_WATCHDOG              GPIO_Pin_13
#define RCC_AHB1Periph_GPIO_EXTERNAL_WATCHDOG   RCC_AHB1Periph_GPIOC

  /********************************************/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */
