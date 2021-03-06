/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co. KG                 *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 2015  SEGGER Microcontroller GmbH & Co. KG               *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* * This software may in its unmodified form be freely redistributed *
*   in source form.                                                  *
* * The source code may be modified, provided the source code        *
*   retains the above copyright notice, this list of conditions and  *
*   the following disclaimer.                                        *
* * Modified versions of this software in source or linkable form    *
*   may not be distributed without prior consent of SEGGER.          *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND     *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,  *
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A        *
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL               *
* SEGGER Microcontroller BE LIABLE FOR ANY DIRECT, INDIRECT,         *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS    *
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS            *
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,       *
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING          *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: V2.24                                    *
*                                                                    *
**********************************************************************
-------------------------- END-OF-HEADER -----------------------------

File        : SEGGER_SYSVIEW_Config_NoOS.c
Purpose     : Sample setup configuration of SystemView without an OS.
*/
#include "SEGGER_SYSVIEW.h"

// SystemcoreClock can be used in most CMSIS compatible projects.
// In non-CMSIS projects define SYSVIEW_CPU_FREQ.
extern unsigned int SystemCoreClock;

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/
// The application name to be displayed in SystemViewer
#define SYSVIEW_APP_NAME        "MRZS-05L-12.1"

// The target device name
#define SYSVIEW_DEVICE_NAME     "Cortex-M3"

// Frequency of the timestamp. Must match SEGGER_SYSVIEW_Conf.h
#define SYSVIEW_TIMESTAMP_FREQ  (SystemCoreClock >> 4)

// System Frequency. SystemcoreClock is used in most CMSIS compatible projects.
#define SYSVIEW_CPU_FREQ        (SystemCoreClock)

// The lowest RAM address used for IDs (pointers)
#define SYSVIEW_RAM_BASE        (0x20000000)

/********************************************************************* 
*
*       _cbSendSystemDesc()
*
*  Function description
*    Sends SystemView description strings.
*/
static void _cbSendSystemDesc(void) {
  SEGGER_SYSVIEW_SendSysDesc("N="SYSVIEW_APP_NAME",D="SYSVIEW_DEVICE_NAME);
  SEGGER_SYSVIEW_SendSysDesc("I#15=SysTick");
  
  SEGGER_SYSVIEW_SendSysDesc("I#22=EXITI_POWER");
  SEGGER_SYSVIEW_SendSysDesc("I#27=DMA_I2C_Rx");
  SEGGER_SYSVIEW_SendSysDesc("I#33=DMA_USART_Tx");
  SEGGER_SYSVIEW_SendSysDesc("I#44=Protect.");
  SEGGER_SYSVIEW_SendSysDesc("I#46=IF_KB_D");
  SEGGER_SYSVIEW_SendSysDesc("I#47=I2C_EV");
  SEGGER_SYSVIEW_SendSysDesc("I#48=I2C_ER");
  SEGGER_SYSVIEW_SendSysDesc("I#51=SPI_DF");
  SEGGER_SYSVIEW_SendSysDesc("I#52=SPI_Meas.");
  SEGGER_SYSVIEW_SendSysDesc("I#54=USART_RS485");
  SEGGER_SYSVIEW_SendSysDesc("I#63=DMA_I2C_Tx");
  SEGGER_SYSVIEW_SendSysDesc("I#66=TIM_Meas.");
  SEGGER_SYSVIEW_SendSysDesc("I#72=DMA_DF_Rx");
  SEGGER_SYSVIEW_SendSysDesc("I#83=USB_OTG_FS");
}

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
void SEGGER_SYSVIEW_Conf(void) {
  SEGGER_SYSVIEW_Init(SYSVIEW_TIMESTAMP_FREQ, SYSVIEW_CPU_FREQ, 
                      0, _cbSendSystemDesc);
  SEGGER_SYSVIEW_SetRAMBase(SYSVIEW_RAM_BASE);
}

/*************************** End of file ****************************/
