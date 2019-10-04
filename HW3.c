#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<assert.h>
#include<buffer.h>

//read input
void *thread1(void *arg){
    int ch;
    ch = getchar ();

}
//parse '\n'
void *thread2(void *arg){


}
//parse '**' and write output
void *thread3(void *arg){


}

int main(){
        char *str = NULL;
    //char array
    str=(char*)malloc(sizeof(char)*100000000);
    pthread_t t1,t2,t3;
    sem_init(&mutex,NULL,thread1, NULL);
    sem_init();
    sem_init();


    //release semaphore
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


