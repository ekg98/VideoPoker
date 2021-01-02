// sdlvpokerstatustable.c:  Source file for graphical status table in video poker

#include <stdio.h>
#include "common.h"
#include "sdlbuttons.h"

extern int intWindowWidth;
extern int intWindowHeight;

// vPokerStatusTableRender:  Renders the video poker status table on the screen for the gametype desired
bool vPokerStatusTableRender(SDL_Renderer* mainRenderer, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	// The boarders of the table on the top of the screen are controlled by the spacing of the buttons on the lower control panel.  This gives illusion of squaring off the game.

	SDL_Rect mainOutsideBoarder;
	SDL_Rect mainInsideBoarder;	
	
	int mainBoarderHeight = intWindowHeight / 2.5;
	
	// Yellow boarder spacing.  This value removes (x) pixels from each side of the box.  Even numbers only.
	int insideLargeYellowBoarderSpacing = 4;
	
	//  large outside black boarder
	mainOutsideBoarder.x = gamePokerControlButtonImageData->pokerControlButtonDest[0].x;
	mainOutsideBoarder.y = 10;
	mainOutsideBoarder.w = (gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w;
	mainOutsideBoarder.h = mainBoarderHeight;

	// calculations for large inside yellow boarder
	int insideLargeYellowBoarderWidth = mainOutsideBoarder.w - insideLargeYellowBoarderSpacing;
	int insideLargeYellowBoarderHeight = mainOutsideBoarder.h - insideLargeYellowBoarderSpacing;
	int insideLargeYellowBoarderX = ((mainOutsideBoarder.w - insideLargeYellowBoarderWidth) / 2) + mainOutsideBoarder.x;
	int insideLargeYellowBoarderY = ((mainOutsideBoarder.h - insideLargeYellowBoarderHeight) / 2) + mainOutsideBoarder.y;

	// large inside yellow boarder
	mainInsideBoarder.x = insideLargeYellowBoarderX;
	mainInsideBoarder.y = insideLargeYellowBoarderY;
	mainInsideBoarder.w = insideLargeYellowBoarderWidth;
	mainInsideBoarder.h = insideLargeYellowBoarderHeight;
		
	// set black color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);

	if (SDL_RenderFillRect(mainRenderer, &mainOutsideBoarder))
		fprintf(stderr, "Error\n");

	// set yellow color
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 0);

	if (SDL_RenderFillRect(mainRenderer, &mainInsideBoarder))
		fprintf(stderr, "Error\n");

	// set blue color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	return false;
}