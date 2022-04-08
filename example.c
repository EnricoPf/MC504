#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct
{

     char answer;
     char try;
     char correct;

} char_block;

void *function1(void *ptr);

char *answer = "poema";

int main()
{

     char_block *char1 = malloc(sizeof(char_block));
     char_block *char2 = malloc(sizeof(char_block));
     char_block *char3 = malloc(sizeof(char_block));
     char_block *char4 = malloc(sizeof(char_block));
     char_block *char5 = malloc(sizeof(char_block));

     char1->answer = answer[0];
     char2->answer = answer[1];
     char3->answer = answer[2];
     char4->answer = answer[3];
     char5->answer = answer[4];

     printf("Aperte T para começar:\n");
     char mode;
     scanf("%c", &mode);

     int attempts = malloc(sizeof(int));
     attempts = 1;
     printf("A palavra tem 5 letras\n");
     int conf1 = malloc(sizeof(int));
     int conf2 = malloc(sizeof(int));
     int conf3 = malloc(sizeof(int));
     int conf4 = malloc(sizeof(int));
     int conf5 = malloc(sizeof(int));
     
     while (mode == 't')
     {

          char try[5];
          printf("\n");
          printf("Tentativa %d. Você possui %d tentativas restantes:\n", attempts, (8 - attempts));
          scanf("%s", try);

          char1->try = try[0];
          char2->try = try[1];
          char3->try = try[2];
          char4->try = try[3];
          char5->try = try[4];

          pthread_t thread1, thread2, thread3, thread4, thread5;
          int iret1, iret2, iret3, iret4, iret5;

          iret1 = pthread_create(&thread1, NULL, function1, (void *)char1);
          iret2 = pthread_create(&thread2, NULL, function1, (void *)char2);
          iret3 = pthread_create(&thread3, NULL, function1, (void *)char3);
          iret4 = pthread_create(&thread4, NULL, function1, (void *)char4);
          iret5 = pthread_create(&thread5, NULL, function1, (void *)char5);

          pthread_join(thread1, (void**) &conf1);
          pthread_join(thread2, (void**) &conf2);
          pthread_join(thread3, (void**) &conf3);
          pthread_join(thread4, (void**) &conf4);
          pthread_join(thread5, (void**) &conf5);

          printf("%c,%c,%c,%c,%c", char1->correct, char2->correct, char3->correct, char4->correct, char5->correct);
          printf("\n");
          if ((conf1 == 1) && (conf2 == 1) && (conf3 == 1) && (conf4 == 1) && (conf5 == 1))
          {
               printf("Acertou!\n");
               mode = 'o';
               break;
          }
          attempts+=1;
     }
     return 0;
}

void *function1(void *entry)
{

     char_block *char_;
     char_ = (char_block *)entry;

     if (char_->try == char_->answer)
     {
          char_->correct = 'C';
          return (void *) 1;
     }
     else if (strchr(answer, char_->try) != NULL)
     {
          char_->correct = 'A';
     }
     else
     {

          char_->correct = 'W';
     }
     return (void*) 0;
}