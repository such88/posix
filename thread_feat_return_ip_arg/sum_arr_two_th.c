#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define NO_OF_TH 2
int primes[10]= {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
// This program demonstrates how to pass an argument to a thread in C using pthreads.

void *routine(void *arg){
    int index = *(unsigned int *)arg;
    printf(" %d", index);
    free(arg); // Free the allocated memory for the argument
    int *localsum = (int *) malloc(sizeof(int));
    if(localsum == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int sum = 0;
    for(int i = 0; i < 5; i++){
        sum += primes[i + index];
    }
    *localsum = sum;
    printf("\nLocal sum : %d\n", *localsum);
    return localsum;
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
        *a = 5* i; // Assign the index to the allocated memory
        if(pthread_create(&th[i], NULL, routine, a) != 0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    int total_sum = 0;

    for(i = 0; i < NO_OF_TH; i++){
        int *r;
        if(pthread_join(th[i], (void **)&r) != 0){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
        total_sum += *r;
        free(r); // Free the memory allocated in the thread
    }

    printf("\nTotal sum: %d\n", total_sum);
    return 0;
}