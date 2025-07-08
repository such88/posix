#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <pthread.h>

#define NO_OF_THREAD 8
#define NO_OF_ITERATIONS 1000000

volatile int mail =0;
pthread_mutex_t mutex;

void *routine(void *arg){

    for(unsigned int count=0; count < NO_OF_ITERATIONS; count++){
        pthread_mutex_lock(&mutex);
        mail++;
        pthread_mutex_unlock(&mutex);
    }

}

int main(){
    pthread_t th[NO_OF_THREAD];
    pthread_mutex_init(&mutex, NULL);

    // Below implementation creates threads and waits for them to finish one by one.
    // This is not the most efficient way to handle threads, but it ensures that each thread completes before the next one starts.
    printf("Starting threads...\n");
    // for(int i=0; i< NO_OF_THREAD; i++){
    //     if(pthread_create(th + i, NULL, routine, NULL) != 0){
    //         perror("Failed to create thread");
    //         exit(EXIT_FAILURE);
    //     }
    //     printf("Thread %d started\n", i);
    //     if(pthread_join(th[i],NULL) != 0){
    //         perror("Failed to join thread");
    //         exit(EXIT_FAILURE);
    //     }

    //     printf("Thread %d finished\n", i);
    // }


    // More efficient way to create threads and wait for all of them to finish
    for(int i=0; i< NO_OF_THREAD; i++){
        if(pthread_create(th + i, NULL, routine, NULL) != 0){
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
        printf("Thread %d started\n", i);
    }
    for(int i=0; i< NO_OF_THREAD;i++) {
        if(pthread_join(th[i],NULL) != 0){
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
        printf("Thread %d finished\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Final value of mail: %d\n", mail);
}