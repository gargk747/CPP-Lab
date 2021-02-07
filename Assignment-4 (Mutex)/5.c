#include <stdio.h>
#include<pthread.h>
struct employee
{
    char name[50];
    int id;
    int salary[5];
};

void* func(void* arr){
	int* x = (int*)arr;
	int sum = 0;
	int i=0;
	int a = *(x+4);
	int b = *(x);
	
	printf("Hike % = %f\n",((a-b)*100.0)/b);
	  pthread_exit(NULL);
}

int main()
{
	struct employee s;
	printf("enter name,id number and salary in 5 years\n");
	pthread_t tid;
	scanf("%s",&s.name);
	scanf("%d",&s.id);
	int i=0;
	for(i=0;i<5;i++){
		scanf("%d",&s.salary[i]);
	}
	pthread_create(&tid,NULL,func,(void*)&s.salary);
	pthread_join(tid,NULL);
	return 0;
}
