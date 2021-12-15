/*////////////////////////////////////////////////////////////////////////////////	 
// This file is a copy, with slight modifications, from the same file obtained from 
// www.lcdwiki.com
// QDtech-TFT???? for STM32 IO??
// The modified code has been tested for a 3.5' touch TFT SPI 320x480 V2.0 and a STM32F103C8T6 BluePill
// xiao?@ShenZhen QDtech co.,LTD
// www.qdtft.com
// +86 0755-23594567 
// Copyright(C) ????????????? 2018-2028
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

#ifndef __TEST_H__
#define __TEST_H__

#include "typedefs_int.h"

void DrawTestPage(u8 *str);
void Test_Color(void);
void Test_FillRec(void);
void Test_Circle(void);
void Test_Triangle(void);
void English_Font_test(void);
void Chinese_Font_test(void);
void Pic_test(void);
void Load_Drow_Dialog(void);
void Touch_Test(void);
void main_test(void);
void Rotate_Test(void);
#endif
