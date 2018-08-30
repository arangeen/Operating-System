#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
/**
 * THESE DEFINE VALUES CANNOT BE CHANGED.
 * DOING SO WILL CAUSE POINTS TO BE DEDUCTED
 * FROM YOUR GRADE
 */
 /** BEGIN VALUES THAT CANNOT BE CHANGED */
#define MAX_THREADS 10
#define MAX_ITERATIONS 25
/** END VALUES THAT CANNOT BE CHANGED */


/**
 * use this struct as a parameter for the function
 * nanosleep. 
 * For exmaple : nanosleep(&ts, NULL);
 */
struct timespec ts = {0, 4969547 };

void *adder(void *arg);
void *subtractor(void *arg);
int globalValue = 0; //single shared integer variable

pthread_mutex_t mut;   

int
main(int argc, char** argv)
{
    pthread_t aThread;

    if(pthread_mutex_init(&mut, NULL) != 0){
        printf("Your pthread_mutex_init failed\n");
        return 1;
    }


    for (int i = 0; i < MAX_THREADS; i++){
        if(i%2 == 0){
            pthread_create(&aThread, NULL, adder, (void *)i);
        }else{
            pthread_create(&aThread, NULL, subtractor, (void *)i);
        }
    }

    pthread_join(aThread ,NULL);
    pthread_mutex_destroy(&mut);
    fprintf(stderr, "Final Value is :  %d\n", globalValue);


    return 0;
}

void *adder(void *arg){

    for(int j = 0; j < MAX_ITERATIONS; j++){

        pthread_mutex_lock(&mut);

        int myid = (int)arg;
        int tempValue;

        tempValue = globalValue;
        nanosleep(&ts, NULL);
        tempValue +=1;
        nanosleep(&ts, NULL);

        globalValue = tempValue;

        fprintf(stderr, "Current Value written to Global Variables by thread : %d  is   %d\n", myid, tempValue);  
        pthread_mutex_unlock(&mut);   
    }

    pthread_exit(0);
}


void *subtractor(void *arg){

    for(int j = 0; j < MAX_ITERATIONS; j++){

        pthread_mutex_lock(&mut);
        int myid = (int)arg;
        int tempValue;

        tempValue = globalValue;
        nanosleep(&ts, NULL);
        tempValue -=1;
        nanosleep(&ts, NULL);

        globalValue = tempValue;

        fprintf(stderr, "Current Value written to Global Variables by thread : %d  is   %d\n", myid, tempValue);
        pthread_mutex_unlock(&mut);  
    }
    pthread_exit(0);
}