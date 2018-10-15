/* Functions for dealing with the handling of the cards in video poker */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

/* deal:  This function takes a structure of cards as input and randomly populates the deck with new cards.  This checks to see if the cards are held and if they are duplicates too. */
void deal(struct card *hand, int size)
{
	int i, dupecheck, dupe = NO;


	srand(time(0));

	for(i = 0; i < size; i++)
	{
		/* if card is not held generate a new card on function call */
		if(hand[i].hold == NO)
		{
			hand[i].value = 2 + (rand() / (RAND_MAX / 13));
			
			hand[i].suit = 1 + (rand() / (RAND_MAX / 4));
		}
	}

	/* check for duplicate cards */
	for(i = 0; i < size; i++)
	{
		for(dupecheck = 0; dupecheck < size; dupecheck++)		
		{
			if(dupecheck != i)
				if(hand[i].value == hand[dupecheck].value && hand[i].suit == hand[dupecheck].suit)
				{
					dupe = YES;	
				}
		}
	}

	/*if(dupe == YES)
		deal(hand, size);*/
}

/* undeck:  unholds the hand and makes it useable */
void unhold(struct card hand[], int size)
{
	int i;

	for(i = 0; i < size; i++)
		hand[i].hold = NO;
}

/* hold:  holds a whole hand of cards.  Effectively making it read only */
void hold(struct card hand[], int size)
{
	int i;

	for(i = 0; i < size; i++)
		hand[i].hold = YES;
}
