#include <stdio.h>
#include <stdlib.h>

void die(char *issue) {
  perror(issue);
  exit(EXIT_FAILURE);
}
void format (int argc,char *argv[]){
	if (argc != 4) {
    fprintf(stderr, "USAGE: %s <host> <port> <numBytes>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
}
