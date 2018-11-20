CC=gcc
CFLAGS=-Wall -g --pedantic -std=c99

all: main

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

main: main.o
	$(CC) $(CFLAGS) -o main main.o

clean:
	rm -rf *.o main
