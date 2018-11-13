/*#include <stdio.h>
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
#define MAX_NAME 100
#define MAX_FULLPATH 256

/* Prépare l'adresse du serveur
void prepare_address( struct sockaddr_in *address, int port ) {
  size_t addrSize = sizeof( address );
  memset(address, 0, addrSize);
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = htonl(INADDR_ANY);
  address->sin_port = htons(port);
}

/* Construit le socket client
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

void handleClient( int clientSock, const char *path ) {
	char fullPath[MAX_FULLPATH];
  int pathLen = strlen( path );
  int file;
  int nRead;
  printf( path );
  strncpy( fullPath, path, MAX_FULLPATH );    // TODO: Proteger le slash
  nRead = read( clientSock, (fullPath+pathLen), MAX_NAME );
  if( nRead <= 0 ) {
    die( "WTF? 1" );
  }
  printf( "Requested file: %s\n", fullPath );
  file = open( fullPath, O_RDONLY, 0 );
  if( copy( file, clientSock ) < 0 ) {
    perror( "Failed to send the file" );
  }
  close( file );
  close( clientSock );
}

void run( int serverSock, int port ) {
  while( 1 ) {
    struct sockaddr_in clientAddress;
    unsigned int clientLength = sizeof(clientAddress);
    int clientSock;
    printf( "Waiting for incoming connections\n");
    clientSock =
      accept(serverSock, (struct sockaddr *) &clientAddress, &clientLength );
    if( clientSock < 0 ) {
      die("Failed to accept client connection");
    }
    printf( "Client connected: %s\n", inet_ntoa(clientAddress.sin_addr));
    //handleClient(clientSock,port);
	}
}
int main(int argc, char *argv[]) {
  int sock;    /* Socket *
  int port;    /* Port du service
  char *data; /* Buffer de reception
  size_t rcvd=0; /* Bytes reçus
  ssize_t n=0;

  /* Initialisation


  if (argc != 2) {
    fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[1]);

  // Connection

  sock = makeSocket( port );
  printf("sock : %i\n", sock);
	run(sock, 1000);

  // Envoie de la requête

  if( write(sock,&numBytes,sizeof(numBytes)) < sizeof(numBytes) ) {
    die( "Cannot send the filename to retrieve" );
  }


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

  /* Libération des resources
  free( data );
  close( sock );

  exit(EXIT_SUCCESS);
}
*/
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

#define MAX_FULLPATH 1024
#define MAX_NAME 255
#define MAX_PENDING 256

void prepare_address( struct sockaddr_in *address,  int port ) {
  size_t addrSize = sizeof( address );
  memset(address, 0, addrSize);
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = htonl(INADDR_ANY);
  address->sin_port = htons(port);
}

int makeSocket( int port ) {
  struct sockaddr_in address;
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if( sock < 0 ) {
    die("Failed to create socket");
  }
  prepare_address( &address, port );
  if(bind(sock, (struct sockaddr *) &address,sizeof(address)) < 0  )
    {
      die("Failed to bind the server socket");
    }
  if (listen(sock, MAX_PENDING) < 0) {
    die("Failed to listen on server socket");
  }
  return sock;
}
//TODO changer le handleClient pour que ca fasse le random
void handleClient( int clientSock, int numBytes) {
  char fullPath[MAX_FULLPATH];
  int file;
  int nRead;
      /* TODO: Proteger le slash */
  nRead = read( clientSock, numBytes, MAX_NAME );
	printf(nRead);
  if( nRead <= 0 ) {
    die( "WTF? 1" );
  }

  close( clientSock );
}
//TODO contoler le run pour que ca colle avec le handleClient
void run( int serverSock, int numBytes) {
  while( 1 ) {
    struct sockaddr_in clientAddress;
    unsigned int clientLength = sizeof(clientAddress);
    int clientSock;
    printf( "Waiting for incoming connections\n");
    clientSock =
      accept(serverSock, (struct sockaddr *) &clientAddress, &clientLength );
    if( clientSock < 0 ) {
      die("Failed to accept client connection");
    }
    printf( "Client connected: %s\n", inet_ntoa(clientAddress.sin_addr));
    handleClient(clientSock,numBytes);
  }
}


int main( int argc, char **argv ) {
  int servSock;
  int port;

  if (argc != 2) {
    fprintf(stderr, "USAGE: %s <port> \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[1]);


  servSock = makeSocket(port);

  printf( "Server running on port %d \n", port);

  run(servSock, 1000);

  close(servSock);

  return EXIT_SUCCESS;
}
