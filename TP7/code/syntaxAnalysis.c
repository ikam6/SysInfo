#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 64
#define TOK_DELIM " \t\r"

//read STDIN enter
char* line_reader(){
	char* buf;

	 buf = readline("monShell >>>> ");
	printf("enter 1 : %s\n", buf);
	// int cmp;
	// cmp = strcmp(buf, "exit");
	// printf("cmp : %d", cmp);
	return buf;
}
// split STDIN get the function call

char **split_line(char *line)
{
  int bufsize = BUFFERSIZE;
	int position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, " allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line,TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += BUFFERSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOK_DELIM);
  }
  tokens[position] = NULL;
	printf("%d\n",position );

  return tokens;
}
