// sdlfonts.h:  Header file for sdl ttf fonts used in Video Poker by ekg98.

int loadFonts(void);
void closeText(SDL_Texture **);
bool gameStatus(struct card *, SDL_Rect *, SDL_Texture **);
