#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "listDir.h"
#include "PrintInfo.h"
#include "copyDir.c"

#define MAX_SIZE 100
#define ONE_FILE 2
#define TWO_FILES 3


/*////////////////////////////////////////////////////////////
 FUNCTION main
////////////////////////////////////////////////////////////*/

	int main (int argc, char *argv[]) {
		int i;
		if (argc == ONE_FILE) {
			 if(IsADirectory(argv[1])==1) {
					 listfile(argv[1]);
					 exit(EXIT_SUCCESS);
				 }
				 else if (IsADirectory(argv[1])==0){
	        	listDir(argv[1]);
					}
				else {
					perror(NULL);
				}
	 }

		else if (argc == TWO_FILES) {
			if (argc > 2){
					 // boucle pour recuperer tout les dossiers/fichiers sauf le dernier
					 // qui sera le repertoire destination
					 for(int i=1;i<argc-1;i++){
							 //printf("%i :: %s\n", i, argv[i]);
							 copyDir(argv[i], argv[argc-1]);//-2 car argc comence a 1 et argv a 0
					 }

	      printf("Rappel pour l'entrée : ./ultra-cp dossier ou fichier \n");
	      exit(EXIT_FAILURE);
	    }

	    return EXIT_SUCCESS;
}
