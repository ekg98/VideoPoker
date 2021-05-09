// sdlvpokerstatustable.h:  Header file for graphical table in video poker

// structure containing starting coordinates for each of the boxes in the vPokerStatusTable
struct vPokerStatusTableCoordinates {
	SDL_Rect largeBlackBox;
	SDL_Rect largeYellowBox;
	SDL_Rect blackBox[6];
	SDL_Rect blueBox[6];
};

// vPokerStatusTableBoxCalculations():  Performs calculations and applies them to the appropriate renderer for the colorful box at the top of a poker game.  Needs type of game and location of buttons at bottom for positioning.
bool vPokerStatusTableBoxCalculations(SDL_Renderer*, struct commonGameStats *,struct vPokerStatusTableCoordinates *, enum gametype, struct gamePokerControlButtonImageData*);

// vPokerStatusTableTextCalculations():  Performs calculations and applies them to the appropriate renderer for the text in the status table.
bool vPokerStatusTableTextCalculations(SDL_Renderer*, struct vPokerStatusTableCoordinates *,  enum gametype);

// vPokerStatusTableRenderer():  Renders the status table at the top of a poker game depending on game selected.
bool vPokerStatusTableRender(SDL_Renderer *, struct commonGameStats *, enum gametype, struct gamePokerControlButtonImageData*);

// setBoxColor():  Sets the box color for the correct bet level.
void setBoxColor(SDL_Renderer *, struct commonGameStats *, int intBox);

// loadvPokerStatusTableFonts():  Loads fonts into memory for vPokerStatusTable depending on what game is desired.
bool loadvPokerStatusTableFonts(struct fonts *, enum gametype);

// unloadvPokerStatusTableFonts():  Unloads fonts from memory for vPokerStatusTable.
bool unloadvPokerStatusTableFonts(struct fonts *);