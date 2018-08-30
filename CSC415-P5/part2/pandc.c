#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>


int buffer_cnt_max = 0;
int *bounded_buffer;
int in = 0;
int out = 0;
int *buffer;
int bufferIndex;
int numOfElements;
int itemsProduced;
int itemsConsumed;
int Ptime;
int Ctime;
int global_counter;
int *producerArray;
int *consumerArray;
int producerIndex;
int consumerIndex;
pthread_mutex_t lock;
sem_t full;
sem_t empty;

/*
* Function to remove item.
* Item removed is returned
*/
int dequeue_item()
{
    int return_item;
    return_item = bounded_buffer[out];
    out = (out+1) % buffer_cnt_max;
    return return_item;

}

/*
* Function to add item.
* Item added is returned.
* It is up to you to determine
* how to use the ruturn value.
* If you decide to not use it, then ignore
* the return value, do not change the
* return type to void.
*/

int enqueue_item(int item)
{
    bounded_buffer[in] = item;
    in = (in+1) % buffer_cnt_max;
    return item;
}



void producer(int *id);
void consumer(int *id);
void currentTime();
int compareProducerConsumer( const void* a, const void* b);
int match(int producerLength, int consumerLength);
void printMatchedProducerConsumer(int producerLength, int consumerLength);



int main(int argc, char* argv[]) {

    int prod_thread_cnt;
    int cons_thread_cnt;
    int a = 1; 
    if(argc != 7)
    {
        printf("You did not enter 6 arguments.\n");


    }
    else
    {
        int numProducer;
        int numConsumer;

        bufferIndex = 0;
        numOfElements = atoi(argv[1]);
        numProducer = atoi(argv[2]);
        numConsumer = atoi(argv[3]);
        itemsProduced = atoi(argv[4]);
        itemsConsumed = (numProducer * itemsProduced / numConsumer);
        Ptime = atoi(argv[5]);
        Ctime = atoi(argv[6]);
        buffer = (int*)malloc(sizeof(int) * numOfElements);
        producerArray = (int*)malloc(sizeof(int) * (numProducer * itemsProduced));
        consumerArray = (int*)malloc(sizeof(int) * (numConsumer * itemsConsumed));
        int overConsume = itemsConsumed+2; 

        //semaphores and mutex Initialization 
        sem_init(&full, 0, 0);
        sem_init(&empty, 0, numOfElements);
        if(pthread_mutex_init(&lock, NULL) != 0) 
        {
            printf("mutex init failed\n");
            return 1;
        }

        //threads Initialization 
        pthread_t *tid_1 = (pthread_t*)malloc(sizeof(pthread_t) * numProducer);
        pthread_t *tid_2 = (pthread_t*)malloc(sizeof(pthread_t) * numConsumer);
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        printf("\n");
       // current time
        currentTime();
        time_t begin = time(NULL);

        printf("\n");
        printf("\n");
        printf("\n");
        printf("                        Number of Buffers :  %s\n" , argv[1]);
        printf("                      Number of Producers :  %s\n" , argv[2]);
        printf("                      Number of Consumers :  %s\n" , argv[3]);
        printf("Number of items produced by each producer :  %s\n" , argv[4]);
        printf("Number of items consumed by each consumer :  %d\n" , itemsConsumed);
        printf("                         Over consume on? :  %d\n" , a );
        printf("                      Over consume amount :  %d\n", overConsume);
        printf("      Time each Producer Sleeps (seconds) :  %s\n" , argv[5]);
        printf("      Time each Consumer Sleeps (seconds) :  %s\n" , argv[6]);
        printf("\n");


        //spawn off threads
        int i, j;
        int id_1[numProducer], id_2[numConsumer];

        for(i = 0; i < numProducer; i++) 
        {
            id_1[i] = i;
            pthread_create(&tid_1[i], &attr, (void*)producer, &id_1[i]);
        }

        for(j = 0; j < numConsumer; j++) 
        {
            id_2[j] = j;
            pthread_create(&tid_2[j], &attr, (void*)consumer, &id_2[j]);
        }

        for(i = 0; i < numProducer; i++) 
        {
            pthread_join(tid_1[i], NULL);
        }
        
        for(j = 0; j < numConsumer; j++) 
        {
            pthread_join(tid_2[j], NULL);
        }

        //print currenttime
        currentTime();
        printMatchedProducerConsumer(numProducer * itemsProduced, numConsumer * itemsConsumed);
        time_t end = time(NULL);

        // print total runtime
        printf("Total Runtime: %ld secs\n" , end - begin);

        // destroy semaphores and mutex
        sem_destroy(&full);
        sem_destroy(&empty);
        pthread_mutex_destroy(&lock);
        free(buffer);
        free(tid_1);
        free(tid_2);
    }

    return 0;

}


void producer(int *id)
{
    int counter = 0;
    int product;

    //produce the items
    while (counter < itemsProduced) 
    {

        //lock
        sem_wait(&empty);
        pthread_mutex_lock(&lock);


        //produce and print item
        product = global_counter++;
        printf("%d was produced by producer->    %d\n", product , *id);
        producerArray[producerIndex++] = product;

        // enqueue item in buffer
        //int t = counter;
        //counter++;
        //enqueue_item(t);
        buffer[bufferIndex++] = product;
        counter++;


        //sleep
        sleep(Ptime);

        //unlock
        pthread_mutex_unlock(&lock);
        sem_post(&full);

    }

    pthread_exit(0);
}

void consumer(int *id)
{
    int counter = 0;
    int consume;

    //consume items
    while(counter < itemsConsumed)
    {
        //lock
        sem_wait(&full);
        pthread_mutex_lock(&lock);

        //consume and print item
        consume = buffer[--bufferIndex];
        printf("%d was consumed by consumer->   %d\n", consume, *id);
        consumerArray[consumerIndex++] = consume;

        //dequeue item in buffer
        //int t = counter;
        //counter++;
        //dequeue_item(t);
        buffer[bufferIndex] = consume;
        counter++;



        //sleep
        sleep(Ctime);

        //unlock
        pthread_mutex_unlock(&lock);
        sem_post(&empty);

    }

    pthread_exit(0);

}

void currentTime() 
{
    time_t ltime;
    ltime = time(NULL);
    printf("Current time : %s\n", asctime(localtime(&ltime)));
}

int compareProducerConsumer( const void* a, const void* b) 
{
    return ( *(int*)a - *(int*)b );
}

int match(int producerLength, int consumerLength) 
{
    if(producerLength != consumerLength) 
    {
        return 0;
    }
    for(int i = 0; i < producerLength; i++) 
    {
        if(producerArray[i] != consumerArray[i]) 
        {
            return 0;
        }
    }
    return 1;
}

void printMatchedProducerConsumer(int producerLength, int consumerLength) 
{
    //sort producerArray and consumerArray
    qsort(producerArray, producerLength, sizeof(int), compareProducerConsumer);
    qsort(consumerArray, consumerLength, sizeof(int), compareProducerConsumer);


    //print producerArray and consumerArray
    printf("Producer Array: ");
    for(int i = 0 ; i < producerLength; i++)
    {
        printf("%d ", producerArray[i]);
    }
    printf("\nConsumer Array: ");
    for(int i = 0 ; i < consumerLength; i++)
    {
        printf("%d ", consumerArray[i]);
    }
        printf("\n");


    //check if producerArray and consumerArray match
    if(match(producerLength, consumerLength)) 
    {
        printf("Consumer and Producer Arrays Match!\n");
    }
    else 
    {
        printf("Consumer and Producer Arrays Don't Match...\n");
    }
    printf("\n");
}
