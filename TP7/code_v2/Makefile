# /*--------------------------------------------------------/
#     Code fait par :
#     Lienhard Alexia
#     et
#     Smiljkovic Marko
# /--------------------------------------------------------*/

CC=gcc
CFLAGS=-Wall -g --pedantic

all: shell_hell

jobs.o : jobs.c
	$(CC) $(CFLAGS) -c -o jobs.o jobs.c

parsing.o: parsing.c
	$(CC) $(CFLAGS) -c -o parsing.o parsing.c

builtin.o: builtin.c
	$(CC) $(CFLAGS) -c -o builtin.o builtin.c

shell_hell.o: shell_hell.c parsing.h builtin.h
	$(CC) $(CFLAGS) -c -o  shell_hell.o shell_hell.c  -D_POSIX_C_SOURCE=200809L

shell_hell: shell_hell.o builtin.o parsing.o jobs.o
	$(CC) $(CFLAGS) -o shell_hell shell_hell.o builtin.o parsing.o jobs.o


clean:
	rm -rf *.o shell_hell
