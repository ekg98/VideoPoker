// sdlvpokerstatustable.c:  Source file for graphical status table in video poker

#include "common.h"
#include "sdlbuttons.h"
#include "sdlvpokerstatustable.h"

extern int intWindowWidth;
extern int intWindowHeight;

bool vPokerStatusTableBoxCalculations(SDL_Renderer* mainRenderer, struct commonGameStats *commonGameStats, struct vPokerStatusTableCoordinates *tableCoordinates, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	// The table on the top of the screen is controlled by the spacing of the buttons on the lower control panel.  This gives illusion of squaring off the game.
			
	// black border trim spacing.  This value removes (x) pixels from each side of the box.  Even numbers only.
	const int BLACKBORDERSPACING = 6;


	// calculations for video poker status table

	// sets position of video poker status table in the vertical
	const int mainBorderHeight = intWindowHeight / 2.5;


	// largeBlackBox
	tableCoordinates->largeBlackBox.x = gamePokerControlButtonImageData->pokerControlButtonDest[0].x;
	tableCoordinates->largeBlackBox.y = 10;
	tableCoordinates->largeBlackBox.w = (gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w;
	tableCoordinates->largeBlackBox.h = mainBorderHeight;

	// largeYellowBox
	tableCoordinates->largeYellowBox.h = tableCoordinates->largeBlackBox.h - BLACKBORDERSPACING;
	tableCoordinates->largeYellowBox.w = tableCoordinates->largeBlackBox.w - BLACKBORDERSPACING;
	tableCoordinates->largeYellowBox.x = ((tableCoordinates->largeBlackBox.w - tableCoordinates->largeYellowBox.w) / 2) + tableCoordinates->largeBlackBox.x;
	tableCoordinates->largeYellowBox.y = ((tableCoordinates->largeBlackBox.h - tableCoordinates->largeYellowBox.h) / 2) + tableCoordinates->largeBlackBox.y;

	// blackBox #0
	tableCoordinates->blackBox[0].h = tableCoordinates->largeYellowBox.h - BLACKBORDERSPACING;
	tableCoordinates->blackBox[0].w = ((tableCoordinates->largeYellowBox.w - BLACKBORDERSPACING) / 3);
	tableCoordinates->blackBox[0].x = tableCoordinates->largeYellowBox.x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blackBox[0].y = ((tableCoordinates->largeYellowBox.h - tableCoordinates->blackBox[0].h) / 2) + tableCoordinates->largeYellowBox.y;

	// blueBox #0
	tableCoordinates->blueBox[0].x = tableCoordinates->blackBox[0].x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[0].y = tableCoordinates->blackBox[0].y + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[0].w = tableCoordinates->blackBox[0].w - BLACKBORDERSPACING;
	tableCoordinates->blueBox[0].h = tableCoordinates->blackBox[0].h - BLACKBORDERSPACING;

	// blackBox #1
	tableCoordinates->blackBox[1].h = tableCoordinates->largeYellowBox.h - BLACKBORDERSPACING;
	tableCoordinates->blackBox[1].w = ((tableCoordinates->largeYellowBox.w - BLACKBORDERSPACING) / 9);
	tableCoordinates->blackBox[1].x = (tableCoordinates->blackBox[0].x + tableCoordinates->blackBox[0].w) + (BLACKBORDERSPACING / 2);
	tableCoordinates->blackBox[1].y = ((tableCoordinates->largeYellowBox.h - tableCoordinates->blackBox[1].h) / 2) + tableCoordinates->largeYellowBox.y;

	// blueBox #1
	tableCoordinates->blueBox[1].h = tableCoordinates->blackBox[1].h - BLACKBORDERSPACING;
	tableCoordinates->blueBox[1].w = tableCoordinates->blackBox[1].w - BLACKBORDERSPACING;
	tableCoordinates->blueBox[1].x = tableCoordinates->blackBox[1].x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[1].y = tableCoordinates->blackBox[1].y + (BLACKBORDERSPACING / 2);

	// blackBox #2
	tableCoordinates->blackBox[2].h = tableCoordinates->largeYellowBox.h - BLACKBORDERSPACING;
	tableCoordinates->blackBox[2].w = ((tableCoordinates->largeYellowBox.w - BLACKBORDERSPACING) / 9);
	tableCoordinates->blackBox[2].x = (tableCoordinates->blackBox[1].x + tableCoordinates->blackBox[1].w) + (BLACKBORDERSPACING / 2);
	tableCoordinates->blackBox[2].y = (tableCoordinates->largeYellowBox.h - tableCoordinates->blackBox[2].h) / 2 + tableCoordinates->largeYellowBox.y;

	// blueBox #2
	tableCoordinates->blueBox[2].h = tableCoordinates->blackBox[2].h - BLACKBORDERSPACING;
	tableCoordinates->blueBox[2].w = tableCoordinates->blackBox[2].w - BLACKBORDERSPACING;
	tableCoordinates->blueBox[2].x = tableCoordinates->blackBox[2].x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[2].y = tableCoordinates->blackBox[2].y + (BLACKBORDERSPACING / 2);

	// blackBox #3
	tableCoordinates->blackBox[3].h = tableCoordinates->largeYellowBox.h - BLACKBORDERSPACING;
	tableCoordinates->blackBox[3].w = ((tableCoordinates->largeYellowBox.w - BLACKBORDERSPACING) / 9);
	tableCoordinates->blackBox[3].x = (tableCoordinates->blackBox[2].x + tableCoordinates->blackBox[2].w) + (BLACKBORDERSPACING / 2);
	tableCoordinates->blackBox[3].y = (tableCoordinates->largeYellowBox.h - tableCoordinates->blackBox[3].h) / 2 + tableCoordinates->largeYellowBox.y;

	// blueBox #3
	tableCoordinates->blueBox[3].h = tableCoordinates->blackBox[3].h - BLACKBORDERSPACING;
	tableCoordinates->blueBox[3].w = tableCoordinates->blackBox[3].w - BLACKBORDERSPACING;
	tableCoordinates->blueBox[3].x = tableCoordinates->blackBox[3].x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[3].y = tableCoordinates->blackBox[3].y + (BLACKBORDERSPACING / 2);

	// blackBox #4
	tableCoordinates->blackBox[4].h = tableCoordinates->largeYellowBox.h - BLACKBORDERSPACING;
	tableCoordinates->blackBox[4].w = ((tableCoordinates->largeYellowBox.w - BLACKBORDERSPACING) / 9);
	tableCoordinates->blackBox[4].x = (tableCoordinates->blackBox[3].x + tableCoordinates->blackBox[3].w) + (BLACKBORDERSPACING / 2);
	tableCoordinates->blackBox[4].y = (tableCoordinates->largeYellowBox.h - tableCoordinates->blackBox[4].h) / 2 + tableCoordinates->largeYellowBox.y;

	// blueBox #4
	tableCoordinates->blueBox[4].h = tableCoordinates->blackBox[4].h - BLACKBORDERSPACING;
	tableCoordinates->blueBox[4].w = tableCoordinates->blackBox[4].w - BLACKBORDERSPACING;
	tableCoordinates->blueBox[4].x = tableCoordinates->blackBox[4].x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[4].y = tableCoordinates->blackBox[4].y + (BLACKBORDERSPACING / 2);

	// blackBox #5
	tableCoordinates->blackBox[5].h = tableCoordinates->largeYellowBox.h - BLACKBORDERSPACING;
	tableCoordinates->blackBox[5].w = ((tableCoordinates->blackBox[0].w / 3) * 2) - (BLACKBORDERSPACING * 2.5);
	tableCoordinates->blackBox[5].x = (tableCoordinates->blackBox[4].x + tableCoordinates->blackBox[4].w) + (BLACKBORDERSPACING / 2);
	tableCoordinates->blackBox[5].y = (tableCoordinates->largeYellowBox.h - tableCoordinates->blackBox[5].h) / 2 + tableCoordinates->largeYellowBox.y;

	// blueBox #5
	tableCoordinates->blueBox[5].h = tableCoordinates->blackBox[5].h - BLACKBORDERSPACING;
	tableCoordinates->blueBox[5].w = tableCoordinates->blackBox[5].w - BLACKBORDERSPACING;
	tableCoordinates->blueBox[5].x = tableCoordinates->blackBox[5].x + (BLACKBORDERSPACING / 2);
	tableCoordinates->blueBox[5].y = tableCoordinates->blackBox[5].y + (BLACKBORDERSPACING / 2);
	

	// render the status table

	// renderMainOutsideBoarderTrim
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->largeBlackBox))
	{
		fprintf(stderr, "Error drawing video poker status table primary outside black box.\n");
		return EXIT_FAILURE;
	}

	// render largeYellowBox
	SDL_SetRenderDrawColor(mainRenderer, 255, 255, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->largeYellowBox))
	{
		fprintf(stderr, "Error drawing video poker status table primary inside yellow boarder trim.\n");
		return EXIT_FAILURE;
	}

	// render blackBox #0
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blackBox[0]))
	{
		fprintf(stderr, "Error drawing video poker status table #0 black box.\n");
		return EXIT_FAILURE;
	}

	// render blueBox #0
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[0]))
	{
		fprintf(stderr, "Error drawing video poker status table #0 blue box.\n");
		return EXIT_FAILURE;
	}

	// render blackBox #1
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blackBox[1]))
	{
		fprintf(stderr, "Error drawing video poker status table #1 black box.\n");
		return EXIT_FAILURE;
	}

	// render blueBox #1
	setBoxColor(mainRenderer, commonGameStats, 1);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[1]))
	{
		fprintf(stderr, "Error drawing video poker status table #1 blue box.\n");
		return EXIT_FAILURE;
	}

	// render blackBox #2
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blackBox[2]))
	{
		fprintf(stderr, "Error drawing video poker status table #2 black box.\n");
		return EXIT_FAILURE;
	}

	// render blueBox #2
	setBoxColor(mainRenderer, commonGameStats, 2);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[2]))
	{
		fprintf(stderr, "Error drawing video poker status table #2 blue box.\n");
		return EXIT_FAILURE;
	}

	// render blackBox #3
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blackBox[3]))
	{
		fprintf(stderr, "Error drawing video poker status table #3 black box.\n");
		return EXIT_FAILURE;
	}

	// render blueBox #3
	setBoxColor(mainRenderer, commonGameStats, 3);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[3]))
	{
		fprintf(stderr, "Error drawing video poker status table #3 blue box.\n");
		return EXIT_FAILURE;
	}

	// render blackBox #4
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blackBox[4]))
	{
		fprintf(stderr, "Error drawing video poker status table #4 black box.\n");
		return EXIT_FAILURE;
	}

	// render blueBox #4
	setBoxColor(mainRenderer, commonGameStats, 4);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blueBox[4]))
	{
		fprintf(stderr, "Error drawing video poker status table #4 blue box.\n");
		return EXIT_FAILURE;
	}
	// render blackBox #5
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
	if (SDL_RenderFillRect(mainRenderer, &tableCoordinates->blackBox[5]))
	{
		fprintf(stderr, "Error drawing video poker status table #5 black box.\n");
		return EXIT_FAILURE;
	}

	// render blueBox #5
	setBoxColor(mainRenderer, commonGameStats, 5);
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

bool vPokerStatusTableRender(SDL_Renderer* mainRenderer, struct commonGameStats *commonGameStats, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	struct vPokerStatusTableCoordinates tableCoordinates;
		
	// perform calculations and apply them to the renderer.  Necessary for all poker games.  gameType not needed.
	if (vPokerStatusTableBoxCalculations(mainRenderer, commonGameStats, &tableCoordinates, gameType, gamePokerControlButtonImageData) == EXIT_FAILURE)
		return EXIT_FAILURE;

	// perform calculations and apply them to the renderer for the text in the status table.
	if (vPokerStatusTableTextCalculations(mainRenderer, &tableCoordinates, gameType) == EXIT_FAILURE)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

void setBoxColor(SDL_Renderer *mainRenderer ,struct commonGameStats *commonGameStats, int intBox)
{
	if (commonGameStats->currentBetLevel == intBox)
		SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 0);
	else
		SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 0);

	return;
}