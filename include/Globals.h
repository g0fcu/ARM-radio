/*******************************************************************************

                   Globals.h module of the program ARM_Radio
						                          
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
#ifndef __GLOBALS_H
#define __GLOBALS_H

// allocate actual memory only when invoked from the main.c module
#ifdef INMAIN
 #define EXTERN
#else
 #define EXTERN extern
#endif  
 
#include "stdint.h" 
#include "stm32f7xx.h"
#include "main.h"
 
// place the following variables in the CCM section of RAM ------------------
EXTERN float Rbasedata[BSIZE*4] __attribute__((at(0x10000000)));
#define runninglen1 sizeof(Rbasedata)
EXTERN float Ibasedata[BSIZE*4] __attribute__((at(0x10000000 + runninglen1)));
#define runninglen2 runninglen1 + sizeof(Ibasedata)
EXTERN float Rbase[BSIZE*4]     __attribute__((at(0x10000000 + runninglen2)));
#define runninglen3 runninglen2 + sizeof(Rbase)
EXTERN float Ibase[BSIZE*4]     __attribute__((at(0x10000000 + runninglen3)));
#define runninglen4 runninglen3 + sizeof(Ibase)
EXTERN float Rdata[BSIZE]       __attribute__((at(0x10000000 + runninglen4)));
#define runninglen5 runninglen4 + sizeof(Rdata)
EXTERN float Idata[BSIZE]       __attribute__((at(0x10000000 + runninglen5)));
#define runninglen6 runninglen5 + sizeof(Idata)
EXTERN float FFTmask[FFTLEN*2]  __attribute__((at(0x10000000 + runninglen6)));
#define runninglen7 runninglen6 + sizeof(FFTmask)
EXTERN float FFTbuf[FFTLEN*2]   __attribute__((at(0x10000000 + runninglen7)));
#define runninglen8 runninglen7 + sizeof(FFTbuf)
EXTERN float FFTbuf2[FFTLEN*2]  __attribute__((at(0x10000000 + runninglen8)));
// end of CCM placing --------------------------------------------------------

EXTERN uint16_t ADC_Data0[BSIZE];
EXTERN uint16_t ADC_Data1[BSIZE];
EXTERN float32_t SamplingRate, AudioRate;

#pragma pack(16)
EXTERN float ADC_Rdata[BSIZE];
EXTERN float ADC_Idata[BSIZE];
EXTERN float IQdata[BSIZE*2];             // IQdata  is a complex signal
EXTERN float fCbase[FFTLEN*2];            // fCbase  is a complex signal
EXTERN float tmpSamp[BSIZE*2+12];         // tmpSamp is a complex signal
EXTERN float tmpGraph[BSIZE*2+12];
EXTERN float LO_R[BSIZE], LO_I[BSIZE];    // LO is a complex signal
EXTERN float fAudio[BSIZE];
EXTERN short AudioOut0[BSIZE];
EXTERN short AudioOut1[BSIZE];

EXTERN float FIRstate1R[NUMFIRCOEFS + BSIZE*4 - 1];
EXTERN float FIRstate1I[NUMFIRCOEFS + BSIZE*4 - 1];
EXTERN Agctype agc[4];
EXTERN Bwidth  bw[4];
EXTERN Presets psets[MAXPRESETS];

EXTERN arm_status arc;
EXTERN arm_fir_decimate_instance_f32 SfirR;
EXTERN arm_fir_decimate_instance_f32 SfirI;

EXTERN uint16_t *pR;

EXTERN float     volume, oldvol, Qfactor, a1, a2, b0, cwpitch, audiotmp,
	               AgcThreshold, AGC_decay[2], LOfreq, mean, meanavg, Decay[4];
EXTERN uint16_t  Hangcount[2], AMindex, LSBindex, USBindex, CWindex, Hcount[4], count, old_count;
EXTERN Mode      currentmode;
EXTERN Scale      currentscale;
EXTERN float32_t SamplingRate, AudioRate;

EXTERN uint32_t  os_time, Fstep;
EXTERN __IO uint32_t uwTick;

EXTERN WM_HWIN   hWin, hItem;
EXTERN u8        Muted;
EXTERN u8        Spectogram;

extern int bar;
extern float foo;
extern int fooint;
extern int scaling_factor;
extern float32_t Output[1024];
EXTERN char      msg[32];

EXTERN int btn_group, step; //rotary
EXTERN int currentbw;
EXTERN int curmode;
EXTERN int maxmode;
EXTERN int curscale;
EXTERN int maxscale;


#define RECOMMENDED_MEMORY (1024L * 20)
#define GRID_DIST_X      	25
#define GRID_DIST_Y      	10

EXTERN WM_MESSAGE *GlobalMsgPtr;
#ifndef   U8
  #define U8  unsigned char
#endif
#ifndef   U16
  #define U16 unsigned short
#endif
#ifndef   U32
  #define U32 unsigned long
#endif
#ifndef   I8
  #define I8  signed char
#endif
#ifndef   I16
  #define I16 signed short
#endif
#ifndef   I32
  #define I32 signed long
#endif

#endif /* __GLOBALS_H */
