#include "uthreads.h"
#include <iostream>
#include "Thread.h"
#include <set>

int main() {
    std::cout << "Hello, World!" << BLOCKED << READY << std::endl;

    set<int> bla;

    bla.insert(3);
    bla.insert(31);
    bla.insert(233);
    bla.insert(0);
    bla.insert(3);

    int temp = *bla.begin();
    std::cout << temp << std::endl;
    bla.erase(temp);

    for (auto &i : bla) {
        std::cout << i << std::endl;
    }


    return 0;
}