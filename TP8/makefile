CC=gcc
CFLAGS=-Wall -g --pedantic -std=c99

all: cooker server

cooker.o: cooker.c
	$(CC) $(CFLAGS) -c -o  cooker.o cooker.c

server.o: server.c
	$(CC) $(CFLAGS) -c -o  server.o server.c

server: server.o
	$(CC) $(CFLAGS) -o server server.o

cooker: cooker.o
	$(CC) $(CFLAGS) -o cooker cooker.o

clean:
	rm -rf *.o cooker server
