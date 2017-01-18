/*******************************************************************************

                   FIRcoefs.h module of the program ARM_Radio
						                          
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

/*
  Coefficients for an equiripple FIR, Fs=111.60714 kHz, Fpass=8 kHz, Fstop=13 kHz, A=80 dB
	to be used before the decimation by 4 of the output of the R16, M4 CIC
	
	                                       Alberto I2PHD, June 2015
*/
float FIRcoefs[NUMFIRCOEFS] = 
{ 
0.00017789551662486736,
 0.00041040450128113212,
 0.00073564571611439266,
 0.0010288567261100756,
 0.0010932262399124643,
 0.00068102790709490837,
-0.0004289270055802503,
-0.0023236818651406581,
-0.0048507073861312269,
-0.0075593215529851923,
-0.0097324529011983477,
-0.010531001526389919,
-0.0092381283518636406,
-0.0055473909222043235,
 0.00019444056850832065,
 0.0068909705091059542,
 0.012822704762057578,
 0.016016481533045596,
 0.014801379079026093,
 0.0084175712824498886,
-0.0025017831741901836,
-0.015752677512255911,
-0.027802873657458295,
-0.034463933605740182,
-0.031871978947576575,
-0.017548806042311991,
 0.0087402114775642515,
 0.044592154434204508,
 0.085191505513169702,
 0.12415538783500346,
 0.15482622425492856,
 0.17171124432304663,
 0.17171124432304663,
 0.15482622425492856,
 0.12415538783500346,
 0.085191505513169702,
 0.044592154434204508,
 0.0087402114775642515,
-0.017548806042311991,
-0.031871978947576575,
-0.034463933605740182,
-0.027802873657458295,
-0.015752677512255911,
-0.0025017831741901836,
 0.0084175712824498886,
 0.014801379079026093,
 0.016016481533045596,
 0.012822704762057578,
 0.0068909705091059542,
 0.00019444056850832065,
-0.0055473909222043235,
-0.0092381283518636406,
-0.010531001526389919,
-0.0097324529011983477,
-0.0075593215529851923,
-0.0048507073861312269,
-0.0023236818651406581,
-0.0004289270055802503,
 0.00068102790709490837,
 0.0010932262399124643,
 0.0010288567261100756,
 0.00073564571611439266,
 0.00041040450128113212,
 0.00017789551662486736
 };
                    
