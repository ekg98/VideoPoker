/* debug:  This program is used as a interim test of the functions useable in cards.c */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "cards.h"
#include "wccommon.h"

int main()
{
	struct card hand[5];
	int i;

	char *suit[] = {
		"",
		"Hearts",
		"Diamonds",
		"Clubs",
		"Spades"
	};

	char *value[] = {
		"",		/* [0] not used currently */
		"",		/* [1] reserved for low ace */
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"10",
		"J",
		"Q",
		"K",
		"A"		/* [14] high ace */
	};

	srand(time(NULL));	/* seed the random number generator.  Need to break this out at a later date for more randomness */
	inithand(hand, 5);
	deal(hand, 5);


	for(i = 0; i < 5; i++)
	{
		printf("%s\t%s \t\t", value[hand[i].value], suit[hand[i].suit]);
		if(hand[i].hold == YES)
			printf("HELD\n", hand[i].hold);
		if(hand[i].hold == NO)
			printf("UNHELD\n", hand[i].hold);
	}

	printf("\n");
	printf("isroyalflush returns: %d\n", isroyalflush(hand, 5));
	printf("isstraightflush returns: %d\n", isstraightflush(hand, 5));
	printf("isfourkind returns: %d\n", isfourkind(hand, 5));
	printf("isfullhouse returns: %d\n", isfullhouse(hand, 5));
	printf("isflush returns: %d\n", isflush(hand, 5));
	printf("isstraight returns: %d\n", isstraight(hand, 5));
	printf("isthreekind returns: %d\n", isthreekind(hand, 5));
	printf("ispair returns: %d\n", ispair(hand, 5));
	printf("isjackorbetter returns: %d\n", isjackorbetter(hand, 5));
	return 0;
}
