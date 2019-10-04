#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#define bufferSize 10

sem_t empty, full, mutex;

char buffer[bufferSize];
int input = 0;
int output = 0;
//save data in the buffer
void deposit(char c)
{

    //decrement semaphore
    sem_wait(&mutex);
    sem_wait(&empty);
    //critical section
    buffer[input] = c;
    input++;
    //increment semaphore
    sem_post(&mutex);
    sem_post(&mutex);
}
//remove data from the buffer
char remoove()
{
    char c;
    //decrement semaphore
    sem_wait(&mutex);
    sem_wait(&empty);
    //critical section
    c = buffer[output];
    output++;
    //increment semaphore
    sem_post(&mutex);
    sem_post(&mutex);

    return c;
}