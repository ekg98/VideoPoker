// Coordinates for button array on bottom of screen

int loadbuttons(struct gameButtonImageData*);
void closebuttons(struct gameButtonImageData*);

struct buttonCoordinates {
	SDL_Rect source[14];
};

struct gameButtonImageData {
	SDL_Texture* denomButtonSelectedTexture[5];
	SDL_Texture* denomButtonNotSelectedTexture[5];
	SDL_Rect denomButtonSource[5];
	SDL_Rect denomButtonDest;
};