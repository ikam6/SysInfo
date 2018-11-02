/* Inspiré d'un exemple de J. Menu */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>     
#include <sys/fcntl.h>
#include <unistd.h>    // pour STDOUT_FILENO

#define BUF_SIZE 64

int openFIFO( char *name ) {
  int fifo = open( name, O_RDONLY );
  if( fifo < 0 ) {
    perror( "Cannot open the fifo" );
    exit(EXIT_FAILURE);
  }
  printf( "The fifo %s is open\n", name );
  return fifo;
}

void fifo2stdout( int fifo ) {
  char buffer[BUF_SIZE];
  ssize_t nread, nwrit;
  while(1) {
    nread = read( fifo, buffer, BUF_SIZE );
    if( nread < 0 ) {
      perror( "Reading fifo failed ");
      exit(EXIT_FAILURE);
    }
    if( nread == 0 ) {
      printf( "Received End-Of-File\n" );
      break;
    }
    nwrit = write( STDOUT_FILENO, buffer, nread );
    if( nwrit != nread ) {
      perror( "Writing to STDOUT failed" );
      exit(EXIT_FAILURE);
    }
  }
}

void disposeFIFO( int fifo, char *name ) {
  int ret = close( fifo );
  if( ret < 0 ) {
    perror( "Cannot close fifo." );
  }
  ret = unlink( name );
  if( ret < 0 ) {
    perror( "Cannot remove fifo." );
  }
}

int main (int argc, char **argv ) {
  if (argc != 2) {
    printf( "Usage: %s <fifo_name> \n", argv[0] );
    exit(EXIT_FAILURE);
  }
  char *name = argv[1];
  int fifo = openFIFO( name );
  fifo2stdout( fifo );
  disposeFIFO( fifo, name );
  exit(EXIT_SUCCESS);
}

