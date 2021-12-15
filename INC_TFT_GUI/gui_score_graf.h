/**
 * \file            gui_score_graf.h
 * \brief           Auxiliary functions related to the component 
 *					behavior along the score annotation 
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

/* ------------ SERVE SIDE: DRAW THE SQUARE SHOWING THE SERVE SIDE -------------------------*/
void plot_serve_side(void) ;

/* ------------ UPDATE COMPONENTS: TEXTVIEWS and BUTTONS-------------------------------------*/

/* ------------ textviews -----------------------*/

void update_text_4_marker(_Bool re_draw) ;
	
void update_games(_Bool re_draw) ;
	
void update_time(u16 ellapsed_time_s, _Bool re_draw) ;

/* ------------ buttons -----------------------*/

void define_player_button(u8 player) ;

/* ------------ MANAGE THE SCORE EVOLUTIONS (THE CENTRAL REGION) ----------------------------*/

void clear_old_result(situation_t* situation) ;
	
void display_situation_in_central_band(situation_t* situation) ;
	
void display_result_in_central_band(result_t* res) ;

void display_complete_result_evolution(void) ;

/* ------------ TRANSLATE CURRENT SITUATION TO GUI ------------------------------------------*/

void current_situation_2_GUI(_Bool re_draw) ;

_Bool manage_first_service_of_match(_Bool re_draw) ;
	
void enable_after_starting_new_game_wo_drawing(_Bool game_started) ;
