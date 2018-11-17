#include<stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define SMTP_domain_name "smtp.unige.ch.";

int main(int argc, const char* argv[]){



	char buffer [100];
	int sended;
	int receved;
	char rcvd_buffer[4000];
	int connected_fd=connectToServer(SMTP_domain_name);


	strcpy(buffer, "EHLO");
	strcat(buffer, domain);
	strcat(buffer, "\r\n");
	send(connected_fd,buffer, strlen(buffer),0);
	sended= recv(connected_fd,rcvd_buffer+rcvd,sizeof(rcvd_buffer)-rcvd,0 );
	rcvd+=sended;


	return 0;
}
/*void prepare_address( struct sockaddr_in *address, const char *host, int port ) {
  size_t addrSize = sizeof( address );
  memset(address, 0, addrSize);
  address->sin_family = AF_INET;
  inet_pton( AF_INET, (char*) host, &(address->sin_addr) );
  address->sin_port = htons(port);
}
//prépare l'adresse du client
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
}*/

//connecte le client sur le serveur TODO changer de port si occupé
int connectToServer(const char* server_address){
	int socket_fd=socket (AF_INET, SOCK_STREAM,IPPROTO_IP);
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(25);
	if (inet_pton(AF_INET, GetIPAdress(server_address), addr.sin_addr)==1){
		connect(socket_fd,&addr, sizeof(addr));
	}

	return socket_fd;
}

//délivre une adresse ip au client
const char* GetIPAdress ( const char* target_domain){
	const char* target_ip;
	int i=0;
	struct in_addr *host_address;
	struct hostent *raw_list=gethostbyname(target_domain);

	for (i; raw_list->h_addr_list[i]!=0;i++){
		host_address=raw_list->h_addr_list[i];
		target_ip=inet_ntoa(host_address);
	}
	return target_ip;
}

//prend le fichier en entrée et le copie dans un buffer
void getEMail(int argc, const char* argv[]){

	FILE *f = fopen(argv[1], "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;
}
