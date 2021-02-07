#include <iostream>
#include <pthread.h>

volatile bool wantf0;
volatile bool wantf1;

//It handle all 3 condition of concurrency in most cases, by using wantf0 and wantf1 bools
//starvation possible in one case, when the statements of both thread are executed equally 

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

        //when wantf1 is also true, allow f1 to proceed by making wantf0 as false
        while(wantf1==true)
        { 
            wantf0 = false;
            __sync_synchronize(); // mfence
            wantf1 = true;
        }
        
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

       //when wantf0 is also true, allow f1 to proceed by making wantf1 as false
       
        while(wantf0==true)
        {
            wantf1 = false ;
            __sync_synchronize(); // mfence
            wantf1 = true;
        }
        // critical section
        
        std::cout<<"f1 Critic\n";
        ++count1;
        ++count;
        
        //Postprotocol
        // yield
        wantf1 = false;
    
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
