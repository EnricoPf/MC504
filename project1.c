#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

void *function1( void *ptr );

int main()
{
    FILE* ptr;
    char curr_word[5];
    ptr = fopen("words.txt","a+");

    if (ptr == NULL){
        printf("Erro ao ler base de palavras\n");
        return 1;
    }

    char all_words[1000][5];
    int counter = 0;
    while (fgets(curr_word,50,ptr)  != NULL){
        strcpy(all_words[counter++],curr_word);
    }
    srand(time(NULL));


    char goal_word[4];
    pthread_t thread1, thread2, thread3, thread4;
    char* letter1,letter2,letter3,letter4;
    letter1 = goal_word[0];
    letter2 = goal_word[1];
    letter3 = goal_word[2];
    letter4 = goal_word[3];
    
    for (int i = 0; i < 4; i++){

    }
    int  iret1, iret2;
    /* Create independent threads each of which will execute function */
    iret1 = pthread_create( &thread1, NULL, function1, (void*) message1);
    iret2 = pthread_create( &thread2, NULL, function1, (void*) message2);
    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL); 
    printf("Thread 1 returns: %d\n",iret1);
    printf("Thread 2 returns: %d\n",iret2);
    exit(0);
}

void *function1( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}