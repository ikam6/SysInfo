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
#include <readline/readline.h>
#include <readline/history.h>


/*=====MAIN=====*/
int main(int argc, char* argv[]){
    char* buf;

    buf = readline("monShell >> ");
    printf("enter 1 : %s\n", buf);
    // int cmp;
    // cmp = strcmp(buf, "exit");
    // printf("cmp : %d", cmp);


    while (strcmp(buf, "exit") != 0) {
        printf("buf : %s\n", buf);
        buf = readline("monShell >> ");
    }
    return 0;
}
