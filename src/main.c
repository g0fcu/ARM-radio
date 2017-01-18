/*******************************************************************************

                   main.c module of the program ARM_Radio
                                                  
                                                  Copyright 2015 by Alberto I2PHD, June 2015
                                                  Converted to use HAL for STM32F7, Simon Kennedy G0FCU, September 2016
                                                              
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
#define  INMAIN

// Includes ------------------------------------------------------------------
#include "main.h"
#include "WM.h"
#include "MESSAGEBOX.h"
#include "LCD_X_8080_8.h"
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
uint8_t GUI_Initialized = 0;
uint16_t xSize = 320;
uint16_t ySize = 240;

TIM_HandleTypeDef 	 TimHandle;
TIM_HandleTypeDef 	 htim;
ADC_HandleTypeDef    AdcHandle1;
ADC_HandleTypeDef    AdcHandle2;
ADC_HandleTypeDef    AdcHandle3;
DMA_HandleTypeDef    hdma_dac1;
DAC_HandleTypeDef   DacHandle;
DMA_HandleTypeDef    hdma_adc1;
GPIO_InitTypeDef  	 GPIO_InitStruct;
GRAPH_DATA_Handle aGraph_Data;


TIM_Encoder_InitTypeDef encoder;
TIM_HandleTypeDef timer;

uint16_t ADC_Data0[BSIZE];
uint16_t ADC_Data1[BSIZE];
uint32_t uwPrescalerValue = 0;

int bar;
int scaling_factor;
float foo;
int fooint;
float32_t Output[1024];

uint16_t focus_btn = 0;
Mode currentmode = CW;
float meanavg;
WM_HWIN hWin;
#include "display.h"
#include "GUI.h"

int FFT_SIZE_CHOOSE =1024;

static void CPU_CACHE_Enable(void);
WM_HWIN CreateSDR_MainForm(void);

//----------------------------------------------------------------------------
int main(void)
{
  /* Enable the CPU Cache */
  CPU_CACHE_Enable();
  /* STM32F7xx HAL library initialization */
  HAL_DeInit();
  HAL_Init();
  SystemCoreClockUpdate();
  /* Configure the system clock to 216 MHz */
  SystemClock_Config();
  /* Compute the prescaler value to have TIM6 counter clock equal to 10 KHz */
  uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 10800) -1;
  // Configure the User push-button
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_EXTI);
  /* Configure LED's */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  __HAL_RCC_CRC_CLK_ENABLE(); /* Enable the CRC Module */
  GUI_Init();
  GUI_SetBkColor(GUI_BLACK);
  GUI_DispStringAt("Starting...", 0, 0);
  /* Multi buffering enable */
  WM_MULTIBUF_Enable(1);
  WM_SetCreateFlags(WM_CF_MEMDEV);
  /* Check if recommended memory for the sample is available */
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY)
    {
      GUI_ErrorOut("Not enough memory available.");
      return(0);
    }
  /* GUI_CURSOR_Show(); */
  WM_SetDesktopColor(GUI_BLACK);
  #if GUI_SUPPORT_MEMDEV
    WM_SetCreateFlags(WM_CF_MEMDEV);
  #endif

  GUI_Initialized = 1;
  hItem = WM_GetDialogItem(hWin, hVOL);
  SLIDER_SetNumTicks(hItem, 10);

  /* Activate the use of memory device feature */
  WM_SetCreateFlags(WM_CF_MEMDEV);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  // Create now the user interface, by loading the panel built
  // using the GUIBuilder utility
  hWin = CreateSDR_MainForm();
  GUI_Exec();
  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
        - Word Length = 8 Bits (7 data bit + 1 parity bit) :
  	                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
        - Stop Bit    = One Stop bit
        - Parity      = ODD parity
        - BaudRate    = 9600 baud
        - Hardware flow control disabled (RTS and CTS signals) */
   UartHandle.Instance        = USARTx;

   UartHandle.Init.BaudRate   = 9600;
   UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
   UartHandle.Init.StopBits   = UART_STOPBITS_1;
   UartHandle.Init.Parity     = UART_PARITY_ODD;
   UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
   UartHandle.Init.Mode       = UART_MODE_TX_RX;
   UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
   if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
      Error_Handler();
    }
// Set now the default values for some variables
  volume = 1;
  oldvol = volume;
  cwpitch = CWPITCH;
  os_time = 0;
  meanavg = 0.f;
  Qfactor = 0.987f;         // Q factor for the CW peak filter
  Muted   = false;
  Spectogram = true;
  AMindex  = LSBindex = 1;
  USBindex = CWindex  = 1;
  bw[AM]   = bw[LSB]  = Wide;
  bw[USB]  = bw[CW]   = Wide;
  agc[AM]  = agc[LSB] = Slow;
  agc[USB] = Slow;
  agc[CW]  = Fast;
  AGC_decay[Fast] = 0.9995f;
  AGC_decay[Slow] = 0.99995f;
  Hangcount[Fast] = 2;
  Hangcount[Slow] = 30;
  AgcThreshold    = 1.92e-4f;
  Fstep = 10;
  currentbw = Narrow;
  curmode = 3;
  maxmode = 4;
  curscale = 3;
  maxscale = 4;
  btn_group = 0;
  step = 0;
  Idx = 1;
  old_count, count = 0; //rotary
  foo = 0;

  bar=0;
  scaling_factor=100;
  foo=0;
  fooint=0;
  SDR_compute_IIR_parms();  // compute the IIR parms for the CW peak filter

// init the decimating FIR control blocks   
  arc = arm_fir_decimate_init_f32(&SfirR, NUMFIRCOEFS, 4, FIRcoefs, FIRstate1R, BSIZE*4); 
  while(arc != ARM_MATH_SUCCESS);   // spin loop if error
  arc = arm_fir_decimate_init_f32(&SfirI, NUMFIRCOEFS, 4, FIRcoefs, FIRstate1I, BSIZE*4); 
  while(arc != ARM_MATH_SUCCESS);   // spin loop if error

  DacHandle.Instance = DACx;
  // initialize the NVIC for PriorityGroup 4
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 1);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 4, 1);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  // initialize the various components of the application
  Load_Presets();
  Tune_Preset(hWin, PRESET_INIT);      // Set the initial tuning
  /*##-2- Configure the TIM peripheral #######################################*/
  if (TIM6_Config() != HAL_OK)
     {
      Error_Handler();
     }
  SDR_InitGPIO();
  initEncoder(); //rotary
  SDR_InitADC();
  SDR_InitDAC();
  SDR_DACStart();
  SDR_ADCStart();

  // Infinite loop in the main task, which has an idle priority
  while(1)
  {
	  //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
	  meanavg = (meanavg * 49.f + mean)/50.f;
	  ManageEncoder(); //rotary
	  GUI_Exec(); // execute all GUI jobs
   // HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

void ManageEncoder() //rotary
{
	//rotary - main rotary encoder code starts here
    uint16_t count=TIM3->CNT;

	if(count != old_count)
	  {
	   switch(btn_group)
		 {
		  case(1):
		  //Fplus / Fminus freq
		  if(count < old_count-2)
			{
			old_count = count;
			FminusClicked();
			}
			else if (count > old_count+2)
			    {
			    old_count = count;
				FplusClicked();
				}
		   break;
		   case(2):
		   //Mode
		   hItem = WM_GetDialogItem(hWin, hMODE);
		   if(count < old_count-2)
			 {
			  old_count = count;
			  curmode--;
			  if(curmode < 0) curmode = 0;
			  SetMode(hItem,curmode);
			 }
			  else if (count > old_count+2)
			    {
				old_count = count;
				curmode++;
				if(curmode>maxmode) curmode = maxmode;
				SetMode(hItem,curmode);
			    }
				break;
			case(3):
			 //BW
			hItem = WM_GetDialogItem(hWin, hBW);
			if(count < old_count-2)
			  {
			   old_count = count;
			   SetBW(hItem, Wide);
			   hItem = WM_GetDialogItem(hWin, hBW);
			   BUTTON_SetText(hItem, "Wide");
			   WM_InvalidateWindow(hWin);
			  }
			  else if (count > old_count+2)
			  	{
			  	 old_count = count;
			  	 SetBW(hItem, Narrow);
			  	 hItem = WM_GetDialogItem(hWin, hBW);
			  	 BUTTON_SetText(hItem, "Narrow");
			  	 WM_InvalidateWindow(hWin);
			  	}
			  	break;
			case(4):
			//AGC
			hItem = WM_GetDialogItem(hWin, hAGC);
			if(count < old_count-2)
			  {
			  old_count = count;
			  SetAGC(hItem, Fast);
			  hItem = WM_GetDialogItem(hWin, hAGC);
			  BUTTON_SetText(hItem, "Fast");
			  WM_InvalidateWindow(hWin);
			  }
			 else if (count > old_count+2)
				 {
			  	  old_count = count;
			  	  SetAGC(hItem, Slow);
				  hItem = WM_GetDialogItem(hWin, hAGC);
			  	  BUTTON_SetText(hItem, "Slow");
			  	  WM_InvalidateWindow(hWin);
			  	 }
			  	 break;
			  case(5):
			  //Mute
			  hItem = WM_GetDialogItem(hWin, hMUTE);
			  if(count < old_count-2)
			  	{
			  	 old_count = count;
			  	 volume = oldvol;
			  	 Muted = false;
			  	 WM_InvalidateWindow(hWin);
			  	}
				else if (count > old_count+2)
				  	{
					 old_count = count;
					 if(!Muted) oldvol = volume;
					 Muted = true;
				  	 volume = 0.f;
				  	 WM_InvalidateWindow(hWin);
				  	}
			  	break;
			  case(6):
			  //Vol
			  hItem = WM_GetDialogItem(hWin, hVOL);
			  if(count < old_count - 2)
				{
				 old_count = count;
			   	 SLIDER_Dec(hItem);
			   	 volume = SLIDER_GetValue(hItem);
			  	 WM_InvalidateWindow(hWin);
				}
				else if (count > old_count + 2)
				{
				 old_count = count;
				 SLIDER_Inc(hItem);
				 volume = SLIDER_GetValue(hItem);
				 WM_InvalidateWindow(hWin);
				}
				break;
			  case(7):
			 //Spectogram
			 hItem = WM_GetDialogItem(hWin, hSPECTOGRAM);
			 if(count < old_count - 2)
				{
				old_count = count;
				Spectogram = false;
				hItem = WM_GetDialogItem(hWin, hGRAPH);
				GRAPH_DATA_YT_Clear(aGraph_Data);
				WM_InvalidateWindow(hWin);
				}
			  	else if (count > old_count+2)
			  		{
			  		old_count = count;
			  		Spectogram = true;
			  		WM_InvalidateWindow(hWin);
			  		}
			  		break;
			  case(8):
			  //Scale
			  hItem = WM_GetDialogItem(hWin, hSCALE);
			  if(count < old_count - 2)
				{
				old_count = count;
			    curscale--;
				if(curscale < 0) curscale = 0;
			  		SetScale(hItem,curscale);
				}
				else if (count > old_count+2)
			  		{
			  		old_count = count;
			  		curscale++;
			  		if(curscale>maxscale) curscale = maxscale;
			  		SetScale(hItem,curscale);
			  		}
			 	break;
			  case(9):
			  //Step
			  hItem = WM_GetDialogItem(hWin, hFRADIO);
			  if(count < old_count - 2)
				{
				 old_count = count;
			 	 RADIO_Dec(hItem);
			 	 WM_InvalidateWindow(hWin);
			  	 SetFstep(RADIO_GetValue(hItem));
			  	}
			  	else if (count > old_count + 2)
			 		{
			  		 old_count = count;
			  		 RADIO_Inc(hItem);
			  		 WM_InvalidateWindow(hWin);
			  		 SetFstep(RADIO_GetValue(hItem));
			  		}
				break;
			  default:
			  		break;

		  	 }
		  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this application:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */

static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}


//-----------------------------------------------------------------------------
