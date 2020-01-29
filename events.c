// events.c:  Handing events in video poker by ekg98

#include "cards.h"
#include "common.h"

void getEvents(SDL_Event *event, struct card *hand)
{
	static bool returnPrevPressed = false, onePrevHeld = false, twoPrevHeld = false, threePrevHeld = false, fourPrevHeld = false, fivePrevHeld = false, firstDeal = true ,heldEnabled = false;

	while (SDL_PollEvent(event))
	{
		// deal keyboard logic
		if (event->key.keysym.scancode == SDL_SCANCODE_RETURN && event->key.state == SDL_PRESSED)
		{
			// first deal.  Unheld all cards and reset held key states
			if (firstDeal == true && returnPrevPressed == false)
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
	}
}