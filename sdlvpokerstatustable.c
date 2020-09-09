// sdlvpokerstatustable.c:  Source file for graphical status table in video poker

#include <stdio.h>
#include "common.h"
#include "sdlbuttons.h"

extern int intWindowWidth;
extern int intWindowHeight;

// vPokerStatusTableRender:  Renders the video poker status table on the screen for the gametype desired
bool vPokerStatusTableRender(SDL_Renderer* mainRenderer, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	const SDL_Rect mainOutsideBoarder = {
		gamePokerControlButtonImageData->pokerControlButtonDest[0].x,
		0,
		(gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w,
		intWindowHeight / 2.4
	};
	
	SDL_Rect mainInsideBoarder;
	
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);

	if (SDL_RenderFillRect(mainRenderer, &mainOutsideBoarder))
		fprintf(stderr, "Error\n");

	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	return false;
}