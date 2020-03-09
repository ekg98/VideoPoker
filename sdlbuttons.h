// configuration defines
#define DENOM_BUTTON_WIDTH	200
#define DENOM_BUTTON_HEIGHT	145
#define POKER_CONTROL_BUTTON_WIDTH	210
#define	POKER_CONTROL_BUTTON_HEIGHT	90

// Coordinates for button array on bottom of screen

int loaddenombuttons(struct gameDenomButtonImageData* gameDenomButtonImageData);
void closedenombuttons(struct gameDenomButtonImageData* gameDenomButtonImageData);
int loadpokercontrolbuttons(struct gamePokerControlButtonImageData* gamePokerControlButtonImageData);
void closepokercontrolbuttons(struct gamePokerControlButtonImageData* gamePokerControlButtonImageData);
bool IsInButton(struct commonGameStats* commonGameStats, SDL_Rect ButtonLocation, int ButtonHeight, int ButtonWidth);

// denom button data structure
struct gameDenomButtonImageData {
	SDL_Texture* denomButtonSelectedTexture;
	SDL_Texture* denomButtonNotSelectedTexture;
	SDL_Rect denomButtonSource[5];
	SDL_Rect denomButtonDest;
};

// poker game control button structure
struct gamePokerControlButtonImageData {
	SDL_Texture* pokerControlButtonTexture;
	SDL_Rect pokerControlButtonSource[6];
	SDL_Rect pokerControlButtonDest[6];
};