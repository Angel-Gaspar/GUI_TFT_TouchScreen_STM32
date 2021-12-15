/**
 * \file            func_string.c
 * \brief           Functions that manipulate strings and texts.
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

#include <string.h>

#include "includes.h"

#if defined WIN32
#include "func_vs.h"
#endif

static u8 string_points[20];
static u8 prv_string[50];

/* -------------------  FUNCTIONS TO OPERATE WITH STRINGS --------------------------------- */

/**
 * \brief       Copy the text in another array of chars
 * \param[in]   target: pointer to the array to be filled with the text
 * \param[in]   source: pointer to the array containing the text to be copied
 * \return      none
 */
void my_strcpy(u8 *target, const u8 *source) {
    u8 length1 = strlen((char*) source);

    for (u8 i = 0; i< length1; i++) {
        target[i] = source[i];
    }
	target[length1] = '\0';
}


/**
 * \brief       Copy the text in another array of chars, limited to a certain number of characters
 * \param[in]   target: pointer to the array to be filled with the text
 * \param[in]   source: pointer to the array containing the text to be copied
 * \param[in]   max_num_char: maximum number of characters to be copied
 * \return      none
 */
void my_strcpy_ltd_number(u8 *target, const u8 *source, u8 max_num_char) {
    u8 length1 = strlen((char*) source);
	length1 = MIN(length1,max_num_char);

    for (u8 i = 0; i< length1; i++) {
        target[i] = source[i];
    }
    target[length1] = '\0';
}

/**
 * \brief       Copy the text in another array of chars, until a '\0' or '\n' is reached
 * \param[in]   target: pointer to the array to be filled with the text
 * \param[in]   source: pointer to the array containing the text to be copied
 * \param[in]   terminator: another terminator to finish the string
 * \return      none
 */
void my_strcpy_1line(u8 *target, const u8 *source) {
    u8 length1 = my_strlen_sl( source);

    for (u8 i = 0; i< length1; i++) {
        target[i] = source[i];
    }
    target[length1] = '\0';
}

/**
 * \brief       Compare two strings and informs if they are equal
 * \param[in]   cad1: one of the strings
 * \param[in]   cad2: the other string
 * \param[in]   num_char: a limit in the number of chars to compare; 0 for no limitation
 * \return      1 if the first num_char characters match; 0 otherwise
 */
_Bool str_equal(const u8* cad1, const u8* cad2, u8 num_char) {
	if (num_char == 0) {
		num_char = 255;
	}
	u8 extens = MIN(num_char, strlen((char*) cad1));
	extens = MIN(extens, strlen((char*) cad2));
	for (u8 cc = 0; cc < extens; cc++) {
		if (cad1[cc] != cad2[cc]) {
			return 0;
		}
	}
    return 1;
}

/**
 * \brief       Concatenates two strings of characters 
 * \param[in]   cad1: the first string
 * \param[in]   cad2: the second string
 * \return      pointer to a string containing both strings
 */
u8 *my_strcat(const u8 *cad1, const u8 *cad2) {
    u8 length1, length2;
    length1 = strlen((char*) cad1);
    length2 = strlen((char*) cad2);
    u8 i;
    for (u8 i = 0; i< length1; i++)
        prv_string[i] = cad1[i];
    for (i = 0; i< length2; i++) {
        prv_string[i+length1] = cad2[i];
    }
	prv_string[i+length1] = '\0';
    return prv_string;
}

/**
 * \brief       Convert a number to a string
 * \param[in]   number: the number to convert
 * \param[in]   cad: the 3-char string that will contain the converted number
 * \param[in]	with_trailing_zeros: 1 if the string is filled with trailing zeros if the number is 
 *					lower than 100
 * \return      the string length after the conversion
 */
u8 my_itoa(u8 number, u8 cad[], _Bool with_trailing_zeros) {
    cad[0] = '0' + number/100;
    cad[1] = '0' + (number%100) / 10;
    cad[2] = '0' + (number%10) ;
    cad[3] = '\0';
    
    if (with_trailing_zeros)
        return 3;
    
    if (cad[0] != '0')
        return 3;
    cad[0] = cad[1];
    cad[1] = cad[2];
    cad[2] = '\0';
    if (cad[0] != '0')
        return 2;
    cad[0] = cad[1];
    cad[1] = '\0';
    return 1;
}

/* ------------- ASSIGNING STRINGS WITH MATCH INFO ------------------------ */

/**
 * \brief       Get a string consisting of the result of the games
 * \param[in]   none
 * \return      a pointer to the string with the result of the games
 */
u8* get_string_games(void) {
    static u8 prv_string_sets[6] = {'X', ' ', ':', ' ', 'X', 0};
	prv_string_sets[0] = var_glob.games_for_player[0] + '0'; 
	prv_string_sets[4] = var_glob.games_for_player[1] + '0'; 
    return prv_string_sets;
}

/**
 * \brief       Get a string consisting of the partial results 
 * \param[in]   none
 * \return      a pointer to the string with the partial results
 */
u8* get_string_points(void) {
    u8 tot_games = get_played_games();
    string_points[0] = '\0';
    u8 posic = 0;
    for (u8 i = 1; i <= tot_games; i++)
    {
        posic += my_itoa(var_glob.points_total_for_player[0][i], string_points+posic, 0);
        string_points[posic++] = ':';
        posic += my_itoa(var_glob.points_total_for_player[1][i], string_points+posic, 0);
        if (i!=tot_games){
            string_points[posic++] = ' ';
            string_points[posic++] = ':';    
            string_points[posic++] = ' ';
        }        
    }
    string_points[posic] = '\0';
    return string_points;
}

/**
 * \brief		Get the text that must be song by the marker
 * \param[in]   situation: pointer to the instance with the result of the rally
 * \return      pointer to the text to be song
 */
u8* get_text_for_the_marker(situation_t *situation) {
	u8 pos = 0;
	u8 ind_winn = situation->player_serving-1;
	u8 ind_los = 1-ind_winn;
	if (situation->points[ind_winn] > 9) {
		prv_string[pos++] = situation->points[ind_winn]/10 + '0';
	}
	prv_string[pos++] = situation->points[ind_winn]%10 + '0';
	prv_string[pos++] = '-';

	if (situation->points[ind_los] > 9) {
		prv_string[pos++] = situation->points[ind_los]/10 + '0';
	}
	prv_string[pos++] = situation->points[ind_los]%10 + '0';
	prv_string[pos++] = ':';
	// prv_string[pos++] = ' ';
	if (situation->there_was_change){
		prv_string[pos++] = Kst_char_Change;
	
	} else if (situation->service_quarter == RIGHT_QUARTER) {
		prv_string[pos++] = Kst_char_Right;
	
	} else {
		prv_string[pos++] = Kst_char_Left;
	}
    prv_string[pos] = '\0';
    return prv_string;   
}
/**
 * \brief		Get the text with the minutes and seconds corresponding to a certain amount of seconds
 * \param[in]   tot_seconds: the total number of seconds to be converted
 * \return      pointer to the text with minutes and seconds
 */
u8 * seconds_2_string_minutes_seconds(u16 tot_seconds) {
	u8 minutes = tot_seconds / 60;
	u8 seconds = tot_seconds % 60;
	prv_string[0] = minutes/10 + '0';
	prv_string[1] = minutes%10 + '0';
	prv_string[2] = ':';
	prv_string[3] = seconds/10 + '0';
	prv_string[4] = seconds%10 + '0';
	prv_string[5] = 0;
	return prv_string;
}

/* --------------- OBTAINING THE DIMENSIONS OF THE TEXT -------------------------------*/

/**
 * \brief		Get the number of lines of a string
 * \param[in]   string: a string that can consist of several lines separated by \n
 * \return      the number of lines
 */
u8 get_number_of_lines(const u8 *string) {
    u8 pos = 0;
    u8 num_lines = 1;
    while(string[pos] != '\0')
    {
        if (string[pos] == '\n')
            num_lines++;
        pos++;
    }
    return num_lines;
}

/**
 * \brief		Get the length of a single line string
 * \param[in]   string: a string that can terminate in \0 or \n
 * \return      the length of the text
 */
u8 my_strlen_sl(const u8 *string) {
    u8 pos = 0;

    while(string[pos] != '\0' && string[pos] != '\n')
        pos++;
    return pos;
}

/**
 * \brief		Get the length of a multi-line string
 * \param[in]   string: a string whose lines are separated by \n
 * \param[in]   pos_terminator: array with the positions where the lines start
 * \return      the maximum of the lines length
 */
u8 my_strlen_ml(const u8 *string, u8 *pos_terminator) {
    u8 pos = 0;
    u8 max_length = 0;
    u8 this_length = 0;
    u8 c_line = 0;
    while(string[pos] != '\0')
    {
        if (string[pos] == '\n')
        {    
            pos_terminator[c_line] = pos;
            c_line++;
            if (this_length > max_length)
                max_length = this_length;
            this_length = 0;
        }
        else
            this_length++;
        pos++;        
    }
    pos_terminator[c_line] = pos;
    if (this_length > max_length)
        max_length = this_length;

    return max_length;
}

/**
 * \brief		Get the width of a string, that can be multi-line or single-line
 * \param[in]   text: a string whose lines are separated by \n if it is a multiline text
 * \param[in]   font_sizeH: the number of pixesl in horizontal of the font (assuming fixed pitch)
 * \return      the width occupied by the text
 */
u8 str_width(const u8 *text, u8 font_sizeH) {
    u8 number_of_lines = get_number_of_lines(text);
    if (number_of_lines == 1) {
        return my_strlen_sl(text)*font_sizeH;
	}
    static u8 pos_terminator[MAX_NUM_LINES+1];
    return  (u16)(my_strlen_ml(text, pos_terminator) )*font_sizeH;
}

/* ------------------------- DISPLAYING THE TEXT  ---------------------------------*/

/**
 * \brief		Get the rectangle containing a string, that can be multi-line or single-line
 * \param[in]   x, y: coordinates of the point that define the text position
 * \param[in]	text:  a string whose lines are separated by \n if it is a multiline text
 * \param[in]	fontsizeV: the font size specified by the font height
 * \param[in]	type_of_reference: defines if the reference point is at the center, at the left...
 * \param[in]   rect (by reference): rectangle containing the text
 * \return      none
 */
void str_2_rect16(u16 x, u16 y, u8 *text, u8 fontsizeV, defined_from type_of_reference, rect16_t *rect) {
    
    u8 number_of_lines = get_number_of_lines(text);

    u8 fontsizeH = V2H(fontsizeV);
    u8 width =  str_width(text, fontsizeH);

    transf_vertices_2_rect16(x, y, NUM_LINES_2_HEIGHT(number_of_lines, fontsizeV), width, type_of_reference, rect);    
}



/**
 * \brief		Display a text, that can 1 line or multi-line
 * \param[in]   x, y: coordinates of the point that define the text position
 * \param[in]	fc:  text color
 * \param[in]	bc:  background color
 * \param[in]	str: string to be displayed
 * \param[in]	fontsizeV: the fontsize, as given by the vertical height
 * \param[in]   type_of_reference: defines if the reference point is at the center, at the left...
 * \param[in]	is_visible
  * \param[in]	is_enabled; if 0, the text is displayed in gray
 * \return      none
 */
void gui_str(u16 x, u16 y, u16 fc, u16 bc, const u8 *str, u8 fontsizeV, 
	defined_from type_of_reference, _Bool is_visible, _Bool is_enabled) {
    if (is_visible == INVISIBLE)
        return;
    if (is_enabled == DISABLED) {
        fc = COLOUR_TEXT_DISABLED;
        bc = fc;
    }
    u8 fontsizeH = V2H(fontsizeV);
    u8 num_lines = get_number_of_lines(str);
    
    u16 height = NUM_LINES_2_HEIGHT(num_lines, fontsizeV);


    if (num_lines == 1)
    {
        u8 length = my_strlen_sl(str);
        
        u16 x_st, y_st;
        Position_2_Position_left_top(x, y, length * fontsizeH, height, &x_st, &y_st, type_of_reference);
        display_1line_text(x_st , y_st , fc, bc, str, fontsizeV, is_visible, is_enabled);
        return;
    }
    // else
    
    static u8 pos_terminator[MAX_NUM_LINES+1];
    static u8 string_auxil[20];
    my_strlen_ml(str, pos_terminator)  ;
    s8 pos_term_ant = -1;
    for (u8 cl = 0; cl < num_lines; cl++)
    {
        u16 x_st = x, y_st;
        u8 this_pos = pos_terminator[cl];
        u8 this_length = this_pos - pos_term_ant -1;
		my_strcpy_ltd_number(string_auxil, str+pos_term_ant+1, this_length);
        
        y_st = y + cl * (SEP_V_LINES(fontsizeV) + fontsizeV);
		u8 pos_wo_sim = type_of_reference & 0x0F;
        if (pos_wo_sim == Center || pos_wo_sim == Left_Center || pos_wo_sim == Right_Center )
            y_st -= height / 2;
        
        if (pos_wo_sim == Center)
            x_st -=  this_length * fontsizeH / 2;

        if (type_of_reference & H_Simmetry)
            x_st = LCD_W - x_st - this_length * fontsizeH;

        display_1line_text(x_st , y_st ,fc, bc, string_auxil, fontsizeV, is_visible, is_enabled);

        pos_term_ant = this_pos;
    }    
}

/**
 * \brief		Assuming a multi-line string, obtain certain line
 * \param[in]   source: the multi-line string
 * \param[in]	index: the number of the line to be extracted
 * \return      pointer to the beginning of the text
 */
const u8* get_string_from_index(const u8 *source, u8 index) {
    u8 cont_strings = 0;
    if (index == 0)
        return source;

    while(1)
    {
        if (*source == '\n')
        {
            cont_strings ++;
            if (cont_strings == index)
                return source+2; // There is a space after the \n
            source++; // There is a space after the \n
        }
        source++;
    } // while (cont_strings < num_items);
}

/* --------------  OPERATIONS WITH THE NAME -------------------------------- */

/**
 * \brief		Suppress the spaces at the beginning, at the end; if there are two or 
 *					more consecutive spaces, eliminates them except 1
 * \param[in]   text_src: the original string
 * \param[in]	text_dest: the clean final string
 * \return      none
 */
void suppress_excessive_spaces(const u8* text_src, u8* text_dest) {
	u8 c_or, c_dest;
	u8 ind_fin, ind_ini;
 
	ind_fin = strlen((char*)text_src)-1;

	while(text_src[ind_fin] ==' ') {
		ind_fin--;
	}
	ind_ini = 0;
	while(text_src[ind_ini] ==' ') {
		ind_ini++;
	}
	for (c_or = ind_ini, c_dest = 0; c_or <= ind_fin; c_or++)
	{
		if (text_src[c_or] != ' ') {
			text_dest[c_dest] = text_src[c_or];
			c_dest++;
			continue;
		}
		while (text_src[c_or+1] == ' ') {
			c_or++;
		}
		text_dest[c_dest++] = ' ';
	}
	text_dest[c_dest] = '\0';
}

/**
 * \brief		Get the initial char of a name
 *					If typed name is John S or S John, returns S
 *					If typed name is John, returns J
 * \param[in]   typed_name: the typed text, without excessive spaces
 * \return      the initial char
 */
u8 get_initial_char(u8* typed_name) {
    u8 length = strlen((char*) typed_name);
    
    if (typed_name[length-2] == ' ')
        return typed_name[length-1];
    /* if (typed_name[1] == " ")
        return typed_name[0];
        */
    return typed_name[0];
}
/**
 * \brief		Get a truncated copy of the name
 *					If typed name is S John, returns S John
 *					If typed name is John S, returns John S
 *					If typed name is Maximiliam S, returns Maximi S  (the maximum length is 8 by default)
 *					If typed name is S Maximiliam, returns S Maximi
 * \param[in]   typed_name: the typed text, without excessive spaces
 * \param[in]   truncated_name: the truncated copy
 * \return      none
 */
void get_truncated_name(const u8* typed_name, u8* truncated_name) {
    u8 length = strlen((char*) typed_name);
    
    if (length <= MAX_NAME_SIZE) {
        my_strcpy(truncated_name, typed_name);
        
    } else if (typed_name[length-2] != ' ') {
        my_strcpy_ltd_number(truncated_name, typed_name, MAX_NAME_SIZE);

    } else {
        my_strcpy_ltd_number(truncated_name, typed_name, MAX_NAME_SIZE-2);
        truncated_name[MAX_NAME_SIZE-2] = ' ';
        truncated_name[MAX_NAME_SIZE-1] = typed_name[length-1];
    }
}

/**
 * \brief       Operates with the typed name: suppress an excess of spaces, assign to a certain player,
 *					get the initial char of the name, and a truncated copy of the name
 * \param[in]   typed_text: the name, as typed by the user
 * \param[in]	player_from_1: the player whose name will be assigned
 * \return      none
 */
void assign_player_name(u8* typed_text, u8 player_from_1) {
	suppress_excessive_spaces(typed_text, var_glob.name_typed_for_player[player_from_1 - 1]);
	u8 *txt = var_glob.name_typed_for_player[player_from_1 - 1];

	var_glob.name_initial_char[player_from_1 - 1] = get_initial_char(txt);
	get_truncated_name(txt, var_glob.name_shown_for_player[player_from_1 - 1]); 
}
