CC=gcc
CFLAGS=-Wall -g --pedantic -std=c99

all: main socket

main.o: main.c sockets.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(CFLAGS) -c -o sockets.o sockets.c
main: main.o sockets.o
	$(CC) $(CFLAGS) -o main main.o
	$(CC) $(CFLAGS) -o sockets sockets.o
clean:
	rm -rf *.o main sockets
