// Coordinates for button array on bottom of screen

int loadbuttons(struct gameButtonImageData*);
void closebuttons(struct gameButtonImageData*);

struct buttonCoordinates {
	SDL_Rect source[14];
};

struct gameButtonImageData {
	SDL_Texture* denomButtonSelectedTexture;
	SDL_Texture* denomButtonNotSelectedTexture;
	SDL_Rect denomButtonSource[5];
	SDL_Rect denomButtonDest;
};