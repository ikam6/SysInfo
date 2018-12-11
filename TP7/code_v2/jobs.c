/*--------------------------------------------------------/
    Code fait par :
    Lienhard Alexia
    et
    Smiljkovic Marko
/--------------------------------------------------------*/

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
#include "builtin.h"

#define BUFFER_LEN 1024
#define PATHLENGTH 1024
#define LASTCHAR	2

/////////////////////////////////////
//-------- Signal functions -------//
////////////////////////////////////

pid_t BG_pid;
pid_t FG_pid;

void sigchldHandler(int signum, siginfo_t *info, void *notused)
{
	int status;
	if(BG_pid==info->si_pid){

		waitpid(BG_pid,&status,WUNTRACED);
		printf("\nBackground job exited with the status :%d\n ", status);
	}
}

void sigintHandler(int signum, siginfo_t *info, void *notused)
{
	if(FG_pid!=0){

		kill(FG_pid, SIGKILL);
	}
	if(BG_pid!=0){

		kill(BG_pid, SIGKILL);
	}

}

void sighupHandler(int signum, siginfo_t *info, void *notused)
{
	if(FG_pid!=0){
		kill(FG_pid, SIGKILL);
	}
	if(BG_pid!=0){
		kill(BG_pid, SIGKILL);
	}
	exit(EXIT_SUCCESS);
}





///////////////////////////////////
//------- Jobs function ---------//
///////////////////////////////////

void jobs(int length, char *line)
{

    char* argv[100];        //user command
	char* path= "";    		//set path at bin
	char progpath[20];      //full file path


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

            // show what the user enters :
            // int argc = i;                           //get arg count
            // for(i=0; i<argc; i++){
            //     printf("%s\n", argv[i]);      //print command/argv
            // }

            // making the program path :
            strcpy(progpath, path);           //copy /bin/ to file path
            strcat(progpath, argv[0]);            //add program to path
            for(i=0; i<strlen(progpath); i++){    //delete newline
                if(progpath[i]=='\n'){
                    progpath[i]='\0';
                }
            }

            // printf("\n progpath : %s\n", progpath);

            if(execvp(progpath,argv)==-1){
                perror(progpath);
                fprintf(stderr, "\nChild process could not do execvp\nIgnore if used \"cd\"\n");
            }

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
        char cwd[PATHLENGTH];
        char *token;                  //split command into separate strings
        token = strtok(line," ");
        int i=0;
        while(token!=NULL){
            argv[i]=token;
            token = strtok(NULL," ");
            i++;
        }
        argv[i]=NULL;                     //set last value to NULL for execvp

        // show what the user enters :
        // int argc = i;                           //get arg count
        // for(i=0; i<argc; i++){
        //     printf("%s\n", argv[i]);      //print command/argv
        // }

        // making the program path :
        strcpy(progpath, path);           //copy /bin/ to file path
        strcat(progpath, argv[0]);            //add program to path
        for(i=0; i<strlen(progpath); i++){    //delete newline
            if(progpath[i]=='\n'){
                progpath[i]='\0';
            }
        }

        // Builtin command : control for cd line
        if(strcmp(argv[0], "cd")==0){ //built in CD à mettre en module
            getcwd(cwd, sizeof(cwd)); //to get the current directory pathname
            builtinCd(argv, cwd);
        }

        FG_pid= fork();              //fork child
        if(FG_pid==0){               //Child
            execvp(progpath,argv);
            fprintf(stderr, "\nChild process could not do execvp\nIgnore if used \"cd\"\n");
            exit(EXIT_FAILURE); //so the child is not added in ps
        }
        else{                    //Parent
            // wait(NULL);
            int status;
            waitpid(FG_pid,&status,0);
            printf("\nChild exited with %d\n\n", WEXITSTATUS(status));
        }
    }
}
