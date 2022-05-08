//Enrico Piovesana Fernandes RA 233895
//Jose Augusto Nascimento A. Marcos RA 200025
//Esse programa é uma adaptação do algoritmo do Jantar dos Selvagens
//Esse algoritmo foi proposto na página 115 da 2° Edição do livro Little Book of Semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//S define o númnero de selvagens, sempre há apenas 1 chefe
#define S 3
//R é o número de refeições que o pote central consegue conter
#define R 6
//MAX_CYCLES define o número máximo de vezes que o chef prepara refeições
#define MAX_CYCLES 3


sem_t sem_pote_cheio;
sem_t sem_pote_vazio;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
            return NULL;
        }
        printf("Selvagem %d se levanta!\n", num);

        sleep(2);

        printf("Selvagem %d se aproxima do pote!\n", num);

        sleep(2);
        
        pthread_mutex_lock(&mutex);

        if (pote <= 0){
            printf("Não há mais comida! Selvagem %d vai acordar o chef!\n", num);
            sleep(1);
            sem_post(&sem_pote_vazio);
            sem_wait(&sem_pote_cheio);
        }

        printf("Selvagem %d come!\n", num);
        sleep(3);
        printf("Selvagem %d se deita!\n", num);
        sleep(num+1);
        pote -= 1;

        pthread_mutex_unlock(&mutex);
    }
}

void* chef(void* aux){
    //o chef segue o seguinte codigo base
    //while True: 
    // botacomida(M)

    while (1){

        if (ciclos <= 0){

            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        sem_wait(&sem_pote_vazio);
        printf("Chef acorda!\n");
        sleep(2);
        printf("Chef cozinhou e encheu o pote!\n");
        sleep(1);
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
    
    //inicializamos os selvagens

    
    pthread_create(&thread_chef, NULL, chef, (void*) &pote);

    for  (int i = 0; i < S; i++){
        sav_id[i] = i;
        pthread_create(&thr[i], NULL, savage, ((void*) &sav_id[i]));
    }

    pthread_join(thread_chef,NULL);

    for (int i = 0; i < S; i++){

        pthread_join(thr[i],NULL);
    }    

    sem_destroy(&sem_pote_cheio);
    sem_destroy(&sem_pote_vazio);
    return 0;
}