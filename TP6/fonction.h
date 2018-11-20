#ifndef __include_fonction_h__
#define __include_fonction_h__
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
extern int sock;
int createSocket();
void read_socket();
void send_socket(char *s);
char* readfile(int argc, char *argv[]);
void SendEmail(char* from_id, char* to_id, char* sub, char* wkstr );
#endif /* #ifndef __include_fichier_h__ */
