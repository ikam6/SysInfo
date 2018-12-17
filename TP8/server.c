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
#define MEMORYNAME "/barica"
#define TEMPSCUISSON 5

typedef struct {
    sem_t etagere;
    int numberplace;
    int numberpizza;
    int numberlivre;
    char ready;
} sharedMemory;

void fermeture(sem_t semaphore);

int _start(int argc, char const *argv[]) {
    sleep(2);
    sharedMemory *shm;
    int fid;


    //création de la mémoire partagée
    if((fid=shm_open(MEMORYNAME,  O_RDWR, S_IRUSR | S_IWUSR))==-1){
        perror("SERVEUR shm_open");
    }


    //File mapping (Les parametres doivent correspondres au mode d'ouverture de l'objet POSIX)
    shm = (sharedMemory*) mmap(NULL, sizeof(sharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fid, 0);
    if(shm == MAP_FAILED){
        perror("SERVEUR mmap");
    }

    sem_init(&shm->etagere, 1, 1);
    shm->ready = READY;
    printf("SERVER is ready to work\n" );
    shm->numberlivre=1;
    while(shm->numberpizza <= NUM_INCREMENTS && shm->numberlivre <= NUM_INCREMENTS){
        sem_wait(&shm->etagere);
        printf(" INFO : il y a %d pizza sur l'étagere\n", shm->numberplace);
        //controler si il y a une pizza a servir

        if(shm->numberplace==0){
            printf(" SERVEUR: Rien a servir\n" );
            sem_post(&shm->etagere);
            sleep(1);
        }
        else if(shm->numberplace!=0){
            sem_post(&shm->etagere);
            int r=rand()%TEMPSCUISSON + 1;
            sleep(r);
            sem_wait(&shm->etagere);
            printf(" SERVEUR: je sers la pizza %d\n",shm->numberlivre);
            shm->numberplace--;
            shm->numberlivre++;
            sem_post(&shm->etagere);
            //printf(" INFO : il y a %d pizza sur l'étagere\n", shm->numberplace);
            sleep(r);
        }

    }

    //Unmap
    if(munmap(shm, sizeof(sharedMemory)) == -1)
    perror("SERVEUR munmap");

    //Detacher l'objet POSIX
    shm_unlink(MEMORYNAME);

    fermeture(shm->etagere);

    return 0;
}

void fermeture(sem_t semaphore){
    sem_close(&semaphore);
    sem_destroy(&semaphore);
}
