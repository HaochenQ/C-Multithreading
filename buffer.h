#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>


sem_t empty, full, mutex;


int input = 0;
int output = 0;
//save data in the buffer
void deposit(char *buf,char c)
{

    //decrement semaphore
    sem_wait(&mutex);
    sem_wait(&empty);
    //critical section
    buf[input] = c;
    input++;
    //increment semaphore
    sem_post(&mutex);
    sem_post(&mutex);
}
//remove data from the buffer
char remoove(char *buf)
{
    char c;
    //decrement semaphore
    sem_wait(&mutex);
    sem_wait(&empty);
    //critical section
    c = buf[output];
    output++;
    //increment semaphore
    sem_post(&mutex);
    sem_post(&mutex);

    return c;
}