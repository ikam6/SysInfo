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
#include <semaphore.h>

int main(int argc, char const *argv[]) {
	sem_t serverStart;
	sem_t cookerPause;
	sem_t etagere;
int pizza=0;
sem_init(&serverStart, 0, 1);

sem_init(&cookerPause, 0, 1);
sem_init(&etagere, 0, 3);
while(pizza<10){
//regarder si l'étagère est rempli si oui ->cooker pause

//creer la pizza temps random
printf("je mets la pizza no %d sur l'etagere", pizza);
//ajouter la pizza à l'étagère
//servir pizza->serverStart





}
//controler que toute les pizzas soient servies== etagere =0 cooker en pause et serveur en pause


sem_close(&serverStart);
sem_close(&etagere);
sem_close(&cookerPause);


	return 0;
}
