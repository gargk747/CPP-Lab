#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]){
	int rank, numprocs, src, dest, data, sum = 0;	
	
	//We will use process Ranks as their input number and perform the presum
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	
	//We need to handle process 0 separately(corner case)
	//for process 0, we send rank (0) to itself
	if(rank == 0){
		MPI_Send(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	
//for rest of the process,we receives the data from 1 rank below 
	//and send data to 1 rank above(to 0 from process numprocs(last one))
	
	else{
		src = rank-1;
		MPI_Recv(&data, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
		//and add it to sum,thus getting presum upto current process
		sum = rank + data;
		printf("process no is %d and Sum untill now(presum) is ---> %d\n",rank,sum);

		//send the calculated sum to one rank above
		dest = (rank + 1)%numprocs;
		MPI_Send(&sum, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
	}
	//we process 0,recived is performed as below
	if(rank==0)
              {
		src = numprocs-1;
		MPI_Recv(&sum, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
		printf("process no is %d and Sum untill now(presum) is ---> 0\n",rank);
	}
	MPI_Finalize();
	return 0;
}

