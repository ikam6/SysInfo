/*--------------------------------------------------------/
    Code fait par :
    Lienhard Alexia
    et
    Smiljkovic Marko
/--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void builtinExit(char *line)
{
	if(strcmp(line, "exit")==0){            //check if command is exit
		printf("\n");
		printf("==================================================\n\n");
		printf("\t\tBye Bye \n\n\tSee you soon in (S)Hell\n\n");
		printf("==================================================\n\n");
		exit(EXIT_FAILURE);

		//break;
	}
}

void builtinCd(char* argv[], char *cwd)
{
	getcwd(cwd, sizeof(cwd));
	// printf("%s \n", cwd);

	strcat(cwd,"/");
	strcat(cwd, argv[1]);
	int ret;

	ret=chdir(cwd);
	// printf("%d\n",ret );
	if (ret==-1){
		perror("error");
	}

	//chmod(argv[1],442);
	printf("Going to : %s\n",cwd );
}
