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


#include "listDir.h"
#include "PrintInfo.h"

#define MAX_SIZE 100


 int IsADirectory ( const char* name)//test si c'est un repertoire
 {
     DIR* directory= opendir(name);

     if(directory!= NULL)//c'est un repertoire
     {
         closedir(directory);
         return 0 ;
     }

     if(errno==ENOTDIR)//Erreur, ce n'est pas un repertoire
     {
         return 1;
     }

     return -1;//autre erreur
 }

/////////////////////////////////////////////////////////////
// FUNCTION main
/////////////////////////////////////////////////////////////

int main (int argc, char *argv[]) {
  /*  if (argc > 2){
        // boucle pour recuperer tout les dossiers/fichiers sauf le dernier
        // qui sera le repertoire destination
        for(int i=1;i<argc-1;i++){
            //printf("%i :: %s\n", i, argv[i]);
            copyDir(argv[i], argv[argc-1]);
        }
    }*/
     if (argc == 2) {
			 if(IsADirectory(argv[1])==1){
				 listfile(argv[1]);
				 exit(EXIT_SUCCESS);
			 }
			 else if (IsADirectory(argv[1])==0){
        listDir(argv[1]);}
			else {perror(NULL);}
    }else{
        printf("Rappel pour l'entrée : ./ultra-cp dossier(s) \n");
        exit(EXIT_FAILURE);
    }

    //copyDir(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
