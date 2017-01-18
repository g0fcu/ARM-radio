/*******************************************************************************

                   Presets.h module of the program ARM_Radio
						                          
						            Copyright 2015 by Alberto I2PHD, December 2015
						                                      
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

#include "main.h"
//---------------------------------------------------------------
// Preset stations
//---------------------------------------------------------------

static char pNames[MAXPRESETS][16] =
 {"User",  "MSF Anthorn", "DCF-77", "Navtex", "NDB", "Alpha", "WSPR-MF","WSPR-LF", "Allouis", "Radio Europe 1", "UK BBC 4","RTE", "5Live" };

static float pFreqs[MAXPRESETS] =
// {0.f, 17200.f, 18300.f, 60000.f, 77500.f, 147300.f, 153000.f, 162000.f, 183000.f, 198000.f,
 {0.f,  60000.f, 77500.f, 517000.f, 315000.f, 11000.f, 474200.f, 136000.f, 162000.f, 183000.f, 198000.f,252000.f, 909000.f};
static Mode pModes[MAXPRESETS] =
 {CW, CW, CW, USB, USB, USB, USB, USB, AM, AM, AM, AM};
 
static Bwidth pBws[MAXPRESETS] =
 {Narrow, Narrow, Narrow, Narrow, Wide, Wide, Wide, Wide, Narrow, Narrow,  Narrow, Wide};
 //--------------------------------------------------------------
