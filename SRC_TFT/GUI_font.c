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

// #define USE_CHINESE_FONT

#include "lcd.h"
#include "string.h"
#ifdef USE_CHINESE_FONT
#include "font_cn.h"
#endif
#include "font_en.h" 
#include "delay.h"
#include "gui_font.h"


/*****************************************************************************
 * @name       :void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size)
 * @date       :2018-08-09 
 * @function   :Display a single English character
 * @parameters :x:the beginning x coordinate of the Character display position
                y:the beginning y coordinate of the Character display position
								fc:the color value of display character
								bc:the background color of display character
								It assumes that if bc = fc, then the background is transparent
								num:the ascii code of display character(0~94)
								size:the size of display character
								
 * @retvalue   :None
******************************************************************************/ 
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 character, u8 size)
{  
    u8 temp;
    u8 pos,t;
	u16 colortemp = get_point_color();      
	_Bool transparent_background = (fc == bc);
	set_point_color(fc);              
		        
	u8 index = GET_INDEX(character);
	
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);

	for(pos=0;pos<size;pos++)
	{
		if(size==12)
			temp=asc2_1206[index][pos];
		else 
			temp=asc2_1608[index][pos];		
			
		for(t=0;t<size/2;t++) { 
			if (transparent_background)	{
				if(temp&0x01)
					LCD_DrawPoint(x+t,y+pos);   		
			} else {
				if(temp&0x01)
					Lcd_WritePixel(fc); 
				else 
					Lcd_WritePixel(bc); 							
			}			
			temp>>=1; 
		}		
	}	
	
	set_point_color(colortemp);	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   	   	 	  
}
/*****************************************************************************
 * @name       :void LCD_ShowScaledChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size)
 * @date       :2018-08-09 
 * @function   :Display a single English character with an arbitrary size
 * @parameters :x:the beginning x coordinate of the Character display position
                y:the beginning y coordinate of the Character display position
								fc:the color value of display character
								bc:the background color of display character
								It assumes that if bc = fc, then the background is transparent
								num:the ascii code of display character(0~94)
								size:the size of display character
								
 * @retvalue   :None
******************************************************************************/ 
void LCD_ShowScaledChar(u16 x,u16 y,u16 fc, u16 bc, u8 character, u8 size)
{
	const unsigned char *array ;
	int base = 12;
	u8 row, pixel_in_row;

	int scale = size / base;

  
	u16 colortemp=get_point_color();      
	_Bool transparent_background = (fc == bc);
	set_point_color(fc);              
		        
	u8 index = GET_INDEX(character);

	if (size % 16 == 0) 
		base = 16;
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);
	
	if(base==12)
		array = asc2_1206[index];
	else 
		array = asc2_1608[index];	
			
	for(row=0;row<base*scale;row++)
	{	
		unsigned char temp = array[row/scale];	
		for(pixel_in_row=0; pixel_in_row<base/2;pixel_in_row++)
		{ 
			if (transparent_background)
			{
				if(temp&0x01)
					for (int csx = 0; csx < scale; csx++)
						LCD_DrawPoint(x+pixel_in_row*scale+csx,	y+row);				
			}
			else
			{
				if(temp&0x01)
					for (int csx = 0; csx < scale; csx++)
						Lcd_WritePixel(fc); 
				else 
					for (int csx = 0; csx < scale; csx++)
						Lcd_WritePixel(bc); 					
			}			
			//if ( row % scale == (scale-1))
			temp>>=1; 
		}		
	}	
	
	set_point_color(colortemp);	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏    
}

/*****************************************************************************
 * @name       :void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p)
 * @date       :2018-08-09 
 * @function   :Display English string
 * @parameters :x:the beginning x coordinate of the English string
                y:the beginning y coordinate of the English string
								p:the start address of the English string
								size:the size of display character
								It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/   	  
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p)
{       
  
    /*while((*p<='~')&&(*p>=' '))
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        LCD_ShowChar(x,y, get_point_color(),get_back_color(),*p,size);
        x+=size/2;
        p++;
    } */ 
	Show_Str(x, y, get_point_color(), get_back_color(), p, size);
} 

/*****************************************************************************
 * @name       :u32 mypow(u8 m,u8 n)
 * @date       :2018-08-09 
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
                n:the power
 * @retvalue   :the nth power of m
******************************************************************************/ 
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

/*****************************************************************************
 * @name       :void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
 * @date       :2018-08-09 
 * @function   :Display number
 * @parameters :x:the beginning x coordinate of the number
                y:the beginning y coordinate of the number
								num:the number(0~4294967295)
								len:the length of the display number
								size:the size of display number
 * @retvalue   :None
******************************************************************************/  			 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y, get_point_color(),get_back_color(),' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y, get_point_color(),get_back_color(),temp+'0',size); 
	}
} 

#ifdef USE_CHINESE_FONT
/*****************************************************************************
 * @name       :void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
 * @date       :2018-08-09 
 * @function   :Display a single 16x16 Chinese character
 * @parameters :x:the beginning x coordinate of the Chinese character
                y:the beginning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//自动统计汉字数目
	
			
	for (k=0;k<HZnum;k++) 
	{
	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
	  { 	LCD_SetWindows(x,y,x+16-1,y+16-1);
		    for(i=0;i<16*2;i++)
		    {
				for(j=0;j<8;j++)
		    	{	
					if(bc!=fc) //非叠加方式
					{
						if(tfont16[k].Msk[i]&(0x80>>j))	Lcd_WritePixel(fc);
						else Lcd_WritePixel(bc);
					}
					else
					{
						set_point_color(fc);
						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//画一个点
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							break;
						}
					}

				}
				
			}	
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
} 

/*****************************************************************************
 * @name       :void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
 * @date       :2018-08-09 
 * @function   :Display a single 24x24 Chinese character
 * @parameters :x:the beginning x coordinate of the Chinese character
                y:the beginning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	
		
			for (k=0;k<HZnum;k++) 
			{
			  if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
			  { 	LCD_SetWindows(x,y,x+24-1,y+24-1);
				    for(i=0;i<24*3;i++)
				    {
							for(j=0;j<8;j++)
							{
								if(bc!=fc) 
								{
									if(tfont24[k].Msk[i]&(0x80>>j))	Lcd_WritePixel(fc);
									else Lcd_WritePixel(bc);
								}
							else
							{
								set_point_color(fc);
								if(tfont24[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//画一个点
								x++;
								if((x-x0)==24)
								{
									x=x0;
									y++;
									break;
								}
							}
						}
					}
					
					
				}				  	
				continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
			}

	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏  
}

/*****************************************************************************
 * @name       :void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
 * @date       :2018-08-09 
 * @function   :Display a single 32x32 Chinese character
 * @parameters :x:the beginning x coordinate of the Chinese character
                y:the beginning y coordinate of the Chinese character
								fc:the color value of Chinese character
								bc:the background color of Chinese character
								s:the start address of the Chinese character
								It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/ 
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
	u8 i,j;
	u16 k;
	u16 HZnum;
	u16 x0=x;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//自动统计汉字数目
	for (k=0;k<HZnum;k++) 
			{
			  if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
			  { 	LCD_SetWindows(x,y,x+32-1,y+32-1);
				    for(i=0;i<32*4;i++)
				    {
						for(j=0;j<8;j++)
				    	{
							if(bc!=fc) 
							{
								if(tfont32[k].Msk[i]&(0x80>>j))	Lcd_WritePixel(fc);
								else Lcd_WritePixel(bc);
							}
							else
							{
								set_point_color(fc);
								if(tfont32[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);
								x++;
								if((x-x0)==32)
								{
									x=x0;
									y++;
									break;
								}
							}
						}
					}
					
					
				}				  	
				continue;  
			}
	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
} 

/*****************************************************************************
 * @name       :_Bool Seem_Chinese_Char(u8 *str)
 * @date       :2021-09-30
 * @function   :Find out whether it is a chinese expresion or not
 * @parameters :str:the start address of the Chinese and English strings						
 * @retvalue   :None
******************************************************************************/
_Bool Seem_Chinese_Char(u8 *str)
{
	int cc = 0;
	int num_latin_char = 0;
	
	while(str[cc] != '\0')
	{
		if (str[cc] < 0x80 || IS_LOCAL_CHAR(str[cc]))
			num_latin_char++;
		cc ++;		
	}
	if (cc == 0) return 0;
	return ((float) num_latin_char / cc) < 0.9f;
}
#endif
/*****************************************************************************
 * @name       :void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
 * @date       :2018-08-09 
 * @function   :Display Chinese and English strings
 * @parameters :x:the beginning x coordinate of the Chinese and English strings
                y:the beginning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/	
void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
{		
    #ifdef USE_CHINESE_FONT
	if (Seem_Chinese_Char(str))
		Show_Chinese_Str(x, y, fc, bc, str, size);
	else
        #endif
		Show_English_Str(x, y, fc, bc, str, size);	
}

/*****************************************************************************
 * @name       :void Show_English_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
 * @date       :2018-08-09 
 * @function   :Display English strings
 * @parameters :x:the beginning x coordinate of the English strings
                y:the beginning y coordinate of theEnglish strings
                fc:the color value of English strings
                bc:the background color of English strings
                str:the start address of the English strings
                size:the size of English strings
                It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/	   		   
void Show_English_Str(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, u8 size)
{		
	u16 x0=x;							  	  
   
	while(*str != '\0' )
	{ 
			char charact = *str;
			if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
				return; 
			          
			if(charact==0x0D) // Carriage return
			{         
				y+=size;
				x=x0;
				str++; 
			}  
			else
			{
				if (size == 12 || size == 16)
					LCD_ShowChar(x,y,fc,bc,charact,size);
				else 
					LCD_ShowScaledChar(x,y,fc,bc,charact,size);
				x+=size/2; 
			} 
			str++; 
		}	 
}

#ifdef USE_CHINESE_FONT
/*****************************************************************************
 * @name       :void Show_Chinese_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
 * @date       :2018-08-09 
 * @function   :Display Chinese and English strings
 * @parameters :x:the beginning x coordinate of the Chinese and English strings
                y:the beginning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								It assumes that if bc = fc, then the background is transparent
								Can be improved
 * @retvalue   :None
******************************************************************************/	   		   
void Show_Chinese_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
{		
	u16 x0=x;							  	  
	u8 bHz=0;    
	while(*str!=0)
	{ 
		if(!bHz)
		{
			if(x>(lcddev.width-size/2)||y>(lcddev.height-size)) 
				return; 
			if(*str>0x80)
				bHz=1;
			else             
			{          
				if(*str==0x0D) // Carriage return
				{         
					y+=size;
					x=x0;
					str++; 
				}  
				else
				{
					int ssize = size > 16 ? 16 : size;
					LCD_ShowChar(x,y,fc,bc,*str,ssize);
					x+=ssize/2; 
				} 
				str++; 
			}
		}
		else
		{   
			if(x>(lcddev.width-size)||y>(lcddev.height-size)) 
				return;  
			bHz=0;  
			if(size==32)
				GUI_DrawFont32(x,y,fc,bc,str);	 	
			else if(size==24)
				GUI_DrawFont24(x,y,fc,bc,str);	
			else
				GUI_DrawFont16(x,y,fc,bc,str);
				
			str+=2; 
			x+=size;    
		}						 
	}   
}
#endif
/*****************************************************************************
 * @name       :void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
 * @date       :2018-08-09 
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the beginning x coordinate of the Chinese and English strings
                y:the beginning y coordinate of the Chinese and English strings
								fc:the color value of Chinese and English strings
								bc:the background color of Chinese and English strings
								str:the start address of the Chinese and English strings
								size:the size of Chinese and English strings
								It assumes that if bc = fc, then the background is transparent
 * @retvalue   :None
******************************************************************************/ 
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size)
{
	u16 len=strlen((const char *)str);
	u16 x1=(lcddev.width-len*8)/2;
	Show_Str(x1,y,fc,bc,str,size);
}
