/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.26 - Graphical user interface for embedded applications **
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
File        : GUI_X_Touch.c
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/
#include "GUI.h"
//#include "stm32746g_discovery_ts.h"

#include "Board_Touch.h"

/*********************************************************************
*
*       Touch screen support (override default library functions)
*
*/

#define GUI_TOUCH_X_MIN 0x0000
#define GUI_TOUCH_X_MAX 0x0FFF
#define GUI_TOUCH_Y_MIN 0x0000
#define GUI_TOUCH_Y_MAX 0x0FFF

static unsigned int TouchOrientation;

static int TouchPhysX;
static int TouchPhysY;

static struct {
  int Min;
  int Max;
} TouchPhysLim[2] = {
  { GUI_TOUCH_X_MIN, GUI_TOUCH_X_MAX},
  { GUI_TOUCH_Y_MIN, GUI_TOUCH_Y_MAX} 
};

void GUI_TOUCH_Initialize (void) {
 // Touch_Initialize();
}

void GUI_TOUCH_SetOrientation (unsigned Orientation) {
  TouchOrientation = Orientation;
}

int  GUI_TOUCH_GetxPhys (void) {
  return TouchPhysX;
}

int  GUI_TOUCH_GetyPhys (void) {
  return TouchPhysY;
}

int  GUI_TOUCH_Calibrate (int Coord, int Log0, int Log1, int Phys0, int Phys1) {
  int size;

  if ((Log0 == Log1) || (Phys0 == Phys1)) return (1);

  switch (Coord) {
    case GUI_COORD_X:
      size = (TouchOrientation & GUI_SWAP_XY) ? LCD_GetYSize() : LCD_GetXSize();
      break;
    case GUI_COORD_Y:
      size = (TouchOrientation & GUI_SWAP_XY) ? LCD_GetXSize() : LCD_GetYSize();
      break;
    default:
      return (1);
  }

  TouchPhysLim[Coord].Min = Phys0 + ((0      - Log0)*(Phys1-Phys0))/(Log1-Log0);
  TouchPhysLim[Coord].Max = Phys0 + ((size-1 - Log0)*(Phys1-Phys0))/(Log1-Log0);

  return (0);
}

void GUI_TOUCH_GetCalData (int Coord, int* pMin, int* pMax) {
  *pMin = TouchPhysLim[Coord].Min;
  *pMax = TouchPhysLim[Coord].Max;
}

void GUI_TOUCH_Exec (void) {
  
  static U8   PressedOld = 0;
  static int  xOld = 0;
  static int  yOld = 0;
         int  x, y;
         int  xDiff, yDiff;
         int  xSize, ySize;
//  TS_StateTypeDef ts;
         TOUCH_STATE ts;
  char strx[3], stry[3];
 // Touch_GetState(&ts);
//  	if (ts.touchDetected > 0)
  if (ts.pressed)
  	{
  	  //GUI_SetFont(&GUI_Font20_1);
  	  //sprintf(strx, "%d", ts.touchX[0]);
  	  //GUI_DispStringAt(strx, 0,0);
  	  //sprintf(stry, "%d", ts.touchY[0]);
  	  //GUI_DispStringAt(stry, 0,20);
//  	  x = ts.touchX[0];
 // 	  y = ts.touchY[0];
	  x = ts.x;
	  y = ts.y;
  	  //while(1);
  	}
  /*BSP_TS_GetState(&touch_state);

  if (touch_state.pressed) {
    // Touch screen is pressed

    if (TouchOrientation & GUI_SWAP_XY) {
      TouchPhysX = touch_state.y;
      TouchPhysY = touch_state.x;
    } else {
      TouchPhysX = touch_state.x;
      TouchPhysY = touch_state.y;
    }*/

    // Convert touch values to pixels
    //x = TouchPhysX - TouchPhysLim[0].Min;
    //y = TouchPhysY - TouchPhysLim[1].Min;
         
   // if (TouchOrientation & GUI_SWAP_XY) {
   //   xSize = LCD_GetYSize();
   //   ySize = LCD_GetXSize(); 
   // } else {
      //xSize = LCD_GetXSize();
      //ySize = LCD_GetYSize(); 
   // }
    //x *= xSize - 1;
    //x /= TouchPhysLim[0].Max - TouchPhysLim[0].Min;
    //y *= ySize - 1;
    //y /= TouchPhysLim[1].Max - TouchPhysLim[1].Min;

    if (PressedOld == 1) {
      // Touch screen has already been pressed

      // Calculate difference between new and old position
      xDiff = (x > xOld) ? (x - xOld) : (xOld - x);
      yDiff = (y > yOld) ? (y - yOld) : (yOld - y);

      // Store state if new position differs significantly
      if (xDiff + yDiff > 2) {
        GUI_TOUCH_StoreState(x, y);
        xOld = x;
        yOld = y;
      }
    }
    else {
      // Touch screen was previously not pressed

      // Store state regardless of position
      GUI_TOUCH_StoreState(x, y);
      xOld = x;
      yOld = y;
      PressedOld = 1;
    }
  }
 // else {
    // Touch screen is not pressed

    // Store state if it was released recently
 //    PressedOld = 0;
 //     GUI_TOUCH_StoreState(-1, -1);
 //   }
//  }
//}

/*************************** End of file ****************************/
