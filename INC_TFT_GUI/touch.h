/*////////////////////////////////////////////////////////////////////////////////
// This file is a copy, with slight modifications, from the same file obtained from 
// www.lcdwiki.com
// QDtech-TFTҺ������ for STM32 IOģ��
// The modified code has been tested for a 3.5' touch TFT SPI 320x480 V2.0 and a STM32F103C8T6 BluePill
// xiao��@ShenZhen QDtech co.,LTD
// www.qdtft.com
// +86 0755-23594567 
// Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
// The rights are reserved for them

****************************************************************************************************
//=========================================Power Supply============================================//
//     Pin  LCD side		STM32side
//      1  	VCC       	DC5V/3.3V
//      2 	GND       	GND
//=======================================SPI for the LCD==========================================//
//     Pin  LCD side	STM32side
//    	6	SDI(MOSI)   PB5   Output for STM
//      7 	SCK         PB3   Output for STM
//    	9	SDO(MISO)   PB4   Input for STM

 //=======================================CONTROL PINS FOR LCD==========================================//
//     Pin  LCD side	STM32side
//      8 LED			PB9     Output for STM
//      5	D/C   		PB1			Output for STM
//      4	RST 		PA7 		Output for STM
//      3	CS          PA5    	Output for STM
//========================================= TOUCH CONTROL PINS=========================================//
//     Pin  LCD side	STM32side
//      10 T_CLK    	PB9     Output for STM
//      11 T_CS       	PB7     Output for STM
//      12 T_DIN      	PB5			Output for STM
//      13 T_DO       	PA15    Input for STM
//      14 T_IRQ      	PA11    Input for STM
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
#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "GPIOS.h"

#include "pinout.h"
#include "typedef.h"

#define TP_PRES_DOWN 0x80   
#define TP_CATH_PRES 0x40  	  
										    
typedef struct
{
	u8 (*init)(void);			
	u8 (*scan)(u8);				
	void (*adjust)(void);		
	u16 x0;						
	u16 y0;
	u16 x; 						
	u16 y;						   	    
	u8  sta;					
							       			  							
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
	u8 touchtype;
}_m_tp_dev;


/*
void    TP_Write_Byte(u8 num);			
u16     TP_Read_AD(u8 CMD);						
u16     TP_Read_XOY(u8 xy);						
u8      TP_Read_XY(u16 *x,u16 *y);			
u8      TP_Read_XY2(u16 *x,u16 *y);		

void    TP_Drow_Touch_Point(u16 x,u16 y,u16 color);
*/

u8      get_TP_status(void);
u16     get_TP_x(void);
u16     get_TP_y(void);
void 	get_TP(point16 *pt);

void    TP_Draw_Big_Point(u16 x, u16 y, u16 color);	
_Bool 	get_touched_position(u8 adjusted_values);
u8      TP_Scan(_Bool adjusted_values);
void    TP_Save_Adjdata(void);				
u8      TP_Get_Adjdata(void);					
void    TP_Adjust(void);						
u8      TP_Init(void);							
																 
void    TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);
 		  
#endif








