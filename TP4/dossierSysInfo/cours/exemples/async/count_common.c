#include <stdlib.h>
#include <stdio.h>
#include "count_common.h"

inline void die( const char *msg ) {
  perror( msg );
  exit(EXIT_FAILURE);
}

