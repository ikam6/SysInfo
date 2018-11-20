#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#define BUFF_SIZE 2

void die(char *issue) {
  perror(issue);
  exit(EXIT_FAILURE);

}

int copy(int from, int to) {
  char buf[BUFF_SIZE];
  ssize_t nread;

  while( nread = read(from, buf, sizeof buf), nread > 0 ) {
		
		char *out_ptr = buf;
    ssize_t nwritten;
    do {
      nwritten = write(to, out_ptr, nread);
      if (nwritten >= 0) {
        nread -= nwritten;
        out_ptr += nwritten;
      } else if (errno != EINTR) {
        return -1;
      }

    } while (nread > 0);
  }

  return nread;
}
