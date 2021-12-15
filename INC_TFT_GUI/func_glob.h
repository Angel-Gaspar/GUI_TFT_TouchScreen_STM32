/**
 * \file            func_glob.h
 * \brief           Global and generic functions 
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
#include "structs_gui.h" // for gui components
/* -------------------------- INITIALIZING GLOBAL VARIABLES ----------------------------------------*/

void Initialize_Global_Variables(void) ;

void reset_numbers_GUI(void) ;

void start_match(void) ;

/* -------------------------- RETRIEVING INFORMATION FROM GLOBAL VARIABLES ---------------------------*/

_Bool is_feasible_extend_to_5_games(void) ;

_Bool some_player_won_the_match(void) ;

u8 get_played_games(void);

/* -------------------------- COLORS AND NAMES FOR THE PLAYERS ---------------------------*/

void get_colours(u8 player_from_1, u16*colour_backgnd, u16*colour_text) ;

void set_colours_and_name_to_button_player(button_t *bt, u8 player_from_1) ;


/*  ----------------------  FUNCTIONS RELATED TO THE SCORE EVOLUTION --------------------------*/

void start_a_new_result_evolution(void) ;

result_t* get_result(u8 index) ;

u16 get_num_results(void) ;

result_t* get_last_result(void) ;

_Bool remove_last_result(void) ;

void add_new_result(situation_t *situation) ;

void situation_2_result(situation_t *situation, result_t* result) ;

void result_2_situation(result_t* result, situation_t* situation) ;

_Bool recover_previous_result(situation_t *situation) ;

_Bool undo_and_recover_previous_result(situation_t *situation) ;

/*  -----------------------------  FUNCTIONS RELATED TO TIME -----------------------------*/

void manage_timer(void) ;

u32 get_milliseconds(void) ;

#if ! defined WIN32
void Sleep (u16 milliseconds);
#endif

void set_start_time(void) ;

u32 get_ellapsed_time_ms(void) ;




