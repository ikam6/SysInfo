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
   int alorsla;

   while (( alorsla = getopt(argc, argv, c))!= -1)
   switch (alorsla) {
     case 'f':
            printf("on a du f maggle");
            option_f=true;
            break;
    case 't':
          printf("on a du t t'as vu");
          option_t=true;
          break;

   }

/*for (i=1;i<argc;i++)
{
  printf("%d %s\n",i, argv[i]);
  c=getopt(argc, argv, "f");
  printf(" celui la %d\n",c);
  if (optopt =="-f")
  {
    printf("ok -f");
    option_f=true;
  }

  if (argv[i]=="-t")
  {
    printf("ok -t");
    option_f=true;
  }
}*/

    return option_f,option_t;

  }

int main(int argc, char *argv[])
{

  recuperation_donnees(argc, argv);
  return EXIT_SUCCESS;
}
