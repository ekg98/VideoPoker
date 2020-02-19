/* Video Poker.  Simple SDL video poker prototype game my ekg98 */


#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "common.h"
#include "wccommon.h"
#include "sdlfonts.h"
#include "sdlcards.h"
#include "sdlbuttons.h"
#include "cards.h"
#include "events.h"
#include <float.h>

/* Window resolutions and card resolutions - Must be floating point */
#define DEFAULT_WINDOW_WIDTH  1920
#define DEFAULT_WINDOW_HEIGHT 1080
#define CARD_WIDTH  350
#define CARD_HEIGHT 500
#define MAX_FRAMERATE	60

#define	TRUE	1
#define	FALSE	0

/* function prototypes */
int initsdl(struct fonts *, struct fiveCardDeckImageData *);
void closesdl(void);
int loadDeck(struct fiveCardDeckImageData *);
void closeDeck(struct fiveCardDeckImageData *);
void loadButtons(void);
void closeButtons(void);


/* global vpoker variables */
SDL_Window *mainWindow = NULL;
SDL_Surface *mainWindowSurface = NULL;
SDL_Renderer *mainWindowRenderer = NULL;
//SDL_Texture *buttonTextures[8];	// Array of pointers to button textures
//struct buttonCoordinates buttonCoordinates[8];	// stucture containing array of SDL_Rect
//SDL_Rect buttonDest[8]; // Destination for the buttons on the screen.  Dependant on screen resolution
SDL_Event event;
struct card hand[5];

// resolution variables
int intWindowWidth = DEFAULT_WINDOW_WIDTH;
int intWindowHeight = DEFAULT_WINDOW_HEIGHT;

/* main program */
int main(int argc, char *argv[])
{
	// local main variables go here
	bool displayFps = false;
	float floatCredits = 0;


	// large structure containing game font datas.
	struct fonts gameFonts;

	struct fiveCardDeckImageData deckImageData;
	
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
							printf("\t-f  Display framerate on screen\n");
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

						case 'f':
							displayFps = true;
							argCounter++;
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
        if(initsdl(&gameFonts, &deckImageData))  /* initialize sdl */
        	return 1;
		else
		{
			// timing variables
			int frameCounter = 0;
			int averageFps = 0;
			uint32_t startRunTicks = 0;
			uint32_t endRunTicks = 0;
			int runTicks = 0;
			float tickInterval = 1000.0 / MAX_FRAMERATE;

			enum gametype gameType = JACKS_OR_BETTER;

			srand(time(NULL));
			inithand(hand, 5);
			
			// gameHeldText:  Generates textures and calculations for game held text.
			if (gameHeldText(&gameFonts))
				return 1;

			while (event.type != SDL_QUIT)
			{
				bool handState = FIRST_HAND;
				
				// get current ticks
				startRunTicks = SDL_GetTicks();
				runTicks = runTicks + (startRunTicks - endRunTicks);
				
				// calculate average fps
				averageFps = (int) (frameCounter / (startRunTicks / 1000.0));

				// poll loop for events, mouse ,or keyboard input.  Loop clears all events before continuing
				handState = getEvents(&event, hand, &floatCredits);
								
				// frame rate limiting for display functions.  Used instead of vsync limiting
				if (runTicks > tickInterval)
				{
					// Set background color to blue and clear the screen of previous garbage.
					SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 255, 0);
					SDL_RenderClear(mainWindowRenderer);
														
					//gameFpsText: returns true on failure.  Displays game fps on the screen
					if (displayFps == true && !gameFpsText(averageFps, &gameFonts))
						SDL_RenderCopy(mainWindowRenderer, gameFonts.gameFpsTextTexture, NULL, &gameFonts.gameFpsTextDest);
														
					// Depending on what game is being played.  Render the correct graphical selection.
					switch (gameType)
					{
						case JACKS_OR_BETTER:
							JacksOrBetterRender(hand, &gameFonts, &deckImageData, handState);
							break;
						case DUCES_WILD:
							break;
					}

					// Render the screen.
					SDL_RenderPresent(mainWindowRenderer);
					
					frameCounter++;
					runTicks = 0;
				}

				endRunTicks = startRunTicks;
			}
		}


	closeDeck(&deckImageData);
	closeText(&gameFonts);
	closesdl();

	return 0;
}

/* initsdl:  Start up SDL */
int initsdl(struct fonts *gameFonts, struct fiveCardDeckImageData *deckImageData)
{
	int imageFlags = IMG_INIT_PNG;

	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "SDL unable to initialize: %s", SDL_GetError());
		return 1;
	}
	else
	{
		if((IMG_Init(imageFlags) & imageFlags) != imageFlags)
		{
			fprintf(stderr, "SDL unable to initialize IMG_Init: %s", IMG_GetError());
			return 1;
		}
		else
			mainWindow = SDL_CreateWindow("Video Poker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, intWindowWidth, intWindowHeight, SDL_WINDOW_SHOWN);
	}

	if(mainWindow == NULL)
	{
		fprintf(stderr, "Window could not be created: %s", SDL_GetError());
		return 1;
	}
	else
		mainWindowSurface = SDL_GetWindowSurface(mainWindow);

	if(mainWindowSurface == NULL)
	{
		fprintf(stderr, "Window surface could not be created: %s", SDL_GetError());
		return 1;
	}
	else
		mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	if(mainWindowRenderer == NULL)
	{
		fprintf(stderr, "SDL could not create renderer: %s", SDL_GetError());
 	return 1;
	}

	/* Error checking for loading the texture deck */
	if(loadDeck(deckImageData))
		return 1;

	if(TTF_Init() == -1)
	{
		fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 1;
	}

	if(loadFonts(gameFonts))
	{
		fprintf(stderr, "Failure to load game fonts.");
		return 1;
	}

	return 0;
}

/* closesdl:  Shut down SDL */
void closesdl(void)
{
	SDL_DestroyRenderer(mainWindowRenderer);
	mainWindowRenderer = NULL;

	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/* loadDeck:  Load deck of card images into memory. */
int loadDeck(struct fiveCardDeckImageData *deckImageData)
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
		deckImageData->suitTexture[suit] = NULL;
	}

  	/* convert the surface to comply with the screen */
  	for(suit = 1; suit < 5; suit++)
  	{
    		deckImageData->suitTexture[suit] = SDL_CreateTextureFromSurface(mainWindowRenderer, cards[suit]);
  	}

  	/* Error check to see if deck texture was loaded into memory */
  	for(suit = 1; suit < 5; suit++)
  	{
  		if(deckImageData->suitTexture[suit] == NULL)
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
	spacingDistance = intWindowWidth / 7;

	/* create output render coordinates dependent on screen resolution */
	for(i = 0; i < 5; i++)
	{
		deckImageData->cardDest[i].y = intWindowHeight/ 2;
		deckImageData->cardDest[i].w = cardResWidthCorrected;
		deckImageData->cardDest[i].h = cardResHeightCorrected;
	}

	deckImageData->cardDest[0].x = ((intWindowWidth / 2) - cardHalf) - (spacingDistance * 2);
	deckImageData->cardDest[1].x = ((intWindowWidth / 2) - cardHalf) - (spacingDistance * 1);
	deckImageData->cardDest[2].x = (intWindowWidth / 2) - cardHalf;
	deckImageData->cardDest[3].x = ((intWindowWidth / 2) - cardHalf) + (spacingDistance * 1);
	deckImageData->cardDest[4].x = ((intWindowWidth / 2) - cardHalf) + (spacingDistance * 2);

	/* create coordinates for the cards from the image deck textures */
        /* first set element of the structure is ignored */
	for(suit = 1; suit < 5; suit++)
		for(i = 0; i < 15; i++)
		{
			deckImageData->cardSource[suit].card[i].x = CARD_WIDTH * i;
			deckImageData->cardSource[suit].card[i].y = 0;
			deckImageData->cardSource[suit].card[i].w = CARD_WIDTH;
			deckImageData->cardSource[suit].card[i].h = CARD_HEIGHT;
		}
	return 0;
}

/* closeDeck:  Free the images that were loaded for the deck of cards */
void closeDeck(struct fiveCardDeckImageData *deckImageData)
{
	int suit;

	/* Destroy the whole deck */
	for(suit = 0; suit < 5; suit++)
	{
		SDL_DestroyTexture(deckImageData->suitTexture[suit]);
    		deckImageData->suitTexture[suit] = NULL;
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
