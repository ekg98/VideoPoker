// Common.h  Common includes for VideoPoker

#ifdef _MSC_VER
	#define _CRT_NONSTDC_NO_WARNINGS
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
#include "cards.h"

enum gametype {
		JACKS_OR_BETTER,
		DUCES_WILD
};
