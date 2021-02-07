#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

/* Main Program */
main (int argc , char **argv)
{
	float          *array_A, sum, *checkarray, serialsum;
	int             arraysize, i, k, Noofthreads=4;

        printf("\n\n\nObjective : Find the Sum of elements of one-dimensional real array  ");
        printf("\nusing OpenMP Parallel for directive and Reduction Clause  ");
        printf("\n..........................................................................\n");


	printf("\nWe will Find the Sum of First N natural NUmbers\nEnter N :\n");
 	scanf("%d", &arraysize);
	arraysize++;
	if (arraysize <= 0) {
		printf("\nPositive Number Required\n");
		exit(1);
	}

        printf("\nThreads     		 : %d ",Noofthreads);
        printf("\nArray Size (Value of N)  : %d ",arraysize-1);

	/* Dynamic Memory Allocation */
	array_A = (float *) malloc(sizeof(float) * arraysize);
	checkarray = (float *) malloc(sizeof(float) * arraysize);

	/* Array Elements Initialization */
	for (i = 0; i < arraysize; i++) {
		array_A[i] = i + 1;
		checkarray[i] = array_A[i];
	}

	sum = 0.0;

        /* Set the number of threads */
	omp_set_num_threads(Noofthreads);
        
	#pragma omp parallel for reduction(+ : sum)
	for (i = 0; i < arraysize; i++)
          {
		sum = sum + array_A[i];
          }
	/* Serial Calculation ==> TO ensure calculated value is correct*/
	serialsum = 0.0;
	for (i = 0; i < arraysize; i++)
		serialsum = serialsum +checkarray[i];


	/* Output Checking */
	if (serialsum != sum) {
		printf("\nThe parallel calculation of array sum is different from serial calculation \n");
		exit(-1);
	} else
		printf("\nThe parallel calculation of array sum is same with serial calculation \n");

	/* Freeing Memory Which Was Allocated */
	free(checkarray);
	free(array_A);

	printf("\nThe SumOfElements Of The Array Using OpenMP Directives Is %f\n", sum);
	printf("The SumOfElements Of The Array By Serial Calculation Is  %f\n\n", serialsum);
}
