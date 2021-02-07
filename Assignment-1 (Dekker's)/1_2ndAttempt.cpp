#include <iostream>
#include <pthread.h>

volatile bool wantf0;
volatile bool wantf1;
// volatile int turn;

//AS mutual exclusion is not satisfied,process may enter into
//infinite loop when wantp=false and wantq=false;

//comparing {count0=limit} instead of {count=limit} allows to exit the process
//else it t may enter into infinte loop,

long count;
long count0;
long count1;
const long limit = 50;

void* f0(void *arg) {
    while (true) {
        // NON-critical
        //preprotocol
       while(wantf1 != false) {
        ;
       }
       wantf0 = true ;
        // critical section
        std::cout<<"f1 Critic\n";
        ++count0;
        ++count;
        
        // Postprotocol/yield
        wantf0 = false ;
        
        std::cout<<"cric f1 out\n";
        // exit
        if (count0 == limit)
            return 0;
    }
}

void* f1(void *arg) {
    while (true) {
        //NON-critical
       while(wantf0 != false)
       { ;}
       wantf1 = true ;
        // critical section
        std::cout<<"f2 Critic\n";
        ++count1;
        ++count;
        // yield;
        wantf1 = false;
        
        // exit
        std::cout<<"Cric f2 out\n";
        if (count1 == limit)
            return 0;
    }
}
int main(int argc, char** argv) {
    pthread_t t0, t1;
   //Creating and joining thread
    pthread_create(&t0, 0, f0, 0);
    pthread_create(&t1, 0, f1, 0);
    pthread_join(t0, 0);
    pthread_join(t1, 0);
    std::cout << count << std::endl;
     std::cout << count1<<”\n” << count0 << std::endl;
    return 0;
}
