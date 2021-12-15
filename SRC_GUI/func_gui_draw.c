/**
 * \file            func_gui_draw.c
 * \brief           Auxiliary functions for the graphical interface
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

#include "func_gui_draw.h"
#include "includes.h"

static u8 string_aux[20];

/* -------------------------- DRAW, DISPLAY AND UPDATE COMPONENTS -----------------------------*/


/* -------------------------- GLOBAL FUNCTION CALLED WHEN CREATING THE WINDOW -----------------*/
/**
 * \brief       Represent all components of the active window
 * \param[in]   none
 * \return      none
 */
void initialize_active_window(void) {    
    gui.timer_enabled = 0;

    draw_regions(); 
    
    display_labels();

    display_textviews();

    display_textboxes();
    
    draw_group_radio_buttons();    
    
    draw_checkboxes(); 
    
    draw_buttons();
    
	/* Uncomment the following lines if you wanto to see a grid (unaesthetic, only for 
		calibration purposes */

 /*  for (u8 cc = 0; cc < LCD_W; cc+=20)
        draw_line(cc,0, cc, LCD_H, WHITE);

    for (u8 cf = 0; cf < LCD_H; cf+=20)
        draw_line(0, cf, LCD_W, cf, WHITE);
   */ 
}

/* -------------------------- BUTTONS ----------------------------------------------*/

/**
 * \brief       Draw the set of buttons
 * \param[in]	none
  * \return     none
 */
void draw_buttons(void) {
    for (u8 i = 0; i < gui.num_buttons; i++)
        draw_button(gui.buttons+i);
}
/**
 * \brief       Draw one of the  buttons. 
 * \param[in]	button: pointer to the instance of the button to be drawn
 * \return      none
 */
void draw_button(const button_t *button) {
    rect16_t rect;
    get_bounding_rect_from_button(button, &rect);
    if (button->visible == INVISIBLE) {
		return;
    }

    draw_rectangle_from_vertices(&rect, button->rect.colour, 0, button->visible, button->enabled);

	inflate(&rect, -INFLATION_BUTTON_4_BORDER);

    draw_rectangle_from_vertices(&rect, button->rect.colour, 1, button->visible, button->enabled);
	
    gui_str(button->rect.x, button->rect.y, button->colour_text, button->colour_text,
        button->text, button->font_sizev, button->rect.type_of_reference, button->visible, button->enabled);
}

/**
 * \brief       Delete the selected button. 
 * \param[in]	button: pointer to the instance of the button to be deleted
 * \return      none
 */
void delete_button(const button_t *button) {
    rect16_t rect;
    point16 center = get_bounding_rect_from_button(button, &rect);

    u16 background_color = get_background_color(center);
    draw_rectangle_from_vertices(&rect, background_color, 1, VISIBLE, ENABLED);
    return;
   }
/**
 * \brief       Update the state of the selected button. 
 * \param[in]	button: pointer to the instance of the button to be updated
 * \return      none
 */
void update_button(const button_t *button) {
    if (button->visible == VISIBLE) {
		draw_button(button);
	} else {
		delete_button(button);
	}
}
/**
 * \brief       Change the background colour and text colour of a button according to the 
 *					selected colours for a certain player
 * \param[in]   button: pointer to the button to be altered
 * \param[in]   player_from_1: the player whose colours will be copied onto the button
 * \return      none
 */
void change_colours_of_button(button_t *button, u8 player_from_1) { 
	u16 colour16_back, colour16_text;
	get_colours(player_from_1, &colour16_back, &colour16_text);

	button->rect.colour = colour16_back; 
	button->colour_text = colour16_text; 
}
/* -------------------------- RADIO BUTTONS  ----------------------------------------------*/
/**
 * \brief       Draw the set of radio buttons
 * \param[in]	none
  * \return     none
 */
void draw_group_radio_buttons(void) {
    for (u8 i = 0; i < gui.num_groups_radio_but; i++)
        draw_group_radio_button(gui.radio_but+i);
}

/**
 * \brief       Draw one of the groups of radio buttons
 * \param[in]	rb: pointer to the instance of the group of radio buttons to be drawn
 * \return      none
 */
void draw_group_radio_button(const group_radiobutton_t* rb) {    
    if (rb->visible == INVISIBLE) {
		return;
    }
    for (u8 ci = 0; ci < rb->num_items; ci++)
        draw_radio_but(rb, ci, ci == rb->index_selected);
}

/**
 * \brief       Delete the specified group of radio buttons
 * \param[in]	rb: pointer to the instance of the group of radio buttons to be deleted
 * \return      none
 */
void delete_group_radio_button(const group_radiobutton_t* rb) {    
    rect16_t rect;
    point16 center = get_bounding_rect_from_group_radio_button(rb, &rect);
    u16 background_color = get_background_color(center);
    draw_rectangle_from_vertices(&rect, background_color, 1, VISIBLE, ENABLED);
}
/**
 * \brief       Update the state of the selected group of radio buttons. 
 * \param[in]	rb: pointer to the instance of the group of radio buttons to be updated
 * \return      none
 */
void update_group_radio_button(const group_radiobutton_t* rb) {
    if (rb->visible == VISIBLE) {
		draw_group_radio_button(rb);
	} else {
		delete_group_radio_button(rb);
   }
}
/**
 * \brief       Draw one of options of one of the groups of radio buttons
 * \param[in]	rb: pointer to the instance of the complete group of radio buttons
 * \param[in]	index: index of the radio buttons that will be drawn
 * \param[in]	marked: 1 if this radio button is the one selected
 * \return      none
 */
void draw_radio_but(const group_radiobutton_t *rb, u8 index, _Bool marked) {   
    rect16_t rect;
    u8 sz = rb->font_size;
    point16 center = get_bounding_rect_from_radio_button(rb, index, &rect);

    const u8 *text = get_string_from_index(rb->texts,  index);

    display_1line_text((u16) (rect.right + RAD_BUT_SEP_H), (u16) (rect.top), 
        rb->colour_text, rb->colour_text, text, sz, rb->visible, rb->enabled);

    draw_rectangle_from_vertices(&rect, rb->colour_text, NOT_FILLED, rb->visible, rb->enabled);

    inflate(&rect, DEFLATION_RAD_BUT_4_MARK);

    if (!marked) {
        u16 color_background = get_background_color(center);
        // Delete the previous square
	    draw_rectangle_from_vertices(&rect, color_background, 1, rb->visible, rb->enabled);
    } else {
        draw_rectangle_from_vertices(&rect, rb->colour_text, 1, rb->visible, rb->enabled);  
    } 
}


/* -------------------------- CHECKBOXES  ----------------------------------------------*/

/**
 * \brief       Draw the set of checkboxes
 * \param[in]	none
  * \return     none
 */
void draw_checkboxes(void) {
    for (u8 i = 0; i < gui.num_checkboxes; i++) {
        draw_checkbox(gui.checkboxes+i);
	}
}

/**
 * \brief       Draw one of the checkboxes
 * \param[in]	rb: pointer to the instance of the checkboxes to be drawn
 * \return      none
 */
void draw_checkbox(const checkbox_t *checkbox) {
    rect16_t rect;
	point16 center = get_bounding_rect_from_checkbox(checkbox, &rect, 0);

    if (checkbox->visible == INVISIBLE) {
        return;
    }

	center = get_bounding_rect_from_checkbox(checkbox, &rect, 1);

    u8 *text = checkbox->text;
    u16 posx = checkbox->left;
    u16 posy = checkbox->top;

	// Draw the square
    draw_rectangle_from_vertices(&rect, checkbox->colour_text, NOT_FILLED, checkbox->visible, checkbox->enabled);

    inflate(&rect, DEFLATION_RAD_BUT_4_MARK);

    if (!checkbox->is_checked) {
        u16 color_background = get_background_color(center);
        // Delete the previous square
	    draw_rectangle_from_vertices(&rect, color_background, 1, checkbox->visible, checkbox->enabled);
    } else {
        draw_rectangle_from_vertices(&rect, checkbox->colour_text, checkbox->is_checked, checkbox->visible, checkbox->enabled);  
    }

    // Display the text

    u8 fontsz_H = V2H(checkbox->font_size);
	u8 fontsz_V = checkbox->font_size;

    if (checkbox->text_at == the_right) {
        posx =  rect.right + CHB_BUT_SEP_H ;
        //posy += sz_V / 3;
    
    } else if (checkbox->text_at == the_left) {
        posx = rect.left - my_strlen_sl(text) * fontsz_H - CHB_BUT_SEP_H; //  + RAD_BUT_SEP_H;
         // posy += sz_V / 3;

    } else if (checkbox->text_at == the_top) {
        posx -= (my_strlen_sl(text)-1) * fontsz_H/2 ;
        posy -=  fontsz_V + RAD_BUT_SEP_V;

    } else if (checkbox->text_at == the_bottom) {
        posx -= (my_strlen_sl(text)-1) * fontsz_H/2 ;
        posy +=  RAD_BUT_SIZE + RAD_BUT_SEP_V;
    }

    display_1line_text(posx, posy, 
        checkbox->colour_text, checkbox->colour_text, text, checkbox->font_size, checkbox->visible, checkbox->enabled);
}

/**
 * \brief       Delete the specified checkbox
 * \param[in]	rb: pointer to the instance of the checkboxes to be deleted
 * \return      none
 */
void delete_checkbox(const checkbox_t *checkbox) {
    rect16_t rect;
	point16 center = get_bounding_rect_from_checkbox(checkbox, &rect, 0);

    u16 background_color = get_background_color(center);
    draw_rectangle_from_vertices(&rect, background_color, 1, VISIBLE, ENABLED);
    return;
}

/**
 * \brief       Update the state of the selected checkbox. 
 * \param[in]	checkbox: pointer to the instance of the checkbox to be updated
 * \return      none
 */
void update_checkbox(const checkbox_t *checkbox) {
    if (checkbox->visible == VISIBLE) {
		draw_checkbox(checkbox);
	} else {
		delete_checkbox(checkbox);
	}
}
/* -------------------------- RECTANGLES  ----------------------------------------------*/

/**
 * \brief       Draw the set of regions
 * \param[in]	none
  * \return     none
 */

void draw_regions(void) {
    for (u8 cr = 0; cr < gui.num_regions; cr++)
        draw_region(gui.regions+cr, 1, VISIBLE, ENABLED);
}

/**
 * \brief       Plot the rectangle (filled or contour) given by its vertices
 * \param[in]   rect: pointer to the instance of the rectangle
 * \param[in]   colour_fill: color of contour and, in case, the filling
 * \param[in]   fill: 1 if the rectangle is to be filled; 0, only contour
 * \param[in]   is_visible: if 0, it will not be drawn
 * \param[in]   is_enabled: if 0, it will be plotted in gray
  * \return      none
 */
#if !defined WIN32
void draw_rectangle_from_vertices(rect16_t *rect, u16 colour_fill, _Bool fill, _Bool is_visible, _Bool is_enabled) {
    if (is_visible == INVISIBLE)
        return;

    if (is_enabled == DISABLED) {
        set_point_color(COLOUR_FILL_DISABLED);
    } else {
        set_point_color(colour_fill);
    }
    enclose_rectangle(rect);
    if (fill) {
        LCD_DrawFillRectangle(rect->left, rect->top, rect->right, rect->bottom);
    } else {
        LCD_DrawRectangle(rect->left, rect->top, rect->right, rect->bottom);
    }
}
#endif
/**
 * \brief       Plot the rectangle (filled or contour) given by the structure region_t
 * \param[in]   rect: pointer to the instance of the rectangle
 * \param[in]   fill: 1 if the rectangle is to be filled; 0, only contour
 * \param[in]   is_visible: if 0, it will not be drawn
 * \param[in]   is_enabled: if 0, it will be plotted in gray
  * \return      none
 */
void draw_region(region_t *rect, _Bool fill, _Bool is_visible, _Bool is_enabled) {
    if (is_visible == INVISIBLE)
        return;
    u16 colour_fill = rect->colour;
    if (is_enabled == DISABLED)
        colour_fill = COLOUR_FILL_DISABLED;

    rect16_t rect16;
    transf_region_2_rect16(rect, &rect16);
	enclose_rectangle(&rect16);
    draw_rectangle_from_vertices( &rect16, colour_fill, fill, is_visible, is_enabled);    
}

/* -------------------------- LABELS  ----------------------------------------------*/
/**
 * \brief       Display the set of labels
 * \param[in]	none
  * \return     none
 */
void display_labels(void) {
    for (u8 cl = 0; cl < gui.num_labels;cl++)
        display_label(gui.labels + cl);
}

/**
 * \brief       Display one of the labels
 * \param[in]	rb: pointer to the instance of labels
 * \return      none
 */
void display_label(label_t *label) {

    if (label->visible == INVISIBLE) {
        delete_label(label);
        return;
    }

    if (label->prev_width > 0) /* delete the previous text */
		delete_label(label);
		
    gui_str(label->x, label->y, label->colour_text, label->colour_text,
        (u8*)label->text, label->font_size, label->type_of_reference, label->visible, ENABLED);

    label->prev_width = str_width((u8*)label->text, V2H(label->font_size));
	label->prev_height = (u8) NUM_LINES_2_HEIGHT(get_number_of_lines((u8*)label->text), label->font_size);
    //show_str(label->x, label->y, label->colour_text,
    //    label->text, label->font_size, label->pos, label->visible, ENABLED);
}

/* -------------------------- TEXTVIEWS  ----------------------------------------------*/
/**
 * \brief       Display the set of textviews
 * \param[in]	none
  * \return     none
 */
void display_textviews(void) {
    for (u8 cl = 0; cl < gui.num_textviews;cl++)
        display_textview(gui.textviews + cl);
}
/**
 * \brief       Display one of the textviews
 * \param[in]	rb: pointer to the instance of textviews
 * \return      none
 */
void display_textview(textview_t *textview) {
    
	if (textview->visible == INVISIBLE) {
        delete_textview(textview);
        return;
    }
		
	if (textview->prev_width > 0) /* delete the previous text */
		delete_textview(textview);
		
    gui_str(textview->x, textview->y, textview->colour_text, textview->colour_text,
        textview->text, textview->font_size, textview->type_of_reference, textview->visible, ENABLED);

    textview->prev_width = str_width(textview->text, V2H(textview->font_size));
	textview->prev_height = (u8) NUM_LINES_2_HEIGHT(get_number_of_lines(textview->text), textview->font_size);
    //show_str(label->x, label->y, label->colour_text,
    //    label->text, label->font_size, label->pos, label->visible, ENABLED);
}
/**
 * \brief       Replace the text of one of the textviews
 * \param[in]	rb: pointer to the instance of textview
 * \param[in]	new_text: the new text to be displayed
 * \param[in]	show_textview: if 0, the text will be assigned but not updated; 
 *				if 1, the text will be assigned and the textview refreshed
 * \return      none
 */
void replace_text_in_textview(textview_t *textview, const u8 *new_text, _Bool show_textview) {
   my_strcpy(textview->text, new_text);
   if (show_textview == AND_SHOW) {
       display_textview(textview);
   }
}
/**
 * \brief       Replace the text of one of the textviews, assuming that the new text is a number
 * \param[in]	rb: pointer to the instance of textview
 * \param[in]	number: the number to be displayed
 * \param[in]	show_textview: if 0, the text will be assigned but not updated; 
 *				if 1, the text will be assigned and the textview refreshed
 * \return      none
 */
void replace_text_in_textview_with_number(textview_t *textview, u8 number, _Bool show_textview) {
    my_itoa(number, string_aux, 0);
    replace_text_in_textview(textview, string_aux, show_textview);
}
/**
 * \brief       Replace the text of one of the textviews, with a text and a number
 * \param[in]	rb: pointer to the instance of textview
 * \param[in]	new_text: the text to be displayed
 * \param[in]	number: the number to be displayed
 * \param[in]	show_textview: if 0, the text will be assigned but not updated; 
 *				if 1, the text will be assigned and the textview refreshed
 * \return      none
 */
void replace_text_in_textview_with_text_and_number(textview_t *textview, u8 *new_text, u8 number, _Bool show_textview) {
    my_itoa(number, string_aux, 0);
    replace_text_in_textview(textview, my_strcat(new_text, string_aux), show_textview);
}

/* -------------------------- TEXTBOXES  ----------------------------------------------*/
/**
 * \brief       Display the set of textboxes
 * \param[in]	none
  * \return     none
 */
void display_textboxes(void) {
    for (u8 cl = 0; cl < gui.num_textboxes;cl++)
        display_textbox(gui.textboxes + cl);
}
/**
 * \brief       Display one of the textboxes
 * \param[in]	rb: pointer to the instance of textboxes
 * \return      none
 */
void display_textbox(textbox_t *textbox) {
    rect16_t rect;
        
    get_bounding_rect_from_textbox(textbox, &rect, textbox->type_of_reference);
	draw_rectangle_from_vertices(&rect, textbox->colour_back, 1, textbox->visible, textbox->enabled);

	gui_str(textbox->x, textbox->y, textbox->colour_text, textbox->colour_text,
        textbox->text, textbox->font_size, textbox->type_of_reference, textbox->visible, textbox->enabled);
    //show_str(label->x, label->y, label->colour_text,
    //    label->text, label->font_size, label->pos, label->visible, ENABLED);
}

/**
 * \brief       Replace the text of one of the textboxes
 * \param[in]	rb: pointer to the instance of textbox
 * \param[in]	new_text: the new text to be displayed
 * \param[in]	show_textbox: if 0, the text will be assigned but not updated; 
 *				if 1, the text will be assigned and the textbox refreshed
 * \return      none
 */
void replace_text_in_textbox(textbox_t *textbox, u8 *new_text, _Bool show_textbox) {
    my_strcpy(textbox->text, new_text); 
    if (show_textbox == AND_SHOW) {
        display_textbox(textbox);
    }
}
/**
 * \brief       Change the background colour and text colour of a textbox according to the 
 *					selected colours for a certain player
 * \param[in]   textbox: pointer to the textbox to be altered
 * \param[in]   player_from_1: the player whose colours will be copied onto the textbox
 * \return      none
 */
void change_colours_of_textbox(textbox_t *textbox, u8 player_from_1) { 
	u16 colour16_back, colour16_text;
	get_colours(player_from_1, &colour16_back, &colour16_text);

	textbox->colour_back = colour16_back; 
	textbox->colour_text = colour16_text; 
}

/* -------------------------- WARNINGS and MESSAGES ----------------------------------------*/
/**
 * \brief       Show a popup message
 * \param[in]	message: the warning that will emerge
  * \return     none
 */
void show_popup(warning_t *message) {
    u8 num_lines_Message = (message->line2[0] == '\0' ? 1 : 2);
    u8 font_sizev = MESSAGE_FONT;

    // u16 height_message = (int)( num_lines_Message * (font_sizev + SEP_V_LINES(font_sizev)) + 10);

    rect16_t rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = LCD_H;
    rect.right = LCD_W;
    draw_rectangle_from_vertices(&rect, LIGHTGRAY, 1, VISIBLE, ENABLED);

    u16 posy = 20;
    gui_str(20, 20, BLUE, BLUE, message->line1, font_sizev, Left_Top, VISIBLE, ENABLED);
     
    if (num_lines_Message == 2){
        posy += font_sizev + SEP_V_LINES(font_sizev);
        gui_str(20, posy, BLUE, BLUE, message->line2, MESSAGE_FONT, Left_Top, VISIBLE, ENABLED);
    }
    posy += 80;

    for (u8 cb = 0; cb < message->num_buttons; cb++){
        // Create the popup buttons
		button_t *button_pu = &gui.buttons_popup[cb];
        button_pu->text = &message->text_butt[cb][0];
        button_pu->colour_text = BLUE;
        button_pu->enabled = ENABLED;
        button_pu->visible = VISIBLE;
        button_pu->font_sizev = font_sizev;
        button_pu->rect.x = LCD_W/2;
        button_pu->rect.y = posy + 60 * cb;
        button_pu->rect.height = 40;
        button_pu->rect.width = 80;
        button_pu->rect.type_of_reference = Center;
        button_pu->rect.colour = ORANGE;

        draw_button(button_pu);
    }
}

/**
 * \brief       Show a popup message and wait for the user to select one of the proposed options
 * \param[in]	message: the warning that will emerge
  * \return     none
 */
u8 show_popup_and_wait_for_answer(warning_t *message) {
	show_popup(message);
	do {
		point16 pt;
		while(!is_screen_pressed(&pt));
		for (u8 cb = 0; cb < message->num_buttons; cb ++)
			if (is_button_pressed(gui.buttons_popup+cb, pt)) {
                Sleep(100);
				return cb;
            }
	} while(1);
}

/**
 * \brief       Assign the lines and the proposed options in a warning/message
 * \param[in]	message: the warning that will emerge
 * \param[in]	line1: the first line of the message
 * \param[in]	line2: the second line of the message
 * \param[in]	num_buttons: the number of options to be displayed
 * \param[in]	but1: the text of the first option
 * \param[in]	but2: the text of the second option; it will be disregarded if num_buttons < 2
 * \param[in]	but3: the text of the third option; it will be disregarded if num_buttons <= 2
 * \return     none
 */
void fill_message(warning_t *message, const u8* line1, const u8* line2, 
	u8 num_buttons, const u8* but1, const u8* but2, const u8* but3) {
    my_strcpy(message->line1, (u8*) line1);
    my_strcpy(message->line2, (u8*) line2);
    my_strcpy(&message->text_butt[0][0], (u8*) but1);
    if (num_buttons > 1)
        my_strcpy(&message->text_butt[1][0], (u8*) but2);
    if (num_buttons > 2)
        my_strcpy(&message->text_butt[2][0], (u8*) but3);
    message->num_buttons = num_buttons;
}   





