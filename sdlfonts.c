// fonts.c:  SDL font functions for VideoPoker by ekg98

#include "common.h"
#include "wccommon.h"


#define SPACING_MULTIPLIER	7	// spacing multiplier for distance between cards.

extern SDL_Renderer *mainWindowRenderer;
extern int intWindowWidth;
extern int intWindowHeight;
extern SDL_Texture *heldTexture;
extern SDL_Rect heldDest[5];

TTF_Font *mainText;

int loadFonts(void)
{
	// pointer to open text file
	mainText = TTF_OpenFont("fonts/OneSlot.ttf", 40);

	if(mainText == NULL)
	{
		fprintf(stderr, "Failed to load font, %s\n", TTF_GetError());
		return 1;
	}

	SDL_Color heldColor = {255, 255, 255};
	SDL_Surface *heldSurface = TTF_RenderText_Solid(mainText, "HELD", heldColor);

	if(heldSurface == NULL)
		return 1;

	heldTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, heldSurface);

	// if was able to create a valid held text.  Then plan logic to place it on the screen
	if(heldTexture == NULL)
		return 1;
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
		for(int i = 0; i < 5; i++)
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

	return 0;
}

// close any open ttf text
void closeText(SDL_Texture **heldTexture, SDL_Texture **gameStatusWinTextTexture, SDL_Texture **gameTypeTextTexture, SDL_Texture **gameOverTextTexture)
{
	TTF_CloseFont(mainText);
	mainText = NULL;

	SDL_DestroyTexture(*heldTexture);
	heldTexture = NULL;

	SDL_DestroyTexture(*gameStatusWinTextTexture);
	gameStatusWinTextTexture = NULL;

	SDL_DestroyTexture(*gameTypeTextTexture);
	gameTypeTextTexture = NULL;

	SDL_DestroyTexture(*gameOverTextTexture);
	gameOverTextTexture = NULL;
}

bool gameStatusWinText(struct card *hand, SDL_Rect *gameStatusWinTextDest, SDL_Texture **gameStatusWinTextTexture)
{
	char *winningString = NULL;
	SDL_Color gameStatusWinTextColor = {255, 255, 255};

	// when finding null return true
	winningString = jacksOrBetterWinCheck(hand);

	// TTF_RenderText_solid cannot accept NULL.  This ends execution of this function if a winning hand was not found.
	if(winningString == NULL)
		return true;

	SDL_Surface *gameStatusWinTextSurface = TTF_RenderText_Solid(mainText, winningString, gameStatusWinTextColor);


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
bool gameTypeText(enum gametype gameName, SDL_Rect *gameTypeTextDest, SDL_Texture **gameTypeTextTexture)
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

	SDL_Surface *gameTypeTextSurface = TTF_RenderText_Solid(mainText, gameTypeTextString, gameTypeTextColor);

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

bool gameOverText(bool gameOver, SDL_Rect *gameOverTextDest, SDL_Texture **gameOverTextTexture)
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

	SDL_Surface *gameOverTextSurface = TTF_RenderText_Solid(mainText, gameOverTextString, gameOverTextColor);

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
