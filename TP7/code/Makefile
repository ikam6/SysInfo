CC=gcc
CFLAGS=-Wall -g --pedantic -std=c99

all: shell_hell

parsing.o: parsing.c parsing.h
	$(CC) $(CFLAGS) -c -o parsing.o parsing.c

builtin.o: builtin.c builtin.h
	$(CC) $(CFLAGS) -c -o builtin.o builtin.c

shell_hell.o: shell_hell.c parsing.h builtin.h
	$(CC) $(CFLAGS) -c -o  shell_hell.o shell_hell.c -D_POSIX_C_SOURCE=199309L

shell_hell: shell_hell.o builtin.o
	$(CC) $(CFLAGS) -o shell_hell shell_hell.o builtin.o parsing.o


clean:
	rm -rf *.o shell_hell
