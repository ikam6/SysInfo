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


void fermeture(sem_t semaphore){
    sem_close(&semaphore);
    sem_destroy(&semaphore);
}

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

    if(sem_init(&shm->etagere, 1, 1) < 0){
        perror("Semaphore error : ");
        exit(0);
    }

    shm->ready = READY;

    printf("SERVEUR is ready to work\n" );
    shm->numberlivre=1;
    while(shm->numberlivre <= NUM_INCREMENTS){
        sem_wait(&shm->etagere);
        // printf(" INFO : il y a %d pizza sur l'étagere\n", shm->numberplace);
        //controler si il y a une pizza a servir

        if(shm->numberplace==0){
            printf(" SERVEUR: Rien a servir\n" );
            sem_post(&shm->etagere);
            sleep(2);
        }
        else if(shm->numberplace!=0){
            sem_post(&shm->etagere);
            int r=rand()%TEMPSCUISSON + 1;
            sleep(r);
            sem_wait(&shm->etagere);
            shm->numberplace--;
            printf(" SERVEUR: je sers la pizza %d, il reste %d pizza sur l'etagere\n",shm->numberlivre, shm->numberplace);
            shm->numberlivre++;
            sem_post(&shm->etagere);
            //printf(" INFO : il y a %d pizza sur l'étagere\n", shm->numberplace);
            //sleep(r);
        }
    }
    printf("Voila, tout est servi\n");
    // printf(" ---> ERRORCHECK  : livre %s, place %s, pizza %s \n",  );

    int destroy = sem_destroy(&shm->etagere);
    if(destroy < 0)
    perror("SERVEUR sem_destroy error");
    printf("HERE after destroy, %d\n", destroy);

    // int semClose = sem_close(&shm->etagere);
    // if(semClose < 0)
    // perror("SERVEUR sem_close error");
    // printf("HERE after sem_close, %d\n", semClose);

    // //Unmap
    int munMap = munmap(shm, sizeof(sharedMemory));
    if(munmap(shm, sizeof(sharedMemory)) == -1)
    perror("SERVEUR munmap error");

    printf("HERE after munmap, %d\n", munMap);

    //Detacher l'objet POSIX
    int shmUnl = shm_unlink(MEMORYNAME);
    if(shmUnl < 0)
    perror("SERVEUR smh_unlink error");

    printf("HERE after shm_unlike, %d\n", shmUnl);


		exit(EXIT_SUCCESS);
    return 0;
}
