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
	
	float mainBoarderHeight = intWindowHeight / 2.4;
	
	// controls size of large yellow boarder
	const float YELLOWMULTIPLIER = 0.995;
	
	//  large outside black boarder
	mainOutsideBoarder.x = gamePokerControlButtonImageData->pokerControlButtonDest[0].x;
	mainOutsideBoarder.y = 10;
	mainOutsideBoarder.w = (gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w;
	mainOutsideBoarder.h = mainBoarderHeight;

	// calculations for large inside yellow boarder
	float insideYellowBoarderWidth = mainOutsideBoarder.w * YELLOWMULTIPLIER;
	float insideYellowBoarderHeight = mainOutsideBoarder.h * YELLOWMULTIPLIER;
	float insideYellowBoarderX = ((mainOutsideBoarder.w - insideYellowBoarderWidth) / 2) + mainOutsideBoarder.x;
	float insideYellowBoarderY = ((mainOutsideBoarder.h - insideYellowBoarderHeight) / 2) + mainOutsideBoarder.y;

	// y??? (mainBoarderHeight - (mainBoarderHeight * YELLOWMULTIPLIER))

	// large inside yellow boarder
	mainInsideBoarder.x = insideYellowBoarderX;
	mainInsideBoarder.y = insideYellowBoarderY;
	mainInsideBoarder.w = insideYellowBoarderWidth;
	mainInsideBoarder.h = insideYellowBoarderHeight;

	printf("insideYellowBoarderX = %f ", insideYellowBoarderX);
	printf("mainOutsideBoarder.x = %d ", mainOutsideBoarder.x);
	printf("mainInsideBoarder.x = %d\n", mainInsideBoarder.x);

	//black
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);

	if (SDL_RenderFillRect(mainRenderer, &mainOutsideBoarder))
		fprintf(stderr, "Error\n");

	//yellow
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 0);

	if (SDL_RenderFillRect(mainRenderer, &mainInsideBoarder))
		fprintf(stderr, "Error\n");

	//blue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	return false;
}