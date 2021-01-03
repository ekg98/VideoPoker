// Functions for dealing with the handling of the cards in video poker

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "cards.h"

// deal:  This function takes a structure of cards as input and randomly populates the deck with new cards.  This checks to see if the cards are held and if they are duplicates too.
void deal(struct card *hand, int size)
{
	int intCounter, dupcheck;
	bool duplicate = false;
	
	for(intCounter = 0; intCounter < size; intCounter++)
	{
		// if card is not held generate a new card on function call
		if(hand[intCounter].held == NO)
		{
			// generate cards
			hand[intCounter].value = 2 + (rand() / (RAND_MAX / 13));
			hand[intCounter].suit = 1 + (rand() / (RAND_MAX / 4));

			// check for out of bounds value
			while(hand[intCounter].value < 2 || hand[intCounter].value >= 15)
				hand[intCounter].value = 2 + (rand() / (RAND_MAX / 13));
						
			// check for out of bounds suit
			while(hand[intCounter].suit < 1 || hand[intCounter].suit >= 5)
				hand[intCounter].suit = 1 + (rand() / (RAND_MAX / 4));
		}
	}

	// cycle through the hand one card at a time.  This is the card that is being checked against the other cards
	for(intCounter = 0; intCounter < size; intCounter++)
	{
		// cycle through the hand checking the other cards against intCounter card flag them as duplicates
		for(dupcheck = 0; dupcheck < size; dupcheck++)
		{
			// Do not check card being checked
			if(dupcheck != intCounter)
				if(hand[intCounter].value == hand[dupcheck].value && hand[intCounter].suit == hand[dupcheck].suit)
				{
					duplicate = true;
					break;
				}
		}
	}

	if(duplicate == true)
	{
		deal(hand, size);
	}
}

/* undeck:  unhelds the hand and makes it useable */
void unheld(struct card *hand, int size)
{
	int i;

	for(i = 0; i < size; i++)
		hand[i].held = NO;
}

/* held:  helds a whole hand of cards.  Effectively making it read only */
void held(struct card *hand, int size)
{
	int i;

	for(i = 0; i < size; i++)
		hand[i].held = YES;
}

/* inithand:  Initializes a hand of cards */
int inithand(struct card *hand, int size)
{
	int i;

	for(i = 0; i < size; i++)
	{
		hand[i].value = 0;
		hand[i].suit = 0;
	}

	unheld(hand, size);

	return 0;
}
