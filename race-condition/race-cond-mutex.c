/*! Race condition and mutex to */

#include<stdio.h>
#include<stdlib.h>  // For standard I/O and memory allocation
#include<unistd.h>  // For sleep function
#include<pthread.h> // For pthreads
#include<stdbool.h> // For boolean type

#define NUM_THREADS 4
#define NUM_ITERATIONS 1000000
volatile int mail = 0; // Shared counter variable
int lock=0;
pthread_mutex_t mutex;
void* routine(void* arg) {

    for(int i=0; i<NUM_ITERATIONS; i++){
        pthread_mutex_lock(&mutex);
            // wait until the lock is 0
        mail++;

        pthread_mutex_unlock(&mutex);
        // read mail value
        // increment mail value 
        // write back mail value
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);
    if(pthread_create(&threads[0], NULL, routine, NULL)) {
        perror("Failed to create thread 0");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&threads[1], NULL, routine, NULL)) {
        perror("Failed to create thread 1");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&threads[2], NULL, routine, NULL)) {
        perror("Failed to create thread 0");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&threads[3], NULL, routine, NULL)) {
        perror("Failed to create thread 1");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(threads[0], NULL)) {
        perror("Failed to join thread 0");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(threads[1], NULL)) {
        perror("Failed to join thread 1");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(threads[2], NULL)) {
        perror("Failed to join thread 0");
        exit(EXIT_FAILURE);
    }
    if(pthread_join(threads[3], NULL)) {
        perror("Failed to join thread 1");
        exit(EXIT_FAILURE);
    }
    printf("Final value of mail: %d\n", mail); // Print the final value of shared_counter

    // Clean up mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}