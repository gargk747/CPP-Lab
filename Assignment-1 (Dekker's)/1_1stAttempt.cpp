#include <iostream>
#include <pthread.h>

volatile int turn;
//	Startvation Possible here

long count;
long count0;
long count1;
const long limit = 10;

void* f0(void *arg) {
    while (true) {
        // acquire NON-critical
        
        //await turn = 0
       while(turn != 0) {
        ;
       }   
        // critical section
        std::cout<<"f0 Critic\n";
        ++count0;
        ++count;
        // yield
        turn = 1;
        
        // exit
        if (count0 == limit)
            return 0;
    }
}

void* f1(void *arg) {
    while (true) {
        // acquire
        //await turn = 1
       while(turn != 1)
       { ;}
        // critical section
        std::cout<<"f1 Critic\n";
        ++count1;
        ++count;
        // yield
        turn = 0;
        
        // exit
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
