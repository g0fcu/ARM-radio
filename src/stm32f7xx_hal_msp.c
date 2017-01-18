/**
  ******************************************************************************
  * @file    stm32f7xx_hal_msp_template.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    25-June-2015
  * @brief   HAL MSP module.
  *          This file template is located in the HAL folder and should be copied 
  *          to the user folder.
  *         
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    This file is generated automatically by STM32CubeMX and eventually modified 
    by the user

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stm32f7xx/stm32f7xx_hal.h>
#include <main.h>
float32_t SamplingRate, AudioRate;
/** @addtogroup STM32F7xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_MSP HAL MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions HAL MSP Private Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */ 

}

/**
  * @brief  DeInitializes the Global MSP.  
  * @retval None
  */
void HAL_MspDeInit(void)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */
}

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();

  /* Select SysClk as source of USART1 clocks */
  RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

  /* Enable USARTx clock */
  USARTx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

}

/**
  * @brief  Initializes the PPP MSP.
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */ 
    /*Enable GPIO clock ****************************************/
    ADCx_CHANNEL_GPIO_CLK_ENABLE();
    /* ADCx & ADCy Periph clock enable */
    ADCx_CLK_ENABLE();
    ADCy_CLK_ENABLE();
    ADCz_CLK_ENABLE();
    /* Enable DMA2 clock */
    DMAADCx_CLK_ENABLE();
    // Configure ADC Channel as analog input
    GPIO_InitStruct.Pin = ADCx_CHANNEL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADCx_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    // configure the DMA2 Stream0 channel0
    hdma_adc1.Instance = ADCx_DMA_STREAM;
    hdma_adc1.Init.Channel  = ADCx_DMA_CHANNEL;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;

    if (HAL_DMA_DeInit(&hdma_adc1) != HAL_OK)
          {
           Error_Handler();
          }
       if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
          {
       	Error_Handler();
          }

	__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc1);
}

/**
  * @brief  DeInitializes the PPP MSP.  
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually  
            modified by the user
   */

	 /*##-1- Reset peripherals ##################################################*/
	 ADCx_FORCE_RESET();
	 ADCx_RELEASE_RESET();

	 /*##-2- Disable peripherals and GPIO Clocks ################################*/
	 /* De-initialize the ADC Channel GPIO pin */
	 HAL_GPIO_DeInit(ADCx_CHANNEL_GPIO_PORT, ADCx_CHANNEL_PIN);
	 /*##-3- Disable the DMA Streams ############################################*/
	 /* De-Initialize the DMA Stream associated to transmission process */
	 HAL_DMA_DeInit(&hdma_adc1);

	 /*##-4- Disable the NVIC for DMA ###########################################*/
	 HAL_NVIC_DisableIRQ(ADCx_DMA_IRQn);
}

void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{

     /*##-1- Enable peripherals and GPIO Clocks #################################*/
     /* Enable GPIO clock ****************************************/
     DACx_CHANNEL_GPIO_CLK_ENABLE();
     /* DAC Periph clock enable */
     DACx_CLK_ENABLE();
     /* DMA1 clock enable */
     DMAx_CLK_ENABLE();
     /*##-2- Configure peripheral GPIO ##########################################*/
     /* DAC Channel1 GPIO pin configuration */
     GPIO_InitStruct.Pin = DACx_CHANNEL_PIN;
     GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
     GPIO_InitStruct.Pull = GPIO_NOPULL;
     HAL_GPIO_Init(DACx_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    /*##-3- Configure the DMA ##########################################*/
    /* Set the parameters to be configured for DACx_DMA_STREAM */
    hdma_dac1.Instance = DACx_DMA_INSTANCE;
    hdma_dac1.Init.Channel  = DACx_DMA_CHANNEL;
    hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dac1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_dac1.Init.Mode = DMA_CIRCULAR;
    hdma_dac1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_dac1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_dac1.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_dac1.Init.PeriphBurst = DMA_PBURST_SINGLE;

    if (HAL_DMA_Init(&hdma_dac1) != HAL_OK)
	   {
	   Error_Handler();
	   }

    /* Associate the initialized DMA handle to the DAC handle */
    __HAL_LINKDMA(hdac, DMA_Handle1, hdma_dac1);
}

/**
  * @brief  DeInitializes the DAC MSP.
  * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @retval None
  */
void HAL_DAC_MspDeInit(DAC_HandleTypeDef *hdac)
{
  /*##-1- Reset peripherals ##################################################*/
  DACx_FORCE_RESET();
  DACx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* De-initialize the DAC Channel1 GPIO pin */
  HAL_GPIO_DeInit(DACx_CHANNEL_GPIO_PORT, DACx_CHANNEL_PIN);

  /*##-3- Disable the DMA Stream ############################################*/
  /* De-Initialize the DMA Stream associate to DAC_Channel1 */
  HAL_DMA_DeInit(hdac->DMA_Handle1);

  /*##-4- Disable the NVIC for DMA ###########################################*/
  HAL_NVIC_DisableIRQ(DACx_DMA_IRQn);
}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim) //rotary - rotary encoder code
{
 GPIO_InitTypeDef GPIO_InitStruct;

 if (htim->Instance == TIM3) {

 __TIM3_CLK_ENABLE();

 __GPIOB_CLK_ENABLE();

 GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
 GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
 GPIO_InitStruct.Pull = GPIO_PULLUP;
 GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
 GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

 HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);

 HAL_NVIC_EnableIRQ(TIM3_IRQn);
 }
}
/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
//----------------------------------------------------------------------------
// Configure here the parameters for Timer6, used to trigger the output DAC
void TIM6_Config(void)
{
     TIM_MasterConfigTypeDef sMasterConfig;
	  /* --------------------------------------------------------
	    TIM6 input clock (TIM6CLK) is set to 2 * APB1 clock (PCLK1),
	    since APB1 prescaler is different from 1.
	      TIM6CLK = 2 * PCLK1
	      TIM6CLK = HCLK / 2 = SystemCoreClock /2

	    TIM6 Update event occurs each TIM6CLK/3584 which means :
	  	   APB1 = HCLK/4, i.e. 200 MHz / 4 = 50 MHz
	  	   TIM6CLK = 2 * APB1 = 100 MHz
	       TIM6 update event = 100e6 / 3584 = 27901.786 Hz,
	                                          which is the output sampling frequency
	  ----------------------------------------------------------- */
     // valid only for ADC_Prescaler_Div4
    	  	 // and ADC_SampleTime_3Cycles
    	  	 // and ADC_Resolution_12b and delay = 14
    	  	 //SamplingRate = ((SystemCoreClock / 2) / 4) / 14.f;
    	  	 SamplingRate = ((SystemCoreClock / 2) / 4) / 20.f;  // 2/4/14
    	  	 AudioRate = SamplingRate / 16.f / 4.f;  // 16/4
	  /*##-1- Configure the TIM peripheral #######################################*/
	  /* Time base configuration */
	  htim.Instance = TIM6;

  // reload value = 3584 :  100MHz / 3584 = 27901.786 Hz
  // which is the sampling freq. of the DAC, and also 1/4
  // of the freq. after the decimation...  1.7857143e6 / 16 = 111607.143 Hz
  // and 111607.143 / 4 = 27901.786 Hz (AudioRate)

	  htim.Init.Period            = (uint32_t) ((SystemCoreClock / 2) / AudioRate) - 1;
	  htim.Init.Prescaler         = 0;
	  htim.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	  htim.Init.CounterMode       = TIM_COUNTERMODE_UP;
	  htim.Init.RepetitionCounter = 0;

   if (HAL_TIM_Base_Init(&htim) != HAL_OK)
	  {
	  Error_Handler();
	  }

  /* TIM6 TRGO selection */
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
    	{
    	Error_Handler();
    	}
    /*##-2- Enable TIM peripheral counter ######################################*/
    HAL_TIM_Base_Start(&htim);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /* TIM6 Periph clock enable */
  __HAL_RCC_TIM6_CLK_ENABLE();

}

/**
  * @brief TIM MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{

  /*##-1- Reset peripherals ##################################################*/
  __HAL_RCC_TIM6_FORCE_RESET();
  __HAL_RCC_TIM6_RELEASE_RESET();
}


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
