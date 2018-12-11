#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define BUFFER_LEN 1024

int getargc(char* line){
	char **command = malloc(8 * sizeof(char *));
	char *separator = " ";
	char *argv;
	int index = 0;

	argv = strtok(line, separator);
	while (argv != NULL) {
			command[index] = argv;
			index++;

			argv = strtok(NULL, separator);
	}

	command[index] = NULL;
	return index;
}

char** getargv(char*line){
	    char **command = malloc(8 * sizeof(char *));
	    char *separator = " ";
	    char *argv;
	    int index = 0;

	    argv = strtok(line, separator);
	    while (argv != NULL) {
	        command[index] = argv;
	        index++;

	        argv = strtok(NULL, separator);
	    }

	    command[index] = NULL;
	    return command;
	}
