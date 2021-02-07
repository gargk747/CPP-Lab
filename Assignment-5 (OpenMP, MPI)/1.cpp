#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc,char **argv)
{
	int             threadid,Noofthreads;
	printf("Master thread  prints this before forking the team of thread \n");

        // Set the number of threads
	omp_set_num_threads(4);

	/* OpenMP Parallel Construct : Fork a team of threads */ 
	#pragma omp parallel private(threadid)
	{
                /* Obtain the thread id */
		threadid = omp_get_thread_num();

		/* Each Thread Prints Its Threadid */
		printf("\n My thread id is : %d\n", threadid);
	
	} /* All thread join Master thread */

	printf("\nMaster thread  prints this after the end parallel region\n");
	
	return 0;
}
