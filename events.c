// events.c:  Handing events in video poker by ekg98

#include "cards.h"
#include "common.h"

// getEvents:  Get events for games
bool getEvents(enum gametype game, enum denomtype denom, SDL_Event *event, struct card *hand, float *floatCash)
{
	static bool returnPrevPressed = false, onePrevHeld = false, twoPrevHeld = false, threePrevHeld = false, fourPrevHeld = false, fivePrevHeld = false, firstDeal = true ,heldEnabled = false, creditPrevPressed = false;
	static bool dealEnabled = true;

	static int intBetLevel = 1;
	static float floatBet = 0.25;
	
	// set floatBet depending on denom value.  This ensures floatBet has the correct value to later determine if in a poker game you have enough credits to play.
	switch (game)
	{
	case JACKS_OR_BETTER:
	case DUCES_WILD:
		switch (denom)
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
		break;
	}
	
	// event loop.  Some events are always avaible.  Check bottom.
	while (SDL_PollEvent(event))
	{

		// switch determines what game is being played and determines what it does with events.
		switch (game)
		{
			case JACKS_OR_BETTER:
			case DUCES_WILD:
				// return pressed
				if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && event->key.state == SDL_PRESSED)
				{
					
					// Ensure that enough credits are available to deal the cards and then enable deal.
					if (*floatCash >= (floatBet * intBetLevel))
						dealEnabled = true;

					// remove credits depending on type of denom and bet level used.
					if (firstDeal == true)
					{
						switch (denom)
						{
						case QUARTER:
							if (*floatCash >= 0.25 * intBetLevel)
								*floatCash -= 0.25 * intBetLevel;
							else
								dealEnabled = false;
							break;
						case HALF:
							if (*floatCash >= 0.50 * intBetLevel)
								*floatCash -= 0.50 * intBetLevel;
							else
								dealEnabled = false;
							break;
						case DOLLAR:
							if (*floatCash >= 1.00 * intBetLevel)
								*floatCash -= 1.00 * intBetLevel;
							else
								dealEnabled = false;
							break;
						case FIVEDOLLAR:
							if (*floatCash >= 5.00 * intBetLevel)
								*floatCash -= 5.00 * intBetLevel;
							else
								dealEnabled = false;
							break;
						case TENDOLLAR:
							if (*floatCash >= 10.00 * intBetLevel)
								*floatCash -= (10.00 * intBetLevel);
							else
								dealEnabled = false;
							break;
						}
					}

					// first deal.  Unheld all cards and reset held key states
					if (dealEnabled == true && firstDeal == true && returnPrevPressed == false)
					{
						// reset held key states
						onePrevHeld = false;
						twoPrevHeld = false;
						threePrevHeld = false;
						fourPrevHeld = false;
						fivePrevHeld = false;
						heldEnabled = true;

						// unheld and deal cards
						unheld(hand, 5);
						deal(hand, 5);
						firstDeal = false;
						returnPrevPressed = true;
						printf("Good Luck!\n");
					}
					// second deal
					if (firstDeal == false && returnPrevPressed == false)
					{
						// deal cards that are not held
						deal(hand, 5);
						firstDeal = true;
						returnPrevPressed = true;
						heldEnabled = false;
						printf("Game Over!\n");
					}
				}

				// return released
				if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && event->key.state == SDL_RELEASED)
					returnPrevPressed = false;

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

				break;
		}

		// credits are allowed durring any time even in main menu.
		// credit pushed
		if (event->key.keysym.scancode == SDL_SCANCODE_C && event->key.state == SDL_PRESSED)
		{
			if (creditPrevPressed == false)
			{
				creditPrevPressed = true;

				switch (denom)
				{
				case QUARTER:
					*floatCash += 0.25;
					break;
				case HALF:
					*floatCash += 0.50;
					break;
				case DOLLAR:
					*floatCash += 1.00;
					break;
				case FIVEDOLLAR:
					*floatCash += 5.00;
					break;
				case TENDOLLAR:
					*floatCash += 10.00;
					break;
				}
			}
		}

		// credit released
		if (event->key.keysym.scancode == SDL_SCANCODE_C && event->key.state == SDL_RELEASED)
			creditPrevPressed = false;

	}
	
	return firstDeal;
}