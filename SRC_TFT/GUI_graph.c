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

    #include "lcd.h"
    #include "string.h"

    #include "delay.h"
    #include "gui_font.h"
    #include "gui_graph.h"

    /*******************************************************************
     * @name       :void GUI_DrawPoint(u16 x,u16 y,u16 color)
     * @date       :2018-08-09 
     * @function   :draw a point in LCD screen
     * @parameters :x:the x coordinate of the point
                    y:the y coordinate of the point
                                    color:the color value of the point
     * @retvalue   :None
    ********************************************************************/
    void GUI_DrawPoint(u16 x,u16 y,u16 color)
    {
        LCD_SetCursor(x,y);
        Lcd_WritePixel(color); 
    }

    /*******************************************************************
     * @name       :void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
     * @date       :2018-08-09 
     * @function   :fill the specified area
     * @parameters :sx:the beginning x coordinate of the specified area
                    sy:the beginning y coordinate of the specified area
                                    ex:the ending x coordinate of the specified area
                                    ey:the ending y coordinate of the specified area
                                    color:the filled color value
     * @retvalue   :None
    ********************************************************************/
    void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
    {  	
        u16 i,j, width, height;		
        if (ex >= lcddev.width)
                ex = lcddev.width-1;
        width=ex-sx+1; 		
        height=ey-sy+1;		
        LCD_SetWindows(sx,sy,ex,ey);
        for(i=0;i<height;i++)
        {
            for(j=0;j<width;j++)
                Lcd_WritePixel(color);	 
        }
        LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
    }

    /*******************************************************************
     * @name       :void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
     * @date       :2018-08-09 
     * @function   :Draw a line between two points
     * @parameters :x1:the beginning x coordinate of the line
                    y1:the beginning y coordinate of the line
                                    x2:the ending x coordinate of the line
                                    y2:the ending y coordinate of the line
     * @retvalue   :None
    ********************************************************************/
    void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
    {
        u16 t; 
        int xerr=0,yerr=0,delta_x,delta_y,distance; 
        int incx,incy,uRow,uCol; 

        delta_x=x2-x1; 
        delta_y=y2-y1; 
        uRow=x1; 
        uCol=y1; 
        
        if(delta_x>0) {
            incx=1; 
        } else if (delta_x==0) {
             incx=0; 
        } else { 
            incx=-1;
            delta_x=-delta_x;
        } 
        if(delta_y>0) {
            incy=1; 
        } else if(delta_y==0) {
            incy=0;
        } else {
            incy=-1;
            delta_y=-delta_y;
        } 
        if( delta_x>delta_y) {
            distance=delta_x;
        } else {
            distance=delta_y; 
        }
            
        for(t=0;t<=distance+1;t++ )
        {  
            LCD_DrawPoint(uRow,uCol);
            xerr+=delta_x ; 
            yerr+=delta_y ; 
            if(xerr>distance) 
            { 
                xerr-=distance; 
                uRow+=incx; 
            } 
            if(yerr>distance) 
            { 
                yerr-=distance; 
                uCol+=incy; 
            } 
        }  
    } 

    /*****************************************************************************
     * @name       :void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
     * @date       :2018-08-09 
     * @function   :Draw a rectangle
     * @parameters :x1:the beginning x coordinate of the rectangle
                    y1:the beginning y coordinate of the rectangle
                                    x2:the ending x coordinate of the rectangle
                                    y2:the ending y coordinate of the rectangle
     * @retvalue   :None
    ******************************************************************************/
    void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
    {
        LCD_DrawLine(x1,y1,x2,y1);
        LCD_DrawLine(x1,y1,x1,y2);
        LCD_DrawLine(x1,y2,x2,y2);
        LCD_DrawLine(x2,y1,x2,y2);
    }  

    /*****************************************************************************
     * @name       :void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
     * @date       :2018-08-09 
     * @function   :Filled a rectangle
     * @parameters :x1:the beginning x coordinate of the filled rectangle
                    y1:the beginning y coordinate of the filled rectangle
                                    x2:the ending x coordinate of the filled rectangle
                                    y2:the ending y coordinate of the filled rectangle
     * @retvalue   :None
    ******************************************************************************/  
    void LCD_DrawFillRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
    {
        LCD_Fill(x1,y1,x2,y2, get_point_color());
    }
     
    /*****************************************************************************
     * @name       :void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
     * @date       :2018-08-09 
     * @function   :8 symmetry circle drawing algorithm (internal call)
     * @parameters :xc:the x coordinate of the Circular center 
                    yc:the y coordinate of the Circular center 
                                    x:the x coordinate relative to the Circular center 
                                    y:the y coordinate relative to the Circular center 
                                    c:the color value of the circle
     * @retvalue   :None
    ******************************************************************************/  
    void _draw_circle_8(int xc, int yc, int x, int y, u16 c)
    {
        GUI_DrawPoint(xc + x, yc + y, c);

        GUI_DrawPoint(xc - x, yc + y, c);

        GUI_DrawPoint(xc + x, yc - y, c);

        GUI_DrawPoint(xc - x, yc - y, c);

        GUI_DrawPoint(xc + y, yc + x, c);

        GUI_DrawPoint(xc - y, yc + x, c);

        GUI_DrawPoint(xc + y, yc - x, c);

        GUI_DrawPoint(xc - y, yc - x, c);
    }

    /*****************************************************************************
     * @name       :void gui_circle(int xc, int yc,u16 c,int r, int fill)
     * @date       :2018-08-09 
     * @function   :Draw a circle of specified size at a specified location
     * @parameters :xc:the x coordinate of the Circular center 
                    yc:the y coordinate of the Circular center 
                                    r:Circular radius
                                    fill:1-filling,0-no filling
     * @retvalue   :None
    ******************************************************************************/  
    void gui_circle(int xc, int yc,u16 c,int r, int fill)
    {
        int x = 0, y = r, yi, d;

        d = 3 - 2 * r;

        if (fill) 
        {
            while (x <= y) {
                for (yi = x; yi <= y; yi++)
                    _draw_circle_8(xc, yc, x, yi, c);

                if (d < 0) {
                    d = d + 4 * x + 6;
                } else {
                    d = d + 4 * (x - y) + 10;
                    y--;
                }
                x++;
            }
        } else {
            while (x <= y) {
                _draw_circle_8(xc, yc, x, y, c);
                if (d < 0) {
                    d = d + 4 * x + 6;
                } else {
                    d = d + 4 * (x - y) + 10;
                    y--;
                }
                x++;
            }
        }
    }

    /*****************************************************************************
     * @name       :void Draw_Triangle(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
     * @date       :2018-08-09 
     * @function   :Draw a triangle at a specified position
     * @parameters :x0:the beginning x coordinate of the triangular edge 
                    y0:the beginning y coordinate of the triangular edge 
                                    x1:the vertex x coordinate of the triangular
                                    y1:the vertex y coordinate of the triangular
                                    x2:the ending x coordinate of the triangular edge 
                                    y2:the ending y coordinate of the triangular edge 
     * @retvalue   :None
    ******************************************************************************/ 
    void Draw_Triangle(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
    {
        LCD_DrawLine(x0,y0,x1,y1);
        LCD_DrawLine(x1,y1,x2,y2);
        LCD_DrawLine(x2,y2,x0,y0);
    }

    static void _swap(u16 *a, u16 *b)
    {
        u16 tmp;
      tmp = *a;
        *a = *b;
        *b = tmp;
    }

    /*****************************************************************************
     * @name       :void Fill_Triangle(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
     * @date       :2018-08-09 
     * @function   :filling a triangle at a specified position
     * @parameters :x0:the beginning x coordinate of the triangular edge 
                    y0:the beginning y coordinate of the triangular edge 
                                    x1:the vertex x coordinate of the triangular
                                    y1:the vertex y coordinate of the triangular
                                    x2:the ending x coordinate of the triangular edge 
                                    y2:the ending y coordinate of the triangular edge 
     * @retvalue   :None
    ******************************************************************************/ 
    void Fill_Triangle(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2)
    {
        u16 a, b, y, last;
        int dx01, dy01, dx02, dy02, dx12, dy12;
        long sa = 0;
        long sb = 0;
        if (y0 > y1) {
        _swap(&y0,&y1); 
            _swap(&x0,&x1);
        } if (y1 > y2) {
        _swap(&y2,&y1); 
            _swap(&x2,&x1);
        } 
        if (y0 > y1) {
        _swap(&y0,&y1); 
            _swap(&x0,&x1);
        }
        if(y0 == y2) { 
            a = b = x0;
            if(x1 < a) {
                a = x1;
            } else if(x1 > b) {
                b = x1;
            }
            if(x2 < a) {
                a = x2;
            } else if(x2 > b) {
                b = x2;
            }
            LCD_Fill(a,y0,b,y0, get_point_color());
            return;
        }
        dx01 = x1 - x0;
        dy01 = y1 - y0;
        dx02 = x2 - x0;
        dy02 = y2 - y0;
        dx12 = x2 - x1;
        dy12 = y2 - y1;
        
        if(y1 == y2)
        {
            last = y1; 
        }
      else
        {
            last = y1-1; 
        }
        for(y=y0; y<=last; y++) 
        {
            a = x0 + sa / dy01;
            b = x0 + sb / dy02;
            sa += dx01;
        sb += dx02;
        if(a > b)
        {
                _swap(&a,&b);
            }
            LCD_Fill(a,y,b,y, get_point_color());
        }
        sa = dx12 * (y - y1);
        sb = dx02 * (y - y0);
        for(; y<=y2; y++) 
        {
            a = x1 + sa / dy12;
            b = x0 + sb / dy02;
            sa += dx12;
            sb += dx02;
            if(a > b)
            {
                _swap(&a,&b);
            }
            LCD_Fill(a,y,b,y, get_point_color());
        }
    }


     
    /*****************************************************************************
     * @name       :void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p)
     * @date       :2018-08-09 
     * @function   :Display a 16-bit BMP image
     * @parameters :x:the beginning x coordinate of the BMP image
                    y:the beginning y coordinate of the BMP image
                                    p:the start address of image array
     * @retvalue   :None
    ******************************************************************************/ 
    void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p) 
    {
        int i; 
        unsigned char picH,picL; 
        LCD_SetWindows(x,y,x+40-1,y+40-1);
        for(i=0;i<40*40;i++)
        {	
            picL=*(p+i*2);	
            picH=*(p+i*2+1);				
            Lcd_WritePixel(picH<<8|picL);  						
        }	
        LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);
    }
