/* debug:  This program is used as a interim test of the functions useable in cards.c */

#include <stdio.h>
#include "cards.h"

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
		"",
		"",
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
		"A"
	};

	unhold(hand, 5);
	deal(hand, 5);


	for(i = 0; i < 5; i++)
	{
		printf("%s\t%s \t\t", value[hand[i].value], suit[hand[i].suit]);
		if(hand[i].hold == YES)
			printf("HELD\n", hand[i].hold);
		if(hand[i].hold == NO)
			printf("UNHELD\n", hand[i].hold);
	}

	return 0;
}
