/**
 * \file            func_gui_touch.c
 * \brief           Functions that manage the touch screen, 
 *					and how buttons are pressed
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

#if !defined WIN32
#include "touch.h"
#endif


/* ------------------- DETECTING WHEN A RESPONSIVE COMPONENT IS PRESSED -----------------*/

/* ------------------- BEHAVIOR WHEN THE TOUCH SCREEN IS PRESSED -----------------*/

static _Bool manage_textbox_pressed(point16 pt) ;

static _Bool manage_button_pressed(point16 pt) ;

static _Bool manage_group_radiobutton_pressed(point16 pt) ;

static _Bool manage_checkbox_pressed(point16 pt) ;

/**
 * \brief       If one of the responsive components (button, checkbox, radio group or textbox) is pressed,
 *					launch the task to be carried
 * \param[in]   pt : point with the coordinates of the position where the screen has been pressed
 * \return      1 if the screen has been pressed; 0 otherwise
 */
void manage_touch(point16 pt) {  	
    
    if (manage_textbox_pressed(pt)) {
        Sleep(100);
        return; 
    }
    if (manage_button_pressed(pt)) {
        Sleep(100);
        return; 
    }
	if (manage_group_radiobutton_pressed(pt)) {
        Sleep(100);
        return; 
    }

	if (manage_checkbox_pressed(pt)) {
        Sleep(100);
        return; 
    }
}


/**
 * \brief       Detect if the touch screen has been pressed
 * \param[in]   pt (by reference): pointer to the point to be filled with the coordinates of the
 *					position where the screen has been pressed
 * \return      1 if the screen has been pressed; 0 otherwise
 */
#if !defined WIN32
_Bool is_screen_pressed(point16* pt) {
    if (!TP_Scan(1)) {
        return 0;
    }
    pt->x = get_TP_x();
    pt->y = get_TP_y();   
    return 1;
}
#endif

/* -------------------------- BUTTON ------------------------------------*/

/**
 * \brief       Detects if a certain button has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \param[in]   button : pointer to the the button being evaluated
 * \return      1 if the button has been pressed; 0 otherwise
 */
_Bool is_button_pressed(const button_t *button, point16 pt) {
    rect16_t rect16;
    transf_region_2_rect16(&button->rect, &rect16);

    return is_point_in_rectangle(pt, &rect16);
}

/**
 * \brief       Detects if any button has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \return      if one of the buttons was pressed, return its index; 0 otherwise
 */
s8 scan_button_pressed(point16 pt) {
    for (u8 cb = 0; cb < gui.num_buttons; cb++) {
        button_t *obj = gui.buttons+cb;
        if (obj->enabled == DISABLED || obj->visible == INVISIBLE){
            continue;
        }
        if (is_button_pressed(gui.buttons+cb, pt))
            return cb;
    }
    return -1;
}

/**
 * \brief       If one of the button is pressed, launch the task associated to this button
 * \param[in]   pt : point with the coordinates of the position where the screen has been pressed
 * \return      1 if one of the buttons is pressed; -1 otherwise
 */

_Bool manage_button_pressed(point16 pt) {
    s8 pressed_button = scan_button_pressed(pt); 
    if (pressed_button == -1)
        return 0;
    
    u16 offset = RGB24_2_RGB16(80, 180, 80);
    u16 prev_colour = gui.buttons[pressed_button].rect.colour;
    gui.buttons[pressed_button].rect.colour = (u16) (gui.buttons[pressed_button].rect.colour + offset);
    draw_button(gui.buttons+pressed_button);
    Sleep(200);
    gui.buttons[pressed_button].rect.colour = prev_colour;
    draw_button(gui.buttons+pressed_button);
    gui.buttons[pressed_button].action();
    return 1;     
}
/* -------------------------- TEXTBOX ------------------------------------*/

/**
 * \brief       Detects if a certain textbox has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \param[in]   textbox : pointer to the the textbox being evaluated
 * \return      1 if the textbox has been pressed; 0 otherwise
 */
_Bool is_textbox_pressed(const textbox_t *textbox, point16 pt) {
    rect16_t rect;
    transf_vertices_2_rect16(textbox->x, textbox->y, 
        textbox->length,  (u16) (textbox->font_size*1.5), textbox->type_of_reference, &rect );
    
    return is_point_in_rectangle(pt, &rect);
}

/**
 * \brief       Detects if any textbox has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \return      if one of the textbox was pressed, return its index; 0 otherwise
 */
s8 scan_textbox_pressed(point16 pt) {
    for (u8 cb = 0; cb < gui.num_textboxes; cb++){
        textbox_t *obj = gui.textboxes + cb;
        if (obj->enabled == DISABLED || obj->visible == INVISIBLE){
            continue;
        }
        if (is_textbox_pressed(gui.textboxes+cb, pt))
            return cb;
    }
    return -1;
}

/**
 * \brief       If one of the textboxes is pressed, launch the task associated to this textbox 
 *					that typically will be opening the keyboard and wait for a text to be typed
 * \param[in]   pt : point with the coordinates of the position where the screen has been pressed
 * \return      1 if one of the textboxes is pressed; -1 otherwise
 */
_Bool manage_textbox_pressed(point16 pt) {
    s8 selected_textbox = scan_textbox_pressed(pt);

    if (selected_textbox == -1) {
        return 0;
    }
	Sleep(200);
    gui.pmanage_Pressed_textbox(selected_textbox);

    return 1;
}
/* -------------------------- CHECKBOX ------------------------------------*/
/**
 * \brief       Detects if a certain checkbox has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \param[in]   checkbox : pointer to the the checkbox being evaluated
 * \return      1 if the checkbox has been pressed; 0 otherwise
 */
_Bool is_checkbox_pressed(const checkbox_t *checkbox, point16 pt) {
    rect16_t rect;
	get_bounding_rect_from_checkbox(checkbox, &rect, 1);
	inflate(&rect, INFLATION_CHECBOX_4_TOUCH);
    
    return is_point_in_rectangle(pt, &rect);
}

/**
 * \brief       Detects if any checkbox has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \return      if one of the checkbox was pressed, return its index; 0 otherwise
 */
s8 scan_checkbox_pressed(point16 pt) {
    for (u8 cb = 0; cb < gui.num_checkboxes; cb++) {
        checkbox_t *obj = gui.checkboxes+cb;
        if (obj->enabled == DISABLED || obj->visible == INVISIBLE){
            continue;
        }
        if (is_checkbox_pressed(gui.checkboxes+cb, pt))	{
			gui.checkboxes[cb].is_checked = !gui.checkboxes[cb].is_checked;
            return cb;
		}
    }
    return -1;
}

/**
 * \brief       If one of the checkboxes is pressed, launch the action associated to it and redraw it
 *					according to whether the checkbox is pressed or not
 * \param[in]   pt : point with the coordinates of the position where the screen has been pressed
 * \return      1 if one of the checkboxes is pressed; -1 otherwise
 */
_Bool manage_checkbox_pressed(point16 pt) {
    s8 pressed_checkbox = scan_checkbox_pressed(pt); 

    if (pressed_checkbox == -1) {
        return 0;
    }
	draw_checkbox(gui.checkboxes + pressed_checkbox);
	gui.checkboxes[pressed_checkbox].action();
	return 1;
}


/* -------------------------- RADIO BUTTON GROUP ------------------------------------*/
/**
 * \brief       Taking into account the text at the right of every option, gets the
 * 				maximum width of the options
 * \param[in]   radiogroup : pointer to the the radio group being evaluated
 * \return      the width of the longest option
 */
u16 get_max_width_of_radiogroup(const group_radiobutton_t *radiogroup) {
    u16 max_width = 0;
    for (u8 index = 0; index < radiogroup->num_items; index  ++) {
    	const u8 *text = get_string_from_index(radiogroup->texts,  index);
    	u16 temp_text_width = V2H(radiogroup->font_size) * (my_strlen_sl(text));

    	if (max_width < temp_text_width) {
    		max_width = temp_text_width;
    	}
    }
    return max_width + radiogroup->font_size + RAD_BUT_SEP_H;
}
/* -------------------------- RADIO BUTTON GROUP ------------------------------------*/
/**
 * \brief       Detects if one of the options of a certain group of radio buttons has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \param[in]   radiogroup : pointer to the the radio group being evaluated
 * \return      index of the selected option if the radio group has been pressed; -1 otherwise
 */
s8 is_radiobutton_pressed(const group_radiobutton_t *radiogroup, point16 pt) {
    rect16_t rect;
    for (u8 index = 0; index < radiogroup->num_items; index  ++) {
        get_bounding_rect_from_radio_button(radiogroup, index, &rect);
		inflate(&rect, INFLATION_RAD_BUT_4_TOUCH);
        if (is_point_in_rectangle(pt, &rect)) {
            return index;
        }
    }
    /* For radiogroups with two options:
	 * If no option is selected but the screen has been touched
	 * "near" the radiogroup, then switch the option
	 */
	if (radiogroup->num_items == 2){
		u16 width = get_max_width_of_radiogroup(radiogroup);
		get_bounding_rect_from_radio_button(radiogroup, 0, &rect);
		rect.right = rect.left + width;
        rect.bottom = rect.top + 1 * (RAD_BUT_SEP_V + RAD_BUT_SIZE); //radiogroup->sepV;
		inflate(&rect, INFLATION_RAD_BUT_4_TOUCH);
		if (is_point_in_rectangle(pt, &rect)) {
			Sleep(300); // To avoid rebounds in the selection
			return 1 - radiogroup->index_selected;
		}
	}
    return -1;
}


/**
 * \brief       Detects if any radio groups has been pressed
 * \param[in]   pt : coordinates of the with the coordinates of the
 *					position where the screen has been pressed
 * \param[in]	index (by reference): if one of the groups was pressed, "index" contains
 *					the selected option; -1 otherwise
 * \return      if one of the groups was pressed, return its index; -1 otherwise
 */
s8 scan_radiobutton_group_pressed(point16 pt, s8 *index) {
	for (u8 cb = 0; cb < gui.num_groups_radio_but; cb++) {
        group_radiobutton_t *obj = gui.radio_but+cb;
        if (obj->enabled == DISABLED || obj->visible == INVISIBLE){
            continue;
        }
        *index = is_radiobutton_pressed(obj, pt);
        if (*index != -1) {
            obj->index_selected = *index;

            return cb;
        }
    }
    return -1;
}

/**
 * \brief       If one of the radio groups is pressed, launch the action associated to it and redraw it
 *					according to the selected option
 * \param[in]   pt : point with the coordinates of the position where the screen has been pressed
 * \return      1 if one of the radio groups is pressed; -1 otherwise
 */
_Bool manage_group_radiobutton_pressed(point16 pt) {
    s8 option;
    s8 index_group_pressed = scan_radiobutton_group_pressed(pt, &option);
    if (index_group_pressed == -1)
        return 0;
    draw_group_radio_button(gui.radio_but+index_group_pressed);
	gui.radio_but[index_group_pressed].action();
	return 1;
}
void func_no_action(void) {};
