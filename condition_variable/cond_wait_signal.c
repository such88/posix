#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/*! @brief
    1. We have a bucket of 20 ltr, to watering plant.
    2. We will start motor to fill the bucket, if the bucket has less than 2 ltr of water.
    3. We will wait for the motor to fill the till it has 20 ltr.
    4. We will water the plant, if the bucket has more than 2 ltr of water.
    5. We will stop the motor, if the bucket has more than 18 l
*/
#if 1
#define NOF_THREADS 2
#define BUCKET_CAPACITY 20
#define MIN_WATER_LEVEL 8

pthread_mutex_t mutex_fill_water;
pthread_cond_t cond_fill_water;
unsigned char water = 0;

void *fill_bucket(void *arg) {
    while(water < BUCKET_CAPACITY) {
        pthread_mutex_lock(&mutex_fill_water);
        water += 2; // Simulate filling 2 liters of water
        printf("Filling bucket: Current water level = %d liters\n", water);
        pthread_mutex_unlock(&mutex_fill_water);
        pthread_cond_signal(&cond_fill_water); // Signal that the bucket is being filled
        usleep(1000); // Simulate time taken to fill the bucket
    }

}

void *watering_plant(void *arg) {
    pthread_mutex_lock(&mutex_fill_water);
    while(water <= MIN_WATER_LEVEL) {
        printf("Not much water, waiting....\n");
        pthread_cond_wait(&cond_fill_water, &mutex_fill_water);
        // Equivalent to:
        // pthread_mutex_unlock(&mutex_fill_water);
        // wait for signal on cond_fill_water
        // pthread_mutex_lock(&mutex_fill_water);
    }
    water -= 2; // Simulate watering the plant with 2 liters of water
    printf("Watering plant: Current water level = %d liters\n", water);
    pthread_mutex_unlock(&mutex_fill_water);
    sleep(1); // Simulate time taken to water the plant

}

int main() {
    pthread_mutex_init(&mutex_fill_water, NULL);
    pthread_cond_init(&cond_fill_water, NULL);

    pthread_t threads[NOF_THREADS];
    pthread_create(&threads[0], NULL, &fill_bucket, NULL);
    pthread_create(&threads[1], NULL, &watering_plant, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex_fill_water);
    pthread_cond_destroy(&cond_fill_water);
}
#endif

#if 0
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, char* argv[]) {
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}

#endif