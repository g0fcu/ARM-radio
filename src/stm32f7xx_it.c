/**
  ******************************************************************************
  * @file    STemWin/STemWin_HelloWorld/Src/stm32f7xx_it.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    18-November-2015 
  * @brief   Main Interrupt Service Routines.
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
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern volatile GUI_TIMER_TIME OS_TimeMS;
uint8_t a,b,ab,c;
uint8_t pre_ab=0;
uint16_t count_=0, old_count_=0;
int opt;
//int bar;
//int scaling_factor;

//float foo;
//int fooint;
//float32_t Output[1024];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  /* Update the LocalTime by adding 1 ms each SysTick interrupt */
  HAL_IncTick();
  
  OS_TimeMS++;
}

/******************************************************************************/
/*                 STM32F7xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f7xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */

// Manage the interrupt generated by the pressing of the User button
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_13)
// User button pressed, cycle through all the presets
       {
	   Idx++;
       if(Idx >= MAXPRESETS) Idx = 1;
       Tune_Preset(hWin, Idx);
  /* Clear the EXTI line 0 pending bit */
       HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
       }

	//rotary - rotary encoder code starts here
     if (GPIO_Pin == ENCODER_PIN)
     {
 	 //encoder pressed processing here
	 btn_group++;
	 if(btn_group>9) btn_group = 1;
	 switch(btn_group)
	 {
	 case(1):
		//Fplus / Fminus freq
		hItem = WM_GetDialogItem(hWin, hFRADIO);
		RADIO_SetTextColor(hItem, GUI_YELLOW);
		hItem = WM_GetDialogItem(hWin, hSTATION);
	 	EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, GUI_RED);
	 	break;
	 case(2):
		//Mode
		hItem = WM_GetDialogItem(hWin, hSTATION);
		EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, GUI_GREEN);
		hItem = WM_GetDialogItem(hWin, hMODE);
		BUTTON_SetPressed(hItem,1);
		break;
	 case(3):
		//BW
		hItem = WM_GetDialogItem(hWin, hMODE);
		BUTTON_SetPressed(hItem,0);
		hItem = WM_GetDialogItem(hWin, hBW);
		BUTTON_SetPressed(hItem,1);
		break;
	 case(4):
	    //AGC
		hItem = WM_GetDialogItem(hWin, hBW);
		BUTTON_SetPressed(hItem,0);
		hItem = WM_GetDialogItem(hWin, hAGC);
		BUTTON_SetPressed(hItem,1);
		break;
	 case(5):
	 	//Mute
		hItem = WM_GetDialogItem(hWin, hAGC);
		BUTTON_SetPressed(hItem,0);
		hItem = WM_GetDialogItem(hWin, hMUTE);
		BUTTON_SetPressed(hItem,1);
		break;
	 case(6):
	 	//Volume
		hItem = WM_GetDialogItem(hWin, hMUTE);
		BUTTON_SetPressed(hItem,0);
		hItem = WM_GetDialogItem(hWin, hVOL);
		SLIDER_SetBkColor(hItem, GUI_RED);
		break;
	 case(7):
	 	//Spectogram
	 	hItem = WM_GetDialogItem(hWin, hVOL);
	    SLIDER_SetBkColor(hItem, GUI_BLACK);
	 	hItem = WM_GetDialogItem(hWin, hSPECTOGRAM);
	 	BUTTON_SetPressed(hItem, 1);
	 	break;
	 case(8):
	 	//Scale
	 	hItem = WM_GetDialogItem(hWin, hSPECTOGRAM);
	    BUTTON_SetPressed(hItem, 0);
	 	hItem = WM_GetDialogItem(hWin, hSCALE);
	 	BUTTON_SetPressed(hItem, 1);
	 	break;
	 case(9):
	 	//Step
	 	hItem = WM_GetDialogItem(hWin, hSCALE);
	    BUTTON_SetPressed(hItem, 0);
	 	hItem = WM_GetDialogItem(hWin, hFRADIO);
	 	RADIO_SetTextColor(hItem, GUI_RED);
	 	break;
	 default:
		break;
	 }

 	 HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
     }
 	//rotary - main rotary encoder code ends here

}
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}
/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim);
}

/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
  LTDC_HandleTypeDef hltdc;
  HAL_LTDC_IRQHandler(&hltdc);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void ADCx_DMA_IRQHandler(void)
{
    //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_DMA_IRQHandler(AdcHandle1.DMA_Handle);
    //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
}

/**
* @brief  This function handles DMA interrupt request.
* @param  None
* @retval None
*/
void DACx_DMA_IRQHandler(void)
{
   BSP_LED_On(LED3);
   //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
   HAL_DMA_IRQHandler(DacHandle.DMA_Handle1);
   HAL_NVIC_ClearPendingIRQ(DACx_DMA_IRQn);
   //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
   BSP_LED_Off(LED3);

}
//-----------------------------------------------------------------------------
// This is the handler of the software interrupt generated when ADC buffer is filled
//
void EXTI1_IRQHandler(void)
{
  float32_t maxValue;
  uint32_t maxIndex;
  short  *p;

  BSP_LED_On(LED1);

  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);  // set bit 8 of GPIOF high, to be observed with an oscilloscope // SHK
  HAL_NVIC_ClearPendingIRQ(EXTI1_IRQn);
// copy into work buffers the data received by CIC decimator
  SDR_memcpy_f32(Rbase, Rbasedata, BSIZE*4);
  SDR_memcpy_f32(Ibase, Ibasedata, BSIZE*4);

// inverse sync filtering and decimation by 4
	arm_fir_decimate_f32(&SfirR, Rbase, Rdata, BSIZE*4);
	arm_fir_decimate_f32(&SfirI, Ibase, Idata, BSIZE*4);

// filter now with fast convolution
//---------------------------------
// shift the FFT buffer to the left
  SDR_memcpy_f32(fCbase, fCbase + FFTLEN, FFTLEN);
// insert at the right edge the latest data
  SDR_2R_toC_f32(Rdata, Idata, fCbase + FFTLEN, BSIZE);
// copy into the (in place...) FFT buffer
  SDR_memcpy_f32(FFTbuf, fCbase, FFTLEN*2);
// compute the direct FFT
	arm_cfft_f32(&arm_cfft_sR_f32_len1024, FFTbuf, DIRECTFFT, NOREVERSE);
// if LSB, copy the LSB in the lower half (USB)
  if(currentmode == LSB) SDR_mirror_LSB(FFTbuf, FFTLEN);
// mult. by the fast convolution mask
  arm_cmplx_mult_cmplx_f32(FFTbuf, FFTmask, FFTbuf2, FFTLEN);

// compute now the inverse FFT
  arm_cfft_f32(&arm_cfft_sR_f32_len1024, FFTbuf2, INVERSEFFT, NOREVERSE);
// then do the overlap-discard
  SDR_memcpy_f32(tmpSamp, FFTbuf2 + 2*FFTLEN - 2*BSIZE, 2*BSIZE);

  if (Spectogram)
  {
    if (fooint>256)
    {
	  switch(curscale)
	  {
		case(0):
		  scaling_factor = 1;
		  break;
		case(1):
		  scaling_factor = 10;
		  break;
		case(2):
		  scaling_factor = 100;
		  break;
		case(3):
		  scaling_factor = 500;
		  break;
		case(4):
		  scaling_factor = 1000;
		  break;
	  }
	  arm_cmplx_mag_f32(tmpSamp, Output, 1024);
	  //arm_max_f32(Output, 1024, &maxValue, &maxIndex);
	  //printf("%i %f\n",maxIndex, maxValue);
      hItem = WM_GetDialogItem(hWin, hGRAPH);
      fooint = 0;
      //printf("%i\n",bar);
      GRAPH_DATA_YT_Clear(aGraph_Data);
	  GRAPH_DATA_YT_SetAlign(aGraph_Data, GRAPH_ALIGN_LEFT);
  // this loop takes 12.5ms to execute - too long?
      for (bar = BSIZE; bar < (BSIZE*2)+12; bar++)
        {
    	//  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
    	GRAPH_DATA_YT_AddValue(aGraph_Data, Output[bar]*scaling_factor);
    	//  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
    	  //printf("%i %f %i %f\n",maxIndex, maxValue, bar, Output[bar]);
        }
      WM_InvalidateWindow(hWin);

      }
    else
      {
	  fooint++;
      }
  }


// we have now the bandpass filtered I/Q, demodulate the signal
  switch(currentmode)
	{
		case AM :
      SDR_demodAM_AGC(tmpSamp, fAudio);  break;

		case LSB :
		case USB :
		  SDR_demodSSB_CW_AGC(tmpSamp, fAudio); break;

		case  CW :
		  SDR_demodSSB_CW_AGC(tmpSamp, fAudio);
      if(bw[CW] == Narrow) SDR_CWPeak(fAudio, BSIZE); break;

		default:
		  break;
	}

 // send the demodulated audio to the DMA buffer just emptied
 /* Current memory buffer used is Memory 0 */
  if((hdma_dac1.Instance->CR & DMA_SxCR_CT) == 0)
    {
      p=AudioOut0;
      BSP_LED_On(LED3);
    }
    else
    {
      p=AudioOut1;
      BSP_LED_Off(LED3);
    }
// and reconvert from floating point to short words
  SDR_float_to_DAC_audio(fAudio, p, BSIZE);
  BSP_LED_Off(LED1);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{

}
void HAL_DAC_ConvCpltM1CallbackCh1(DAC_HandleTypeDef* hdac)
{

}

void TIM3_IRQHandler(void)
{
 HAL_TIM_IRQHandler(&timer);
}

void EXTI0_IRQHandler(void) //rotary
{
 HAL_GPIO_EXTI_IRQHandler(ENCODER_PIN);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
