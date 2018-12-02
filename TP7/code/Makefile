CC=gcc
CFLAGS=-Wall -g --pedantic -std=c99

all: main

syntaxAnalysis.o: syntaxAnalysis.c syntaxAnalysis.h
		$(CC) $(CFLAGS) -c -o syntaxAnalysis.o syntaxAnalysis.c -lreadline

main.o: main.c syntaxAnalysis.h
	$(CC) $(CFLAGS) -c -o  main.o main.c -lreadline

main: main.o syntaxAnalysis.o
	$(CC) $(CFLAGS) -o main main.o -lreadline


clean:
	rm -rf *.o main
