// payouttables.h:  Payout tables for various poker games

struct payoutTable {
	int intJacksOrBetter[9][5];
};

// initPayoutTable():  Initialize the list of payout tables in memory.
struct payoutTable * getPayoutTables(void);