#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#define BUFF_SIZE (16)
typedef struct{
    unsigned int buff[BUFF_SIZE];
    int head;
    int tail;
}buffer;


sem_t sem_fill, sem_empty;
pthread_mutex_t mut;

void *producer(void *arg){
    buffer *l_b = (buffer *)arg;
    static int i=0;
    int val=0;
    
    while(1){
        sem_wait(&sem_empty);
        pthread_mutex_lock(&mut);
        val = i*10;
        printf("produced %d\n", val);
        l_b->buff[l_b->tail] = i*10;
        l_b->tail = (l_b->tail+1) % BUFF_SIZE;
        i++;
        pthread_mutex_unlock(&mut);
        sem_post(&sem_fill);
        sleep(1);    
    }
    
    return NULL;
}

void *consumer(void *arg){
    buffer *l_b = (buffer *)arg;
    int val;
    
    while(1){
        sem_wait(&sem_fill);
        pthread_mutex_lock(&mut);
        val = l_b->buff[l_b->head];
        printf("consumed %d\n", val);
        l_b->head = (l_b->head+1) % BUFF_SIZE;
        pthread_mutex_unlock(&mut);
        sem_post(&sem_empty);
        sleep(2);    
    }
    
    return NULL;
}
void buff_init(buffer *b){
    memset(b->buff, 0, BUFF_SIZE);
    b->head = 0;
    b->tail = 0;
}
int main()
{
    pthread_t th_producer, th_consumer;
    sem_init(&sem_fill, 0, 0);
    sem_init(&sem_empty, 0, 10);
    pthread_mutex_init(&mut, 0);

    buffer b;
    buff_init(&b);    
    if(pthread_create(&th_producer, NULL, &producer, &b)!=NULL){
        printf("producer th craete failed\n");
    }
    if(pthread_create(&th_consumer, NULL, &consumer, &b)!=NULL){
        printf("consumer th craete failed\n");
    }
    
    
    if(pthread_join(th_producer, NULL)!=NULL){
        printf("join failed at prod th");
    }
    if(pthread_join(th_consumer, NULL)!=NULL){
        printf("join failed at consumer th");
    }
    return 0;
}
