/* cards.h:  Contains function prototypes and variables for a video poker game */

/* Card information */
struct card {
	int value;
	int suit;
	int held;
};

void deal(struct card *, int);
void unheld(struct card *, int);
void held(struct card *, int);
int inithand(struct card *, int);

enum cardsuits { HEARTS, DIAMONDS, CLUBS, SPADES, YES, NO };
