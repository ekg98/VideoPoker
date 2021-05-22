// sdlfonts.h:  Header file for sdl ttf fonts used in Video Poker by ekg98.

int loadFonts(struct fonts *);
void closeText(struct fonts *, struct text *);
bool gameHeldText(struct fonts *);
bool gameStatusWinText(struct card *, struct fonts *);
bool gameTypeText(enum gametype, struct fonts *);
bool gameOverText(bool, struct fonts *);
bool gameFpsText(int, struct fonts *);
bool gameCashText(float , struct fonts*);
bool gameBetLevelText(int , struct fonts*);

// structure fonts:  Contains pointers to opened fonts.
struct fonts {

	TTF_Font* heldFont;
	SDL_Texture* heldTexture;
	SDL_Rect heldDest[5];

	TTF_Font* gameStatusWinFont;
	SDL_Texture* gameStatusWinTextTexture;
	SDL_Rect gameStatusWinTextDest;

	TTF_Font* gameTypeFont;
	SDL_Texture* gameTypeTextTexture;
	SDL_Rect gameTypeTextDest;

	TTF_Font* gameOverFont;
	SDL_Texture* gameOverTextTexture;
	SDL_Rect gameOverTextDest;

	TTF_Font* gameFpsFont;
	SDL_Texture* gameFpsTextTexture;
	SDL_Rect gameFpsTextDest;

	TTF_Font* gameCashFont;
	SDL_Texture* gameCashTextTexture;
	SDL_Rect gameCashTextDest;

	TTF_Font* gameBetLevelFont;
	SDL_Texture* gameBetLevelTextTexture;
	SDL_Rect gameBetLevelTextDest;
		
	bool vPokerStatusTableFontLoaded;
	TTF_Font* vPokerStatusTableFont;
	SDL_Texture* vPokerStatusTableTexture[6][10];
	SDL_Rect vPokerStatusTableText[6][10];
	SDL_Color vPokerStatusTableTextColor[6][10];

};

// various game strings
struct text {

	bool vPokerStatusTableStringsLoaded;
	char *vPokerStatusTableString[6][10];

};