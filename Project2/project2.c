//Enrico Piovesana Fernandes RA 233895
//Jose Augusto Nascimento A. Marcos RA 200025
//Esse programa é uma adaptação do algoritmo do Jantar dos Selvagens
//Esse algoritmo foi proposto na página 115 da 2° Edição do livro Little Book of Semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//N define o númnero de selvagens, sempre há apenas 1 chefe
#define S 3
//M é o número de refeições que o pote central consegue conter
#define R 8
#define MAX_CYCLES 10


sem_t sem_pote_cheio;
sem_t sem_pote_vazio;
sem_t sem_mutex;
int pote = R;
int ciclos = MAX_CYCLES;

/*
mutex . wait ()
2 # critical section
3 count = count + 1
4 mutex . signal ()
*/


void* savage(void *numero_selvagem){
    //O selvagem segue o seguinte codigo base
    //while True: 
    // pegacomida()
    // come()

    int num = *(int*)numero_selvagem;

    while (1){
        if (ciclos <= 0){
            return;
        }
        sem_wait(&sem_mutex);
            if (pote == 0){
                sem_post(&sem_pote_vazio);
                sem_wait(&sem_pote_cheio);
            }
        pote -= pote;
        printf("Selvagem %d comeu!", &num);
        sem_post(&sem_mutex);
    }
    return;
}

void* chef(void* aux){
    //o chef segue o seguinte codigo base
    //while True: 
    // botacomida(M)

    while (1){
        if (ciclos <= 0){
            return;
        }
        sem_wait(&sem_pote_vazio);
        pote = R;
        ciclos -= 1;
        sem_post(&sem_pote_cheio);
    }
}

int main() {

    //declaracao das threads
    pthread_t thr[S], thread_chef;
    int sav_id[S];
    
    sem_init(&sem_pote_cheio, 0, 0);
    sem_init(&sem_pote_vazio, 0, 0);
    sem_init(&sem_mutex, 0, 0);

    //inicializamos os selvagens
    pthread_create(&thread_chef, NULL, chef, (void*) &pote);
    for  (int i = 0; i < S; i++){
        sav_id[i] = i;
        pthread_create(&thr[i], NULL, savage, ((void*) &sav_id[i]));
    }

    

    for (int i = 0; i < S; i++){
        pthread_join(thr[i],NULL);
    }    

    sem_destroy(&sem_pote_cheio);
    sem_destroy(&sem_pote_vazio);
    sem_destroy(&sem_mutex);
    return;
}