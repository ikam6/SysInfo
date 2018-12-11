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
#include "parsing.h"

int main(int argc, char* argv[])
{
	if (argc != 1){
		printf("To execute the (S)Hell you must enter : ./shell_hell\n");
		printf("Please start again with the right entry.\n");
		exit(EXIT_FAILURE);
	}
	printf("\n");
	printf("===================================================\n\n");
	printf ("\t\tWelcome in (S)Hell\n\n");
	printf("===================================================\n\n");

	lireUtilisateur();

	return 0;
}
