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


#define MAX_SIZE 80

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


int printInfo (int argc, char *argv[])//affiche les données
{

  char t[ 100 ] = "";
  struct stat fileStat;


    if(stat(argv[1],&fileStat) < 0)
        return 1;

    printf("Information for %s\n",argv[1]);


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

    printf(" %ld",sizeof(fileStat));
//affichage jour /mois /heure / année de modification
  if (!stat(argv[1], &fileStat)) {
    strftime(t, 100, " %a %b %d %T %Y  ",
            localtime( &fileStat.st_mtime));
            printf(" %s", t);
  }
   else {
  printf("-----------------");
  }
  printf(" %s\n",argv[1]);
}
static void list_dir (const char * dir_name){

  DIR *d = opendir(dir_name);
  struct dirent *entry;
  const char *d_name;   //nom d'une entrée

  //En cas d'erreur d'ouverture
  if (! d) {
    fprintf(stderr, "Cannot open directory '%s': %s\n",
    dir_name, strerror(errno));
    exit(EXIT_FAILURE);
  }

  //Boucle sur chaque entrée
  while( (entry = readdir(d)) != NULL ) {

    // Obtient le nom de l'entrée et affiche
    d_name = entry->d_name;
    printf("%s/%s\n", dir_name, d_name);

    //Est-ce que 'entry' est un sous-répertoire
    if (entry->d_type & DT_DIR) {
      //Est-ce que 'entry' n'est pas '..' ou '.'
      if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
        char path[PATH_MAX];

        //forme le nom du sous-répertoire et affiche
        int path_length = snprintf (path, PATH_MAX,
          "%s/%s", dir_name, d_name);
          printf("%s\n", path);

          //Vérifie que le nom du sous-répertoire n'est pas trop long
          if (path_length >= PATH_MAX) {
            fprintf(stderr, "Path length has got too long.\n");
            exit(EXIT_FAILURE);
          }

          //Appel récursif
          list_dir(path);
        }
      }
    } //while(1)

    //On ferme le répertoite
    if( closedir(d) ) {
      fprintf(stderr, "Could not close '%s': %s\n",
      dir_name, strerror (errno));
      exit (EXIT_FAILURE);
    }
  }


  static void copy_dir (const char *dir_in, const char *dir_out){
    DIR *d_in = opendir(dir_in);
    DIR *d_out = opendir(dir_out);
    struct dirent *entry;
    const char *d_name;   //nom d'une entrée

    //En cas d'erreur d'ouverture
    if (! d_in) {
      fprintf(stderr, "Cannot open directory '%s': %s\n",
      dir_in, strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (! d_out) {

      printf("On va creer un dossier ... \n");
      d_out = mkdir(dir_out, 0777);

      if (d_out < 0) {
        int savedError = errno;
        closedir(d_in);
        fprintf(stderr, "Could not open the file %s: %s\n", dir_out, strerror(savedError));
      }
    }



}
  int main (int argc, char *argv[]) {
    list_dir(argv[1]);
    copy_dir(argv[1], argv[2]);
    return EXIT_SUCCESS;
  }
