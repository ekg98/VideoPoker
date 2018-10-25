# Makefile for Video Poker project

vpokerdebug : debug.o cards.o wccommon.o
	gcc -o vpokerdebug debug.o cards.o wccommon.o

debug.o : debug.c cards.h wccommon.h
	gcc -c debug.c

cards.o : cards.c cards.h
	gcc -c cards.c

wccommon.o : wccommon.c cards.h
	gcc -c wccommon.c

clean :
	rm vpokerdebug debug.o cards.o wccommon.o
