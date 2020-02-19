// events.c:  Handing events in video poker by ekg98

#include "cards.h"
#include "common.h"

// getEvents:  Get events for games
bool getEvents(enum gametype game, enum denomtype denom, SDL_Event *event, struct card *hand, float *floatCash)
{
	static bool returnPrevPressed = false, onePrevHeld = false, twoPrevHeld = false, threePrevHeld = false, fourPrevHeld = false, fivePrevHeld = false, firstDeal = true ,heldEnabled = false, creditPrevPressed = false;
	static bool dealEnabled = true;

	int intBetLevel = 1;
	float floatBet = 0.25;

	while (SDL_PollEvent(event))
	{
		
		switch (game)
		{
			case JACKS_OR_BETTER:
			case DUCES_WILD:
				// return pressed
				if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && event->key.state == SDL_PRESSED)
				{
					
					// check bet level and enable deal.
					if (*floatCash >= (floatBet * intBetLevel))
						dealEnabled = true;

					// remove credits depending on type of denom used.
					if (firstDeal == true)
					{
						switch (denom)
						{
						case QUARTER:
							if (*floatCash >= 0.25)
								*floatCash -= 0.25;
							else
								dealEnabled = false;
							break;
						case HALF:
							if (*floatCash >= 0.50)
								*floatCash -= 0.50;
							else
								dealEnabled = false;
							break;
						case DOLLAR:
							if (*floatCash >= 1.00)
								*floatCash -= 1.00;
							else
								dealEnabled = false;
							break;
						case FIVEDOLLAR:
							if (*floatCash >= 5.00)
								*floatCash -= 5.00;
							else
								dealEnabled = false;
							break;
						case TENDOLLAR:
							if (*floatCash >= 10.00)
								*floatCash -= 10.00;
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

				break;
		}
	}
	
	return firstDeal;
}