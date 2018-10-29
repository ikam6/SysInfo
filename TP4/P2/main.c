#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "list.h"
#include "PrintInfo.h"
#include "copyDir.h"

#define MAX_SIZE 100
#define ONE_FILE 2
#define TWO_FILES 3


/*////////////////////////////////////////////////////////////
 FUNCTION main
////////////////////////////////////////////////////////////*/

	int main (int argc, char *argv[]) {
		int i;
		if (argc == 2) { //si une entrée-> afficher infos
			list(argv[1]);
			}
		else if (argc == TWO_FILES) {//si deux entrée -> si E1= fichier alors E2  =fichier si nouveau mais peut être dossier si existant
																//si plusieurs entrées alors dernier E_n = dossier
					 // boucle pour recuperer tout les dossiers/fichiers sauf le dernier
					 // qui sera le repertoire destination
					 for(int i=1;i<argc-1;i++){
							 printf("%i :: %s\n", i, argv[i]);
							 copy(argv[i], argv[argc-1]);
							 printInfo(argv[argc-1], argv[argc-1]);

	     // printf("Rappel pour l'entrée : ./ultra-cp dossier ou fichier \n");
	      //exit(EXIT_FAILURE);
	    }
}
	    return EXIT_SUCCESS;
}
