#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
# include<bits/stdc++.h>
using namespace std; 
// Define the data we need to create the monitor
struct monitor_DataType {
          sem_t OKtoRead;
          sem_t OKtoWrite;
          int readerCount;
          int isBusyWriting;
          // The read-queue
          int readRequested;
};
struct monitor_DataType monitor_data; 

// Function that will block until write can start
void monitor_StartWrite() {
          if(monitor_data.isBusyWriting || monitor_data.readerCount != 0){
                sem_wait(&(monitor_data.OKtoWrite));
          }
          monitor_data.isBusyWriting++;    // Using 1 as true
}

// Function to signal reading is complete
void monitor_EndWrite() {
          monitor_data.isBusyWriting--;
          if(monitor_data.readRequested){
            sem_post(&(monitor_data.OKtoRead));
          } else {
            sem_post(&(monitor_data.OKtoWrite));
          }
}

// Function that will block until read can start
void monitor_StartRead() {
          if(monitor_data.isBusyWriting){
                monitor_data.readRequested++;
                sem_wait(&(monitor_data.OKtoRead));
                monitor_data.readRequested--;
          }
          monitor_data.readerCount++;
          sem_post(&(monitor_data.OKtoRead));
}

// Function to signal reading is complete
void monitor_EndRead() {
          monitor_data.readerCount--;
          if(monitor_data.readerCount == 0){
            sem_post(&(monitor_data.OKtoWrite));
          }
}

// intialize the monitor
// return's 0 on success, just like sem_init()
int monitor_Initialized(){  
        int returnValue = 1;
        // Initialize the structure
        monitor_data.readerCount = 0;
        monitor_data.isBusyWriting = 0;
        monitor_data.readRequested = 0;
        // initialize the semaphores
        if(sem_init(&(monitor_data.OKtoWrite), 0, 1) == 0 && 
           sem_init(&(monitor_data.OKtoRead), 0, 1) == 0){
                returnValue = 0;
        } else {
             cout&lt;&lt;"Unable to initialize semaphores\n";
        }
        return returnValue;
}
// Destroys the semphores.
void monitor_Destroy(){
      sem_destroy(&(monitor_data.OKtoWrite));
      sem_destroy(&(monitor_data.OKtoRead));
}
int main() {
       if(monitor_Initialized() == 0){
         cout << "Initialized\n";
         monitor_StartWrite();
         cout << "Writing stuffs...\n";
         monitor_EndWrite();
         monitor_StartRead();
         cout << "Reading stuffs...\n";
         monitor_EndRead();
         monitor_Destroy();
       }
      return 0;
}
