#pragma once


#include <stdint.h>


#if defined WIN32
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;
typedef char s8;
typedef int s32;
#else 
#include "typedefs_int.h"
#include "Hardware_definition.h"
#endif

typedef u8    defined_from;
 
#if defined WIN32
typedef BOOL _Bool;
#endif

#if !defined(WIN32)
#define _Bool u8
#endif

typedef int16_t s16; // Why is it necessary ?? 

typedef struct {
    s16 x;
    s16 y;
} point16;

#if defined WIN32
typedef struct  
{                                            
    u16 width;            
    u16 height;            
    u16 id;                  
    u8  dir;              
    u16 wramcmd;        
    u16 setxcmd;        
    u16 setycmd;        
}_lcd_dev;     
#endif


typedef struct {
    u8 points0;
    u8 points1;
    u8 serve_situation;
	u16 time_s;
} result_t;

typedef struct {
	u8 points[2];
	_Bool there_was_change;
	_Bool service_quarter;
	u8 player_serving;
	u16 time_s;

} situation_t;




