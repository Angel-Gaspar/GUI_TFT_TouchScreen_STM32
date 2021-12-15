/**
 * \file            gui_match_conf.h
 * \brief           GUI for the initial configuration
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

#include "defines.h"
#include "typedef.h"


void set_window_match_configuration(void);

void operations_pre_initialize_configuration(void) ;

/* -------------------- ACTIONS WHEN PRESSING THE BUTTONS  ------------------*/

void action_player1(void) ;
   
void action_player2(void) ;
   
void action_warmup(void) ;
   
void action_connect_BT(void) ;
   
void action_disconnect_BT(void) ;
   
void action_recover_data(void) ;

void action_reset_scores(void) ;

/* -------------------- BEHAVIOUR OF COMPONENTS: VISIBLE AND ENABLE  ------------------*/

void set_buttons_Bluetooth(_Bool redraw) ;
	
void set_operative_buttons(_Bool redraw) ;

void set_names_and_colours(void) ;

void display_partial_scores(void) ;

/* -------------------- INTERACTIONS WITH RADIO BUTTONS  ------------------*/

void mark_radio_buttons(u8 opcion) ;
	
void read_radio_buttons(void) ;

/* ----------------------------- BLUETOOTH FUNCTIONS  ----------------------------*/

void match_bluetooth(void) ;
	
void disconnect_bluetooth(void) ;
	
void actions_when_bluetooth_is_connected(void) ;


