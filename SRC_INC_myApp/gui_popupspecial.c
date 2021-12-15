/**
 * \file            gui_popupspecial.c
 * \brief           Buttons for special actions during score annotation
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
#include "gui_match_conf.h"
#include "gui_popupspecial.h"
#include "gui_score.h"
#include "gui_score_graf.h"
#include "gui_definplayer.h"
#include "gui_break.h"


static const u8 this_window = POPUP_SPEC;

static void action_correct_winner(void);
static void action_undo(void);

static void action_change_colour1(void);
static void action_change_colour2(void);
static void action_sp_recover_state(void);
static void action_ReconectarBT(void);
static void action_back(void);
static void action_abort_game(void);

warning_t message_new_game;

extern situation_t situation;

extern _Bool game_apparently_finished;

extern u8 player_who_won_the_rally;

//_Bool show_seconds = 0;



/* -------------------- COMPONENT DEFINITIONS ------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Component_Definitions
#endif

#define HAS_BUTTONS				1
#define HAS_RADIO_BUTTONS		0
#define HAS_LABELS				0
#define HAS_REGIONS			1
#define HAS_CHECKBOXES			0
#define HAS_TEXTVIEWS			1


#if HAS_BUTTONS
static button_t buttons[] = {    { action_abort_game, Kst_QUITGAME, {Center,				180, 40, 200, 35,
                GRAY}, LILA, FONT16, ENABLED, VISIBLE}
    
    ,{ action_correct_winner, Kst_CORREGIR, {Center,			180, 100, 200, 35,
                BLACK}, LILA, FONT16, ENABLED, VISIBLE}
    
    ,{ action_undo, Kst_UNDO, {Center,						180, 160, 200, 35,
                GRAY}, LILA, FONT16, ENABLED, VISIBLE}
    
    ,{ action_change_colour1, Kst_CHANGEcolour1, {Center,		125, 220, 90, 35,
                BLACK}, LILA, FONT16, ENABLED, VISIBLE}

    ,{ action_change_colour2, Kst_CHANGEcolour2, {Center,		235, 220, 90, 35,
                BLACK}, LILA, FONT16, ENABLED, VISIBLE}

    ,{ action_sp_recover_state, Kst_RECOVERSTATE, {Center,	180, 280,  200, 35,
                GRAY}, LILA, FONT16, ENABLED, VISIBLE}
    
    ,{ action_ReconectarBT, Kst_RECONECTARBT, {Center,		180, 340,  200, 35,
                BLACK}, LILA, FONT16, ENABLED, VISIBLE}
	
    ,{ action_back, Kst_BACK, {Center,						180, 400,  200, 35,
                GRAY}, LILA, FONT16, ENABLED, VISIBLE}
};

typedef enum {
	en_PUspec_bt_back, 
	en_PUspec_bt_correct, 
	en_PUspec_bt_undo, 
	en_PUspec_bt_recover,  
	en_PUspec_bt_ReconBT
} button_PopUpSpec_t;
#endif 

#if HAS_LABELS

#endif

#if HAS_TEXTVIEWS
static   textview_t textviews_score[] = {
        {Center, 40, 130,    BLUE, /*LIGHTGRAY,*/  FONT16, VISIBLE}
    };
typedef enum  {
	en_PUspec_tv_score
} textview_PopUpSpec_t;
#endif

#if HAS_REGIONS
static region_t regions[] = {
    {Left_Top, 0,    0, LCD_W, LCD_H, LIGHTGRAY  }
}; 
#endif

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Component_Definitions
#endif

/* -------------------- GUI CREATION ------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region GUI_Creation
#endif


/**
 * \brief		Assign to var_glob the arrays of component for this window and draw the components
 * \param[in]   none
 * \return      none
 */
void set_window_popup_Especiales()
{    
    UPDATE_ACTIVE_WINDOW;

    reset_numbers_GUI();

    // Initialize buttons
#if HAS_BUTTONS
    gui.num_buttons = sizeof(buttons) / sizeof(button_t);
    gui.buttons = buttons;
#endif

#if HAS_RADIO_BUTTONS
    gui.num_groups_radio_but = sizeof(radio_but) / sizeof(group_radiobutton_t);
    gui.radio_but = radio;
#endif
    // Initialize radio buttons

#if HAS_REGIONS
    gui.num_regions = sizeof(regions) / sizeof (region_t);
    gui.regions = regions;
#endif

#if HAS_LABELS
    gui.num_labels = sizeof(labels) / sizeof (label_t);
    gui.labels = labels;
#endif

#if HAS_TEXTBOXES
    gui.num_textboxes = sizeof(textboxes) / sizeof (textbox_t);
    gui.textboxes = textboxes;
#endif

#if HAS_TEXTVIEWS
    gui.textviews = textviews_score;
    gui.num_textviews = sizeof(textviews_score) / sizeof(textview_t);
#endif

    initialize_active_window();
	replace_text_in_textview(&gui.textviews[0], get_text_for_the_marker(&situation), AND_SHOW);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion GUI_Creation
#endif

/* -------------------- ACTIONS WHEN PRESSING THE BUTTONS  ------------------*/


#if defined PRAGMA_REGION_ACCEPTED
#pragma region ACTIONS
#endif
static void action_abort_game(void) {
        fill_message(&message_new_game, Kst_abort_this_game, 
            Kst_SPACE, 2, Kst_YES, Kst_NO, NULL);
		u8 option = show_popup_and_wait_for_answer(&message_new_game);

        if (option == 0) {
            set_window_break();
        } else {
		set_window_popup_Especiales();
		}

}

static void action_correct_winner(void) {
    if (get_num_rallies() <1)
        return;
    if (! remove_last_result())
        return ;

    situation.points[player_who_won_the_rally - 1] --;
    player_who_won_the_rally = 3 - player_who_won_the_rally;	// the other player

    update_situation();
	
	game_apparently_finished = (some_player_won_the_game() > 0);

	replace_text_in_textview(&gui.textviews[0], get_text_for_the_marker(&situation), AND_SHOW);
	//set_window_score();

	// Trama.rellenaYEnviaTrama(K.messagePuntos)
}
static void action_undo(void) {
    if (get_num_rallies() <1)
        return;
	
    if (! remove_last_result())
        return ;
	
    recover_previous_result(&situation);

    update_text_4_marker(ONLY_ASSIGN);
 
	replace_text_in_textview(&gui.textviews[0], get_text_for_the_marker(&situation), AND_SHOW);
	// Trama.rellenaYEnviaTrama(K.messagePuntos)
    game_apparently_finished = (some_player_won_the_game() > 0);

	//set_window_score();
}

static void change_player_colour(u8 player_from_1) {
	set_window_definplayer(player_from_1);
	// ToDo Trama.rellenaYEnviaTrama(K.messagePuntos)
    /*current_situation_2_GUI(AND_SHOW);
	
	plot_serve_side();
	
	define_player_button(player_from_1); */
}
static void action_change_colour1(void) {
    change_player_colour(1);
}
static void action_change_colour2(void) {
    change_player_colour(2);
}

static void action_sp_recover_state(void) {
    if (get_num_rallies() <1)
        return;

    // ToDo val tramaBT : ByteArray =  func_eeprom.RecuperaTrama()
    // ToDo func_eeprom.read_state(applicationContext)
    // ToDo Trama.Trama_2_situacionActual(tramaBT)
    game_apparently_finished = (some_player_won_the_game( ) > 0);
    // func_file.recover_state();
    //Trama.rellenaYEnviaTrama(K.messagePuntos);
}

static void action_ReconectarBT(void) {
    // func_file.recover_state();
    // reconectarBluetooth()
}

static void action_back(void) {
	set_window_score();
}


#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion ACTIONS
#endif

#undef HAS_BUTTONS
#undef HAS_RADIO_BUTTONS
#undef HAS_LABELS
#undef HAS_REGIONS


