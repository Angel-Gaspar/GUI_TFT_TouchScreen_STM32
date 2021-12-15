/**
 * \file            func_gui_aux.c
 * \brief           Definition of structs for the graphical components of the gui
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

#include "func_gui_aux.h"
#include "includes.h"

#if !defined WIN32
#include "GUI_font.h"
#endif


    
void HAL_Delay(uint32_t Delay);

/* ------------------- OPERATIONS WITH RECTANGLES ----------------------------------------------*/
/**
 * \brief       Gives the upper-left coordinates for a shape defined with a certain justification
 * \param[in]   x_ref: x-coordinate of the reference position
 * \param[in]   y_ref: y-coordinate of the reference position
 * \param[in]   width: shape (or text) width
 * \param[in]   height: shape (or text) height
 * \param[in]   left (by reference): x coordinate where the shape or text begins
 * \param[in]   top (by reference): y coordinate where the shape or text begins
 * \param[in]   type_of_reference: indicates if the justification is center, left, right...
                     and also if horizontal symmetry must be applied
 * \return      None 
 */
void Position_2_Position_left_top(u16 x_ref, u16 y_ref, u16 width, u16 height, 
    u16 *left, u16 *top, defined_from type_of_reference) {
    *left = x_ref;
    *top = y_ref;
	defined_from pos_wo_simm = (type_of_reference & 0x0F) ;
    if (pos_wo_simm == Center) {
        *left -=  width/2;
        *top -=  height/2;
    
	} else if (pos_wo_simm == Left_Center) {
        *top -= height/2;

    } else if (pos_wo_simm == Right_Center) {
        *top -= height/2;
		*left -= width;
    } 
    // else Left_Top is assumed

    if (type_of_reference & H_Simmetry)
        *left = LCD_W - *left - width;
}
/**
 * \brief       Constrain the rectangle so that the vertices are inside the LCD dimension
 * \param[in]   rect: instance of structure rect16_t to be analyzed
 * \return      None 
 */
void enclose_rectangle(rect16_t *rect) {
	if (rect->left < 0) {
		rect->left = 0;
	}
	if (rect->right > LCD_W) {
		rect->right = LCD_W;
	}
	if (rect->top < 0) {
		rect->top = 0;
	}
	if (rect->bottom > LCD_H) {
		rect->bottom = LCD_H;
	}
}

/**
 * \brief       Get the location of the center of the rectangle
 * \param[in]   rectangle: pointer to the rect16 rectangle
 * \return      the location of the center of the rectangle
 */
point16 get_central_point_of_rectangle(rect16_t *rect16) {
    point16 pt16;
    pt16.x = (rect16->left + rect16->right) / 2;
    pt16.y = (rect16->top + rect16->bottom) / 2;
    return pt16;
}

/**
 * \brief       Get the location of the center of the region
 * \param[in]   region: pointer to the region
 * \return      the location of the center of the region
 */
point16 get_central_point_of_region(region_t *region) {
    point16 pt16;
    pt16.x = region->x;
    pt16.y = region->y;
    return pt16;
}

/* ------------------- TRANSFORMATIONS BETWEEN RECTANGLES ----------------------------------------------*/

/**
 *              NOT USED IN THIS VERSION
 * \brief       Obtain the vertices of a rectangle, where its x and y coordinates are the reference pos that
                    can be center, top, left...
 * \param[in]   rect: instance of structure region_t to be analyzed
 * \param[in]   left (by reference): x coordinate where the shape or text begins
 * \param[in]   top (by reference): y coordinate where the shape or text begins
 * \param[in]   right (by reference): x coordinate where the shape or text ends
 * \param[in]   bottom (by reference): y coordinate where the shape or text ends
 * \param[in]   type_of_reference: indicates if the justification is center, left, right...
                     and also if horizontal symmetry must be applied
 * \return      None 
 */
void transf_region_2_vertices(const region_t *rect,  u16 *left, u16 *top, u16 *right, u16*bottom, defined_from type_of_reference) {
    Position_2_Position_left_top(rect->x, rect->y, rect->width, rect->width,
        left, top, type_of_reference);

    *right = *left + rect-> width;
    *bottom = *top + rect->height;
}

/**
 * \brief       Translate a shape defined by the reference position, width and height to the structure rect16_t defined only 
                    its vertices
 * \param[in]   x: x-coordinate of the reference position
 * \param[in]   y: y-coordinate of the reference position
 * \param[in]   width: width of the reference position
 * \param[in]   height: height of the reference position
 * \param[in]   type_of_reference: indicates if the justification is center, left, right...
                     and also if horizontal symmetry must be applied
 * \param[in]   rectangle (by reference): the rectangle rect16 corresponding to the input structure 
 * \return      none
 */

void transf_vertices_2_rect16(u16 x, u16 y, u16 width, u16 height, defined_from type_of_reference, rect16_t *rect16) {
    Position_2_Position_left_top(x, y, width, height, &(rect16->left), &(rect16->top), type_of_reference);

    rect16->right        = rect16->left + width;
    
    rect16->bottom    = rect16->top + height;
}

/**
 * \brief       Translate an instance from the structure region_t to the structure rect16_t defined only 
                    its vertices
 * \param[in]   rect: instance of structure region_t to be translated
 * \param[in]   rectangle (by reference): the rectangle rect16 corresponding to the input structure 
 * \return      none
 */

void transf_region_2_rect16(const region_t *rect, rect16_t* rect16) {
    transf_vertices_2_rect16(rect->x, rect->y, rect->width, rect->height,rect->type_of_reference, rect16);
}


/* ------------------- OBTAINING THE BOUNDING BOX OF COMPONENTS ----------------------------------------------*/

/**
 * \brief       Get the rectangle evolving certain item in a radio button component
 * \param[in]   index: option in the radio group to be analyzed
 * \param[in]   rb: pointer to the instance of the radio group
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \return       the center of the rectangle
 */
point16 get_bounding_rect_from_radio_button(const group_radiobutton_t *rb, u8 index, rect16_t *rect) {
    point16 pt;
    rect->top = rb->top + index * (RAD_BUT_SIZE + RAD_BUT_SEP_V); // rb->sepV;
    rect->left = rb->left;
    rect->bottom = rect->top + RAD_BUT_SIZE;
    rect->right = rect->left + RAD_BUT_SIZE;
    
    pt = get_central_point_of_rectangle(rect);
    return pt;
}
/**
 * \brief       Get the rectangle evolving the complete group of radio buttons, including the longest text
 * \param[in]   rb: pointer to the instance of the radio group
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \return       the center of the rectangle
 */
point16 get_bounding_rect_from_group_radio_button(const group_radiobutton_t *rb, rect16_t *rect) {
    rect->top = rb->top ;
    rect->left = rb->left;
    rect->bottom = rect->top + (rb->num_items-1) * (RAD_BUT_SIZE + RAD_BUT_SEP_V) + RAD_BUT_SIZE;

    u8 fontsz_H = V2H(rb->font_size);
	// u8 fontsz_V = rb->font_size;
 
    u8 *texts = rb->texts;
    rect->right = rect->left + str_width(texts, fontsz_H) + RAD_BUT_SEP_H + RAD_BUT_SIZE;
  
    point16 pt = get_central_point_of_rectangle(rect);
    return pt;
}

/**
 * \brief       Get the rectangle evolving a checkbox
 * \param[in]   cb: pointer to the instance of the checkbox
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \return      the center of the rectangle
 */
point16 get_bounding_rect_from_checkbox(const checkbox_t *cb,  rect16_t *rect, _Bool only_the_square) {
	rect->top = cb->top;
    rect->left = cb->left;
    rect->bottom = rect->top + cb->font_size;
    rect->right = rect->left + cb->font_size;

    if (only_the_square) {
        return get_central_point_of_rectangle(rect);
    }
    
    u8 fontsz_H = V2H(cb->font_size);
	u8 fontsz_V = cb->font_size;
 
    // Display the text
    u8 *text = cb->text;
    if (cb->text_at == the_left) {
        rect->left -= my_strlen_sl(text) * fontsz_H + CHB_BUT_SEP_H; 
    }
    else if (cb->text_at == the_right) {
        
    }
    else if (cb->text_at == the_top) {
        rect->left -= (my_strlen_sl(text)-1) * fontsz_H/2 ; 
        rect->top -=  fontsz_V + RAD_BUT_SEP_V;

    } else if (cb->text_at == the_bottom) {
        rect->left -= (my_strlen_sl(text)-1) * fontsz_H/2 ; // Not tested ToDo
        rect->top +=  RAD_BUT_SIZE + RAD_BUT_SEP_V;
    }

    if (cb->text_at == the_left || cb->text_at == the_right) {
        rect->right = rect->left + my_strlen_sl(text) * fontsz_H + RAD_BUT_SEP_H + RAD_BUT_SIZE;
        rect->bottom = rect->top + RAD_BUT_SIZE;
    }
    else {
        rect->right = rect->left + my_strlen_sl(text) * fontsz_H ;
        rect->bottom = rect->top + RAD_BUT_SIZE + RAD_BUT_SEP_V;
    }

    point16 pt = get_central_point_of_rectangle(rect);
    return pt;
}
/**
 * \brief       Get the rectangle evolving a checkbox
 * \param[in]   cb: pointer to the instance of the checkbox
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \return      the center of the rectangle
 */
point16 get_bounding_rect_from_button(const button_t *bt,  rect16_t *rect16) {
	//if (bt->rect.width == ADJUST_TO_TEXT)
	//		bt->rect.width = (u16)(str_width(bt->text, V2H(bt->font_sizev)) * BUT_MARGIN_ADJ_W);

	transf_region_2_rect16(&bt->rect, rect16);
    inflate(rect16, INFLATION_BUTTON_4_BORDER);
    point16 pt = get_central_point_of_rectangle(rect16);
    return pt;
}

/**
 * \brief       Get the rectangle evolving a textbox
 * \param[in]   tb: pointer to the instance of the textbox
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \param[in]   type_of_reference: indicates if the justification is center, left, right...
                     and also if horizontal symmetry must be applied
 * \return       the center of the rectangle
 */
point16 get_bounding_rect_from_textbox(const textbox_t *tb,  rect16_t *rect16, defined_from type_of_reference) {
	transf_vertices_2_rect16(tb->x, tb->y, tb->length, 
		(u16) (tb->font_size * MULTIPLIER_HEIGHT_TEXTBOX), type_of_reference, rect16);

    point16 pt = get_central_point_of_rectangle(rect16);
    return pt;
}

/**
 * \brief       Transform a rectangle by inflating or deflating it
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \param[in]   inflation: amount to inflate the rectangle (if positive) or deflate it (if negative)
 * \return      none
 */
void inflate(rect16_t* rect, s8 inflation) {
    rect->top       -=inflation;
    rect->bottom    += inflation;
    rect->left      -= inflation;
    rect->right     += inflation;    
}


/* ------------------- OTHER FUNCTIONS ----------------------------------------------*/

#if !defined WIN32
/**
 * \brief       Display a text (only one line)
 * \param[in]   rect (by reference): instance of rectangle containing the component
 * \param[in]   inflation: amount to inflate the rectangle (if positive) or deflate it (if negative)
 * \return      none
 */
u8 string[40];
void display_1line_text(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, u8 fontsizev, _Bool is_visible, _Bool is_enabled)
{    
    my_strcpy_1line(string, str);
    if (is_visible == INVISIBLE)
        return;
    if (is_enabled == DISABLED)
        fc = COLOUR_TEXT_DISABLED;

    Show_English_Str(x, y, fc, bc, string, fontsizev);
}
#endif

#if !defined WIN32
/**
 * \brief       Assign values to the LCD device 
 * \param[in]   none
 * \return      none
 */
extern _lcd_dev lcddev;
void Set_lcdDev()
{
    lcddev.setxcmd=0x2A;
    lcddev.setycmd=0x2B;
    lcddev.wramcmd=0x2C;
                              
    lcddev.width=LCD_W;
    lcddev.height=LCD_H;    
}

#endif

/**
 * \brief       Deduces if the point is insed a rectangle
 * \param[in]   pt : coordinates of the point 
 * \param[in]   rect : pointer to the the rectangle being evaluated
 * \return      1 if the point is inside the rectangle; 0 otherwise
 */
_Bool is_point_in_rectangle(point16 pt, const rect16_t* rect) {
    if (pt.x > rect->left  && pt.x < rect->right &&
        pt.y > rect->top && pt.y < rect->bottom)
        return 1;
    return 0;
}

/**
 * \brief       Deduces if the point is insed a region
 * \param[in]   pt : coordinates of the point 
 * \param[in]   region : pointer to the the rectangle being evaluated
 * \return      1 if the point is inside the rectangle; 0 otherwise
 */
_Bool is_point_in_region(point16 pt, const region_t* region) {
    rect16_t rect16;
	transf_region_2_rect16(region, &rect16);
	return is_point_in_rectangle(pt, &rect16);
}

/* ------------------- DELETE FUNCTIONS ----------------------------------------------*/
/**
 * \brief		Get the background colour at the specified location. 
 *                  It corresponds to the last region that contains the point
 * \param[in]   x, y: coordinates of the point that define the text position
 * \param[in]	bc:  background color
 * \param[in]	prev_height: the height of the rectangle containing the previous text
 * \param[in]	prev_width: the width of the rectangle containing the previous text
 * \param[in]   type_of_reference: defines if the reference point is at the center, at the left...
 * \return      none
 */
u16 get_background_color(point16 pt) {
    // Search in inverse order. 
    for (s8 cr = gui.num_regions - 1; cr >= 0 ; cr--) {
        if (is_point_in_region(pt, gui.regions+cr)) {
            return gui.regions[cr].colour;
		}
	}
    return COLOR_BACKGROUND_DEFAULT;
}

/**
 * \brief		Clear the space where the previous text was displayed 
 * \param[in]   x, y: coordinates of the point that define the text position
 * \param[in]	prev_height: the height of the rectangle containing the previous text
 * \param[in]	prev_width: the width of the rectangle containing the previous text
 * \param[in]   type_of_reference: defines if the reference point is at the center, at the left...
 * \return      none
 */
void delete_str(u16 x, u16 y, u8 prev_height, u16 prev_width, defined_from type_of_reference){
	
    /*u8 c = 0;
	for (u8 cl = 0; cl < num_lines; cl++) {
		if (cl != 0)
			prv_string[c++] = '\n';
		for (u8 cc = 0; cc < num_char; cc++) {
			prv_string[c++] = ' ';
		}
	}
	prv_string[c] = '\0'; 
	gui_str(x, y, bc+1, bc, prv_string, fontsizeV, pos, VISIBLE, ENABLED); // bc+1 to avoid transparency
   */
    rect16_t rect;
    transf_vertices_2_rect16(x, y, prev_width, prev_height, type_of_reference, &rect);
    u16 bc = get_background_color(get_central_point_of_rectangle(&rect));
    draw_rectangle_from_vertices(&rect, bc, FILLED, VISIBLE, ENABLED);
}
/**
 * \brief		Delete the label
 * \param[in]   label: the component to be deleted
 * \return      none
 */
void delete_label(label_t *label) {
	delete_str(label->x, label->y,  /* maybe it won't work if text had two lines */
			label->prev_height, label->prev_width, label->type_of_reference);
}
/**
 * \brief		Delete the textview
 * \param[in]   textview: the component to be deleted
 * \return      none
 */
void delete_textview(textview_t *textview) {
delete_str(textview->x, textview->y, /* maybe it won't work if text had two lines */
			textview->prev_height, textview->prev_width, textview->type_of_reference);
}
