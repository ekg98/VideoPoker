// Video Poker:  Jacks or Better render functions
#include <stdio.h>
#include "common.h"
#include "cards.h"
#include "sdlfonts.h"
#include "sdlcards.h"
#include "sdlbuttons.h"
#include "sdlvpokerstatustable.h"

extern SDL_Renderer* mainWindowRenderer;

// JacksOrBetterRender:  Renders the whole graphical selection of Jacks Or Better to the renderer
void JacksOrBetterRender(struct commonGameStats *commonGameStats ,struct card *hand, struct fonts *gameFonts, struct text *gameText, struct fiveCardDeckImageData *deckImageData, struct gameDenomButtonImageData *gameDenomButtonImageData, struct gamePokerControlButtonImageData *gamePokerControlButtonImageData, bool handState, float floatGameCash, int intBetLevel, enum denomtype denom)
{
	// vPokerStatusTableRender:  Draws the status table on the top of the screen.
	if (vPokerStatusTableRender(mainWindowRenderer, commonGameStats, hand, gameFonts, gameText, JACKS_OR_BETTER, gamePokerControlButtonImageData))
	{
		fprintf(stderr, "Error:  Could not render Status table properly.\n");
		exit(EXIT_FAILURE);
	}

	// draw cards on renderer
	for (int intCounter = 0; intCounter < 5; intCounter++)
		SDL_RenderCopy(mainWindowRenderer, deckImageData->suitTexture[hand[intCounter].suit], &deckImageData->cardSource[hand[intCounter].suit].card[hand[intCounter].value], &deckImageData->cardDest[intCounter]);

	// gameTypeText: returns true on failure.  Displays game type text in lower left corner.
	if (!gameTypeText(JACKS_OR_BETTER, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameTypeTextTexture, NULL, &gameFonts->gameTypeTextDest); 

	// gameWinTextStatus: returns true on failure.  When no win is detected.  NULL causes problems with TTF_RenderText_Solid.
	if (!gameStatusWinText(hand, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameStatusWinTextTexture, NULL, &gameFonts->gameStatusWinTextDest);

	//gameOverText: returns true on failure.  Displays game over text in lower right section of screen.
	if (!gameOverText(handState, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameOverTextTexture, NULL, &gameFonts->gameOverTextDest); 

	//gameCashText: returns true on failure.  Displays game cash text in lower right section of screen.
	if (!gameCashText(floatGameCash, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameCashTextTexture, NULL, &gameFonts->gameCashTextDest);

	//gameBetLevelText: returns true on failure.  Displays game bet level text in middle section of screen.
	if (!gameBetLevelText(intBetLevel, gameFonts))
		SDL_RenderCopy(mainWindowRenderer, gameFonts->gameBetLevelTextTexture, NULL, &gameFonts->gameBetLevelTextDest);

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

	// render denom button based on denom value
	SDL_RenderCopy(mainWindowRenderer, gameDenomButtonImageData->denomButtonSelectedTexture , &gameDenomButtonImageData->denomButtonSource[denom], &gameDenomButtonImageData->denomButtonDest);

	// render poker control buttons.
	for (int intCounter = 0; intCounter < 6; intCounter++)
	{
		SDL_RenderCopy(mainWindowRenderer, gamePokerControlButtonImageData->pokerControlButtonTexture, &gamePokerControlButtonImageData->pokerControlButtonSource[intCounter], &gamePokerControlButtonImageData->pokerControlButtonDest[intCounter]);
	}
}