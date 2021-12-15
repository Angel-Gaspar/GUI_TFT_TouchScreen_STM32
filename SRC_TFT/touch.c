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
#include "touch.h" 
#include "lcd.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include "mode_LL_HAL.h"

#include "gui_font.h"	    
#include "gui_graph.h"	

_m_tp_dev tp_dev=
{
	TP_Init,
	TP_Scan,
	TP_Adjust,
	0,
	0,
 	0,
	0,
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					

u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;

u8      get_TP_status(void) {return tp_dev.sta;}
u16     get_TP_x(void)      {return tp_dev.x;}
u16     get_TP_y(void)      {return tp_dev.y;}
void 	get_TP(point16 *pt) {
	pt->x = tp_dev.x;
	pt->y = tp_dev.y;
}


/*****************************************************************************
 * @name       :void TP_Write_Byte(u8 num)   
 * @date       :2018-08-09 
 * @function   :Write a byte data to the touch screen IC with SPI bus
 * @parameters :num:Data to be written
 * @retvalue   :None
******************************************************************************/  	 			    					   
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)
			T_DIN_Set;  
		else 
			T_DIN_Reset;   
		num<<=1;    
		T_CLK_Reset; 	 
		T_CLK_Set;		        
	}		 			    
}


/*****************************************************************************
 * @name       :u16 TP_Read_AD(u8 CMD)	  
 * @date       :2018-08-09 
 * @function   :Reading adc values from touch screen IC with SPI bus
 * @parameters :CMD:Read command,0xD0 for x,0x90 for y
 * @retvalue   :Read data
******************************************************************************/    
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	T_CLK_Reset;			 
	T_DIN_Reset; 	
	T_CS_Reset; 		
	TP_Write_Byte(CMD);
	delay_us(6);
	T_CLK_Reset; 	     	    
	delay_us(1);    	   
	T_CLK_Set;		  	    
	T_CLK_Reset; 	
	
	for(count=0;count<16;count++)
	{ 				  
		Num<<=1; 	 
		T_CLK_Reset;	 	    	   
		T_CLK_Set;
		if(T_DO)
			Num++; 		 
	}  	
	Num>>=4;   
	T_CS_Set;			 
	return(Num);  

}


#define READ_TIMES 5 	
#define LOST_VAL 1	  	
/*****************************************************************************
 * @name       :u16 TP_Read_XOY(u8 xy)  
 * @date       :2018-08-09 
 * @function   :Read the touch screen coordinates (x or y),
								Read the READ_TIMES secondary data in succession 
								and sort the data in ascending order,
								Then remove the lowest and highest number of LOST_VAL 
								and take the average
 * @parameters :xy:Read command(CMD_RDX/CMD_RDY)
 * @retvalue   :Read data
******************************************************************************/  
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
		buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)
		sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 

/*****************************************************************************
 * @name       :u8 TP_Read_XY(u16 *x,u16 *y)
 * @date       :2018-08-09 
 * @function   :Read touch screen x and y coordinates,
								The minimum value can not be less than 100
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
 * @retvalue   :0-fail,1-success
******************************************************************************/ 
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}

#define ERR_RANGE 50 
/*****************************************************************************
 * @name       :u8 TP_Read_XY2(u16 *x,u16 *y) 
 * @date       :2018-08-09 
 * @function   :Read the touch screen coordinates twice in a row, 
								and the deviation of these two times can not exceed ERR_RANGE, 
								satisfy the condition, then think the reading is correct, 
								otherwise the reading is wrong.
								This function can greatly improve the accuracy.
 * @parameters :x:Read x coordinate of the touch screen
				y:Read y coordinate of the touch screen
 * @retvalue   :0-fail,1-success
******************************************************************************/ 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
	flag=TP_Read_XY(&x1,&y1);   
	if(flag==0)
		return(0);
	flag=TP_Read_XY(&x2,&y2);	   
	if(flag==0)
		return(0);   
	if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))
		&&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
		{
				*x=(x1+x2)/2;
				*y=(y1+y2)/2;
				return 1;
		}
		else 
			return 0;	  
} 

/*****************************************************************************
 * @name       :void TP_Drow_Touch_Point(u16 x,u16 y,u16 color)
 * @date       :2018-08-09 
 * @function   :Draw a touch point,Used to calibrate							
 * @parameters :x:Read x coordinate of the touch screen
								y:Read y coordinate of the touch screen
								color:the color value of the touch point
 * @retvalue   :None
******************************************************************************/  
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color)
{	
//void gui_circle(int xc, int yc, u16 c, int r, int fill);
	set_point_color(color);
	LCD_DrawLine(x-12,y,x+13,y);
	LCD_DrawLine(x,y-12,x,y+13);
	LCD_DrawPoint(x+1,y+1);
	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x+1,y-1);
	LCD_DrawPoint(x-1,y-1);

	gui_circle(x, y, color, 6, 0);
}	

/*****************************************************************************
 * @name       :void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
 * @date       :2018-08-09 
 * @function   :Draw a big point(2*2)					
 * @parameters :x:Read x coordinate of the point
								y:Read y coordinate of the point
								color:the color value of the point
 * @retvalue   :None
******************************************************************************/   
void TP_Draw_Big_Point(u16 x, u16 y, u16 color)
{	    
	set_point_color(color);
	LCD_DrawPoint(x, y);
	LCD_DrawPoint(x+1, y);
	LCD_DrawPoint(x, y+1);
	LCD_DrawPoint(x+1, y+1);	 	  	
}	

/*****************************************************************************
 * @name       :u8 get_touched_position(u8 adjusted_values)
 * @date       :2021-10-29 
 * @function   :Get the position where screen is pressed
 * @parameters :tp: 0-screen coordinate, after applying offset and proportionality
                    1-Physical coordinates (for special occasions such as calibration)
 * @retvalue   :Current touch screen status,
					0-no success
					1-success
******************************************************************************/  					  
_Bool get_touched_position(u8 adjusted_values)
{			   
	_Bool success = TP_Read_XY2(&tp_dev.x,&tp_dev.y);
	if (adjusted_values && success) {
		tp_dev.x = tp_dev.xfac * tp_dev.x + tp_dev.xoff;
		tp_dev.y = tp_dev.yfac * tp_dev.y + tp_dev.yoff;
	}
	return success;
}

/*****************************************************************************
 * @name       :u8 TP_Scan(u8 adjusted_values)
 * @date       :2021-10-29
 * @function   :Scanning touch event
 * @parameters :adjusted_values: 1-screen coordinate, after applying offset and proportionality
                    0-Physical coordinates (for special occasions such as calibration)
 * @retvalue   :Current touch screen status,
					0-no touch
					1-touch
******************************************************************************/
u8 TP_Scan(_Bool adjusted_values)  // aka tp_dev.scan(
{
	if (T_IRQ==0)  // input IRQ signal, although this IRQ is not enabled
	{
		get_touched_position(adjusted_values);

		if((tp_dev.sta & TP_PRES_DOWN)==0) {
			tp_dev.sta = TP_PRES_DOWN|TP_CATH_PRES;  // TP_CATH_PRES used for adjusting
			tp_dev.x0 = tp_dev.x;
			tp_dev.y0 = tp_dev.y;
		}
	} else {
		if(tp_dev.sta & TP_PRES_DOWN) {
			tp_dev.sta &= ~(1<<7); // When pen is separated from touch screen
        }
        else {
			tp_dev.x0=0;
			tp_dev.y0=0;
			tp_dev.x=0xffff;
			tp_dev.y=0xffff;
		}
	}
	return tp_dev.sta & TP_PRES_DOWN;
}
// #define Using_AT24   // We are not going to use it.

  
//////////////////////////////////////////////////////////////////////////	 
//(RANGE:SAVE_ADDR_BASE~SAVE_ADDR_BASE+12)
#define SAVE_ADDR_BASE 40
/*****************************************************************************
 * @name       :void TP_Save_Adjdata(void)
 * @date       :2018-08-09 
 * @function   :Save calibration parameters		
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 										    
void TP_Save_Adjdata(void)
{
#ifdef Using_AT24	
	s32 temp;			 
  							  
	temp=tp_dev.xfac*100000000;  
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE,temp,4);   
	temp=tp_dev.yfac*100000000;
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,temp,4);

    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+8,tp_dev.xoff,2);		    

	AT24CXX_WriteLenByte(SAVE_ADDR_BASE+10,tp_dev.yoff,2);	
	
	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+12,tp_dev.touchtype);	
	temp=0X0A;
	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+13,temp); 
	#endif
}

/*****************************************************************************
 * @name       :u8 TP_Get_Adjdata(void)
 * @date       :2018-08-09 
 * @function   :Gets the calibration values stored in the EEPROM		
 * @parameters :None
 * @retvalue   :1-get the calibration values successfully
								0-get the calibration values unsuccessfully and Need to recalibrate
******************************************************************************/ 	
u8 TP_Get_Adjdata(void)
{			
#ifdef Using_AT24			  
	s32 tempfac;
	tempfac=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+13);	 
	if(tempfac==0X0A)	   
	{    												 
		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE,4);		   
		tp_dev.xfac=(float)tempfac/100000000;
		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);			          
		tp_dev.yfac=(float)tempfac/100000000;

		tp_dev.xoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+8,2);			   	  

		tp_dev.yoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+10,2);				 	  
 		tp_dev.touchtype=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+12);
		if(tp_dev.touchtype)
		{
			CMD_RDX=0X90;
			CMD_RDY=0XD0;	 
		}
		else				   
		{
			CMD_RDX=0XD0;
			CMD_RDY=0X90;	 
		}		 
		return 1;	 
	}
	#endif
	return 0;
	
}	
 
const u8* TP_REMIND_MSG_TBL=(u8*)"Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";

/*****************************************************************************
 * @name       :void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac)
 * @date       :2018-08-09 
 * @function   :Display calibration results	
 * @parameters :x0:the x coordinates of first calibration point
								y0:the y coordinates of first calibration point
								x1:the x coordinates of second calibration point
								y1:the y coordinates of second calibration point
								x2:the x coordinates of third calibration point
								y2:the y coordinates of third calibration point
								x3:the x coordinates of fourth calibration point
								y3:the y coordinates of fourth calibration point
								fac:calibration factor 
 * @retvalue   :None
******************************************************************************/ 	 					  
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac)
{	  
	set_point_color(RED);
	set_back_color(WHITE);
	LCD_ShowString(40,160,16,(u8*)"x1:");
 	LCD_ShowString(40+80,160,16,(u8*)"y1:");
 	LCD_ShowString(40,180,16,(u8*)"x2:");
 	LCD_ShowString(40+80,180, 16,(u8*)"y2:");
	LCD_ShowString(40,200, 16,(u8*)"x3:");
 	LCD_ShowString(40+80,200, 16,(u8*)"y3:");
	LCD_ShowString(40,220, 16,(u8*)"x4:");
 	LCD_ShowString(40+80,220, 16,(u8*)"y4:");  
 	LCD_ShowString(40,240, 16,(u8*)"fac is:");     
	LCD_ShowNum(40+24,160,x0,4,16);		
	LCD_ShowNum(40+24+80,160,y0,4,16);	
	LCD_ShowNum(40+24,180,x1,4,16);		
	LCD_ShowNum(40+24+80,180,y1,4,16);	
	LCD_ShowNum(40+24,200,x2,4,16);		
	LCD_ShowNum(40+24+80,200,y2,4,16);	
	LCD_ShowNum(40+24,220,x3,4,16);		
	LCD_ShowNum(40+24+80,220,y3,4,16);	
 	LCD_ShowNum(40+56,lcddev.width,fac,3,16); 	
}
u16 Get_Distance(u16 pos_temp1[2], u16 pos_temp2[2])
{
		u16	d1;
		u32			tem1=abs(pos_temp1[0]-pos_temp2[0]);//x1-x2
		u32			tem2=abs(pos_temp1[1]-pos_temp2[1]);//y1-y2
		tem1*=tem1;
		tem2*=tem2;
		d1 =sqrt(tem1+tem2);
		return d1;
	}

/*****************************************************************************
 * @name       :u8 TP_Get_Adjdata(void)
 * @date       :2018-08-09 
 * @function   :Calibration touch screen and Get 4 calibration parameters
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 		 
void TP_Adjust(void)
{								 
	u16 pos_temp[4][2];
	u8  cnt=0;	
	u16 d1,d2;

	float fac; 	
	u16 outtime=0;
 	cnt=0;				
	set_point_color(BLUE);
	set_back_color(WHITE);
	LCD_Clear(WHITE);
	set_point_color(RED);
	LCD_Clear(WHITE);	   
	set_point_color(BLACK);
	LCD_ShowString(10,40,16,(u8*)"Please use the stylus click the");
	LCD_ShowString(10,56,16,(u8*)"cross on the screen.The cross will");
	LCD_ShowString(10,72,16,(u8*)"always move until the screen ");
	LCD_ShowString(10,88,16,(u8*)"adjustment is completed.");

	TP_Drow_Touch_Point(20,20,RED); 
	tp_dev.sta=0;
	tp_dev.xfac=0; 
	while(1)
	{
		tp_dev.scan(0); //  TP_Scan
		if((tp_dev.sta&0xc0)==TP_CATH_PRES)//
		{	
			outtime=0;		
			tp_dev.sta&=~(1<<6);//
						   			   
			pos_temp[cnt][0]=tp_dev.x;
			pos_temp[cnt][1]=tp_dev.y;
			cnt++;	  
			switch(cnt)
			{			   
				case 1:						 
					TP_Drow_Touch_Point(20,20,WHITE);				
					TP_Drow_Touch_Point(lcddev.width-20,20,RED);	
					break;
				case 2:
 					TP_Drow_Touch_Point(lcddev.width-20,20,WHITE);	
					TP_Drow_Touch_Point(20,lcddev.height-20,RED);	
					break;
				case 3:
 					TP_Drow_Touch_Point(20,lcddev.height-20,WHITE);			
 					TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,RED);	
					break;
				case 4:	 
	    		    

					d1=Get_Distance(pos_temp[0], pos_temp[1]); 
					
					d2=Get_Distance(pos_temp[2], pos_temp[3]); 
					
					fac=(float)d1/d2;
					if(fac<0.95f||fac>1.05f||d1==0.0f||d2==0.0f)
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	
   	 					TP_Drow_Touch_Point(20,20,RED);							
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],
										pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);  
 						continue;
					}
					d1=Get_Distance(pos_temp[0], pos_temp[2]); 
					
					d2=Get_Distance(pos_temp[1], pos_temp[3]); 
					
					fac=(float)d1/d2;
					if(fac<0.95f||fac>1.05f)//���ϸ�
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);
   	 					TP_Drow_Touch_Point(20,20,RED);						
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],
									pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);
						continue;
					}
								   
					
					d1=Get_Distance(pos_temp[2], pos_temp[1]); 
					
					d2=Get_Distance(pos_temp[0], pos_temp[3]); 
					fac=(float)d1/d2;
					if(fac<0.95f||fac>1.05f)
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	
   	 					TP_Drow_Touch_Point(20,20,RED);							
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����   
						continue;
					}//��ȷ��
					//������
					tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]); 
					tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;
						  
					tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//yfac
					tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//yoff  
					if(abs(tp_dev.xfac)>2||abs(tp_dev.yfac)>2)
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	
   	 					TP_Drow_Touch_Point(20,20,RED);								
						LCD_ShowString(40,26, 16,(u8*)"TP Need readjust!");
						tp_dev.touchtype=!tp_dev.touchtype;
						if(tp_dev.touchtype)
						{
							CMD_RDX=0X90;
							CMD_RDY=0XD0;	 
						}else				 
						{
							CMD_RDX=0XD0;
							CMD_RDY=0X90;	 
						}			    
						continue;
					}		
					set_point_color(BLUE);
					LCD_Clear(WHITE);
					LCD_ShowString(35,110, 16,(u8*)"Touch Screen Adjust OK!");
					delay_ms(1000);
					TP_Save_Adjdata();  
 					LCD_Clear(WHITE);   
					return;			 
			}
		}
		delay_ms(10);
		outtime++;
		if(outtime>1000)
		{
			TP_Get_Adjdata();
			break;
	 	} 
 	}
}		

/*****************************************************************************
 * @name       :u8 TP_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization touch screen
 * @parameters :None
 * @retvalue   :0-no calibration
								1-Has been calibrated
******************************************************************************/  
u8 TP_Init(void)
{		
	// Inputs
	Configure_GPI(PORT_TDO, 	PIN_TDO);
	Configure_GPI(PORT_TIRQ, 	PIN_TIRQ);
	
	// Outputs
	Configure_GPO(PORT_TDIN, 	PIN_TDIN);
	Configure_GPO(PORT_TCLK, 	PIN_TCLK);
	Configure_GPO(PORT_TCS, 	PIN_TCS);
	
  	TP_Read_XY(&tp_dev.x,&tp_dev.y); 
    #ifdef Using_AT24	
        AT24CXX_Init();
    #endif

    if(TP_Get_Adjdata())
        return 0;
    else			   
    { 										    
        _Bool use_already_adjusted_values = 1;
        if (use_already_adjusted_values) 
        {  
            // These are the ones that I got. 
            // Maybe you could assign use_already_adjusted_values = 1 
            // and get you own values
            tp_dev.xfac = 0.0869565234;
            tp_dev.xoff = -14;
            tp_dev.yfac = -0.128617361;
            tp_dev.yoff = 504;
            return 0;
        }
        else
        {
            LCD_Clear(WHITE);
            TP_Adjust();  
            TP_Save_Adjdata();	 
        }
    }			
    TP_Get_Adjdata();	
    return 1; 									 
}



