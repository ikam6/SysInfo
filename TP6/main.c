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
#include "fonction.h"




char *host_id="smtp.unige.ch";

//TODO : changer le nom envoyeur, recepteur et sujet du mail ici :
char *from_id = "alexia.lienhard@etu.unige.ch";
char *to_id = "alexia.lienhard@etu.unige.ch";
char *sub = "testmail\r\n";



int sock;




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

/*=====MAIN=====*/
int main(int argc, char* argv[]){
	struct sockaddr_in server;
	struct hostent *hp;
	struct hostent *gethostbyname();

	if (argc != 2){
		printf("Rappel d'exécution : %s 'fichier.txt' \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*=====Create Socket=====*/
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock==-1) {
		perror("opening stream socket");
		exit(EXIT_FAILURE);
	}
	else {
        //printf("socket created\n");
        printf("Trying %s", HELO);
    }
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

	/*===== READ FILE AND SEND EMAIL ======*/

char*message = readfile(argc, argv);
	SendEmail(from_id, to_id, sub, message);
	free(message);
}
