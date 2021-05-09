// payouttables.c:  Functions to handle payout tables for various poker games.

#include "payouttables.h"

struct payoutTables * getPayoutTables(void)
{
	static const struct payoutTables payoutTables = { 
		// jacks or better
		{{250, 500, 750, 100, 4000},
		{50, 100, 150, 200, 250},
		{25, 50, 75, 100, 125},
		{9, 18, 27, 36, 45},
		{6, 12, 18, 24, 30},
		{4, 8, 12, 16, 20},
		{3, 6, 9, 12, 15},
		{2, 4, 6, 8, 10},
		{1, 2, 3, 4, 5}}
		// add more here
	};

	return &payoutTables;
}