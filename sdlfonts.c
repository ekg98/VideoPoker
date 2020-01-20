// fonts.c:  SDL font functions for VideoPoker by ekg98

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "cards.h"
#include "wccommon.h"


#define SPACING_MULTIPLIER	7	// spacing multiplier for distance between cards.

extern SDL_Renderer *mainWindowRenderer;
extern int intWindowWidth;
extern int intWindowHeight;
extern SDL_Texture *heldTexture;
extern SDL_Texture *gameStatusTexture;
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
void closeText(void)
{
	TTF_CloseFont(mainText);
	mainText = NULL;

	SDL_DestroyTexture(heldTexture);
	SDL_DestroyTexture(gameStatusTexture);
}

bool gameStatus(struct card *hand, SDL_Rect *gameStatusDest)
{
	char *winningString = NULL;
	SDL_Color gameStatusColor = {255, 255, 255};
	SDL_Surface *gameStatusSurface = TTF_RenderText_Solid(mainText, (winningString = jacksOrBetterWinCheck(hand)), gameStatusColor);

	if(gameStatusSurface == NULL)
	{
		fprintf(stderr, "Could not render gameStatusTexture.");
		return true;
	}

	gameStatusTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, gameStatusSurface);

	float gameStatusTextWidth = gameStatusSurface->w;
	float gameStatusTextHeight = gameStatusSurface->h;

	float correctedGameStatusTextHeight = 0.0;
	float correctedGameStatusTextWidth = 0.0;

	// corrects initial size for the screen resolution being used
	correctedGameStatusTextWidth = (intWindowWidth / 1920.0) * gameStatusTextWidth;
	correctedGameStatusTextHeight = (intWindowHeight / 1200.0) * gameStatusTextHeight;

	gameStatusDest->h = correctedGameStatusTextHeight;
	gameStatusDest->w = correctedGameStatusTextWidth;

	gameStatusDest->y = intWindowHeight / 2.4;
	gameStatusDest->x = (intWindowWidth / 2) - (correctedGameStatusTextWidth / 2);

	jacksOrBetterWinCheckFree(winningString);
	SDL_FreeSurface(gameStatusSurface);

	return false;
}
