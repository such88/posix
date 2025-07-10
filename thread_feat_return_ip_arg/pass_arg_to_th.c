#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define NO_OF_TH 10
int primes[20]= {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                        31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
// This program demonstrates how to pass an argument to a thread in C using pthreads.

void *routine(void *arg){
    sleep(1);
    int index = *(unsigned int *)arg;
    printf(" %d", primes[index]);
    free(arg); // Free the allocated memory for the argument
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t th[NO_OF_TH];
    unsigned int arg = 0x12345678;
    int i;
    for(i = 0; i < NO_OF_TH; i++){
        int *a = malloc(sizeof(int));
        if(a == NULL){
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *a = i; // Assign the index to the allocated memory
        if(pthread_create(&th[i], NULL, routine, a) != 0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for(i = 0; i < NO_OF_TH; i++){    
        if(pthread_join(th[i], NULL) != 0){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    //pthread_join(th, NULL);
    return 0;
}