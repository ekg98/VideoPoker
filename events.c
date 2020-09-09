// events.c:  Handing events in video poker by ekg98

#include "cards.h"
#include "common.h"
#include "jobpayout.h"
#include "sdlbuttons.h"
#include "sdlcards.h"

extern int intWindowWidth;
extern int intWindowHeight;

// getEvents:  Get events for games
bool getEvents(struct commonGameStats* commonGameStats, SDL_Event *event, struct card *hand, int *intBetLevel, struct gamePokerControlButtonImageData* gamePokerControlButtonImageData, struct fiveCardDeckImageData* gamePokerDeckImageData)
{
	static bool returnPrevPressed = false, onePrevHeld = false, twoPrevHeld = false, threePrevHeld = false, fourPrevHeld = false, fivePrevHeld = false, firstDeal = true ,heldEnabled = false, creditPrevPressed = false;
	static bool dealEnabled = true;
	static bool betPrevPressed = false;
	static bool leftMouseButtonPrevPressed = false;

	static bool inButtonOne = false, inButtonTwo = false, inButtonThree = false, inButtonFour = false, inButtonFive = false, inButtonSix = false;

	static bool dealRequested = false;

	static float floatBet = 0.25;
	
	// mouse variables		
	float PokerControlButtonResWidthCorrected = 0.0;
	float PokerControlButtonResHeightCorrected = 0.0;
	float cardResWidthCorrected = 0.0;
	float cardResHeightCorrected = 0.0;

	// more bullshit needs corrected
	PokerControlButtonResWidthCorrected = ((intWindowWidth / 1920.0) * POKER_CONTROL_BUTTON_WIDTH);
	PokerControlButtonResHeightCorrected = ((intWindowHeight / 1280.0) * POKER_CONTROL_BUTTON_HEIGHT);
	
	// this is bullshit needs corrected
	cardResWidthCorrected = ((intWindowWidth / 1920.0) * 350) * 0.7;
	cardResHeightCorrected = ((intWindowHeight / 1200.0) * 500) * 0.72;

	// event loop.  Some events are always avaible.  Check bottom.
	while (SDL_PollEvent(event))
	{

		// get mouse x and y data regardless of game being played.
		if(event->type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&commonGameStats->mouseX, &commonGameStats->mouseY);

		// switch determines what game is being played and determines what it does with events.
		switch (commonGameStats->currentGame)
		{
			case JACKS_OR_BETTER:
			case DUCES_WILD:
			
				// set floatBet depending on denom value.  This ensures floatBet has the correct value to later determine if in a poker game you have enough credits to play.
				switch (commonGameStats->currentDenom)
				{
				case QUARTER:
					floatBet = 0.25;
					break;
				case HALF:
					floatBet = 0.50;
					break;
				case DOLLAR:
					floatBet = 1.00;
					break;
				case FIVEDOLLAR:
					floatBet = 5.00;
					break;
				case TENDOLLAR:
					floatBet = 10.00;
					break;
				default:
					floatBet = 0.25;
					break;
				}

				// mouse events for poker
				// Determine if you are inside one of the buttons on the screen
				if (event->type == SDL_MOUSEMOTION)
				{
					// poker control buttons
					if (IsInButton(commonGameStats, gamePokerControlButtonImageData->pokerControlButtonDest[0], PokerControlButtonResHeightCorrected, PokerControlButtonResWidthCorrected))
						commonGameStats->inButton = BUTTON_ONE;
					else if (IsInButton(commonGameStats, gamePokerControlButtonImageData->pokerControlButtonDest[1], PokerControlButtonResHeightCorrected, PokerControlButtonResWidthCorrected))
						commonGameStats->inButton = BUTTON_TWO;
					else if (IsInButton(commonGameStats, gamePokerControlButtonImageData->pokerControlButtonDest[2], PokerControlButtonResHeightCorrected, PokerControlButtonResWidthCorrected))
						commonGameStats->inButton = BUTTON_THREE;
					else if (IsInButton(commonGameStats, gamePokerControlButtonImageData->pokerControlButtonDest[3], PokerControlButtonResHeightCorrected, PokerControlButtonResWidthCorrected))
						commonGameStats->inButton = BUTTON_FOUR;
					else if (IsInButton(commonGameStats, gamePokerControlButtonImageData->pokerControlButtonDest[4], PokerControlButtonResHeightCorrected, PokerControlButtonResWidthCorrected))
						commonGameStats->inButton = BUTTON_FIVE;
					else if (IsInButton(commonGameStats, gamePokerControlButtonImageData->pokerControlButtonDest[5], PokerControlButtonResHeightCorrected, PokerControlButtonResWidthCorrected))
						commonGameStats->inButton = BUTTON_SIX;
					else if (IsInButton(commonGameStats, gamePokerDeckImageData->cardDest[0], cardResHeightCorrected, cardResWidthCorrected))
						commonGameStats->inButton = CARD_ONE;
					else if (IsInButton(commonGameStats, gamePokerDeckImageData->cardDest[1], cardResHeightCorrected, cardResWidthCorrected))
						commonGameStats->inButton = CARD_TWO;
					else if (IsInButton(commonGameStats, gamePokerDeckImageData->cardDest[2], cardResHeightCorrected, cardResWidthCorrected))
						commonGameStats->inButton = CARD_THREE;
					else if (IsInButton(commonGameStats, gamePokerDeckImageData->cardDest[3], cardResHeightCorrected, cardResWidthCorrected))
						commonGameStats->inButton = CARD_FOUR;
					else if (IsInButton(commonGameStats, gamePokerDeckImageData->cardDest[4], cardResHeightCorrected, cardResWidthCorrected))
						commonGameStats->inButton = CARD_FIVE;
					else
						commonGameStats->inButton = NONE;
				}

				// Determine what to do if you pressed a left mouse button
				if (event->button.button == SDL_BUTTON_LEFT && leftMouseButtonPrevPressed == false)
				{
					leftMouseButtonPrevPressed = true;
					
					// BUTTON_SIX is deal button
					switch (commonGameStats->inButton)
					{
						case BUTTON_ONE:
							break;
						case BUTTON_TWO:
							break;
						case BUTTON_THREE:
							break;
						case BUTTON_FOUR:
							break;
						case BUTTON_FIVE:
							break;
						case BUTTON_SIX:
							dealRequested = true;
							break;
						case CARD_ONE:
							if (heldEnabled == true)
							{
								if (onePrevHeld == false)
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
							break;
						case CARD_TWO:
							if (heldEnabled == true)
							{
								if (twoPrevHeld == false)
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
							break;
						case CARD_THREE:
							if (heldEnabled == true)
							{
								if (threePrevHeld == false)
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
							break;
						case CARD_FOUR:
							if (heldEnabled == true)
							{
								if (fourPrevHeld == false)
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
							break;
						case CARD_FIVE:
							if (heldEnabled == true)
							{
								if (fivePrevHeld == false)
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
							break;
						default:
							dealRequested = false;
							break;
					}
				}

				// Enable deal request if you pressed return
				if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && returnPrevPressed == false)
				{
					returnPrevPressed = true;
					dealRequested = true;
				}

				// deal request handling
				if (dealRequested == true)
				{
					// Ensure that enough credits are available to deal the cards and then enable deal.
					if (commonGameStats->currentGameCash >= (floatBet * (*intBetLevel)))
						dealEnabled = true;
					else
						dealEnabled = false;
					
					
					// first deal.  Unheld all cards and reset held key states
					if (dealRequested == true && dealEnabled == true && firstDeal == true)
					{
						// reset held key states
						onePrevHeld = false;
						twoPrevHeld = false;
						threePrevHeld = false;
						fourPrevHeld = false;
						fivePrevHeld = false;
						heldEnabled = true;

						// remove credits depending on type of denom and bet level used. 
						switch (commonGameStats->currentDenom)
						{
						case QUARTER:
							commonGameStats->currentGameCash -= 0.25 * (*intBetLevel);
							break;
						case HALF:
							commonGameStats->currentGameCash -= 0.50 * (*intBetLevel);
							break;
						case DOLLAR:
							commonGameStats->currentGameCash -= 1.00 * (*intBetLevel);
							break;
						case FIVEDOLLAR:
							commonGameStats->currentGameCash -= 5.00 * (*intBetLevel);
							break;
						case TENDOLLAR:
							commonGameStats->currentGameCash -= (10.00 * (*intBetLevel));
							break;
						}
						
						// unheld and deal cards
						unheld(hand, 5);
						deal(hand, 5);
						firstDeal = false;
						dealRequested = false;
						printf("Good Luck!\n");
					}
					// second deal
					if (dealRequested == true && firstDeal == false)
					{
						// deal cards that are not held
						deal(hand, 5);
						JacksOrBetterPayout(hand, *intBetLevel, &commonGameStats->currentGameCash, commonGameStats->currentDenom);
						firstDeal = true;
						heldEnabled = false;
						dealRequested = false;
						printf("Game Over!\n");
					}
					
					// If no condition is met for a proper deal deny the request for a deal.  This prevents automatic dealing if out of credits and the deal button was previously pressed to request a deal
					if (dealRequested == true)
						dealRequested = false;
				}
								
				// first card held logic
				if (heldEnabled == true && event->key.keysym.scancode == SDL_SCANCODE_1 && event->key.state == SDL_PRESSED)
				{
					if (onePrevHeld == false)
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
				if (heldEnabled == true && event->key.keysym.scancode == SDL_SCANCODE_2 && event->key.state == SDL_PRESSED)
				{
					if (twoPrevHeld == false)
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
				if (heldEnabled == true && event->key.keysym.scancode == SDL_SCANCODE_3 && event->key.state == SDL_PRESSED)
				{
					if (threePrevHeld == false)
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
				if (heldEnabled == true && event->key.keysym.scancode == SDL_SCANCODE_4 && event->key.state == SDL_PRESSED)
				{
					if (fourPrevHeld == false)
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
				if (heldEnabled == true && event->key.keysym.scancode == SDL_SCANCODE_5 && event->key.state == SDL_PRESSED)
				{
					if (fivePrevHeld == false)
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

				// bet level logic
				// b key pressed
				if (event->key.keysym.scancode == SDL_SCANCODE_B && event->key.state == SDL_PRESSED)
				{
					if (betPrevPressed == false)
					{
						betPrevPressed = true;

						if (*intBetLevel < 5)
							*intBetLevel += 1;
						else
							*intBetLevel = 1;
					}
				}

				// left mouse button released
				if (event->button.button == SDL_BUTTON_LEFT && event->type == SDL_MOUSEBUTTONUP)
					leftMouseButtonPrevPressed = false;

				// return released
				if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && event->key.state == SDL_RELEASED)
					returnPrevPressed = false;

				// bet level key released
				if (event->key.keysym.scancode == SDL_SCANCODE_B && event->key.state == SDL_RELEASED)
					betPrevPressed = false;

			break;
		}

		// credit logic
		// credits are allowed durring any time even in main menu.
		// credit c key pressed
		if (event->key.keysym.scancode == SDL_SCANCODE_C && event->key.state == SDL_PRESSED)
		{
			if (creditPrevPressed == false)
			{
				creditPrevPressed = true;
				commonGameStats->currentGameCash += 0.25;
			}
		}

		// credit key released
		if (event->key.keysym.scancode == SDL_SCANCODE_C && event->key.state == SDL_RELEASED)
			creditPrevPressed = false;

	}
	
	return firstDeal;
}