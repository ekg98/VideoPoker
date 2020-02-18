// Video Poker:  Jacks or Better render functions
#include "common.h"
#include "cards.h"
#include "sdlfonts.h"

extern SDL_Renderer* mainWindowRenderer;

// JacksOrBetterRender:  Renders the whole graphical selection of Jacks Or Better to the renderer
void JacksOrBetterRender(struct card *hand, struct fonts *gameFonts)
{
	// gameTypeText: returns true on failure.  Displays game type text in lower left corner
	if (!gameTypeText(JACKS_OR_BETTER, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameTypeTextTexture, NULL, &gameFonts->gameTypeTextDest);

}