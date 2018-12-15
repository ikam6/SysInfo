CC=gcc
CFLAGS=-Wall -g  -nostartfiles --pedantic -std=c99

all: cooker server

cooker.o: cooker.c
	$(CC) $(CFLAGS) -lpthread -c -o   cooker.o cooker.c  -lpthread

server.o: server.c
	$(CC) $(CFLAGS) -c -o  server.o server.c -lpthread

server: server.o
	$(CC) $(CFLAGS) -o server server.o -lpthread

cooker: cooker.o
	$(CC) $(CFLAGS) -o cooker cooker.o -lpthread

clean:
	rm -rf *.o cooker server
