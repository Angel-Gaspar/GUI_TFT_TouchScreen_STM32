//////////////////////////////////////////////////////////////////////////////////	 
// This file is a copy, with slight modifications, from the same file obtained from 
// www.lcdwiki.com
// QDtech-TFTҺ������ for STM32 IOģ��
// The modified code has been tested for a 3.5' touch TFT SPI 320x480 V2.0 and a STM32F103C8T6 BluePill
// xiao��@ShenZhen QDtech co.,LTD
// www.qdtft.com
// +86 0755-23594567 
// Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
// The rights are reserved for them
/****************************************************************************************************
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

#ifndef __LCD_H
#define __LCD_H		

#include "stdlib.h"

#include "GPIOS.h"

#include "pinout.h"

typedef struct  
{										    
	u16 width;			
	u16 height;			
	u16 id;				  
	u8  dir;			  
	u16	 wramcmd;		
	u16  setxcmd;		
	u16  setycmd;		
}_lcd_dev; 	


extern _lcd_dev lcddev;	
////////////////////////////////////////////////////////////////////////	 


//////////////////////////////////////////////////////////////////////////////////	  

#define LCD_W 320
#define LCD_H 480


////////////////////////////////////////////////////////////////////


#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0xBC40 
#define BRRED 		0xFC07 
#define GRAY  		0x8430 


#define DARKBLUE    0x01CF	
#define LIGHTBLUE   0x7D7C	 
#define GRAYBLUE    0x5458 

 
#define LIGHTGREEN  0x841F 
#define LIGHTGRAY   0xEF5B 
#define LGRAY 		0xC618 

#define LGRAYBLUE   0xA651 
#define LBBLUE      0x2B12 

void    set_point_color(u16 new_point_color);
u16     get_point_color(void);

void    set_back_color(u16 new_back_color);
u16     get_back_color(void);

void    LCD_Init(void);	    															  

void    LCD_DisplayOn(void);
void    LCD_DisplayOff(void);
void    LCD_Clear(u16 Color);	 

void    LCD_SetCursor(u16 Xpos, u16 Ypos);
void    LCD_DrawPoint(u16 x,u16 y);
u16     LCD_ReadPoint(u16 x,u16 y); 
void    LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void    LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		
void    LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2);	
void    LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
void    LCD_direction(u16 direction );

u16     LCD_RD_DATA(void);							    
void    LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void    LCD_WR_DATA(u8 data);
u16     LCD_ReadReg(u8 LCD_Reg);
void    LCD_WriteRAM_Prepare(void);
void    LCD_WriteRAM(u16 RGB_Code);
u16     LCD_ReadRAM(void);		   
u16     LCD_BGR2RGB(u16 c);
void    LCD_SetParam(void);
void    Lcd_WritePixel(u16 Data);

				  		 
#endif  
	 
	 



