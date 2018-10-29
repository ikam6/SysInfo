#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>  //PATH_MAX
#include <libgen.h>//basename
#include <sys/types.h>
#include <sys/stat.h>

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

    if( close( fd_from ) ) {
        fprintf(stderr, "Could not close '%s': %s\n",
        from, strerror (errno));
        exit (EXIT_FAILURE);
    }

    if( close( fd_to ) ) {
        fprintf(stderr, "Could not close '%s': %s\n",
        to, strerror (errno));
        exit (EXIT_FAILURE);
    }

    // if( (errno = close(fd_from)) != 0 ) {
    //     fprintf(stderr, "Could not close '%s': %s\n",
    //     fd_from, strerror (errno));
    //     exit (EXIT_FAILURE);
    // }
    //
    // if( (errno = close(fd_to)) != 0 ) {
    //     fprintf(stderr, "Could not close '%s': %s\n",
    //     fd_to, strerror (errno));
    //     exit (EXIT_FAILURE);
    // }
}

void copying_rec(const char *dirFrom, const char *dirTo) {

    DIR *pathFrom = opendir(dirFrom);
    DIR *pathTo = opendir(dirTo);
    struct dirent *entry;
    const char *d_name;   //nom d'une entrée

    //En cas d'erreur d'ouverture
    if (! pathFrom) {

        fprintf(stderr, "Cannot open directory '%s': %s\n",
        dirFrom, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (! pathTo) {
        printf("On va creer le dossier : %s\n", dirTo);
        mkdir(dirTo, 0777);

        if (pathTo < 0 ) {
            int savedError = errno;
            closedir(pathFrom);
            fprintf(stderr, "Could not open directory %s: %s\n",
            dirTo, strerror(savedError));
        }
    }

    //Boucle sur chaque entrée
    while( (entry = readdir(pathFrom)) != NULL ) {
        // Obtient le nom de l'entrée et affiche
        d_name = entry->d_name;

        if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
            printf("d_name %s\n", d_name);
        }

        //Est-ce que 'entry' est un sous-répertoire
        if (entry->d_type & DT_DIR) {
            //Est-ce que 'entry' n'est pas '..' ou '.'
            if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                char path[PATH_MAX];
                //forme le nom du sous-répertoire et affiche
                int path_length = snprintf (path, PATH_MAX, "%s/%s",
                dirTo, d_name);
                //printf("Dans la question if : %s\n", path);
                //Vérifie que le nom du sous-répertoire n'est pas trop long
                if (path_length >= PATH_MAX) {
                    fprintf(stderr, "Path length has got too long.\n");
                    exit(EXIT_FAILURE);
                }

                //Appel récursif
                printf("dirFrom %s, dirTo %s, d_name %s\n", dirFrom, dirTo, d_name);
                copying_rec(dirFrom, dirTo);
            }
        }
    } //while(1)
    //On ferme le répertoite
    printf("On arrive a la fin \n" );
    closedir( pathFrom );
    closedir( pathTo );

    if( closedir( pathFrom ) ) {
        fprintf(stderr, "Could not close '%s': %s\n",
        dirFrom, strerror (errno));
        exit (EXIT_FAILURE);
    }

    if( closedir( pathTo ) ) {
        fprintf(stderr, "Could not close '%s': %s\n",
        dirTo, strerror (errno));
        exit (EXIT_FAILURE);
    }
}
