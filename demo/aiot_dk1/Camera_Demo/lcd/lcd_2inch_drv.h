/********************************************************************************************************
 * @file    lcd_2inch_drv.h
 *
 * @brief   This is the source file for TL7518/TL721X/TL321X
 *
 * @author  Driver Group
 * @date    2024
 *
 * @par     Copyright (c) 2024, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#ifndef LCD_2IN_DRIVER_H
#define LCD_2IN_DRIVER_H

#define LCD_2IN_WIDTH  240 //LCD width
#define LCD_2IN_HEIGHT 320 //LCD height

#define LCD_2IN_CS_0   DEV_Digital_Write(DEV_CS_PIN, 0)
#define LCD_2IN_CS_1   DEV_Digital_Write(DEV_CS_PIN, 1)

#define LCD_2IN_RST_0  DEV_Digital_Write(DEV_RST_PIN, 0)
#define LCD_2IN_RST_1  DEV_Digital_Write(DEV_RST_PIN, 1)

#define LCD_2IN_DC_0   DEV_Digital_Write(DEV_DC_PIN, 0)
#define LCD_2IN_DC_1   DEV_Digital_Write(DEV_DC_PIN, 1)

typedef unsigned char  UBYTE;
typedef unsigned short UWORD;

void LCD_2IN_Init(void);
void LCD_2IN_Clear(UWORD Color);
void LCD_2IN_Display(int x, int y, UBYTE *image, int width, int height);
void LCD_2IN_DrawPaint(UWORD x, UWORD y, UWORD Color);
void LCD_2IN_SetBackLight(UWORD Value);

void LCD_2IN_WriteData_Word(UWORD da);
void LCD_2IN_SetCursor(UWORD X, UWORD Y);
void LCD_2IN_SetWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend);
void LCD_2IN_ClearWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD color);

unsigned int lcd_spi_init(void);
#endif
