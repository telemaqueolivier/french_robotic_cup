#ifndef OPTIONS_DEFINED
#define OPTIONS_DEFINED

#include <uart_pc.h>
#include <stdio.h>
//Some uart_pc doesn't work if defined but
//strat communication doesn't work if not defined 
#define STRAT_OPTIMIZED

//In order to unactivate speed filter
//uncomment the folowing line
//#define NO_SPEED_FILTER

//décommenter cette ligne pour utiliser la nouvelle rampe
#define NEW_RAMP
#define DEBUG

#ifdef DEBUG
	#define DEBUG_CS
	#define DEBUG_RS
	#define DEBUG_XY
#endif

#endif//OPTIONS_DEFINED