#include <stdio.h>
#include "cards.h"

int main()
{
	struct card deck[5];
	int i;

	unhold(deck, 5);
	deal(deck, 5);

	for(i = 0; i < 5; i++)
	{
		printf("value = %d\t\tsuit = %d\t\t", deck[i].value, deck[i].suit);
		if(deck[i].hold == 4)
			printf("HELD\n", deck[i].hold);
		if(deck[i].hold == 5)
			printf("UNHELD\n", deck[i].hold);
	}


}
