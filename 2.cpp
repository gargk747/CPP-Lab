#include <iostream>
#include <pthread.h>

//Requied flags/variables
volatile bool flag0;
volatile bool flag1;
volatile int turn;

//to stop the infinite loop
long count;
long count0;
long count1;
const long limit = 8;

void* f0(void *arg) {
    while (true) {
        // acquire
	//Preprotocols
        flag0 = true;
        __sync_synchronize(); // mfence
        while (flag1) {
             if (turn != 0) {
                 flag0 = false;
                 while (turn != 0) {
                 }
                 flag0 = true;
             }
        __sync_synchronize(); // mfence
        }
        // critical section
        ++count0;
        ++count;
        std::cout<<"f0 crictical\n";
        // yield/Postprotocol
        turn = 1;
        flag0 = false;
        __sync_synchronize(); // mfence
        // exit
        if (count0 == limit)
            return 0;
    }
}

void* f1(void *arg) {
    while (true) {
        // acquire
	//Preprotocol
        flag1 = true;
        __sync_synchronize(); // mfence
        while (flag0) {
             if (turn != 1) {
                 flag1 = false;
                 while (turn != 1) {
                 }
                 flag1 = true;
             }
        __sync_synchronize(); // mfence
        }
        // critical section
        ++count1;
        ++count;
        std::cout<<"f1 crictical\n";
        // yield/postprotocol
        turn = 0;
        flag1 = false;
        __sync_synchronize(); // mfence
        // exit
        if (count1 == limit)
            return 0;
    }
}

int main(int argc, char** argv) {
    pthread_t t0, t1;
    //Thread Creation and joining
    pthread_create(&t0, 0, f0, 0);
    pthread_create(&t1, 0, f1, 0);
    pthread_join(t0, 0);
    pthread_join(t1, 0);
    std::cout << count << std::endl;
    return 0;
}
