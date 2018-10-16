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

int recuperation_donnees(int argc, char *argv[])
{
    //déclaration des variables
    int option = 0;
    int option_f= 0;
    int option_t= 0;
    int i;
    int *sizeofchain=NULL;
    char c[]="ft:";
    char *arr=malloc(1000*sizeof(char));
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
    //printf("f et t : %i %i\n", option_f, option_t );
    if (argc == 1) {
        fprintf(stderr, "Utilisation: %s [-f with file] string [-t with digest]\n",
        argv[0]);
        exit(EXIT_FAILURE);
    }

    // si on a les 2 options -f et -t :
    if (option_f + option_t == 4){
        option = 22;
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

    //si on a que l'option de fichier -f :
    else if (option_f + option_t == 1){
        option = 21;
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

    // si on a que l'option de digest -t :
    else if (option_f + option_t == 3){
        option = 12;
        calculHash(argv[3], argv[2]);
    }

    // si on a aucune option :
    else if (option_f + option_t == 0){
        option = 11;
        for(i=0;i<argc-1;i++){
            strcat(arr,argv[i+1]);
            strcat(arr," ");
        }
        printf("%s\n",arr);
        calculHash(arr, "sha1");
        free(arr);
    }

    // par defaut
    else {
        option = 0;
    }

    return option;
}
