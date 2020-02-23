// events.h: Header for event functions

// getEvents:  Function that grabs all program events.  Parses events depending on gametype.
bool getEvents(enum gametype, enum denomtype, SDL_Event*, struct card*, float*);