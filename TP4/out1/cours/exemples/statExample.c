#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>


int main( int argc, char **argv ) {
  struct stat infos = {0};
  char *filename = argv[1];
  if( stat( filename, &infos ) < 0 ) {
    char *err = strerror(errno);
    fprintf( stderr, "Cannot stat %s: %s\n", 
                     filename, err );
   } else {
    printf( "Filesize: %i\n", (int) infos.st_size );
  }

  return 0;
}
