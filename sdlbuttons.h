// Coordinates for button array on bottom of screen

int loaddenombuttons(struct gameDenomButtonImageData* gameDenomButtonImageData);
void closedenombuttons(struct gameDenomButtonImageData* gameDenomButtonImageData);
int loadpokercontrolbuttons(struct gamePokerControlButtonImageData* gamePokerControlButtonImageData);
void closepokercontrolbuttons(struct gamePokerControlButtonImageData* gamePokerControlButtonImageData);

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