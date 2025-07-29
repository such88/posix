#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define SHARED_BUFFER_SIZE 10
#define THREAD_COUNT 20
#define CONSUMER_COUNT 2

int shared_buffer[SHARED_BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutexBuffer = PTHREAD_MUTEX_INITIALIZER;

sem_t semFull;
sem_t semEmpty;

void * producer(void *arg) {
    while(1) {
        // produce an item
        int x = rand() %1000;
        sleep(1); // Simulate time taken to produce an item
        printf("thread %u: Produced %d\n", *(int *)arg, x);
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        shared_buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
    return NULL;
}

void *consumer(void *arg) {
    while(1) {
        int y;
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        y = shared_buffer[count - 1];
        shared_buffer[count - 1] = -1;
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);
        printf("thread %u: got %d\n", *(int *)arg, y);
        sleep(1);
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    pthread_t th[THREAD_COUNT];
    sem_init(&semEmpty, 0, SHARED_BUFFER_SIZE);
    sem_init(&semFull, 0, 0);

    int i;
    for(i =0; i< THREAD_COUNT; i++) {
        int *arg = (malloc(sizeof(int)));
        if(arg == NULL) {
            perror("failed to allocate memory for thread argument");
            exit(EXIT_FAILURE);
        }
        *arg = i;
        if( i%2 ==0){
            if(pthread_create(&th[i], NULL, &producer, arg) !=0 ) {
                perror("failed to create producer thread");
            }
        } else{
            if(pthread_create(&th[i], NULL, &consumer, arg) !=0 ) {
                perror("failed to create consumer thread");
            }
        }
    }

    for(i =0; i< THREAD_COUNT; i++) {
        if(pthread_join(th[i], NULL) != 0) {
            perror("failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexBuffer);
    sem_destroy(&semFull);
    sem_destroy(&semEmpty);
    return 0;
}