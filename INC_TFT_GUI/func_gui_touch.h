/**
 * \file            func_gui_touch.h
 * \brief           Functions that manage the touch screen, 
 *					and how buttons are pressed
 */

/*
 * Copyright (c) 2021 �ngel Gaspar Gonz�lez Rodr�guez
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
 * Author:      �ngel Gaspar Gonz�lez Rodr�guez
 */

#pragma once

#include "typedef.h"
#include "structs_gui.h"

/* ------------------- DETECTING WHEN A RESPONSIVE COMPONENT IS PRESSED -----------------*/

/* ------------------- BEHAVIOR WHEN THE TOUCH SCREEN IS PRESSED ------------------------*/

void manage_touch(point16 pt) ;  
void func_no_action(void);
    
#if !defined WIN32
_Bool is_screen_pressed(point16* pt) ;
#endif

/* -------------------------- BUTTON ------------------------------------*/

_Bool is_button_pressed(const button_t *button, point16 pt) ;
    
/* -------------------------- TEXTBOX ------------------------------------*/

_Bool is_textbox_pressed(const textbox_t *textbox, point16 pt) ;

/* -------------------------- CHECKBOX ------------------------------------*/

_Bool is_checkbox_pressed(const checkbox_t *checkbox, point16 pt) ;

/* -------------------------- RADIO BUTTON GROUP ------------------------------------*/

s8 is_radiobutton_pressed(const group_radiobutton_t *radiogroup, point16 pt) ;
   

