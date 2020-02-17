// sdlfonts.h:  Header file for sdl ttf fonts used in Video Poker by ekg98.

int loadFonts(struct fonts *);
void closeText(struct fonts *);
bool gameHeldText(SDL_Rect [], struct fonts *);
bool gameStatusWinText(struct card *, SDL_Rect *, struct fonts *);
bool gameTypeText(enum gametype, SDL_Rect *, struct fonts *);
bool gameOverText(bool, SDL_Rect *, struct fonts *);
bool gameFpsText(int, SDL_Rect*, struct fonts *);

// structure fonts:  Contains pointers to opened fonts.
struct fonts {

	TTF_Font* heldFont;
	SDL_Texture* heldTexture;

	TTF_Font* gameStatusWinFont;
	SDL_Texture* gameStatusWinTextTexture;

	TTF_Font* gameTypeFont;
	SDL_Texture* gameTypeTextTexture;

	TTF_Font* gameOverFont;
	SDL_Texture* gameOverTextTexture;

	TTF_Font* gameFpsFont;
	SDL_Texture* gameFpsTextTexture;
		
};