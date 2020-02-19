// Common.h  Common includes for VideoPoker

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
#endif

#include <stdio.h>
#include <stdbool.h>


enum gametype {
		MAIN_MENU,
		JACKS_OR_BETTER,
		DUCES_WILD
};

enum handState {
	SECOND_HAND,
	FIRST_HAND 
};

enum denomtype {
	QUARTER,
	HALF,
	DOLLAR,
	FIVEDOLLAR,
	TENDOLLAR
};