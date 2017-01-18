/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.30 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information

Licensor:                 SEGGER Software GmbH
Licensed to:              ARM Ltd
Licensed SEGGER software: emWin
License number:           GUI-00181
License model:            LES-SLA-20007, Agreement, effective since October 1st 2011 
Licensed product:         MDK-ARM Professional
Licensed platform:        ARM7/9, Cortex-M/R4
Licensed number of seats: -
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
//#include "stm32746g_discovery_ts.h"
#include "Board_Touch.h"
//#include "stm32_adafruit_lcd.h"

void GUI_TOUCH_X_ActivateX(void) {
}

void GUI_TOUCH_X_ActivateY(void) {
}

int  GUI_TOUCH_X_MeasureX(void) {
//	TS_StateTypeDef ts;
	TOUCH_STATE ts;
	char str[15];
	BSP_TS_GetState(&ts);
	//if (ts.touchDetected > 0)
	if (ts.pressed)
	{
	  //GUI_SetFont(&GUI_Font20_1);
	  //sprintf(str, "%d", ts.touchX[0]);
	  //GUI_DispStringAt(str, 0,0);
	  //while(1);
	}

//  return ts.touchX[0];
}

int  GUI_TOUCH_X_MeasureY(void) {
	TOUCH_STATE ts;
	char str[15];
	BSP_TS_GetState(&ts);
	if (ts.pressed)
		{
		  //GUI_SetFont(&GUI_Font20_1);
		  //sprintf(str, "%d", ts.touchY[0]);
		 // GUI_DispStringAt(str, 50,50);
		  //while(1);
		}

  //return ts.touchY[0];
}


