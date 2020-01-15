/* Video Poker.  Simple SDL video poker prototype game my ekg98 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "cards.h"
#include "wccommon.h"
#include "sdlfonts.h"
#include "sdlcards.h"
#include "sdlbuttons.h"

/* Window resolutions and card resolutions - Must be floating point */
#define DEFAULT_WINDOW_WIDTH  1920.0
#define DEFAULT_WINDOW_HEIGHT 1080.0
#define CARD_WIDTH  350.0
#define CARD_HEIGHT 500.0
#define	SPACING_MULTIPLIER	7	// multiplier to determine spacing between the cards.  intWindowWidth / SPACING_MULTIPLIER

#define	TRUE	1
#define	FALSE	0

/* function prototypes */
int initsdl(void);
void closesdl(void);
int loadDeck(void);
void closeDeck(void);
void loadButtons(void);
void closeButtons(void);


/* global vpoker variables */
SDL_Window *mainWindow = NULL;
SDL_Surface *mainWindowSurface = NULL;
SDL_Renderer *mainWindowRenderer = NULL;
SDL_Texture *DeckTextures[5];	/* Array of pointers to the deck textures */
SDL_Texture *buttonTextures[8];	// Array of pointers to button textures
SDL_Texture *heldTexture = NULL;	// texture helding the held text
SDL_Rect heldSource;
SDL_Rect heldDest[5];
struct cardSuitCoordinates cardCoordinates[5]; /* structure containing array of SDL_Rect */
struct buttonCoordinates buttonCoordinates[8];	// stucture containing array of SDL_Rect`
SDL_Rect cardDest[5];	/* Destination for the cards on the screen.  Dependent on screen resolution */
SDL_Rect buttonDest[8]; // Destination for the buttons on the screen.  Dependant on screen resolution
SDL_Event event;
struct card hand[5];

// resolution variables
int intWindowWidth = DEFAULT_WINDOW_WIDTH;
int intWindowHeight = DEFAULT_WINDOW_HEIGHT;

/* main program */
int main(int argc, char *argv[])
{

	// main variables


	// checks to see if there are any arguments available
	if(argc > 1)
	{

		// parse the argumenmt line for available options
		for(int argCounter = 1; argCounter < argc; argCounter++)
		{
			if(*(argv[argCounter]) == '-')
			{

				// argv is a pointer.  We can increment pointers.  Checks argCounter to see if its out of bounds otherwise it will result in checking last argument twice
				while(argCounter < argc && *(argv[argCounter])++ != '\0')
				{
					switch(*argv[argCounter])
					{
						case 'h':
							printf("Video Poker - A copy of a vegas poker game.\n");
							printf("arguments:\n");
							printf("\t-h  This menu.\n");
							printf("\t-r  Adjust screen resolution\n");
							return 0;
							break;
						case 'r':
							if((argc - 1) > argCounter)
							{
								argCounter++;

								// 1080p
								if(strcmp(argv[argCounter], "1920x1080") == 0)
								{
									intWindowWidth = 1920;
									intWindowHeight = 1080;
									argCounter++;
								}
								// 720p
								else if(strcmp(argv[argCounter], "1280x720") == 0)
								{
									intWindowWidth = 1280;
									intWindowHeight = 720;
									argCounter++;
								}
								// 1280x1024 SuperXGA
								else if(strcmp(argv[argCounter], "1280x1024") == 0)
								{
									intWindowWidth = 1280;
									intWindowHeight = 1024;
									argCounter++;
								}
								// 1024x768 XGA
								else if(strcmp(argv[argCounter], "1024x768") == 0)
								{
									intWindowWidth = 1024;
									intWindowHeight = 768;
									argCounter++;
								}
								// 800x600 SVGA
								else if(strcmp(argv[argCounter], "800x600") == 0)
								{
									intWindowWidth = 800;
									intWindowHeight = 600;
									argCounter++;
								}
								// 640x480 VGA
								else if(strcmp(argv[argCounter], "640x480") == 0)
								{
									intWindowWidth = 640;
									intWindowHeight = 480;
									argCounter++;
								}
								else
								{
									fprintf(stderr, "Invalid resolution requested.\n");
									exit(1);
								}

								break;
							}
							else
								return 1;
							break;
						default:
							printf("%d\n", argCounter);
							printf("Invalid argument(s)\n");
							return 1;
							break;
					}
				}


			}
		}


	}

	// start the game here
        if(initsdl())  /* initialize sdl */
        	return 1;
        else
        {
    	       	int i;
		bool returnPrevPressed, onePrevHeld, twoPrevHeld, threePrevHeld, fourPrevHeld, fivePrevHeld = false;
		bool firstDeal = true;
        	srand(time(NULL));
        	inithand(hand, 5);

		while(event.type != SDL_QUIT)
		{
			// poll for events, mouse ,or keyboard input
        		SDL_PollEvent(&event);

			// deal keyboard logic
			if(event.key.keysym.scancode == SDL_SCANCODE_RETURN && event.key.state == SDL_PRESSED)
			{
				// first deal.  Unheld all cards and reset held key states
				if(firstDeal == true && returnPrevPressed == false)
				{
					// reset held key states
					onePrevHeld = false;
					twoPrevHeld = false;
					threePrevHeld = false;
					fourPrevHeld = false;
					fivePrevHeld = false;

					// unheld and deal cards
					unheld(hand, 5);
					deal(hand, 5);
					firstDeal = false;
					returnPrevPressed = true;
					printf("Good Luck!\n");
				}
				// second deal
				if(firstDeal == false && returnPrevPressed == false)
				{
					// deal cards that are not held
					deal(hand, 5);
					firstDeal = true;
					returnPrevPressed = true;
					printf("Game Over!\n");
				}
			}

			if(event.key.keysym.scancode == SDL_SCANCODE_RETURN && event.key.state == SDL_RELEASED)
				returnPrevPressed = false;

			// first card held logic
			if(event.key.keysym.scancode == SDL_SCANCODE_1 && event.key.state == SDL_PRESSED)
			{
				if(onePrevHeld == false)
				{
					hand[0].held = YES;
					onePrevHeld = true;
				}
				else
				{
					hand[0].held = NO;
					onePrevHeld = false;
				}
			}

			// second card held logic
			if(event.key.keysym.scancode == SDL_SCANCODE_2 && event.key.state == SDL_PRESSED)
			{
				if(twoPrevHeld == false)
				{
					hand[1].held = YES;
					twoPrevHeld = true;
				}
				else
				{
					hand[1].held = NO;
					twoPrevHeld = false;
				}
			}

			// third card held logic
			if(event.key.keysym.scancode == SDL_SCANCODE_3 && event.key.state == SDL_PRESSED)
			{
				if(threePrevHeld == false)
				{
					hand[2].held = YES;
					threePrevHeld = true;
				}
				else
				{
					hand[2].held = NO;
					threePrevHeld = false;
				}
			}

			// fourth card held logic
			if(event.key.keysym.scancode == SDL_SCANCODE_4 && event.key.state == SDL_PRESSED)
			{
				if(fourPrevHeld == false)
				{
					hand[3].held = YES;
					fourPrevHeld = true;
				}
				else
				{
					hand[3].held = NO;
					fourPrevHeld = false;
				}
			}

			// fifth card held logic
			if(event.key.keysym.scancode == SDL_SCANCODE_5 && event.key.state == SDL_PRESSED)
			{
				if(fivePrevHeld == false)
				{
					hand[4].held = YES;
					fivePrevHeld = true;
				}
				else
				{
					hand[4].held = NO;
					fivePrevHeld = false;
				}
			}

			// draw images
			SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 255, 0);	// sets window to blue color
	        	SDL_RenderClear(mainWindowRenderer);

			for(i = 0; i < 5; i++)
				SDL_RenderCopy(mainWindowRenderer, DeckTextures[hand[i].suit], &cardCoordinates[hand[i].suit].source[hand[i].value], &cardDest[i]);

			if(hand[0].held == YES)
				SDL_RenderCopy(mainWindowRenderer, heldTexture, NULL, &heldDest[0]);

			if(hand[1].held == YES)
				SDL_RenderCopy(mainWindowRenderer, heldTexture, NULL, &heldDest[1]);

			if(hand[2].held == YES)
				SDL_RenderCopy(mainWindowRenderer, heldTexture, NULL, &heldDest[2]);

			if(hand[3].held == YES)
				SDL_RenderCopy(mainWindowRenderer, heldTexture, NULL, &heldDest[3]);

			if(hand[4].held == YES)
				SDL_RenderCopy(mainWindowRenderer, heldTexture, NULL, &heldDest[4]);


			// update the screen
			SDL_RenderPresent(mainWindowRenderer);
		}
	}

	closeDeck();
	closeText();
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
			mainWindow = SDL_CreateWindow("Video Poker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, intWindowWidth, intWindowHeight, SDL_WINDOW_SHOWN);
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

	if(TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}

	if(loadFont())
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

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/* loadDeck:  Load deck of card images into memory. */
int loadDeck(void)
{
	int suit, i, spaceWidth = 0;
	float resCorrectedSpaceWidth = 0.0;
	float resCorrectedInterval = 0.0;
	float cardResHeightCorrected = 0.0;
	float cardResWidthCorrected = 0.0;
	float cardXEdge = 0.0;
	float cardHalf = 0.0;
	float edgeToCenter = 0.0;
	float spacingDistance = 0.0;
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

	/* calculate the cards width and height corrected for set screen resolution.  0.7 is a correction factor since cards are made for 1920x1080 resolution */
	cardResWidthCorrected = ((intWindowWidth / 1920.0) * CARD_WIDTH) * 0.7;
	cardResHeightCorrected = ((intWindowHeight / 1200.0) * CARD_HEIGHT) * 0.7;

	// card spacing calculations
	cardHalf = cardResWidthCorrected / 2;
	spacingDistance = intWindowWidth / SPACING_MULTIPLIER;

	/* create output render coordinates dependent on screen resolution */
	for(i = 0; i < 5; i++)
	{
		cardDest[i].y = intWindowHeight/ 2;
		cardDest[i].w = cardResWidthCorrected;
		cardDest[i].h = cardResHeightCorrected;
	}

	cardDest[0].x = ((intWindowWidth / 2) - cardHalf) - (spacingDistance * 2);
	cardDest[1].x = ((intWindowWidth / 2) - cardHalf) - (spacingDistance * 1);
	cardDest[2].x = (intWindowWidth / 2) - cardHalf;
	cardDest[3].x = ((intWindowWidth / 2) - cardHalf) + (spacingDistance * 1);
	cardDest[4].x = ((intWindowWidth / 2) - cardHalf) + (spacingDistance * 2);

	/* create coordinates for the cards from the image deck textures */
        /* first set element of the structure is ignored */
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
	for(suit = 0; suit < 5; suit++)
	{
		SDL_DestroyTexture(DeckTextures[suit]);
    		DeckTextures[suit] = NULL;
  	}
}

// loadButtons: Load the buttons into memory
void loadButtons(void)
{

}

// closeButtons: Free the images used for the buttons from memory
void closeButtons(void)
{

}
