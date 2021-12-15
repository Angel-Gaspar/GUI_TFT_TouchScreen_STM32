/**
 * \file            structs_gui.h
 * \brief           Definition of structs for the graphical components of the gui
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
#include "defines.h"

typedef struct
{
    defined_from type_of_reference; /* the same justification applies to the shape and to the text */
    u16		x;            
    u16		y;            
    u16		width;                  
    u16		height;              
    u16     colour;    
} region_t;

typedef struct
{
    u16		left;
	u16		top;
	u16		right;
	u16		bottom;    
} rect16_t;

typedef struct
{
    void (*action)(void);  // Function to be executed when clicking the button
    u8* text;
    region_t rect;
    u16 colour_text;
    u8 font_sizev;
    _Bool enabled;
    _Bool visible;
} button_t;


typedef struct
{
    void (*action)(void);   // func_no_action if no action defined
    u8* text;
    u16 left;               // x-coordinate of the left side of the checbox
	u16 top;                // y-coordinate of the top side of the checbox
    u8 text_at;
    u16 colour_text;
	// u16 colour_back;  /* Necessary when deselecting the previous option */
    u8 font_size;
    _Bool is_checked;
    _Bool enabled;
    _Bool visible;
} checkbox_t;

// typedef char* string;
typedef struct {
	void (*action)(void);  // NULL if no action defined
    u16 num_items; 
    u16 left;               // x-coordinate of the left side of the radio button
	u16 top;                // y-coordinate of the top side of the radio button
    // u8 sepV;
    u8 font_size;
    u16 colour_text;
    //u16 colour_but;
    // u16 colour_back;  /* Necessary when deselecting the previous option */
    s8 index_selected;
    u8 * texts; 
    _Bool enabled;
    _Bool visible;
} group_radiobutton_t;

/* The text of labels can be only replaced by another constant string */
typedef struct {
    defined_from type_of_reference;     /* the same justification applies to the form and to the text */
    u16 x;
    u16 y;
    u16 colour_text;
    // u16 colour_back; // The background colour is necessary when modifiying the text
    u8 font_size;
    const u8 *text;  // It must be assigned to a predefined string
    _Bool visible;
    
    u16 prev_width;
	u8 prev_height;
} label_t;

/* The text of textviews can be modified from the code. It can have more than one line */
typedef struct {
    defined_from type_of_reference;     /* the same justification applies to the form and to the text */
    u16 x;
    u16 y;
    u16 colour_text;
    // u16 colour_back; // The background colour is necessary when modifiying the text
    u8 font_size;

    _Bool visible; 
	u8 text[MAX_NUM_CHAR_IN_TEXTVIEW];  

    u16 prev_width;
	u8 prev_height;
} textview_t;

/* The text of textboxes can be modified by clicking in them (in some of them), or from the code */
/* Only one line */
typedef struct {
    defined_from type_of_reference;  /* the same justification applies to the form and to the text */
    u16 x;
    u16 y;
    u16 length;    
    u16 colour_text;
	u16 colour_back;
    u8 font_size;
    _Bool visible;
    _Bool enabled;
    u8 text[MAX_NUM_CHAR_IN_TEXTBOX];
} textbox_t;

typedef struct {
    u8 line1[30];
    u8 line2[30];
    u8 num_buttons;
    u8 text_butt[MAX_NUM_BUTTONS_POPUP][10];

    u8 selected_button;
} warning_t;
