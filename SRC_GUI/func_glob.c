/**
 * \file            func_glob.c
 * \brief           Global and generic functions 
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

#include "func_glob.h"
#include "defines.h"
#include "structs_var_glob.h"  // for var_glob_t, gui_t and bluetooth_t
#include "macros.h"
#include "func_string.h"
#include "kstrings.h"

//#include "includes.h"

//#include "func_string.h"
//


var_glob_t var_glob;

gui_t gui;

bluetooth_t bluetooth;

static result_t results[MAX_NUM_RECORDED_RESULTS];
static u16 num_results_in_this_game;

/* -------------------------- INITIALIZING GLOBAL VARIABLES --------------------------------------- */

/**
 * \brief       Initialize global variables and assign default values in case of fast start         
 * \param[in]   None 
 * \return      None
 */
void Initialize_Global_Variables() {
	gui.procedence_window = GUI_START_APP;

    var_glob.fast_start = 1;
    var_glob.colours_background[0] = 0;
    var_glob.colours_text[0] = 0xFFFF;
    
    var_glob.colours_background[ind_RED] = RGB24_2_RGB16(255, 0, 0);
    var_glob.colours_text[ind_RED] = 0xFFFF;

    var_glob.colours_background[ind_GREEN] = RGB24_2_RGB16(0, 255, 0);
    var_glob.colours_text[ind_GREEN] = 0x0000;

    var_glob.colours_background[ind_YELLOW] = RGB24_2_RGB16(0xFF, 0xFF, 0x00);
    var_glob.colours_text[ind_YELLOW] = 0x0000;

    var_glob.colours_background[ind_BLUE] = RGB24_2_RGB16(0x40, 0x10, 0xFF);
    var_glob.colours_text[ind_BLUE] = 0xFFFF;

    var_glob.colours_background[ind_MAGENTA] = RGB24_2_RGB16(255, 0, 255);
    var_glob.colours_text[ind_MAGENTA] = 0x0000;

    var_glob.colours_background[ind_CYAN] = RGB24_2_RGB16(0x20, 0xE0, 0xFF);
    var_glob.colours_text[ind_CYAN] = 0x0000;

    var_glob.colours_background[ind_WHITE] = RGB24_2_RGB16(255, 255, 255);
    var_glob.colours_text[ind_WHITE] = 0x0000;
    
    for (u8 cp = 0; cp < 2; cp++)   {
        var_glob. colour_index[cp] = -1;
        var_glob.player_is_defined[cp] = 0;
        var_glob. games_for_player[cp] = 0;
    }
    for (u8 cj = 0; cj < 6; cj++)    {
        var_glob. points_total_for_player[0][cj] = 0;// porque el indice 0 se reserva
        var_glob. points_total_for_player[1][cj] = 0;// el �ndice es el game disputado
    }
    var_glob.seconds_warmup = 300;
    var_glob.seconds_break = 90;
    var_glob.games_to_win_the_match = 2;
    
    var_glob.winner_of_match = 0;
    var_glob.winner_of_previous_game = 0;

	assign_player_name(Kst_PLAYER1, 1);
	assign_player_name(Kst_PLAYER2, 2);

	if (var_glob.fast_start) {
		var_glob.colour_index[0] = 1;
		var_glob.colour_index[1] = 2;		

		var_glob.player_is_defined[0] = 1;
		var_glob.player_is_defined[1] = 1;

		assign_player_name((u8*)"O'Brian", 1);
		assign_player_name((u8*)"Meryweather", 2);

		var_glob.name_initial_char[0] = 'O';
		var_glob.name_initial_char[1] = 'M';

		var_glob.is_left_handed[0] = 1;
		var_glob.is_left_handed[1] = 1;

		//func_eeprom.open_file_for_read_data()
		//func_eeprom.read_state()
	}
}

/**
 * \brief       Clear previous info about the components of the GUI         
 * \param[in]   None 
 * \return      None
 */
void reset_numbers_GUI() {
    gui.num_buttons = 0;
    gui.num_buttons_popup = 0;
    gui.num_checkboxes = 0;
    gui.num_groups_radio_but = 0;
    gui.num_labels = 0;
    gui.num_regions = 0;
    gui.num_textboxes = 0;
	gui.num_textviews = 0;
}


/**
 * \brief       Initialize the apropriate global variables when a new match is to be started
 * \param[in]   None 
 * \return      None
 */
void start_match(void) {
    var_glob.games_for_player[0] = 0;
    var_glob.games_for_player[1] = 0;
    var_glob.winner_of_match = 0;

    for (u8 cj = 0; cj  < 6; cj ++){
        var_glob.points_total_for_player[0][cj] = 0;
        var_glob.points_total_for_player[1][cj] = 0;
    }
}

/* -------------------------- RETRIEVING INFORMATION FROM GLOBAL VARIABLES ---------------------------*/

/**
 * \brief       Used when a match is configured to 3 games, but maybe the use wants to extend to 
 *                  5 games when one of the player reaches 2 won games.
 * \param[in]   None 
 * \return      True (1)  when the match is configured to 3 games and one of the players reached 2.
 */

_Bool is_feasible_extend_to_5_games(void) {
    return some_player_won_the_match() && var_glob.games_to_win_the_match < 3;
}

/**
 * \brief       Answer whether one of the player won the match
 * \param[in]   None 
 * \return      True (1)  when the match is configured to 3 games and one of the players reached 2,
 *              or when the match is configured to 5 games and one of the players reached 3,
 */
_Bool some_player_won_the_match() {
    return (var_glob.games_for_player[0] == var_glob.games_to_win_the_match ||
            var_glob.games_for_player[1] == var_glob.games_to_win_the_match );
}

/**
 * \brief       Retrieves the number of played games
 * \param[in]   None 
 * \return      The sum of the games won by player 1 and player 2,
 */
u8 get_played_games(void)  {
     return var_glob.games_for_player[0] + var_glob.games_for_player[1];
 }


/* -------------------------- COLORS AND NAMES FOR THE PLAYERS ---------------------------*/

/**
 * \brief       Retrieves by reference the colours (background and text) assigned to a certain player
 * \param[in]   player_from_1: the player (1 or 2)
 * \param[in]   colour_backgnd (by reference): pointer to the background color (its shirt or shorts);
 * \param[in]   colour_text (by reference): pointer to the text color (black if background is clear and white if background is dark)
 * \return      None
 */
void get_colours(u8 player_from_1, u16*colour_backgnd, u16*colour_text) {
    *colour_backgnd = var_glob.colours_background[var_glob.colour_index[player_from_1-1]];
    *colour_text = var_glob.colours_text[var_glob.colour_index[player_from_1-1]];
}

/**
 * \brief       Assign the properties (colours and name) to the button that corresponds to a certain player
 * \param[in]   bt (by reference): pointer to the button structure;
 * \param[in]   player_from_1: the player (1 or 2)
 * \return      None
 */
void set_colours_and_name_to_button_player(button_t *bt, u8 player_from_1) {
    u16 colour16_back, colour16_text;
    get_colours(player_from_1, &colour16_back, &colour16_text);

	bt->rect.colour = colour16_back;
	bt->colour_text = colour16_text;
	bt->text =  var_glob.name_shown_for_player[player_from_1-1];
}


//  -----------------------------  FUNCTIONS RELATED TO THE SCORE EVOLUTION -------------------------*/

/**
 *              The last results are stored in an array named "results". If its range is going to be exceeded
 *              the older results are overwritten
 */


u8 num_allowed_undoes = 0;      // If the range is 20, and 25 results have been saved, there are 20 allowed undoes
                                // If the range is 20, and 5 results have been saved, there are 5 allowed undoes

/**
 * \brief       Prepare the array "results" to accept a new series of items
 * \param[in]   None
 * \return      None
 */
void start_a_new_result_evolution(void) { 
    results[0].points0 = results[0].points1 = 0;
    results[0].serve_situation = 1 | 0x00 | 0x20; // Can be improved 
    num_results_in_this_game = 1; 
    num_allowed_undoes = 1;
}

/**
 * \brief       Get a certain item from the array results
 * \param[in]   index: the index of the item to be obtained.
 * \return      Pointer to the item 
 */
result_t* get_result(u8 index) {
	if (index >= num_results_in_this_game) {
		return NULL;

	} else if (num_results_in_this_game < MAX_NUM_RECORDED_RESULTS) {
		return results + index ;	
	
	} else {
		u8 fin_index = (num_results_in_this_game - MAX_NUM_RECORDED_RESULTS + index);
		fin_index %= MAX_NUM_RECORDED_RESULTS;
		return results + fin_index;
	}
}
/**
 * \brief       Get the number of results stored (even the overwritten) for this game
 * \param[in]   None
 * \return      The number of results for this game
 */
u16 get_num_results(void) {
    return num_results_in_this_game;
}

/**
 * \brief       Get the last item from the array results
 * \param[in]   None
 * \return      Pointer to the last item
 */
result_t* get_last_result(void) {
    if (/*num_results_in_this_game == 0 ||*/ num_allowed_undoes == 0)
        // If you include 25 results, but you consecutevely undo 20 times, you do not have valid results
        return NULL;

    return results + ((num_results_in_this_game-1) % MAX_NUM_RECORDED_RESULTS);
}

/**
 * \brief       Remove the last result, e.g. when undoing the last result
 * \param[in]   None
 * \return      true (1) if the number of allowed undoes was positive => if it could be removed
 */
_Bool remove_last_result(void) {
    if (num_allowed_undoes == 0)
        return 0;
    num_results_in_this_game --;
    num_allowed_undoes --;
    return 1;
}

/**
 * \brief       Add a new result at the end of the array of results
 * \param[in]   situation: pointer to the item situation; it must be translated into a result structure
 * \return      None
 */
void add_new_result(situation_t *situation) {
    num_results_in_this_game ++;
    if (num_allowed_undoes <= 20)
        num_allowed_undoes ++;
    result_t *new_result = get_last_result();

	situation_2_result(situation, new_result);
}

/**
 * \brief       Tranlate the info from the structure situation, into the structure result
 * \param[in]   situation: pointer to the instance of the structure situation_t
 * \param[in]   result (by reference): pointer to the instance of the structure result_t
 * \return      None
 */
void situation_2_result(situation_t *situation, result_t* result) {
	result->points0 = situation->points[0];
    result->points1 = situation->points[1];
    result->serve_situation = situation->player_serving;
    
    if (situation->service_quarter) {
        result->serve_situation |= 0x10;
    }
    if (situation->there_was_change) {
        result->serve_situation |= 0x20;
    }
	result->time_s = situation->time_s;
}

/**
 * \brief       Tranlate the info from the structure result, into the structure situation
 * \param[in]   result: pointer to the instance of the structure result_t
 * \param[in]   situation (by reference): pointer to the instance of the structure situation_t
 * \return      None
 */
void result_2_situation(result_t* result, situation_t* situation) {
	situation->points[0] = result->points0;
    situation->points[1] = result->points1;
    situation->player_serving = 0x0F & result->serve_situation;
    situation->service_quarter = ((0x10 & result->serve_situation) !=0);
    situation->there_was_change = ((0x20 & result->serve_situation) != 0);
	situation->time_s = result->time_s;
}

/**
 * \brief       Get the last result, translating it to the structure situation_t
 * \param[in]   situation (by reference): pointer to the instance of the structure situation_t storing the 
                    result information
 * \return      True if num_allowed_undoes != 0
 */
_Bool recover_previous_result(situation_t *situation) {

    result_t *prev_result = get_last_result();
    if (prev_result == NULL) {
    	return 0;
    }

	result_2_situation(prev_result, situation);

    return 1;
}

/**
 * \brief       Undo the last result store, and get the previous result, translating it to the structure situation_t
 * \param[in]   situation (by reference): pointer to the instance of the structure situation_t storing the 
                    result information
 * \return      True if num_allowed_undoes != 0
 */
_Bool undo_and_recover_previous_result(situation_t *situation) {
    if (! remove_last_result() ) { 
        return 0;
    }

    result_t *prev_result = get_last_result();
    if (prev_result == NULL)
        return 0;

    situation->points[0] = prev_result->points0;
    situation->points[1] = prev_result->points1;
    situation->player_serving = 0x0F & prev_result->serve_situation;
    situation->service_quarter = 0x10 & prev_result->serve_situation;
    situation->there_was_change = 0x20 & prev_result->serve_situation;

    return 1;
}

/*  ---------------------------- FUNCTIONS RELATED TO TIME ---------------------------------------*/ 

u32 start_time;

/**
 * \brief       Obtain the ellapsed time from the moment in which the timer was started, and launch the 
 *                  corresponding task according to the active window (typically break/warm-up or score annotation)
 * \param[in]   None
 * \return      None
 */

void manage_timer(void) {
	gui.manage_specific_timer(get_ellapsed_time_ms());
}

#if defined WIN32
#include <Windows.h>

SYSTEMTIME st;
/**
 * \brief       Obtain the time in milliseconds, as given by the microprocessor 
 * \param[in]   None
 * \return      The time in milliseconds 
 */

u32 get_milliseconds(void) {
    
	GetSystemTime(&st);
    return 1000 * (st.wHour * 3600 + st.wMinute*60 + st.wSecond ) + st.wMilliseconds;
}
#else
#if defined USE_HAL_DRIVER
uint32_t HAL_GetTick(void);
void HAL_Delay(uint32_t Delay);
/**
 * \brief       Obtain the time in milliseconds, as given by the microcontroller 
 * \param[in]   None
 * \return      The time in milliseconds 
 */
u32 get_milliseconds(void) {
    
	return HAL_GetTick();
}
void Sleep (u16 milliseconds) {
	HAL_Delay(milliseconds);
}
#elif defined USE_LL_DRIVER
#error "check which Delay to use: maybe LL_mDelay(a)"
#error "Define the function get_milliseconds according to the way of obtaining the ticks"
#elif defined USE_STDPERIPH_DRIVER
#error "check which Delay to use: maybe delay(a)"
#error "Define the function get_milliseconds according to the way of obtaining the ticks"
#endif
#endif



/**
 * \brief       Store the system time, as a starting reference to obtain the ellapsed time
 *                 Several time measurements are allowed, although not simultaneously
 * \param[in]   None
 * \return      The time in milliseconds 
 */

void set_start_time(void) {
	
	start_time = get_milliseconds();
}

/**
 * \brief       Get the ellapsed time in milliseconds, from the starting reference
 * \param[in]   None
 * \return      The time in milliseconds 
 */
u32 get_ellapsed_time_ms(void) {
    u32 ellapsed_time = get_milliseconds() - start_time;
	return ellapsed_time;
}


