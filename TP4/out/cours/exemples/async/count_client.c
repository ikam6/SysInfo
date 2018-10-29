#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include "count_common.h"

void prepare_address( struct sockaddr_in *address, const char *host, int port ) {
  memset(address, 0, sizeof(*address));
  address->sin_family = AF_INET;
  inet_pton( AF_INET, (char*) address, &(address->sin_addr) );
  address->sin_port = htons(port);
}

int makeSocket( const char *host, int port ) {
  struct sockaddr_in address;
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if( sock < 0 ) {
    die("Failed to create socket");
  }
  prepare_address( &address, host, port );
  if( connect(sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
    die("Failed to connect with server");
  }
  return sock;
}

void sleepRand( int max ) {
  int n = rand() % max;
  sleep(n);
}


int main(int argc, char *argv[]) {
  int sock;
  char *host;
  int port;
  Counter count,total;

  if (argc != 4) {
    fprintf(stderr, "USAGE: %s <host> <port> <count>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  host = argv[1];
  port = atoi(argv[2]);
  count = atoi(argv[3]);

  srand( time(NULL) );

  sleepRand(5);

  sock = makeSocket( host, port );

  sleepRand(5);
  
  if( write( sock, &count, COUNTER_SIZE ) != COUNTER_SIZE ) {
    die( "Cannot send the count" );
  }

  sleepRand(5);

  if( read( sock, &total, COUNTER_SIZE ) != COUNTER_SIZE ) {
    printf( "TOTAL: %d\n", total );
    die( "Cannot receive the total" );
  }

  printf( "The total is: %d.\n", total );

  
  close(sock);
  
  exit(EXIT_SUCCESS);
}        
