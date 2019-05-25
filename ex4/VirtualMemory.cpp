#include <cmath>
#include <iostream>
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

using namespace std;

void breakVirtualAddre(uint64_t *p, uint64_t addr) {
    while (addr) {
        *p = (addr & (uint64_t) (pow(2, OFFSET_WIDTH) - 1));
        addr = addr >> OFFSET_WIDTH
                ;
        p += 1;
    }
}

//uint64_t findUnusedFrame (){
//
//}

void clearTable(uint64_t frameIndex) {
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {

        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

void VMinitialize() {
    clearTable(0);
}


int VMread(uint64_t virtualAddress, word_t *value) {
    uint64_t p_ref[TABLES_DEPTH + 1];
    breakVirtualAddre(p_ref, virtualAddress);

    return 1;
}


int VMwrite(uint64_t virtualAddress, word_t value) {
    uint64_t p_ref[TABLES_DEPTH + 1] = {0};
    breakVirtualAddre(p_ref, virtualAddress);

    for (auto &p : p_ref) {
        cout << p << endl;
    }
    return 1;
}

