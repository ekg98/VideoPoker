// sdlvpokerstatustable.h:  Header file for graphical table in video poker

// vPokerStatusTableBoxCalculations():  Performs calculations and applies them to the appropriate renderer for the colorful box at the top of a poker game.  Needs type of game and location of buttons at bottom for positioning.
bool vPokerStatusTableBoxCalculations(SDL_Renderer*, enum gametype, struct gamePokerControlButtonImageData*);

// vPokerStatusTableTextCalculations():  Performs calculations and applies them to the appropriate renderer for the text in the status table.
bool vPokerStatusTableTextCalculations(SDL_Renderer*, enum gametype);

// vPokerStatusTableRenderer():  Renders the status table at the top of a poker game depending on game selected.
bool vPokerStatusTableRender(SDL_Renderer *, enum gametype, struct gamePokerControlButtonImageData*);