/**
 * \file            gui_score_graf.c
 * \brief           Auxiliary functions related to the component 
 *					behavior along the score annotation 
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





#include "includes.h"
#include "structs_gui.h"
#include "macros.h"
#include "func_gui_draw.h"
#include "gui_score.h"

extern situation_t situation;

extern _Bool game_apparently_finished;

#if ! defined WIN32
typedef enum {
	en_Score_tv_result_4_marker, 
	en_Score_tv_ellapsed_time, 
	en_Score_tv_sets
} textview_score_t;

typedef enum {
	en_Score_bt_break, 
	en_Score_bt_refresh, 
	en_Score_bt_win_pl1, 
	en_Score_bt_win_pl2, 
	en_Score_bt_changeLR,  
	en_Score_bt_pu_changesets, 
	en_Score_bt_pu_specialactions
} button_score_t;

typedef enum {
	en_Score_lb_games, 
	en_Score_lb_endgame
} label_score_t;
#endif

/* ------------ SERVE SIDE: DRAW THE SQUARE SHOWING THE SERVE SIDE -------------------------*/
#if defined PRAGMA_REGION_ACCEPTED
#pragma region Serve_Side
#endif
/**
 * \brief		Plot a little square to show which player is serving, and at which side
 * \param[in]   none
 * \return      none
 */
void plot_serve_side(void) {
	static rect16_t rect1 = {1,	Esc_Vrt(.3), Esc_Hor(0.33), Esc_Vrt(.35)};
	static rect16_t rect2 = {Esc_Hor(0.67), Esc_Vrt(.3), LCD_W, Esc_Vrt(.35)};
	static rect16_t rect =  {1,	Esc_Vrt(.3), LCD_W, Esc_Vrt(.32)};
	
	draw_rectangle_from_vertices(&rect1, BLACK, FILLED, VISIBLE, ENABLED);
	draw_rectangle_from_vertices(&rect2, BLACK, FILLED, VISIBLE, ENABLED);

	u16 x_st;
        
	x_st = situation.player_serving == 1 ? Esc_Hor(0.165) : Esc_Hor(0.835);
	if (situation.service_quarter == RIGHT_QUARTER) {
		x_st += Esc_Hor(0.1);
	} else {
		x_st -= Esc_Hor(0.1);
	}
	
	rect.left = x_st-5;
	rect.right = x_st+5;
	draw_rectangle_from_vertices(&rect, CYAN, FILLED, VISIBLE, ENABLED);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Serve_Side
#endif

/* ------------ UPDATE COMPONENTS: TEXTVIEWS and BUTTONS-------------------------------------------*/

/* ------------ textviews -----------------------*/
#if defined PRAGMA_REGION_ACCEPTED
#pragma region Update_Textviews
#endif
/**
 * \brief		Update the textview with the text that the marker must sing
 * \param[in]   none
 * \return      none
 */
void update_text_4_marker(_Bool re_draw) {
	replace_text_in_textview(&gui.textviews[en_Score_tv_result_4_marker], 
		get_text_for_the_marker(&situation), re_draw);
}
/**
 * \brief		Update the textview with the games for each player
 * \param[in]   none
 * \return      none
 */
void update_games(_Bool re_draw) {
	replace_text_in_textview(&gui.textviews[en_Score_tv_sets],
		get_string_games(), re_draw);
}
/**
 * \brief		Update the textview with the ellapsed time
 * \param[in]   none
 * \return      none
 */
void update_time(u16 ellapsed_time_s, _Bool re_draw) {
	replace_text_in_textview(&gui.textviews[en_Score_tv_ellapsed_time],
		 seconds_2_string_minutes_seconds(ellapsed_time_s), re_draw);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Update_Textviews
#endif

/* ------------ buttons -----------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Update_Buttons
#endif
/**
 * \brief		Set the name and colour for certain player
 * \param[in]   player: the player whose button is set
 * \return      none
 */
void define_player_button(u8 player) {
	if (player == 1)
		set_colours_and_name_to_button_player(gui.buttons + en_Score_bt_win_pl1, 1);
	else
		set_colours_and_name_to_button_player(gui.buttons + en_Score_bt_win_pl2, 2);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Update_Buttons
#endif

/* ------------ MANAGE THE SCORE EVOLUTIONS (THE CENTRAL REGION) ----------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Score_Evolution
#endif

const u16 posx_1 = Esc_Hor(0.35);
const u16 posx_2 = Esc_Hor(0.65);
const u16 org_y = Esc_Vrt(0.78);
const u8 num_max_items = 25;
const u8 incr_y = org_y / (num_max_items);
#define SITUATION_2_INDEX(sit) ((sit->points[0]+sit->points[1]) )

/**
 * \brief		In the central vertical band, clear the space corresponding to a result that is being undone or
 *                  corrected
 * \param[in]   situation: the situation/result to be corrected or undone
 * \return      none
 */
void clear_old_result(situation_t* situation) {
	rect16_t rect;
	rect.left = posx_1;
	rect.right = posx_2;
	u8 index = SITUATION_2_INDEX(situation) % num_max_items;
	index = index  % num_max_items;
	rect.bottom =  org_y - index * incr_y + 3;
	rect.top = rect.bottom - 2 * incr_y;
	
	draw_rectangle_from_vertices(&rect, PINK_PURPLE, FILLED, VISIBLE, ENABLED);
}
/**
 * \brief		In the central vertical band, display the result for a certain situation
 * \param[in]   situation: the situation whose result is being displayed
 * \return      none
 */
void display_situation_in_central_band(situation_t* situation) {
	u16 colour_text;
	u8 text_4_marker[9];
	my_strcpy(text_4_marker, get_text_for_the_marker(situation));

	u8 index = SITUATION_2_INDEX(situation);

	colour_text = (index / num_max_items) % 2 == 0 ? BLUE : RED;
	
	if (index >= num_max_items) {
		clear_old_result(situation);
		index %= num_max_items;
	}

	u8* text_time = NULL;

	_Bool time_visible = gui.checkboxes[0].is_checked;
	if (time_visible)
		text_time = seconds_2_string_minutes_seconds(situation->time_s);
	
	u16 posy = org_y - index * incr_y;
	if (situation->player_serving == 1) {
		gui_str(posx_1, posy, colour_text, PINK_PURPLE, text_4_marker, FONT16, Left_Center, VISIBLE, ENABLED);
		gui_str(LCD_W/2+6, posy, GRED, PINK_PURPLE, text_time, FONT16, Left_Center, time_visible, ENABLED);

	} else {
		gui_str(posx_2, posy, colour_text, PINK_PURPLE, text_4_marker, FONT16, Right_Center, VISIBLE, ENABLED);
		gui_str(LCD_W/2-6, posy, GRED, PINK_PURPLE, text_time, FONT16, Right_Center, time_visible, ENABLED);
	}
}
/**
 * \brief		In the central vertical band, display a certain result
 * \param[in]   situation: the result being displayed
 * \return      none
 */
void display_result_in_central_band(result_t* res) {

	situation_t l_situation;
	result_2_situation(res, &l_situation);

	display_situation_in_central_band(&l_situation);	
}
/**
 * \brief		Clear the central vertical band, display all of the results of the current game
 * \param[in]   situation: the result being displayed
 * \return      none
 */
void display_complete_result_evolution(void) {
	draw_region(gui.regions+1, 1, VISIBLE, ENABLED);
	u8 num_items = MIN(MAX_NUM_RECORDED_RESULTS, get_num_results());
	for (u8 ci = 0; ci < num_items; ci++) {
		result_t *result = get_result(ci);
		display_result_in_central_band(result);
	}
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Score_Evolution
#endif

/* ------------ TRANSLATE CURRENT SITUATION TO GUI ------------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Update_GUI
#endif
// Se llama al cambiar de colour un jugador, 
// en la inicializaci�n de la ventana, si no proviene del break
// y en update_situation
/**
 * \brief		Update the GUI with the info of the new situation
 * \param[in]   re_draw: if 0, it only assign, but do not repaint the components; if 1, assign and repaint
 *                  It is called when changing a player colour, during the GUI initialization (if not coming from break)
 *                  and in update_situation
 * \return      none
 */
void current_situation_2_GUI(_Bool re_draw)
{    //  tvRallies = cop_tvRallies.clone() as ArrayList<TextView>
    
	if (get_num_rallies() == 1)        {
		gui.radio_but[0].visible = INVISIBLE;
		delete_group_radio_button(&gui.radio_but[0]);
		
		gui.buttons[en_Score_bt_refresh].visible = VISIBLE;
		draw_button(&gui.buttons[en_Score_bt_refresh]);
    }

    update_text_4_marker(re_draw);

	if (some_player_won_the_game( ) > 0) {
		game_apparently_finished = 1;
	}
	
	if (gui.buttons[en_Score_bt_win_pl1].enabled == game_apparently_finished) {
		gui.buttons[en_Score_bt_win_pl1].enabled = !game_apparently_finished;
		gui.buttons[en_Score_bt_win_pl2].enabled = !game_apparently_finished;
		update_button(gui.buttons+en_Score_bt_win_pl1);
		update_button(gui.buttons+en_Score_bt_win_pl2);
	}
	if (gui.buttons[en_Score_bt_break].visible != game_apparently_finished) {
		gui.buttons[en_Score_bt_break].visible = game_apparently_finished;
		gui.labels[en_Score_lb_endgame].visible = game_apparently_finished;
		update_button(gui.buttons+en_Score_bt_break);
		display_label(gui.labels+en_Score_lb_endgame);
	}
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Update_GUI
#endif

/* ------------ ENABLING and VISIBILIZATION of CONTROLS -------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Enable_Visible_Controls
#endif
/**
 * \brief		Operations to do when a match is being started, mainly related to which components
 *              must be visible in order to chose who is serving first.
 * \param[in]   situation: the result being displayed
 * \return      none
 */
/* Only called in operations_pre_initialize_score */
_Bool manage_first_service_of_match(_Bool re_draw) {
	_Bool previous_state = gui.radio_but[0].visible;

	if (get_num_rallies() == 0 && get_played_games() == 0) {
		gui.radio_but[0].visible = VISIBLE;
	
	} else {
		gui.radio_but[0].visible = INVISIBLE;
	}

	gui.buttons[en_Score_bt_refresh].visible = ! gui.radio_but[0].visible;

	if (gui.radio_but[0].visible != previous_state && re_draw) {
		if (gui.radio_but[0].visible) {
			draw_group_radio_button(gui.radio_but+0);
		} else {
			delete_group_radio_button(gui.radio_but+0);
		}
	}
	return (gui.radio_but[0].visible == VISIBLE);
}
/**
 * \brief		Make enable or visible components just after start a new game
 * \param[in]   game_started: 1 if the game has just started; 0 if must start
 * \return      none
 */
void enable_after_starting_new_game_wo_drawing(_Bool game_started) {
    gui.buttons[en_Score_bt_win_pl1].enabled = game_started;
    gui.buttons[en_Score_bt_win_pl2].enabled = game_started;

    gui.buttons[en_Score_bt_changeLR].enabled = game_started;
        
    gui.buttons[en_Score_bt_break].visible = !game_started;
	
	draw_button(&gui.buttons[en_Score_bt_win_pl1]);
	draw_button(&gui.buttons[en_Score_bt_win_pl2]);
}


#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Enable_Visible_Controls
#endif
