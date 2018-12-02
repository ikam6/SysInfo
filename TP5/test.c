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

int main(){
        int i;
        unsigned char buffer[8];
        int fd = open("/dev/urandom", O_RDONLY);
        read(fd, buffer, 8);
        //buffer now contains the random data
        close(fd);
        for(i = 0; i < 8; ++i)
                printf("%02X \n", buffer[i]);
        printf("\n");
        return 0;

}
