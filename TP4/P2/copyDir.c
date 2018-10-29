#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>  //snprintf
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
/////////////////////////////////////////////////////////////
// FUNCTION copyDir
/////////////////////////////////////////////////////////////
//Pas besoin de copydir pour la première partie

void copyDir (const char *dir_in, const char *dir_out){
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
    printf("On a le dossier %s et on peut copier le contenu de %s dedans \n", dir_out, dir_in);
    //printf( (link(dir_in, dir_out) == 0) ? "Succes\n" :"Fail\n" );


    printf("dirIn %s, drirOut: %s\n", dir_in, dir_out);
//TODO Pourquoi on fait ca ici, il y a deja dans listDir
    while( (entry = readdir(d_in)) != NULL ) {
        // Obtient le nom de l'entrée et affiche
        d_name = entry->d_name;
        //Est-ce que 'entry' est un sous-répertoire
        if (entry->d_type & DT_DIR) {
            //Est-ce que 'entry' n'est pas '..' ou '.'
            if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                char path[PATH_MAX];
                //forme le nom du sous-répertoire et affiche
                int path_length = printf (path, PATH_MAX,"%s/%s",
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
        /*err = 1; //TODO aucune idee de ce machin
        int n = err;
        if (n==0) break;
        char pathNewDir[]="";
        char oldPath []="";
        struct stat fileStat;
        strcat(pathNewDir, dir_out);
        strcat(pathNewDir, "/");
        strcat(pathNewDir, d_name);
        printf("Notre nouveau path est %s\n", pathNewDir);

        strcat(oldPath, dir_in);
        strcat(oldPath, "/");
        strcat(oldPath, d_name);


        int fd = open(pathNewDir, O_CREAT, 0777);
        printf(" c'est la merde %s", pathNewDir);
        link ( oldPath, pathNewDir);

        if (fd < 0){
            int savedError = errno;
            fprintf(stderr, "Could not open directory %s sa mere la pute: %s\n",
            pathNewDir, strerror(savedError));
        }

        fd= open(pathNewDir, 1);
        printf("%d\n", fd);
        if (fd < 0){printf("sa mère la pute\n");}
        err = write(fd, d_name, 1);
        if (err == -1){
            printf("Error writing file.\n" );
            exit(EXIT_FAILURE);

        }*/
        err = 1; //TODO aucune idee de ce machin
        int n = err;
        if (n==0) break;
        char pathDir[]="";
        char oldPath []="";
        strcat(pathDir, dir_out);
        strcat(pathDir, "/");
        strcat(pathDir, d_name);
        printf("Notre nouveau path est %s\n", pathDir);

        strcat(oldPath, dir_in);
        strcat(oldPath, "/");
        strcat(oldPath, d_name);

        int fd = open(pathDir, O_CREAT, 0777);
        printf("%d\n", fd );
        link(oldPath, pathDir);
        if (fd < 0){
            int savedError = errno;
            fprintf(stderr, "Could not open directory %s: %s\n",
            pathDir, strerror(savedError));
        }
        fd= open(pathDir, O_CREAT);
        err = write(fd, d_name, 1);
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
