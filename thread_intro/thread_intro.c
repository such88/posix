#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void *thread_function(void *arg) {
    int *num = (int *)arg;
    printf("Thread %d is running\n", *num);
    return NULL;
}

int main() {
    pthread_t th[5];
    int thread_args[5];

    for (int i = 0; i < 5; i++) {
        thread_args[i] = i + 1;
        if (pthread_create(&th[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(th[i], NULL);
    }

    printf("All threads have finished execution.\n");
    return 0;
}