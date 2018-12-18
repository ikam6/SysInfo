# /*--------------------------------------------------------/
#     Code fait par :
#     Lienhard Alexia
#     et
#     Smiljkovic Marko
# /--------------------------------------------------------*/

CC=gcc
CFLAGS=-Wall -g  -nostartfiles --pedantic -std=c99

all: cooker server

cooker.o: cooker.c
	$(CC) $(CFLAGS) -lpthread -c -o   cooker.o cooker.c  -lpthread -lrt -D_POSIX_C_SOURCE=200809L

server.o: server.c
	$(CC) $(CFLAGS) -c -o  server.o server.c -lpthread -lrt

server: server.o
	$(CC) $(CFLAGS) -o server server.o -lpthread -lrt

cooker: cooker.o
	$(CC) $(CFLAGS) -o cooker cooker.o -lpthread -lrt -D_POSIX_C_SOURCE=200809L

clean:
	rm -rf *.o cooker server
