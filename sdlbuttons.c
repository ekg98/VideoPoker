// Source file for buttons

#include "common.h"
#include "cards.h"
#include "sdlbuttons.h"

// configuration defines
#define DENOM_BUTTON_WIDTH	200
#define DENOM_BUTTON_HEIGHT	145
#define POKER_CONTROL_BUTTON_WIDTH	220
#define	POKER_CONTROL_BUTTON_HEIGHT	90

extern SDL_Renderer* mainWindowRenderer;
extern int intWindowWidth;
extern int intWindowHeight;

// loaddenombuttons:  Loads the denom buttons.
int loaddenombuttons(struct gameDenomButtonImageData *gameDenomButtonImageData)
{
	int intCounter = 0;
	float denomButtonResWidthCorrected = 0.0;
	float denomButtonResHeightCorrected = 0.0;
	
	SDL_Surface* denomButtonSelectedSurface = NULL;
	SDL_Surface* denomButtonNotSelectedSurface = NULL;

	// null the denom buttons
	gameDenomButtonImageData->denomButtonSelectedTexture = NULL;
	gameDenomButtonImageData->denomButtonNotSelectedTexture = NULL;
	

	// load the image into the surfaces
	denomButtonSelectedSurface = IMG_Load("images/denomselected.png");
	denomButtonNotSelectedSurface = IMG_Load("images/denomnotselected.png");

	// check if denom buttons loaded properly
	if (denomButtonSelectedSurface == NULL || denomButtonNotSelectedSurface == NULL)
	{
		printf("SDL could not load images: %s\n", IMG_GetError());
		return 1;
	}

	// set color key
	SDL_SetColorKey(denomButtonSelectedSurface, SDL_TRUE, SDL_MapRGB(denomButtonSelectedSurface->format, 255, 174, 201));
	SDL_SetColorKey(denomButtonNotSelectedSurface, SDL_TRUE, SDL_MapRGB(denomButtonNotSelectedSurface->format, 255, 174, 201));

	// load textures from surface
	gameDenomButtonImageData->denomButtonSelectedTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, denomButtonSelectedSurface);
	gameDenomButtonImageData->denomButtonNotSelectedTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, denomButtonNotSelectedSurface);

	if(gameDenomButtonImageData->denomButtonSelectedTexture == NULL || gameDenomButtonImageData->denomButtonNotSelectedTexture == NULL)
	{
		printf("SDL could not load denom button textures: %s\n", SDL_GetError());
		return 1;
	}
	
	// coordinates here
	denomButtonResWidthCorrected = ((intWindowWidth / 1920.0) * DENOM_BUTTON_WIDTH);
	denomButtonResHeightCorrected = ((intWindowHeight / 1280.0) * DENOM_BUTTON_HEIGHT);
	
	// Assign coordinates to source rect for denom buttons
	for (intCounter = 0; intCounter < 5; intCounter++)
	{
		gameDenomButtonImageData->denomButtonSource[intCounter].x = DENOM_BUTTON_WIDTH * intCounter;
		gameDenomButtonImageData->denomButtonSource[intCounter].y = 0;
		gameDenomButtonImageData->denomButtonSource[intCounter].w = DENOM_BUTTON_WIDTH;
		gameDenomButtonImageData->denomButtonSource[intCounter].h = DENOM_BUTTON_HEIGHT;
	}

	// denomButtonDest location is for poker game.  Centered bottom of screen
	gameDenomButtonImageData->denomButtonDest.x = (intWindowWidth /2) - (denomButtonResWidthCorrected / 2);
	gameDenomButtonImageData->denomButtonDest.y = (intWindowHeight / 1.15);
	gameDenomButtonImageData->denomButtonDest.h = denomButtonResHeightCorrected;
	gameDenomButtonImageData->denomButtonDest.w = denomButtonResWidthCorrected;


	// free the denom button surfaces
	SDL_FreeSurface(denomButtonSelectedSurface);
	denomButtonSelectedSurface = NULL;

	SDL_FreeSurface(denomButtonNotSelectedSurface);
	denomButtonNotSelectedSurface = NULL;

	return 0;
}

// closedenombuttons:  Closes the denom buttons.
void closedenombuttons(struct gameDenomButtonImageData *gameDenomButtonImageData)
{
	SDL_DestroyTexture(gameDenomButtonImageData->denomButtonSelectedTexture);
	gameDenomButtonImageData->denomButtonSelectedTexture = NULL;

	SDL_DestroyTexture(gameDenomButtonImageData->denomButtonNotSelectedTexture);
	gameDenomButtonImageData->denomButtonNotSelectedTexture = NULL;
}

// loadpokercontrolbuttons:  Loads the poker control buttons.
int loadpokercontrolbuttons(struct gamePokerControlButtonImageData *gamePokerControlButtonImageData)
{
	int intCounter = 0;
	SDL_Surface* pokerControlButtonsSurface = NULL;

	float PokerControlButtonResWidthCorrected = 0.0;
	float PokerControlButtonResHeightCorrected = 0.0;

	// null the control button texture
	gamePokerControlButtonImageData->pokerControlButtonTexture = NULL;

	pokerControlButtonsSurface = IMG_Load("images/pokercontrolbuttons.png");

	// check for errors in loading surface
	if (pokerControlButtonsSurface == NULL)
	{
		printf("SDL could not load images: %s\n", IMG_GetError());
		return 1;
	}

	// load texture from surface
	gamePokerControlButtonImageData->pokerControlButtonTexture = SDL_CreateTextureFromSurface(mainWindowRenderer, pokerControlButtonsSurface);

	// error check texture
	if (gamePokerControlButtonImageData->pokerControlButtonTexture == NULL)
	{
		printf("SDL could not load poker control button textures: %s\n", SDL_GetError());
		return 1;
	}

	// resolution adjustments
	PokerControlButtonResWidthCorrected = ((intWindowWidth / 1920.0) * POKER_CONTROL_BUTTON_WIDTH);
	PokerControlButtonResHeightCorrected = ((intWindowHeight / 1280.0) * POKER_CONTROL_BUTTON_HEIGHT);

	// load coordinates for poker control button source
	for (intCounter = 0; intCounter < 6; intCounter++)
	{
		gamePokerControlButtonImageData->pokerControlButtonSource[intCounter].x = POKER_CONTROL_BUTTON_WIDTH * intCounter;
		gamePokerControlButtonImageData->pokerControlButtonSource[intCounter].y = 0;
		gamePokerControlButtonImageData->pokerControlButtonSource[intCounter].w = POKER_CONTROL_BUTTON_WIDTH;
		gamePokerControlButtonImageData->pokerControlButtonSource[intCounter].h = POKER_CONTROL_BUTTON_HEIGHT;

		// x needs to skew for proper placement
		gamePokerControlButtonImageData->pokerControlButtonDest[intCounter].x = 20;
		gamePokerControlButtonImageData->pokerControlButtonDest[intCounter].y = (intWindowHeight / 1.11);
		gamePokerControlButtonImageData->pokerControlButtonDest[intCounter].h = PokerControlButtonResHeightCorrected;
		gamePokerControlButtonImageData->pokerControlButtonDest[intCounter].w = PokerControlButtonResWidthCorrected;
	}

	return 0;
}

// closepokercontrolbuttons:  Closes the poker control buttons.
void closepokercontrolbuttons(struct gamePokerControlButtonImageData *gamePokerControlButtonImageData)
{
	SDL_DestroyTexture(gamePokerControlButtonImageData->pokerControlButtonTexture);
	gamePokerControlButtonImageData->pokerControlButtonTexture = NULL;
}