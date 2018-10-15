#include <stdio.h>
#include <stdlib.h>

// int main()
// {
// 	printf("Hello, World!\n");
// 	return 0;
// }


#include "module1.h"
#include "module2.h"


#define STRING_MAX 30


int main(int argc, char const *argv[]) {
	int optionFichier = 10;
	int optionDigest = 21;
	char text[] = "Hello World";
	char digest[] = "md7";

	printf("Le text est : %s\n", text);
	printf("Le digest est : %s\n", digest);
	printf("-f est : %i\n", optionFichier);
	printf("-t est : %i\n", optionDigest);
	
	choixHash(optionFichier, optionDigest, text, digest);

	return 0;
}
