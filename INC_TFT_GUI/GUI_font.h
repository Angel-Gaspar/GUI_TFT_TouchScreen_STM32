/*////////////////////////////////////////////////////////////////////////////////	 
// This file is a copy, with slight modifications, from the same file obtained from 
// www.lcdwiki.com
// QDtech-TFT液晶驱动 for STM32 IO模拟
// The modified code has been tested for a 3.5' touch TFT SPI 320x480 V2.0 and a STM32F103C8T6 BluePill
// xiao冯@ShenZhen QDtech co.,LTD
// www.qdtft.com
// +86 0755-23594567 
// Copyright(C) 深圳市全动电子技术有限公司 2018-2028
// The rights are reserved for them

****************************************************************************************************
//=========================================Power Supply============================================//
//     Pin  LCD side		STM32side
//      1  	VCC       	DC5V/3.3V      
//      2 	GND       	GND          
//=======================================SPI for the LCD==========================================//
//     Pin  LCD side		STM32side
//    	6  	SDI (MOSI)	PB15	Output for STM
//    	7  	SCK         PB13  Output for STM
//    	9 	SDO (MISO)  PB14  Input for STM
 //=======================================CONTROL PINS FOR LCD==========================================//
//     Pin  LCD side		STM32side
//      8 LED					PB9     Output for STM     
//      5	D/C   			PB1			Output for STM
//      4	RST 				PA7 		Output for STM
//      3	CS          PA5    	Output for STM     
//========================================= TOUCH CONTROL PINS=========================================//
//     Pin  LCD side	STM32side
//      10 T_CLK    	PB9     Output for STM
//      11 T_CS       PB7     Output for STM
//      12 T_DIN      PB5			Output for STM
//      13 T_DO       PA15    Input for STM
//      14 T_IRQ      PA11    Input for STM
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING PROGRAMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, AUTHORS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY PROGRAMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/

#ifndef __GUI_FONT_H__
#define __GUI_FONT_H__

#include "typedefs_int.h"

void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 character, u8 size);
void LCD_ShowScaledChar(u16 x,u16 y,u16 fc, u16 bc, u8 character, u8 size);
void LCD_ShowScaledChar(u16 x,u16 y,u16 fc, u16 bc, u8 character, u8 size);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len,u8 size);
void LCD_ShowString(u16 x,u16 y,u8 size, u8 *p);
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s);

void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size);
void Show_Chinese_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size);
void Show_English_Str(u16 x, u16 y, u16 fc, u16 bc, const u8 *str,u8 size);

void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size);


#endif

