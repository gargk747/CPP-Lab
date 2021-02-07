Assignment: 5

//To execute the OPENMP programs, we compile and run as given below :
//gargk747@gargk747-VirtualBox:~/Desktop/cpp$	 g++ 1.cpp -fopenmp -o 1
//gargk747@gargk747-VirtualBox:~/Desktop/cpp$	 ./1

//To execute MPI programs, we execute following: (mpic++ wrapper is used)
//gargk747@gargk747-VirtualBox:~/Desktop$   mpic++ 5.cpp -o 5
//gargk747@gargk747-VirtualBox:~/Desktop$   mpirun -np 5 ./5


1. Write an OpenMP program to print each thread’s unique identifier.

2. Write MPI program to broadcast message &quot;Hello world&quot; to all the processes.

3. Write an OpenMP program to find Sum of Natural Numbers using OpenMP Parallel FOR directive and REDUCTION clause.

4. Write MPI program to find sum of n integers on a Parallel Computing System and use MPI collective blocking communication library calls.

5. Write MPI program for prefix sum (scan operation) calculation using MPI point-to-point blocking communication library calls.

6. Implement parallel Quick sort using OpenMP, MPI, and Posix thread.