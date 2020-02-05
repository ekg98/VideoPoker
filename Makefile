# Makefile for Video Poker project

vpoker : vpoker.o cards.o wccommon.o sdlfonts.o events.o
	gcc -o vpoker vpoker.o cards.o wccommon.o sdlfonts.o events.o -lSDL2 -lSDL2_image -lSDL2_ttf

debug : debug.o cards.o wccommon.o
	gcc -o vpokerdebug debug.o cards.o wccommon.o

vpoker.o : vpoker.c common.h cards.h wccommon.h sdlcards.h sdlfonts.h events.h
	gcc -c vpoker.c -lSDL2 -lSDL2_image -lSDL2_ttf

debug.o : debug.c cards.h wccommon.h
	gcc -c debug.c

cards.o : cards.c cards.h
	gcc -c cards.c

wccommon.o : wccommon.c common.h cards.h wccommon.h
	gcc -c wccommon.c

sdlfonts.o : sdlfonts.c common.h sdlfonts.h
	gcc -c sdlfonts.c

events.o : events.c common.h cards.h
	gcc -c events.c

clean :
	rm vpoker vpoker.o cards.o wccommon.o sdlfonts.o events.o debug.o