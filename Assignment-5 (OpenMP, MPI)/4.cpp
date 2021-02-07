#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
    //Initialzing the necessary variables
    int iproc;
    int MyRank, Numprocs, Root = 0;
    int value, sum = 0;
    int	Source, Source_tag;
    int Destination, Destination_tag;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);

    if(MyRank == Root){
       
       //Iterating Through each of process and receiving the value sent
       for(iproc = 1 ; iproc < Numprocs ; iproc++){
           Source     = iproc;	
	   Source_tag = 0;
	   
	   //Receving the value sent by from other process
	   MPI_Recv(&value, 1, MPI_INT, Source, Source_tag, 
		     MPI_COMM_WORLD, &status);
	   printf("Receieved value from %d is %d\n",Source,value);
		
	   //Adding it to the Sum variable
	   sum = sum + value;
       }
       printf("The process %d (Root) Recieves the Numbers\nCorresponding SUM = %d\n", MyRank, sum);
    }
    else{
	//Destination is Root(0 here) for all the process other than 0;
	Destination     = 0;
	Destination_tag = 0;
	
	//Each process Other than Root(= 0 here) sends it's Rank as Number to be added
	MPI_Send(&MyRank, 1, MPI_INT, Destination, Destination_tag, 
		  MPI_COMM_WORLD);
    }

    MPI_Finalize();

}
