#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

bool recuperation_donnees(int argc, char *argv[])
{

   bool option_f= false;
   bool option_t=false;
   int i;
   char c[]="f:t:";
   int IsOptionHere;



   while ((IsOptionHere = getopt(argc, argv, c))!= -1)
   switch (IsOptionHere) {
    case 'f':
          option_f=true;
          break;
    case 't':
          option_t=true;
          break;
    }

    return option_f, option_t;

}

/*
int main(int argc, char *argv[])
{
  recuperation_donnees(argc, argv);
  return EXIT_SUCCESS;
}
*/
