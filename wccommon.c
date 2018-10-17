/* wccommon.c:  Winning Check Common functions.  This file contains common functions used to determine winners in a game of video poker */

#include "cards.h"

/* isflush:  Checks to see if structure is flush.  Returns the suit value of a flush or 0 if no flush was detected. */
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
