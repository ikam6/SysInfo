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
	else if (argc > 2) {//si deux entrée -> si E1= fichier alors E2  =fichier si nouveau mais peut être dossier si existant
		//si plusieurs entrées alors dernier E_n = dossier
		// boucle pour recuperer tout les dossiers/fichiers sauf le dernier
		// qui sera le repertoire destination
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
