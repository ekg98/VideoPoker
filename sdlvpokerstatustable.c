// sdlvpokerstatustable.c:  Source file for graphical status table in video poker

#include "common.h"
#include "sdlbuttons.h"
#include "sdlvpokerstatustable.h"

extern int intWindowWidth;
extern int intWindowHeight;

bool vPokerStatusTableBoxCalculations(SDL_Renderer* mainRenderer, struct vPokerStatusTableCoordinates *tableCoordinates, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	// The table on the top of the screen is controlled by the spacing of the buttons on the lower control panel.  This gives illusion of squaring off the game.

	// variable declarations
	SDL_Rect mainInsideBoarderTrim;
	SDL_Rect columnOneHandDescriptionTextTrim, columnTwoBetOneValueTrim, columnThreeBetTwoValueTrim, columnFourBetThreeValueTrim, columnFiveBetFourValueTrim, columnSixBetFiveValueTrim;
	
	// black boarder trim spacing.  This value removes (x) pixels from each side of the box.  Even numbers only.
	const int blackBoarderSpacing = 6;


	// calculations for video poker status table

	// sets position of video poker status table in the vertical
	const int mainBoarderHeight = intWindowHeight / 2.5;


	// largeBlackBox
	tableCoordinates->largeBlackBox.x = gamePokerControlButtonImageData->pokerControlButtonDest[0].x;
	tableCoordinates->largeBlackBox.y = 10;
	tableCoordinates->largeBlackBox.w = (gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w;
	tableCoordinates->largeBlackBox.h = mainBoarderHeight;

	// calculations for large inside yellow boarder trim
	mainInsideBoarderTrim.h = tableCoordinates->largeBlackBox.h - blackBoarderSpacing;
	mainInsideBoarderTrim.w = tableCoordinates->largeBlackBox.w - blackBoarderSpacing;
	mainInsideBoarderTrim.x = ((tableCoordinates->largeBlackBox.w - mainInsideBoarderTrim.w) / 2) + tableCoordinates->largeBlackBox.x;
	mainInsideBoarderTrim.y = ((tableCoordinates->largeBlackBox.h - mainInsideBoarderTrim.h) / 2) + tableCoordinates->largeBlackBox.y;

	// columnOneHandDescriptionTextTrim
	columnOneHandDescriptionTextTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnOneHandDescriptionTextTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 3);
	columnOneHandDescriptionTextTrim.x = mainInsideBoarderTrim.x + (blackBoarderSpacing / 2);
	columnOneHandDescriptionTextTrim.y = ((mainInsideBoarderTrim.h - columnOneHandDescriptionTextTrim.h) / 2) + mainInsideBoarderTrim.y;

	// blueBox #0
	tableCoordinates->blueBox[0].x = columnOneHandDescriptionTextTrim.x + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[0].y = columnOneHandDescriptionTextTrim.y + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[0].w = columnOneHandDescriptionTextTrim.w - blackBoarderSpacing;
	tableCoordinates->blueBox[0].h = columnOneHandDescriptionTextTrim.h - blackBoarderSpacing;

	// columnTwoBetOneValueTrim
	columnTwoBetOneValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnTwoBetOneValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnTwoBetOneValueTrim.x = (columnOneHandDescriptionTextTrim.x + columnOneHandDescriptionTextTrim.w) + (blackBoarderSpacing / 2);
	columnTwoBetOneValueTrim.y = ((mainInsideBoarderTrim.h - columnTwoBetOneValueTrim.h) / 2) + mainInsideBoarderTrim.y;

	// blueBox #1
	tableCoordinates->blueBox[1].h = columnTwoBetOneValueTrim.h - blackBoarderSpacing;
	tableCoordinates->blueBox[1].w = columnTwoBetOneValueTrim.w - blackBoarderSpacing;
	tableCoordinates->blueBox[1].x = columnTwoBetOneValueTrim.x + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[1].y = columnTwoBetOneValueTrim.y + (blackBoarderSpacing / 2);

	// columnThreeBetTwoTrim
	columnThreeBetTwoValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnThreeBetTwoValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnThreeBetTwoValueTrim.x = (columnTwoBetOneValueTrim.x + columnTwoBetOneValueTrim.w) + (blackBoarderSpacing / 2);
	columnThreeBetTwoValueTrim.y = (mainInsideBoarderTrim.h - columnThreeBetTwoValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// blueBox #2
	tableCoordinates->blueBox[2].h = columnThreeBetTwoValueTrim.h - blackBoarderSpacing;
	tableCoordinates->blueBox[2].w = columnThreeBetTwoValueTrim.w - blackBoarderSpacing;
	tableCoordinates->blueBox[2].x = columnThreeBetTwoValueTrim.x + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[2].y = columnThreeBetTwoValueTrim.y + (blackBoarderSpacing / 2);

	// columnFourBetThreeTrim
	columnFourBetThreeValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnFourBetThreeValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnFourBetThreeValueTrim.x = (columnThreeBetTwoValueTrim.x + columnThreeBetTwoValueTrim.w) + (blackBoarderSpacing / 2);
	columnFourBetThreeValueTrim.y = (mainInsideBoarderTrim.h - columnFourBetThreeValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// blueBox #3
	tableCoordinates->blueBox[3].h = columnFourBetThreeValueTrim.h - blackBoarderSpacing;
	tableCoordinates->blueBox[3].w = columnFourBetThreeValueTrim.w - blackBoarderSpacing;
	tableCoordinates->blueBox[3].x = columnFourBetThreeValueTrim.x + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[3].y = columnFourBetThreeValueTrim.y + (blackBoarderSpacing / 2);

	// columnFiveBetFourTrim
	columnFiveBetFourValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnFiveBetFourValueTrim.w = ((mainInsideBoarderTrim.w - blackBoarderSpacing) / 9);
	columnFiveBetFourValueTrim.x = (columnFourBetThreeValueTrim.x + columnFourBetThreeValueTrim.w) + (blackBoarderSpacing / 2);
	columnFiveBetFourValueTrim.y = (mainInsideBoarderTrim.h - columnFiveBetFourValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// blueBox #4
	tableCoordinates->blueBox[4].h = columnFiveBetFourValueTrim.h - blackBoarderSpacing;
	tableCoordinates->blueBox[4].w = columnFiveBetFourValueTrim.w - blackBoarderSpacing;
	tableCoordinates->blueBox[4].x = columnFiveBetFourValueTrim.x + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[4].y = columnFiveBetFourValueTrim.y + (blackBoarderSpacing / 2);

	// columnSixBetFiveTrim
	columnSixBetFiveValueTrim.h = mainInsideBoarderTrim.h - blackBoarderSpacing;
	columnSixBetFiveValueTrim.w = ((columnOneHandDescriptionTextTrim.w / 3) * 2) - (blackBoarderSpacing * 2.5);
	columnSixBetFiveValueTrim.x = (columnFiveBetFourValueTrim.x + columnFiveBetFourValueTrim.w) + (blackBoarderSpacing / 2);
	columnSixBetFiveValueTrim.y = (mainInsideBoarderTrim.h - columnSixBetFiveValueTrim.h) / 2 + mainInsideBoarderTrim.y;

	// blueBox #5
	tableCoordinates->blueBox[5].h = columnSixBetFiveValueTrim.h - blackBoarderSpacing;
	tableCoordinates->blueBox[5].w = columnSixBetFiveValueTrim.w - blackBoarderSpacing;
	tableCoordinates->blueBox[5].x = columnSixBetFiveValueTrim.x + (blackBoarderSpacing / 2);
	tableCoordinates->blueBox[5].y = columnSixBetFiveValueTrim.y + (blackBoarderSpacing / 2);
	

	// render the status table

	// renderMainOutsideBoarderTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->largeBlackBox))
	{
		fprintf(stderr, "Error drawing video poker status table primary outside black box.\n");
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
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[0]))
	{
		fprintf(stderr, "Error drawing video poker status table #0 blue box.\n");
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
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[1]))
	{
		fprintf(stderr, "Error drawing video poker status table #1 blue box.\n");
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
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[2]))
	{
		fprintf(stderr, "Error drawing video poker status table #2 blue box.\n");
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
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[3]))
	{
		fprintf(stderr, "Error drawing video poker status table #3 blue box.\n");
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
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[4]))
	{
		fprintf(stderr, "Error drawing video poker status table #4 blue box.\n");
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
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[5]))
	{
		fprintf(stderr, "Error drawing video poker status table #5 blue box.\n");
		return EXIT_FAILURE;
	}

	// set back to blue color for gameplay.  Unsure if needed.  Good practice
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	// everything was rendered correctly
	return EXIT_SUCCESS;
}

bool vPokerStatusTableTextCalculations(SDL_Renderer *mainRenderer, struct vPokerStatusTableCoordinates *tableCoordinates, enum gametype gameType)
{ 
	switch (gameType)
	{
	case JACKS_OR_BETTER:
		break;
	default:
		fprintf(stderr, "Error: Game type not found.\n");
		return EXIT_FAILURE;
		break;
	}

	return EXIT_SUCCESS;
}

bool vPokerStatusTableRender(SDL_Renderer* mainRenderer, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	struct vPokerStatusTableCoordinates tableCoordinates;

	// perform calculations and apply them to the renderer.  Necessary for all poker games.  gameType not needed.
	if (vPokerStatusTableBoxCalculations(mainRenderer, &tableCoordinates, gameType, gamePokerControlButtonImageData) == EXIT_FAILURE)
		return EXIT_FAILURE;

	// perform calculations and apply them to the renderer for the text in the status table.
	if (vPokerStatusTableTextCalculations(mainRenderer, &tableCoordinates, gameType) == EXIT_FAILURE)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}