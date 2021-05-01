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
#include <stdlib.h>

// Window resolutions and card resolutions
#define DEFAULT_WINDOW_WIDTH 1920 // 1920
#define DEFAULT_WINDOW_HEIGHT 1200 // was 1200
#define CARD_WIDTH  350
#define CARD_HEIGHT 500
#define MAX_FRAMERATE	60

#define	TRUE	1
#define	FALSE	0

// gametype:  Enum for selection of a game type to play.
enum gametype {
		MAIN_MENU,
		JACKS_OR_BETTER,
		DUCES_WILD
};

// handState:  Enum for the state of a poker hand.  Used to determine if on first or second hand for held card logic.
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
	BUTTON_ONE,
	BUTTON_TWO,
	BUTTON_THREE,
	BUTTON_FOUR,
	BUTTON_FIVE,
	BUTTON_SIX,
	CARD_ONE,
	CARD_TWO,
	CARD_THREE,
	CARD_FOUR,
	CARD_FIVE
};

// commonGameStats:  Structure holding some common game stats used in various places.
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