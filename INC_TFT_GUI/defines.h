#pragma once

#if defined WIN32
#define PRAGMA_REGION_ACCEPTED 
#endif

/*  -------------------------- OPERATIVE DEFINITIONS ----------------------------*/
#define POINTS_TO_WIN 11

/* -------------------------  COMMUNICATIONS DEFINES ---------------------------*/
#define messagePuntos 1
#define messagePuntos 2



/*  -------------------------- DIFFERENT WINDOWS ---------------------------- */
#define GUI_START_APP 0
#define GUI_MATCH_CONF 1
#define GUI_PLAYERS_DEF 2
#define GUI_BREAK 3
#define GUI_SCORE 4
#define KEYBOARD 5
#define POPUP_SETS 6
#define POPUP_SPEC 7


/* --------------------- SCREEN DIMENSIONS  ------------------------------- */
#define X_ORG  5  // 130
#define Y_ORG  5

#define LCD_W				320
#define LCD_H				480


/* ----------------------BOOLEAN OPTIONS ------------------------------- */
#define VISIBLE         1
#define INVISIBLE       0
#define ENABLED         1
#define DISABLED        0
#define CHECKED         1
#define NOT_CHECKED     0
#define NOT_FILLED      0
#define FILLED          1
#define AND_SHOW        1
#define ONLY_ASSIGN     0

#define BACK_TRANSPARENT    1
#define BACK_OPAQUE         0
#define RIGHT_QUARTER		1
#define LEFT_QUARTER		0

/* ----------------------MAXIMUM RANGE OF ARRAYS ------------------------------*/
#define MAX_NAME_SIZE				8
#define MAX_NUM_CHAR_IN_TEXTBOX		20
#define MAX_NUM_CHAR_IN_TEXTVIEW	20
#define MAX_NUM_RECORDED_RESULTS	50
#define MAX_NUM_LINES				4       /* maximum number of lines in a button or label */
#define MAX_NUM_BUTTONS_POPUP		3
#if ! defined NULL
#define NULL 0
#endif

/* --------------------- COMPONENT DEFINITION -------------------------------	*/
#define RAD_BUT_FONT		        FONT16			
#define RAD_BUT_SIZE		        ((u16)(RAD_BUT_FONT*1.2))
#define RAD_BUT_SEP_H		        ((u16)(RAD_BUT_FONT*0.3))
#define	RAD_BUT_SEP_V		        ((u16)(RAD_BUT_SIZE*0.2)+4)
#define CHB_BUT_SEP_H		        ((u16)(RAD_BUT_FONT*0.6))


#define INFLATION_RAD_BUT_4_TOUCH   ((RAD_BUT_SEP_V)/2)
#define INFLATION_CHECBOX_4_TOUCH	3
#define DEFLATION_RAD_BUT_4_MARK    -3
#define DEFLATION_CHECkBOX_4_MARK	-3

#define INFLATION_BUTTON_4_BORDER	3

#define MULTIPLIER_HEIGHT_TEXTBOX 1.5

/* ------  Options for the shape justification  */
#define Center			0x01
#define Left_Top		0x02
#define Left_Center		0x03
#define Right_Center	0x04
#define No_Symmetry		0x00
#define H_Simmetry		0x10

/* ------- Position of the text with respect to the checkboxes   */
#define the_left	0
#define the_right	1
#define the_top		2
#define the_bottom	3


/* --------------------- FONTS ------------------------------- 	*/

#define FONT12				12      /* The vertical size of the font */
#define FONT16				16
#define FONT24				24
#define FONT32				32

#define MESSAGE_FONT        FONT24


/* --------------------- COLOURS -------------------------------*/

#if defined WIN32
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0xBC40 
#define BRRED 		0xFC07 
#define GRAY  		0x8430 

#define DARKBLUE    0x01CF	
#define LIGHTBLUE   0x7D7C	 
#define GRAYBLUE    0x5458 

 
#define LIGHTGREEN  0x841F 
#define LIGHTGRAY   0xEF5B 
#define LGRAY 		0xC618 

#define LGRAYBLUE   0xA651 
#define LBBLUE      0x2B12 

#endif

#define LILA			RGB24_2_RGB16(216,179,225)
#define DARKGRAY		RGB24_2_RGB16(30,30,30)
#define PURPLE_BLUE		RGB24_2_RGB16(129,38,238)
#define PURPLE_RED		RGB24_2_RGB16(160,70,160)
#define LTPURPLE_RED	RGB24_2_RGB16(220,60,220)
#define PINK_PURPLE		RGB24_2_RGB16(220,120,220)
#define ORANGE			RGB24_2_RGB16(235,160,25)

#define COLOUR_FILL_DISABLED LIGHTGRAY
#define COLOUR_TEXT_DISABLED GRAY

#define COLOR_BACKGROUND_DEFAULT WHITE

/* ------------- Colour indexes ----------------------*/
#define ind_RED 1
#define ind_CYAN 6
#define ind_WHITE 7
#define ind_YELLOW 3
#define ind_GREEN 2
#define ind_BLUE 4
#define ind_MAGENTA 5
