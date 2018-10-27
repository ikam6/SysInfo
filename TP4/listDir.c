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
#include "PrintInfo.h"

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
