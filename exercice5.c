#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semaphore;
int k=1;

void *func_thread(void* arg)
{
    int tmp = *((int*)arg);
    while(1)
    {
        sem_wait(&semaphore);
        if(tmp<k)
        {
            k=1;
        }
        printf("thread %d\n",k++);
        sem_post(&semaphore);
    }
    pthread_exit(NULL);

}


int main(int argc , char* argv[])
{
    if(argc <2)
    {
        perror("Erreur: nombre d'arguments insuffisants\n");
        printf("Usage: %s entier\n",argv[0]);
    }
    int reponse,rep,n;
    n = atoi(argv[1]);
    pthread_t tab_thread[n];
    rep=sem_init(&semaphore,0,1);
    if(rep == -1)
    {
        perror("Erreur d'initialisation du semaphore\n");
        return 0;
    }
    for(int i=0 ; i<n ; i++)
    {
        reponse = pthread_create(&tab_thread[i],NULL,func_thread,&n);
        if(reponse==-1)
        {
            perror("pthread_create\n");
            return 0;
        }
    }
    for(int i=0 ; i<n ; i++)
        pthread_join(tab_thread[i],NULL);
    return 0;
}
