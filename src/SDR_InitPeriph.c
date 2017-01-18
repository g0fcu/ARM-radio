/*******************************************************************************

                   SDR_InitPeriph.c module of the program ARM_Radio
						                          
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

// In this module all the components of the ARM chip that are used by this application
// are initialized

#include "main.h"
#include "periphs.h"
#include "stm32f7xx_nucleo_144.h"


//-----------------------------------------------------------------------------
/**
  *         System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 200000000
  *            HCLK(Hz)                       = 200000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 400
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  */

// Init ADC1/2/3 in interleaved mode
void SDR_InitADC(void)
{
    uint16_t bufsz;

    ADC_ChannelConfTypeDef     	sConfigAdc;
    ADC_MultiModeTypeDef       	AdcMM;

    bufsz = BSIZE / 2;

    /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle1.Instance                   = ADCx;
    AdcHandle1.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
    AdcHandle1.Init.Resolution            = ADC_RESOLUTION_12B;
    AdcHandle1.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    AdcHandle1.Init.ContinuousConvMode    = ENABLE;                        /* Continuous mode disabled to have only 1 conversion at each conversion trig */
    AdcHandle1.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    AdcHandle1.Init.NbrOfDiscConversion   = 0;
    AdcHandle1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;        /* was RISING, Conversion start trigged at each external event */
    AdcHandle1.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;  // was ADC_EXTERNALTRIGCONV_T1_CC1
    AdcHandle1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    AdcHandle1.Init.NbrOfConversion       = 1;
    AdcHandle1.Init.DMAContinuousRequests = ENABLE;
    AdcHandle1.Init.EOCSelection          = DISABLE;
   /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle2.Instance                   = ADCy;
    AdcHandle2.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
    AdcHandle2.Init.Resolution            = ADC_RESOLUTION_12B;
    AdcHandle2.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    AdcHandle2.Init.ContinuousConvMode    = DISABLE;                        /* Continuous mode disabled to have only 1 conversion at each conversion trig */
    AdcHandle2.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    AdcHandle2.Init.NbrOfDiscConversion   = 0;
    AdcHandle2.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;        /* was RISING, Conversion start trigged at each external event */
    AdcHandle2.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
    AdcHandle2.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    AdcHandle2.Init.NbrOfConversion       = 1;
    AdcHandle2.Init.DMAContinuousRequests = DISABLE;
    AdcHandle2.Init.EOCSelection          = DISABLE;
    /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle3.Instance                   = ADCz;
    AdcHandle3.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
    AdcHandle3.Init.Resolution            = ADC_RESOLUTION_12B;
    AdcHandle3.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    AdcHandle3.Init.ContinuousConvMode    = DISABLE;                        /* Continuous mode disabled to have only 1 conversion at each conversion trig */
    AdcHandle3.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    AdcHandle3.Init.NbrOfDiscConversion   = 0;
    AdcHandle3.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;        /* was RISING, Conversion start trigged at each external event */
    AdcHandle3.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
    AdcHandle3.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    AdcHandle3.Init.NbrOfConversion       = 1;
    AdcHandle3.Init.DMAContinuousRequests = DISABLE;
    AdcHandle3.Init.EOCSelection          = DISABLE;

    DacHandle.Instance = DACx;


  //*******************************************/
     //  ADCs configuration: double interleaved   /
     //*******************************************/

     // ADC Common configuration
      // ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_Interl;
     // delay 12 => 2.083333.. MS/sec
     // delay 13 => 1.923077.. MS/sec
     // delay 14 => 1.785714.. MS/sec
     // delay 15 => 1.666667.. MS/sec
     // delay 16 => 1.562500   MS/sec
     // delay 18 => 1.388889.. MS/sec
     // delay 20 => 1.250000   MS/sec
    if (HAL_ADC_Init(&AdcHandle3) != HAL_OK)
             {
              Error_Handler();
             }

      if (HAL_ADC_Init(&AdcHandle2) != HAL_OK)
         {
          Error_Handler();
         }
     /*##-2- Configure ADC regular channel ######################################*/
      sConfigAdc.Channel      = ADCx_CHANNEL;
      sConfigAdc.Rank         = 1;
      sConfigAdc.SamplingTime = ADC_SAMPLETIME_3CYCLES; // was 3
      sConfigAdc.Offset       = 0;

      if (HAL_ADC_ConfigChannel(&AdcHandle2, &sConfigAdc) != HAL_OK)
         {
          Error_Handler();
         }

    /*##-4- Configure ADC1 regular channel #####################################*/
      if (HAL_ADC_ConfigChannel(&AdcHandle3, &sConfigAdc) != HAL_OK)
    	 {
    	  Error_Handler();
    	 }

   	  if (HAL_ADC_Init(&AdcHandle1) != HAL_OK)
   	  	 {
   	  	  Error_Handler();
   	  	 }

    /*##-4- Configure ADC1 regular channel #####################################*/
      if (HAL_ADC_ConfigChannel(&AdcHandle1, &sConfigAdc) != HAL_OK)
    	 {
    	  Error_Handler();
    	 }

    /*##-5- Configure Multimode ################################################*/
     AdcMM.Mode = ADC_TRIPLEMODE_INTERL;
     AdcMM.DMAAccessMode = ADC_DMAACCESSMODE_2;
     AdcMM.TwoSamplingDelay = ADC_TWOSAMPLINGDELAY_20CYCLES; //was 14CYCLES

    if (HAL_ADCEx_MultiModeConfigChannel(&AdcHandle1, &AdcMM) != HAL_OK)
    	{
    	 Error_Handler();
    	 }
}

void SDR_ADCStart()
{
	uint16_t bufsz;

    bufsz = BSIZE / 2;
    if (HAL_ADC_Start(&AdcHandle3) != HAL_OK)
    			   {
    			    Error_Handler();
    			   }

    if (HAL_ADC_Start(&AdcHandle2) != HAL_OK)
    			   {
    			    Error_Handler();
    			   }

	if (HAL_ADCEx_MultiModeStart_DMA(&AdcHandle1, (uint32_t *)&ADC_Data0, (uint32_t)bufsz) != HAL_OK)
	    {
	    	Error_Handler();
	    }
	__HAL_UNLOCK(&hdma_adc1);

	if (HAL_DMAEx_MultiBufferStart(&hdma_adc1, (uint32_t)&ADC->CDR, (uint32_t)&ADC_Data0, (uint32_t)&ADC_Data1, (uint32_t)bufsz) != HAL_OK)
	    {
		 Error_Handler();
		}

	// Configure the Interrupt Controller for DMA requests
	    HAL_NVIC_SetPriority(ADCx_DMA_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(ADCx_DMA_IRQn);
}

void SDR_InitGPIO()
{
  /* NOTE : This function is generated automatically by STM32CubeMX and eventually
            modified by the user
   */

	 // Configure GPIO pins
	 GPIO_InitStruct.Pin   = GPIO_PIN_7 | GPIO_PIN_14;
	 GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	 GPIO_InitStruct.Pull  = GPIO_PULLDOWN;

	 __HAL_RCC_GPIOF_CLK_ENABLE();
	 // Configure GPIO pins
	 GPIO_InitStruct.Pin   = GPIO_PIN_8 | GPIO_PIN_9;
	 GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	 GPIO_InitStruct.Pull  = GPIO_PULLUP;
	 HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);


	  __HAL_RCC_GPIOE_CLK_ENABLE();

	  GPIO_InitStruct.Pin = 1<<LCD_CS_PIN|1<<LCD_RS_PIN|1<<LCD_WR_PIN|1<<LCD_RD_PIN|1<<LCD_RST_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); //GPIOC


}
//-----------------------------------------------------------------------------
/**
  *         System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 200000000
  *            HCLK(Hz)                       = 200000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 400
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  */
//-----------------------------------------------------------------------------
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  HAL_RCC_DeInit();

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 432; // was 400
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
     Error_Handler();
    }

  /* Activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
      Error_Handler();
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
      {
       Error_Handler();
      }

   // Initialise display pins
   __HAL_RCC_GPIOE_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();

   GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_PULLUP;
   GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); //GPIOC

   GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

// Init here the output DAC, which uses DMA1 Stream 6 in double buffered mode
void SDR_InitDAC()
{
   DAC_ChannelConfTypeDef dacConfig;

    if (HAL_DAC_DeInit(&DacHandle) != HAL_OK)
      {
        Error_Handler();
      }
  /*##-1- Initialize the DAC peripheral ######################################*/
    if (HAL_DAC_Init(&DacHandle) != HAL_OK)
    {
      Error_Handler();
    }

    /*##-1- DAC channel1 Configuration #########################################*/
    dacConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
    dacConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

    if (HAL_DAC_ConfigChannel(&DacHandle, &dacConfig, DACx_CHANNEL) != HAL_OK)
    {
      Error_Handler();
    }

}
void SDR_DACStart()
{
	uint16_t bufsz;

    bufsz = BSIZE;

	if (HAL_DAC_Start_DMA(&DacHandle, DACx_CHANNEL, &AudioOut0, (uint32_t)BSIZE, DAC_ALIGN_12B_R) != HAL_OK)
		    {
		    	Error_Handler();
		    }

	__HAL_UNLOCK(&hdma_dac1);
	if (HAL_DMAEx_MultiBufferStart(&hdma_dac1, (uint32_t *)&AudioOut1, (uint32_t)DAC_DHR12R1_ADDRESS, (uint32_t *)&AudioOut0,  (uint32_t)BSIZE) != HAL_OK) // changed DHR12R2 to DHR12R1
	    {
	        Error_Handler();
	    }

	// Configure the Interrupt Controller for DMA requests
	    HAL_NVIC_SetPriority(DACx_DMA_IRQn, 1, 1);
	    HAL_NVIC_EnableIRQ(DACx_DMA_IRQn);
}
void initEncoder() //rotary - rotary encoder initialisation code
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	timer.Instance = TIM3;
	timer.Init.Period = 0xFFFF;
	timer.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer.Init.Prescaler = 0;
	timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	encoder.EncoderMode = TIM_ENCODERMODE_TI12;

	encoder.IC1Filter = 0x0F;
	encoder.IC1Polarity = TIM_INPUTCHANNELPOLARITY_RISING;
	encoder.IC1Prescaler = TIM_ICPSC_DIV4;
	encoder.IC1Selection = TIM_ICSELECTION_DIRECTTI;

	encoder.IC2Filter = 0x0F;
	encoder.IC2Polarity = TIM_INPUTCHANNELPOLARITY_FALLING;
	encoder.IC2Prescaler = TIM_ICPSC_DIV4;
	encoder.IC2Selection = TIM_ICSELECTION_DIRECTTI;

	if (HAL_TIM_Encoder_Init(&timer, &encoder) != HAL_OK)
	{
	  Error_Handler();
	 }

	if(HAL_TIM_Encoder_Start_IT(&timer,TIM_CHANNEL_1)!=HAL_OK)
	{
	  Error_Handler();
	 }
//this next section of code should probably be moved to the HAL_TIM_Encoder_MspInit routine
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 6, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
