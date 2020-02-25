// Jacks Or Better payout source file

#include "cards.h"
#include "common.h"
#include "wccommon.h"

// JacksOrBetterPayout:  Processes payouts for jacks or better game.
void JacksOrBetterPayout(struct card *hand, int intBetLevel, float *floatGameCash, enum denomtype denom)
{
	// payout table for jacks or better.  This is in credits.
	const int intJacksOrBetterPayoutTable[9][5] = {
		{250, 500, 750, 100, 4000},
		{50, 100, 150, 200, 250},
		{25, 50, 75, 100, 125},
		{9, 18, 27, 36, 45},
		{6, 12, 18, 24, 30},
		{4, 8, 12, 16, 20},
		{3, 6, 9, 12, 15},
		{2, 4, 6, 8, 10},
		{1, 2, 3, 4, 5,}
	};

	float floatDenomMultiplier = 0.0;

	// set denom multiplier based on denom used.
	switch (denom)
	{
	case QUARTER:
		floatDenomMultiplier = 0.25;
		break;
	case HALF:
		floatDenomMultiplier = 0.50;
		break;
	case DOLLAR:
		floatDenomMultiplier = 1.00;
		break;
	case FIVEDOLLAR:
		floatDenomMultiplier = 5.00;
		break;
	case TENDOLLAR:
		floatDenomMultiplier = 10.00;
		break;
	}

	// apply the payout for jacks or better.
	if (isroyalflush(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[0][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (isstraightflush(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[1][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (isfourkind(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[2][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (isfullhouse(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[3][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (isflush(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[4][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (isstraight(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[5][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (isthreekind(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[6][intBetLevel - 1] * floatDenomMultiplier;
	}
	else if (ispair(hand, 5) == 2)
	{
		*floatGameCash += intJacksOrBetterPayoutTable[7][intBetLevel - 1] * floatDenomMultiplier;
	}
	/*else if (isjackorbetter(hand, 5))
	{
		*floatGameCash += intJacksOrBetterPayoutTable[8][intBetLevel - 1] * floatDenomMultiplier;
	}*/
}
