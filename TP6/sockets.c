#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <unistd.h>

inline void die(char *issue) {
  perror(issue);
  exit(EXIT_FAILURE);
}

void prepare_address ( struct sockaddr_in *address, const char *host, int port) {
  size_t addrSize = sizeof( address );
  memset(address, 0, addrSize);
  address->sin_family = AF_INET;
  inet_pton( AF_INET, (char*) address, &(address->sin_addr) );
  address->sin_port = htons(port);
}

int openSocket (const char *host, int port){
	struct sockaddr_in *address;
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if( sock < 0 ) {
    die("Failed to create socket");
  	}

	prepare_address( address, host, port );
  if(connect(sock, (struct sockaddr *) &address, sizeof(address)) < 0) {
    die("Failed to connect with server");
		}
	return sock;
	}
