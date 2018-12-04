CC=gcc
CFLAGS=-Wall -g --pedantic -std=c99

all: main

# parsing.o: parsing.c parsing.h
# 	$(CC) $(CFLAGS) -c -o parsing.o parsing.c

builtin.o: builtin.c builtin.h
	$(CC) $(CFLAGS) -c -o builtin.o builtin.c

main.o: main.c parsing.h builtin.h
	$(CC) $(CFLAGS) -c -o  main.o main.c

main: main.o builtin.o
	$(CC) $(CFLAGS) -o main main.o builtin.o


clean:
	rm -rf *.o main
