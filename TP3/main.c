#include <stdio.h>
#include <stdlib.h>

// int main()
// {
// 	printf("Hello, World!\n");
// 	return 0;
// }

extern "C" {
	#include "module1.h"
	#include "module2.h"
}

#define STRING_MAX 30

namespace {
	char option = "none",
	char text = "none";

	int calcul = 0;
}
int main(int argc, char const *argv[]) {
	option = recuperation_option();
	text = recuperation_text();

	calcul = calculhash();

	return 0;
}
