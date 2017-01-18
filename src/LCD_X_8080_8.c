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
File        : LCD_X_8080_8.c
Purpose     : Port routines 8080 interface, 8 bit data bus
----------------------------------------------------------------------
*/

#include "GUI.h"

#include "LCD_X_8080_8.h"
#include "main.h"
/*********************************************************************
*
*       Defines: Configuration
*
**********************************************************************
  Needs to be adapted to custom hardware.
*/
#define Chip_30600

/*********************************************************************
*
*       Defines: Common
*
**********************************************************************
  Usually, there is no need to modify these macros.
  It should be sufficient ot modify the low-level macros
  above.
*/

#define LCD_X_READ(c)     \
  LCD_SET_DIR_IN();       \
  LCD_CLR_CS();           \
  LCD_CLR_RD();           \
  c = LCD_DATA_IN;        \
  LCD_SET_RD();           \
  LCD_SET_CS();           \
  LCD_SET_DIR_OUT()

#define LCD_X_WRITE(data) \
  LCD_DATA_OUT = data;    \
  LCD_CLR_CS();           \
  LCD_CLR_WR();           \
  LCD_SET_WR();           \
  LCD_SET_CS()

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_X_8080_8_Init
*
* Purpose:
*   This routine should be called from your application program
*   to set port pins to their initial values.
*   
*/
void LCD_X_8080_8_Init(void) {
	   LCD_SET_CS();
	   LCD_CLR_RESET();;
	   GUI_X_Delay(20);
	   LCD_SET_RESET();
	   GUI_X_Delay(5);
	   }

/*********************************************************************
*
*       LCD_X_8080_8_Sync
*
* Purpose:
*   This routine can be used under certain conditions to synchronize
*   the communication with the display controller at startup.
*   
*/
void LCD_X_8080_8_Sync(void) {

}

/*********************************************************************
*
*       LCD_X_8080_8_Write00
*
* Purpose:
*   Write to controller, with A0 = 0
*/
void LCD_X_8080_8_Write00(unsigned char c) {
  LCD_CLR_A0();
  LCD_X_WRITE(c);
  }

/*********************************************************************
*
*       LCD_X_8080_8_Write01
*
* Purpose:
*   Write to controller, with A0 = 1
*/
void LCD_X_8080_8_Write01(unsigned char c) {
  LCD_SET_A0();
  LCD_X_WRITE(c);
}

/*********************************************************************
*
*       LCD_X_8080_8_WriteM00
*
* Purpose:
*   Write multiple bytes to controller, with A0 = 0
*/
void LCD_X_8080_8_WriteM00(unsigned char * pData, int NumBytes) {
  LCD_CLR_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
}

/*********************************************************************
*
*       LCD_X_8080_8_WriteM01
*
* Purpose:
*   Write multiple bytes to controller, with A0 = 1
*/
void LCD_X_8080_8_WriteM01(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
}

/*********************************************************************
*
*       LCD_X_8080_8_Read00
*
* Purpose:
*   Read from controller, with A0 = 0
*/
unsigned char LCD_X_8080_8_Read00(void) {
  unsigned char c;
  LCD_CLR_A0();
  LCD_X_READ(c);
  return c;
}

/*********************************************************************
*
*       LCD_X_8080_8_Read01
*
* Purpose:
*   Read from controller, with A0 = 1
*/
unsigned char LCD_X_8080_8_Read01(void) {
  unsigned char c;
  LCD_SET_A0();
  LCD_X_READ(c);
  return c;
}


/*********************************************************************
*
*       LCD_X_8080_8_ReadM00
*
* Purpose:
*   Read multiple bytes from controller, with A0 = 0
*/
void LCD_X_8080_8_ReadM00(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_READ(*pData);
    pData++;
  }
}

/*********************************************************************
*
*       LCD_X_8080_8_ReadM01
*
* Purpose:
*   Read multiple bytes from controller, with A0 = 1
*/
/* Read multiple bytes from controller, with A0 = 1 */
void LCD_X_8080_8_ReadM01(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_READ(*pData);
    pData++;
  }
}

/*************************** End of file ****************************/
