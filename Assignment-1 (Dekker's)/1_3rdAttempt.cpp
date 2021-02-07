#include <iostream>
#include <pthread.h>

volatile bool wantf0;
volatile bool wantf1;

//Livelock possible here 

//when wantf0=1 && wantf1=1, process won't preceed
//This creates a situation of Livelock;

long count;
long count0;
long count1;
const long limit = 5;

void* f0(void *arg) {
    while (true) {
        //Non-Critical
        //Preprotocol
        
        // acquire
        wantf0 = true;
	__sync_synchronize(); // mfence
        //wating wantf1 to be false
        while(wantf1!=false)
        {;}
        
        // critical section
        std::cout<<"f0 Critic\n";
        ++count0;
        ++count;
        
        //Postprotocol
        // yield
        wantf0 = false;
        
        __sync_synchronize(); // mfence
        // exit
        if (count0 == limit)
            return 0;
    }
}

void* f1(void *arg) {
    while (true) {
       //Non-Critical
        //Preprotocol
        
        // acquire
        wantf1 = true;
       __sync_synchronize(); // mfence
       //wating wantf0 to be false
        while(wantf0!=false)
        {;}
        // critical section
        std::cout<<"f1 Critic\n";
        ++count1;
        ++count;
        
        //Postprotocol
        // yield
        wantf1 = false;
        ; // mfence
        // exit
        __sync_synchronize(); // mfence
        if (count1 == limit)
            return 0;
    }
}

int main(int argc, char** argv) {
    pthread_t t0, t1;

    pthread_create(&t0, 0, f0, 0);
    pthread_create(&t1, 0, f1, 0);
    pthread_join(t0, 0);
    pthread_join(t1, 0);
    std::cout << count << std::endl;
    return 0;
}

