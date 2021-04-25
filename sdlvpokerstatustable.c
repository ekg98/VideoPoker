// sdlvpokerstatustable.c:  Source file for graphical status table in video poker

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "sdlbuttons.h"

extern int intWindowWidth;
extern int intWindowHeight;

// vPokerStatusTableRender:  Renders the video poker status table on the screen for the gametype desired
bool vPokerStatusTableRender(SDL_Renderer* mainRenderer, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	// The boarders of the table on the top of the screen are controlled by the spacing of the buttons on the lower control panel.  This gives illusion of squaring off the game.

	// variable declarations
	SDL_Rect mainOutsideBoarderTrim, mainInsideBoarderTrim;
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
	mainInsideBoarderTrim.h = mainOutsideBoarderTrim.h - blackBoarderSpacing;
	mainInsideBoarderTrim.w = mainOutsideBoarderTrim.w - blackBoarderSpacing;
	mainInsideBoarderTrim.x = ((mainOutsideBoarderTrim.w - mainInsideBoarderTrim.w) / 2) + mainOutsideBoarderTrim.x;
	mainInsideBoarderTrim.y = ((mainOutsideBoarderTrim.h - mainInsideBoarderTrim.h) / 2) + mainOutsideBoarderTrim.y;
		
	// columnOneHandDescriptionTextTrim
	columnOneHandDescriptionTextTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnOneHandDescriptionTextTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 3);
	columnOneHandDescriptionTextTrim.x = mainInsideBoarderTrim.x + (blackBoarderSpacing / 2);
	columnOneHandDescriptionTextTrim.y = ((mainInsideBoarderTrim.h - columnOneHandDescriptionTextTrim.h) / 2) + mainInsideBoarderTrim.y;
	
	// columnOneHandDescriptionText
	columnOneHandDescriptionText.x = columnOneHandDescriptionTextTrim.x + (blackBoarderSpacing / 2);
	columnOneHandDescriptionText.y = columnOneHandDescriptionTextTrim.y + (blackBoarderSpacing / 2);
	columnOneHandDescriptionText.w = columnOneHandDescriptionTextTrim.w - blackBoarderSpacing;
	columnOneHandDescriptionText.h = columnOneHandDescriptionTextTrim.h - blackBoarderSpacing;

	// columnTwoBetOneValueTrim
	columnTwoBetOneValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnTwoBetOneValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnTwoBetOneValueTrim.x = (columnOneHandDescriptionTextTrim.x + columnOneHandDescriptionTextTrim.w) + (blackBoarderSpacing / 2);
	columnTwoBetOneValueTrim.y = ((mainInsideBoarderTrim.h - columnTwoBetOneValueTrim.h) / 2) + mainInsideBoarderTrim.y;
		
	// columnTwoBetOneValue
	columnTwoBetOneValue.w = columnTwoBetOneValueTrim.w - blackBoarderSpacing;
	columnTwoBetOneValue.h = columnTwoBetOneValueTrim.h - blackBoarderSpacing;
	columnTwoBetOneValue.x = columnTwoBetOneValueTrim.x + (blackBoarderSpacing / 2);
	columnTwoBetOneValue.y = columnTwoBetOneValueTrim.y + (blackBoarderSpacing / 2);

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

	// columnSixBetFiveTrim
	columnSixBetFiveValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnSixBetFiveValueTrim.w = ((columnOneHandDescriptionTextTrim.w / 3) * 2) - (blackBoarderSpacing * 2.5);
	columnSixBetFiveValueTrim.x = (columnFiveBetFourValueTrim.x + columnFiveBetFourValueTrim.w) + (blackBoarderSpacing / 2);
	columnSixBetFiveValueTrim.y = (mainInsideBoarderTrim.h - columnSixBetFiveValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// columnSixBetFiveValue
	columnSixBetFiveValue.h = columnSixBetFiveValueTrim.h - blackBoarderSpacing;
	columnSixBetFiveValue.w = columnSixBetFiveValueTrim.w - blackBoarderSpacing;
	columnSixBetFiveValue.x = columnSixBetFiveValueTrim.x + (blackBoarderSpacing / 2);
	columnSixBetFiveValue.y = columnSixBetFiveValueTrim.y + (blackBoarderSpacing / 2);



	// render the status table

	// renderMainOutsideBoarderTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &mainOutsideBoarderTrim))
	{
		fprintf(stderr, "Error drawing video poker status table primary outside black boarder trim.\n");
		return EXIT_FAILURE;
	}

	// render mainInsideBoarderTrim
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &mainInsideBoarderTrim))
	{
		fprintf(stderr, "Error drawing video poker status table primary inside yellow boarder trim.\n");
		return EXIT_FAILURE;
	}

	// render columnOneHandDescriptionTextTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnOneHandDescriptionTextTrim))
	{
		fprintf(stderr, "Error drawing video poker status table column one hand description text trim.\n");
		return EXIT_FAILURE;
	}

	// render columnOneHandDescriptionText
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnOneHandDescriptionText))
	{
		fprintf(stderr, "Error drawing video poker status table column one hand description text box.\n");
		return EXIT_FAILURE;
	}

	// render columnTwoBetOneValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnTwoBetOneValueTrim))
	{
		fprintf(stderr, "Error drawing video poker status table column two bet one text trim.\n");
		return EXIT_FAILURE;
	}

	// render columnTwoBetOneValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnTwoBetOneValue))
	{
		fprintf(stderr, "Error drawing video poker status table column two bet one text box.\n");
		return EXIT_FAILURE;
	}

	// render columnThreeBetTwoValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnThreeBetTwoValueTrim))
	{
		fprintf(stderr, "Error drawing video poker status table column three bet two text trim.\n");
		return EXIT_FAILURE;
	}

	// render columnThreeBetTwoValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnThreeBetTwoValue))
	{
		fprintf(stderr, "Error drawing video poker status table column three bet two text box.\n");
		return EXIT_FAILURE;
	}

	// render columnFourBetThreeValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFourBetThreeValueTrim))
	{
		fprintf(stderr, "Error drawing video poker status table column four bet three text trim.\n");
		return EXIT_FAILURE;
	}

	// render columnFourBetThreeValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFourBetThreeValue))
	{
		fprintf(stderr, "Error drawing video poker status table column four bet three text box.\n");
		return EXIT_FAILURE;
	}

	// render columnFiveBetFourValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFiveBetFourValueTrim))
	{
		fprintf(stderr, "Error drawing video poker status table column five bet four text trim.\n");
		return EXIT_FAILURE;
	}

	// render columnFiveBetFourValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnFiveBetFourValue))
	{
		fprintf(stderr, "Error drawing video poker status table column five bet four text box.\n");
		return EXIT_FAILURE;
	}
	// render columnSixBetFiveValueTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnSixBetFiveValueTrim))
	{
		fprintf(stderr, "Error drawing video poker status table column six bet five text trim.\n");
		return EXIT_FAILURE;
	}

	// render columnSixBetFiveValue
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &columnSixBetFiveValue))
	{
		fprintf(stderr, "Error drawing video poker status table column six bet five text box.\n");
		return EXIT_FAILURE;
	}

	// set back to blue color for gameplay.  Unsure if needed.  Good practice
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	// everything was rendered correctly
	return EXIT_SUCCESS;
}