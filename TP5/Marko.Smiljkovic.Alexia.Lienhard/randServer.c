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

#define BUFF_MAX 10
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
void handleClient( int clientSock ) {
	int nRead;
	int sended=0;
ssize_t numBytes;
	//trouve les nombres aléatoires
	unsigned char buffer[BUFF_MAX];
	int fd = open("/dev/urandom", O_RDONLY);
	//TODO  a contrler devrait retourner le nbre de byte demander par le client
	nRead =read(clientSock, &numBytes,sizeof(numBytes));
printf("%ld\n",numBytes);
	printf("%d\n et %d ET %d ",nRead,BUFF_MAX,sended );
	//
	if( nRead <= 0 ) {
    die( "WTF? 1" );
  }

else if(numBytes<BUFF_MAX-sended){
		copy(fd,clientSock);
	}
else if(numBytes>BUFF_MAX-sended)	{
printf("il y a plus de demande que de place dans le buffer\n" );
	copy(fd,clientSock);
	printf("%d sended \n",sended );
}

  close(clientSock);
	close(fd);
}



void run( int serverSock) {
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

    handleClient(clientSock);
//  }
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

  run(servSock);

  close(servSock);

  return EXIT_SUCCESS;
}
