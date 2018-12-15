#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>
#define NUM_INCREMENTS 10
#define READY 0
#define MEMORYNAME "/baric"
typedef struct {
    sem_t etagere;
    int numberpizza;
		char ready;
} sharedMemory;

void fermeture(sem_t semaphore);
int main(int argc, char const *argv[]) {
sleep(2);
	sharedMemory *shm;
	int fid;
int i;
	int valeur;

	//création de la mémoire partagée
	if((fid=shm_open(MEMORYNAME,  O_RDWR, S_IRUSR | S_IWUSR))==-1){
			perror("SERVEUR shm_open");
	}


			//File mapping (Les parametres doivent correspondres au mode d'ouverture de l'objet POSIX)
			shm = (sharedMemory*) mmap(NULL, sizeof(sharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fid, 0);
			if(shm == MAP_FAILED){
				perror("SERVEUR mmap");
			}
			sem_init(&shm->etagere,1, 3);
		shm->ready = READY;
		printf("SERVER is ready to work\n" );
		while(1){
			if(valeur <3){
				int x=sem_post(&shm->etagere);
				sem_getvalue(&shm->etagere, &valeur);
				printf("SERVEUR valeur%d\n", valeur);
			}

		}






//Unmap
    if(munmap(shm, sizeof(sharedMemory)) == -1)
        perror("SERVEUR munmap");

    //Detacher l'objet POSIX
    shm_unlink(MEMORYNAME);

return 0;
}

void fermeture(sem_t semaphore){
	sem_close(&semaphore);
	sem_destroy(&semaphore);
}
