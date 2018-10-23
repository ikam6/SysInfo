/*--------------------------------------------------------/
    Code fait par :
    Lienhard Alexia
    et
    Smiljkovic Marko
/--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>


#include "module2.h"

#define STRING_MAX 1000

void recuperation_donnees(int argc, char *argv[])
{
    //déclaration des variables
    int option = 0;
    int option_f= 0;
    int option_t= 0;
    char* Choix;
    int options;
    char c[]="ft:";

    int *sizeofchain=NULL;



    int IsOptionHere = 0;
    char text[STRING_MAX] = "";

    //récuperation des options d'entrées
    while ((IsOptionHere = getopt(argc, argv, c))!= -1){
        switch (IsOptionHere) {
            case 'f':
            option_f = 1;
            break;
            case 't':
            option_t = 3;
            Choix = optarg; //récupération de l'argument de digest
            break;
            default: // si l'entree n'est pas correcte :
            fprintf(stderr, "Utilisation: %s [-f with file] string [-t with digest]\n",
            argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // message d'erreur s'il n'y a pas d'arguments :
    // pour debog : printf("f et t : %i %i\n", option_f, option_t );
    if (argc == 1) {
        fprintf(stderr, "Utilisation: %s [-f with file] string [-t with digest]\n",
        argv[0]);
        exit(EXIT_FAILURE);
    }
    options=option_f+option_t;
     return Choix;
  }

    // si on a les 2 options -f et -t :
    if (option_f + option_t == 4){
        //option = 22;
        // pour debog : bon à savoir sur argv[] :
        /*printf("argc %i\n", argc );
        for (size_t i = 0; i < argc; i++) {
            printf("argv[argc] %s\n", argv[i]);
        }*/

        // permet de recuperer tous les fichiers après -f :
        for(i=4;i<argc;i++){
            FILE* fichier = NULL;
            char text[STRING_MAX] = "";
            fichier = fopen(argv[i], "r");
            if (fichier != NULL){
                fgets(text, STRING_MAX, fichier);
                fclose(fichier);
            }
            else {
                printf("\nImpossible d'ouvrir le fichier %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            calculHash(text, argv[3]);
            printf("    %s\n", argv[i]);
        }
    }

    //si on a que l'option de fichier -f :
    else if (option_f + option_t == 1){
        //option = 21;
        // permet de recuperer tous les fichiers après -f :
        for(i=2;i<argc;i++){
            FILE* fichier = NULL;
            char text[STRING_MAX] = "";
            fichier = fopen(argv[i], "r");
            if (fichier != NULL){
                fgets(text, STRING_MAX, fichier);
                fclose(fichier);
            }
            else {
                printf("\nImpossible d'ouvrir le fichier %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            calculHash(text, "sha1");
            printf("    %s\n", argv[i]);
        }
    }

    // si on a que l'option de digest -t :
    else if (option_f + option_t == 3){
        //option = 12;
        // pour debog : bon à savoir sur argv[] :
        /*printf("argc %i\n", argc );
        for (size_t i = 0; i < argc; i++) {
            printf("argv[argc] %s\n", argv[i]);
        }*/

        // pour recuperer tout le message :
        for(i=3;i<argc;i++){
            strcat(arr,argv[i]);
            strcat(arr," ");
        }
        //pour debog : printf("%s\n",arr);
        calculHash(arr, argv[2]);
        printf("\n");
        free(arr);
    }

    // si on a aucune option :
    else if (option_f + option_t == 0){
        //option = 11;

        // pour recuperer tout le message :
        for(i=1;i<argc;i++){
            strcat(arr,argv[i]);
            strcat(arr," ");
        }
        //printf("%s\n",arr);
        calculHash(arr, "sha1");
        printf("\n");
        free(arr);
    }

    // par defaut (inutile)
    else {
        option = 0;
    }
    //return option;
}
