/* wccommon.c:  Winning Check Common functions.  This file contains common functions used to determine winners in a game of video poker */

#include "common.h"
#include "cards.h"
#include <stdlib.h>
#include <string.h>


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

/* isstraightflush:  Checks to see if a structure contains a straight flush.  Returns 1 if its a straight flush or 0 if none was detected. */
int isstraightflush(struct card *hand, int size)
{
	if(isstraight(hand, size) && isflush(hand, size))
		return 1;
	else
		return 0;
}

/* isfourkind:  Checks to see if a structure contains four of a kind.  Returns 1 if it contains four of a kind.  0 if none was detected. */
int isfourkind(struct card *hand, int size)
{
	int i;
	int table[15];

	for(i = 0; i < 15; i++)
		table[i] = 0;

	for(i = 0; i < size; i++)
		table[hand[i].value] += 1;

	for(i = 0; i < 15; i++)
	{
		if(table[i] == 4)
			return 1;
	}

	return 0;
}

/* isthreekind:  Checks to see if a structure contains three of a kind.  Returns 1 if it contains three of a kind.  0 if none was detected. */
int isthreekind(struct card *hand, int size)
{
	int intCounter = 0;
	int table[15];
	int tableCounter = 0;

	// initializing lookup table
	for(intCounter = 0; intCounter < 15; intCounter++)
		table[intCounter] = 0;

	for(intCounter = 0; intCounter < size; intCounter++)
		table[hand[intCounter].value] += 1;

	for(intCounter = 0; intCounter < 15; intCounter++)
	{
		if(table[intCounter] == 3)
			return 1;
	}
	return 0;
}

/* ispair:  Checks to see if a structure contains a pair.  Returns number of pairs if it contains a pair.  0 if none was detected. */
int ispair(struct card *hand, int size)
{
	int i, pairCounter = 0;
	int table[15];

	for(i = 0; i < 15; i++)
		table[i] = 0;

	for(i = 0; i < size; i++)
		table[hand[i].value] += 1;

	for(i = 0; i < 15; i++)
	{
		if(table[i] == 2)
			pairCounter += 1;
	}

	if(pairCounter >= 1)
		return pairCounter;
	else
		return 0;
}

/* isfullhouse:  Checks to see if a structure contains a full house.  Returns 1 if it contains a full house.  0 if none was detected. */
int isfullhouse(struct card *hand, int size)
{
	if(isthreekind(hand, size) && ispair(hand, size))
		return 1;
	else
		return 0;
}

/* isjackorbetter:  Checks to see if a structure contains a jack or better.  Returns 1 if it contains a jack or better.  0 if none was detected. */
int isjackorbetter(struct card *hand, int size)
{
	int i;
	int table[15];

	for(i = 0; i < 15; i++)
		table[i] = 0;

	for(i = 0; i < size; i++)
		table[hand[i].value] += 1;

	for(i = 11; i < 15; i++)
	{
		if(table[i] >= 1)
			return 1;
	}

	return 0;
}

/* isroyalflush:  Checks to see if a structure contains a royal flush.  Returns 1 if it contains a royal flush.  0 if none was detected. */
int isroyalflush(struct card *hand, int size)
{
	int i, isRoyal = NO;
	int table[15];

	for(i = 0; i < 15; i++)
		table[i] = 0;

	for(i = 0; i < size; i++)
		table[hand[i].value] += 1;

	if(table[10] == 1 && table[11] == 1 && table[12] == 1 && table[13] == 1 && table[14] == 1)
		isRoyal = YES;

	if(isRoyal == YES && isflush(hand, size))
		return 1;
	else
		return 0;
}

char *jacksOrBetterWinCheck(struct card *hand)
{
	int stringSize = 0;
	char *returnString = NULL;

	// royal flush check
	if(isroyalflush(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("ROYAL FLUSH")))
			strcpy(returnString, "ROYAL FLUSH");
	}
	else if(isstraightflush(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("STRAIGHT FLUSH")))
			strcpy(returnString, "STRAIGHT FLUSH");
	}
	else if(isfourkind(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("FOUR OF A KIND")))
			strcpy(returnString, "FOUR OF A KIND");
	}
	else if(isfullhouse(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("FULL HOUSE")))
			strcpy(returnString, "FULL HOUSE");
	}
	else if(isflush(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("FLUSH")))
			strcpy(returnString, "FLUSH");
	}
	else if(isstraight(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("STRAIGHT")))
			strcpy(returnString, "STRAIGHT");
	}
	else if(isthreekind(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("THREE OF A KIND")))
			strcpy(returnString, "THREE OF A KIND");
	}
	else if(ispair(hand, 5) == 2)
	{
		if(returnString = (char *) malloc(sizeof("TWO PAIR")))
			strcpy(returnString, "TWO PAIR");
	}
	else if(isjackorbetter(hand, 5))
	{
		if(returnString = (char *) malloc(sizeof("JACKS OR BETTER")))
			strcpy(returnString, "JACKS OR BETTER");
	}

	return returnString;
}

// jacksOrBetterWinCheckFree:  Frees pointer allocated by jacksOrBetterWinCheck
bool jacksOrBetterWinCheckFree(char *returnString)
{
	bool failStatus = true;

	if(returnString != NULL)
	{
		free(returnString);
		returnString = NULL;
		failStatus = false;
	}

	return failStatus;
}
