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
#include "jobrender.h"
#include "jobpayout.h"
#include "events.h"

/* function prototypes */
int initsdl(bool, struct fonts *, struct fiveCardDeckImageData *, struct gameDenomButtonImageData *, struct gamePokerControlButtonImageData *);
void closesdl(void);
int loadDeck(struct fiveCardDeckImageData *);
void closeDeck(struct fiveCardDeckImageData *);

/* global vpoker variables */
SDL_Window *mainWindow = NULL;
SDL_Surface *mainWindowSurface = NULL;
SDL_Renderer *mainWindowRenderer = NULL;
SDL_Event event;
struct card hand[5];

// resolution variables and default initialization
int intWindowWidth = DEFAULT_WINDOW_WIDTH;
int intWindowHeight = DEFAULT_WINDOW_HEIGHT;

/* main program */
int main(int argc, char *argv[])
{
	// local main variables go here
	bool displayFps = false;
	float floatGameCash = 0;
	int intBetLevel = 1;
	bool fullscreen = false;

	// large structure containing game font datas.
	struct fonts gameFonts;

	// large structure containing game deck image data for five card poker.
	struct fiveCardDeckImageData deckImageData;

	// large structure containing game denom button image data for five card poker.
	struct gameDenomButtonImageData gameDenomButtonImageData;
	
	// large structure containing poker control button image data.
	struct gamePokerControlButtonImageData gamePokerControlButtonImageData;

	// large structure containing common game stats
	struct commonGameStats commonGameStats;
	

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
							printf("\t-r  Adjust screen resolution.  -r fs for full screen\n");
							printf("\t\t1920x1080, 1280x720, 1280x1024, 1024x768, 800x600, and 640x480\n");
							printf("\t-f  Display framerate on screen\n");
							return EXIT_SUCCESS;
							break;

						case 'r':
							if ((argc - 1) > argCounter)
							{
								argCounter++;

								// full screen
								if(strcmp(argv[argCounter], "fs") == 0)
								{
									fullscreen = true;
									argCounter++;
								}

								// 1080p
								else if(strcmp(argv[argCounter], "1920x1080") == 0)
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
							{
								fprintf(stderr, "Missing resolution argument.\n");
								return EXIT_FAILURE;
							}

							break;

						case 'f':
							displayFps = true;
							argCounter++;
							break;

						default:
							printf("%d\n", argCounter);
							printf("Invalid argument(s)\n");
							return EXIT_FAILURE;
							break;
					}
				}


			}
		}


	}

	// start the game here
        if(initsdl(fullscreen, &gameFonts, &deckImageData, &gameDenomButtonImageData, &gamePokerControlButtonImageData) == EXIT_FAILURE)  /* initialize sdl */
        	return EXIT_FAILURE;
		else
		{
			// timing variables
			int frameCounter = 0;
			int averageFps = 0;
			uint32_t startRunTicks = 0;
			uint32_t endRunTicks = 0;
			int runTicks = 0;
			float tickInterval = 1000.0 / MAX_FRAMERATE;

			commonGameStats.currentGameCash = 0.0;
			commonGameStats.currentGame = JACKS_OR_BETTER;
			commonGameStats.currentDenom = QUARTER;

			srand(time(NULL));
			inithand(hand, 5);
			
			// gameHeldText:  Generates textures and calculations for game held text.
			if (gameHeldText(&gameFonts))
				return EXIT_FAILURE;
					
			while (event.type != SDL_QUIT)
			{
				bool handState = FIRST_HAND;
				
				// get current ticks
				startRunTicks = SDL_GetTicks();
				runTicks = runTicks + (startRunTicks - endRunTicks);
				
				// calculate average fps
				averageFps = (int) (frameCounter / (startRunTicks / 1000.0));

				// poll loop for events, mouse ,or keyboard input.  Loop clears all events before continuing
				handState = getEvents(&commonGameStats, &event, hand, &intBetLevel, &gamePokerControlButtonImageData, &deckImageData);
							
				// frame rate limiting for display functions.  Used instead of vsync limiting
				if (runTicks > tickInterval)
				{
					// Set background color to blue and clear the screen of previous garbage.
					SDL_SetRenderDrawColor(mainWindowRenderer, 0, 0, 255, 0);
					SDL_RenderClear(mainWindowRenderer);
														
					//gameFpsText: returns true on failure.  Displays game fps on the screen.
					if (displayFps == true && !gameFpsText(averageFps, &gameFonts))
						SDL_RenderCopy(mainWindowRenderer, gameFonts.gameFpsTextTexture, NULL, &gameFonts.gameFpsTextDest);
														
					// Depending on what game is being played.  Render the correct graphical selection.
					switch (commonGameStats.currentGame)
					{
						case MAIN_MENU:
							break;
						case JACKS_OR_BETTER:
							JacksOrBetterRender(hand, &gameFonts, &deckImageData, &gameDenomButtonImageData, &gamePokerControlButtonImageData, handState, commonGameStats.currentGameCash, intBetLevel, commonGameStats.currentDenom);
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
	closedenombuttons(&gameDenomButtonImageData);
	closepokercontrolbuttons(&gamePokerControlButtonImageData);
	closesdl();

	return EXIT_SUCCESS;
}

/* initsdl:  Start up SDL */
int initsdl(bool fullscreen ,struct fonts *gameFonts, struct fiveCardDeckImageData *deckImageData, struct gameDenomButtonImageData *gameDenomButtonImageData, struct gamePokerControlButtonImageData *gamePokerControlButtonImageData)
{
	int imageFlags = IMG_INIT_PNG;

	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "SDL unable to initialize: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	else
	{
		if((IMG_Init(imageFlags) & imageFlags) != imageFlags)
		{
			fprintf(stderr, "SDL unable to initialize IMG_Init: %s\n", IMG_GetError());
			return EXIT_FAILURE;
		}
		else
		{
			mainWindow = SDL_CreateWindow("Video Poker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, intWindowWidth, intWindowHeight, SDL_WINDOW_SHOWN);
		}
	}

	if(mainWindow == NULL)
	{
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	else
	{
		// main window has been created.  We can modifiy it here after we verify its been created.
		SDL_SetWindowBordered(mainWindow, SDL_FALSE);

		// forumulate full screen
		if (fullscreen == true)
		{
			SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

			SDL_DisplayMode currentDisplayMode;
			if (SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(mainWindow), &currentDisplayMode))
			{
				fprintf(stderr, "Couldn't get current display mode: %s\n", SDL_GetError());
				return EXIT_FAILURE;
			}
			else
			{
				intWindowWidth = currentDisplayMode.w;
				intWindowHeight = currentDisplayMode.h;
			}
				

		}

		// create main window surface
		mainWindowSurface = SDL_GetWindowSurface(mainWindow);
	}

	// check to see if main window surface was created
	if(mainWindowSurface == NULL)
	{
		fprintf(stderr, "Window surface could not be created: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	else
		mainWindowRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

	if(mainWindowRenderer == NULL)
	{
		fprintf(stderr, "SDL could not create renderer: %s\n", SDL_GetError());
 		return EXIT_FAILURE;
	}

	/* Error checking for loading the texture deck */
	if(loadDeck(deckImageData))
		return EXIT_FAILURE;

	if(TTF_Init() == -1)
	{
		fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	if(loadFonts(gameFonts))
	{
		fprintf(stderr, "Failure to load game fonts.\n");
		return EXIT_FAILURE;
	}

	if(loaddenombuttons(gameDenomButtonImageData))
	{
		fprintf(stderr, "Failure to load game buttons.\n");
		return EXIT_FAILURE;
	}

	if (loadpokercontrolbuttons(gamePokerControlButtonImageData))
	{
		fprintf(stderr, "Failure to load poker control buttons.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
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

// loadDeck:  Load deck of card images into memory.
int loadDeck(struct fiveCardDeckImageData *deckImageData)
{
	int suit, i, spaceWidth = 0;
	int cardResHeightCorrected;
	int cardResWidthCorrected;
	int cardHalf = 0.0;
	int spacingDistance;
	SDL_Surface *cards[5];

	// null the card surfaces
	for (suit = 0; suit < 5; suit++)
	{
		cards[suit] = NULL;
	}

	// load the cards into memory for manipulation
	cards[0] = NULL;
	cards[1] = IMG_Load("images/cardh.png");
	cards[2] = IMG_Load("images/cardd.png");
	cards[3] = IMG_Load("images/cardc.png");
	cards[4] = IMG_Load("images/cards.png");

	// Error loading card images
	for(suit = 1; suit < 5; suit++)
	{
		if(cards[suit] == NULL)
 		{
			printf("SDL could not load images: %s\n", IMG_GetError());
    		return EXIT_FAILURE;
    	}
	}

  	// Null the whole deck texture array
	for(suit = 0; suit < 5; suit++)
	{
		deckImageData->suitTexture[suit] = NULL;
	}

  	// convert the surface to comply with the screen 
  	for(suit = 1; suit < 5; suit++)
  	{
    		deckImageData->suitTexture[suit] = SDL_CreateTextureFromSurface(mainWindowRenderer, cards[suit]);
  	}

  	// Error check to see if deck texture was loaded into memory
  	for(suit = 1; suit < 5; suit++)
  	{
  		if(deckImageData->suitTexture[suit] == NULL)
		{
			printf("SDL could not load deck textures: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}
  	}

  	// free the function local surfaces
  	for(suit = 0; suit < 5; suit++)
  	{
    		SDL_FreeSurface(cards[suit]);
    		cards[suit] = NULL;
  	}

	// calculate the cards width and height corrected for set screen resolution.  0.7 is a correction factor since cards are made for 1920x1080 resolution.  Correction factor must result in whole number
	cardResWidthCorrected = ((intWindowWidth / 1920.0) * CARD_WIDTH) * 0.7;
	cardResHeightCorrected = ((intWindowHeight / 1200.0) * CARD_HEIGHT) * 0.72;
	
	// card spacing calculations
	cardHalf = cardResWidthCorrected / 2;
	spacingDistance = intWindowWidth / 7.4;

	// create output render coordinates dependent on screen resolution
	for(i = 0; i < 5; i++)
	{
		deckImageData->cardDest[i].y = intWindowHeight / 2;
		deckImageData->cardDest[i].w = cardResWidthCorrected;
		deckImageData->cardDest[i].h = cardResHeightCorrected;
	}

	deckImageData->cardDest[0].x = ((intWindowWidth / 2) - cardHalf) - (spacingDistance * 2);
	deckImageData->cardDest[1].x = ((intWindowWidth / 2) - cardHalf) - (spacingDistance * 1);
	deckImageData->cardDest[2].x = (intWindowWidth / 2) - cardHalf;
	deckImageData->cardDest[3].x = ((intWindowWidth / 2) - cardHalf) + (spacingDistance * 1);
	deckImageData->cardDest[4].x = ((intWindowWidth / 2) - cardHalf) + (spacingDistance * 2);

	// create coordinates for the cards from the image deck textures
    // first set element of the structure is ignored
	for(suit = 1; suit < 5; suit++)
		for(i = 0; i < 15; i++)
		{
			deckImageData->cardSource[suit].card[i].x = CARD_WIDTH * i;
			deckImageData->cardSource[suit].card[i].y = 0;
			deckImageData->cardSource[suit].card[i].w = CARD_WIDTH;
			deckImageData->cardSource[suit].card[i].h = CARD_HEIGHT;
		}
	return EXIT_SUCCESS;
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
