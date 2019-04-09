#include "uthreads.h"
#include <iostream>
#include <set>
#include <cstring>
#include <setjmp.h>

using namespace std;
int la_id;
int lo_id;
int li_id;
bool bla = true;

void la() {
    la_id = uthread_get_tid();
    while (1) {}
}

void lo() {

    if (bla) {
        bla = !bla;
//        uthread_sleep(9000000);
        uthread_block(100);
    }
    lo_id = uthread_get_tid();
    while (1) {}
}

void li() {
    li_id = uthread_get_tid();
    while (1) {}
}



int main() {
    uthread_init(900000);
    uthread_spawn(la);
    uthread_spawn(lo);
    uthread_spawn(li);
    int a0 = uthread_get_tid();
    cout << "running now: " << a0 << endl;
    while (1){}
//    uthread_block(a0);
    return 0;

}