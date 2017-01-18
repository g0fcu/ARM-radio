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
File        : LCD_X_8080_8.h
Purpose     : Interface definition:
              Port routines 8080 interface, 8 bit data bus
----------------------------------------------------------------------
*/
#include "main.h"
#ifndef LCD_X_8080_8_H
#define LCD_X_8080_8_H

#define LCD_CS_GPIO_PORT      GPIOE
#define LCD_RS_GPIO_PORT      GPIOE
#define LCD_WR_GPIO_PORT      GPIOE
#define LCD_RD_GPIO_PORT      GPIOE
#define LCD_RESET_GPIO_PORT   GPIOE

#define LCD_DATA_IN       GPIOC->IDR
#define LCD_DATA_OUT      GPIOC->ODR
#define LCD_SET_DIR_IN()  GPIOC->IDR = 0x0
#define LCD_SET_DIR_OUT() GPIOC->ODR = 0x0
#define LCD_DELAY(ms)     GUI_X_Delay(ms)

#define LCD_CS_PIN      GPIO_PIN_3
#define LCD_RS_PIN      GPIO_PIN_4
#define LCD_WR_PIN      GPIO_PIN_5
#define LCD_RD_PIN      GPIO_PIN_6
#define LCD_RST_PIN     GPIO_PIN_2

#define LCD_CLR_CS() HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_RESET)
#define LCD_CLR_A0() HAL_GPIO_WritePin(LCD_RS_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_RESET)
#define LCD_CLR_WR() HAL_GPIO_WritePin(LCD_WR_GPIO_PORT, LCD_WR_PIN, GPIO_PIN_RESET)
#define LCD_CLR_RD() HAL_GPIO_WritePin(LCD_RD_GPIO_PORT, LCD_RD_PIN, GPIO_PIN_RESET)
#define LCD_CLR_RESET() HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT, LCD_RST_PIN, GPIO_PIN_RESET)

#define LCD_SET_CS() HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_SET)
#define LCD_SET_A0() HAL_GPIO_WritePin(LCD_RS_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_SET)
#define LCD_SET_WR() HAL_GPIO_WritePin(LCD_WR_GPIO_PORT, LCD_WR_PIN, GPIO_PIN_SET)
#define LCD_SET_RD() HAL_GPIO_WritePin(LCD_RD_GPIO_PORT, LCD_RD_PIN, GPIO_PIN_SET)
#define LCD_SET_RESET() HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT, LCD_RST_PIN, GPIO_PIN_SET)

/*********************************************************************
*
*       Public routines
*/
void          LCD_X_8080_8_Init(void);
void          LCD_X_8080_8_Sync(void);
void          LCD_X_8080_8_Write00(unsigned char c);
void          LCD_X_8080_8_Write01(unsigned char c);
void          LCD_X_8080_8_WriteM01(unsigned char * pData, int NumBytes);
void          LCD_X_8080_8_WriteM00(unsigned char * pData, int NumBytes);
unsigned char LCD_X_8080_8_Read00(void);
unsigned char LCD_X_8080_8_Read01(void);
void          LCD_X_8080_8_ReadM00(unsigned char * pData, int NumBytes);
void          LCD_X_8080_8_ReadM01(unsigned char * pData, int NumBytes);

#endif /* LCD_X_8080_8_H */

/*************************** End of file ****************************/
