/**
 * \file            structs_var_glob.h
 * \brief           Definition of structs global variables
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
#include "structs_gui.h"
#include "defines.h"

/* -------------------------   STRUCTS_VAR_GLOB.H  ---------------------------------------*/

typedef struct
{
    u16 colours_background[8];
    u16 colours_text[8];

    _Bool fast_start ;
    u8 name_typed_for_player[2][MAX_NUM_CHAR_IN_TEXTBOX+1];
    u8 name_shown_for_player[2][MAX_NAME_SIZE+1];
    u8 name_initial_char [2];

    _Bool is_left_handed[2] ;
    s8 colour_index[2] ;
    _Bool player_is_defined[2] ;

    u16 seconds_warmup ;
    u16 seconds_break ;

    _Bool pannel_is_inverted;

    u8 games_to_win_the_match;
    u8 games_for_player[2];
   
    u8 points_total_for_player[2][6];   // index 0 is reserved
                                        // index from 1 to 6 is the played game
    u8 winner_of_match;
    u8 winner_of_previous_game;
}var_glob_t;

typedef struct
{
    _Bool socket_is_set;
    u8 *address;
    u8 *name;
} bluetooth_t;

typedef struct
{
    _Bool direct_access;

    u8 active_window; 

    u8 procedence_window;

    void (*manage_specific_timer)(u32 ellapsed_ms);

    void (* pmanage_Pressed_textbox)(s8 ind_textbox);

    button_t *buttons;
    u8 num_buttons;
          
    button_t buttons_popup[MAX_NUM_BUTTONS_POPUP];
    u8  num_buttons_popup;

    checkbox_t *checkboxes;
    u8  num_checkboxes;

    group_radiobutton_t *radio_but;
    u8  num_groups_radio_but;

    region_t *regions;
    u8  num_regions;
	 
    label_t *labels;
    u8  num_labels;

    textview_t *textviews;
    u8  num_textviews;

    textbox_t *textboxes;
    u8  num_textboxes;

    warning_t message;

    _Bool timer_enabled;

}gui_t;

extern var_glob_t var_glob;

extern  gui_t gui;

extern bluetooth_t bluetooth;
