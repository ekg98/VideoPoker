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
	
	SDL_Surface* denomButtonSelectedSurface[5];
	SDL_Surface* denomButtonNotSelectedSurface[5];

	// null the denom buttons
	for (intCounter = 0; intCounter < 5; intCounter++)
	{
		denomButtonSelectedSurface[intCounter] = NULL;
		denomButtonNotSelectedSurface[intCounter] = NULL;
		gameButtonImageData->denomButtonSelectedTexture[intCounter] = NULL;
		gameButtonImageData->denomButtonNotSelectedTexture[intCounter] = NULL;
	}

	// load the image into the surfaces
	denomButtonSelectedSurface[0] = IMG_Load("images/denom.png");

	// check if denom buttons loaded properly
	if (denomButtonSelectedSurface[0] == NULL)
	{
		printf("SDL could not load images: %s\n", IMG_GetError());
		return 1;
	}

	// load textures from surface
	gameButtonImageData->denomButtonSelectedTexture[0] = SDL_CreateTextureFromSurface(mainWindowRenderer, denomButtonSelectedSurface[0]);

	if(gameButtonImageData->denomButtonSelectedTexture[0] == NULL)
	{
		printf("SDL could not load denom button textures: %s\n", SDL_GetError());
		return 1;
	}

	// coordinates here
	denomButtonResWidthCorrected = ((intWindowWidth / 1920.0) * DENOM_BUTTON_WIDTH);
	denomButtonResHeightCorrected = ((intWindowHeight / 1200.0) * DENOM_BUTTON_HEIGHT);
	
	gameButtonImageData->denomButtonSource[0].x = 0;
	gameButtonImageData->denomButtonSource[0].y = 0;
	gameButtonImageData->denomButtonSource[0].w = DENOM_BUTTON_WIDTH;
	gameButtonImageData->denomButtonSource[0].h = DENOM_BUTTON_HEIGHT;
	
	gameButtonImageData->denomButtonDest.x = (intWindowWidth /2) - (denomButtonResWidthCorrected / 2);
	gameButtonImageData->denomButtonDest.y = (intWindowHeight / 1.15);
	gameButtonImageData->denomButtonDest.h = denomButtonResHeightCorrected;
	gameButtonImageData->denomButtonDest.w = denomButtonResWidthCorrected;


	// free the denom button surfaces
	SDL_FreeSurface(denomButtonSelectedSurface[0]);
	denomButtonSelectedSurface[0] = NULL;
}

void closebuttons(struct gameButtonImageData *gameButtonImageData)
{
	SDL_DestroyTexture(gameButtonImageData->denomButtonSelectedTexture[0]);
	gameButtonImageData->denomButtonSelectedTexture[0] = NULL;
}