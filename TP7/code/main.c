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
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_LEN 1024

int main(){
    char line[BUFFER_LEN];  //get command line
    char* argv[100];        //user command
    char* path= "";    //set path at bin
    char progpath[20];      //full file path
    int argc;               //arg count
printf("===================================================\n\n");
printf ("\t\tWelcome in (S)Hell\n\n");
printf("===================================================\n\n");
while(1){

    printf("(S)hell>> ");                    //print shell prompt

		if(!fgets(line, BUFFER_LEN, stdin))
		    raise(SIGTERM);
		size_t length = strlen(line);

		if (line[length - 1] == '\n'){
		    line[length - 1] = '\0';
                                      //if user hits CTRL+D break
    }
    if(strcmp(line, "exit")==0){            //check if command is exit
			printf("==================================================\n\n");
			printf("\tbye, see you soon in (S)Hell\n\n");
			printf("==================================================\n\n");
			raise(SIGTERM);
			//break;

    }

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
		if(strcmp(argv[0], "cd")==0){

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
    int pid= fork();              //fork child
		printf("pid : %d\n", pid);

    if(pid==0){               //Child
        execvp(progpath,argv);
        fprintf(stderr, "Child process could not do execvp\n");
				raise(SIGTERM);
			}
			else{                    //Parent
        // wait(NULL);
				int status;
				pid_t w;
				w=waitpid(pid,&status,WUNTRACED);
				if(w==-1){
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

        printf("Child exited with %d\n", WEXITSTATUS(status));
    }
}
}
