/**
 * \file            gui_score.h
 * \brief           GUI for the annotation of the score
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

/* -------------------------- GUI CREATION --------------------------------------*/

void set_window_score(void) ;    
   
void operations_pre_initialize_score(void) ;
   
void operations_post_initialize_score(void) ;

/* -------------------- CLICK ACTIONS Functions ------------------------------*/

void action_who_serves_at_the_beginning_of_match(void) ;
	
void action_show_times(void) ;
   
void action_annotation(u8 rally_winner) ;
    
void action_winplyr1(void) ;
   
void action_winplyr2(void) ;
   
void action_start_break(void) ;
   
void action_change_lf_rg(void) ;
	
void action_change_sets(void) ;
   
void action_special_actions(void) ;
	
void action_refresh(void) ;

/* -------------------- TIMER ----------------------------------------------*/

#if defined WIN32
static void simul_timer(void) ;
#endif

/* -------------------- AUXILIARY FUNCTIONS ----------------------------------------------*/

void update_situation(void) ;
   
void actions_new_game(void) ;

void actions_service_change(u8 winner) ;
	
u8 some_player_won_the_game(void) ;
   
u8 get_num_rallies(void) ;
