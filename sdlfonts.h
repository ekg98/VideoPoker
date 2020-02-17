// sdlfonts.h:  Header file for sdl ttf fonts used in Video Poker by ekg98.

int loadFonts(struct fonts *);
void closeText(struct fonts *, SDL_Texture **, SDL_Texture **, SDL_Texture **, SDL_Texture **);
bool gameHeldText(SDL_Rect [], SDL_Texture**, TTF_Font**);
bool gameStatusWinText(struct card *, SDL_Rect *, SDL_Texture **, TTF_Font **);
bool gameTypeText(enum gametype, SDL_Rect *, SDL_Texture **, TTF_Font **);
bool gameOverText(bool, SDL_Rect *, SDL_Texture **, TTF_Font **);
bool gameFpsText(int, SDL_Rect*, SDL_Texture**, TTF_Font **);

// structure fonts:  Contains pointers to opened fonts.
struct fonts {
	TTF_Font* heldFont;
	TTF_Font* gameStatusWinFont;
	TTF_Font* gameTypeFont;
	TTF_Font* gameOverFont;
	TTF_Font* gameFpsFont;
};