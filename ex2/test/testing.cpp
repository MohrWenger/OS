#include "uthreads.h"
#include <iostream>
#include <set>
#include <cstring>
#include <setjmp.h>

using namespace std;

void la() {
    while (1) {
        cout << "la" << endl;
    }
}

void lo() {
    while (1) {
        cout << "lo" << endl;
    }
}

void li() {
    while (1) {
        cout << "li" << endl;
    }
}


int main() {
    uthread_init(100000);
    uthread_spawn(la);
    uthread_spawn(lo);
    uthread_spawn(li);
    while (1) {
        cout << "main" << endl;
    }
    return 0;

}