/*--------------------------------------------------------/
     Code fait par :
     Lienhard Alexia
     et
     Smiljkovic Marko
/--------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>  //PATH_MAX
#include <libgen.h> //basename
#include <sys/types.h>
#include <sys/stat.h>

#include "PrintInfo.h"

#define MAX_BUF 4096
#define PATH_MAX 4096

void copy(const char *from, const char *to) {
    int fd_to, fd_from, errno;
    char buf[MAX_BUF];
    ssize_t nread;

    fd_from = open(from, O_RDONLY);
    if (fd_from < 0) {
        fprintf( stderr, "Could not open the file %s: %s\n",
        from, strerror(errno) );
        exit(EXIT_FAILURE);
    }

    fd_to = open(to, O_RDWR | O_CREAT, 0777);
    if (fd_to < 0) {
        int savedError =errno;
        close( fd_from );
        fprintf( stderr, "Could not open the file %s: %s\n",
        to, strerror(savedError) );
        exit(EXIT_FAILURE);
    }

    while( nread = read(fd_from, buf, sizeof buf), nread > 0 ) {
        char *out_ptr = buf;
        ssize_t nwritten;
        do {
            nwritten = write(fd_to, out_ptr, nread);

            if (nwritten >= 0) {
                nread -= nwritten;
                out_ptr += nwritten;
            } else if (errno != EINTR) {
                int savedError =errno;
                close( fd_from );
                close( fd_to );
                fprintf( stderr, "Could not copy  %s to %s: %s\n",
                from, to, strerror(savedError) );
                exit(EXIT_FAILURE);
            }

        } while (nread > 0);
    }

    if (nread != 0) {
        int savedError =errno;
        close( fd_from );
        close( fd_to );
        fprintf( stderr, "Could not read %s: %s\n",
        from, strerror(savedError) );
        exit(EXIT_FAILURE);
    }

    close( fd_from );
    close( fd_to );
    //Il faudrait gérer les erreurs de fermeture

    // if( close( fd_from ) ) {
    //     fprintf(stderr, "Could not close file from '%s': %s\n",
    //     from, strerror (errno));
    //     exit (EXIT_FAILURE);
    // }
    //
    // if( close( fd_to ) ) {
    //     fprintf(stderr, "Could not close file to '%s': %s\n",
    //     to, strerror (errno));
    //     exit (EXIT_FAILURE);
    // }

}

void copying_rec(char *dirFrom, char *dirTo) {

    struct stat infoFile;

    char *directory = dirTo;
    stat(directory, &infoFile);

    if (S_ISREG(infoFile.st_mode) || S_ISLNK(infoFile.st_mode)) {
        printf("Last entry most be a directory and not %s\n", dirTo);
        exit(EXIT_FAILURE);
    }
    else {
        DIR *d = opendir(dirTo);
        if (! d){
            //printf("On va creer le dossier '%s' : \n", dirTo);
            mkdir(dirTo, 0777);
        }
        // else{
        //     printf("Le dossier '%s', existe deja.\n", dirTo);
        // }
    }

    char *filename = dirFrom;
    stat(filename, &infoFile);

    if (S_ISREG(infoFile.st_mode) || S_ISLNK(infoFile.st_mode)) {
        filename = basename(dirFrom);
        printf("filename %s\n", filename);
        printf("dirTo %s\n", dirTo);

        // char outFrom[MAX_BUF] = "";
        // strcat(outFrom, dirFrom);
        // strcat(outFrom, "/");
        // strcat(outFrom, filename);

        char outTo[MAX_BUF] = "";
        strcat(outTo, dirTo);
        strcat(outTo, "/");
        strcat(outTo, filename);
        //printf("outTo %s\n", outTo);

        copy(filename, outTo);
    }
    else if (S_ISDIR(infoFile.st_mode)) {
        DIR *d = opendir(dirFrom);
        struct dirent *entry;
        const char *d_name;

        if (!d) {
            fprintf(stderr, "Cannot open directory '%s' : %s\n",
            dirFrom, strerror(errno));
            exit(EXIT_FAILURE);
        }

        char outFrom[MAX_BUF] = "";
        strcat(outFrom, dirFrom);

        char outTo[MAX_BUF] = "";
        strcat(outTo, dirTo);

        //printf("outTo avant mkdir %s\n", outTo);
        mkdir(outTo, 0777);

        while ( (entry = readdir(d)) != NULL ) {
            d_name = entry -> d_name;

            if ((strcmp(d_name, "..") == 0) || (strcmp(d_name, ".") == 0)) {
                continue;
            }

            if ((entry->d_type & DT_REG) || (entry->d_type & DT_LNK)) {
                strcat(outFrom, "/");
                strcat(outFrom, d_name);

                // pour pouvoir faire l'affichage creer tmp:
                char tmp[MAX_BUF] = "";
                strcpy(tmp, outTo);

                strcat(outTo, "/");
                strcat(outTo, d_name);

                // printf("outFrom %s\n", outFrom);
                // printf("outTo %s\n", outTo);

                copy(outFrom, outTo);

                //printf("tmp : %s, d-name : %s\n", tmp, d_name);
                printInfo(tmp, d_name);


                strcpy(outFrom, dirFrom);
                strcpy(outTo, dirTo);

            }

            //Sous-repertoire :
            if (entry->d_type & DT_DIR) {
                if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {

                    char path[MAX_BUF] = "";

                    //forme le nom du sous-répertoire et affiche
                    int path_length = snprintf (path, PATH_MAX, "%s/%s", dirFrom, d_name);
                    //printf("path name : %s\n", path);

                    //verifie que le nom du sous-répertoire n'est pas trop long
                    if (path_length >= PATH_MAX) {
                        fprintf(stderr, "Path length has got too long.\n");
                        exit(EXIT_FAILURE);
                    }

                    // pour pouvoir faire l'affichage creer tmp:
                    char tmp2[MAX_BUF] = "";
                    strcpy(tmp2, outTo);

                    strcat(outTo, "/");
                    strcat(outTo, d_name);

                    //printf("path : %s, dirTo : %s, outTo %s,\n tmp2 %s, d_name %s\n",
                    //path, dirTo, outTo, tmp2, d_name);


                    //appel rec
                    copying_rec(path, outTo);
                    printInfo(tmp2, d_name);
                }
            }
        }

        if (closedir(d)) {
            fprintf(stderr, "Could not close '%s': %s\n",
            d_name, strerror (errno));
            exit (EXIT_FAILURE);
        }
    }
}
