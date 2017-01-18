/*******************************************************************************

                   SDR_func.c module of the program ARM_Radio
						                          
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

#include "Presets.h"
#include "main.h"
#include "fftmask.h"
#include "WM.h"
#include "stm32f7xx_nucleo_144.h"
#include "stm32f746xx.h"

uint16_t *pR;
//-----------------------------------------------------------------------------
uint32_t bouncing(void)
{	
	int delta;
	static int last_time = 0;
	
  delta = os_time - last_time;
	last_time = os_time; 
// if less than 100 time units have elapsed from the previous
// invokation, then bouncing...  

	return delta < 100;
}
//-----------------------------------------------------------------------------
// Load from the Presets table
void Load_Presets(void)
{
  int k;

  for(k=0; k<MAXPRESETS; k++)
  {
    strcpy(psets[k].name, pNames[k]);
    psets[k].freq = pFreqs[k];
    psets[k].mode = pModes[k];
    psets[k].bw   = pBws[k];    
  }    
}
//-----------------------------------------------------------------------------
//Tune to the chosen preset
void Tune_Preset(WM_HWIN ptr, u8 Idx)
{
  char msg[14];
  int kHz, Hz;

  LOfreq = psets[Idx].freq;
  SetMode(ptr, psets[Idx].mode);
  SetBW(ptr, psets[Idx].bw);
  currentbw = psets[Idx].bw;
  strcpy(msg, psets[Idx].name);
  hItem = WM_GetDialogItem(ptr, hSTATION);
  EDIT_SetText(hItem, msg);
  WM_InvalidateWindow(ptr);

  kHz = LOfreq / 1000.f;  Hz = LOfreq - kHz*1000;
  hItem = WM_GetDialogItem(ptr, hFREQ);
  sprintf(msg, "%4d,%03d  Hz", kHz, Hz);
  EDIT_SetText(hItem, msg);
  WM_InvalidateWindow(ptr);
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Load the FFT mask according to the mode and the bandwidth chosen,
// and change the color of the buttons to indicate the active bandwidth
void SetBW(WM_HWIN ptr, Bwidth newbw)                                                        
{
	hItem = WM_GetDialogItem(ptr, hBW);
	switch(currentmode)
	{
	  case AM :
      bw[AM] = newbw;
      AMindex = (newbw == Narrow) ? 0 : 1;
      SDR_2R_toC_f32((float *)FFTmaskAM_R[AMindex], 
				             (float *)FFTmaskAM_I[AMindex], FFTmask, FFTLEN);	
      currentbw = (newbw == Narrow) ? 0 : 1;
	  break;
		
    case LSB :
      bw[LSB] = newbw;
      LSBindex = (newbw == Narrow) ? 0 : 1;
  	  SDR_2R_toC_f32((float *)FFTmaskSSB_R[LSBindex],
				             (float *)FFTmaskSSB_I[LSBindex], FFTmask, FFTLEN);	
      currentbw = (newbw == Narrow) ? 0 : 1;
      break; 

    case USB :
      bw[USB] = newbw;
      USBindex = (newbw == Narrow) ? 0 : 1;
  	  SDR_2R_toC_f32((float *)FFTmaskSSB_R[USBindex],
				             (float *)FFTmaskSSB_I[USBindex], FFTmask, FFTLEN);	
      currentbw = (newbw == Narrow) ? 0 : 1;
      break; 

    case CW  : 			
      bw[CW] = newbw;
      CWindex = (newbw == Narrow) ? 0 : 1;
  	  SDR_2R_toC_f32((float *)FFTmaskCW_R[CWindex],
				             (float *)FFTmaskCW_I[CWindex], FFTmask, FFTLEN);	
      currentbw = (newbw == Narrow) ? 0 : 1;
      break; 

    default :
      break;		
  }    
}	

//-----------------------------------------------------------------------------
// Change the AGC constants according to the mode and the AGC chosen,
// and change the color of the buttons to indicate the active AGC speed
void SetAGC(WM_HWIN ptr, Agctype newAGC)                                                        
{

	hItem = WM_GetDialogItem(ptr, hAGC);
	switch(currentmode)
	{
	  case AM :       agc[AM] = newAGC;
      Decay[AM]   = AGC_decay[newAGC];
      Hcount[AM]  = Hangcount[newAGC];
      BUTTON_SetPressed(hItem,0);
      WM_InvalidateWindow(ptr);
      break;
    
    case LSB :      agc[LSB] = newAGC;
      Decay[LSB]  = AGC_decay[newAGC];
      Hcount[LSB] = Hangcount[newAGC];
      BUTTON_SetPressed(hItem,0);
      WM_InvalidateWindow(ptr);
      break;
    
    case USB :      agc[USB] = newAGC;
      Decay[USB]  = AGC_decay[newAGC];
      Hcount[USB] = Hangcount[newAGC];
      BUTTON_SetPressed(hItem,0);
      WM_InvalidateWindow(ptr);
      break;
    
    case CW :       agc[CW] = newAGC;
      Decay[CW]   = AGC_decay[newAGC];
      Hcount[CW]  = Hangcount[newAGC];
      BUTTON_SetPressed(hItem,0);
      WM_InvalidateWindow(ptr);
      break;

    default :
         break;
  }
}	
//-----------------------------------------------------------------------------
// Set the new demodulation mode chosen by the user, and change the color
// of the buttons to indicate the active mode
void SetMode(WM_HWIN ptr, Mode newmode)                                                        
{
	currentmode = newmode;	
	hItem = WM_GetDialogItem(ptr, hMODE);
	BUTTON_SetPressed(hItem,0);
	switch(currentmode)
	{
	  case AM :
      SetBW(ptr, bw[AM]); SetAGC(ptr, agc[AM]);
      hItem = WM_GetDialogItem(hWin, hMODE);
      BUTTON_SetText(hItem, "AM");
      WM_InvalidateWindow(ptr);
	  break;
		
    case LSB :
      SetBW(ptr, bw[LSB]);  SetAGC(ptr, agc[LSB]);
      hItem = WM_GetDialogItem(hWin, hMODE);
      BUTTON_SetText(hItem, "LSB");
      WM_InvalidateWindow(ptr);
      break; 

    case USB :
      SetBW(ptr, bw[USB]);  SetAGC(ptr, agc[USB]);
      hItem = WM_GetDialogItem(hWin, hMODE);
      BUTTON_SetText(hItem, "USB");
      WM_InvalidateWindow(ptr);
      break; 

    case CW  : 			
      SetBW(ptr, bw[CW]);  SetAGC(ptr, agc[CW]);
      hItem = WM_GetDialogItem(hWin, hMODE);
      BUTTON_SetText(hItem, "CW");
      WM_InvalidateWindow(ptr);
      break; 

    default :
      break;			
	}
}	
void SetScale(WM_HWIN ptr, Scale newscale)
{

	hItem = WM_GetDialogItem(ptr, hSCALE);
	BUTTON_SetPressed(hItem,0);
	switch(newscale)
	{
	  case x1 :
      hItem = WM_GetDialogItem(hWin, hSCALE);
      BUTTON_SetText(hItem, "x1");
      WM_InvalidateWindow(ptr);
	  break;

	  case x10 :
	  hItem = WM_GetDialogItem(hWin, hSCALE);
	  BUTTON_SetText(hItem, "x10");
      WM_InvalidateWindow(ptr);
      break;

	  case x100 :
	  hItem = WM_GetDialogItem(hWin, hSCALE);
	  BUTTON_SetText(hItem, "x100");
      WM_InvalidateWindow(ptr);
      break;

	  case x500 :
	  hItem = WM_GetDialogItem(hWin, hSCALE);
	  BUTTON_SetText(hItem, "x500");
      WM_InvalidateWindow(ptr);
      break;

	  case x1000 :
	  hItem = WM_GetDialogItem(hWin, hSCALE);
	  BUTTON_SetText(hItem, "x1k");
	  WM_InvalidateWindow(ptr);
	  break;

    default :
      break;
	}
}
//-----------------------------------------------------------------------------
// Change the color of the button selected by the parameter "handle"
void ChangeColor(WM_HWIN ptr, int handle, int color)
{	
  WM_HWIN hItem;
	
	hItem = WM_GetDialogItem(ptr, handle);
  BUTTON_SetTextColor(hItem, BUTTON_CI_PRESSED, color); 						 
  BUTTON_SetTextColor(hItem, BUTTON_CI_UNPRESSED, color); 						 
}	
//-----------------------------------------------------------------------------
// Set the frequency step according to the radio button pressed by the user
void SetFstep(int idx)
{
  Fstep = pow(10, 5 - idx);	
}	
//-----------------------------------------------------------------------------
// Increase the frequency by the value of the current step
void FplusClicked()
{
  LOfreq += Fstep;
  LOfreq  = min(LOfreq, 2000000.f);
  psets[0].freq = LOfreq; psets[0].mode = currentmode; 
  psets[0].bw = bw[currentmode]; 
  Tune_Preset(hWin, 0);  // preset 0 means "User tuning"
}	
//-----------------------------------------------------------------------------
// Decrease the frequency by the value of the current step
void FminusClicked()
{
  LOfreq -= Fstep;
  LOfreq  = max(LOfreq, 8000.f);
  psets[0].freq = LOfreq; psets[0].mode = currentmode; 
  psets[0].bw = bw[currentmode]; 
  Tune_Preset(hWin, 0);  // preset 0 means "User tuning"

}	
//-----------------------------------------------------------------------------
// Toggle the ON/OFF status of the two on-board Leds
void LED_switch()
{	
  static uint32_t timer_cnt = 0;
	
  if (++timer_cnt & 1) {BSP_LED_On(LED2); BSP_LED_Off(LED3);} // SHK
	else                 {BSP_LED_On(LED3); BSP_LED_Off(LED2);}	// SHK
}
//-----------------------------------------------------------------------------
// Handle the SysTick interrupt 
//void SysTick_Handler()
//{
//	uwTick = OS_TimeMS = ++os_time;
	
//	if((os_time % 400) == 0) // toggle the green/red Leds every 400 time units
//    LED_switch();
//}
//-----------------------------------------------------------------------------
// Hopefully we should never land here.....
void Error_Handler(void)
{
	int cnt = 0;

		while(1)
		{
			cnt++;
			if (cnt == 10000000)
			{
				BSP_LED_Toggle(LED3);
				cnt = 0;
			}

		}
}


//-----------------------------------------------------------------------------  
// This the call back procedure of the highest priority task interrupts, those generated
// by DMA2 Stream when a new ADC buffer is just filled
/**
  * @brief  Conversion complete callback in non blocking mode
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and
  *         you can add your own implementation.
  * @retval None
  */


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  //DMA_HandleTypeDef DMA_Handle;

  static int16_t k, idx = 0;
  float sum;

  register float *ptDataR, *ptDataI, inER, inOR, inEI, inOI, outR, outI,
	               tmp1R, tmp1I, tmp2R, tmp2I, tmp3R, tmp3I;
	
  static   float inE1Rold,  inE2Rold,  inE1Iold,   inE2Iold,  inO1Rold,
	               inO2Rold,  inO1Iold,  inO2Iold,   inO1Rold2, inO1Iold2,   
	               inO2Rold2, inO2Iold2,             inE3Rold,  inE3Iold,
                 inO3Rold,  inO3Iold,  inO3Rold2,  inO3Iold2, inE4Rold, 
	               inE4Iold,  inO4Rold2, inO4Iold2,  inO4Rold,  inO4Iold;
	               
  //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET); // uncomment this if you want to measure time spent in this routine
  //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
  HAL_NVIC_ClearPendingIRQ(ADCx_DMA_IRQn);
  BSP_LED_On(LED2);

// compute the new NCO buffer, with the CWpitch offset if receiving CW  
  if(currentmode == CW)
	  SDR_ComputeLO(LOfreq-cwpitch);  // prepare next LO buffer
  else
	  SDR_ComputeLO(LOfreq);          // prepare next LO buffer
	
// compute the smoothed average value of the buffer, to be used as offset
// in the short words to floating point conversion routine  
	sum = 0;
	k = BSIZE;
  while(k)
	{ 	
		sum += pR[k-1];
		sum += pR[k-2];
		sum += pR[k-3];
		sum += pR[k-4];
		k-=4;
	}	

	mean = sum/(float)BSIZE;

// downconvert to zero IF, by multiplication by the exp(-jwt) signal
// generated by the NCO, and at the same time convert to floating point  
	SDR_downconvert_f32((uint16_t *)pR, meanavg, ADC_Rdata, ADC_Idata);
	ptDataR = ADC_Rdata;  ptDataI = ADC_Idata;

//-------------------------------------------------------------------------
// Now we decimate by 16 the input samples, using the CIC polyphase decomposition
// technique, which has the advantage of eliminating the recursive
// component, allowing the use of floating point, rather fast on a Cortex M4F
//
// A dividing by 16, order 4, CIC is used. Then a 4096-entry buffer is filled, and
// passed to the baseband interrupt routine, where it is additionally filtered with a
// sync-compensating FIR, which also adds further stop band rejection and a decimation by 4
//-------------------------------------------------------------------------

  k=BSIZE/2;  // BSIZE/2 to process BSIZE entries, two at a time

  while(k--)
	{	 
// CIC, R=16, M=4, computed in four div_by_2 sections, using the polyphase decomposition
// H(z) = (1 + z^-1)(1 + z^-1)(1 + z^-1)(1 + z^-1) each section, which can be decomposed as follows :
// H(z) = 1 + 4z^-1 + 6z^-2 + 4z^-3 + z^-4 
//        which being separated in even and odd samples in advance becomes
// (1 + 6z^-1 + z^-2) for odd samples and (4 + 4z^-1) for even samples, which, when summed, give :
// odd + 6odd_old + odd_old2 + 4even + 4even_old =	odd + 6odd_old + odd_old2 + 4(even + even_old)		
		
		inER=*ptDataR++; inOR=*ptDataR++;
		inEI=*ptDataI++; inOI=*ptDataI++;

        outR=(inOR+6.f*inO1Rold+inO1Rold2+4.f*(inER+inE1Rold));
        outI=(inOI+6.f*inO1Iold+inO1Iold2+4.f*(inEI+inE1Iold));

		inE1Rold = inER;
		inE1Iold = inEI;

		inO1Rold2 = inO1Rold;
		inO1Rold = inOR;

		inO1Iold2 = inO1Iold;
		inO1Iold = inOI;
		
		if((k & 0x1))  // skip the if-block for k multiple of 2 (in base zero),
			             // else save the even element just produced and cycle the while loop... 
		   {
           tmp1R = outR;
           tmp1I = outI;  // save the even element produced
		   continue;
		   }
		
// at this point we have two elem. (tmp1R[even] and outR[odd] and also the I counterparts)
// produced using 4 input samples, totalling a decimation by 2		
// now compute the couple of elements for the next step

          inER=tmp1R;
          inOR=outR;
          inEI=tmp1I;
          inOI=outI;

          outR=(inOR+6.f*inO2Rold+inO2Rold2+4.f*(inER+inE2Rold));
          outI=(inOI+6.f*inO2Iold+inO2Iold2+4.f*(inEI+inE2Iold));

		  inE2Rold = inER;
		  inE2Iold = inEI;

		  inO2Rold2 = inO2Rold;
		  inO2Rold = inOR;

		  inO2Iold2 = inO2Iold;
		  inO2Iold = inOI;
		
		  if((k & 0x2)) // skip the if block for k multiple of 4 (in base zero),
			            // else save the even element just produced and cycle the while loop... 
		     {
             tmp2R = outR;
             tmp2I = outI;  // save the even element produced
		     continue;
		     }
		
// now we have the input samples decimated by 4, even element in tmp2R, tmp2I,
// and the odd element in outR, outI		
// now compute the couple of elements for the next step
		
           inER=tmp2R;
           inOR=outR;

           inEI=tmp2I;
           inOI=outI;

           outR=(inOR+6.f*inO3Rold+inO3Rold2+4.f*(inER+inE3Rold));
           outI=(inOI+6.f*inO3Iold+inO3Iold2+4.f*(inEI+inE3Iold));

		   inE3Rold  = inER;
		   inE3Iold  = inEI;

		   inO3Rold2 = inO3Rold; inO3Rold = inOR;
		   inO3Iold2 = inO3Iold; inO3Iold = inOI;

		   if((k & 0x4)) // skip the if block for k multiple of 8 (in base zero),
			            // else save the even element just produced and cycle the while loop... 
		     {
             tmp3R = outR;
             tmp3I = outI;  // save the even element produced
		     continue;
		     }

// at this point we have two elem. (tmp3R[even] and outR[odd] and also the I counterparts)
// produced with 4 of the previous elem, i.e. with 16 input samples, totalling 
// a decimation by 8. Now compute the couple of elements for the next step

           inER=tmp3R;
           inOR=outR;

           inEI=tmp3I;
           inOI=outI;

           outR=(inOR+6.f*inO4Rold+inO4Rold2+4.f*(inER+inE4Rold));
           outI=(inOI+6.f*inO4Iold+inO4Iold2+4.f*(inEI+inE4Iold));

		   inE4Rold = inER;
		   inE4Iold = inEI;

		   inO4Rold2 = inO4Rold;
		   inO4Rold = inOR;

		   inO4Iold2 = inO4Iold;
		   inO4Iold = inOI;
		
// at this point we have a single element (outR and its counterpart outI), produced 
// with 2 of the previous element, i.e. with 16 input samples, totalling a decimation by 16	
// we downscale it with a factor of 32768, i.e. the gain of the CIC, i.e.	R^M = 16^4 = 65536
// divided by two, to compensate for the 3 dB loss caused by keeping just half of the band    

// create a block of BSIZE*4 entries, which will be then decimated by 4

	       Rbasedata[idx] = outR/32768.f;
	       Ibasedata[idx++] = outI/32768.f;

		   if(idx < BSIZE*4) continue;

		   idx = 0;
		// generate now an interrupt to signal the base band processing routine that it has a new buffer
		 HAL_NVIC_SetPendingIRQ(EXTI1_IRQn);
		 //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
	}

  BSP_LED_Off(LED2);
}	


//-----------------------------------------------------------------------------

