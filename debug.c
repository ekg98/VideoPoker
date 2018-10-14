#include <stdio.h>
#include "cards.h"

int main()
{
	struct card deck[5];
	int i;

	char *suit[4] = {
		"Heart",
		"Diamond",
		"Club",
		"Spade"
	};

	unhold(deck, 5);
	deal(deck, 5);


	for(i = 0; i < 5; i++)
	{
		printf("value = %d\t\tsuit = %s\t\t", deck[i].value, suit[deck[i].suit]);
		if(deck[i].hold == YES)
			printf("HELD\n", deck[i].hold);
		if(deck[i].hold == NO)
			printf("UNHELD\n", deck[i].hold);
	}


}
