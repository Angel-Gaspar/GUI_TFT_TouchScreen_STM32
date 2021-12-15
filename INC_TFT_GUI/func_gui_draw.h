/**
 * \file            func_gui_draw.h
 * \brief           Auxiliary functions for the graphical interface
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
#include "func_gui_draw.h"
#include "structs_gui.h"

void initialize_active_window(void) ;    
   
/* -------------------------- BUTTONS ----------------------------------------------*/

void draw_buttons(void) ;
    
void draw_button(const button_t *button) ;

void delete_button(const button_t *button) ;

void update_button(const button_t *button) ;
 
void change_colours_of_button(button_t *button, u8 player_from_1) ; 

/* -------------------------- RADIO BUTTONS  -------------------------------------------*/

void draw_group_radio_buttons(void) ;
  
void draw_group_radio_button(const group_radiobutton_t* rb) ;    

void delete_group_radio_button(const group_radiobutton_t* rb) ; 

void update_group_radio_button(const group_radiobutton_t* rb) ; 
 
void draw_radio_but(const group_radiobutton_t *rb, u8 index, _Bool marked) ;   
 
/* -------------------------- CHECKBOXES  ----------------------------------------------*/

void draw_checkboxes(void);

void draw_checkbox(const checkbox_t *checkbox);

void delete_checkbox(const checkbox_t *checkbox);

void update_checkbox(const checkbox_t *checkbox) ;

/* -------------------------- RECTANGLES  ----------------------------------------------*/

void draw_regions(void) ;
  
#if !defined WIN32
void draw_rectangle_from_vertices(rect16_t *rect, u16 colour_fill, _Bool fill, _Bool is_visible, _Bool is_enabled) ;

#endif

void draw_region(region_t *rect, _Bool fill, _Bool is_visible, _Bool is_enabled) ;

/* -------------------------- LABELS  ----------------------------------------------*/

void display_labels(void) ;

void display_label(label_t *label) ;
 
/* -------------------------- TEXTVIEWS  ----------------------------------------------*/

void display_textviews(void) ;

void display_textview(textview_t *textview) ;
    
void replace_text_in_textview(textview_t *textview, const u8 *new_text, _Bool show_textview) ;
   
void replace_text_in_textview_with_number(textview_t *textview, u8 number, _Bool show_textview) ;
    
void replace_text_in_textview_with_text_and_number(textview_t *textview, u8 *new_text, u8 number, _Bool show_textview) ;
    
/* -------------------------- TEXTBOXES  ----------------------------------------------*/

void display_textboxes(void) ;
    
void display_textbox(textbox_t *textbox) ;
    
void replace_text_in_textbox(textbox_t *textbox, u8 *new_text, _Bool show_textbox) ;
    
void change_colours_of_textbox(textbox_t *textbox, u8 player_from_1) ; 

/* ---------------------------	WARNINGS and MESSAGES  -------------------------------------- */
	
void show_popup(warning_t *message) ;
    
u8	 show_popup_and_wait_for_answer(warning_t *message) ;
	
void fill_message(warning_t *message, const u8* line1, const u8* line2, 
	u8 num_buttons, const u8* but1, const u8* but2, const u8* but3) ;
