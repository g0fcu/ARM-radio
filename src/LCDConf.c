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
File        : LCDConf.c
Purpose     : Sample display controller configuration

              Controller:     Novatek NT39122
              Display driver: GUIDRV_FlexColor
              Operation mode: 16bpp, 8 bit interface

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

#include "LCD_X_8080_8.h"
#include "GUIDRV_FlexColor.h"

#define XSIZE_PHYS 320
#define YSIZE_PHYS 240

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/
//

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation
//
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION GUI_SWAP_XY
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _InitController
*
* Purpose:
*   Initializes the display controller
*/
static void _InitController(void) {
  #ifndef WIN32



     LCD_SET_RESET();
     GUI_X_Delay(5);
     LCD_CLR_RESET();
     GUI_X_Delay(15);
     LCD_SET_RESET();
     GUI_X_Delay(15);

     LCD_SET_RD();
     LCD_SET_CS();
     LCD_SET_WR();

        LCD_X_8080_8_Write00(0xCB);
        LCD_X_8080_8_Write01(0x39);
        LCD_X_8080_8_Write01(0x2C);
        LCD_X_8080_8_Write01(0x00);
        LCD_X_8080_8_Write01(0x34);
        LCD_X_8080_8_Write01(0x02);

        LCD_X_8080_8_Write00(0xCF);
        LCD_X_8080_8_Write01(0x00);
        LCD_X_8080_8_Write01(0XC1);
        LCD_X_8080_8_Write01(0X30);

        LCD_X_8080_8_Write00(0xE8);
        LCD_X_8080_8_Write01(0x85);
        LCD_X_8080_8_Write01(0x00);
        LCD_X_8080_8_Write01(0x78);

        LCD_X_8080_8_Write00(0xEA);
        LCD_X_8080_8_Write01(0x00);
        LCD_X_8080_8_Write01(0x00);

        LCD_X_8080_8_Write00(0xED);
        LCD_X_8080_8_Write01(0x64);
        LCD_X_8080_8_Write01(0x03);
        LCD_X_8080_8_Write01(0X12);
        LCD_X_8080_8_Write01(0X81);

        LCD_X_8080_8_Write00(0xF7);
        LCD_X_8080_8_Write01(0x20);

        LCD_X_8080_8_Write00(0xC0);    //Power control
        LCD_X_8080_8_Write01(0x23);   //VRH[5:0]

        LCD_X_8080_8_Write00(0xC1);    //Power control
        LCD_X_8080_8_Write01(0x10);   //SAP[2:0];BT[3:0]

        LCD_X_8080_8_Write00(0xC5);    //VCM control
        LCD_X_8080_8_Write01(0x3e);   //Contrast
        LCD_X_8080_8_Write01(0x28);

        LCD_X_8080_8_Write00(0xC7);    //VCM control2
        LCD_X_8080_8_Write01(0x86);   //--

        LCD_X_8080_8_Write00(0x36);    // Memory Access Control
        LCD_X_8080_8_Write01(0x48);

        LCD_X_8080_8_Write00(0x3A);
        LCD_X_8080_8_Write01(0x55);

        LCD_X_8080_8_Write00(0xB1);
        LCD_X_8080_8_Write01(0x00);
        LCD_X_8080_8_Write01(0x18);

        LCD_X_8080_8_Write00(0xB6);    // Display Function Control
        LCD_X_8080_8_Write01(0x08);
        LCD_X_8080_8_Write01(0x82);
        LCD_X_8080_8_Write01(0x27);

        LCD_X_8080_8_Write00(0xF6);    // Data transfer endianess
        LCD_X_8080_8_Write01(0x0);
        LCD_X_8080_8_Write01(0b00110010);
        LCD_X_8080_8_Write01(0b00100000); // Code is compiled with Little Endian (default of ILI9341 is Big Endian)

        LCD_X_8080_8_Write00(0x11);    //Exit Sleep
        GUI_X_Delay(120);

        LCD_X_8080_8_Write00(0x29);    //Display on

        LCD_X_8080_8_Write00(0xbf);    // Backlight on???
        LCD_X_8080_8_Write01(0x0);

        LCD_X_8080_8_Write00(0x51);    // Display Brighest
        LCD_X_8080_8_Write01(0xff);

        LCD_X_8080_8_Write00(0x53);    //
        LCD_X_8080_8_Write01(0b00100100);

        LCD_CLR_WR();
  #endif
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  GUI_PORT_API PortAPI;
  CONFIG_FLEXCOLOR Config = {0};

  //
  // Set display driver and color conversion for 1st layer
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration
  //
  if (DISPLAY_ORIENTATION & GUI_SWAP_XY) {
    LCD_SetSizeEx (0, YSIZE_PHYS,   XSIZE_PHYS);
    LCD_SetVSizeEx(0, VYSIZE_PHYS,  VXSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS,   YSIZE_PHYS);
    LCD_SetVSizeEx(0, VXSIZE_PHYS,  VYSIZE_PHYS);
  }
  //
  // Function selection, hardware routines (PortAPI) and operation mode (bus, bpp and cache)
  //
  PortAPI.pfWrite8_A0  = LCD_X_8080_8_Write00;
  PortAPI.pfWrite8_A1  = LCD_X_8080_8_Write01;
  PortAPI.pfWriteM8_A0 = LCD_X_8080_8_WriteM00;
  PortAPI.pfWriteM8_A1 = LCD_X_8080_8_WriteM01;
  PortAPI.pfRead8_A0   = LCD_X_8080_8_Read00;
  PortAPI.pfRead8_A1   = LCD_X_8080_8_Read01;
  PortAPI.pfReadM8_A0  = LCD_X_8080_8_ReadM00;
  PortAPI.pfReadM8_A1  = LCD_X_8080_8_ReadM01;
  GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B8);
  //
  // Orientation
  //
  Config.Orientation = DISPLAY_ORIENTATION;
  if (DISPLAY_ORIENTATION & GUI_SWAP_XY) {
    if (DISPLAY_ORIENTATION & GUI_MIRROR_Y) {
      Config.FirstSEG = 60;
    }
  } else {
    if (DISPLAY_ORIENTATION & GUI_MIRROR_Y) {
      Config.FirstCOM = 60;
    }
  }
  GUIDRV_FlexColor_Config(pDevice, &Config);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  GUI_USE_PARA(LayerIndex);
  GUI_USE_PARA(pData);

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    _InitController();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
