/*--------------------------------------------------------/
     Code fait par :
     Lienhard Alexia
     et
     Smiljkovic Marko
/--------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "list.h"
#include "PrintInfo.h"
#include "copyDir.h"


/*////////////////////////////////////////////////////////////
FUNCTION main
////////////////////////////////////////////////////////////*/
int main (int argc, char *argv[]) {
	if (argc <= 1) {
		printf("Rappel pour l'exécution : \n");
		printf("./ultra-cp fichiers/dossiers [destinataire]\n");
		exit(EXIT_FAILURE);
	}
	else if (argc == 2) { //si une entrée-> afficher infos
		list(argv[1]);
	}
	else if (argc==3){
		copy(argv[1], argv[2]);

	}
	else if (argc > 3) {
		for(int i=1;i<argc-1;i++){
			// printf("%i :: %s\n", i, argv[i]);
			copying_rec(argv[i], argv[argc-1]);
			//printInfo(argv[i], argv[argc-1]);

			// printf("Rappel pour l'entrée : ./ultra-cp dossier ou fichier \n");
			//exit(EXIT_FAILURE);
		}
	}
	return EXIT_SUCCESS;
}
