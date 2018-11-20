#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


#define HELO "HELO 192.168.1.1\r\n"
#define DATA "DATA\r\n"
#define QUIT "QUIT\r\n"
#define h_addr h_addr_list[0]
#define STRING_MAX 10000


/*=====Create Socket=====*/
int createSocket(){
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock==-1)	{
		perror("opening stream socket");
		exit(1);
	}
	else {
        printf( "socket created\n");
    }
	return sock;
}

//=====Read a string from the socket=====*/
void read_socket() {
	char buf[BUFSIZ+1];
	int len;

	len = read(sock,buf,BUFSIZ);
	write(1,buf,len);
	//printf("Server:%s\n",buf);
}

/*=====Send a string to the socket=====*/
void send_socket(char *s)	{
	write(sock,s,strlen(s));
	write(1,s,strlen(s));
	//printf("Client:%s\n",s);
}

/*=====READ FILE======*/
char* readfile(int argc, char *argv[]) {
	char wkstr[STRING_MAX]="";
	FILE *fichier = NULL;
	char* message=malloc(STRING_MAX);
	fichier = fopen(argv[1], "r");

	if(fichier != NULL) {
        while(fgets(wkstr, STRING_MAX, fichier)){
					strcat(message,wkstr);
				};
		fclose(fichier);
	}
	else {
		perror("Erreur lors de l'ouverture du fichier.\n");
		exit(EXIT_FAILURE);
	}
	strcat(message, "\r\n");
	//printf("%s",message);

	return message;
}


/*==== SEND A MAIL =====*/
void SendEmail(char* from_id, char* to_id, char* sub, char* message ){
	/*=====Write some data then read some =====*/
	read_socket(); /* SMTP Server logon string */
	send_socket(HELO); /* introduce ourselves */
	read_socket(); /*Read reply */
	send_socket("MAIL FROM: ");
	send_socket(from_id);
	send_socket("\r\n");
	read_socket(); /* Sender OK */
	send_socket("VRFY ");
	send_socket(from_id);
	send_socket("\r\n");
	read_socket(); // Sender OK */
	send_socket("RCPT TO: "); /*Mail to*/
	send_socket(to_id);
	send_socket("\r\n");
	read_socket(); // Recipient OK*/
	send_socket(DATA);// body to follow*/
	send_socket("Subject: ");
	send_socket(sub);
	read_socket(sock); // Recipient OK*/
	send_socket(message);
	send_socket(".\r\n");
	read_socket();
	send_socket(QUIT); /* quit */
	read_socket(); // log off */

	//=====Close socket and finish=====*/
	close(sock);
	exit(0);
}
