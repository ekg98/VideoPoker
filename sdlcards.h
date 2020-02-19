// sdlcards.h:  Contains related information necessary with sdl card image data for video poker.

// struct of rects with each representing the individual card for the respective suitTexture.
struct cardSource {
	SDL_Rect card[15];
};

// fiveCardDeckImageData:  Contains deckImageData for five card poker game.
struct fiveCardDeckImageData {
	SDL_Texture* suitTexture[5];

	// you only need 5 destinations
	SDL_Rect cardDest[5];

	// there are 52 cards to pick from so there are a lot of sources in the image files
	struct cardSource cardSource[5];
};