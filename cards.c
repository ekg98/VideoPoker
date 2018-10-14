/* Functions for dealing with the handling of the cards in video poker */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

/* deal:  This function takes a structure of cards as input and randomly populates the deck with new cards.  This checks to see if the cards are held and if they are duplicates too. */
void deal(struct card *deck, int size)
{
	int i, dupecheck;

	srand(time(0));

	for(i = 0; i < size; i++)
	{
		/* if card is not held generate a new card on function call */
		if(deck[i].hold == NO)
		{
			while((deck[i].value = rand() / (RAND_MAX / 13)) <= 1);
			
			while((deck[i].suit = rand() / (RAND_MAX / 4)) == 0);
		}
	}

	/* check for duplicate card */
	for(i = 0; i < size; i++)
	{
		for(dupecheck = 0; dupecheck < size; dupecheck++)		
		{
			if(dupecheck != i)
				if(deck[i].value == deck[dupecheck].value && deck[i].suit == deck[dupecheck].suit)
				{
					printf("Duplicate found card %d and %d.\n", i + 1, dupecheck + 1);	
				}
		}
	}
}

/* undeck:  unholds the deck and makes it useable */
void unhold(struct card deck[], int size)
{
	int i;

	for(i = 0; i < size; i++)
		deck[i].hold = NO;
}

/* hold:  holds a whole deck of cards.  Effectively making it read only */
void hold(struct card deck[], int size)
{
	int i;

	for(i = 0; i < size; i++)
		deck[i].hold = YES;
}
