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


/////////////////////////////////////////////////////////////
// FUNCTION formatDate
/////////////////////////////////////////////////////////////

char *formatDate(char *message, time_t val){
    strftime(message, MAX_SIZE, " %d.%m.%Y %H:%M ", localtime(&val));
    return message;
}

/////////////////////////////////////////////////////////////
// FUNCTION printInfo
/////////////////////////////////////////////////////////////

int printInfo(const char *nameDir, const char *nameFile)//affiche les données
{

    char t[MAX_SIZE] = "";
    struct stat fileStat;
    // printf("1. %s\n", nameDir);
    // printf("2. %s\n", nameFile);

    char strDir[MAX_SIZE]="";
    strcat(strDir, nameDir);
    strcat(strDir, "/"); // a faire attention selon l'entrée sur le terminal !! (risque de double //)
    strcat(strDir, nameFile);
    strcpy(t, strDir); //utile pour afficher le temps 
    //printf("\nstringDir : %s\n", strDir);


    if(stat(strDir, &fileStat) <0 ){
        fprintf(stderr, "Cannot stat %s : %s\n", strDir, strerror(errno) );
    }else  {
        //printf("File inode: %ld\n", fileStat.st_ino);
    }


    if ((S_ISDIR(fileStat.st_mode))== 0)
    {
        if (S_ISLNK(fileStat.st_mode)==0)
        {
            printf("-");
        }
        else  printf("l");
    }
    else  printf("d");

    //affichage des infos de lecture/écriture
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %6ld",fileStat.st_size);
    printf(" %s", formatDate(t, fileStat.st_mtime)); //
    printf(" %s\n", strDir);
}

/////////////////////////////////////////////////////////////
// FUNCTION listDir
/////////////////////////////////////////////////////////////

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

// static void copyDir (const char *dir_in, const char *dir_out){
//     DIR *d_in = opendir(dir_in);
//     DIR *d_out = opendir(dir_out);
//     struct dirent *entry;
//     const char *d_name;   //nom d'une entrée
//
//     //En cas d'erreur d'ouverture
//     if (! d_in) {
//         fprintf(stderr, "Cannot open directory '%s': %s\n",
//         dir_in, strerror(errno));
//         exit(EXIT_FAILURE);
//     }
//
//     if (! d_out) {
//         printf("On va creer un dossier ... \n");
//         d_out = mkdir(dir_out, 0777);
//
//         if (d_out < 0) {
//             int savedError = errno;
//             closedir(d_in);
//             fprintf(stderr, "Could not open the file %s: %s\n",
//             dir_out, strerror(savedError));
//         }
//     }
// }

/////////////////////////////////////////////////////////////
// FUNCTION main
/////////////////////////////////////////////////////////////

int main (int argc, char *argv[]) {
    listDir(argv[1]);
    //copyDir(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
