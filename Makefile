# Makefile for Video Poker project

vpoker : vpoker.o cards.o wccommon.o
	gcc -o vpoker vpoker.o cards.o wccommon.o -lSDL2 -lSDL2_image -lSDL2_ttf

vpokerdebug : debug.o cards.o wccommon.o
	gcc -o vpokerdebug debug.o cards.o wccommon.o

vpoker.o : vpoker.c cards.h wccommon.h sdlcards.h
	gcc -c vpoker.c -lSDL2 -lSDL2_image -lSDL2_ttf

debug.o : debug.c cards.h wccommon.h
	gcc -c debug.c

cards.o : cards.c cards.h
	gcc -c cards.c

wccommon.o : wccommon.c cards.h
	gcc -c wccommon.c

clean :
	rm vpoker vpoker.o cards.o wccommon.o

cleandebug :
	rm vpokerdebug debug.o cards.o wccommon.o
