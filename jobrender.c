// Video Poker:  Jacks or Better render functions
#include "common.h"
#include "cards.h"
#include "sdlfonts.h"

extern SDL_Renderer* mainWindowRenderer;

// JacksOrBetterRender:  Renders the whole graphical selection of Jacks Or Better to the renderer
void JacksOrBetterRender(struct card *hand, struct fonts *gameFonts, bool handState)
{
	
	// gameTypeText: returns true on failure.  Displays game type text in lower left corner
	if (!gameTypeText(JACKS_OR_BETTER, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameTypeTextTexture, NULL, &gameFonts->gameTypeTextDest);

	// gameWinTextStatus: returns true on failure.  When no win is detected.  NULL causes problems with TTF_RenderText_Solid
	if (!gameStatusWinText(hand, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameStatusWinTextTexture, NULL, &gameFonts->gameStatusWinTextDest);

	//gameOverText: returns true on failure.  Displays game over text in lower right section of screen
	if (!gameOverText(handState, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameOverTextTexture, NULL, &gameFonts->gameOverTextDest);

	// draw held text on renderer
	if (hand[0].held == YES)
		SDL_RenderCopy(mainWindowRenderer, gameFonts->heldTexture, NULL, &gameFonts->heldDest[0]);
	if (hand[1].held == YES)
		SDL_RenderCopy(mainWindowRenderer, gameFonts->heldTexture, NULL, &gameFonts->heldDest[1]);
	if (hand[2].held == YES)
		SDL_RenderCopy(mainWindowRenderer, gameFonts->heldTexture, NULL, &gameFonts->heldDest[2]);
	if (hand[3].held == YES)
		SDL_RenderCopy(mainWindowRenderer, gameFonts->heldTexture, NULL, &gameFonts->heldDest[3]);
	if (hand[4].held == YES)
		SDL_RenderCopy(mainWindowRenderer, gameFonts->heldTexture, NULL, &gameFonts->heldDest[4]);

}