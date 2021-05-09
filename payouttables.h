// payouttables.h:  Payout tables for various poker games

struct payoutTables {
	int intJacksOrBetter[9][5];
};

// getPayoutTables():  Initialize the list of payout tables in memory.
struct payoutTables * getPayoutTables(void);