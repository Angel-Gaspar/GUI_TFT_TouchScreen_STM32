#pragma once

/**
 * \brief           get absolute value
 * \param[in]       x: numeric value
 * \return          Its absolute value
 * \hideinitializer
 */
#ifndef ABS
#define ABS(a) (a)>0?(a):(-(a))
#endif

/**
 * \brief           get minimal value between `x` and `y`
 * \param[in]       x: First value
 * \param[in]       y: Second value
 * \return          Minimal value between `x` and `y`
 * \hideinitializer
 */
#ifndef MIN
#define MIN(x, y)       ((x) < (y) ? (x) : (y))
#endif

/**
 * \brief           Convert a colour formatted in RGB24 into RGB16
 * \param[in]       r: amount of red between 0 and 255
 * \param[in]       g: amount of green between 0 and 255
 * \param[in]       b: amount of blue between 0 and 255
 * \return          The converted value as 2-byte colour
 * \hideinitializer
 */
#define RGB24_2_RGB16(r,g,b) ((((r)/8)<<11) | (((g)/4) << 5) | ((b)/8))

/**
 * \brief           Increment the number of won games of a player
 * \param[in]       a: player
 * \return          Nothing
 * \hideinitializer
 */
#define INCR_GAMES_FOR_PLAYER(a) do  { \
	 if (var_glob.games_for_player[a-1] < var_glob.games_to_win_the_match) \
        var_glob.games_for_player[a-1] ++; \
		} while (0)

/**
 * \brief           decrement the number of won games of a player
 * \param[in]       a: player
 * \return          Nothing
 * \hideinitializer
 */
#define DECR_GAMES_FOR_PLAYER(a) do  { \
	 if (var_glob.games_for_player[a-1] > 0) \
        var_glob.games_for_player[a-1] --; \
		} while (0)

/**
 * \brief           Assign the active window and store the procedence one
 * \param[in]       None
 * \return          Nothing
 * \hideinitializer
 */
#define UPDATE_ACTIVE_WINDOW do { \
	gui.procedence_window = gui.active_window; \
	gui.active_window = this_window; \
	} while (0)


/**
 * \brief           get a fraction of the screen width
 * \param[in]       a: fraction between 0 and 1
 * \return          The horizontal position between o and lcd width
 * \hideinitializer
 */
#define Esc_Hor(a)			(u16)(LCD_W*a)

/**
 * \brief           get a fraction of the screen height
 * \param[in]       a: fraction between 0 and 1
 * \return          The vertical position between o and lcd height
 * \hideinitializer
 */
#define Esc_Vrt(a)			(u16)(LCD_H*a)

/**
 * \brief           get the width of the font from its height
 * \param[in]       a: the font size given as its vertical height
 * \return          The font size as given by its horizontal width
 * \hideinitializer
 */
#define V2H(a)              (a/2)   /* Applied to font size */

/**
 * \brief           get the vertical separation between lines of text
 * \param[in]       a: the font size as given by its vertical height
 * \return          The vertical separation between lines
 * \hideinitializer
 */
#define SEP_V_LINES(font)	(u16)(font*0.1)

/**
 * \brief           Deduce the text height from the number of lines and the vertical fontsize
 * \param[in]       nlines: the number of lines
 * \param[in]       fontsize: the font size as given by its vertical height
 * \return          The vertical separation between lines
 * \hideinitializer
 */
#define NUM_LINES_2_HEIGHT(nlines,fontsize)		(u16)((nlines*fontsize+(nlines-1)*SEP_V_LINES(fontsize)))
