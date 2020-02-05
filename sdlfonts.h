// sdlfonts.h:  Header file for sdl ttf fonts used in Video Poker by ekg98.

int loadFonts(void);
void closeText(SDL_Texture **, SDL_Texture **, SDL_Texture **, SDL_Texture **);
bool gameStatusWinText(struct card *, SDL_Rect *, SDL_Texture **);
bool gameTypeText(enum gametype, SDL_Rect *, SDL_Texture **);
bool gameOverText(bool, SDL_Rect *, SDL_Texture **);
bool gameFpsText(int, SDL_Rect*, SDL_Texture**);