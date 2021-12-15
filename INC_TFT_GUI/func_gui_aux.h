/**
 * \file            func_gui_aux.h
 * \brief           Definition of structs for the graphical components of the gui
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

#pragma once

#include <stdlib.h>

#include "typedef.h"
#if defined WIN32
#include <WinDef.h>
#endif

#include "structs_gui.h"

/* ------------------- OPERATIONS WITH RECTANGLES ---------------------------------------------*/

void Position_2_Position_left_top(u16 x_ref, u16 y_ref, u16 width, u16 height, u16 *left, u16 *top, defined_from type_of_reference) ;

void enclose_rectangle(rect16_t *rect);

point16 get_central_point_of_rectangle(rect16_t *rect16) ;

point16 get_central_point_of_region(region_t *region) ;

/* ------------------- TRANSFORMATIONS BETWEEN RECTANGLES ----------------------------------------------*/

void transf_region_2_vertices(const region_t *rect,  u16 *left, u16 *top, u16 *right, u16*bottom, defined_from type_of_reference) ;

void transf_vertices_2_rect16(u16 x, u16 y, u16 width, u16 height, defined_from type_of_reference, rect16_t *rectangle) ;

void transf_region_2_rect16(const region_t *rect, rect16_t* rectangle) ;


/* ------------------- OBTAINING THE BOUNDING BOX OF COMPONENTS ----------------------------------------------*/

point16 get_bounding_rect_from_radio_button(const group_radiobutton_t *rb, u8 index, rect16_t *rect) ;

point16 get_bounding_rect_from_group_radio_button(const group_radiobutton_t *rb, rect16_t *rect) ;

point16 get_bounding_rect_from_checkbox(const checkbox_t *cb,  rect16_t *rect, _Bool only_the_square) ;

point16 get_bounding_rect_from_button(const button_t *bt,  rect16_t *rect16) ;

point16 get_bounding_rect_from_textbox(const textbox_t *tb,  rect16_t *rect, defined_from type_of_reference) ;

void inflate(rect16_t* rect, s8 inflation) ;

/* ------------------- OTHER FUNCTIONS ----------------------------------------------*/

#if !defined WIN32
void display_1line_text(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, u8 fontsizev, _Bool is_visible, _Bool is_enabled) ;
#endif

#if !defined WIN32

void Set_lcdDev(void) ;
#endif


_Bool is_point_in_rectangle(point16 pt, const rect16_t* rect) ;

_Bool is_point_in_region(point16 pt, const region_t* region);

/* ------------------- DELETE FUNCTIONS ----------------------------------------------*/

u16 get_background_color(point16 pt);

void delete_str(u16 x, u16 y,  u8 prev_height, u16 prev_width, defined_from type_of_reference);

void delete_label(label_t *label) ;

void delete_textview(textview_t *textview) ;