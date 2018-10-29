/* Inspiré d'un exemple de J. Menu */

#include <stdlib.h>
#include <stdio.h>
#include  <errno.h> 
#include <sys/fcntl.h>
#include <sys/stat.h>		
#include <unistd.h>	// pour STDOUT_FILENO

#define BUF_SIZE 64

int createFIFO( char *name ) {
  int fifo = -1;
  int result = mkfifo( name, 0600 );
  if( result < 0 ) {
    perror( "Cannot create the fifo" );
    exit(EXIT_FAILURE);
  } 
  printf( "Created fifo %s\n", name );
  fifo = open( name, O_WRONLY );
  if( fifo < 0 ) {
    perror( "Cannot open the fifo" );
    exit(EXIT_FAILURE);
  }
  printf( "The fifo %s is open\n", name );
  return fifo;
}

void stdin2fifo( int fifo ) {
  char buffer[BUF_SIZE];
  ssize_t nread, nwrit;
  while (1) {
    nread = read(STDIN_FILENO, buffer, BUF_SIZE);
    if( nread < 0 ) {
      perror( "Reading STDIN failed ");
      exit(EXIT_FAILURE);
    }
    if( nread == 0 ) {
      printf( "Received End-Of-File \n" );
      return;
    }
    nwrit = write( fifo, buffer, nread );
    if( nwrit != nread ) {
      perror( "Writing to fifo failed" );
      exit(EXIT_FAILURE);
    }
  }
}

int main (int argc, char **argv) {
  if (argc != 2) {
    printf( "Usage: %s <fifo_name> \n", argv[0] );
    exit(EXIT_FAILURE);
  }
  int fifo = createFIFO( argv[1] );
  stdin2fifo( fifo );
  close(fifo);
  exit(EXIT_SUCCESS);
}
