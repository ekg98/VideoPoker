// dataStrings.c:  String data for various games.

#include "dataStrings.h"

struct vPokerStatusTableJacksOrBetterStrings* getvPokerStatusTableJacksOrBetterStrings(void)
{
	static const struct vPokerStatusTableJacksOrBetterStrings vPokerStatusTableJacksOrBetterStrings = {
		{"ROYAL FLUSH ··············",
		"STRAIGHT FLUSH ···········",
		"FOUR OF A KIND ···········",
		"FULL HOUSE ···············",
		"FLUSH ····················",
		"STRAIGHT ·················",
		"THREE OF A KIND ··········",
		"TWO PAIR ·················",
		"JACKS OR BETTER ··········"}
	};

	return &vPokerStatusTableJacksOrBetterStrings;
}