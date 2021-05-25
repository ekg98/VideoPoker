// dataStrings.c:  String data for various games.

#include "dataStrings.h"

struct vPokerStatusTableJacksOrBetterStrings* getvPokerStatusTableJacksOrBetterStrings(void)
{
	static const struct vPokerStatusTableJacksOrBetterStrings vPokerStatusTableJacksOrBetterStrings = {
		{"ROYAL FLUSH ииииииииииииии",
		"STRAIGHT FLUSH иииииииииии",
		"FOUR OF A KIND иииииииииии",
		"FULL HOUSE иииииииииииииии",
		"FLUSH ииииииииииииииииииии",
		"STRAIGHT иииииииииииииииии",
		"THREE OF A KIND ииииииииии",
		"TWO PAIR иииииииииииииииии",
		"JACKS OR BETTER ииииииииии"}
	};

	return &vPokerStatusTableJacksOrBetterStrings;
}