/**
 * \file            gui_score.c
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

#include "gui_score.h"

#include "includes.h"
#include "gui_match_conf.h"
#include "gui_popupsets.h"
#include "gui_popupspecial.h"
#include "gui_break.h"
#include "gui_score.h"
#include "gui_score_graf.h"

static const u8 this_window = GUI_SCORE;

#undef THIS_WINDOW
#define THIS_WINDOW GUI_SCORE

situation_t situation;

_Bool game_apparently_finished;

u8	player_who_won_the_rally = 0;

_Bool show_seconds = 0;


static void manage_this_timer(u32 ellapsed_time_ms) ;

/* -------------------- COMPONENT DEFINITIONS ------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Component_Definitions
#endif

#define HAS_BUTTONS           1
#define HAS_RADIO_BUTTONS     1
#define HAS_LABELS            1
#define HAS_REGIONS        1
#define HAS_CHECKBOXES        1
#define HAS_TEXTVIEWS         1  

#if HAS_BUTTONS
static button_t buttons_score[] = {     { action_start_break, Kst_STARTDESCANSO, {Center,            60, Esc_Vrt(.63), 70, 40,
				GREEN}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_refresh, Kst_REFRESH, {Center,                     260, Esc_Vrt(.15), 70, 30,
                LIGHTBLUE}, BLACK, FONT16, ENABLED, INVISIBLE}

    ,{ action_winplyr1, Kst_PLAYER1, {Center,                    60, Esc_Vrt(.4), 80, 40,
                LILA}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_winplyr2, Kst_PLAYER2, {Center|H_Simmetry,			60, Esc_Vrt(.4), 80, 40,
                LILA}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_change_lf_rg, Kst_CHANGELEFTRIGHT, {Center,        55, 90, 90, 30,
                LILA}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_change_sets, Kst_CHANGEGAMES, {Center,             80, Esc_Vrt(.9),  100, 50,
                GRAY}, LILA, FONT16, ENABLED, VISIBLE}

    ,{ action_special_actions, Kst_SPECIALACTIONS, {Center|H_Simmetry,	80, Esc_Vrt(.9),  100, 50,
				GRAY}, LILA, FONT16, ENABLED, VISIBLE}

#if defined WIN32
	,{simul_timer, (u8*)"T", {Center, 300,460,10,10,GREEN},LILA,FONT12,ENABLED, VISIBLE} // To simulate systicks
#endif
};

typedef enum {
	en_Score_bt_break, 
	en_Score_bt_refresh, 
	en_Score_bt_win_pl1, 
	en_Score_bt_win_pl2, 
	en_Score_bt_changeLR,  
	en_Score_bt_pu_changesets, 
	en_Score_bt_pu_specialactions
} button_score_t;
	
#endif

#if HAS_RADIO_BUTTONS
static group_radiobutton_t radio_but_score[] = {
    {action_who_serves_at_the_beginning_of_match, 2, 220, Esc_Vrt(0.10), FONT16, YELLOW, /*BLACK, */0, Kst_rb_SERVE12, ENABLED, VISIBLE}  
};
#endif

#if HAS_REGIONS
static region_t regions_score[] = {
     {Left_Top, 0,    0, LCD_W, (u16)(LCD_H*0.8), BLACK  }
    ,{Left_Top, (u16)(LCD_W*0.34), 0,(u16)(LCD_W*0.33),    (u16)(LCD_H*0.8), PINK_PURPLE  }
    ,{Left_Top, 0,    (u16)(LCD_H*0.8), LCD_W, (u16)(LCD_H*0.2), ORANGE  }
    ,{Center, (u16)(LCD_W*0.84),(u16)(LCD_H*0.6), (u16)(LCD_W*0.32), (u16)(LCD_H*0.1), GRED  }
}; 
#endif

#if HAS_CHECKBOXES
static checkbox_t checkBoxes_score[] = {
    {action_show_times, Kst_TIME, 80, 20, the_left, LIGHTBLUE, /*BLACK,*/ FONT16, CHECKED, ENABLED, VISIBLE}  
};
#endif

#if HAS_LABELS
static label_t labels_score[] = {
        {Center, Esc_Hor(0.16), Esc_Vrt(.71), YELLOW, /*BLACK,*/ FONT24, Kst_GAMES_, VISIBLE}
        ,{Center, Esc_Hor(0.16), Esc_Vrt(.52), CYAN, /*BLACK,*/ FONT24, Kst_ENDGAME, INVISIBLE}
    };
typedef enum {
	en_Score_lb_games, 
	en_Score_lb_endgame
} label_score_t;
#endif

#if HAS_TEXTVIEWS
static   textview_t textviews_score[] = {
        {Center, (u16)(LCD_W*0.83), (u16)(LCD_H*0.6),    RED, /*YELLOW, */ FONT24, VISIBLE}
        ,{Center, (u16)(LCD_W*0.83), (u16)(LCD_H*0.75),  PURPLE_BLUE, /*BLACK,*/ FONT24, VISIBLE}
        ,{Center, Esc_Hor(0.16), Esc_Vrt(0.76),			 YELLOW, /*BLACK,*/ FONT24, VISIBLE}
    };
typedef enum {
	en_Score_tv_result_4_marker, 
	en_Score_tv_ellapsed_time, 
	en_Score_tv_sets
} textview_score_t;
#endif


#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Component_Definitions
#endif

/* -------------------------- GUI CREATION --------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region GUI_Creation
#endif
/**
 * \brief		Assign to var_glob the arrays of component for this window and draw the components
 * \param[in]   none
 * \return      none
 */
void set_window_score() {    
    UPDATE_ACTIVE_WINDOW;

	reset_numbers_GUI();

    // Initialize buttons
#if HAS_BUTTONS
    gui.buttons = buttons_score;
	gui.num_buttons = sizeof(buttons_score) / sizeof(button_t);    
#endif

#if HAS_RADIO_BUTTONS
    gui.radio_but = radio_but_score;
	gui.num_groups_radio_but = sizeof(radio_but_score) / sizeof(group_radiobutton_t);    
#endif
    // Initialize radio buttons

#if HAS_REGIONS
    gui.regions = regions_score;
	gui.num_regions = sizeof(regions_score) / sizeof (region_t);    
#endif

#if HAS_LABELS
    gui.labels = labels_score;
	gui.num_labels = sizeof(labels_score) / sizeof (label_t);    
#endif

#if HAS_TEXTBOXES
    gui.textboxes = textboxes_score;
	gui.num_textboxes = sizeof(textboxes_score) / sizeof (textbox_t);    
#endif
    
#if HAS_CHECKBOXES
    gui.checkboxes = checkBoxes_score;
    gui.num_checkboxes = sizeof(checkBoxes_score) / sizeof (checkbox_t);
#endif

#if HAS_TEXTVIEWS
    gui.textviews = textviews_score;
    gui.num_textviews = sizeof(textviews_score) / sizeof(textview_t);
#endif

    operations_pre_initialize_score();
    initialize_active_window();
    operations_post_initialize_score();
}
/**
 * \brief		Operations to do before the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_pre_initialize_score() {
    define_player_button(1);
    define_player_button(2);

    if (gui.procedence_window == GUI_BREAK || gui.procedence_window == 0) {
            set_start_time();
            gui.manage_specific_timer = manage_this_timer;
            situation.player_serving = gui.radio_but[0].index_selected+1;
            manage_first_service_of_match(ONLY_ASSIGN);

            actions_new_game();
            /* ToDo   if (BluetoothGlob.socket_is_set())
                btSocket = BluetoothGlob.get_btSocket()!! */

			update_text_4_marker (ONLY_ASSIGN);            
        
	}  else {
            current_situation_2_GUI(ONLY_ASSIGN);
			//display_complete_result_evolution();
			
    }       
    // ToDo Trama.rellenaYEnviaTrama(K.messagePuntos)
}
/**
 * \brief		Operations to do just after the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_post_initialize_score(void) {
	update_text_4_marker(AND_SHOW);
    update_games(AND_SHOW);
    update_time(0, AND_SHOW);
	if (gui.procedence_window != GUI_BREAK && gui.procedence_window != 0) {
		
	}
	display_complete_result_evolution();
	plot_serve_side(); 

    gui.timer_enabled = 1;
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion GUI_Creation
#endif

/* -------------------- CLICK ACTIONS Functions ------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Click_Actions
#endif
/**
 * \brief		At the beginning of the match, the user decides who serves first.
 *                  Read the radio button and change the indicator of server side
 * \param[in]   none
 * \return      none
 */
void action_who_serves_at_the_beginning_of_match(void) {
	actions_service_change(gui.radio_but[0].index_selected+1);
	plot_serve_side();
}
/**
 * \brief		Responsive action when the checkbox "Show_time" is pressed. If the checkbox
 *                  is marked, the times are displayed together with the score
 * \param[in]   none
 * \return      none
 */
void action_show_times(void) {
    if (gui.checkboxes[0].is_checked) {
        display_complete_result_evolution();
    }
}
/**
 * \brief		Actions to be performed when a player wins the rally
 * \param[in]   none
 * \return      none
 */
void action_annotation(u8 rally_winner) {
    player_who_won_the_rally = rally_winner;
    update_situation();
	current_situation_2_GUI(AND_SHOW);
	plot_serve_side();
	display_situation_in_central_band(&situation); 
}
/**
 * \brief		Actions to be performed when player 1 wins the rally
 * \param[in]   none
 * \return      none
 */
void action_winplyr1(void) {
    action_annotation(1);
}
/**
 * \brief		Actions to be performed when player 2 wins the rally
 * \param[in]   none
 * \return      none
 */
void action_winplyr2(void) {
    action_annotation(2);
}
/**
 * \brief		Actions to be performed when the user press the break button
 * \param[in]   none
 * \return      none
 */
void action_start_break(void) {
    gui.buttons[en_Score_bt_win_pl1].enabled = DISABLED;
    gui.buttons[en_Score_bt_win_pl2].enabled = DISABLED;
   
    gui.buttons[en_Score_bt_changeLR].enabled = DISABLED;

    var_glob.games_for_player[player_who_won_the_rally-1] ++;

    var_glob.winner_of_previous_game = player_who_won_the_rally;
	
    // ToDo Trama.rellenaYEnviaTrama(K.messageSets)
    u8 ind_game = get_played_games();
	var_glob.points_total_for_player[0][ind_game] = situation.points[0];
	var_glob.points_total_for_player[1][ind_game] = situation.points[1];

    set_window_break();
}
/**
 * \brief		Change the server side right <-> left
 * \param[in]   none
 * \return      none
 */
void action_change_lf_rg(void) {
	situation.service_quarter = !situation.service_quarter;
	
	plot_serve_side();
}
/**
 * \brief		Open a new window with the buttons to modify the won games
 * \param[in]   none
 * \return      none
 */
void action_change_sets(void) {
    set_window_popup_Sets();  
}

/**
 * \brief		Open a new window with the buttons for special actions
 * \param[in]   none
 * \return      none
 */
void action_special_actions(void) {
	set_window_popup_Especiales();
}

/**
 * \brief		Refresh the result evolution
 * \param[in]   none
 * \return      none
 */
void action_refresh(void) {
    display_complete_result_evolution();
    // ToDo Send the Bluetooth waive
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Click_Actions
#endif

/* -------------------- TIMER ----------------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Timer
#endif

/**
 * \brief		Periodical tasks to carry out: show the ellapsed time. 
 * \param[in]   none
 * \return      none
 */
static void manage_this_timer(u32 ellapsed_time_ms) {
    u16 ellapsed_time_s = ellapsed_time_ms / 1000;
    update_time(ellapsed_time_s, AND_SHOW);
}
/**
 * \brief		A simple button to force the gui to display the ellapsed time		
 * \param[in]   none
 * \return      none
 */
#if defined WIN32
static void simul_timer(void) {
	manage_timer();
}
#endif

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Timer
#endif

/* -------------------- AUXILIARY FUNCTIONS ----------------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region AUXILIARY_FUNCTIONS
#endif


/**
 * \brief		Update the structure that contains the current information of the game	
 *                  It is called in the "action_correct" function, and when a player wins the rally
 * \param[in]   none
 * \return      none
 */

void update_situation(void)  {
    situation.points[player_who_won_the_rally - 1] ++;

    situation.there_was_change = (player_who_won_the_rally != situation.player_serving);

    if (situation.there_was_change)        {
        situation.player_serving = player_who_won_the_rally;
        actions_service_change(player_who_won_the_rally);
    
    } else {
        situation.service_quarter= !situation.service_quarter;        
    }

	situation.time_s = get_ellapsed_time_ms()/1000;
  
    // ToDo val tramaBT = Trama.rellenaYEnviaTrama(K.messagePuntos)
    // ToDo func_eeprom.GrabaTrama(getApplicationContext(), tramaBT)
	
    add_new_result(&situation);

    Sleep(100);
}
/**
 * \brief		Tasks to be performed when a player apparently wins the game
 * \param[in]   none
 * \return      none
 */
/* Only is called in operations_pre_initialize */
void actions_new_game(void)     {

        game_apparently_finished = 0;

        start_a_new_result_evolution();

        actions_service_change(var_glob.winner_of_previous_game);

        situation.points[0] =0;
        situation.points[1] =0;

		enable_after_starting_new_game_wo_drawing(1);

		update_games(ONLY_ASSIGN);
    }

/**
 * \brief		Assign the service side and serving player when there is a change in the winner
 * \param[in]   winner: the new winner
 * \return      none
 */

void actions_service_change(u8 winner) {
	situation.service_quarter = !var_glob.is_left_handed[2 - winner];
    situation.player_serving = winner;   
}

/**
 * \brief		Informs if one of the players apparently won the game
 * \param[in]   none
 * \return      If one of the player won the game, return the player; 0 otherwise
 */
u8 some_player_won_the_game(void) {
    if (situation.points[0] >=  POINTS_TO_WIN && situation.points[0] - situation.points[1]>1)
        return 1;

    if  (situation.points[1] >= POINTS_TO_WIN && situation.points[1] - situation.points[0]>1)
        return 2;

    return 0;
}
/**
 * \brief		Return the number of played games in this match
 * \param[in]   none
 * \return      the number of played games
 */
u8 get_num_rallies(void){
	return situation.points[0]+ situation.points[1];
}	


#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion AUXILIARY_FUNCTIONS
#endif

/*
    fun reconectarBluetooth()
    {
        if (BluetoothGlob.establish_Socket(BluetoothGlob.address) == null){
            Toast.makeText(
                applicationContext,
                R.string.bt_failed_reconnection,
                Toast.LENGTH_LONG
            ).show()
            finish()
        }
        else
            Trama.rellenaYEnviaTrama(K.messagePuntos)
    }
    */ 


#undef HAS_BUTTONS
#undef HAS_RADIO_BUTTONS
#undef HAS_LABELS
#undef HAS_REGIONS
#undef HAS_TEXTBOXES
#undef HAS_CHECKBOXES    
