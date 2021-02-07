#include <stdio.h>
#include <pthread.h>

#define M 5
#define N 10
int matrix[N][M];
int total=0;               
pthread_mutex_t mutex;    

void *SumValues(void *i)
{
  int *k = (int*)i; 
  int n = *k;        
  int my_total = 0;       
  int j;
   for (j = 0; j < M; j++)      
     my_total += matrix[n][j];
     printf("sum of elements of row %d : %d\n", n, my_total);
     pthread_mutex_lock(&mutex);       
     total += my_total;               
     pthread_mutex_unlock(&mutex);     
     pthread_exit(NULL);               
   }
int main(int argc, char *argv[])   {
   int i, j;
   pthread_t threads[N];           
   for (i = 0; i < N; i++)         
     for (j = 0; j < M; j++)
       matrix[i][j] = (i * M + j)%10;
   pthread_mutex_init(&mutex, NULL);
   int values[N];
   for(i=0;i<N;i++) values[i]=i;
   
   for(i = 0; i < N; i++)
     if (pthread_create(&threads[i], NULL, SumValues, &values[i]))
     {
       printf("Can not create a thread\n");
      
     }
   for (i = 0; i < N; i++){     
     pthread_join(threads[i], NULL);
    }
    printf("Sum of matrix: %d\n", total);
   pthread_mutex_destroy(&mutex);       
   return 0;
 }
