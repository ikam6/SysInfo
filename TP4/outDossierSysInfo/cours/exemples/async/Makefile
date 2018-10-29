CC=gcc
CFLAGS=-Wall -g --pedantic -c

all: count_client count_server

count_client: count_client.o count_common.o 
	$(CC) -o count_client count_client.o count_common.o

count_client.o: count_client.c count_common.h
	$(CC) $(CFLAGS) -o count_client.o count_client.c 

count_common.o: count_common.c count_common.h
	$(CC) $(CFLAGS) -o count_common.o count_common.c 


count_server: count_server.o count_common.o
	$(CC) -o count_server count_server.o count_common.o

count_server.o: count_server.c count_common.h
	$(CC) $(CFLAGS) -o count_server.o count_server.c 


clean:
	rm -rf *o count_client count_server