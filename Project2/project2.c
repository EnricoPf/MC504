//Enrico Piovesana Fernandes RA 233895
//Esse programa é uma adaptação do algoritmo do Jantar dos Selvagens
//Esse algoritmo foi proposto na página 115 da 2° Edição do livro Little Book of Semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//N define o númnero de selvagens, sempre há apenas 1 chefe
#define N 3
//M é o número de refeições que o pote central consegue conter
#define M 8
#define MAX_CYCLES 10


sem_t sem_pote[M];



void* savage(void *aux){
    //O selvagem segue o seguinte codigo base
    //while True: 
    // pegacomida()
    // come()



    return;
}

void* chef(void* aux){
    //o chef segue o seguinte codigo base
    //while True: 
    // botacomida(M)
}

int main() {
    pthread_t thr[N];
    int sav_id[N];

    sem_init(&sem_pote, 0, M);

    //inicializamos os selvagens
    for  (int i = 0; i < N; i++){
        sav_id[i] = i;
        pthread_create(&thr[i], NULL, savage, ((void*) &sav_id[i]));
    }

    for (int i = 0; i < N; i++){
        pthread_join(thr[i],NULL);
    }    

    sem_destroy(&sem_pote)
}