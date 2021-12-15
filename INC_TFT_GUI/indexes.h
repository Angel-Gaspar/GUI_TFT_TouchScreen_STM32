#pragma once


/* ----------------------- */ CONFIGURATION ------------------------------------------

enum en_button_conf {en_Conf_bt_Jug1, en_Conf_bt_Jug2, en_Conf_bt_Breaking, en_Conf_bt_Recup
    , en_Conf_bt_Reset, en_Conf_bt_aON, en_Conf_bt_aOFF};

enum en_radio_button_conf {en_Conf_rb_3_5sets, en_Conf_rb_invert};

enum en_labels_conf {en_Conf_lb_points, en_Conf_lb_matched, en_Conf_lb_numsets, en_Conf_lb_orient
	, en_Conf_lb_defplyr1, en_Conf_lb_defplyr2, en_Conf_lb_Connect_leds};



/* ----------------------- */ DEFINITION OF PLAYERS -----------------------------------

enum en_button_defpl {en_Def_bt_Retornar, en_Def_bt_Red, en_Def_bt_Green, en_Def_bt_Yellow, en_Def_bt_Cyan, en_Def_bt_Blue, 
    en_Def_bt_Magenta,     en_Def_bt_White};

enum en_labels_defpl {en_Def_tv_type_tochange};

enum en_textviews_defpl {en_Def_tv_name_plx};

enum radio_button_defpl {en_Def_rb_zurdo};

/* ----------------------- */ HEATING and BREAK -----------------------------------

enum button_break {en_Break_bt_back, en_Break_bt_Reset, en_Break_bt_Score, en_Break_bt_Minus1_Play1, en_Break_bt_Plus1_Play1,  
en_Break_bt_Minus1_Play2, en_Break_bt_Plus1_Play2};

 enum label_break {en_Break_lb_rem_time, 
 en_Break_lb_ellapsed_time, en_Break_lb_name, en_Break_lb_sets,  en_Break_lb_sets_pl1,  en_Break_lb_sets_pl2};
 
 enum textview_break {en_Break_tv_rem_time, 
en_Break_tv_ellapsed_time, en_Break_tv_sets, en_Break_tv_serie_of_sets};
 
 /* ----------------------- */ SCORE  -----------------------------------
 enum button_score {en_Score_bt_break, en_Score_bt_refresh, en_Score_bt_win_pl1, en_Score_bt_win_pl2, en_Score_bt_changeLR,  en_Score_bt_pu_changesets, en_Score_bt_pu_specialactions};

enum label_score {en_Score_lb_games, en_Score_lb_endgame};

enum textview_score {en_Score_tv_result_4_marker, en_Score_tv_ellapsed_time, en_Score_tv_sets};

 /* ----------------------- */ POPUP SETS  -----------------------------------
/*
enum button_PopUpSets {en_PUSets_bt_back, en_PUSets_bt_Minus1_Play1, en_PUSets_bt_Plus1_Play1,  
en_PUSets_bt_Minus1_Play2, en_PUSets_bt_Plus1_Play2};

enum labels_PopUpSets {en_PUSets_bt_lb_setsply1, en_PUSets_bt_lb_setsply2};
enum textview_PopUpSets {en_PUSets_tv_name_pl1, en_PUSets_tv_name_pl2,
 en_PUSets_tv_setsply1, en_PUSets_tv_setsply2};
*/
 /* ----------------------- */ POPUP SPECIAL ACTIONS  --------------------------
/*
 enum button_PopUpSpec {en_PUspec_bt_back, en_PUspec_bt_correct, en_PUspec_bt_undo, en_PUspec_bt_recover,  en_PUspec_bt_ReconBT};
*/