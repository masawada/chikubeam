CC=gcc
CFLAGS=-O

beam: beam.c
	$(CC) $(CFLAGS) -o chikubeam beam.c -lncurses
