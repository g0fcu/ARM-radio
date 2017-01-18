/*******************************************************************************

                   main.h module of the program ARM_Radio
						                          
						                          Copyright 2015 by Alberto I2PHD, June 2015
						                                      
    This file is part of ARM_Radio.

    ARM_Radio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ARM_Radio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARM_Radio.  It is contained in the file Copying.txt in the
    same ZIP file where this file was extracted from.				                                      
						                                      
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
// Includes ------------------------------------------------------------------
// some of these include files have ad-hoc modifications for this project
#include "system_stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "core_cm7.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_adc.h"
#include "stm32f7xx_hal_adc_ex.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_dac.h"
#include "stm32f7xx_hal_rcc_ex.h"
#include "stm32f7xx_hal_cortex.h"
#include "stm32f7xx_hal_flash.h"
#include "stm32f7xx_hal_dma.h"
#include "stm32f7xx_hal_dma_ex.h"
#include "stm32f7xx_hal_ltdc.h"
#include "stm32f7xx_hal_sdram.h"
#include "stm32f7xx_hal_pwr.h"
#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_tim_ex.h"
#include "stm32f746xx.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144.h"
#include <WM.h>
#include <BUTTON.h>
#include <arm_math.h>
#include <arm_const_structs.h>
#include "SDR_math.h"
#include "Board_LED.h"
#include "Board_Buttons.h"
#include "GUI.h"
#include "DIALOG.h"
#include "Driver_I2C.h"

#define true  1
#define false 0 
#define __FPU_PRESENT 1

extern TIM_HandleTypeDef 	 htim;
extern ADC_HandleTypeDef    AdcHandle1;
extern ADC_HandleTypeDef    AdcHandle2;
extern ADC_HandleTypeDef    AdcHandle3;
extern DMA_HandleTypeDef    hdma_dac1;
extern DAC_HandleTypeDef    DacHandle;
extern DMA_HandleTypeDef    hdma_adc1;
extern GPIO_InitTypeDef  	 GPIO_InitStruct;
extern GRAPH_DATA_Handle aGraph_Data;
extern TIM_Encoder_InitTypeDef encoder; //rotary
extern TIM_HandleTypeDef timer;

/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

typedef uint8_t    u8;
typedef enum {AM=0, LSB=1, USB=2, CW=3} Mode;
typedef enum {Fast, Slow}   Agctype;
typedef enum {Narrow, Wide} Bwidth;
typedef enum {x1=0, x10=1, x100=2, x500=3, x1000=4} Scale;

typedef struct 
        {
          char   name[16];
          float  freq;
          Mode   mode;
          Bwidth bw;
        } Presets;

#define MAXPRESETS 13

#define myPI         3.14159265358979f
#define TWOPI        (2.f*myPI)
#define CWPITCH      650.f
//#define SAMPLINGRATE 1785714.286f //clock speed 200MHz
//#define SAMPLINGRATE 1687500.0f //clock speed 216MHz 16 cycles delay
//#define SAMPLINGRATE 1928571.429f //clock speed 216MHz 14 cycles delay
#define SAMPLINGRATE 1250000.000f //clock speed 216MHz 14 cycles delay
//#define SAMPLINGRATE 3000000.000f //clock speed 216MHz 9 cycles delay
//#define SAMPLINGRATE 2700000.000f //clock speed 216MHz 10 cycles delay
#define RATEOUT      (SAMPLINGRATE/64)
#define BSIZE        (uint32_t)512
#define FFTLEN       BSIZE*2
#define NUMFIRCOEFS  64
#define DIRECTFFT    0
#define INVERSEFFT   1
#define NOREVERSE    1
#define PRESET_INIT  1


#define hSTATION       (GUI_ID_USER + 0x01)
#define hVOL           (GUI_ID_USER + 0x0B)
#define hFRADIO        (GUI_ID_USER + 0x02)
#define hFPLUS         (GUI_ID_USER + 0x06)
#define hFMINUS        (GUI_ID_USER + 0x06)
#define hMUTE          (GUI_ID_USER + 0x03)
#define hMODE          (GUI_ID_USER + 0x04)
#define hBW            (GUI_ID_USER + 0x05)
#define hAGC           (GUI_ID_USER + 0x08)
#define hFREQ          (GUI_ID_USER + 0x0A)
#define hFREQ1         (GUI_ID_USER + 0x09)
#define hGRAPH         (GUI_ID_USER + 0x0C)
#define hSPECTOGRAM    (GUI_ID_USER + 0x0D)
#define hSCALE         (GUI_ID_USER + 0x0E)
 
#define AIRCR_VECTKEY_MASK ((uint32_t)0x05FA0000)
#define PriorityGroup_4    ((uint32_t)0x300) // 4 bits for pre-emption priority
                                             // 0 bits for subpriority

/* Definition for ADCx clock resources */
#define ADCx                            ADC1
#define ADCy                            ADC2
#define ADCz                            ADC3

#define ADC_CDR_ADDRESS    ((uint32_t)0x40012308)

#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()
#define ADCy_CLK_ENABLE()               __HAL_RCC_ADC2_CLK_ENABLE()
#define ADCz_CLK_ENABLE()               __HAL_RCC_ADC3_CLK_ENABLE()

#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                GPIO_PIN_3
#define ADCx_CHANNEL_GPIO_PORT          GPIOA

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                    ADC_CHANNEL_3 //see STM32F745 datasheet pp52 onwards for pin to channel mappings

/* Definition for ADCx's DMA */
#define ADCx_DMA_CHANNEL                DMA_CHANNEL_0
#define ADCx_DMA_STREAM                 DMA2_Stream0
#define DMAADCx_CLK_ENABLE()            __HAL_RCC_DMA2_CLK_ENABLE()

/* Definition for ADCx's NVIC */
#define ADCx_DMA_IRQn                   DMA2_Stream0_IRQn
#define ADCx_DMA_IRQHandler             DMA2_Stream0_IRQHandler




#ifdef   INMAIN
  #include "FIRcoefs.h"
#endif


#ifdef  INMAIN
 u8 Idx;
#else
 extern u8 Idx;
#endif

#include "Globals.h"

#ifndef TSC_I2C_PORT
 #define TSC_I2C_PORT    3              // I2C Port number
#endif

/* Definition for TIMx clock resources */
#define TIMx                           TIM6
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM6_CLK_ENABLE()
#define TIMx_CHANNEL_PIN                GPIO_PIN_11
#define TIMx_CHANNEL_GPIO_PORT          GPIOF
/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM6_IRQn
#define TIMx_IRQHandler                TIM6_IRQHandler

//#define DAC_DHR12L1_ADDRESS  0x4000740C
#define DAC_DHR12R1_ADDRESS  0x40007408
/* Definition for DACx clock resources */
#define DACx                            DAC
#define DACx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define DMAx_CLK_ENABLE()               __HAL_RCC_DMA1_CLK_ENABLE()

#define DACx_CLK_ENABLE()               __HAL_RCC_DAC_CLK_ENABLE()
#define DACx_FORCE_RESET()              __HAL_RCC_DAC_FORCE_RESET()
#define DACx_RELEASE_RESET()            __HAL_RCC_DAC_RELEASE_RESET()

/* Definition for DACx Channel Pin */
#define DACx_CHANNEL_PIN                GPIO_PIN_4
#define DACx_CHANNEL_GPIO_PORT          GPIOA

/* Definition for DACx's Channel */
#define DACx_DMA_CHANNEL                DMA_CHANNEL_7
#define DACx_CHANNEL                    DAC_CHANNEL_1

/* Definition for DACx's DMA_STREAM */
#define DACx_DMA_INSTANCE               DMA1_Stream5

/* Definition for DACx's NVIC */
#define DACx_DMA_IRQn                   DMA1_Stream5_IRQn
#define DACx_DMA_IRQHandler             DMA1_Stream5_IRQHandler

#define TSC_I2C_ADDR    0x41            // 7-bit I2C address

/* I2C Driver */
#define _I2C_Driver_(n)  Driver_I2C##n
#define  I2C_Driver_(n) _I2C_Driver_(n)
extern ARM_DRIVER_I2C    I2C_Driver_(TSC_I2C_PORT);
#define ptrI2C           (&I2C_Driver_(TSC_I2C_PORT))

extern uint32_t os_time;
extern volatile GUI_TIMER_TIME OS_TimeMS;

#define LCD_CS_PIN      3
#define LCD_RS_PIN      4
#define LCD_WR_PIN      5
#define LCD_RD_PIN      6
#define LCD_RST_PIN     2

#define ENCODER_PIN	GPIO_PIN_0 //rotary

extern int opt;


#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3



extern void SystemClock_Config(void);
extern void Error_Handler(void);
extern void SysTick_Handler(void);
extern void ADC_DMA_CallBack(void);

extern uint32_t bouncing(void);
extern void Load_Presets(void);
extern void Tune_Preset(WM_HWIN ptr, u8 Idx);
extern void SetMode(WM_HWIN ptr, Mode newmode);
extern void SetBW(WM_HWIN ptr, Bwidth newbw);
extern void SetAGC(WM_HWIN ptr, Agctype newagc);
extern void ChangeColor(WM_HWIN ptr, int handle, int color);
extern void SetFstep(int idx);
extern void FplusClicked(void);
extern void FminusClicked(void);
extern WM_HWIN CreateSDR_MainForm(void);
extern int32_t Touch_Initialize(void);
extern void Set_NVIC_PriorityGroupConfig(uint32_t PriorityGroup);

extern void SDR_InitDAC(void);
extern void SDR_InitADC(void);

#endif /* __MAIN_H */
