// fonts.c:  SDL font functions for VideoPoker by ekg98

#include "common.h"
#include "cards.h"
#include "wccommon.h"
#include "sdlfonts.h"


#define SPACING_MULTIPLIER	7	// spacing multiplier for distance between cards.

extern SDL_Renderer *mainWindowRenderer;
extern int intWindowWidth;
extern int intWindowHeight;
extern SDL_Texture *heldTexture;
extern SDL_Rect heldDest[5];

int loadFonts(struct fonts *gameFonts)
{
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

	return 0;
}

// close any open ttf text
void closeText(struct fonts *gameFonts, SDL_Texture **heldTexture, SDL_Texture **gameStatusWinTextTexture, SDL_Texture **gameTypeTextTexture, SDL_Texture **gameOverTextTexture)
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

	SDL_DestroyTexture(*heldTexture);
	heldTexture = NULL;

	SDL_DestroyTexture(*gameStatusWinTextTexture);
	gameStatusWinTextTexture = NULL;

	SDL_DestroyTexture(*gameTypeTextTexture);
	gameTypeTextTexture = NULL;

	SDL_DestroyTexture(*gameOverTextTexture);
	gameOverTextTexture = NULL;
}

bool gameStatusWinText(struct card *hand, SDL_Rect *gameStatusWinTextDest, SDL_Texture **gameStatusWinTextTexture, TTF_Font **gameStatusWinFont)
{
	char *winningString = NULL;
	SDL_Color gameStatusWinTextColor = {255, 255, 255};

	// when finding null return true
	winningString = jacksOrBetterWinCheck(hand);

	// TTF_RenderText_solid cannot accept NULL.  This ends execution of this function if a winning hand was not found.
	if(winningString == NULL)
		return true;

	SDL_Surface *gameStatusWinTextSurface = TTF_RenderText_Solid(*gameStatusWinFont, winningString, gameStatusWinTextColor);


	if(gameStatusWinTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameStatusWinTextTexture.\n");
		return true;
	}

	*gameStatusWinTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameStatusWinTextSurface);

	if(gameStatusWinTextTexture == NULL)
		return true;

	float gameStatusWinTextWidth = gameStatusWinTextSurface->w;
	float gameStatusWinTextHeight = gameStatusWinTextSurface->h;

	float correctedGameStatusWinTextHeight = 0.0;
	float correctedGameStatusWinTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameStatusWinTextWidth = (intWindowWidth / 1920.0) * gameStatusWinTextWidth;
	correctedGameStatusWinTextHeight = (intWindowHeight / 1200.0) * gameStatusWinTextHeight;

	gameStatusWinTextDest->h = correctedGameStatusWinTextHeight;
	gameStatusWinTextDest->w = correctedGameStatusWinTextWidth;

	gameStatusWinTextDest->y = intWindowHeight / 2.4;
	gameStatusWinTextDest->x = (intWindowWidth / 2) - (correctedGameStatusWinTextWidth / 2);

	jacksOrBetterWinCheckFree(winningString);
	SDL_FreeSurface(gameStatusWinTextSurface);

	return false;
}

//gameTypeText: Function is responsible for displaying the text in the lower left corner of screen for type of game being played
bool gameTypeText(enum gametype gameName, SDL_Rect *gameTypeTextDest, SDL_Texture **gameTypeTextTexture, TTF_Font **gameTypeFont)
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

	SDL_Surface *gameTypeTextSurface = TTF_RenderText_Solid(*gameTypeFont, gameTypeTextString, gameTypeTextColor);

	if(gameTypeTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameTypeTextSurface.\n");
		return true;
	}

	*gameTypeTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameTypeTextSurface);

	if(gameTypeTextTexture == NULL)
		return true;

	float gameTypeTextWidth = gameTypeTextSurface->w;
	float gameTypeTextHeight = gameTypeTextSurface->h;

	float correctedGameTypeTextHeight = 0.0;
	float correctedGameTypeTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameTypeTextWidth = (intWindowWidth / 1920.0) * gameTypeTextWidth;
	correctedGameTypeTextHeight = (intWindowHeight / 1200.0) * gameTypeTextHeight;

	gameTypeTextDest->h = correctedGameTypeTextHeight;
	gameTypeTextDest->w = correctedGameTypeTextWidth;

	gameTypeTextDest->y = intWindowHeight - correctedGameTypeTextHeight;
	gameTypeTextDest->x = 0;

	SDL_FreeSurface(gameTypeTextSurface);
	free(gameTypeTextString);

	return false;
}

// gameOverText:  Generates textures and locations for game over text.
bool gameOverText(bool gameOver, SDL_Rect *gameOverTextDest, SDL_Texture **gameOverTextTexture, TTF_Font **gameOverFont)
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

	SDL_Surface *gameOverTextSurface = TTF_RenderText_Solid(*gameOverFont, gameOverTextString, gameOverTextColor);

	if(gameOverTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameOverTextSurface.\n");
		return true;
	}

	*gameOverTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameOverTextSurface);

	if(gameOverTextTexture == NULL)
		return true;

	float gameOverTextWidth = gameOverTextSurface->w;
	float gameOverTextHeight = gameOverTextSurface->h;

	float correctedGameOverTextHeight = 0.0;
	float correctedGameOverTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameOverTextWidth = (intWindowWidth / 1920.0) * gameOverTextWidth;
	correctedGameOverTextHeight = (intWindowHeight / 1200.0) * gameOverTextHeight;

	gameOverTextDest->h = correctedGameOverTextHeight;
	gameOverTextDest->w = correctedGameOverTextWidth;

	gameOverTextDest->y = intWindowHeight - correctedGameOverTextHeight;
	gameOverTextDest->x = intWindowWidth / 1.8;

	SDL_FreeSurface(gameOverTextSurface);
	free(gameOverTextString);

	return false;
}

// gameFpsText: Generates textures and locations for game fps text.
bool gameFpsText(int fps, SDL_Rect* gameFpsTextDest, SDL_Texture** gameFpsTextTexture, TTF_Font **gameFpsFont)
{
	SDL_Color gameFpsTextColor = { 255, 255, 255 };

	char gameFpsTextString[9];

	// limit string size to 3 digits.
	if (fps > 1000)
		fps = 999;
	
	// create string based off of fps.
	sprintf(gameFpsTextString, "FPS: %d", fps);
	
	SDL_Surface* gameFpsTextSurface = TTF_RenderText_Solid(*gameFpsFont, gameFpsTextString, gameFpsTextColor);

	if (gameFpsTextSurface == NULL)
	{
		fprintf(stderr, "Could not render gameFpsTextSurface.\n");
		return true;
	}

	*gameFpsTextTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameFpsTextSurface);

	if (gameFpsTextTexture == NULL)
		return true;

	float gameFpsTextWidth = gameFpsTextSurface->w;
	float gameFpsTextHeight = gameFpsTextSurface->h;

	float correctedGameFpsTextHeight = 0.0;
	float correctedGameFpsTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameFpsTextWidth = (intWindowWidth / 1920.0) * gameFpsTextWidth;
	correctedGameFpsTextHeight = (intWindowHeight / 1200.0) * gameFpsTextHeight;

	gameFpsTextDest->h = correctedGameFpsTextHeight;
	gameFpsTextDest->w = correctedGameFpsTextWidth;

	gameFpsTextDest->y = intWindowHeight - correctedGameFpsTextHeight;
	gameFpsTextDest->x = intWindowWidth / 2.6;

	SDL_FreeSurface(gameFpsTextSurface);

	return false;
}

// gameHeldText:  Generates textures and calculations for ganme held text.
bool gameHeldText(SDL_Rect heldDest[] ,SDL_Texture **heldTexture, TTF_Font **heldFont)
{
	SDL_Color heldColor = { 255, 255, 255 };
	SDL_Surface* heldSurface = TTF_RenderText_Solid(*heldFont, "HELD", heldColor);

	if (heldSurface == NULL)
		return true;

	*heldTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, heldSurface);

	// if was able to create a valid held text.  Then plan logic to place it on the screen
	if (*heldTexture == NULL)
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
			heldDest[i].w = correctedHeldTextWidth;
			heldDest[i].h = correctedHeldTextHeight;
			heldDest[i].y = intWindowHeight / 2.2;
		}

		// Aligns the held text X.  Horzontal across the screen directly over the cards.
		heldDest[0].x = ((intWindowWidth / 2) - heldTextHalf) - (spacingDistance * 2);
		heldDest[1].x = ((intWindowWidth / 2) - heldTextHalf) - (spacingDistance * 1);
		heldDest[2].x = (intWindowWidth / 2) - heldTextHalf;
		heldDest[3].x = ((intWindowWidth / 2) - heldTextHalf) + (spacingDistance * 1);
		heldDest[4].x = ((intWindowWidth / 2) - heldTextHalf) + (spacingDistance * 2);

	}

	SDL_FreeSurface(heldSurface);

	return false;
}

