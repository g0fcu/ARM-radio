/*******************************************************************************

                   SDR_math.h module of the program ARM_Radio
						                          
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
#ifndef SDRMATH_H
#define SDRMATH_H

#include "main.h"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

extern void  SDR_2R_toC_f32(float * pSrcA, float * pSrcB, float * pDst, uint32_t blockSize);
extern void  SDR_float_to_DAC_audio(float *pSrc, short *pDst, uint16_t blockSize);
extern void  SDR_downconvert_f32(uint16_t* signal, float offset, float* zeroIF_R, float* zeroIF_I);
extern void  SDR_memcpy_f32(float* pDst, float* pSrc, uint32_t blockSize);																 
extern void  SDR_mirror_LSB(float* buf, uint32_t blockSize);
extern void  SDR_compute_IIR_parms(void);
extern void  SDR_CWPeak(float *buf, uint32_t blockSize);
extern void  SDR_demodAM_AGC(float32_t * tmpSamp, float32_t * fAudio);
extern void  SDR_demodSSB_CW_AGC(float32_t * tmpSamp, float32_t * fAudio);
extern void  SDR_ComputeLO(float freq);

#endif   /* SDRMATH_N  */

