#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "listDir.h"
#include "PrintInfo.h"

#define MAX_SIZE 100


/////////////////////////////////////////////////////////////
// FUNCTION main
/////////////////////////////////////////////////////////////

	int main (int argc, char *argv[]) {

		if (argc == 2) {
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

		else {
	      printf("Rappel pour l'entrée : ./ultra-cp dossier ou fichier \n");
	      exit(EXIT_FAILURE);
	    }

	    return EXIT_SUCCESS;
}
