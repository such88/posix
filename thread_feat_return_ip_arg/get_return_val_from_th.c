#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define NO_OF_THREAD 8
#define NO_OF_ITERATIONS 1000000

volatile int mail =0;
pthread_mutex_t mutex;

void *roll_dice(void *arg){
    int value = (rand() % 6) + 1; // Generate a random number between 1 and 6
    printf("Thread %ld rolled a dice and got: %d\n", pthread_self(), value);
    int *result = (int *)malloc(sizeof(int));
    if(result == NULL){ 
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    *result =  value;
    printf("Thread result: %p\n", result);
    return (void *) result;
}

int main(int argc, char **argv){
    pthread_t th[NO_OF_THREAD];
    int *th_return;
    for(int i =0; i<NO_OF_THREAD; i++){
        if(pthread_create(th + i, NULL, roll_dice, NULL) != 0){
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for(int i =0; i<NO_OF_THREAD; i++){
        if(pthread_join(th[i], (void *)&th_return)!= 0){
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
        printf("Main res: %p\n", th_return);
        printf("Thread %ld returned value: %d\n", th[i], *th_return);
        free(th_return); // Free the allocated memory for the result
    }
}