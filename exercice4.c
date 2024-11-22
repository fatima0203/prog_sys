#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int cpt = 0;
int n;
sem_t semanphore1, semanphore2;

void * func_thread1(void *arg)
{
    while(1)
    {
        for (int i = 1; i <= n; i++)
        {
            sem_wait(&semanphore1);
            cpt++;
            printf("Thread 1 : %d\n", cpt);
            if (cpt == n)
            {
                sem_post(&semanphore2);
            }
            else
            {
                sem_post(&semanphore1);
            }
        }

    }
    pthread_exit(NULL);
}

void * func_thread2(void *arg)
{
    while(1)
    {
        sem_wait(&semanphore2);
        for (int i = 1; i <= n; i++)
        {
            cpt--;
            printf("Thread 2 : %d\n", cpt);
        }
        sem_post(&semanphore1);
    }

   pthread_exit(NULL);
}

int main(int argc ,char* argv[])
{
    pthread_t thread1, thread2;
    int reponse,rep;

    n=atoi(argv[1]);

    reponse=sem_init(&semanphore1, 0, 1);
    if(reponse==-1)
    {
        perror("Erreur dans l'initialisation\n");
        exit(-1);
    }
    reponse=sem_init(&semanphore2, 0, 0);
    if(reponse==-1)
    {
        perror("Erreur dans l'initialisation\n");
        exit(-1);
    }

    rep=pthread_create(&thread1, NULL, func_thread1, NULL);
    if(rep==-1)
    {
        perror("pthread_create\n");
        exit(-1);
    }
    rep=pthread_create(&thread2, NULL, func_thread2, NULL);
    if(rep==-1)
    {
        perror("pthread_create\n");
        exit(-1);
    }


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    sem_destroy(&semanphore1);
    sem_destroy(&semanphore2);


    return 0;
}
