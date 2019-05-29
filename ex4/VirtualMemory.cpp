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


void get_frame_helper(const uint64_t prev, const int row, int depth, int *max_t, int *found, bool firstRun) {

//    auto curr = (uint64_t) (prev * PAGE_SIZE + row);
    word_t curr = 0;
    if (!firstRun) {
        PMread(prev * PAGE_SIZE + row, &curr);
    }
    if (depth == 0) {
        return;
    } else {
        int zeros = 0;
        word_t row_val;
        for (int i = 0; i < PAGE_SIZE; i++) {
            PMread(curr + i, &row_val);
            if (row_val == 0) {
                zeros++;
            } else {
                if (*max_t < row_val) {
                    *max_t = row_val;
                }
                get_frame_helper(curr, i, depth - 1, max_t, found, false);
            }
        }

        if (zeros == PAGE_SIZE) { //TODO check prev != null
            *found = (int) curr;
//            uint64_t address = (prev + row);
//            PMwrite(address, 0);
        }
    }
}

void evictLRU() {
    cout << "not implemened LRU" << endl;
}

int get_frame(int lastFound) {
// read gets: uint64_t virtualAddress, word_t *value
// write gets: uint64_t virtualAddress, word_t value
//    cout << " in get frame "<< endl;
    int d = TABLES_DEPTH;
    int max_t = 0;    //TODO maybe uint64_t ?
    uint64_t prev = 0;
    int row = ROOT;
    int found = -1;
    get_frame_helper(prev, row, d, &max_t, &found, true);
    cout << "found = " << found << endl;
    cout << "max t = " << max_t << endl;


    if (found > 0 && found != lastFound) {
        return found; //TODO when *PAGE_SIZE
    } else if (max_t < NUM_FRAMES) //TODO how does max_T work?
    {
//        cout << "frame from max = " << max_t + 1 << endl;

        return max_t + 1;
    } else {
        evictLRU();
    }

//    cout << endl;
//    print_all_frames();
//    cout << endl;
    return -1;
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
    uint64_t curr = ROOT * PAGE_SIZE;
    int prevFrame = 0;
    for (int i = 1; i < TABLES_DEPTH + 1; ++i) {
        PMread(curr + p_ref[i], &addr_i);
        if (!addr_i) {
//            cout << "in write , i =  " <<i<<" and curr = "<< curr <<endl;
            int frame = get_frame(prevFrame);
            prevFrame = frame ;
            cout << "prev frame = " << prevFrame << endl;
//            cout << "GOT frame: " << frame << endl;
            PMwrite(curr + p_ref[i], frame);
            curr = (uint64_t) (frame) * PAGE_SIZE;
            cout << endl;
            print_all_frames();
            cout << endl;
        } else {
            curr = (uint64_t) (addr_i * PAGE_SIZE);
        }
    }

    return 1;
}


void print_all_frames() {
    word_t word;
    for (int f = 0; f < NUM_FRAMES; ++f) {
        for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
            PMread(f * PAGE_SIZE + i, &word);
            cout << "frame number: " << f << ", row number: " << i << " has: " << word << endl;
        }
    }
}

