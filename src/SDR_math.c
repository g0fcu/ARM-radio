/*******************************************************************************

                   SDR_math.c module of the program ARM_Radio
						                          
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

/******************************************************************************
         Some mathematical routines needed by the program ARM_Radio
******************************************************************************/

#include "Globals.h"

//------------------------------------------------------------------------------
void SDR_ComputeLO(float32_t freq)
{
/*------------------------------------------------------------------------------
  ComputeLO,  fill the LO complex vector with the new samples
 *------------------------------------------------------------------------------*/
	uint16_t        k;
	float           *pBufR=LO_R, *pBufI=LO_I;
  static float    costheta, sintheta, oldfreq = 1.e9f, ym1i=1.f, ym1q=0.f, 
	                ypi, ypq, tmpi, gain=1.f;
	
	if (oldfreq != freq)
	{	
	  oldfreq  =  freq;
		costheta =  cos(TWOPI * freq / SamplingRate);
    sintheta = -sin(TWOPI * freq / SamplingRate);		
	}

	k=BSIZE/4;   // BSIZE/4, as the loop is unrolled by 4 and we
               // have to fill a buffer of BSIZE complex entries	                             
	
// Coupled Quadrature Oscillator with level stabilization	
	while(k)
	{                    
// loop partially unrolled for performance		

		ypi  = ym1i * costheta - ym1q * sintheta; *pBufR++ = tmpi = ypi * gain;
		ypq  = ym1i * sintheta + ym1q * costheta; *pBufI++ = ym1q = ypq * gain;  
    ym1i = tmpi;
		
		ypi  = ym1i * costheta - ym1q * sintheta; *pBufR++ = tmpi = ypi * gain;
		ypq  = ym1i * sintheta + ym1q * costheta; *pBufI++ = ym1q = ypq * gain;  
    ym1i = tmpi;
		
		ypi  = ym1i * costheta - ym1q * sintheta; *pBufR++ = tmpi = ypi * gain;
		ypq  = ym1i * sintheta + ym1q * costheta; *pBufI++ = ym1q = ypq * gain;  
    ym1i = tmpi;
		
		ypi  = ym1i * costheta - ym1q * sintheta; *pBufR++ = tmpi = ypi * gain;
		ypq  = ym1i * sintheta + ym1q * costheta; *pBufI++ = ym1q = ypq * gain;  
    ym1i = tmpi;
		
    k--;
	}
// compute the gain to be applied to stabilize the level
  gain = (8192.5f - (ypi * ypi + ypq * ypq))/8192.f;
}	
//------------------------------------------------------------------------------
// Combine two floating point real vectors into one complex vector 
void SDR_2R_toC_f32(float * pSrcA, float * pSrcB, float * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;           /* loop counter */

// loop Unrolling
  blkCnt = blockSize >> 2u;

// Compute 4 outputs at a time
  while(blkCnt)
  {
    *pDst++ = *pSrcA++;  *pDst++ = *pSrcB++;
    *pDst++ = *pSrcA++;  *pDst++ = *pSrcB++;
    *pDst++ = *pSrcA++;  *pDst++ = *pSrcB++;
    *pDst++ = *pSrcA++;  *pDst++ = *pSrcB++;
    
    blkCnt--;
  }
}
//---------------------------------------------------------------------------------------
// Multiply the real signal vector by the complex NCO vector producing the zeroIF
// complex vector, and at the same time convert to floating point also using
// the smoothed average ADC offset computed by the DMA2_Stream0_IRQHandler routine
void SDR_downconvert_f32(uint16_t* signal, float offset, float* zeroIF_R, float* zeroIF_I)
{
  uint32_t blkCnt;            // loop counter
  float  tmp1, tmp2, tmp3, tmp4, *LOR=LO_R, *LOI=LO_I;
	uint16_t *pt = signal;
	
// loop Unrolling
  blkCnt = BSIZE >> 2u;   // loop unrolling.  Compute 4 outputs at a time
  while(blkCnt)
  {  // DMA Mode2, first ADC2 then ADC1...
/*
     tmp1=((*(pt+1)-offset)) / 2048.f;
		 tmp2=((*(pt)  -offset)) / 2048.f;
		 tmp3=((*(pt+3)-offset)) / 2048.f;
		 tmp4=((*(pt+2)-offset)) / 2048.f;
*/

     tmp2=((*(pt+1)-offset)) / 2048.f;
		 tmp1=((*(pt)  -offset)) / 2048.f;
		 tmp4=((*(pt+3)-offset)) / 2048.f;
		 tmp3=((*(pt+2)-offset)) / 2048.f;
    
    *zeroIF_R++ = *LOR++ * tmp1;  *zeroIF_I++ = *LOI++ * tmp1;
		 *zeroIF_R++ = *LOR++ * tmp2;  *zeroIF_I++ = *LOI++ * tmp2;
		 *zeroIF_R++ = *LOR++ * tmp3;  *zeroIF_I++ = *LOI++ * tmp3;
		 *zeroIF_R++ = *LOR++ * tmp4;  *zeroIF_I++ = *LOI++ * tmp4;
     pt += 4;
     blkCnt--;
	}	
}
//---------------------------------------------------------------------------------------
// Convert back from floating point to short words, applying the volume setting
void SDR_float_to_DAC_audio(float *pSrc, short *pDst, uint16_t blockSize)
{
  uint16_t blkCnt;            // loop counter
  //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
  /* loop Unrolling */
  blkCnt = blockSize >> 2u;   // loop unrolling.  Compute 4 outputs at a time
  while(blkCnt--)
  {
	  *pDst++ = (short)(2048.f + *pSrc++ * 2048.f * volume);
	  *pDst++ = (short)(2048.f + *pSrc++ * 2048.f * volume);
	  *pDst++ = (short)(2048.f + *pSrc++ * 2048.f * volume);
	  *pDst++ = (short)(2048.f + *pSrc++ * 2048.f * volume);
   }
  //HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
	return;
	
}	
//---------------------------------------------------------------------------------------
// Optimized version of the memcpy routine
void SDR_memcpy_f32(float* pDst, float* pSrc, uint32_t blockSize)
{
  uint32_t blkCnt;            /* loop counter */

  float32_t in1, in2, in3, in4;
// loop Unrolling
  blkCnt = blockSize >> 2u;

// Compute 4 outputs at a time.    
  while(blkCnt > 0u)
  {
    /* Copy and then store the results in the destination buffer */
	  in1 = *pSrc++;

	  	      *pDst++ = in1;
	  	      in2 = *pSrc++;

	  	      *pDst++ = in2;
	  	      in3 = *pSrc++;

	  	      *pDst++ = in3;
	  	      in4 = *pSrc++;

	  	      *pDst++ = in4;


// Decrement the loop counter
    blkCnt--;
  }
}

//---------------------------------------------------------------------------------------
// Mirror the upper half (LSB) into the lower half (USB) of the complex buffer	
void  SDR_mirror_LSB(float* buf, uint32_t blockSize)
{
  uint32_t blkCnt;            /* loop counter */
  float *pbR, *pbI, *peR, *peI;
	
// loop Unrolling */
  blkCnt = blockSize >> 3u;  // divide by 8, as the mirroring stops at half the buffer...
	blkCnt--;                  // minus 1, as the DC term is skipped

  pbR = buf+2;  pbI = buf+3; peR = buf + blockSize*2 - 2; peI = buf + blockSize*2 - 1;

//  Compute 4 outputs at a time.    
	while(blkCnt--)
	{
     *pbR = *peR; *pbI = -*peI; pbR+=2; pbI+=2; peR-=2; peI-=2;
     *pbR = *peR; *pbI = -*peI; pbR+=2; pbI+=2; peR-=2; peI-=2;
     *pbR = *peR; *pbI = -*peI; pbR+=2; pbI+=2; peR-=2; peI-=2;
     *pbR = *peR; *pbI = -*peI; pbR+=2; pbI+=2; peR-=2; peI-=2;
	}
}
// ------------------------------------------------------
// Compute the parameters for the double IIR filter used for the narrow CW mode
void SDR_compute_IIR_parms(void)
{
   float r, r2, wr, cosw0;
	 float rate = RATEOUT;

   r = Qfactor;

   a1 = a2 = b0 = 0.f; 
   r2 = r*r;
   wr = 2.f * cwpitch / rate * myPI;
   cosw0 = (2.f * r / (1.f + r2)) * cos(wr); // resonance frequency correction
										                         // (see the Proakis & Manolakis book)
   a1 = -2.f * r * cosw0;
   a2 = r2;
// b0 is normalized for gain ~ 2dB on all the band
   b0 = 1.2f * (1.f - r) * sqrt(1.f + r2 - 2.f * r * cos(2.f*wr));
}
// ------------------------------------------------------
// Double IIR resonator with two poles at wr e -wr. Used for the narrow CW mode
void SDR_CWPeak(float *buf, uint32_t blockSize)
{
   static float y1a=0.f, y2a=0.f, y1b=0.f, y2b=0.f;
	 register float x0, y0;
   uint32_t blkCnt = blockSize >> 2u;       /* loop counter */
	
// Compute 4 outputs at a time, loop unrolled for performance     
	 while(blkCnt--)
   {  
		 x0 = *buf;
	   y0 = -a1 * y1a - a2 * y2a + b0 * x0;
	   y2a = y1a;
	   y1a = y0;
	   y0 = -a1 * y1b - a2 * y2b + b0 * y0;
	   y2b = y1b;
	   y1b = y0;
	   *buf++ = y0;

		 x0 = *buf;
	   y0 = -a1 * y1a - a2 * y2a + b0 * x0;
	   y2a = y1a;
	   y1a = y0;
	   y0 = -a1 * y1b - a2 * y2b + b0 * y0;
	   y2b = y1b;
	   y1b = y0;
	   *buf++ = y0;

		 x0 = *buf;
	   y0 = -a1 * y1a - a2 * y2a + b0 * x0;
	   y2a = y1a;
	   y1a = y0;
	   y0 = -a1 * y1b - a2 * y2b + b0 * y0;
	   y2b = y1b;
	   y1b = y0;
	   *buf++ = y0;

		 x0 = *buf;
	   y0 = -a1 * y1a - a2 * y2a + b0 * x0;
	   y2a = y1a;
	   y1a = y0;
	   y0 = -a1 * y1b - a2 * y2b + b0 * y0;
	   y2b = y1b;
	   y1b = y0;
	   *buf++ = y0;
   }
}
// ------------------------------------------------------
// AM demodulation with AGC
void SDR_demodAM_AGC(float32_t * tmpSamp, float32_t * fAudio)
{
	static float wold = 0.f, pk = 0.02f;
	float        w, tmp;
  int          k, j;
	static int   hangcnt = 0;
	
// AM demodulation, compute the magnitude taking the data from the right edge
// of the buffer after the inverse FFT and the overlap-and-discard algorithm

	for(k=j=0; k<BSIZE*2; k+=2)
	{
	  tmp = tmpSamp[k]*tmpSamp[k] + tmpSamp[k+1]*tmpSamp[k+1];
	  arc = arm_sqrt_f32(tmp, &audiotmp);      // implement also the AM demod
	  while(arc != ARM_MATH_SUCCESS);

	  if(pk < audiotmp)
	  {
			pk = audiotmp;
		  hangcnt = Hcount[AM]; 
	  }

    audiotmp /= max(pk, AgcThreshold);  
		
	  if(hangcnt == 0)
		  pk  *= Decay[AM];
		
// DC removal filter -----------------------
	  w = audiotmp + wold * 0.96f; // increasing this constant gives more bass response...
	  fAudio[j++] = w - wold;      // .... but keep it ALWAYS less than 1 ....  !
	  wold = w;
// -----------------------------------------
	}

	if(hangcnt > 0)  hangcnt--;
}
//---------------------------------------------------------------------------
// SSB and CW demodulation with AGC
void SDR_demodSSB_CW_AGC(float32_t * tmpSamp, float32_t * fAudio)
{
	static float pk = 0.02f, sav;
	float        tmp;
  int          k, j;
	static int   hangcnt = 0;
	
// SSB or CW demodulation, compute the audio taking the data from the real part of 
// the right edge of the buffer after the inverse FFT and the overlap-and-discard algorithm

	for(k=j=0; k<BSIZE*2; k+=2)
	{
	  tmp = tmpSamp[k]*tmpSamp[k] + tmpSamp[k+1]*tmpSamp[k+1];
	  arm_sqrt_f32(tmp, &sav);  

	  if(pk < sav)
	  {
			pk = sav;
      if(currentmode == CW) hangcnt = Hcount[CW];
      else
        hangcnt = (currentmode == LSB) ? Hcount[LSB] : Hcount[USB]; 
	  }

// take just the real part and that is the demodulated audio
    fAudio[j++] = tmpSamp[k] / max(pk, AgcThreshold);  
		
	  if(hangcnt == 0)
    {  
      if(currentmode == CW) pk  *= Decay[CW];
      else
		    pk  *= (currentmode == LSB) ? Decay[LSB] : Decay[USB];
    }  
	}
	
	if(hangcnt > 0)  hangcnt--;
}
//---------------------------------------------------------------------------
