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
	int blackBoarderSpacing = 6;




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
	int columnOneHandDescriptionTextTrimWidth = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 3);
	int columnOneHandDescriptionTextTrimHeight = mainInsideBoarderTrim.h - blackBoarderSpacing;
	int columnOneHandDescriptionTextTrimX = mainInsideBoarderTrim.x + (blackBoarderSpacing / 2);
	int columnOneHandDescriptionTextTrimY = ((mainInsideBoarderTrim.h - columnOneHandDescriptionTextTrimHeight) / 2) + mainInsideBoarderTrim.y;

	// columnOneHandDescriptionTextTrim assignments
	columnOneHandDescriptionTextTrim.x = columnOneHandDescriptionTextTrimX;
	columnOneHandDescriptionTextTrim.y = columnOneHandDescriptionTextTrimY;
	columnOneHandDescriptionTextTrim.w = columnOneHandDescriptionTextTrimWidth;
	columnOneHandDescriptionTextTrim.h = columnOneHandDescriptionTextTrimHeight;

	// calculations for card text column blue box

	int columnOneHandDescriptionTextWidth = columnOneHandDescriptionTextTrim.w - blackBoarderSpacing;
	int columnOneHandDescriptionTextHeight = columnOneHandDescriptionTextTrim.h - blackBoarderSpacing;
	int columnOneHandDescriptionTextX = columnOneHandDescriptionTextTrim.x + (blackBoarderSpacing / 2);
	int columnOneHandDescriptionTextY = columnOneHandDescriptionTextTrim.y + (blackBoarderSpacing / 2);

	// columnOneHandDescriptionText assignments
	columnOneHandDescriptionText.x = columnOneHandDescriptionTextX;
	columnOneHandDescriptionText.y = columnOneHandDescriptionTextY;
	columnOneHandDescriptionText.w = columnOneHandDescriptionTextWidth;
	columnOneHandDescriptionText.h = columnOneHandDescriptionTextHeight;

	// calculations for column two bet one value trim
	int columnTwoBetOneValueTrimWidth = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	int columnTwoBetOneValueTrimHeight = mainInsideBoarderTrim.h - blackBoarderSpacing;
	int columnTwoBetOneValueTrimX = (columnOneHandDescriptionTextTrim.x + columnOneHandDescriptionTextTrim.w) + (blackBoarderSpacing / 2);
	int columnTwoBetOneValueTrimY = ((mainInsideBoarderTrim.h - columnTwoBetOneValueTrimHeight) / 2) + mainInsideBoarderTrim.y;

	//columnTwoBetOneValueTrim assignments
	columnTwoBetOneValueTrim.x = columnTwoBetOneValueTrimX;
	columnTwoBetOneValueTrim.y = columnTwoBetOneValueTrimY;
	columnTwoBetOneValueTrim.w = columnTwoBetOneValueTrimWidth;
	columnTwoBetOneValueTrim.h = columnTwoBetOneValueTrimHeight;

	// columnTwoBetOneValue
	int columnTwoBetOneValueWidth = columnTwoBetOneValueTrim.w - blackBoarderSpacing;
	int columnTwoBetOneValueHeight = columnTwoBetOneValueTrim.h - blackBoarderSpacing;
	int columnTwoBetOneValueX = columnTwoBetOneValueTrim.x + (blackBoarderSpacing / 2);
	int columnTwoBetOneValueY = columnTwoBetOneValueTrim.y + (blackBoarderSpacing / 2);

	//columnTwoBetOneValue assignments
	columnTwoBetOneValue.x = columnTwoBetOneValueX;
	columnTwoBetOneValue.y = columnTwoBetOneValueY;
	columnTwoBetOneValue.w = columnTwoBetOneValueWidth;
	columnTwoBetOneValue.h = columnTwoBetOneValueHeight;

	// columnThreeBetTwoTrim
	columnThreeBetTwoValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnThreeBetTwoValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnThreeBetTwoValueTrim.x = (columnTwoBetOneValueTrim.x + columnTwoBetOneValueTrim.w) + (blackBoarderSpacing / 2);
	columnThreeBetTwoValueTrim.y = (mainInsideBoarderTrim.h - columnThreeBetTwoValueTrim.h) / 2 + mainInsideBoarderTrim.y;
	
	// columnThreeBetTwoValue
	columnThreeBetTwoValue.h = columnThreeBetTwoValueTrim.h - blackBoarderSpacing;
	columnThreeBetTwoValue.w = columnThreeBetTwoValueTrim.w - blackBoarderSpacing;
	columnThreeBetTwoValue.x = columnThreeBetTwoValueTrim.x + (blackBoarderSpacing / 2);
	columnThreeBetTwoValue.y = columnThreeBetTwoValueTrim.y + (blackBoarderSpacing / 2);

	// columnFourBetThreeTrim
	columnFourBetThreeValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnFourBetThreeValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnFourBetThreeValueTrim.x = (columnThreeBetTwoValueTrim.x + columnThreeBetTwoValueTrim.w) + (blackBoarderSpacing / 2);
	columnFourBetThreeValueTrim.y = (mainInsideBoarderTrim.h - columnFourBetThreeValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// columnFourBetThreeValue
	columnFourBetThreeValue.h = columnFourBetThreeValueTrim.h - blackBoarderSpacing;
	columnFourBetThreeValue.w = columnFourBetThreeValueTrim.w - blackBoarderSpacing;
	columnFourBetThreeValue.x = columnFourBetThreeValueTrim.x + (blackBoarderSpacing / 2);
	columnFourBetThreeValue.y = columnFourBetThreeValueTrim.y + (blackBoarderSpacing / 2);

	// columnFiveBetFourTrim
	columnFiveBetFourValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnFiveBetFourValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnFiveBetFourValueTrim.x = (columnFourBetThreeValueTrim.x + columnFourBetThreeValueTrim.w) + (blackBoarderSpacing / 2);
	columnFiveBetFourValueTrim.y = (mainInsideBoarderTrim.h - columnFiveBetFourValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// columnFiveBetFourValue
	columnFiveBetFourValue.h = columnFiveBetFourValueTrim.h - blackBoarderSpacing;
	columnFiveBetFourValue.w = columnFiveBetFourValueTrim.w - blackBoarderSpacing;
	columnFiveBetFourValue.x = columnFiveBetFourValueTrim.x + (blackBoarderSpacing / 2);
	columnFiveBetFourValue.y = columnFiveBetFourValueTrim.y + (blackBoarderSpacing / 2);
	


	// render the status table

	// draw primary black outside boarder trim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &mainOutsideBoarderTrim))
		fprintf(stderr, "Error drawing video poker status table primary outside black boarder trim.\n");

	// draw primary yellow inside boarder trim
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &mainInsideBoarderTrim))
		fprintf(stderr, "Error drawing video poker status table primary inside yellow boarder trim.\n");
		
	// draw column one hand description text trim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnOneHandDescriptionTextTrim))
		fprintf(stderr, "Error drawing video poker status table column one hand description text trim.\n");

	// draw column one hand description text box
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnOneHandDescriptionText))
		fprintf(stderr, "Error drawing video poker status table column one hand description text box.\n");
		
	// draw column two bet one value trim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnTwoBetOneValueTrim))
		fprintf(stderr, "Error drawing video poker status table column two bet one text trim.\n");
	
	// draw column two bet one value
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnTwoBetOneValue))
		fprintf(stderr, "Error drawing video poker status table column two bet one text box.\n");

	// render columnThreeBetTwoValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnThreeBetTwoValueTrim))
		fprintf(stderr, "Error drawing video poker status table column three bet two text trim.\n");

	// render columnThreeBetTwoValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnThreeBetTwoValue))
		fprintf(stderr, "Error drawing video poker status table column three bet two text box.\n");

	// render columnFourBetThreeValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFourBetThreeValueTrim))
		fprintf(stderr, "Error drawing video poker status table column four bet three text trim.\n");

	// render columnFourBetThreeValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFourBetThreeValue))
		fprintf(stderr, "Error drawing video poker status table column four bet three text box.\n");

	// render columnFiveBetFourValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFiveBetFourValueTrim))
		fprintf(stderr, "Error drawing video poker status table column five bet four text trim.\n");

	// render columnFiveBetFourValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFiveBetFourValue))
		fprintf(stderr, "Error drawing video poker status table column five bet four text box.\n");

	// set back to blue color for gameplay.  Unsure if needed.  Good practice
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	return false;
}