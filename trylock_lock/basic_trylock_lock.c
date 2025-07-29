#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define NOF_THREADS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
    int thread_id = pthread_self(); // Get the thread ID
    printf("Process %d is running thread %d \n", getpid(), thread_id);
    if(pthread_mutex_trylock(&mutex) ==0) {
        printf("Thread %d got the lock.\n", thread_id);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else{
        printf("Thread %d didn't get the lock.\n", thread_id);
    }
    return NULL;
}

int main(){
    pthread_t th[NOF_THREADS];
    pthread_mutex_init(&mutex, NULL);
    for(int i=0; i< NOF_THREADS; i++) {
        if(pthread_create(&th[i], NULL, &thread_function, NULL) != 0){
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i< NOF_THREADS; i++) {
        if(pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}