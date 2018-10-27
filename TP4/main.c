#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>  //snprintf
#include <errno.h>
#include <dirent.h>
#include <limits.h>  //PATH_MAX
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "listDir.h"
#include "PrintInfo.h"


#define MAX_SIZE 100

/////////////////////////////////////////////////////////////
// FUNCTION IsADirectory
/////////////////////////////////////////////////////////////

// TODO ca sert a rien la fonction IsADirectory... Il est deja dans listDir
// int IsADirectory ( const char* name)//test si c'est un repertoire
// {
//     DIR* directory= opendir(name);
//
//     if(directory!= NULL)//c'est un repertoire
//     {
//         closedir(directory);
//         return 0 ;
//     }
//
//     if(errno==ENOTDIR)//Erreur, ce n'est pas un repertoire
//     {
//         return 1;
//     }
//
//     return -1;//autre erreur
// }

static void listDir (const char *dirName){

    DIR *d = opendir(dirName);
    struct dirent *entry;
    const char *d_name;   //nom d'une entrée

    //En cas d'erreur d'ouverture
    if (! d) {
        fprintf(stderr, "Cannot open directory '%s': %s\n",
        dirName, strerror(errno));
        exit(EXIT_FAILURE);
    }

    //Boucle sur chaque entrée
    while( (entry = readdir(d)) != NULL ) {
        // Obtient le nom de l'entrée et affiche
        d_name = entry->d_name;
        printInfo(dirName, d_name);
        //Est-ce que 'entry' est un sous-répertoire
        if (entry->d_type & DT_DIR) {
            //Est-ce que 'entry' n'est pas '..' ou '.'
            if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                char path[PATH_MAX];
                //forme le nom du sous-répertoire et affiche
                int path_length = snprintf (path, PATH_MAX,"%s/%s",
                dirName, d_name);
                //printf("Dans la question if : %s\n", path);
                //Vérifie que le nom du sous-répertoire n'est pas trop long
                if (path_length >= PATH_MAX) {
                    fprintf(stderr, "Path length has got too long.\n");
                    exit(EXIT_FAILURE);
                }
                //Appel récursif
                //printInfo(dirName, d_name);
                listDir(path);
            }
        }
    } //while(1)
    //On ferme le répertoite
    if( closedir(d) ) {
        fprintf(stderr, "Could not close '%s': %s\n",
        dirName, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

/////////////////////////////////////////////////////////////
// FUNCTION copyDir
/////////////////////////////////////////////////////////////

static void copyDir (const char *dir_in, const char *dir_out){
    DIR *d_in = opendir(dir_in);
    DIR *d_out = opendir(dir_out);
    struct dirent *entry;
    const char *d_name;   //nom d'une entrée
    int err;

    //En cas d'erreur d'ouverture
    if (! d_in) {
        fprintf(stderr, "Cannot open directory '%s': %s\n",
        dir_in, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (! d_out) {
        printf("On va creer un dossier %s\n", dir_out);
        mkdir(dir_out, 0777);
        printf("path dirOut: %s\n", dir_out);

        if (d_out < 0) {
            int savedError = errno;
            closedir(d_in);
            fprintf(stderr, "Could not open directory %s: %s\n",
            dir_out, strerror(savedError));
        }
    }
    printf("On a le dossier %s et on peut copier les %s dedans \n", dir_out, dir_in);
    //printf( (link(dir_in, dir_out) == 0) ? "Succes\n" :"Fail\n" );


    printf("dirIn %s, drirOut: %s\n", dir_in, dir_out);

    while( (entry = readdir(d_in)) != NULL ) {
        // Obtient le nom de l'entrée et affiche
        d_name = entry->d_name;
        //Est-ce que 'entry' est un sous-répertoire
        if (entry->d_type & DT_DIR) {
            //Est-ce que 'entry' n'est pas '..' ou '.'
            if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                char path[PATH_MAX];
                //forme le nom du sous-répertoire et affiche
                int path_length = snprintf (path, PATH_MAX,"%s/%s",
                dir_in, d_name);
                //printf("Dans la question if : %s\n", path);
                //Vérifie que le nom du sous-répertoire n'est pas trop long
                if (path_length >= PATH_MAX) {
                    fprintf(stderr, "Path length has got too long.\n");
                    exit(EXIT_FAILURE);
                }
                //Appel récursif
                //printInfo(dirName, d_name);
                copyDir(path, dir_out);
                printf("Hello\n" );
            }
        }
        err = 1; //TODO aucune idee de ce machin
        int n = err;
        if (n==0) break;
        char pathDir[]="";
        strcat(pathDir, dir_in);
        strcat(pathDir, "/");
        strcat(pathDir, d_name);
        printf("Notre nouveau path est %s\n", pathDir);

        int fd = open(pathDir, O_CREAT, 0777);

        if (fd < 0){
            int savedError = errno;
            fprintf(stderr, "Could not open directory %s: %s\n",
            pathDir, strerror(savedError));
        }

        err = write(fd, d_name, n);
        if (err == -1){
            printf("Error writing file.\n" );
            exit(EXIT_FAILURE);
        }
    } //while(1)

    closedir(d_in);
    closedir(d_out);

    if( closedir(d_in) ) {
        fprintf(stderr, "Could not close '%s': %s\n",
        dir_in, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

/////////////////////////////////////////////////////////////
// FUNCTION main
/////////////////////////////////////////////////////////////

int main (int argc, char *argv[]) {
    if (argc > 2){
        // boucle pour recuperer tout les dossiers/fichiers sauf le dernier
        // qui sera le repertoire destination
        for(int i=1;i<argc-1;i++){
            //printf("%i :: %s\n", i, argv[i]);
            copyDir(argv[i], argv[argc-1]);
        }
    }
    else if (argc == 2) {
        listDir(argv[1]);
    }else{
        printf("Rappel pour l'entrée : ./ultra-cp dossier(s) \n");
        exit(EXIT_FAILURE);
    }

    //copyDir(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
