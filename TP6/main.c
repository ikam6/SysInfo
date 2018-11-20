/*--------------------------------------------------------/
    Code fait par :
    Lienhard Alexia
    et
    Smiljkovic Marko
/--------------------------------------------------------/
Explication comment utiliser le programme :

Il y a un commentaire TODO qui vous indique l'endroit oû il faudrait changer :
- nom de l'expéditeur
- nom de recevant
- sujet du mail

Un fois ceci modifié, il faut exécuter dans le terminal :
$ make
$ ./main nomFichier.txt

avec nomFichier.txt votre fichier ayant le contenu du mail à envoyer.


Voilà votre mail est envoyé.
/--------------------------------------------------------*/


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


// variable globale pour permettre un echange plus facile entre les fonctions
// car on n'arrive pas a sortir un string de la fonction void readfile():
char filestr[STRING_MAX]="";


/*=====Create Socket=====*/
int createSocket(){
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock==-1)	{
		perror("opening stream socket");
		exit(EXIT_FAILURE);
	}
	else {
        printf("Trying %s", HELO);
    }
	return sock;
}

//=====Read a string from the socket=====*/
void read_socket(int sock) {
	char buf[BUFSIZ+1];
	int len;

	len = read(sock,buf,BUFSIZ);
	write(1,buf,len);
	//printf("Server:%s\n",buf);
}

/*=====Send a string to the socket=====*/
void send_socket(int sock, char *s)	{
	write(sock,s,strlen(s));
	write(1,s,strlen(s));
	//printf("Client:%s\n",s);
}

/*=====READ FILE======*/
char* readfile(char *argv[]) {
	char filestr[STRING_MAX]="";
	FILE *fichier = NULL;
	char* message=malloc(STRING_MAX);
	fichier = fopen(argv[1], "r");

	if(fichier != NULL) {
		while(fgets(filestr, STRING_MAX, fichier)){
			strcat(message,filestr);
		}
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
void SendEmail(int sock, char* from_id, char* to_id, char* sub, char* filestr ){
	/*=====Write some data then read some =====*/
	read_socket(sock); /* SMTP Server logon string */
	send_socket(sock, HELO); /* introduce ourselves */
	read_socket(sock); /*Read reply */
	send_socket(sock, "MAIL FROM: ");
	send_socket(sock, from_id);
	send_socket(sock, "\r\n");
	read_socket(sock); /* Sender OK */
	send_socket(sock, "VRFY ");
	send_socket(sock, from_id);
	send_socket(sock, "\r\n");
	read_socket(sock); // Sender OK */
	send_socket(sock, "RCPT TO: "); /*Mail to*/
	send_socket(sock, to_id);
	send_socket(sock, "\r\n");
	read_socket(sock); // Recipient OK*/
	send_socket(sock, DATA);// body to follow*/
	send_socket(sock, "Subject: ");
	send_socket(sock, sub);
	read_socket(sock); // Recipient OK*/
	send_socket(sock, filestr);
	send_socket(sock, ".\r\n");
	read_socket(sock);
	send_socket(sock, QUIT); /* quit */
	read_socket(sock); // log off */
}

/*=====MAIN=====*/
int main(int argc, char* argv[]){
	// Initialisation
	struct sockaddr_in server;
	struct hostent *hp;
	struct hostent *gethostbyname();


	char *host_id="smtp.unige.ch";

	//TODO : changer le nom envoyeur, recepteur et sujet du mail ici :
	char *from_id = "marko.smiljkovic@etu.unige.ch";
	char *to_id = "marko.smiljkovic@etu.unige.ch";
	char *sub = "testmail\r\n";

	// Controle de l'entree utilisateur :
	if (argc != 2){
		printf("Rappel d'exécution : %s 'fichier.txt' \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=====Create Socket=====*/
	int sock = createSocket();

	/*=====Verify host=====*/
	server.sin_family = AF_INET;
	hp = gethostbyname(host_id);
	if (hp == (struct hostent *) 0) {
		fprintf(stderr, "%s: unknown host\n", host_id);
		exit(EXIT_FAILURE);
	}
	/*=====Connect to port 25 on remote host=====*/
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port=htons(25); /* SMTP PORT */
	if (connect(sock, (struct sockaddr *) &server, sizeof server)==-1) {
		perror("connecting stream socket");
		exit(EXIT_FAILURE);
	}
	else {
        printf( "Connected to %s\n", host_id);
    }

	/*===== READ FILE ======*/
	char *message = readfile(argv);

	//printf("\n\n filestr : %s\n\n", message);
	SendEmail(sock, from_id, to_id, sub, message);

	//=====Close socket and finish=====*/
	close(sock);
	free(message);
	exit(0);
}
