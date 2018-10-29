#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>  //snprintf
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 100




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


    char strDir[MAX_SIZE]="";
		if (nameDir!=nameFile){
			strcat(strDir, nameDir);
	    strcat(strDir, "/"); // a faire attention selon l'entrée sur le terminal !! (risque de double //)
	    strcat(strDir, nameFile);
	    strcpy(t, strDir);
		}
		if(nameDir==nameFile){
			strcat(strDir,nameFile);
		}
     //utile pour afficher le temps
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

    printf(" %8ld",fileStat.st_size);
    printf(" %s", formatDate(t, fileStat.st_mtime)); //
    printf(" %s\n", strDir);

}
