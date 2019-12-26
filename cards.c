/* Functions for dealing with the handling of the cards in video poker */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

/* deal:  This function takes a structure of cards as input and randomly populates the deck with new cards.  This checks to see if the cards are held and if they are duplicates too. */
void deal(struct card *hand, int size)
{
	int i, dupcheck, duplicate = NO;

	for(i = 0; i < size; i++)
	{
		/* if card is not held generate a new card on function call */
		if(hand[i].held == NO)
		{
			hand[i].value = 2 + (rand() / (RAND_MAX / 13));

			hand[i].suit = 1 + (rand() / (RAND_MAX / 4));
		}
	}

	/* check for duplicate cards */
	for(i = 0; i < size; i++)
	{
		for(dupcheck = 0; dupcheck < size; dupcheck++)
		{
			if(dupcheck != i)
				if(hand[i].value == hand[dupcheck].value && hand[i].suit == hand[dupcheck].suit)
				{
					duplicate = YES;
					break;
				}

		}
	}

	if(duplicate == YES)
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
