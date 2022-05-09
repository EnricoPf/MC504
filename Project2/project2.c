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

/*
mapa dos status na animação:

selvagens: 0 - esperando (wai)
           1 - comendo (eat)
           2 - pegando (pic)
           3 - acordando o chef (wup)
           4 - cheio (zzz)

cozinheiro: 0 - dormindo (zzz)
            1 - acorda (!!!)
            2 - enche (fil)

*/


int status_selvagens[S];
int status_cozinheiro = 0;

sem_t sem_pote_cheio; //semaforo para avisar aos selvagens que o pote está cheio
sem_t sem_pote_vazio; //semaforo para avisar o chef que o pote esta vazio

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex

int pote = R;
int ciclos = MAX_CYCLES;

/*
                ALDEIA 
 ______________________________________
|                                      |
| eat  eat  eat      pic     wup   !!! |              
|  0    1    2        1       1     3  |     
| M00  M01  M02       P       W     C  | 
|______________________________________|
QUANTIDADE POTE: X

*/

void imprimirAldeia(){

    //top print
    printf("                ALDEIA\n");
    printf(" ______________________________________\n");
    printf("|                                      |\n");

    //mid print - selvagens

    printf("|");

    for(int i = 0; i < S; i++){ //status de quem está nas mesas

        if (status_selvagens[i] == 0){
            printf(" wai ");
        }
        else if (status_selvagens[i] == 1){
            printf(" eat ");
        }
        else if (status_selvagens[i] == 4){
            printf(" zzz ");
        }
        else{
            printf("     ");
        }
    }
    printf("    ");

    int is_pote = 0;

    for(int i = 0; i < S; i++){ //status de quem está pegando comida no pote

        if (status_selvagens[i] == 2){
            printf(" pic ");
            is_pote = 0;
            break;
        }
        else{
            is_pote = 1;
        }
    }
    if (is_pote == 1){
        printf("     ");
        is_pote = 0;
    }

    printf("   ");

    for(int i = 0; i < S; i++){ //status de alguem que esta acordando o cozinheiro

        if (status_selvagens[i] == 3){
            printf(" wup ");
            is_pote = 0;
            break;
        }
        else{
            is_pote = 1;
        }
    }
    if (is_pote == 1){
        printf("     ");
        is_pote = 0;
    }
    printf(" ");

    //mid print - cozinheiro

    if (status_cozinheiro == 0){
        printf(" zzz ");
    }
    else if (status_cozinheiro == 1){
        printf(" !!! ");
    }
    else{
        printf(" fil ");
    }

    printf("|\n");

    //mid print - selvagens

    printf("|");
    for(int i = 0; i < S; i++){ //quem esta nas mesas
        
        if (status_selvagens[i] == 0 || status_selvagens[i] == 1 || status_selvagens[i] == 4){
            printf("  %d  ", i);
        }
        else{
            printf("     ");
        }
    }
    printf("     ");

    for(int i = 0; i < S; i++){

        if (status_selvagens[i] == 2){ //quem esta enchendo
            printf(" %d   ", i);
            is_pote = 0;
            break;
        }
        else{
            is_pote = 1;
        }
    }
    if (is_pote == 1){
        printf("     ");
        is_pote = 0;
    }

    printf("    ");

    for(int i = 0; i < S; i++){ //quem esta acordando

        if (status_selvagens[i] == 3){
            printf("%d    ", i);
            is_pote = 0;
            break;
        }
        else{
            is_pote = 1;
        }
    }
    if (is_pote == 1){
        printf("     ");
        is_pote = 0;
    }
    printf(" 3  |\n");


    //bottom print

    printf("| M00  M01  M02       P       W     C  |\n");
    printf("|______________________________________|\n");
    printf("\n");
    printf("QUANTIDADE POTE: %d", pote);
    printf("\n");
    printf("\n");
    printf("\n");

}




void* savage(void *numero_selvagem){
    //O selvagem segue o seguinte codigo base
    //while True: 
    // pegacomida()
    // come()

    int num = *(int*)numero_selvagem;

    while (1){

        sleep(random()%3);

        if (ciclos <= 0 && pote <= 0){
            status_selvagens[num] = 4;
            return NULL;
        }
        
        pthread_mutex_lock(&mutex);

        status_selvagens[num] = 2;

        imprimirAldeia();

        if (pote <= 0){
            status_selvagens[num] = 3;
            imprimirAldeia();

            sem_post(&sem_pote_vazio);
            sem_wait(&sem_pote_cheio);
            status_selvagens[num] = 2;
            imprimirAldeia();
        }
        pote -= 1;
        status_selvagens[num] = 1;
        imprimirAldeia();

        status_selvagens[num] = 0;
        imprimirAldeia();
        pthread_mutex_unlock(&mutex);
    }
}

void* chef(void* aux){
    //o chef segue o seguinte codigo base
    //while True: 
    // botacomida(M)

    while (1){

        if (ciclos <= 0){
            status_cozinheiro = 0;
            imprimirAldeia();
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        sem_wait(&sem_pote_vazio);

        sleep(random()%3);
        status_cozinheiro = 1;
        imprimirAldeia();

        status_cozinheiro = 2;
        pote = R;
        imprimirAldeia();

        status_cozinheiro = 0;
        imprimirAldeia();
        ciclos -= 1;
        sem_post(&sem_pote_cheio);
    }
}

int main() {

    //declaracao das threads
    
    pthread_t thr[S], thread_chef;
    int sav_id[S];

    //selvagens começam esperando e o pote

    for(int i = 0; i < S; i++){
        status_selvagens[i] = 0;
    }

    imprimirAldeia();
    
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

    imprimirAldeia();

    //destroy

    sem_destroy(&sem_pote_cheio);
    sem_destroy(&sem_pote_vazio);
    return 0;
}