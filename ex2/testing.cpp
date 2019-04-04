#include "uthreads.h"
#include <iostream>
#include <set>
#include <cstring>
#include <setjmp.h>

using namespace std;
int la_id;
int lo_id;
int li_id;

void la() {
    la_id = uthread_get_tid();
    for (int i = 0; i < 10; ++i) {
        cout << "la" << endl;
    }
    uthread_block(la_id);
}

void lo() {
    lo_id = uthread_get_tid();
    for (int i = 0; i < 10; ++i) {
        cout << "lo" << endl;
    }
    uthread_resume(la_id);
    uthread_block(lo_id);
}

void li() {
    li_id = uthread_get_tid();
    uthread_sleep(1000000000);
    for (int i = 0; i < 10; ++i) {
        cout << "li" << endl;
    }
}



int main() {
    uthread_init(90);
    uthread_spawn(la);
    uthread_spawn(lo);
    uthread_spawn(li);
    int a0 = uthread_get_tid();
    cout << "running now: " << a0 << endl;
//    uthread_terminate(a0);
    uthread_block(a0);
    return 0;

}