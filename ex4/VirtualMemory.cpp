#include <cmath>
#include <iostream>
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

#define ROOT 0

using namespace std;

void breakVirtualAddre(uint64_t *p, uint64_t addr) {
    while (addr) {
        *p = (addr & (uint64_t) (pow(2, OFFSET_WIDTH) - 1));
        addr = addr >> OFFSET_WIDTH;
        p += 1;
    }
}

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
    uint64_t offset = p_ref[0];
    word_t addr_i;
    uint64_t curr = ROOT;
    for (int i = 1; i < TABLES_DEPTH + 1; ++i) {
        PMread(curr + p_ref[i], &addr_i);
        if (!addr_i) {
            PMwrite(curr + p_ref[i], i);
        } else {
            curr = (uint64_t) (addr_i * PAGE_SIZE);
        }
    }

    return 1;
}

void print_all_tables() {
    word_t word;
    for (int f = 0; f < NUM_FRAMES; ++f) {
        for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
            PMread(f * PAGE_SIZE + i, &word);
            cout << "frame number: " << f << ", row number: " << i << " has: " << word << endl;
        }
    }
}

