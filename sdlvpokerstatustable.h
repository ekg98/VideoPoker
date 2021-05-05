// sdlvpokerstatustable.h:  Header file for graphical table in video poker

// vPokerStatusTableBoxCalculations():  Performs calculations and applies them to the appropriate renderer for the colorful box at the top of a poker game.  Needs type of game and location of buttons at bottom for positioning.
bool vPokerStatusTableBoxCalculations(SDL_Renderer*, struct vPokerStatusTableCoordinates *, enum gametype, struct gamePokerControlButtonImageData*);

// vPokerStatusTableTextCalculations():  Performs calculations and applies them to the appropriate renderer for the text in the status table.
bool vPokerStatusTableTextCalculations(SDL_Renderer*, struct vPokerStatusTableCoordinates *,  enum gametype);

// vPokerStatusTableRenderer():  Renders the status table at the top of a poker game depending on game selected.
bool vPokerStatusTableRender(SDL_Renderer *, enum gametype, struct gamePokerControlButtonImageData*);

// structure containing starting coordinates for each of the boxes in the vPokerStatusTable
struct vPokerStatusTableCoordinates {
	SDL_Rect largeBlackBox;
	SDL_Rect largeYellowBox;
	SDL_Rect blackBox[6];
	SDL_Rect blueBox[6];
};