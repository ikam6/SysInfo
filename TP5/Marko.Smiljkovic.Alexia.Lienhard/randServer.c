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

#include "common.h"

/* Prépare l'adresse du serveur */
void prepare_address( struct sockaddr_in *address, int port ) {
  size_t addrSize = sizeof( address );
  memset(address, 0, addrSize);
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = htonl(INADDR_ANY);
  address->sin_port = htons(port);
}

/* Construit le socket client */
int makeSocket( int port ) {
  struct sockaddr_in address;
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if( sock < 0 ) {
    die("Failed to create socket");
  }
  prepare_address( &address, port );

  bind(sock, ( struct sockaddr* ) &address, sizeof( address ));
  listen(sock, 512);

  if( connect(sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
    die("Failed to connect with server");
  }
  return sock;
}

int main(int argc, char *argv[]) {
  int sock;    /* Socket */
  int port;    /* Port du service */
  char *data; /* Buffer de reception */
  size_t rcvd=0; /* Bytes reçus */
  ssize_t n=0;

  /* Initialisation */


  if (argc != 2) {
    fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[1]);

  /* Connection */

  sock = makeSocket( port );
  printf("sock : %i\n", sock);

  /* Envoie de la requête

  if( write(sock,&numBytes,sizeof(numBytes)) < sizeof(numBytes) ) {
    die( "Cannot send the filename to retrieve" );
  }
  */

  /* Reception de la réponse

  data = (char*) malloc( numBytes );

  while( rcvd < numBytes ) {
    n = read( sock, data+rcvd, numBytes-rcvd );
    if( n  < 0 ) {
      die( "Cannot receive data" );
    }
    rcvd += n;
    printf( "Received %ld bytes.\n", n );
  }
  */

  /* Décommenter pour afficher le résultats en hexadecimal */

  /*
  printf( "Received: " );
  for( int i=0; i < numBytes; i++ ) {
    printf("%x", data[i] & 0xff );
  }
  printf("\n");
  */

  /* Libération des resources */
  free( data );
  close( sock );

  exit(EXIT_SUCCESS);
}
