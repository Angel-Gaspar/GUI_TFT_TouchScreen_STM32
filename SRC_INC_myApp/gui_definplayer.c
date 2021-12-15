/**
 * \file            gui_definplayer.c
 * \brief           GUI for the definition of colour and name
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

#include "gui_definplayer.h"
#include "includes.h"
#include "gui_score.h"
#include "gui_match_conf.h"
#include "gui_popupspecial.h"
#include "keyboard.h"

static const u8 this_window = GUI_PLAYERS_DEF;
u8 player_from_1;
static _Bool text_defined;
static _Bool colour_defined;

/* --------------------COMPONENT DEFINITIONS ------------------------------ */

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Component_Definitions
#endif

#define HAS_BUTTONS             1
#define HAS_RADIO_BUTTONS       1
#define HAS_LABELS              1
#define HAS_REGIONS          1
#define HAS_CHECKBOXES          0
#define HAS_TEXTBOXES           1
#define HAS_TEXTVIEWS           1

#define C_FONT_SIZE_JUG        FONT24
#define C_FONT_SIZE_JUGH       V2H(C_FONT_SIZE_JUG)
#define C_WIDTH_BT_colour  40
#define C_HEIGHT_BT_colour 40 

#if HAS_BUTTONS
button_t buttons_def[] = {
    {action_return, Kst_RETURN, {Center, 240, 320,
        C_FONT_SIZE_JUGH*8, C_HEIGHT_BT_colour, BLACK}, WHITE, C_FONT_SIZE_JUG, ENABLED, VISIBLE}

    ,{ action_Red, (u8*) " ", {Center, 50, 40,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, RED}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_Green, (u8*) " ", {Center, 120, 40,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, GREEN}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_Yellow, (u8*) " ", {Center, 190, 40,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, YELLOW}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_Cyan, (u8*) " ", {Center, 260, 40,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, CYAN}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_Blue, (u8*) " ", {Center, 80, 100,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, BLUE}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_Magenta, (u8*) " ", {Center, 150, 100,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, MAGENTA}, BLACK, FONT16, ENABLED, VISIBLE}

    ,{ action_White, (u8*) " ", {Center, 220, 100,
        C_WIDTH_BT_colour, C_HEIGHT_BT_colour, WHITE}, BLACK, FONT16, ENABLED, VISIBLE}
};

typedef enum {
	en_Def_bt_Retornar, 
	en_Def_bt_Red, 
	en_Def_bt_Green, 
	en_Def_bt_Yellow, 
	en_Def_bt_Cyan, 
	en_Def_bt_Blue, 
    en_Def_bt_Magenta,     
	en_Def_bt_White
} en_button_defpl_t;
#endif

#if HAS_RADIO_BUTTONS
group_radiobutton_t radio_but_def[] = {
    {action_serveside, 2, 20, 160, RAD_BUT_FONT, BLACK, /*LILA ,*/ 0, Kst_rb_RIGHTLEFTHANDED, ENABLED, VISIBLE}  
};

typedef enum  {
	en_Def_rb_zurdo
} radio_button_defpl_t;
#endif


#if HAS_REGIONS
static region_t regions_def[] = {
     {Left_Top, 0,    0, (u16)(LCD_W), (int)(LCD_H*0.8), LILA  }
    ,{Left_Top, 0,    (u16)(LCD_H*0.8), LCD_W, (int)(LCD_H*0.2), DARKGRAY  }
}; 
#endif

#if HAS_LABELS
static label_t labels_def[] = {
	{Left_Center, 30, 285,          BLACK, /*LILA,*/ FONT16, Kst_def_TYPEtoCHANGE, VISIBLE}
};
typedef enum {
	en_Def_tv_type_tochange
} en_labels_defpl_t;
#endif

#if HAS_TEXTVIEWS 
static textview_t textviews_def[] = {
    {Left_Center, 30, 355,        BLACK, /*LILA,*/ FONT16, VISIBLE}
};
typedef enum en_textviews_defpl_t {
	en_Def_tv_name_plx
} en_textviews_defpl_t;
#endif

#if HAS_TEXTBOXES
static    textbox_t textboxes_def[] = {
     {Center, 85, 320, 110, GRAY, YELLOW, FONT24, VISIBLE, ENABLED}
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
 * \param[in]   in_player_from_1: the player to be configured
 * \return      none
 */
void set_window_definplayer(u8 in_player_from_1)
{    
    player_from_1 = in_player_from_1;

    UPDATE_ACTIVE_WINDOW;

    gui.pmanage_Pressed_textbox = manage_pressed_textbox_defin_player;

	reset_numbers_GUI();

    // Initialize buttons
#if HAS_BUTTONS
    gui.buttons = buttons_def;
	gui.num_buttons = sizeof(buttons_def) / sizeof(button_t);    
#endif

#if HAS_RADIO_BUTTONS
    gui.radio_but = radio_but_def;
	gui.num_groups_radio_but = sizeof(radio_but_def) / sizeof(group_radiobutton_t);    
#endif
    // Initialize radio buttons

#if HAS_REGIONS
    gui.regions = regions_def;
	gui.num_regions = sizeof(regions_def) / sizeof (region_t);    
#endif

#if HAS_LABELS
    gui.labels = labels_def;
	gui.num_labels = sizeof(labels_def) / sizeof (label_t);    
#endif

#if HAS_TEXTVIEWS
    gui.textviews = textviews_def;
    gui.num_textviews = sizeof(textviews_def) / sizeof(textview_t);
#endif

#if HAS_TEXTBOXES
    gui.textboxes = textboxes_def;
	gui.num_textboxes = sizeof(textboxes_def) / sizeof (textbox_t);    
#endif
    
	operations_pre_initialize_defin_player();

    initialize_active_window();

    operations_post_initialize_defin_player();

}
/**
 * \brief		Operations to do before the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_pre_initialize_defin_player(void) {
	my_strcpy(textboxes_def[0].text, var_glob.name_shown_for_player[player_from_1-1]); 
	gui.radio_but[0].index_selected = var_glob.is_left_handed[player_from_1-1] ? 1 : 0;

    u16 back_colour, text_colour;
    get_colours(player_from_1, &back_colour, &text_colour);
    
    gui.textboxes[0].colour_back = back_colour;
    gui.textboxes[0].colour_text = text_colour;
}

/**
 * \brief		Operations to do just after the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_post_initialize_defin_player(void) {
    if (player_from_1 == 1) {
        // replace_text_in_textbox(gui.textboxes+0, Kst_PLAYER1);
		replace_text_in_textview(gui.textviews + en_Def_tv_name_plx, Kst_NAMEPLY1, AND_SHOW);
    
	} else {
        // replace_text_in_textbox(gui.textboxes+0, Kst_PLAYER2);
        replace_text_in_textview(gui.textviews + en_Def_tv_name_plx, Kst_NAMEPLY2, AND_SHOW);
    }
}


#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion GUI_Creation
#endif


/* -------------------- ACTIONS WHEN PRESSING THE BUTTONS AND TEXTBOX ------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region ACTIONS
#endif
/**
 * \brief		Define the actions when the textbox with the player name and color  is pressed
 * \param[in]   pressed_textbox: index of the pressed textbox. In this GUI can be disregarded
 *                  but syntactically must appear as parameters as this is a callback function
 * \return      none
 */
void manage_pressed_textbox_defin_player(s8 pressed_textbox) {
    u8* typed_text = get_Text_from_Keyboard();
	if (typed_text[0] != '\0')
		text_defined = 1;
    assign_player_name(typed_text, player_from_1);
    gui.active_window = gui.procedence_window; // To avoid update the procedence_window
	set_window_definplayer( player_from_1);
	//Replace_textbox(gui.textboxes, typed_text);
    
	my_strcpy(gui.textboxes[0].text, var_glob.name_typed_for_player[player_from_1-1]);
	display_textbox(&gui.textboxes[0]);
	Sleep(200);
}
/**
 * \brief		Define the actions when the textbox with the player name and color  is pressed
 * \param[in]   index_colour: index of the colour assigned to the player
 * \return      none
 */
void action_change_colour(u8 index_colour) {
	var_glob.colour_index[player_from_1 - 1] = index_colour;
    change_colours_of_textbox(textboxes_def, player_from_1) ;
	display_textbox(textboxes_def);
	colour_defined = 1;
}
/**
 * \brief		Assign the color RED to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_Red(void) {
	action_change_colour(ind_RED);
}
/**
 * \brief		Assign the color GREEN to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_Green(void) {
    action_change_colour(ind_GREEN);
}
/**
 * \brief		Assign the color YELLOW to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_Yellow(void) {
    action_change_colour(ind_YELLOW);
}
/**
 * \brief		Assign the color CYAN to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_Cyan(void) {
    action_change_colour(ind_CYAN);
}
/**
 * \brief		Assign the color BLUE to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_Blue(void) {
    action_change_colour(ind_BLUE);
}
/**
 * \brief		Assign the color MAGENTA to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_Magenta(void) {
    action_change_colour(ind_MAGENTA);
}
/**
 * \brief		Assign the color WHITE to the player being defined
 * \param[in]   none
 * \return      none
 */
void action_White(void) {
    action_change_colour(ind_WHITE);
}
/**
 * \brief		Return to the initial (configuration) GUI
 * \param[in]   none
 * \return      none
 */
void action_return(void) {
	colour_defined = var_glob.colour_index[player_from_1-1] != 0;
	text_defined = ! str_equal(Kst_PLAYER1, var_glob.name_typed_for_player[player_from_1-1], 3);

    if (gui.procedence_window == GUI_MATCH_CONF) {
		if (colour_defined && text_defined) {
			var_glob.player_is_defined[player_from_1-1] = 1;
		}
		colour_defined = 0;
		text_defined = 0;
		set_window_match_configuration();
    
    } else if (gui.procedence_window == POPUP_SPEC) {
        set_window_popup_Especiales();
    }
}
/**
 * \brief		Read the radio_button specifying if the player is left-handed or right-handed
 * \param[in]   none
 * \return      none
 */
void action_serveside(void) {
	var_glob.is_left_handed[player_from_1 - 1] = (gui.radio_but[0].index_selected == 1);
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion ACTIONS
#endif

#undef HAS_BUTTONS
#undef HAS_RADIO_BUTTONS
#undef HAS_LABELS
#undef HAS_REGIONS
#undef HAS_TEXTBOXES
#undef HAS_CHECKBOXES    


