#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "PrintInfo.h"

/////////////////////////////////////////////////////////////
// FUNCTION main
/////////////////////////////////////////////////////////////

int main (int argc, char *argv[]) {

	if (argc == 2) {
		list(argv[1]);
		}
	else {
		printf("Rappel pour l'entrée : ./ultra-cp dossier ou fichier \n");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
