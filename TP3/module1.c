#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "module2.h"

#define STRING_MAX 1000

int recuperation_donnees(int argc, char *argv[])
{
  //déclaration des variables
    int option = 0;
    int option_f= 0;
    int option_t= 0;
    int i;
    char c[]="ft:";
    char* Choix;
    int IsOptionHere = 0;
    char text[STRING_MAX] = "";
    

//récuperation des options d'entrées
    while ((IsOptionHere = getopt(argc, argv, c))!= -1){
        switch (IsOptionHere) {
            case 'f':
            option_f = 1;
            break;
            case 't':
            option_t = 1;
            Choix = optarg;//récupération de l'argument de digest
            break;
            default: /* '?' */
            fprintf(stderr, "Utilisation: %s [-f with file] string [-t with digest]\n",
            argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    //message d'erreur s'il n'y a pas d'arguments
    printf("f et t : %i %i\n", option_f, option_t );
    if (argc == 1) {
        fprintf(stderr, "Utilisation: %s [-f with file] string [-t with digest]\n",
        argv[0]);
        exit(EXIT_FAILURE);
    }


/*si on a les deux options, on doit lire le fichier
 et prendre l'argument de hash
  */
   if (option_f == 1 && option_t == 1){
        option = 22;

        //printf("si f et t : %s, %s\n", argv[2], argv[4]);
        //choixHash(option, argv[2], argv[4]);
        FILE* fichier = NULL;



          fichier = fopen(argv[2], "r");
          if (fichier != NULL){
            fgets(text, STRING_MAX, fichier);
            fclose(fichier);
          }
      else
       {
        printf("Impossible d'ouvrir le fichier %s\n", argv[2]);
        exit(EXIT_FAILURE);
      }


        printf("%s", text);
        calculHash(text, argv[4]);

}

//si on a que l'option de fichier on doit lire le fichier et faire le hash sha1
     else if (option_f == 1 && option_t == 0){
        option = 21;
        //printf("si f : %s\n", argv[2]);
        //choixHash(option, argv[2], "sha1");
        FILE* fichier = NULL;
        char text[STRING_MAX] = "";

        fichier = fopen(argv[2], "r");
        if (fichier != NULL){
            fgets(text, STRING_MAX, fichier);
            fclose(fichier);
        }
        else {
            printf("Impossible d'ouvrir le fichier %s\n", argv[2]);
            exit(EXIT_FAILURE);
        }
        printf("%s\n", text);

        calculHash(text, "sha1");
      }
     else if (option_f == 0 && option_t == 1){
        option = 12;
        //choixHash(option, argv[1], argv[3]);
        calculHash(argv[3], argv[2]);
    } else if (option_f == 0 && option_t == 0){
        option = 11;
        //choixHash(option, argv[1], "sha1");
        calculHash(argv[1], "sha1");
    } else {
        option = 0;
    }

    return option;
}
