/**
  ******************************************************************************
  * @file    Project/STM32F2xx_StdPeriph_Template/stm32f2xx_it.h 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F2xx_IT_H
#define __STM32F2xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
void I2C_EV_IRQHandler(void);
void I2C_ER_IRQHandler(void);
void DMA_StreamI2C_Tx_IRQHandler(void);
void DMA_StreamI2C_Rx_IRQHandler(void);
void SPI_ADC_IRQHandler(void);
void DMA_StreamSPI_DF_Rx_IRQHandler(void);
void SPI_DF_IRQHandler(void);
void USARTRS485_IRQHandler(void);
void DMA_StreamRS485_Tx_IRQHandler(void);
void EXITI_POWER_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F2xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
