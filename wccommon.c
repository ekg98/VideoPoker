/* wccommon.c:  Winning Check Common functions.  This file contains common functions used to determine winners in a game of video poker */

#include "cards.h"

/* isflush:  Checks to see if a structure contains flush.  Returns the suit value of a flush or 0 if no flush was detected. */
int isflush(struct card *hand, int size)
{
	int i, prevCardSuit;

	prevCardSuit = hand[0].suit;

	for(i = 1; i < size; i++)			/* start at the second card */
	{
		if(hand[i].suit == prevCardSuit)	/* examine the previous cards suit and if it is equal to the current cards suit move on to the next card. */
		       ;
		else
			return 0;			/* if the current suit being checked was not equal to the last then return 0 */
	}

	return prevCardSuit;	
}

/* isstraight:  Checks to see if a structure contains a straight.  Returns 1 if its a straight or 0 if no straight was detected. */
int isstraight(struct card *hand, int size)
{
	int i, sequentialCards = 0;
	int table[15];

	for(i = 0; i < 15; i++)			/* initialize table */
		table[i] = 0;

	for(i = 0; i < size; i++)		/* populate the table with values from the various cards in the hand */
	{
		table[hand[i].value] += 1;

		if(hand[i].value == 14)		/* enable low ace too */
			table[1] += 1;
	}

	for(i = 0; i < 15; i++)			/* runs through table and detects sequential cards */
	{
		if(table[i] == 1)
			sequentialCards += 1;
		else
			sequentialCards = 0;

		if(sequentialCards == 5)	/* if found 5 sequential cards then exit function as true */
			return 1;
	}

	return 0;				/* no sequence found */
}
