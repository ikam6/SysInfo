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


void prepareAddress(struct sockaddr_in *address,  int port ) {
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

prepareAddress(&address, port);

if( bind(sock, (struct sockaddr *) &address,sizeof(address)) < 0  )
	{
		die("Failed to bind the server socket");
	}

if (listen(sock, MAX_PENDING) < 0) {
	die("Failed to listen on server socket");
}
return sock;
}

void handleClient( int clientSock, int numberByte ) {
  //TODO gérer le random ici
  if( numberByte <= 0 ) {
    die( "WTF? 1" );
  }
}

void run(int serverSock, int numberByte) {
  while( 1 ) {
    struct sockaddr_in clientAddress;
    unsigned int clientLength = sizeof(clientAddress);
    int clientSock;
    printf( "Waiting for incoming connections\n");
    clientSock = accept(serverSock, (struct sockaddr *) &clientAddress, &clientLength );
    if( clientSock < 0 ) {
      die("Failed to accept client connection");
    }
    printf( "Client connected: %s\n", inet_ntoa(clientAddress.sin_addr));
    handleClient(clientSock, numberByte);
  }
}

int main(int argc, char **argv) {
  int servSock;
  char *path;
  int port;

  format(argc,argv);


  port = atoi(argv[1]);
  path = argv[2];

  servSock = makeSocket( port );

  printf( "Server running on port %d at dir '%s'\n", port, path );

  run( servSock, path );

  close(servSock);

  return EXIT_SUCCESS;
}
