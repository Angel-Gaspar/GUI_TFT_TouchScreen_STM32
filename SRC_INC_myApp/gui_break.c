/**
 * \file            gui_break.c
 * \brief           GUI for the break and heating 
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

#include "gui_break.h"
#include "includes.h"
#include "gui_match_conf.h"
#include "gui_score.h"

static const u8 this_window = GUI_BREAK;
static u32 allowed_time;
warning_t message_extend_5sets;

static void manage_this_timer(u32 ellapsed_time_ms);

static void action_decr_games_for_1(void);

static void action_incr_games_for_1(void);

static void action_decr_games_for_2(void);

static void action_incr_games_for_2(void);

/* --------------  WARM-UP and BREAK WINDOW -------------------------------- */

/* -------------------- COMPONENT DEFINITIONS ------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Component_Definitions
#endif

#define HAS_BUTTONS         1
#define HAS_RADIO_BUTTONS   0
#define HAS_LABELS          1
#define HAS_REGIONS      1
#define HAS_CHECKBOXES      1
#define HAS_TEXTVIEWS       1

#define C_FONT_SIZE_JUG        FONT16
#define C_MARGIN_BUT_PLAYER 1.2

#if HAS_BUTTONS
static button_t buttons_break[] =
        { { action_goto_start, Kst_GOTOSTART, { Center, 70, 100, 100, 40,
        YELLOW }, BLACK, C_FONT_SIZE_JUG, ENABLED, VISIBLE }

        , { action_break_reset_score, Kst_SCORETO0, { Center, 70, 150, 100, 40,
        ORANGE }, BLACK, C_FONT_SIZE_JUG, ENABLED, VISIBLE }

        , { action_start_game, Kst_STARTGAME, { Center, 220, 135, 140, 60,
        PURPLE_RED }, LILA, FONT24, ENABLED, VISIBLE }\
,
                { action_decr_games_for_1, (u8*) "-1", { Center, 80,
                        (u16) (LCD_H * 0.76), 80, 40, BLACK }, LILA, FONT24,
                        ENABLED, VISIBLE }\
, { action_incr_games_for_1,
                        (u8*) "+1", { Center, 80, (u16) (LCD_H * 0.9), 80, 40,
                                GRAY }, LILA, FONT24, ENABLED, VISIBLE }\
, {
                        action_decr_games_for_2, (u8*) "-1", { Center
                                | H_Simmetry, 80, (u16) (LCD_H * 0.76), 80, 40,
                                BLACK }, LILA, FONT24, ENABLED, VISIBLE }\
, {
                        action_incr_games_for_2, (u8*) "+1", { Center
                                | H_Simmetry, 80, (u16) (LCD_H * 0.9), 80, 40,
                                GRAY }, LILA, FONT24, ENABLED, VISIBLE }
#if defined WIN32
	,{simul_timer, (u8*)"T", {Center, 300,460,10,10,GREEN},LILA,FONT12,ENABLED, VISIBLE}  // To simulate systicks
#endif
        };
typedef enum {
    en_Break_bt_back,
    en_Break_bt_Reset,
    en_Break_bt_Score,
    en_Break_bt_Minus1_Play1,
    en_Break_bt_Plus1_Play1,
    en_Break_bt_Minus1_Play2,
    en_Break_bt_Plus1_Play2
} button_break_t;
#endif

#if HAS_RADIO_BUTTONS
/*group_radiobutton_t radio_but_break[] = {
    {2, 20, 40, RAD_BUT_SEP_V, RAD_BUT_FONT, WHITE, YELLOW, 0, (u8*) "3 sets\0 5 sets\0", ENABLED, VISIBLE}  
    ,{2, 200, 40, RAD_BUT_SEP_V, RAD_BUT_FONT, WHITE, YELLOW, 0, (u8*) "Normal\0 Invertida\0", ENABLED, VISIBLE}
};*/
#endif

#if HAS_REGIONS
static region_t regions_break[] = { { Left_Top, 0, 0, LCD_W,
        (u16) (LCD_H * 0.7), LIGHTGRAY }, { Left_Top, 0, (u16) (LCD_H * 0.7),
        LCD_W, (u16) (LCD_H * 0.3), LILA } };
#endif

#if HAS_CHECKBOXES
checkbox_t checkBoxes_break[] = { { func_no_action, Kst_To5andSTART, 140, 80,
        the_right, BLUE, /*LIGHTGRAY,*/FONT16, CHECKED, ENABLED, VISIBLE } };
#endif

#if HAS_LABELS
static label_t labels_break[] = { { Left_Top, 20, 22, GRAY, /*LIGHTGRAY,*/
        FONT16, Kst_TIMEREMAIN, VISIBLE }, { Left_Top, 20, 40, GRAY, /*LIGHTGRAY,*/
        FONT16, Kst_ELAPSEDTIME, VISIBLE }, { Center, 160, 220, PURPLE_RED, /*LIGHTGRAY,*/
        FONT24, Kst_VS, VISIBLE }, { Center, 100, 250, PURPLE_RED, /*LIGHTGRAY,*/
        FONT24, Kst_GAMES_, VISIBLE }, { Center, 80, (u16) (LCD_H * 0.83),
        DARKGRAY, /*LILA,*/FONT16, Kst_GAMESPLAYER1, VISIBLE }, { Center
        | H_Simmetry, 80, (u16) (LCD_H * 0.83), DARKGRAY, /*LILA,*/FONT16,
        Kst_GAMESPLAYER2, VISIBLE } };
enum label_break {
    en_Break_lb_rem_time,
    en_Break_lb_ellapsed_time,
    en_Break_lb_name,
    en_Break_lb_sets,
    en_Break_lb_sets_pl1,
    en_Break_lb_sets_pl2
};
#endif

#if HAS_TEXTVIEWS
static textview_t textviews_break[] = { { Left_Top, 200, 20, PURPLE_BLUE, /*LIGHTGRAY ,*/
        FONT16, VISIBLE /*, (u8*)"05:00"*/}, { Left_Top, 200, 40, PURPLE_BLUE, /*LIGHTGRAY ,*/
        FONT16, VISIBLE /*, (u8*)"0:00"*/}, { Center, 190, 250, PURPLE_RED, /*LIGHTGRAY ,*/
        FONT24, VISIBLE /*, (u8*)"0:0"*/}, { Center, 160, 280, PURPLE_RED, /*LIGHTGRAY ,*/
        FONT16, VISIBLE /*, (u8*)"0:0"*/}, { Right_Center, 130, 220, PURPLE_RED, /*LIGHTGRAY ,*/
        FONT24, VISIBLE }, { Left_Center, 190, 220, PURPLE_RED, /*LIGHTGRAY ,*/
        FONT24, VISIBLE } };

enum textview_break {
    en_Break_tv_rem_time,
    en_Break_tv_ellapsed_time,
    en_Break_tv_sets,
    en_Break_tv_serie_of_sets,
    en_Break_tv_name_pl1,
    en_Break_tv_name_pl2
};
#endif

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Component_Definitions
#endif

/* -------------------- GUI CREATION ----------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region GUI_Creation
#endif
/**
 * \brief		Assign to var_glob the arrays of component for this window and draw the components
 * \param[in]   none
 * \return      none
 */
void set_window_break() {
    UPDATE_ACTIVE_WINDOW
    ;

    reset_numbers_GUI();

    // Initialize buttons
#if HAS_BUTTONS
    gui.buttons = buttons_break;
    gui.num_buttons = sizeof(buttons_break) / sizeof(button_t);
#endif

#if HAS_RADIO_BUTTONS
    gui.radio_but = radio_but_break;
	gui.num_groups_radio_but = sizeof(radio_but_break) / sizeof(group_radiobutton_t);    
#endif
    // Initialize radio buttons

#if HAS_REGIONS
    gui.regions = regions_break;
    gui.num_regions = sizeof(regions_break) / sizeof(region_t);
#endif

#if HAS_LABELS
    gui.labels = labels_break;
    gui.num_labels = sizeof(labels_break) / sizeof(label_t);
#endif

#if HAS_TEXTVIEWS
    gui.textviews = textviews_break;
    gui.num_textviews = sizeof(textviews_break) / sizeof(textview_t);
#endif

#if HAS_TEXTBOXES
    gui.textboxes = textboxes_break;
	gui.num_textboxes = sizeof(textboxes_break) / sizeof (textbox_t);    
#endif

#if HAS_CHECKBOXES
    gui.checkboxes = checkBoxes_break;
    gui.num_checkboxes = sizeof(checkBoxes_break) / sizeof(checkbox_t);
#endif

    operations_pre_initialize_break();
    initialize_active_window();
    operations_post_initialize_break();

}

/**
 * \brief		Operations to do before the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_pre_initialize_break(void) {

    set_start_time();

    gui.manage_specific_timer = manage_this_timer;

    if (get_played_games() == 0) {
        allowed_time = var_glob.seconds_warmup;
    } else {
        allowed_time = var_glob.seconds_break;
    }

    gui.checkboxes[0].is_checked = 1;

    //  Trama.rellenaYEnviaTrama(K.messageSets)

    define_start_button_and_checkbox(ONLY_ASSIGN);

    replace_text_in_textview(gui.textviews + en_Break_tv_name_pl1,
            var_glob.name_shown_for_player[0], ONLY_ASSIGN);
    replace_text_in_textview(gui.textviews + en_Break_tv_name_pl2,
            var_glob.name_shown_for_player[1], ONLY_ASSIGN);
}
/**
 * \brief		Operations to do just after the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_post_initialize_break(void) {
    show_score();

    show_games();

	gui.timer_enabled = 1;
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion GUI_Creation
#endif

/* -------------------- ACTIONS WHEN PRESSING THE BUTTONS  ------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region ACTIONS
#endif
/**
 * \brief		Go to the configuration window.
 * \param[in]   none
 * \return      none
 */
void action_goto_start(void) {
    start_match();
    set_window_match_configuration();
}
/**
 * \brief		Reset the score (points and games)
 * \param[in]   none
 * \return      none
 */
void action_break_reset_score(void) {
    // ToDo
}
/**
 * \brief		Start the game
 * \param[in]   none
 * \return      none
 */
void action_start_game(void) {
    if (!is_feasible_extend_to_5_games()) {
        set_window_score();
        return;
    }

    fill_message(&message_extend_5sets, Kst_end_game_3games,
    Kst_extend_to_5games_, 2, Kst_YES, Kst_NO, NULL);
    gui.timer_enabled = 0;
    u8 option = show_popup_and_wait_for_answer(&message_extend_5sets);

    if (option == 0) { // Yes --> Extend to 5 sets (three to win)
        var_glob.games_to_win_the_match = 3;
        if (gui.checkboxes[1].is_checked) { // Go to score window
            set_window_score();
        } else {
            define_start_button_and_checkbox(AND_SHOW);
            set_window_break();
        }
    } else {  // No --> Keep in 3 sets (two to win)
        define_start_button_and_checkbox(AND_SHOW);
    	gui.timer_enabled = 1;
    	set_window_break();
    }
}
/**
 * \brief		decrease the number of won games for player 1
 * \param[in]   none
 * \return      none
 */
static void action_decr_games_for_1(void) {
    DECR_GAMES_FOR_PLAYER(1);
    show_games();
    define_start_button_and_checkbox(AND_SHOW);
    //Trama.rellenaYEnviaTrama(K.messageSets);
}
/**
 * \brief		Increase the number of won games for player 1
 * \param[in]   none
 * \return      none
 */
static void action_incr_games_for_1(void) {
    INCR_GAMES_FOR_PLAYER(1);
    show_games();
    define_start_button_and_checkbox(AND_SHOW);
    //Trama.rellenaYEnviaTrama(K.messageSets);
}
/**
 * \brief		decrease the number of won games for player 2
 * \param[in]   none
 * \return      none
 */
static void action_decr_games_for_2(void) {
    DECR_GAMES_FOR_PLAYER(2);
    show_games();
    define_start_button_and_checkbox(AND_SHOW);
    //Trama.rellenaYEnviaTrama(K.messageSets);
}
/**
 * \brief		Increase the number of won games for player 2
 * \param[in]   none
 * \return      none
 */
static void action_incr_games_for_2(void) {
    INCR_GAMES_FOR_PLAYER(2);
    show_games();
    define_start_button_and_checkbox(AND_SHOW);
    //Trama.rellenaYEnviaTrama(K.messageSets);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion ACTIONS
#endif

/* -------------------- FUNCTION TO UPDATE THE COMPONENTS ------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region UPDATE_COMPONENT
#endif

/**
 * \brief		Display the complete score (points for each game)
 * \param[in]   none
 * \return      none
 */
void show_score(void) {
    replace_text_in_textview(&gui.textviews[en_Break_tv_serie_of_sets],
            get_string_points(), AND_SHOW);
}
/**
 * \brief		Display the games for every player
 * \param[in]   none
 * \return      none
 */
void show_games(void) {
    // func_eeprom.write_state()
    u8 *string_sets = get_string_games();

    replace_text_in_textview(&gui.textviews[en_Break_tv_sets], string_sets,
            AND_SHOW);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion UPDATE_COMPONENT
#endif

/**
 * \brief		Define the characteristics of Start Button
 *				It is called at the beginning, when games are changed, or when it is confirmed
 * 					to extend to 5 games, with the checkbox unmarked
 * \param[in]   redraw; if 0, only assign; if 1, assign and draw
 * \return      none
 */

void define_start_button_and_checkbox(_Bool redraw) {
    button_t *start_button = &gui.buttons[en_Break_bt_Score];
    /* ---------- Definici�n del text del Bot�n -----------------*/
    if (is_feasible_extend_to_5_games()) {
        start_button->text = Kst_extend_to_5games;

    } else {
        u8 num_sets = get_played_games() + 1;
        u8 string_aux[20];
        my_itoa(num_sets, string_aux, 0);
        start_button->text = my_strcat(Kst_STARTGAME, string_aux);
    }

    /* ---------- Definici�n de la visibilidad  del Bot�n -----------------*/
    start_button->visible =
            (some_player_won_the_match() && var_glob.games_to_win_the_match == 3) ?
                    INVISIBLE : VISIBLE;
    if (redraw) {
        draw_button(gui.buttons + en_Break_bt_Score);
    }
    /* ---------- Definici�n de la visibilidad  del Checkbox -----------------*/
    gui.checkboxes[0].visible =
            is_feasible_extend_to_5_games() ? VISIBLE : INVISIBLE;
    if (redraw) {
        draw_checkbox(gui.checkboxes + 0);
    }
}
/* -------------------- MANAGE THE TIMER   ---------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region TIMER
#endif

/**
 * \brief		Periodical tasks to carry out: show the remaining and ellapsed time. 
 * \param[in]   none
 * \return      none
 */
static void manage_this_timer(u32 ellapsed_time_ms) {
    u16 ellapsed_time_s = ellapsed_time_ms / 1000;
    replace_text_in_textview(gui.textviews + en_Break_tv_ellapsed_time,
            seconds_2_string_minutes_seconds(ellapsed_time_s), AND_SHOW);
    u16 rem_time = allowed_time - ellapsed_time_s;
    replace_text_in_textview(gui.textviews + en_Break_tv_rem_time,
            seconds_2_string_minutes_seconds(rem_time), AND_SHOW);
}
/**
 * \brief		A simple button to force the gui to display the ellapsed and remaining time		
 * \param[in]   none
 * \return      none
 */
#if defined WIN32
static void simul_timer(void)
{
	manage_timer();
}
#endif
#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion TIMER
#endif

#undef HAS_BUTTONS
#undef HAS_RADIO_BUTTONS
#undef HAS_LABELS
#undef HAS_REGIONS
#undef HAS_TEXTBOXES
#undef HAS_CHECKBOXES    
