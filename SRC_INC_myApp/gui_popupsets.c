/**
 * \file            gui_popupsets.c
 * \brief           Pop up to increase and decrease sets
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
#include "gui_popupsets.h"
#include "gui_score.h"

static const u8 this_window = POPUP_SETS;


static void operations_pre_initialize_Popupsets(void);
static void action_decr_games_for_1(void);
static void action_incr_games_for_1(void);
static void action_decr_games_for_2(void);
static void action_incr_games_for_2(void);
static void action_back(void);

/* -------------------- COMPONENT DEFINITIONS ------------------------------ */

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Component_Definitions
#endif

#define HAS_BUTTONS           1
#define HAS_RADIO_BUTTONS     0
#define HAS_LABELS            1
#define HAS_REGIONS        1
#define HAS_CHECKBOXES        0
#define HAS_TEXTVIEWS         1


#if HAS_BUTTONS
static button_t buttons_pu_sets[] = { \
	{ action_decr_games_for_1, Kst_Minus1game, {Center,          240, 60, 90, 40,\
                BLACK}, LILA, FONT24, ENABLED, VISIBLE}\

    ,{ action_incr_games_for_1, Kst_Plus1game, {Center,          240, 140, 90, 40,\
                GRAY}, LILA, FONT24, ENABLED, VISIBLE}\

    ,{ action_decr_games_for_2, Kst_Minus1game, {Center,         240, 220, 90, 40,\
                BLACK}, LILA, FONT24, ENABLED, VISIBLE}\

    ,{ action_incr_games_for_2, Kst_Plus1game, {Center,          240, 300, 90, 40,\
                GRAY}, LILA, FONT24, ENABLED, VISIBLE}\

    ,{ action_back, Kst_BACK, {Center,                           240, 380, 90, 40,\
                BLUE}, LILA, FONT24, ENABLED, VISIBLE}\
};
typedef enum {
	en_PUSets_bt_back, 
	en_PUSets_bt_Minus1_Play1, 
	en_PUSets_bt_Plus1_Play1,  
	en_PUSets_bt_Minus1_Play2, 
	en_PUSets_bt_Plus1_Play2
} button_PopUpSets_t;

#endif

#if HAS_LABELS
static label_t labels_pu_sets[] = {
         {Left_Top, 20, 60, BLACK, /*LIGHTGRAY,*/ FONT24, Kst_GAMESPLAYER1, VISIBLE}
        ,{Left_Top, 20, 220, BLACK, /*LIGHTGRAY,*/ FONT24, Kst_GAMESPLAYER2, VISIBLE}
    };

enum {
	en_PUSets_lb_setsply1, 
	en_PUSets_lb_setsply2
} labels_PopUpSets_t;

#endif

#if HAS_TEXTVIEWS
static    textview_t textviews_pu_sets[] = {    
		  {Left_Center, 30, 100,  BLUE, /*LIGHTGRAY,*/ FONT24, VISIBLE}
        , {Left_Center, 30, 260,  BLUE, /*LIGHTGRAY,*/ FONT24, VISIBLE}    
        , {Left_Center, 30, 130,  BLACK, /*LIGHTGRAY,*/ FONT24, VISIBLE}
        , {Left_Center, 30, 290,  BLACK, /*LIGHTGRAY,*/ FONT24, VISIBLE}
    };

typedef enum {
	en_PUSets_tv_name_pl1, 
	en_PUSets_tv_name_pl2,
	en_PUSets_tv_setsply1, 
	en_PUSets_tv_setsply2
} textview_PopUpSets_t;

#endif

#if HAS_REGIONS
static region_t regions_pu_sets[] = {
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
void set_window_popup_Sets() {    
    UPDATE_ACTIVE_WINDOW;
    
    reset_numbers_GUI();

    // Initialize buttons
#if HAS_BUTTONS
    gui.num_buttons = sizeof(buttons_pu_sets) / sizeof(button_t);
    gui.buttons = buttons_pu_sets;
#endif

#if HAS_RADIO_BUTTONS
    gui.num_groups_radio_but = sizeof(radio_but_pu_sets) / sizeof(group_radiobutton_t);
    gui.radio_but = radio;
#endif
    // Initialize radio buttons

#if HAS_REGIONS
    gui.num_regions = sizeof(regions_pu_sets) / sizeof (region_t);
    gui.regions = regions_pu_sets;
#endif

#if HAS_LABELS
    gui.num_labels = sizeof(labels_pu_sets) / sizeof (label_t);
    gui.labels = labels_pu_sets;
#endif

#if HAS_TEXTVIEWS
    gui.textviews = textviews_pu_sets;
    gui.num_textviews = sizeof(textviews_pu_sets) / sizeof(textview_t);
#endif

#if HAS_TEXTBOXES
    gui.num_textboxes = sizeof(textboxes_pu_sets) / sizeof (textbox_t);
    gui.textboxes = textboxes_pu_sets;
#endif

    operations_pre_initialize_Popupsets();

	initialize_active_window();

}
/**
 * \brief		Operations to do before the initial representation of this window
 * \param[in]   none
 * \return      none
 */
static void operations_pre_initialize_Popupsets() {    
    replace_text_in_textview(gui.textviews+en_PUSets_tv_name_pl1, 
        var_glob.name_typed_for_player[0], ONLY_ASSIGN);
    replace_text_in_textview(gui.textviews+en_PUSets_tv_name_pl2,
        var_glob.name_typed_for_player[1], ONLY_ASSIGN);  

	replace_text_in_textview_with_number(gui.textviews+en_PUSets_tv_setsply1, 
        var_glob.games_for_player[0], ONLY_ASSIGN);
    replace_text_in_textview_with_number(gui.textviews+en_PUSets_tv_setsply2,
        var_glob.games_for_player[1], ONLY_ASSIGN);  
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion GUI_Creation
#endif

/* ---------------------------- ACTIONS Functions ------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region ACTIONS
#endif

/**
 * \brief		Decrement the number games for player 1
 * \param[in]   none
 * \return      none
 */
static void action_decr_games_for_1(void) {
    DECR_GAMES_FOR_PLAYER(1);

    replace_text_in_textview_with_number(textviews_pu_sets + en_PUSets_tv_setsply1, var_glob.games_for_player[0], AND_SHOW);
	// ToDo Trama.rellenaYEnviaTrama(K.messagePuntos); 
}
/**
 * \brief		Increment the number games for player 1
 * \param[in]   none
 * \return      none
 */
static void action_incr_games_for_1(void) {
    INCR_GAMES_FOR_PLAYER(1);

    replace_text_in_textview_with_number(textviews_pu_sets + en_PUSets_tv_setsply1, var_glob.games_for_player[0], AND_SHOW);
	// ToDo Trama.rellenaYEnviaTrama(K.messagePuntos); 
}
/**
 * \brief		Decrement the number games for player 2
 * \param[in]   none
 * \return      none
 */
static void action_decr_games_for_2(void) {
    DECR_GAMES_FOR_PLAYER(2);

    replace_text_in_textview_with_number(textviews_pu_sets + en_PUSets_tv_setsply2, var_glob.games_for_player[1], AND_SHOW);
	// ToDo Trama.rellenaYEnviaTrama(K.messagePuntos); 
}
/**
 * \brief		Increment the number games for player 2
 * \param[in]   none
 * \return      none
 */
static void action_incr_games_for_2(void) {
	INCR_GAMES_FOR_PLAYER(2);

    replace_text_in_textview_with_number(textviews_pu_sets + en_PUSets_tv_setsply2, var_glob.games_for_player[1], AND_SHOW);
	// ToDo Trama.rellenaYEnviaTrama(K.messagePuntos); 
}
/**
 * \brief       Return to the score annotation GUI
 * \param[in]   none
 * \return      none
 */
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


