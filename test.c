#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
//#include <buffer.h>

#define BUFFER_SIZE 10

//initial 2 buffers
char buf[BUFFER_SIZE];
char buf1[BUFFER_SIZE];
//output string
char str [100000000];
sem_t empty, full, mutex, empty1, full1, mutex1;
int strIndex = 0;
int input = 0;
int output = 0;
int input1 = 0;
int output1 = 0;

//read input
void *thread1(void *arg)
{
    int ch;
    ch = getchar();
    while (ch != EOF)
    {
        //decrement semaphore
        sem_wait(&empty);
        sem_wait(&mutex);
        //critical section
        buf[input] = ch;
        input++;
        //increment semaphore
        sem_post(&mutex);
        sem_post(&full);
    }
}
//parse '\n'
void *thread2(void *arg)
{
    int ch1;
    while (1)
    {
        //decrement semaphore
        sem_wait(&full);
        sem_wait(&mutex);
        //critical section
        ch1 = buf[output];
        output++;
        //increment semaphore
        sem_post(&mutex);
        sem_post(&empty);
    }
    //parse '\n'
    if (ch1 == '\n')
    {
        ch1 = ' ';
    }
    while (1)
    {
        //decrement semaphore
        sem_wait(&empty1);
        sem_wait(&mutex1);
        //critical section
        buf1[input1] = ch1;
        input1++;
        //increment semaphore
        sem_post(&mutex1);
        sem_post(&full1);
    }
}
//parse '**' and write output
void *thread3(void *arg)
{
    int ch2;
    while (1)
    {
        //decrement semaphore
        sem_wait(&full1);
        sem_wait(&mutex1);
        //critical section
        ch2 = buf1[output1];
        output1++;
        //increment semaphore
        sem_post(&mutex1);
        sem_post(&empty1);
    }
    if (strIndex > 0 && ch2 == '*' && str[strIndex - 1] == '*')
    {
        str[strIndex - 1] = '^';
    }
    else
    {
        str[strIndex] = ch2;
        strIndex++;
    }

    //print out when there are 80 chars
    if (strIndex == 80)
    {
        printf("%s\n", str);
    }
    else if (strIndex > 80)
    {
        int j = strIndex / 80;
        for (int z = 1; z <= 80 * j; z++)
        {
            printf("%c", str[z - 1]);
            if (z % 80 == 0)
            {
                printf("\n");
            }
        }
    }
    free(str);
}

int main(void)
{
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex1, 0, 1);
    sem_init(&empty1, 0, BUFFER_SIZE);
    sem_init(&full1, 0, 0);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);

    // wait for both threads to terminate
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    //release semaphore
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex1);
    sem_destroy(&empty1);
    sem_destroy(&full1);

    return 0;
}
