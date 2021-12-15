/**
 * \file            gui_match_conf.c
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

#include "includes.h"
#include "gui_match_conf.h"
#include "gui_definplayer.h"
#include "gui_break.h"

static const u8 this_window = GUI_MATCH_CONF;
_Bool comprobar_bluetooth = 1;
_Bool unique_device = 0;

/* -------------------- COMPONENT DEFINITIONS ------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region Component_Definitions
#endif

#define HAS_BUTTONS				1
#define HAS_RADIO_BUTTONS		1
#define HAS_LABELS				1
#define HAS_REGIONS			1
#define HAS_CHECKBOXES			0

#define C_FONT_SIZE_JUG			FONT16
#define C_MARGIN_BUT_PLAYER		2.5
#define C_WIDTH_BT_PLAYER		(u8)(MAX_NAME_SIZE*C_FONT_SIZE_JUG)
#define C_HEIGHT_BT_PLAYER		(u8)(C_FONT_SIZE_JUG*C_MARGIN_BUT_PLAYER+4)

#if HAS_BUTTONS
button_t buttons_conf[] = { { action_player1, Kst_PLAYER1, { Center, (u8) (20
        + C_WIDTH_BT_PLAYER / 2), 170,
C_WIDTH_BT_PLAYER, 40, YELLOW }, BLACK, C_FONT_SIZE_JUG, ENABLED, VISIBLE }

, { action_player2, Kst_PLAYER2, { Center | H_Simmetry, 20
        + C_WIDTH_BT_PLAYER / 2, 170,
C_WIDTH_BT_PLAYER, 40, ORANGE }, BLACK, C_FONT_SIZE_JUG, ENABLED, VISIBLE }

, { action_warmup, Kst_WARMUP, { Center, LCD_W / 2, 240, 120, 70, BLUE }, LILA,
        FONT24, ENABLED, VISIBLE }

, { action_recover_data, Kst_RECOVER,
        { Center, 80, Esc_Vrt(0.65), 80, 30, LILA }, BLACK, FONT16, ENABLED,
        VISIBLE }

, { action_reset_scores, Kst_SCORETO0, { Center | H_Simmetry, 80, Esc_Vrt(0.65),
        80, 30, LILA }, BLACK, FONT16, ENABLED, VISIBLE }

, { action_connect_BT, Kst_ToON, { Center, 60, (u16) (LCD_H * 0.9), 80, 40,
        BLACK }, LILA, FONT24, ENABLED, VISIBLE }

, { action_disconnect_BT, Kst_ToOFF, { Center, 180, (u16) (LCD_H * 0.9), 80, 40,
        GRAY }, LILA, FONT24, ENABLED, VISIBLE } };
typedef enum {
    en_Conf_bt_Jug1,
    en_Conf_bt_Jug2,
    en_Conf_bt_Break,
    en_Conf_bt_Recup,
    en_Conf_bt_Reset,
    en_Conf_bt_aON,
    en_Conf_bt_aOFF
} en_button_conf_t;
#endif

#if HAS_RADIO_BUTTONS
static group_radiobutton_t radio_but_conf[] = { { func_no_action, 2, 20, 40,
        RAD_BUT_FONT, BLACK, /*GRAY,*/0, Kst_rb_3_5_games, ENABLED, VISIBLE }, {
        func_no_action, 2, 160, 40, RAD_BUT_FONT, BLACK, /*GRAY,*/0,
        Kst_rb_ORIENTATION, ENABLED, VISIBLE } };
typedef enum {
    en_Conf_rb_3_5sets, en_Conf_rb_invert
} en_radio_button_conf_t;
#endif

#if HAS_REGIONS
static region_t regions_conf[] = {
        { Left_Top, 0, 0, LCD_W, Esc_Vrt(0.77), GRAY }, { Left_Top, 0, Esc_Vrt(
                0.77), LCD_W, Esc_Vrt(0.23), LILA }, { Left_Center, 250,
                Esc_Vrt(0.9), Esc_Vrt(0.1), Esc_Vrt(0.1), RED } };
#endif

#if HAS_LABELS
static label_t labels_conf[] = { { Left_Top, 20, Esc_Vrt(0.73), BLACK, /*GRAY,*/
        FONT16, Kst_PUNTOS, VISIBLE }, { Left_Top, 40, Esc_Vrt(0.79), BLACK, /*GRAY,*/
        FONT16, Kst_string_emparejado_con, INVISIBLE }, { Left_Top, 20, 12,
        BLACK, /*GRAY,*/FONT16, Kst_NUM_GAMES, VISIBLE }, { Left_Top, 160, 12,
        BLACK, /*GRAY,*/FONT16, Kst_ORIENTATION, VISIBLE }, { Left_Top, 20, 120,
        BLACK, /*GRAY,*/FONT16, Kst_DEFINEPLAYER1, VISIBLE }, { Left_Top, 170,
        120, BLACK, /*GRAY,*/FONT16, Kst_DEFINEPLAYER2, VISIBLE },
        { Center, LCD_W / 2, Esc_Vrt(0.8), BLUE, /*LILA,*/FONT24,
                Kst_ConnectLeds, VISIBLE } };
typedef enum {
    en_Conf_lb_points,
    en_Conf_lb_matched,
    en_Conf_lb_numsets,
    en_Conf_lb_orient,
    en_Conf_lb_defplyr1,
    en_Conf_lb_defplyr2,
    en_Conf_lb_Connect_leds
} en_labels_conf_t;
#endif

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion Component_Definitions
#endif

/* -------------------- GUI CREATION ---------------------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region GUI_Creation
#endif

/**
 * \brief		Assign to var_glob the arrays of component for this window and draw the components
 * \param[in]   none
 * \return      none
 */
void set_window_match_configuration() {
    UPDATE_ACTIVE_WINDOW
    ;

    reset_numbers_GUI();

    // Initialize buttons
#if HAS_BUTTONS
    gui.buttons = buttons_conf;
    gui.num_buttons = sizeof(buttons_conf) / sizeof(button_t);

#endif

#if HAS_RADIO_BUTTONS
    gui.radio_but = radio_but_conf;
    gui.num_groups_radio_but = sizeof(radio_but_conf)
            / sizeof(group_radiobutton_t);

#endif
    // Initialize radio buttons

#if HAS_REGIONS
    gui.regions = regions_conf;
    gui.num_regions = sizeof(regions_conf) / sizeof(region_t);

#endif

#if HAS_LABELS
    gui.labels = labels_conf;
    gui.num_labels = sizeof(labels_conf) / sizeof(label_t);

#endif

#if HAS_CHECKBOXES
    gui.checkboxes = checkBoxes_conf;
    gui.num_checkboxes = sizeof(checkBoxes_conf) / sizeof (checkbox_t);
#endif

#if HAS_TEXTBOXES
    gui.textboxes = textboxes_conf;
	gui.num_textboxes = sizeof(textboxes_conf) / sizeof (textbox_t);    
#endif

    operations_pre_initialize_configuration();

    initialize_active_window();
}

/**
 * \brief		Operations to do before the initial representation of this window
 * \param[in]   none
 * \return      none
 */
void operations_pre_initialize_configuration(void) {
//#if !defined WIN32
    if (gui.procedence_window == GUI_START_APP) {
        Initialize_Global_Variables();
    }
//#endif

    if (!bluetooth.socket_is_set && comprobar_bluetooth) {
        actions_when_bluetooth_is_connected();
        comprobar_bluetooth = 0;
    }
    set_operative_buttons(ONLY_ASSIGN);

    mark_radio_buttons(2);

    set_buttons_Bluetooth(0);

    set_names_and_colours();

    display_partial_scores();
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion GUI_Creation
#endif

/* -------------------- ACTIONS WHEN PRESSING THE BUTTONS  ------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region ACTIONS
#endif

/**
 * \brief		Launch the GUI that defines the name and color of player 1
 * \param[in]   none
 * \return      none
 */
void action_player1(void) {
    set_window_definplayer(1);
}

/**
 * \brief		Launch the GUI that defines the name and color of player 1
 * \param[in]   none
 * \return      none
 */
void action_player2(void) {
    set_window_definplayer(2);
}
/**
 * \brief		Launch the gui that manages warm-up and break
 * \param[in]   none
 * \return      none
 */
void action_warmup(void) {
    /* if (var_glob.player_is_defined[0] &&  var_glob.player_is_defined[1])
     {
     fill_message(& gui.message, Kst_BothPlayers, Kst_MustBeDefined,
     1,  Kst_BACK, (u8*)"", (u8*)"");

     u8 option = show_popup_and_wait_for_answer(&gui.message);
     set_window_match_configuration();
     return;
     } */
    // ToDo func_eeprom.write_state()
    read_radio_buttons();
    set_window_break();
}

/**
 * \brief		Connect the Bluetooth
 * \param[in]   none
 * \return      none
 */
void action_connect_BT(void) {
    // ToDo
}

/**
 * \brief		Disconnect the Bluetooth
 * \param[in]   none
 * \return      none
 */
void action_disconnect_BT(void) {
    // ToDo
}

/**
 * \brief		Recover the data in case of reseting the device
 * \param[in]   none
 * \return      none
 */
void action_recover_data(void) {
    var_glob.player_is_defined[0] = 1;
    var_glob.player_is_defined[1] = 1;

    // ToDo func_eeprom.read_state(applicationContext)
    set_names_and_colours();

    set_operative_buttons(AND_SHOW);

    display_partial_scores();
}

/**
 * \brief		Reset the points and games
 * \param[in]   none
 * \return      none
 */
void action_reset_scores(void) {
    start_match();
    // ToDo func_eeprom.write_state()
    display_partial_scores();
    gui.buttons[en_Conf_bt_Reset].enabled = DISABLED;
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion ACTIONS
#endif

/* -------------------- BEHAVIOUR OF COMPONENTS: VISIBLE AND ENABLE  ------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region VISIBLE_ENABLE
#endif

/**
 * \brief		Show or hide the buttons to connect or disconnect the bluetooth. Display also messages about BT.
 * \param[in]   redraw: if 1, draw buttons; if 0, only assign
 * \return      none
 */
void set_buttons_Bluetooth(_Bool redraw) {
    //
    if (!bluetooth.socket_is_set) {
        gui.labels[en_Conf_lb_matched].text = Kst_conectar_por_BT;
        gui.labels[en_Conf_lb_matched].colour_text = DARKBLUE;

        gui.buttons[en_Conf_bt_aOFF].visible = INVISIBLE;
        gui.buttons[en_Conf_bt_aON].visible = VISIBLE;
    } else {
        gui.labels[en_Conf_lb_matched].text = my_strcat(
                Kst_string_emparejado_con, bluetooth.name);
        gui.labels[en_Conf_lb_matched].colour_text = RGB24_2_RGB16(0x10, 0xEE,
                0x10);

        gui.buttons[en_Conf_bt_aON].visible = INVISIBLE;
        gui.buttons[en_Conf_bt_aOFF].visible = VISIBLE;

        // ToDo Trama.rellenaYEnviaTrama(K.messageBT)
    }
    if (redraw) {
        display_label(&gui.labels[en_Conf_lb_matched]);
        draw_button(&gui.buttons[en_Conf_bt_aOFF]);
        draw_button(&gui.buttons[en_Conf_bt_aON]);
    }

}

/**
 * \brief		Make visible and enable the buttons that can be used
 * \param[in]   none
 * \return      none
 */
void set_operative_buttons(_Bool redraw) {
    gui.buttons[en_Conf_bt_Break].enabled = (var_glob.player_is_defined[0]
            && var_glob.player_is_defined[1]);

    //gui.buttons[Recover].enabled = func_eeprom.existeFicheroDefinicion();

    gui.buttons[en_Conf_bt_Reset].enabled = (get_played_games() > 0);
    if (redraw) {
        draw_button(gui.buttons+en_Conf_bt_Break);
        draw_button(gui.buttons+en_Conf_bt_Reset);
    }
}
/**
 * \brief		Assign the corresponding colour and name to the players buttons
 * \param[in]   none
 * \return      none
 */
void set_names_and_colours(void) {
    //if (var_glob.player_is_defined[0]){
    set_colours_and_name_to_button_player(gui.buttons + en_Conf_bt_Jug1, 1);
    //}
    //if (var_glob.player_is_defined[1]) {
    set_colours_and_name_to_button_player(gui.buttons + en_Conf_bt_Jug2, 2);
    //}
}
/**
 * \brief		Display the points for each game
 * \param[in]   none
 * \return      none
 */
void display_partial_scores() {
    gui.labels[en_Conf_lb_points].text = get_string_points();
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion VISIBLE_ENABLE
#endif

/* -------------------- INTERACTIONS WITH RADIO BUTTONS  ------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region RADIO_BUTTON
#endif
/**
 * \brief		Represent the selected option of every radio group as marked
 * \param[in]   none
 * \return      none
 */
void mark_radio_buttons(u8 opcion) {
    gui.radio_but[en_Conf_rb_3_5sets].index_selected =
            var_glob.games_to_win_the_match == 2 ? 0 : 1;

    gui.radio_but[en_Conf_rb_invert].index_selected =
            var_glob.pannel_is_inverted ? 1 : 0;
}
/**
 * \brief		Read the selected option for the radio groups
 * \param[in]   none
 * \return      none
 */
void read_radio_buttons(void) {
    var_glob.pannel_is_inverted =
            (gui.radio_but[en_Conf_rb_invert].index_selected == 1);
    var_glob.games_to_win_the_match =
            gui.radio_but[en_Conf_rb_3_5sets].index_selected == 0 ? 2 : 3;
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion RADIO_BUTTON
#endif

/* ----------------------------- BLUETOOTH FUNCTIONS  ----------------------------*/

#if defined PRAGMA_REGION_ACCEPTED
#pragma region BLUETOOTH
#endif
/**
 * \brief		Match this device with the remote slave
 * \param[in]   none
 * \return      none
 */
void match_bluetooth(void) {
    /* ToDo
     val intent = Intent(this, BluetoothConnection::class.java)
     startActivity(intent)
     */
}
/**
 * \brief		Disconnect this device from the bluetooth
 * \param[in]   none
 * \return      none
 */
void disconnect_bluetooth(void) {
    /* ToDo
     if (BluetoothGlob.socket_is_set() ) {
     if (!BluetoothGlob.disconnect())
     {
     Toast.makeText(this, R.string.bt_conn_failed, Toast.LENGTH_LONG).show()
     return
     }
     }

     mostrar_buttons_Bluetooth()*/
}
/**
 * \brief		Perform the required tasks when the bluetooth has just connected
 * \param[in]   none
 * \return      none
 */
void actions_when_bluetooth_is_connected() {
    if (!unique_device)
        return;

    // ToDo bluetooth.address = BluetoothGlob.is_a_slave_near(BluetoothGlob.prefijo)

    //  Bluetooth   BluetoothGlob.establish_Socket(BluetoothGlob.address)
}

#if defined PRAGMA_REGION_ACCEPTED
#pragma endregion BLUETOOTH
#endif

#undef HAS_BUTTONS
#undef HAS_RADIO_BUTTONS
#undef HAS_LABELS
#undef HAS_REGIONS
#undef HAS_TEXTBOXES
#undef HAS_CHECKBOXES    
