#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "syntaxAnalysis.h"

#define BUFFERSIZE 64
#define TOK_DELIM " \t\r"


char* line_reader(){
	char* buf;

	 buf = readline("monShell >>>> ");
	printf("enter 1 : %s\n", buf);
	// int cmp;
	// cmp = strcmp(buf, "exit");
	// printf("cmp : %d", cmp);



	return buf;
}

char **split_line(char *line)
{
  int bufsize = BUFFERSIZE;
	int argc = 0;
  char **argv = malloc(bufsize * sizeof(char*));
  char *token;

  if (!argv) {
    fprintf(stderr, " allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line,TOK_DELIM);
  while (token != NULL) {
    argv[argc] = token;
		printf("%s\n", argv[argc]);
    argc++;

    if (argc >= bufsize) {
      bufsize += BUFFERSIZE;
      argv = realloc(argv, bufsize * sizeof(char*));
      if (!argv) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOK_DELIM);


  }

  argv[argc] = NULL;
	printf("%d\n",argc);


  return argv;
}


/*=====MAIN=====*/
int main(int argc, char* argv[]){

	char* buf="";
	while (strcmp(buf, "exit") != 0) {
			printf("buf : %s\n", buf);
			buf = line_reader();
			split_line(buf);
			printf ("j'ai split\n");

	}

}
