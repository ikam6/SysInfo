#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void builtinExit(char line){

		printf("==================================================\n\n");
		printf("\tbye, see you soon in (S)Hell\n\n");
		printf("==================================================\n\n");
		raise(SIGTERM);
}

void builtinCd(int argc, char *argv[]){
	char cwd[1000];
	int ret;
	getcwd(cwd, sizeof(cwd));
	printf("%s \n", cwd);

	strcat(cwd,"/");
	strcat(cwd, argv[1]);
	ret=chdir(cwd);

	if (ret==-1){
			perror("error");
		}
}
