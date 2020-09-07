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

// denomtype:  Enum for denomination types used in a video poker game.
enum denomtype {
	QUARTER,
	HALF,
	DOLLAR,
	FIVEDOLLAR,
	TENDOLLAR
};

// buttonId:  Enum for all of the associated buttons in video poker game.
enum buttonId {
	NONE,
	BUTTON_ZERO,
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_FOUR,
	BUTTON_FIVE
};

struct commonGameStats {
	
	// mouse X and Y
	int mouseX;
	int mouseY;
	
	// current game being played
	enum gametype currentGame;

	// current denom being used
	enum denomtype currentDenom;

	// current currency value
	float currentGameCash;

	// mouse location in or out of button
	enum buttonId inButton;

	// current pressed button
	enum buttonId pressedButton;

};