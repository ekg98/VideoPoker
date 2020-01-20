/* wccommon.h:  This file contains the function prototypes for Winning Check Common functions */

int isflush(struct card *, int);
int isstraight(struct card *, int);
int isstraightflush(struct card *, int);
int isfourkind(struct card *, int);
int isthreekind(struct card *, int);
int ispair(struct card *, int);
int isfullhouse(struct card *, int);
int isjackorbetter(struct card *, int);
int isroyalflush(struct card *, int);
char *jacksOrBetterWinCheck(struct card *);
bool jacksOrBetterWinCheckFree(char *);
