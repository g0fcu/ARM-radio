#ifndef PERIPHS_H
  #define PERIPHS_H

//#include "stm32f7xx_hal_adc.h"  //changed to F7 HAL- SHK
//#include "stm32f7xx_hal_dac.h" //changed to F7 HAL- SHK
//#include "stm32f7xx_hal_dma.h" //changed to F7 HAL- SHK
//#include "stm32f7xx_hal_exti.h"
//#include "stm32f7xx_hal_gpio.h" //changed to F7 HAL- SHK
//#include "stm32f7xx_hal_rcc.h" //changed to F7 HAL- SHK

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);

#endif
