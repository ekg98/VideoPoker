// fonts.c:  SDL font functions for VideoPoker by ekg98

#include "common.h"
#include "cards.h"
#include "wccommon.h"
#include "sdlfonts.h"


#define SPACING_MULTIPLIER	7	// spacing multiplier for distance between cards.

extern SDL_Renderer *mainWindowRenderer;
extern int intWindowWidth;
extern int intWindowHeight;

int loadFonts(struct fonts *gameFonts)
{
	// nulling fonts
	gameFonts->heldFont = NULL;
	gameFonts->gameStatusWinFont = NULL;
	gameFonts->gameTypeFont = NULL;
	gameFonts->gameOverFont = NULL;
	gameFonts->gameFpsFont = NULL;

	// pointer to open holdFont
	gameFonts->heldFont = TTF_OpenFont("fonts/OneSlot.ttf", 40);

	if(gameFonts->heldFont == NULL)
	{
		fprintf(stderr, "Failed to load font, %s\n", TTF_GetError());
		return 1;
	}

	gameFonts->gameStatusWinFont = TTF_OpenFont("fonts/OneSlot.ttf", 40);

	if (gameFonts->gameStatusWinFont == NULL)
	{
		fprintf(stderr, "Failed to load font, %s\n", TTF_GetError());
		return 1;
	}

	gameFonts->gameTypeFont = TTF_OpenFont("fonts/OneSlot.ttf", 40);

	if (gameFonts->gameTypeFont == NULL)
	{
		fprintf(stderr, "Failed to load font, %s\n", TTF_GetError());
		return 1;
	}

	gameFonts->gameOverFont = TTF_OpenFont("fonts/OneSlot.ttf", 40);

	if (gameFonts->gameOverFont == NULL)
	{
		fprintf(stderr, "Failed to load font, %s\n", TTF_GetError());
		return 1;
	}

	gameFonts->gameFpsFont = TTF_OpenFont("fonts/OneSlot.ttf", 32);

	if (gameFonts->gameFpsFont == NULL)
	{
		fprintf(stderr, "Failed to load font, %s\n", TTF_GetError());
		return 1;
	}

	// nulling textures
	gameFonts->heldTexture = NULL;
	gameFonts->gameStatusWinTextTexture = NULL;
	gameFonts->gameTypeTextTexture = NULL;
	gameFonts->gameOverTextTexture = NULL;
	gameFonts->gameFpsTextTexture = NULL;

	return 0;
}

// closeText:  close any open ttf texts
void closeText(struct fonts *gameFonts)
{
	TTF_CloseFont(gameFonts->heldFont);
	gameFonts->heldFont = NULL;

	TTF_CloseFont(gameFonts->gameStatusWinFont);
	gameFonts->gameStatusWinFont = NULL;

	TTF_CloseFont(gameFonts->gameOverFont);
	gameFonts->gameOverFont = NULL;

	TTF_CloseFont(gameFonts->gameTypeFont);
	gameFonts->gameTypeFont = NULL;

	TTF_CloseFont(gameFonts->gameFpsFont);
	gameFonts->gameFpsFont = NULL;

	SDL_DestroyTexture(gameFonts->heldTexture);
	gameFonts->heldTexture = NULL;

	SDL_DestroyTexture(gameFonts->gameStatusWinTextTexture);
	gameFonts->gameStatusWinTextTexture = NULL;

	SDL_DestroyTexture(gameFonts->gameTypeTextTexture);
	gameFonts->gameTypeTextTexture = NULL;

	SDL_DestroyTexture(gameFonts->gameOverTextTexture);
	gameFonts->gameOverTextTexture = NULL;

	SDL_DestroyTexture(gameFonts->gameFpsTextTexture);
	gameFonts->gameFpsTextTexture = NULL;
}

bool gameStatusWinText(struct card *hand, struct fonts *gameFonts)
{
	char *winningString = NULL;
	SDL_Color gameStatusWinTextColor = {255, 255, 255};

	// when finding null return true
	winningString = jacksOrBetterWinCheck(hand);

	// TTF_RenderText_solid cannot accept NULL.  This ends execution of this function if a winning hand was not found.
	if(winningString == NULL)
		return true;

	SDL_Surface *gameStatusWinTextSurface = TTF_RenderText_Solid(gameFonts->gameStatusWinFont, winningString, gameStatusWinTextColor);


	if(gameStatusWinTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameStatusWinTextTexture.\n");
		return true;
	}

	// destroy old texture from previous run
	if (gameFonts->gameStatusWinTextTexture != NULL)
	{
		SDL_DestroyTexture(gameFonts->gameStatusWinTextTexture);
		gameFonts->gameStatusWinTextTexture = NULL;
	}

	gameFonts->gameStatusWinTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameStatusWinTextSurface);

	if(gameFonts->gameStatusWinTextTexture == NULL)
		return true;

	float gameStatusWinTextWidth = gameStatusWinTextSurface->w;
	float gameStatusWinTextHeight = gameStatusWinTextSurface->h;

	float correctedGameStatusWinTextHeight = 0.0;
	float correctedGameStatusWinTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameStatusWinTextWidth = (intWindowWidth / 1920.0) * gameStatusWinTextWidth;
	correctedGameStatusWinTextHeight = (intWindowHeight / 1200.0) * gameStatusWinTextHeight;

	gameFonts->gameStatusWinTextDest.h = correctedGameStatusWinTextHeight;
	gameFonts->gameStatusWinTextDest.w = correctedGameStatusWinTextWidth;

	gameFonts->gameStatusWinTextDest.y = intWindowHeight / 2.4;
	gameFonts->gameStatusWinTextDest.x = (intWindowWidth / 2) - (correctedGameStatusWinTextWidth / 2);

	jacksOrBetterWinCheckFree(winningString);
	SDL_FreeSurface(gameStatusWinTextSurface);

	return false;
}

//gameTypeText: Function is responsible for displaying the text in the lower left corner of screen for type of game being played
bool gameTypeText(enum gametype gameName, struct fonts *gameFonts)
{
	char *gameTypeTextString = NULL;

	SDL_Color gameTypeTextColor = {255, 255, 255};

	switch(gameName)
	{
		case JACKS_OR_BETTER:
			gameTypeTextString = (char *) malloc(sizeof("JACKS OR BETTER"));

			if(gameTypeTextString == NULL)
				return true;
			else
				strcpy(gameTypeTextString, "JACKS OR BETTER");
			break;
		case DUCES_WILD:
			gameTypeTextString = (char *) malloc(sizeof("DUCES WILD"));

			if(gameTypeTextString == NULL)
				return true;
			else
				strcpy(gameTypeTextString, "DUCES WILD");
			break;
	}

	SDL_Surface *gameTypeTextSurface = TTF_RenderText_Solid(gameFonts->gameTypeFont, gameTypeTextString, gameTypeTextColor);

	if(gameTypeTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameTypeTextSurface.\n");
		return true;
	}

	// destroy old texture from previous run
	if (gameFonts->gameTypeTextTexture != NULL)
	{
		SDL_DestroyTexture(gameFonts->gameTypeTextTexture);
		gameFonts->gameTypeTextTexture = NULL;
	}

	gameFonts->gameTypeTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameTypeTextSurface);

	if(gameFonts->gameTypeTextTexture == NULL)
		return true;

	float gameTypeTextWidth = gameTypeTextSurface->w;
	float gameTypeTextHeight = gameTypeTextSurface->h;

	float correctedGameTypeTextHeight = 0.0;
	float correctedGameTypeTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameTypeTextWidth = (intWindowWidth / 1920.0) * gameTypeTextWidth;
	correctedGameTypeTextHeight = (intWindowHeight / 1200.0) * gameTypeTextHeight;

	gameFonts->gameTypeTextDest.h = correctedGameTypeTextHeight;
	gameFonts->gameTypeTextDest.w = correctedGameTypeTextWidth;

	gameFonts->gameTypeTextDest.y = intWindowHeight - correctedGameTypeTextHeight;
	gameFonts->gameTypeTextDest.x = 0;

	SDL_FreeSurface(gameTypeTextSurface);
	free(gameTypeTextString);

	return false;
}

// gameOverText:  Generates textures and locations for game over text.
bool gameOverText(bool gameOver, struct fonts *gameFonts)
{
	char *gameOverTextString = NULL;

	SDL_Color gameOverTextColor = {255, 255, 255};

	switch(gameOver)
	{
		case true:
			gameOverTextString = (char *) malloc(sizeof("GAME OVER"));

			if(gameOverTextString == NULL)
				return true;
			else
				strcpy(gameOverTextString, "GAME OVER");
			break;
		case false:
			return true;
			break;
	}

	SDL_Surface *gameOverTextSurface = TTF_RenderText_Solid(gameFonts->gameOverFont, gameOverTextString, gameOverTextColor);

	if(gameOverTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameOverTextSurface.\n");
		return true;
	}

	// destroy old texture from previous run
	if (gameFonts->gameOverTextTexture != NULL)
	{
		SDL_DestroyTexture(gameFonts->gameOverTextTexture);
		gameFonts->gameOverTextTexture = NULL;
	}

	gameFonts->gameOverTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameOverTextSurface);

	if(gameFonts->gameOverTextTexture == NULL)
		return true;

	float gameOverTextWidth = gameOverTextSurface->w;
	float gameOverTextHeight = gameOverTextSurface->h;

	float correctedGameOverTextHeight = 0.0;
	float correctedGameOverTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameOverTextWidth = (intWindowWidth / 1920.0) * gameOverTextWidth;
	correctedGameOverTextHeight = (intWindowHeight / 1200.0) * gameOverTextHeight;

	gameFonts->gameOverTextDest.h = correctedGameOverTextHeight;
	gameFonts->gameOverTextDest.w = correctedGameOverTextWidth;

	gameFonts->gameOverTextDest.y = intWindowHeight - correctedGameOverTextHeight;
	gameFonts->gameOverTextDest.x = intWindowWidth / 1.8;

	SDL_FreeSurface(gameOverTextSurface);
	free(gameOverTextString);

	return false;
}

// gameFpsText: Generates textures and locations for game fps text.
bool gameFpsText(int fps, struct fonts *gameFonts)
{
	SDL_Color gameFpsTextColor = { 255, 255, 255 };

	char gameFpsTextString[9];

	// limit string size to 3 digits.
	if (fps > 1000)
		fps = 999;
	
	// create string based off of fps.
	sprintf(gameFpsTextString, "FPS: %d", fps);
	
	SDL_Surface* gameFpsTextSurface = TTF_RenderText_Solid(gameFonts->gameFpsFont, gameFpsTextString, gameFpsTextColor);

	if (gameFpsTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameFpsTextSurface.\n");
		return true;
	}

	gameFonts->gameFpsTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameFpsTextSurface);

	if (gameFonts->gameFpsTextTexture == NULL)
		return true;

	float gameFpsTextWidth = gameFpsTextSurface->w;
	float gameFpsTextHeight = gameFpsTextSurface->h;

	float correctedGameFpsTextHeight = 0.0;
	float correctedGameFpsTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameFpsTextWidth = (intWindowWidth / 1920.0) * gameFpsTextWidth;
	correctedGameFpsTextHeight = (intWindowHeight / 1200.0) * gameFpsTextHeight;

	gameFonts->gameFpsTextDest.h = correctedGameFpsTextHeight;
	gameFonts->gameFpsTextDest.w = correctedGameFpsTextWidth;

	gameFonts->gameFpsTextDest.y = intWindowHeight - correctedGameFpsTextHeight;
	gameFonts->gameFpsTextDest.x = intWindowWidth / 2.6;

	SDL_FreeSurface(gameFpsTextSurface);

	return false;
}

// gameHeldText:  Generates textures and calculations for ganme held text.
bool gameHeldText(struct fonts *gameFonts)
{
	SDL_Color heldColor = { 255, 255, 255 };
	SDL_Surface* heldSurface = TTF_RenderText_Solid(gameFonts->heldFont, "HELD", heldColor);

	if (heldSurface == NULL)
		return true;

	gameFonts->heldTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, heldSurface);

	// if was able to create a valid held text.  Then plan logic to place it on the screen
	if (gameFonts->heldTexture == NULL)
		return true;
	else
	{
		float heldTextWidth = heldSurface->w;
		float heldTextHeight = heldSurface->h;

		float correctedHeldTextWidth = 0.0;
		float correctedHeldTextHeight = 0.0;
		float heldTextHalf = 0.0;
		float spacingDistance = 0.0;

		// corrects initial size for the screen resolution being used
		correctedHeldTextWidth = (intWindowWidth / 1920.0) * heldTextWidth;
		correctedHeldTextHeight = (intWindowHeight / 1200.0) * heldTextHeight;

		// calculations for spacing
		heldTextHalf = correctedHeldTextWidth / 2;
		spacingDistance = intWindowWidth / SPACING_MULTIPLIER;

		// assigns text size per calulations on resoluletion.  Alignm text just above the cards in the vertical.
		for (int i = 0; i < 5; i++)
		{
			gameFonts->heldDest[i].w = correctedHeldTextWidth;
			gameFonts->heldDest[i].h = correctedHeldTextHeight;
			gameFonts->heldDest[i].y = intWindowHeight / 2.2;
		}

		// Aligns the held text X.  Horzontal across the screen directly over the cards.
		gameFonts->heldDest[0].x = ((intWindowWidth / 2) - heldTextHalf) - (spacingDistance * 2);
		gameFonts->heldDest[1].x = ((intWindowWidth / 2) - heldTextHalf) - (spacingDistance * 1);
		gameFonts->heldDest[2].x = (intWindowWidth / 2) - heldTextHalf;
		gameFonts->heldDest[3].x = ((intWindowWidth / 2) - heldTextHalf) + (spacingDistance * 1);
		gameFonts->heldDest[4].x = ((intWindowWidth / 2) - heldTextHalf) + (spacingDistance * 2);

	}

	SDL_FreeSurface(heldSurface);

	return false;
}

