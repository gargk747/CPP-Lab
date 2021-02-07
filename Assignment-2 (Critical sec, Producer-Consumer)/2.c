#include <stdio.h>
	#include<pthread.h>
	#include <semaphore.h> 
	#include <unistd.h> 
	sem_t sema;
	void* func(void* arg) 
	{ 
	    int* k = (int*)arg;
	    int i = *k;
	    sem_wait(&sema); 
	    printf("\tIn the critical section of thread %d\n\t\tGoing to sleep for 2s\n",i); 
	  
	    //critical section 
	    sleep(2); 
	      
	    //signal 
	    printf("\tSignalling end of critical section\n"); 
	    sem_post(&sema); 
	} 
	int main(){
		
	    sem_init(&sema, 0, 1); 
	    pthread_t t[5];
	    while(1) {
	    	    printf("\n\n\n\nInside Loop\n");
	    	    int i =1;
	    	    for(i=1;i<=5;i++){
		    	    pthread_create(&t[i],NULL,func,(void*)(&i));
			    printf("\tGoing to sleep for 1s\n");
			    sleep(1); 
			    pthread_join(t[i],NULL); 
	    	    }
		    printf("Ending this iteration\n"); 
	    }
	    sem_destroy(&sema); 
	}
