#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> 
 
#define SIZE_OF_DATASET 9 void* quickSort( void* data); 
 int partition( int* a, int, int); 
 struct info { 
 int start_index; 
 int* data_set; 
 int end_index; 
 }; 
 
int main(int argc, char **argv)
{ 
 
int a[] = { 27, 12, 1, -2,-8,2,4,11,0}; 
pthread_t thread_id; 
struct info *info = (struct info*)malloc(sizeof(struct info));
info->data_set = a;  
info->data_set=a; info->start_index = 0; 
info->end_index = SIZE_OF_DATASET-1; 
int i; 
printf("\n\nunsorted array is: \n");

for(i = 0; i < SIZE_OF_DATASET; ++i) 
printf(" %d ", info->data_set[i]); printf("\n"); 

if (pthread_create(&thread_id, NULL, quickSort, info)) 
    { 
        fprintf(stderr, "No threads for you.\n"); 
        return 1;  
    } 
 
pthread_join(thread_id, NULL); 
printf("\n\nSorted array is:  \n"); 
 
for(i = 0; i < SIZE_OF_DATASET; ++i) 
 printf(" %d ", info->data_set[i]); 
 
printf("\n"); 
 
free(info); 
pthread_exit(NULL); 
 
} 
 
void* quickSort( void *data) 
 
{ 
 
struct info *info = (struct info *)data; 
int j,l,r; 
 
l = info->start_index; 
r = info->end_index; 
pthread_t thread_id1; 
pthread_t thread_id2; 
if( l < r ) 
 
{ 
 
j = partition( info->data_set, l, r); 
info->start_index=l; 
 
info->end_index=j-1; 
 
struct info * left_info = new struct info; 
struct info * right_info = new struct info; 
 
left_info->data_set = right_info->data_set = info->data_set; 
left_info->start_index = l; 
 
left_info->end_index = j-1; 
right_info->start_index = j+1; 
right_info->end_index = r; 
 
if(info->end_index<0)info->end_index=0; 
 
if (pthread_create(&thread_id1, NULL, quickSort, left_info)) { 
 
fprintf(stderr, "No threads for you.\n"); 
return NULL; 
 
} 
 
if (pthread_create(&thread_id2, NULL, quickSort, right_info)) { 
    fprintf(stderr, "No threads for you.\n"); 
    return NULL; 
} 
 
pthread_join(thread_id1, NULL); pthread_join(thread_id2, NULL); 
delete left_info; 
 
delete right_info; 
 
} 
 
return NULL; 
 
} 
 
int partition( int* a, int l, int r) { 
    int pivot, i, j, t; 
 
    pivot = a[l]; 
 
    i = l; 
    j = r+1; 
    while( 1) 
 
{ 
 
do ++i; while( a[i] <= pivot && i <= r ); 
 
do --j; while( a[j] > pivot ); 
if( i >= j ) break; 
t = a[i]; 
a[i] = a[j]; 
a[j] = t;  
} 
 
t = a[l]; 
a[l] = a[j]; 
a[j] = t; 
return j;  
}
