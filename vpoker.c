/* Video Poker.  Simple SDL video poker prototype game my ekg98 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"
#include "wccommon.h"
#include "sdlcards.h"

/* global constants aka defines */
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200
#define CARD_WIDTH  350
#define CARD_HEIGHT 500

/* function prototypes */
int initsdl(void);
void closesdl(void);
int loadDeck(void);
void closeDeck(void);

/* global vpoker variables */
SDL_Window *mainWindow = NULL;
SDL_Surface *mainWindowSurface = NULL;
SDL_Renderer *mainWindowRenderer = NULL;
SDL_Texture *DeckTextures[5];	/* Array of pointers to the deck textures */
struct cardSuitCoordinates cardCoordinates[5]; /* structure containing array of SDL_Rect */
SDL_Rect cardDest[5];	/* Destination for the cards on the screen.  Dependent on screen resolution */
SDL_Event event;
struct card hand[5];

/* main program */
int main()
{
  if(initsdl())  /* initialize sdl */
    return 1;
  else
  {
    	int i;

	srand(time(NULL));
	inithand(hand, 5);
	deal(hand , 5);

	SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 255, 0);
    	SDL_RenderClear(mainWindowRenderer);

	for(i = 0; i < 5; i++)
		SDL_RenderCopy(mainWindowRenderer, DeckTextures[hand[i].suit], &cardCoordinates[hand[i].suit].source[hand[i].value], &cardDest[i]);

      while(event.type != SDL_QUIT)
      {

        SDL_RenderPresent(mainWindowRenderer);
        SDL_PollEvent(&event);
      }
  }

  closesdl(); /* shut down sdl */
  return 0;
}

/* initsdl:  Start up SDL */
int initsdl(void)
{
  int imageFlags = IMG_INIT_PNG;

  if(SDL_Init(SDL_INIT_VIDEO))
  {
    printf("SDL unable to initialize: %s", SDL_GetError());
    return 1;
  }
  else
  {
    if((IMG_Init(imageFlags) & imageFlags) != imageFlags)
    {
      printf("SDL unable to initialize IMG_Init: %s", IMG_GetError());
      return 1;
    }
    else
      mainWindow = SDL_CreateWindow("Video Poker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  }

  if(mainWindow == NULL)
  {
    printf("Window could not be created: %s", SDL_GetError());
    return 1;
  }
  else
    mainWindowSurface = SDL_GetWindowSurface(mainWindow);

  if(mainWindowSurface == NULL)
  {
    printf("Window surface could not be created: %s", SDL_GetError());
    return 1;
  }
  else
      mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(mainWindowRenderer == NULL)
  {
    printf("SDL could not create renderer: %s", SDL_GetError());
    return 1;
  }

  /* Error checking for loading the texture deck */
  if(loadDeck())
    return 1;

  return 0;
}

/* closesdl:  Shut down SDL */
void closesdl(void)
{
  closeDeck();

  SDL_DestroyRenderer(mainWindowRenderer);
  mainWindowRenderer = NULL;

  SDL_DestroyWindow(mainWindow);
  mainWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}

/* loadDeck:  Load deck of card images into memory. */
int loadDeck(void)
{

  int suit, i;
  SDL_Surface *cards[5];

  /* load the cards into memory for manipulation */
  cards[0] = NULL;
  cards[1] = IMG_Load("images/cardh.png");
  cards[2] = IMG_Load("images/cardd.png");
  cards[3] = IMG_Load("images/cardc.png");
  cards[4] = IMG_Load("images/cards.png");

  /* Error loading card images */
  for(suit = 1; suit < 5; suit++)
  {
    if(cards[suit] == NULL)
    {
      printf("SDL could not load images: %s", IMG_GetError());
      return 1;
    }
  }

  	/* Null the whole deck texture array */
	for(suit = 0; suit < 5; suit++)
	{
		DeckTextures[suit] = NULL;
	}

  /* convert the surface to comply with the screen */
  for(suit = 1; suit < 5; suit++)
  {
    DeckTextures[suit] = SDL_CreateTextureFromSurface(mainWindowRenderer, cards[suit]);
  }

  /* Error check to see if deck texture was loaded into memory */
  for(suit = 1; suit < 5; suit++)
  {
  	if(DeckTextures[suit] == NULL)
	{
		printf("SDL could not load deck textures: %s\n", SDL_GetError());
		return 1;
	}
  }

  /* free the function local surfaces */
  for(suit = 0; suit < 5; suit++)
  {
    SDL_FreeSurface(cards[suit]);
    cards[suit] = NULL;
  }

	/* create output render coordinates dependent on screen resolution */
	for(i = 0; i < 5; i++)
	{
		cardDest[i].x = (((WINDOW_WIDTH / 5) * (i + 1)) - CARD_WIDTH);
		cardDest[i].y = WINDOW_HEIGHT / 2;
		cardDest[i].w = (WINDOW_WIDTH / 1920) * CARD_WIDTH;
		cardDest[i].h = (WINDOW_HEIGHT / 1200) * CARD_HEIGHT;
	}

	/* create coordinates for the cards from the image deck textures */
	for(suit = 1; suit < 5; suit++)
		for(i = 0; i < 15; i++)
		{
			cardCoordinates[suit].source[i].x = CARD_WIDTH * i;
			cardCoordinates[suit].source[i].y = 0;
			cardCoordinates[suit].source[i].w = CARD_WIDTH;
			cardCoordinates[suit].source[i].h = CARD_HEIGHT;
		}

  return 0;

}

/* closeDeck:  Free the images that were loaded for the deck of cards */
void closeDeck(void)
{

  int suit, i;

  /* Destroy the whole deck */
  for(suit = 0; suit < 4; suit++)
  {
    SDL_DestroyTexture(DeckTextures[suit]);
    DeckTextures[suit] = NULL;
  }

}
