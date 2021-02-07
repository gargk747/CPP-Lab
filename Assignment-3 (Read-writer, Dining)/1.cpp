#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include<bits/stdc++.h>
#include <pthread.h>
using namespace std;

//Defining Moniter
struct Monitor_datatype
 {
    int s = 1;  //Limits the thread that can run critical at a time
    sem_t notZero; //to check not Zero condition
    
    void wait() //Process wait condition
    {
        if(s==0)
            sem_wait(&notZero);
        s=s-1;
    }
    void signals()  //Process signal - other thread can run 
    {
        s=s+1;
        sem_post(&notZero);
    }
    
};
struct Monitor_datatype Monitor; 	// initialise Monitor

//Process p && q
void *p(void* arg)
{
    int l= 3;	//to limit the number of iteration
    while(l--)
    {
        Monitor.wait(); //waits for s>0, allowing it to run
        cout<<" Critical of p\n";
        Monitor.signals();
    }
}

void *q(void* arg)
{
    int r=3; //to limit the number of iteration
    while(r--)
    {
        Monitor.wait();
        cout<<" Critical of q\n";
        Monitor.signals();
    }
}
int main()
{
    //initialise semaphore of Monitor
    sem_init(&(Monitor.notZero),0,0);
    pthread_t t1,t2;

    //Creating the threads
    pthread_create(&t1,NULL,p,NULL);
    pthread_create(&t2,NULL,q,NULL);

    //Joining the threads
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
