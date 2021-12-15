/**
 * \file            gui_definplayer.h
 * \brief           GUI for the definition of colour and name
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

#include "typedef.h"  // for u8, u16...

/* -------------------- GUI CREATION ------------------------------*/

void set_window_definplayer(u8 in_player_from_1);

void operations_pre_initialize_defin_player(void) ;

void operations_post_initialize_defin_player(void) ;

/* -------------------- ACTIONS WHEN PRESSING THE BUTTONS AND TEXTBOX ------------------*/

void manage_pressed_textbox_defin_player(s8 pressed_textbox) ;
   
void action_change_colour(u8 index_colour) ;
	
void action_Red(void) ;
	
void action_Green(void) ;
   
void action_Yellow(void) ;
   
void action_Cyan(void) ;
   
void action_Blue(void) ;
   
void action_Magenta(void) ;
   
void action_White(void) ;
   
void action_return(void) ;
	
void action_serveside(void) ;


