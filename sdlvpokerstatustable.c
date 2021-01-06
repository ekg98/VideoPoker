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

	// variable declarations
	SDL_Rect mainOutsideBoarderTrim;
	SDL_Rect mainInsideBoarderTrim;	
	SDL_Rect columnOneHandDescriptionTextTrim, columnTwoBetOneValueTrim, columnThreeBetTwoValueTrim, columnFourBetThreeValueTrim, columnFiveBetFourValueTrim, columnSixBetFiveValueTrim;
	SDL_Rect columnOneHandDescriptionText, columnTwoBetOneValue, columnThreeBetTwoValue, columnFourBetThreeValue, columnFiveBetFourValue, columnSixBetFiveValue;

	// black boarder trim spacing.  This value removes (x) pixels from each side of the box.  Even numbers only.
	int blackBoarderSpacing = 4;




	// calculations for video poker status table

	// sets position of video poker status table in the vertical
	int mainBoarderHeight = intWindowHeight / 2.5;
	
			
	
	// calculations for large outside black boarder trim 
	mainOutsideBoarderTrim.x = gamePokerControlButtonImageData->pokerControlButtonDest[0].x;
	mainOutsideBoarderTrim.y = 10;
	mainOutsideBoarderTrim.w = (gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w;
	mainOutsideBoarderTrim.h = mainBoarderHeight;



	// calculations for large inside yellow boarder trim
	int insideLargeYellowBoarderWidth = mainOutsideBoarderTrim.w - blackBoarderSpacing;
	int insideLargeYellowBoarderHeight = mainOutsideBoarderTrim.h - blackBoarderSpacing;
	int insideLargeYellowBoarderX = ((mainOutsideBoarderTrim.w - insideLargeYellowBoarderWidth) / 2) + mainOutsideBoarderTrim.x;
	int insideLargeYellowBoarderY = ((mainOutsideBoarderTrim.h - insideLargeYellowBoarderHeight) / 2) + mainOutsideBoarderTrim.y;

	// large inside yellow boarder trim assignments
	mainInsideBoarderTrim.x = insideLargeYellowBoarderX;
	mainInsideBoarderTrim.y = insideLargeYellowBoarderY;
	mainInsideBoarderTrim.w = insideLargeYellowBoarderWidth;
	mainInsideBoarderTrim.h = insideLargeYellowBoarderHeight;
	


	// calculations for card text column black trim
	int columnOneHandDescriptionTextTrimWidth = mainInsideBoarderTrim.w - blackBoarderSpacing;
	int columnOneHandDescriptionTextTrimHeight = mainInsideBoarderTrim.h - blackBoarderSpacing;
	int columnOneHandDescriptionTextTrimX = (mainInsideBoarderTrim.w - columnOneHandDescriptionTextTrimWidth);
	int columnOneHandDescriptionTextTrimY;

	// columnOneHandDescriptionTextTrim assignments
	columnOneHandDescriptionTextTrim.x;
	columnOneHandDescriptionTextTrim.y;
	columnOneHandDescriptionTextTrim.w = columnOneHandDescriptionTextTrimWidth;
	columnOneHandDescriptionTextTrim.h = columnOneHandDescriptionTextTrimHeight;



	// draw the status table

	// set black color
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);

	// draw primary black outside boarder trim
	if (SDL_RenderFillRect(mainRenderer, &mainOutsideBoarderTrim))
		fprintf(stderr, "Error drawing video poker status table primary outside black boarder trim.\n");

	// set yellow color
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 0);

	// draw primary yellow inside boarder trim
	if (SDL_RenderFillRect(mainRenderer, &mainInsideBoarderTrim))
		fprintf(stderr, "Error drawing video poker status table primary inside yellow boarder trim.\n");

	// set back to blue color for gameplay.  Unsure if needed.  Good practice
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	return false;
}