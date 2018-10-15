#include <stdio.h>
#include <stdlib.h>

#include "module1.h"

int main(int argc, char *argv[]) {
	// int option = 0;
	// char text[] = "Hello World";
	// char digest[] = "";

	//printf("argc %i\n", argc);
	// for (size_t i = 0; i < argc; i++) {
	// 	printf("argv %s\n", argv[i]);
	// }

	recuperation_donnees(argc, argv);
	//option = recuperation_donnees(argc, argv);
	// printf("Le text est : %s\n", text);
	// printf("Le digest est : %s\n", digest);
	// printf("-f est : %i\n", option);
	// choixHash(option, text, digest);

	return 0;
}
