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

//using namespace std;

#define HELO "HELO 192.168.1.1\r\n"
#define DATA "DATA\r\n"
#define QUIT "QUIT\r\n"

#define h_addr h_addr_list[0]

#define STRING_MAX 1000

//FILE *fin;


struct sockaddr_in server;
struct hostent *hp;
struct hostent *gethostbyname();

int sock;
char *host_id="smtp.unige.ch";
char *from_id="marko.smiljkovic@etu.unige.ch";

char *to_id="marko.smiljkovic@etu.unige.ch";
char *sub="testmail\r\n";
char wkstr[STRING_MAX]="yo\r\n";


/*=====Create Socket=====*/
int createSocket(){
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock==-1)	{
		perror("opening stream socket");
		exit(1);
	}
	else
	printf( "socket created\n");
	return sock;
}

//=====Read a string from the socket=====*/
void read_socket() {
	char buf[BUFSIZ+1];
	int len;

	len = read(sock,buf,BUFSIZ);
	write(1,buf,len);
	printf("Server:%s\n",buf);
}

/*=====Send a string to the socket=====*/
void send_socket(char *s)	{
	write(sock,s,strlen(s));
	write(1,s,strlen(s));
	//printf("Client:%s\n",s);
}

/*=====READ FILE======*/
void readfile(int argc, char *argv[]) {
	FILE *fichier = NULL;
	fichier = fopen(argv[1], "r");

	if(fichier != NULL) {
		fgets(wkstr, STRING_MAX, fichier);
		fclose(fichier);
	}
	else {
		perror("Erreur lors de l'ouverture du fichier.\n");
		exit(EXIT_FAILURE);
	}
	strcat(wkstr, "\r\n");
}


/*==== SEND A MAIL =====*/
void SendEmail(char* from_id, char* to_id, char* sub, char* wkstr ){
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
	send_socket(wkstr);
	send_socket(".\r\n");
	read_socket();
	send_socket(QUIT); /* quit */
	read_socket(); // log off */

	//=====Close socket and finish=====*/
	close(sock);
	exit(0);
}

/*=====MAIN=====*/
int main(int argc, char* argv[]){
	printf("%d\n", argc);
	if (argc != 2){
		printf("Rappel d'exécution : %s 'fichier.txt' \n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/*=====Create Socket=====*/
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock==-1)
	{
		perror("opening stream socket");
		exit(1);
	}
	else
	printf("socket created\n");
	/*=====Verify host=====*/
	server.sin_family = AF_INET;
	hp = gethostbyname(host_id);
	if (hp==(struct hostent *) 0)
	{
		fprintf(stderr, "%s: unknown host\n", host_id);
		exit(2);
	}
	/*=====Connect to port 25 on remote host=====*/
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port=htons(25); /* SMTP PORT */
	if (connect(sock, (struct sockaddr *) &server, sizeof server)==-1)
	{
		perror("connecting stream socket");
		exit(1);
	}
	else
	printf( "Connected\n");

	/*===== READ FILE ======*/
	readfile(argc, argv);

	printf("\n\n wkstr : %s\n\n", wkstr);

	SendEmail(from_id, to_id, sub, wkstr);
}
