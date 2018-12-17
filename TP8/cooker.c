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

#define TEMPSCUISSON 4
#define MEMORYNAME "/barica"
#define NUM_INCREMENTS 10
#define READY 0

void fermeture(sem_t semaphore);
void ouverture();


typedef struct {
    sem_t etagere;
    int numberplace;
    int numberpizza;
    int numberlivre;
    char ready;
} sharedMemory;

void initialisation(sharedMemory *shm);

int _start(int argc, char const *argv[]) {
    time_t t;
    srand((unsigned) time(&t));

    int fd;
    sharedMemory *shm;


    ouverture();

    //création de la mémoire partagée
    if((fd=shm_open(MEMORYNAME, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR))==-1){
        perror("shm_open");
    }

    //Taille de la mémoire = indicator + number
    if( ftruncate(fd, sizeof(sharedMemory)) == -1){
        perror("ftruncate");
    }


    //File mapping (Les parametres doivent correspondres au mode d'ouverture de l'objet POSIX)
    shm = (sharedMemory*) mmap(NULL, sizeof(sharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(shm == MAP_FAILED){
        perror("mmap");
    }

    //initialisation du sémaphore
    sem_init(&shm->etagere, 1, 1);

    shm->ready = !READY;
    printf("Ok j'attends un processus qui peut m'aider...\n");
    while(!(shm->ready == READY));

    shm->numberplace=0;
    shm->numberpizza=0;

    while(shm->numberpizza < NUM_INCREMENTS){
        sem_wait(&shm->etagere);
        //regarder si l'étagère est rempli si oui ->cooker pause
        //printf("\nil y a %d places prises sur l'etagere\n ",shm->numberplace);
        if(shm->numberplace >= 3){
            sem_post(&shm->etagere);
            sleep(1);
        }
        //creer la pizza temps random
        else{
            sem_post(&shm->etagere);
            int r=rand()%TEMPSCUISSON + 1;
            // //printf("%d\n",r );
            sleep(r);
            shm->numberplace++;
            shm->numberpizza++;
            sem_wait(&shm->etagere);
            printf(" PIZZAYOLO : j'ai mis la pizza no %d sur l'etagere\n", shm->numberpizza);
            printf(" INFO : il y a %d pizza sur l'étagere\n", shm->numberplace);
            sem_post(&shm->etagere);
            // sleep(2);
        }
    }
    //controler que toute les pizzas soient servies=> etagere =0 cooker en pause et serveur en pause
    // while(shm->numberlivre <= NUM_INCREMENTS){
    //     sem_post(&shm->etagere);
    // }

    // sem_close(serverStart);
    // fermeture(shm->etagere);

    // sem_close(cookerPause);
    // printf("j'ai fermé les semaphore");
    printf("j'ai fini le travail\n" );
    //Unmap
    if(munmap(shm, sizeof(sharedMemory)) == -1) {
        perror("munmap");
    }

    //Detacher l'objet POSIX
    shm_unlink(MEMORYNAME);
    fermeture(shm->etagere);

    return 0;
}

void fermeture(sem_t semaphore){
    sem_close(&semaphore);
    sem_destroy(&semaphore);
}

void ouverture(){
    printf("\n========================================================\n\n" );
    printf("\t Bienvenue à la pizzeria\n\n" );
    printf("========================================================\n\n" );
}

void initialisation(sharedMemory *shm){
    int fd;
    //initialisation du sémaphore
    sem_init(&shm->etagere, 1, 1);
    //création de la mémoire partagée
    if((fd=shm_open("/cp", O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR))==-1){
        perror("shm_open");
    }


    //Taille de la mémoire = indicator + number
    if( ftruncate(fd, sizeof(sharedMemory)) == -1)
    perror("ftruncate");

    //File mapping (Les parametres doivent correspondres au mode d'ouverture de l'objet POSIX)
    shm = (sharedMemory*) mmap(NULL, sizeof(sharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(shm == MAP_FAILED)
    perror("mmap");
}
