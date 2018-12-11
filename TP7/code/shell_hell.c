
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "parsing.h"
#include "builtin.h"

#define BUFFER_LEN 1024
#define LASTCHAR	2
pid_t BG_pid;
pid_t FG_pid;

void sigchldHandler(int signum, siginfo_t *info, void *notused)
{

	   int status;
		  if(BG_pid==info->si_pid){

				waitpid(BG_pid,&status,WUNTRACED);
		   printf("\nbackground job exited with the status :%d\n ", status);
}
}
void sigintHandler(int signum, siginfo_t *info, void *notused){

	if(FG_pid!=0){

		kill(FG_pid, SIGKILL);
	}
if(BG_pid!=0){

	kill(BG_pid, SIGKILL);
}

}

void sighupHandler(int signum, siginfo_t *info, void *notused){

	if(FG_pid!=0){
		kill(FG_pid, SIGKILL);
	}
	if(BG_pid!=0){
	kill(BG_pid, SIGKILL);
}
exit(EXIT_SUCCESS);
}

int main(){
    char line[BUFFER_LEN];  //get command line
    char* argv[100];        //user command
    char* path= "";    			//set path at bin
    char progpath[20];      //full file path
    int argc;               //arg count

printf("===================================================\n\n");
printf ("\t\tWelcome in (S)Hell\n\n");
printf("===================================================\n\n");
while(1){

    printf("(S)hell>> ");                    //print shell prompt

		if(!fgets(line, BUFFER_LEN, stdin))
		    break;
		size_t length = strlen(line);

		if (line[length - 1] == '\n'){
		    line[length - 1] = '\0';
			}

			if(strcmp(line, "exit")==0){            //check if command is exit
				printf("==================================================\n\n");
				printf("\tbye, see you soon in (S)Hell\n\n");
				printf("==================================================\n\n");
				break;
				//break;

			}
			//case :  background job
    if  (line[length - LASTCHAR] == '&'){
				line[length - LASTCHAR] = '\0';
			printf("-> this action will be executed in background\n");

			 BG_pid= fork();              //fork child
			if(BG_pid==0){               //Child
				stdin=freopen("/dev/null/","w",stdin); //redirction sur une autre entrée
				char *token;                  //split command into separate strings
				token = strtok(line," ");
				int i=0;
				while(token!=NULL){
						argv[i]=token;
						token = strtok(NULL," ");
						i++;
				}
				argv[i]=NULL;                     //set last value to NULL for execvp

				argc=i;                           //get arg count
				for(i=0; i<argc; i++){
						printf("%s\n", argv[i]);      //print command/argv
				}
				strcpy(progpath, path);           //copy /bin/ to file path
				strcat(progpath, argv[0]);            //add program to path

				for(i=0; i<strlen(progpath); i++){    //delete newline
						if(progpath[i]=='\n'){
								progpath[i]='\0';
						}
				}

				if(execvp(progpath,argv)==-1){
					perror(progpath);
				}
				fprintf(stderr, "Child process could not do execvp\n");
				//break
				}
				else{                    //Parent
					 signal(SIGQUIT,SIG_IGN);
					 signal(SIGTERM,SIG_IGN);


					struct sigaction chld_act;
					chld_act.sa_flags=SA_SIGINFO|SA_RESTART;
					chld_act.sa_sigaction=sigchldHandler;

					struct sigaction int_act;
					int_act.sa_flags=SA_SIGINFO|SA_RESTART;
					int_act.sa_sigaction=sigintHandler;

					struct sigaction hup_act;
					hup_act.sa_flags=SA_SIGINFO|SA_RESTART;
					hup_act.sa_sigaction=sighupHandler;

					sigaction(SIGCHLD,&chld_act,NULL);
					sigaction(SIGINT,&int_act,NULL);
					sigaction(SIGHUP,&hup_act,NULL);

					}
				}
else{

		char cwd[1000];
    char *token;                  //split command into separate strings
    token = strtok(line," ");
    int i=0;
    while(token!=NULL){
        argv[i]=token;
        token = strtok(NULL," ");
        i++;
    }
    argv[i]=NULL;                     //set last value to NULL for execvp

    argc=i;                           //get arg count
    for(i=0; i<argc; i++){
        printf("%s\n", argv[i]);      //print command/argv
    }
    strcpy(progpath, path);           //copy /bin/ to file path
    strcat(progpath, argv[0]);            //add program to path

    for(i=0; i<strlen(progpath); i++){    //delete newline
        if(progpath[i]=='\n'){
            progpath[i]='\0';
        }
    }
		if(strcmp(argv[0], "cd")==0){ //built in CD à mettre en module

			getcwd(cwd, sizeof(cwd));
			printf("%s \n", cwd);

			strcat(cwd,"/");
			strcat(cwd, argv[1]);
			int ret;

			ret=chdir(cwd);
			if (ret==-1){
				perror("error");
			}
			printf("%d\n",ret );
			//chmod(argv[1],442);
			printf(" coucou %s\n",cwd );
}

    FG_pid= fork();              //fork child
    if(FG_pid==0){               //Child

				execvp(progpath,argv);
        fprintf(stderr, "Child process could not do execvp\n");
				exit(EXIT_FAILURE);
			}
			else{                    //Parent
        // wait(NULL);
				int status;


				waitpid(FG_pid,&status,0);

        printf("Child exited with %d\n", WEXITSTATUS(status));
    }
	}
}
}
