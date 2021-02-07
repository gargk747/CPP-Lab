#include <mpi.h>
#include <stdio.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main (int argc, char* argv[])
{
  int rank, size;
  char s[100];  
  //s is used as buffer to broadcast "HELLO WORLD msg"

  MPI_Init (&argc, &argv);     	 /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);       	 /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);       	 /* get number of processes */
  
  if(rank==0)
  {
	//Setting the broadcast variable in root(rank==0) process
	char temp[12] = {'H','E','L','L','O',' ', 'W','O','R','L','D','\0'} ;
	for(int i=0;i<12;i++)
		{s[i] = temp[i];}
  }
  
  
  MPI_Bcast(&s[0],12, MPI_CHAR, rank, MPI_COMM_WORLD);
   
  printf("From the process %d, we have ---> %s\n",rank,s);
   
  MPI_Finalize();
  return 0;
}
