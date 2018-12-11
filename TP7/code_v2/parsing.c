/*--------------------------------------------------------/
    Code fait par :
    Lienhard Alexia
    et
    Smiljkovic Marko
/--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "builtin.h"
#include "jobs.h"


#define BUFFER_LEN 1024


void lireUtilisateur()
{
	char line[BUFFER_LEN];  //get command line

	while(1){

		printf("(S)hell>> "); //print shell prompt

		if(!fgets(line, BUFFER_LEN, stdin))
			break;

		size_t length = strlen(line);

		// changing the last character in the line from newline to null :
		if (line[length - 1] == '\n'){
			line[length - 1] = '\0';
		}

		// Builtin command : control for exit line
		builtinExit(line);

		//Jobs process :
		jobs(length, line);
	}
}
