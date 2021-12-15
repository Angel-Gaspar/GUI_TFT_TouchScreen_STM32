/**
 * \file            func_vs.cpp
 * \brief           Graphical functions for the Win32 project 
 *					to simulate the LCD functions
 *					It will not be necessary in the STM32 project
 */

/*
 * Copyright (c) 2021 Ángel Gaspar González Rodríguez
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:      Ángel Gaspar González Rodríguez
 */

#include "StdAfx.h"    
#include "WinGDI.h"
#include "func_vs.h"

#include "includes.h"

static HDC hDC;
HFONT hFont,hFontTmp;

u32 time_last_asynchr_press = 0;

/* -------------------  FUNCTIONS THAT WILL NOT BE USED BY STM32 ------------------------ */

/**
 * \brief       Convert from RGB16 to RGB24
 * \param[in]   colour: a colour expressed in RGB16
 * \return      the corresponding colour in 3 bytes
 */
COLORREF RGB16_2_RGB24(u16 colour) {
    WORD red_mask = 0xF800;
    WORD green_mask = 0x7E0;
    WORD blue_mask = 0x1F;
    BYTE r = (colour & red_mask) >> 11;
    BYTE g = (colour & green_mask) >> 5;
    BYTE b = (colour & blue_mask);
    COLORREF rgb24 = RGB(r*8,g*4,b*8);
    return rgb24;
}

/**
 * \brief       Store the handle to the device context
 * \param[in]   in_hDC: the handle to the device context
 * \return      none
 */
void set_hDC(HDC in_hDC) {
    hDC = in_hDC;
    // SetBkMode(hDC,TRANSPARENT);
}

/**
 * \brief       Set the font size and its colour
 * \param[in]   fontsize
 * \param[in]   colour: text colour in RGB24
 * \return      none
 */
void change_font(u8 fontsize, COLORREF colour) {
    // FW_BOLD FW_NORMAL
    SetTextColor(hDC, colour);
    fontsize = (u8) (fontsize * 1.9); // resize the fontsize
    hFont=CreateFont(fontsize,0,0,0,FW_NORMAL,0,0,0,0,0,0,2,FIXED_PITCH,TEXT("Elite"));
    hFontTmp = (HFONT) SelectObject(hDC,hFont);
}

/**
 * \brief       Draw a line with a specified colour
 * \param[in]   x0, y0: coordinates of the starting point
 * \param[in]   x1, y1: coordinates of the ending point
 * \param[in]   colour: line colour in RGB16
 * \return      none
 */
void draw_line(u16 x0, u16 y0, u16 x1, u16 y1, u16 colour) { 
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255,255,255));;
    SelectObject(hDC, pen);
    MoveToEx(hDC, x0, y0, (LPPOINT) NULL);
    LineTo(hDC, x1, y1);
}
/**
 * \brief       Plot the rectangle (filled or contour) given by its vertices
 * \param[in]   rect: pointer to the instance of the rectangle
 * \param[in]   colour_fill: color of contour and, in case, the filling
 * \param[in]   fill: 1 if the rectangle is to be filled; 0, only contour
 * \param[in]   is_visible: if 0, it will not be drawn
 * \param[in]   is_enabled: if 0, it will be plotted in gray
  * \return      none
 */
void draw_rectangle_from_vertices(rect16_t *rect, u16 colour_fill, _Bool fill, 
	_Bool is_visible, _Bool is_enabled) {
    if (is_visible == INVISIBLE)
        return;

    if (is_enabled == DISABLED)
        colour_fill = COLOUR_FILL_DISABLED;

    COLORREF colour24 = RGB16_2_RGB24(colour_fill);
    HPEN pen = CreatePen(PS_SOLID, 1, colour24);
    SelectObject(hDC, pen);
        
    HGDIOBJ hobject_brush;
    if (fill)
    {
        HBRUSH brush = CreateSolidBrush(colour24);
        hobject_brush = SelectObject(hDC, brush); 
    }
    else
    {
        hobject_brush = SelectObject( hDC, GetStockObject( NULL_BRUSH ) );
    }
    Rectangle(hDC, rect->left, rect->top, rect->right, rect->bottom);
    
    DeleteObject(SelectObject(hDC, hobject_brush));
}

/**
 * \brief       Display a text (only one line)
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \param[in]   inflation: amount to inflate the rectangle (if positive) or deflate it (if negative)
 * \return      none
 */
void display_1line_text(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, 	size_t fontsizev, _Bool is_visible, _Bool is_enabled) {    
    if (is_visible == INVISIBLE)
        return;
    if (is_enabled == DISABLED) {
        fc = COLOUR_TEXT_DISABLED;
        bc = fc;
    }

    size_t num_char = my_strlen_sl(str);

    change_font(V2H(fontsizev), RGB16_2_RGB24(fc));
    // HGDIOBJ hobject_brush;
    
    if (fc == bc)  {
        // hobject_brush = SelectObject( hDC, GetStockObject( NULL_BRUSH ) );
        SetBkMode(hDC,TRANSPARENT);

    }  else {
		COLORREF back_colour = RGB16_2_RGB24(bc);
		SetBkColor(hDC, back_colour);
        // HBRUSH brush = CreateSolidBrush(back_colour);
        //hobject_brush = SelectObject(hDC, brush); 
        SetBkMode(hDC,OPAQUE);
    }

    TextOut(hDC, x, y-2, (LPCSTR) str, num_char);
    
    DeleteObject(SelectObject(hDC,hFontTmp));
    
    //if (fc != bc)
    //    DeleteObject(SelectObject(hDC, hobject_brush));
}

/**
 * \brief       Detects if the left button of the mouse was pressed
 * \param[in]   pt16 (by reference): coordinates of the position where the touch screen was pressed
 * \return      1 if the touch screen was pressed; 0 otherwise
 */
_Bool is_mouseLB_pressed_asynchronous(point16* pt16) {
    SHORT state =
		GetAsyncKeyState(VK_LBUTTON);
	if (state == 0)
	{
        return 0;
    }
	
    POINT pt;
    LPPOINT lpPoint = &pt;
    GetCursorPos(lpPoint);    
    
    const u16 off_x = 10;
    const u16 off_y = 50;
    pt.x -= X_ORG + off_x;
    pt.y -= Y_ORG + off_y;
    
    pt16->x = (s16) pt.x;
    pt16->y = (s16) pt.y;

	if (pt16->x > LCD_W || pt16->y > LCD_H)
		return 0;
	if (pt16->x < 0 || pt16->y < 0)
		return 0;

	time_last_asynchr_press = get_milliseconds();

    return 1;
}

   
