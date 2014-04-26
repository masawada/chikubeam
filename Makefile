CC=gcc
CFLAGS=-O

beam: beam.c beam.h
	$(CC) $(CFLAGS) -o chikubeam beam.c -lncurses
