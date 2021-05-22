// sdlvpokerstatustable.c:  Source file for graphical status table in video poker

#include "common.h"
#include "sdlbuttons.h"
#include "sdlvpokerstatustable.h"
#include "payouttables.h"
#include "sdlfonts.h"

extern int intWindowWidth;
extern int intWindowHeight;

bool vPokerStatusTableBoxCalculations(SDL_Renderer* mainRenderer, struct commonGameStats *commonGameStats, struct vPokerStatusTableCoordinates *tableCoordinates, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	// The table on the top of the screen is controlled by the spacing of the buttons on the lower control panel.  This gives illusion of squaring off the game.
			
	// black border trim spacing.  This value removes (x) pixels from each side of the box.  Even numbers only.
	const int BLACKBORDERSPACING = 6;


	// calculations for video poker status table
		
	// largeBlackBox - height of black box is windowHeight / 2.5.  This makes largeBlackBox 43.2% of the screen height. Location from top of screen is set at .05% from top.
	tableCoordinates->largeBlackBox.x = gamePokerControlButtonImageData->pokerControlButtonDest[0].x;
	tableCoordinates->largeBlackBox.y = round(commonGameStats->windowHeight * .005);
	tableCoordinates->largeBlackBox.w = (gamePokerControlButtonImageData->pokerControlButtonDest[5].x - gamePokerControlButtonImageData->pokerControlButtonDest[0].x) + gamePokerControlButtonImageData->pokerControlButtonDest[0].w;
	tableCoordinates->largeBlackBox.h = round(commonGameStats->windowHeight / 2.5);
	
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

bool vPokerStatusTableTextCalculations(SDL_Renderer *mainRenderer, struct vPokerStatusTableCoordinates *tableCoordinates, struct fonts *gameFonts, enum gametype gameType)
{ 
	int intCounterColumn, intCounterRow;
	int correctedTextWidth[6][10], correctedTextHeight[6][10];

	// adjust for resolution height and width
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].h = (intWindowWidth / 1920.0) * gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].h;
			gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].w = (intWindowHeight / 1200.0) * gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].w;
		}
	}

	switch (gameType)
	{
	case JACKS_OR_BETTER:
		// set X
		for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
		{
			for (intCounterRow = 0; intCounterRow < 9; intCounterRow++)
			{
				gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].x = tableCoordinates->blueBox[intCounterColumn].x;
				gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].y = (tableCoordinates->blueBox[intCounterColumn].y + (intCounterRow * gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].h));
			}
		}


		break;
	default:
		fprintf(stderr, "Error: Unknown game type.\n");
		return EXIT_FAILURE;
		break;
	}

	return EXIT_SUCCESS;
}

bool vPokerStatusTableRender(SDL_Renderer* mainRenderer, struct commonGameStats *commonGameStats, struct fonts *gameFonts, struct text *gameText, enum gametype gameType, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData)
{
	int intCounterColumn, intCounterRow;
	struct vPokerStatusTableCoordinates tableCoordinates;
		
	// perform calculations and apply them to the renderer.  Necessary for all poker games.  gameType not needed.
	if (vPokerStatusTableBoxCalculations(mainRenderer, commonGameStats, &tableCoordinates, gameType, gamePokerControlButtonImageData) == EXIT_FAILURE)
		return EXIT_FAILURE;
	
	// load the fonts into memory only once
	if (gameFonts->vPokerStatusTableFontLoaded == false)
	{
		if (loadvPokerStatusTableFonts(gameFonts, gameType) == EXIT_SUCCESS)
			gameFonts->vPokerStatusTableFontLoaded = true;
		else
			return EXIT_FAILURE;
	}
	
	// load strings into memory
	if (gameText->vPokerStatusTableStringsLoaded == false)
	{
		if (loadvPokerStatusTableStrings(gameText, gameType) == EXIT_SUCCESS)
			gameText->vPokerStatusTableStringsLoaded = true;
		else
			return EXIT_FAILURE;
	}
		
	// create surfaces and textures
	if (loadvPokerStatusTableTextures(mainRenderer, gameFonts, gameText, gameType) == EXIT_FAILURE)
		return EXIT_FAILURE;
	
	// perform calculations for the text in the status table.
	if (vPokerStatusTableTextCalculations(mainRenderer, &tableCoordinates, gameFonts, gameType) == EXIT_FAILURE)
		return EXIT_FAILURE;

	// render textures to vPokerStatusTable
	switch (gameType)
	{
	case JACKS_OR_BETTER:
		for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
		{
			for (intCounterRow = 0; intCounterRow < 9; intCounterRow++)
				SDL_RenderCopy(mainRenderer, gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow], NULL, &gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow]);
		}
		break;
	case DUCES_WILD:
		for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
		{
			for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
				SDL_RenderCopy(mainRenderer, gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow], NULL, &gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow]);
		}
		break;
	default:
		fprintf(stderr, "Error: Unknown game type.\n");
		return EXIT_FAILURE;
		break;
	}

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

bool loadvPokerStatusTableFonts(struct fonts *gameFonts, enum gametype gameType)
{
	// need to edit this funciton.  Doesn't matter what game is requested font size is not changed here.

	gameFonts->vPokerStatusTableFont = NULL;
		
	switch (gameType)
	{
	case JACKS_OR_BETTER:
		gameFonts->vPokerStatusTableFont = TTF_OpenFont("fonts/OneSlot.ttf", 40);

		if (gameFonts->vPokerStatusTableFont == NULL)
		{
			fprintf(stderr, "Failed to load vPokerStatusTableFont, %s\n", TTF_GetError());
			return EXIT_FAILURE;
		}

		break;
	default:
		fprintf(stderr, "Error:  unknown game type for status table.\n");
		return EXIT_FAILURE;
		break;
	}

	return EXIT_SUCCESS;
}

bool unloadvPokerStatusTableFonts(struct fonts *gameFonts)
{
	if (gameFonts->vPokerStatusTableFont == NULL)
	{
		fprintf(stderr, "Error:  Cannot unload vPokerStatusTableFont.\n");
		return EXIT_FAILURE;
	}
	else
	{
		TTF_CloseFont(gameFonts->vPokerStatusTableFont);
		gameFonts->vPokerStatusTableFont = NULL;
	}

	return EXIT_SUCCESS;
}

bool loadvPokerStatusTableTextures(SDL_Renderer *mainRenderer, struct fonts *gameFonts, struct text *gameText, enum gametype gametype)
{
	
	SDL_Color vPokerStatusTableTextYellow = { 255,255,0 };
	SDL_Color vPokerStatusTableTextWhite = { 255,255,255 };

	SDL_Surface* vPokerStatusTableSurface[6][10];

	int intCounterColumn = 0, intCounterRow = 0;
	
	//
	// get strings for surfaces from gameText structure
	//
	
	// null surfaces.
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
			vPokerStatusTableSurface[intCounterColumn][intCounterRow] = NULL;
	}

	// make them all white.  Need to change this so it reflects winner for each hand.
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
			gameFonts->vPokerStatusTableTextColor[intCounterColumn][intCounterRow] = vPokerStatusTableTextWhite;
	}

	// create surfaces from strings
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			if (gameText->vPokerStatusTableString[intCounterColumn][intCounterRow] == NULL)
				vPokerStatusTableSurface[intCounterColumn][intCounterRow] = TTF_RenderText_Solid(gameFonts->vPokerStatusTableFont, "NULL", gameFonts->vPokerStatusTableTextColor[intCounterColumn][intCounterRow]);
			else
				vPokerStatusTableSurface[intCounterColumn][intCounterRow] = TTF_RenderText_Solid(gameFonts->vPokerStatusTableFont, gameText->vPokerStatusTableString[intCounterColumn][intCounterRow], gameFonts->vPokerStatusTableTextColor[intCounterColumn][intCounterRow]);
		}
	}
	
	// check surfaces for null.  If null exit.
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
			if (vPokerStatusTableSurface[intCounterColumn][intCounterRow] == NULL)
				return EXIT_FAILURE;
	}

	// check textures for null.  If not null destroy.
	for ( intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for ( intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			if (gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow] != NULL)
			{
				SDL_DestroyTexture(gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow]);
				gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow] = NULL;
			}
		}
	}

	// create textures from surfaces
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			if (vPokerStatusTableSurface[intCounterColumn][intCounterRow] == NULL)
			{
				fprintf(stderr, "Error:  vPokerStatusTableSurface did not load properly.\n");
				return EXIT_FAILURE;
			}

			gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow] = SDL_CreateTextureFromSurface(mainRenderer, vPokerStatusTableSurface[intCounterColumn][intCounterRow]);

			if (gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow] == NULL)
			{
				fprintf(stderr, "Error:  vPokerStatusTableTexture did not load properly.\n");
				return EXIT_FAILURE;
			}
		}
	}

	// grab height and width coordinates for sdl rect on screen.
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].h = vPokerStatusTableSurface[intCounterColumn][intCounterRow]->h;
			gameFonts->vPokerStatusTableText[intCounterColumn][intCounterRow].w = vPokerStatusTableSurface[intCounterColumn][intCounterRow]->w;
		}
	}

	// free surfaces
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			SDL_FreeSurface(vPokerStatusTableSurface[intCounterColumn][intCounterRow]);
			vPokerStatusTableSurface[intCounterColumn][intCounterRow] = NULL;
		}
	}

	return EXIT_SUCCESS;
}

bool unloadvPokerStatusTableTextures(struct fonts *gameFonts)
{
	for (int intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (int intCounterRow = 0; intCounterRow < 10; intCounterRow++)
		{
			SDL_DestroyTexture(gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow]);
			gameFonts->vPokerStatusTableTexture[intCounterColumn][intCounterRow] = NULL;
		}
	}

	return EXIT_SUCCESS;
}

bool loadvPokerStatusTableStrings(struct text *gameText, enum gametype gameType)
{
	struct payoutTables* payoutTables;
	payoutTables = getPayoutTables();

	int intCounterColumn = 0, intCounterRow = 0;

	// null array in gameText
	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
			gameText->vPokerStatusTableString[intCounterColumn][intCounterRow] = NULL;	
	}

	//
	//  Populate gameText array here
	//

	gameText->vPokerStatusTableStringsLoaded = true;

	return EXIT_SUCCESS;
}

bool unloadvPokerStatusTableStrings(struct text* gameText, enum gametype gameType)
{
	int intCounterColumn = 0, intCounterRow = 0;

	for (intCounterColumn = 0; intCounterColumn < 6; intCounterColumn++)
	{
		for (intCounterRow = 0; intCounterRow < 10; intCounterRow++)
			if(gameText->vPokerStatusTableString[intCounterColumn][intCounterRow] != NULL)
				free(gameText->vPokerStatusTableString[intCounterColumn][intCounterRow]);
	}

	gameText->vPokerStatusTableStringsLoaded = false;

	return EXIT_SUCCESS;
}