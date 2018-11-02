#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "list.h"
#include "PrintInfo.h"

/////////////////////////////////////////////////////////////
// FUNCTION main
/////////////////////////////////////////////////////////////

int main (int argc, char *argv[]) {
int i;
int option_f= 0;
int IsOptionHere;
char c[]="ft:";
char buf[PATH_MAX -1];


while ((IsOptionHere = getopt(argc, argv, c))!= -1){
		switch (IsOptionHere){
			case 'f':
				option_f=1;
				printf("referencement des liens\n");
				printf("%d\n",option_f);
				break;
			default:
				option_f=0;
				printf("dereferencement des liens\n");
			break;
		}
	}
	printf("ici tout va bien\n");
if (option_f==1){
	printf("ici encore\n");
char* linkPath;

	for(i=1;i<argc-1;i++){
		printf("ici c'est cool\n");
		if (argv[i]!="-f"){

		if (linkPath=realpath(argv[i], buf)==NULL){
			list(argv[i]);
		}
	}



fprintf(stderr, "%s\n",linkPath );
	linkPath="rien";
}

}
/*
	if (argc == 2) {
		list(argv[1]);
		}
	else {
		printf("Rappel pour l'entrée : ./ultra-cp dossier ou fichier \n");
		exit(EXIT_FAILURE);
	}
*/
	return EXIT_SUCCESS;
}
