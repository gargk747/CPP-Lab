#include <stdio.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h> 
	sem_t sema;
	void* func(void* arg) 
	{ 
	    int* k = (int*)arg;
	    int i = *k;
	    sem_wait(&sema); 
	    printf("\tIn the critical section of thread %d\n\tGoing to sleep for 5s\n",i); 
	  
	    //critical section 
	    sleep(5); 
	      
	    //signal 
	    printf("\tSignalling end of critical section\n"); 
	    sem_post(&sema); 
	} 
	int main(){
		
	    sem_init(&sema, 0, 1); 
	    pthread_t t1,t2;
	    while(1) {
	    	    printf("\n\n\n\n Inside Loop\n");
	    	    int i =1;
		    pthread_create(&t1,NULL,func,(void*)(&i));
		    printf("\tGoing to sleep for 2s\n");
		    sleep(2); 
		    i = 2;
		    pthread_create(&t2,NULL,func,(void*)(&i)); 
		    pthread_join(t1,NULL); 
		    pthread_join(t2,NULL);
		    printf("Ending this iteration\n"); 
	    }
	    sem_destroy(&sema); 
	}
