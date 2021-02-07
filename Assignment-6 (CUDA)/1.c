%%cu
#include<stdio.h>
#define MAX 10

//kernel function for addition of 2 Vectors
__global__ void Addition(int *gpu1,int *gpu2,int *res,int N)
{
  int index;
  index = threadIdx.x + blockIdx.x*blockDim.x;
  if(index<N)
  {
    res[index] = gpu1[index] + gpu2[index];
  }
}
//Function to display Array elements
void Display(int Arr[MAX],int n)
{
  for(int i=0;i<n;i++)
  { 
    printf("\n\t Element %d : %d",i+1,Arr[i]);
  }
  printf("\n\t");
}

//Main function
int main()
{
  int Result[MAX],i,N;						//Memory Allocation on the device
  int *dev1,*dev2,*dev_Result;       //to declare on CPU & allocate memory on the Device/GPU

  printf("\n\t No. of elements : ");
  N=5;
  printf("%d",N);
  //scanf("%d",&N);

  //First_Array elements
  printf("\n\t First Array elements : ");
  int Array1[]={20,34,23,12,50};
  
  //Display array1 elements
  printf("\n\t Elements of Array1 : "); 
  Display(Array1,N);

 //Second_Array elements
  printf("\n\t Second Array elements : ");
  int Array2[]={51,34,56,23,12};
  
  //Display array2 elements
  printf("\n\t Elements of Array2 : "); 
  Display(Array2,N);

  //Memory Allocation for arrays on the CUDA device
  cudaMalloc((void**)&dev1, sizeof(int)*N);
  cudaMalloc((void**)&dev2, sizeof(int)*N);  
  cudaMalloc((void**)&dev_Result, sizeof(int)*N);  
  
  //Data Transfer from CPU to the device for computation
  cudaMemcpy(dev1,Array1, sizeof(int)*N, cudaMemcpyHostToDevice);
  cudaMemcpy(dev2,Array2, sizeof(int)*N, cudaMemcpyHostToDevice);
  
  //function call with 1 i.e. number of parallel blocks 
  // N = Number of threads in each block
  Addition<<<1,N>>>(dev1, dev2, dev_Result, N);

  // Resultant array copy from GPU to CPU.
  printf("\n\t Vector addition : ");
  cudaMemcpy(Result, dev_Result, sizeof(int)*N, cudaMemcpyDeviceToHost);
  Display(Result, N); 
  return 0;
}
