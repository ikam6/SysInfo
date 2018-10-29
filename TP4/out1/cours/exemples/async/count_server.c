#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "count_common.h"

#define READING 0
#define WRITING 1
#define DONE    2

typedef struct {
  Counter count;
  int status;
} FDState;

static Counter total = 0;

FDState *allocFDState() {
  FDState *state = malloc(sizeof(FDState));
  if (!state) return NULL;
  state->count = 0;
  state->status = READING; 
  return state;
}

void freeFDState(FDState *state) {
    free(state);
}

void setNonBlocking(int fd){
  int flags = fcntl(fd, F_GETFL, 0);
  fcntl(fd, F_SETFL, flags|O_NONBLOCK);
}

int receiveCount(int fd, FDState *state) {
  int result = read( fd, &(state->count), sizeof(Counter) );
  if (result != sizeof(Counter) ) {
    if( errno == EAGAIN ) {
      return 0;
    } else return -1;
  } else {
    state->status = WRITING;
    return 0;
  }
}

int sendTotal(int fd, FDState *state) {
  int result;
  total += state->count;
  printf( "Sending total=%d\n", total );
  result = write( fd, &total, sizeof(Counter) );
  if( result != sizeof(Counter) ) {
    if (errno == EAGAIN) {
	return 0;
    } else return -1;
  }
  state->status = DONE;
  return 0;
}

void run() {
  int listener;
  FDState *state[FD_SETSIZE];
  struct sockaddr_in sin;
  int i, maxfd;
  fd_set readset, writeset;

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = 0;
  sin.sin_port = htons(9998);

  for (i = 0; i < FD_SETSIZE; ++i)
    state[i] = NULL;

  listener = socket(AF_INET, SOCK_STREAM, 0);
  setNonBlocking(listener);
  
  if (bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
    die( "Cannot bind" );
  }
  if (listen(listener, 16)<0) {
    die( "Cannot Listen" );
  }
 
  printf( "Ready to listen for conections\n" );

  while (1) {
    maxfd = listener;
    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    
    FD_SET(listener, &readset);

    for (i=0; i < FD_SETSIZE; ++i) {
      if (state[i]) {
         if (i > maxfd) 
	   maxfd = i;
	 FD_SET(i, &readset);
	 if( state[i]->status == WRITING) {
	   FD_SET(i, &writeset);
	 }
      }
    }

    if (select(maxfd+1, &readset, &writeset, NULL, NULL) < 0) {
      die( "Cannot select." );
    }

    if (FD_ISSET(listener, &readset)) {
      int fd;
      struct sockaddr_storage ss;
      socklen_t slen = sizeof(ss);
      printf( "Accepting...\n" );
      fd = accept(listener, (struct sockaddr*)&ss, &slen);
      if (fd < 0) {
		die("Accept");
      } else if (fd > FD_SETSIZE) {
		close(fd);
      } else {
		printf( "Accepted: %d\n", fd );
		setNonBlocking(fd);
		state[fd] = allocFDState();
      }
    }

    for (i=0; i < maxfd+1; ++i) {
      int r = 0;
      if (i == listener) continue;
      if (FD_ISSET(i, &readset)) {
		printf( "Reading from %d\n" , i );
		r = receiveCount(i, state[i]);
      }
      if (r == 0 && FD_ISSET(i, &writeset)) {
		printf( "Writing to %d\n" , i );
		r = sendTotal(i, state[i]);
		if ( state[i]->status == DONE ) {
		  printf( "Closing socket: %d\n", i );
		  freeFDState(state[i]);
		  state[i] = NULL;
		  close(i);
		}
      }
    }
  }
}

int main(int argc, char **argv) {
  printf( "MAXIMUM CONNECTIONS: %d\n", FD_SETSIZE );
  run();
  return EXIT_SUCCESS;
}
