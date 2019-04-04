#include "uthreads.h"
#include <iostream>
#include "Thread.h"
#include <set>
#include <cstring>

void la() {
    cout << "la";
}
void lo() {
    cout << "lo";
}


int main() {
    uthread_init(90);
    uthread_spawn(la);
    uthread_spawn(lo);
    uthread_terminate(1);



    return 0;

}