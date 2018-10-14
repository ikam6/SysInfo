#include <stdio.h>
#include <stdlib.h>
#include "openssl/sha.h"

int main(int argc, char *argv[])

{

    int i;
    const char var;
for (i=0;i<argc;i++)
{
 printf("argument %d: %s\n",i, argv[i]);
    if (argv[i] == "-f")
    {
      FILE *fichier = fopen ("fichier.txt","w");
      fprintf(fichier, "%s\n", fichier);
      if (fichier!=NULL)
      {
        fscanf(fichier,"%c", &var);

        fclose (fichier);
        printf("%c",var);
      }
    }


    if (argv[i] == "-t")
    {
      printf("cadeau");
    }

}


    return EXIT_SUCCESS;
  }
