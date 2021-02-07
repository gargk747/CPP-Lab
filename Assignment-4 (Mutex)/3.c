# include <stdio.h>
# include <pthread.h>

#define N_THREAD 5
int min=10000,max=0;
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
void *f(void *no)
{
   int *x = (int*)no;
   int i = *x;
    
   
        pthread_mutex_lock(&mutex1);
        if(i<min) min=i;
        pthread_mutex_unlock(&mutex1);
    
    pthread_exit(NULL);
}

int main()
{
    int i,n,j;
    pthread_t tid[N_THREAD];
    printf("Enter N:");
    
    scanf("%d",&n);    
    int arr[n];
    for(i=0;i<n;i++){
    	scanf("%d",&arr[i]);
    }
   	for(i=0;i<n;){
   		for(j=0;j<N_THREAD && i<n;j++,i++){
   			pthread_create(&tid[j],NULL,f,(void*)&arr[i]);
   			pthread_join(tid[j],NULL);
   		}
   	}
  
    
    printf("\nmin = %d \n",min);
    return 0;
}
