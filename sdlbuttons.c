// Source file for buttons

#include "common.h"
#include "cards.h"
#include "sdlbuttons.h"

#define DENOM_BUTTON_WIDTH	200
#define DENOM_BUTTON_HEIGHT	145

extern SDL_Renderer* mainWindowRenderer;
extern int intWindowWidth;
extern int intWindowHeight;

int loadbuttons(struct gameButtonImageData *gameButtonImageData)
{
	int intCounter = 0;
	float denomButtonResWidthCorrected = 0.0;
	float denomButtonResHeightCorrected = 0.0;
	
	SDL_Surface* denomButtonSelectedSurface;
	SDL_Surface* denomButtonNotSelectedSurface;

	// null the denom buttons
	denomButtonSelectedSurface = NULL;
	denomButtonNotSelectedSurface = NULL;
	gameButtonImageData->denomButtonSelectedTexture = NULL;
	gameButtonImageData->denomButtonNotSelectedTexture = NULL;
	

	// load the image into the surfaces
	denomButtonSelectedSurface = IMG_Load("images/denomselected.png");

	// check if denom buttons loaded properly
	if (denomButtonSelectedSurface == NULL)
	{
		printf("SDL could not load images: %s\n", IMG_GetError());
		return 1;
	}

	// set color key
	SDL_SetColorKey(denomButtonSelectedSurface, SDL_TRUE, SDL_MapRGB(denomButtonSelectedSurface->format, 255, 174, 201));

	// load textures from surface
	gameButtonImageData->denomButtonSelectedTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, denomButtonSelectedSurface);

	if(gameButtonImageData->denomButtonSelectedTexture == NULL)
	{
		printf("SDL could not load denom button textures: %s\n", SDL_GetError());
		return 1;
	}

	// coordinates here
	denomButtonResWidthCorrected = ((intWindowWidth / 1920.0) * DENOM_BUTTON_WIDTH);
	denomButtonResHeightCorrected = ((intWindowHeight / 1280.0) * DENOM_BUTTON_HEIGHT);
	
	// Assign coordinates to source rect
	for (intCounter = 0; intCounter < 5; intCounter++)
	{
		gameButtonImageData->denomButtonSource[intCounter].x = DENOM_BUTTON_WIDTH * intCounter;
		gameButtonImageData->denomButtonSource[intCounter].y = 0;
		gameButtonImageData->denomButtonSource[intCounter].w = DENOM_BUTTON_WIDTH;
		gameButtonImageData->denomButtonSource[intCounter].h = DENOM_BUTTON_HEIGHT;
	}

	gameButtonImageData->denomButtonDest.x = (intWindowWidth /2) - (denomButtonResWidthCorrected / 2);
	gameButtonImageData->denomButtonDest.y = (intWindowHeight / 1.15);
	gameButtonImageData->denomButtonDest.h = denomButtonResHeightCorrected;
	gameButtonImageData->denomButtonDest.w = denomButtonResWidthCorrected;


	// free the denom button surfaces
	SDL_FreeSurface(denomButtonSelectedSurface);
	denomButtonSelectedSurface = NULL;

	return 0;
}

void closebuttons(struct gameButtonImageData *gameButtonImageData)
{
	SDL_DestroyTexture(gameButtonImageData->denomButtonSelectedTexture);
	gameButtonImageData->denomButtonSelectedTexture = NULL;

	SDL_DestroyTexture(gameButtonImageData->denomButtonNotSelectedTexture);
	gameButtonImageData->denomButtonNotSelectedTexture = NULL;
}