/*////////////////////////////////////////////////////////////////////////////////	 
// This file is a copy, with slight modifications, from the same file obtained from 
// www.lcdwiki.com
// QDtech-TFT�G��?? for STM32 IO��?
// The modified code has been tested for a 3.5' touch TFT SPI 320x480 V2.0 and a STM32F103C8T6 BluePill
// xiao?@ShenZhen QDtech co.,LTD
// www.qdtft.com
// +86 0755-23594567 
// Copyright(C) �`�`����??�l��?�������q 2018-2028
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

#include "delay.h"
#include "sys_10x_4xx.h"

typedef struct
{
  volatile uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  volatile const uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;


#define SCS_BASE                        (0xE000E000UL) 
#define SysTick_BASE                    (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */


static u8  fac_us=0;

static u32 sLOAD, sVAL, sCTRL;
void Save_SysTick_values_for_LL_HAL(void)
{
	sLOAD = SysTick->LOAD;
	sVAL = SysTick->VAL;
	sCTRL = SysTick->CTRL;
}
void Load_SysTick_values_for_LL_HAL(void)
{
	SysTick->LOAD = sLOAD;
	SysTick->VAL = sVAL;
	SysTick->CTRL = sCTRL;
}
						    
void delay_us(u32 nus)
{		
    static _Bool prima_volta = 1;
    if (prima_volta) {
        prima_volta = 0;
        Save_SysTick_values_for_LL_HAL();
        u8 SYSCLK = SysTick->LOAD / 1000;
        fac_us=SYSCLK/8;        
    }
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 	  		 
	SysTick->VAL=0x00;       
	SysTick->CTRL=0x01 ;      
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));  
	Load_SysTick_values_for_LL_HAL();       
}










