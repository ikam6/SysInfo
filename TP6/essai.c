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
//TODO chercher automatiquement l'adresse IP
#define HELO "HELO 192.168.1.1\r\n"
#define DATA "DATA\r\n"
#define QUIT "QUIT\r\n"
#define MAX 256

struct sockaddr_in server;
struct hostent *hp;
struct hostent *gethostbyname();

int sock;
char *host_id="smtp.unige.ch";

const char sub[MAX];
char wkstr[100]="hello how r u\r\n";


void die(char *issue) {
  perror(issue);
  exit(EXIT_FAILURE);
}

void read_socket()
{
	char buf[BUFSIZ+1];
	int len;

	len = read(sock,buf,BUFSIZ);

	write(1,buf,len);
	memset(buf,1, sizeof(buf));

}

/*=====Send a string to the socket=====*/
void send_socket(char *s)	{
	write(sock,s,strlen(s));
	write(1,s,strlen(s));
		}

void SendEmail(char* from_id, char* to_id, char* sub, char* wkstr ){
	/*=====Write some data then read some =====*/
/* SMTP Server logon string */
	read_socket();

	/* introduce ourselves */
	send_socket(HELO);

	/*Read reply */
	read_socket();

	/*intruduce sender*/
	send_socket("MAIL FROM: ");
	send_socket(from_id);
	send_socket("\r\n");

	 /* sender OK */
	read_socket();
	send_socket("VRFY ");
	send_socket(from_id);
	send_socket("\r\n");
	read_socket();

	/*introduce Recipient*/
	send_socket("RCPT TO: "); /*Mail to*/
	send_socket(to_id);
	send_socket("\r\n");

	/* Recipient OK*/
	read_socket();

	// body to follow*/
	send_socket(DATA);
	send_socket("subject: ");
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
	void verifyHost(struct hostent* hp, char* host_id){
		server.sin_family = AF_INET;
		hp = gethostbyname(host_id);
		if (hp==(struct hostent *) 0)
		 {
		 		fprintf(stderr, "%s: unknown host\n", host_id);
					 exit(2);
			   }
			 }
	/*=====MAIN=====*/

int main(int argc, char* argv[]){
char* from_id;
char* to_id;
char* sub;

/*=====Initialisation======*/
	//TODO mettre a 5, et verifier le file.txt
	//TODO mettre exemple
	if (argc != 4) {
		fprintf(stderr, "USAGE: %s <Email address FROM> <Email addres TO>
									<subject><File.txt>\n 
		EXEMPLE: prenom.nom@unige.ch prenom.nom@etu.unige.ch SUJET File.txt\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	from_id = argv[1];
	to_id = argv[2];
	sub= argv[3];
	//file = argv[4];

/*=====Create Socket=====*/
sock = socket(AF_INET, SOCK_STREAM, 0);

	    if (sock==-1)
	    {
	     perror("opening stream socket");
	     exit(1);
	    }

	    else

	      printf ("socket created\n");


} /*=====Verify host=====*/
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

			SendEmail(from_id, to_id, sub, wkstr);
		}
