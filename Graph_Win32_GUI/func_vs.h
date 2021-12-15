#pragma once

#include "typedef.h"
#include "structs_gui.h"

COLORREF RGB16_2_RGB24(u16 colour) ;

void set_hDC(HDC in_hDC) ;

void change_font(u8 fontsize, COLORREF colour) ;
    
void draw_line(u16 x0, u16 y0, u16 x1, u16 y1, u16 colour) ; 

void draw_rectangle_from_vertices(rect16_t *rect, u16 colour_fill, 
	_Bool fill, _Bool is_visible, _Bool is_enabled) ;

void display_1line_text(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, size_t fontsizev, 
	_Bool is_visible, _Bool is_enabled) ;

#define is_screen_pressed(a) is_mouseLB_pressed_asynchronous(a)
_Bool is_mouseLB_pressed_asynchronous(point16* pt16) ;

