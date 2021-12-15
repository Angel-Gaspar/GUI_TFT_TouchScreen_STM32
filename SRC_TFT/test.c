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


#include "lcd.h"
#include "delay.h"
#include "gui_font.h"
#include "gui_graph.h"
#include "test.h"
#include "touch.h"
//#include "key.h" 
//#include "led.h"
#include "pic.h"
#include "Hardware_definition.h"

//========================variable==========================//
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};
//=====================end of variable======================//

/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09 
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/ 
void DrawTestPage(u8 *str)
{
	//up
	LCD_Clear(WHITE);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
	//down
	LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	set_point_color(WHITE);
	Gui_StrCenter(0,2,WHITE,BLUE,str,16);
	Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,(u8*)"http://www.lcdwiki.com",16);

	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void main_test(void)
 * @date       :2018-08-09 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void main_test(void)
{
	DrawTestPage((u8*) "Main Test");	
	Gui_StrCenter(0,30,WHITE,BLACK,	(u8*) "English fonts",16);
	Gui_StrCenter(0,90,GREEN,BLUE,	(u8*) "3.5\" ILI9488 320X480",16);
	Gui_StrCenter(0,120,BRRED,BRRED,(u8*) "xiaoFeng@QDtech 2018-08-06",16);
	delay_ms(800);		

}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-09 
 * @function   :Color fill test(white,black,red,green,blue)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Color(void)
{
	DrawTestPage((u8*) "Test Color");
	LCD_Fill(0,0,lcddev.width,lcddev.height,WHITE);
	Show_Str(20,30,BLUE,YELLOW,(u8*) "BL Test",16);
	delay_ms(300);
	LCD_Fill(0,0,lcddev.width,lcddev.height,RED);
	Show_Str(20,30,BLUE,YELLOW,(u8*) "RED ",16);
	delay_ms(300);
	LCD_Fill(0,0,lcddev.width,lcddev.height,GREEN);
	Show_Str(20,30,BLUE,YELLOW,(u8*) "GREEN ",16);
	delay_ms(300);
	LCD_Fill(0,0,lcddev.width,lcddev.height,BLUE);
	Show_Str(20,30,RED,YELLOW,(u8*) "BLUE ",16);
	delay_ms(300);
}

/*****************************************************************************
 * @name       :void Test_FillRec(void)
 * @date       :2018-08-09 
 * @function   :Rectangular display and fill test
								Display red,green,blue,yellow,pink rectangular boxes in turn,
								1500 milliseconds later,
								Fill the rectangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_FillRec(void)
{
	u8 i=0;
	DrawTestPage((u8*) "Test_FillRec");
	LCD_Fill(1,20,lcddev.width-1,lcddev.height-20,BLUE);
	for (i=0; i<5; i++) 
	{
		set_point_color(ColorTab[i]);
		LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),
        lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	}
	delay_ms(500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	{
		set_point_color(ColorTab[i]);
		LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),
        lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	}
	delay_ms(500);
}

/*****************************************************************************
 * @name       :void Test_Circle(void)
 * @date       :2018-08-09 
 * @function   :circular display and fill test
								Display red,green,blue,yellow,pink circular boxes in turn,
								1500 milliseconds later,
								Fill the circular in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Circle(void)
{
	u8 i=0;
	DrawTestPage((u8*)"Plot and fill circles");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
	delay_ms(500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
	delay_ms(500);
}
/*****************************************************************************
 * @name       :void Test_Triangle(void)
 * @date       :2018-08-09 
 * @function   :triangle display and fill test
								Display red,green,blue,yellow,pink triangle boxes in turn,
								1500 milliseconds later,
								Fill the triangle in red,green,blue,yellow and pink in turn
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Triangle(void)
{
	u8 i=0;
	DrawTestPage((u8*)"Plot and fill triangles");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for(i=0;i<5;i++)
	{
		set_point_color(ColorTab[i]);
		Draw_Triangle(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),
        lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),
        lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
	}
	delay_ms(500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for(i=0;i<5;i++)
	{
		set_point_color(ColorTab[i]);
		Fill_Triangle(lcddev.width/2-80+(i*20),lcddev.height/2-20+(i*15),
        lcddev.width/2-50-1+(i*20),lcddev.height/2-20-52-1+(i*15),
        lcddev.width/2-20-1+(i*20),lcddev.height/2-20+(i*15));
	}
	delay_ms(500);
}

/*****************************************************************************
 * @name       :void English_Font_test(void)
 * @date       :2018-08-09 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void English_Font_test(void)
{
	DrawTestPage((u8*)"English letters and font sizes");
	Show_Str(10,30,BLUE,YELLOW,(u8*)"6x12:abcdefghijklmnpqrstuvwxyz0123456789",12);
	Show_Str(10,45,BLUE,YELLOW,(u8*)"6x12:ABCDEFGHIJKLMNPQRSTUVWXYZ0123456789",12);
	Show_Str(10,60,BLUE,YELLOW,(u8*)"6x12:~!@#$%^&*()_+{}:<>?/|-+.",12);
	Show_Str(10,80,BLUE,YELLOW,(u8*)"8x16:abcdefghijklmnopqrstuvwxyz0123456789",16);
	Show_Str(10,100,BLUE,YELLOW,(u8*)"8x16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",16);
	Show_Str(10,120,BLUE,YELLOW,(u8*)"8x16:~!@#$%^&*()_+{}:<>?/|-+.",16); 
	Show_Str(10,140,BLUE,YELLOW,(u8*)"8x24:AaEeIiOoUu",24); 
	Show_Str(10,180,BLUE,YELLOW,(u8*)"8x24:AaEeIiOoUu",36); 
	delay_ms(200);
}

/*****************************************************************************
 * @name       :void Chinese_Font_test(void)
 * @date       :2018-08-09 
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Chinese_Font_test(void)
{	
	DrawTestPage((u8*)"����6:������ʾ����");
	Show_Str(10,30,BLUE,YELLOW,(u8*)"16X16:ȫ�����Ӽ������޹�˾��ӭ��",16);
	Show_Str(10,50,BLUE,YELLOW,(u8*)"16X16:Welcomeȫ������",16);
	Show_Str(10,70,BLUE,YELLOW,(u8*)"24X24:���������Ĳ���",24);
	Show_Str(10,100,BLUE,YELLOW,(u8*)"32X32:�������",32);
	delay_ms(200);
}

/*****************************************************************************
 * @name       :void Pic_test(void)
 * @date       :2018-08-09 
 * @function   :picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Pic_test(void)
{
	DrawTestPage((u8*)"Simple image representation");
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(30,30,gImage_qq);
	Show_Str(30+12,75,BLUE,YELLOW,(u8*)"QQ",16);
	Gui_Drawbmp16(90,30,gImage_qq);
	Show_Str(90+12,75,BLUE,YELLOW,(u8*)"QQ",16);
	Gui_Drawbmp16(150,30,gImage_qq);
	Show_Str(150+12,75,BLUE,YELLOW,(u8*)"QQ",16);
	delay_ms(200);
}

/*****************************************************************************
 * @name       :void Rotate_Test(void)
 * @date       :2018-08-09 
 * @function   :rotate test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Rotate_Test(void)
{
	u8 i=0;
	u8 *Direction[4]={(u8*)"Rotation:0",(u8*)"Rotation:90",(u8*)"Rotation:180",(u8*)"Rotation:270"};
	
	for(i=0;i<4;i++)
	{
	LCD_direction(i*90);
	DrawTestPage((u8*)"Image Rotation Test");
	Show_Str(20,30,BLUE,YELLOW,Direction[i],16);
	Gui_Drawbmp16(30,50,gImage_qq);
	delay_ms(200);delay_ms(200);
	}
	LCD_direction(ROTATION_SCREEN);  // ROTATION_180
}

/*****************************************************************************
 * @name       :void Touch_Test(void)
 * @date       :2018-08-09 
 * @function   :touch test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Touch_Test(void)
{
	// caution: suppressed u8 key;
	u16 j=0;
	u16 colorTemp=0;
	TP_Init(); // Calibrate the touch screen or use typical values for offset and scaling
 	
	// caution: suppressed KEY_Init();
	// caution: suppressed LED_Init();
	
	DrawTestPage((u8*)" Touch Test ");
	LCD_ShowString(lcddev.width-24,0,16,(u8*)"RST");
	set_point_color(RED);
	LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,RED); 
		
	while(1) {
	 	// caution: suppressed key=KEY_Scan();
		TP_Scan(1);
		if(get_TP_status() & TP_PRES_DOWN) {	
            
		 	if(get_TP_x() <lcddev.width&& get_TP_y() <lcddev.height) {	
                
				if(get_TP_x() > (lcddev.width-24) && get_TP_y() <16) {
					DrawTestPage((u8*)"Use the pen to draw in the screen   ");
					LCD_ShowString(lcddev.width-24,0,16,(u8*)"RST");
					set_point_color(colorTemp);
					LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18, get_point_color()); 
				}
				else if((get_TP_x() >(lcddev.width-60)&&get_TP_x() <(lcddev.width-50+20))
                    && get_TP_y() <20) {
                    LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,ColorTab[j%5]); 
                    colorTemp = ColorTab[(j++)%5];
                    set_point_color(colorTemp);
                    delay_ms(10);
				}

				else 
					TP_Draw_Big_Point(get_TP_x() ,get_TP_y(), get_point_color());		  			   
			}
		}
		else 
			delay_ms(10);    
		/* caution: commented the following lines
		if(key==1)	
		{

			LCD_Clear(WHITE);
		    TP_Adjust();  
			TP_Save_Adjdata();	 
			DrawTestPage("����9:Touch����(��KEY0��У׼)  ");
			LCD_ShowString(lcddev.width-24,0,16,"RST",1);
			get_point_color()=colorTemp;
			LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18, get_point_color()); 
		} */
	}   
}




