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
    print_ready();
    while (1) {}
}

void lo() {
    lo_id = uthread_get_tid();
    print_ready();
    while (1) {}
}

void li() {
    li_id = uthread_get_tid();
    print_ready();
    while (1) {}
}



int main() {
    uthread_init(900000);
    uthread_spawn(la);
    uthread_spawn(lo);
    uthread_spawn(li);
//    while (1){}
    uthread_block(0);
//    cout << !2 << endl;
//    cout << !-2 << endl;
//    cout << !0 << endl;

    return 0;

}