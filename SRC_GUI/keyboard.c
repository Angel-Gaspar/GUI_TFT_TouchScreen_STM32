/**
 * \file            keyboard.c
 * \brief           Functions to manage a keyboard to type a text
 */

/*
 * Copyright (c) 2021 Ángel Gaspar González Rodríguez
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
 * Author:      Ángel Gaspar González Rodríguez
 */

#include "keyboard.h"

#include "includes.h"
#include "func_gui_touch.h"


#define HAS_BUTTONS          1
#define HAS_RADIO_BUTTONS    0
#define HAS_LABELS           0
#define HAS_REGIONS       0
#define HAS_CHECKBOXES       0
#define HAS_TEXTBOXES        0

#define K_Margin_pcnt 0.1
#define K_NumFilas 5
#define K_NumCar_fila 6
#define K_Solidity   0.7

#define K_ORG_X (K_Margin_pcnt*LCD_W)
#define K_ORG_Y (LCD_H/2)
#define K_SeparX (LCD_W*(1-2*K_Margin_pcnt)/K_NumCar_fila)
#define K_TAMA_X (K_SeparX*K_Solidity)
#define K_SeparY (LCD_H*0.45/K_NumFilas)
#define K_TAMA_Y (K_SeparY*K_Solidity)
#define K_FONT_SIZE FONT24
#define K_FONT_SIZEV K_FONT_SIZE
#define K_FONT_SIZEH V2H(K_FONT_SIZE)

#define K_FONT_COLOUR YELLOW
#define K_KEY_BACK DARKGRAY

#define K_POS_X_LABEL 100
#define K_POS_Y_LABEL 200

extern volatile _Bool key_pressed;

static void define_key_button(u8 cf, u8 cc, button_t *key) ;

static void show_button_char(u8 cf, u8 cc) ;

static _Bool Pressed_Key(point16 pt, s8* index) ;

static void flash_the_key(s8 index_key) ;

static void get_Text(u8 *text);

static void update_keyboard_label(u8 *text);

static u8 typed_text[MAX_NUM_CHAR_IN_TEXTBOX];

/* ---------------------------  KEYBOARD -----------------------------------------------*/

/**
 * \brief		Display a keyboard and wait for the user to type a text
 * \param[in]   none
 * \return      the typed text
 */

u8* get_Text_from_Keyboard(void) {
	// gui.active_window = KEYBOARD;

    rect16_t rect = { 0, 0, LCD_W, LCD_H};

    draw_rectangle_from_vertices(&rect, LIGHTGRAY, 1, VISIBLE, ENABLED);
    for (u8 cf = 0; cf < K_NumFilas; cf ++)
        for (u8 cc = 0; cc < K_NumCar_fila; cc++)
            show_button_char(cf, cc);
    Sleep(100);
    update_keyboard_label((u8*)"");
    get_Text(typed_text);
    return typed_text;
}

// ------------------------ SHOW the KEYBOARD ---------------------------------------------------*/

/**
 * \brief		Obtain the center location of a certain key
 * \param[in]   cf: row of the key
 * \param[in]   cc: column of the key
 * \param[in]   cx (by reference): x-coordinate of the center of the key
 * \param[in]   cy (by reference): y-coordinate of the center of the key
 * \return      none
 */
void prv_item_2_center(u16 cf, u16 cc, u16 *cx, u16 *cy) {
    *cx = (u16) (K_ORG_X + cc * K_SeparX + K_SeparX/2);
    *cy = (u16) (K_ORG_Y + cf * K_SeparY + K_SeparY/2);
}

/**
 * \brief		Define the parameters of the button for a certain key
 * \param[in]   cf: row of the key
 * \param[in]   cc: column of the key
 * \param[in]   key (by reference): new button to be assigned
 * \return      1 if the key must be shown
 */
static void define_key_button(u8 cf, u8 cc, button_t *key) {
    static u8 string[] = {'O','k','\0'};
    key->font_sizev = K_FONT_SIZE;
    key->visible = 1;
    u8 ind_letter = cf * K_NumCar_fila + cc;
    s8 overpass = ind_letter - ('Z' - 'A');
    if (overpass <= 0)
        string[0] = 'A' + ind_letter;
    else if (overpass == 1)
        string[0] = ' ';
    else if (overpass == 2)
        string[0] = '<';
    else if (overpass == 3) {
        key->visible = INVISIBLE;
        string[0] = ' ';
    }
    if (overpass == 4) {
        string[0] = 'O';
        string[1] = 'k';
    } else {
        string[1] = '\0';
    }

    key->text = string;
    key->colour_text = YELLOW;

    prv_item_2_center(cf, cc, &key->rect.x, &key->rect.y);

    key->rect.width = (u16)K_TAMA_X;
    key->rect.height = (u16)K_TAMA_Y;
    key->rect.colour= K_KEY_BACK;
    key->rect.type_of_reference = Center;
}

/**
 * \brief		Define the parameters of the button for a certain key and show the key
 * \param[in]   cf: row of the key
 * \param[in]   cc: column of the key
 * \return      none
 */
static void show_button_char(u8 cf, u8 cc) {
    button_t letra;
    define_key_button(cf, cc, &letra);
    draw_button(&letra);
}
// ------------------------ DETECT AND MANAGE THE SELECTION OF A KEY ---------------------------------*/
/**
 * \brief		Obtain the index of the key that has been pressed
 * \param[in]   pt: point of the location where the screen has been pressed
 * \param[in]   index (by reference): index of the pressed key (-1 if the screen
 *                  has been pressed outside the keyboard)
 * \param[in]   cx (by reference): x-coordinate of the center of the key
 * \param[in]   cy (by reference): y-coordinate of the center of the key
 * \return      1 if one of the keys has been pressed; 0 otherwise
 */
static _Bool Pressed_Key(point16 pt, s8* index) {
    u8 cc = (u8) ((pt.x - K_ORG_X) / K_SeparX);
    u8 cf = (u8) ((pt.y - K_ORG_Y) / K_SeparY);
    u16 cx, cy;
    prv_item_2_center(cf, cc, &cx, &cy);

    if (ABS(pt.x -cx) < K_TAMA_X/2 && ABS(pt.y - cy) < K_TAMA_Y/2) {
        *index = cf*K_NumCar_fila+cc;
        return 1;
    }
    *index = -1;
    return 0;
}

/**
 * \brief		Make a flash in the button that has been pressed, in order to make visible which key has been pressed
 * \param[in]   pt: point of the location where the screen has been pressed
 * \param[in]   index (by reference): index of the pressed key (-1 if the screen
 *                  has been pressed outside the keyboard)
 * \param[in]   cx (by reference): x-coordinate of the center of the key
 * \param[in]   cy (by reference): y-coordinate of the center of the key
 * \return      1 if one of the keys has been pressed; 0 otherwise
 */
static void flash_the_key(s8 index_key) {
    u8 cf = index_key / K_NumCar_fila;
    u8 cc = index_key % K_NumCar_fila;
    
    button_t letra;
    define_key_button(cf, cc, &letra);
    letra.rect.colour = YELLOW;
    draw_region(&letra.rect, 1, VISIBLE, ENABLED);
    letra.rect.colour = BLACK;
    Sleep(200);
    draw_button(&letra);
}

/**
 * \brief		Wait for the user to type a text
 * \param[in]   the typed text
 * \return      none
 */

static void get_Text(u8 *text)
{
    // gui.active_window = KEYBOARD;
    _Bool pressed_return = 0;
    s16 number_of_valid_letters = -1;

    do{        
        point16 pt;
        if (is_screen_pressed(&pt)) {
			if (number_of_valid_letters == -1) {
				number_of_valid_letters ++;
				continue;
			}

            if (pt.x < 0 || pt.x >  LCD_W)
                continue;
            if (pt.y < 0 || pt.y >  LCD_H)
                continue;
            s8 index;
            if (!Pressed_Key(pt, &index))
                continue;
            flash_the_key(index);

            if (index == 27 && number_of_valid_letters > 0) {
                number_of_valid_letters --;
            } else {
                if (number_of_valid_letters >= MAX_NUM_CHAR_IN_TEXTBOX)
                    continue;
                else if (index == 29){
                    text[number_of_valid_letters] = '\0';
                    return;}
                else if (index == 28)
                    continue;
                else if (index == 26)
                    text[number_of_valid_letters] = ' ';
                else 
                    text[number_of_valid_letters] = 'A'+index;
                number_of_valid_letters ++;
            }
            text[number_of_valid_letters] = '\0';
            update_keyboard_label(text);
        }
        //
        
    } while(!pressed_return);
}

static void update_keyboard_label(u8 *text)
{
    rect16_t vertices;
    vertices.left = (LCD_W - K_FONT_SIZEH * MAX_NUM_CHAR_IN_TEXTBOX)/2;
    vertices.top = K_POS_Y_LABEL - 10;
    vertices.right = vertices.left + K_FONT_SIZEH * MAX_NUM_CHAR_IN_TEXTBOX;
    vertices.bottom = K_POS_Y_LABEL + (u16) (K_FONT_SIZE * MULTIPLIER_HEIGHT_TEXTBOX);

    draw_rectangle_from_vertices (&vertices, BLACK, 1, VISIBLE, ENABLED);
    display_1line_text(K_POS_X_LABEL, K_POS_Y_LABEL, K_FONT_COLOUR, K_FONT_COLOUR,
        text, K_FONT_SIZE, VISIBLE, ENABLED);
}


#undef HAS_BUTTONS
#undef HAS_RADIO_BUTTONS
#undef HAS_LABELS
#undef HAS_REGIONS
#undef HAS_TEXTBOXES
#undef HAS_CHECKBOXES    
