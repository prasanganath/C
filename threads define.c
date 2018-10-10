#include <stdio.h>
#include <pthread.h>
#define ARRAYSIZE 1000
#define THREADS 2
void *slave(void *myid);

int data[ARRAYSIZE];
int sum = 0;
pthread_mutex_t mutex;
int wsize;
void *slave(void *myid){
    int i,low,high,myresult=0;
    low = (int) myid * wsize;
    high = low + wsize;
        for (i=low;i<high;i++)
            myresult += data[i];
    pthread_mutex_lock(&mutex);
    sum += myresult;
    pthread_mutex_unlock(&mutex);
    return;



}
int main()
{
    int i;
    pthread_t tid[THREADS];
    pthread_mutex_init(&mutex,NULL);
    wsize = ARRAYSIZE/THREADS;
    for (i=0;i<ARRAYSIZE;i++)
        data[i] = i+1;
    for(i=0;i<THREADS;i++)
        if (pthread_create(&tid[i],NULL,slave,(void*)i) !=0)
            perror("Pthread_craete fails");
    for (i=0;i<THREADS;i++)
        if (pthread_join(tid[i],NULL) !=0)
            perror("Pthread_join fails");
    printf("The sum from 1 to %i is %d\n",ARRAYSIZE,sum);

}
