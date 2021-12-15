/**
 * \file            func_string.h
 * \brief           Functions that manipulate strings and texts.
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


#include "typedef.h"
#include "structs_gui.h"



/* -------------------  FUNCTIONS TO OPERATE WITH STRINGS --------------------------------- */

void my_strcpy(u8 *target, const u8 *source) ;
    
void my_strcpy_ltd_number(u8 *target, const u8 *source, u8 max_num_char) ;

void my_strcpy_1line(u8 *target, const u8 *source);
    
_Bool str_equal(const u8* cad1, const u8* cad2, u8 num_char) ;
	
u8 *my_strcat(const u8 *cad1, const u8 *cad2) ;
 
u8 my_itoa(u8 number, u8 cad[], _Bool with_trailing_zeros) ;
    

/* ------------- ASSIGNING STRINGS WITH MATCH INFO ------------------------ */

u8* get_string_games(void) ;
    
u8* get_string_points(void) ;
    
u8* get_text_for_the_marker(situation_t *situation) ;
	
u8 * seconds_2_string_minutes_seconds(u16 tot_seconds) ;
	
u8 get_number_of_lines(const u8 *string) ;

/* --------------- OBTAINING THE DIMENSIONS OF THE TEXT -------------------------------*/
    
u8 my_strlen_sl(const u8 *string) ;
   
u8 my_strlen_ml(const u8 *string, u8 *pos_terminator) ;
    
u8 str_width(const u8 *text, u8 font_sizeH) ;

/* ------------------------- DISPLAYING THE TEXT  ---------------------------------*/
    
void str_2_rect16(u16 x, u16 y, u8 *text, u8 fontsizeV, defined_from type_of_reference, rect16_t *rect) ;
    
void gui_str(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, u8 fontsizeV, 
    	defined_from type_of_reference, _Bool is_visible, _Bool is_enabled);
	
const u8* get_string_from_index(const u8 *source, u8 index) ;
    
/* --------------  OPERATIONS WITH THE NAME -------------------------------- */

void suppress_excessive_spaces(const u8* text_src, u8* text_dest) ;
	
u8 get_initial_char(u8* typed_name) ;
   
void get_truncated_name(const u8* typed_name, u8* truncated_name) ;

void assign_player_name(u8* typed_text, u8 player_from_1) ;
