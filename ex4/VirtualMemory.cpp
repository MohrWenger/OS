#include <cmath>
#include <iostream>
#include <cmath>
#include "VirtualMemory_old.h"
#include "PhysicalMemory.h"

#define ROOT 0

using namespace std;

uint64_t PagesToFrames[NUM_PAGES][2] = {0};


uint64_t breakVirtualAddress(uint64_t *p, uint64_t addr) {
    uint64_t pageNum = addr >> OFFSET_WIDTH;
    while (addr) {
        *p = (addr & (uint64_t) (pow(2, OFFSET_WIDTH) - 1));
        addr = addr >> OFFSET_WIDTH;
        p += 1;
    }
    return pageNum;
}

void clearTable(uint64_t frameIndex) {
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

int calcDist (uint64_t potential, uint64_t pageNum)
{
    return static_cast<int>(fmin(abs((int) pageNum - (int) potential),
                                                  NUM_PAGES - (abs((int) pageNum - (int) potential))));
}

void get_frame_helper(const uint64_t *prev, int row, int depth, uint64_t *max_t, uint64_t *found,
                      uint64_t *father, bool firstRun, int* max_dst, uint64_t* pageToEvict,
                      uint64_t* fatherEvicted, uint64_t curr_page, uint64_t* frame, uint64_t
                      page_to_inresrt, uint64_t current) {
    uint64_t curr = 0;
    auto curr_to_read = (word_t) curr;
    if (!firstRun) {
//        cout << "in helper "<< *prev * PAGE_SIZE + row << endl;
        PMread(*prev * PAGE_SIZE + row, &curr_to_read);
        curr = (uint64_t) curr_to_read;
    }
//    cout << "depth = " << depth << endl;
    if (depth == 0) {               //check distance for possible eviction
        int d = calcDist(curr_page, page_to_inresrt);
        if (d > *max_dst) {
//            cout << " heree " << endl;
            *max_dst = d;
            *pageToEvict = curr_page;
            *fatherEvicted = *prev*PAGE_SIZE + row;
            *frame = curr;
//            cout << " frame = " << curr << endl;
//            cout << "potential evicting = "<< curr_page <<", and its father is "<< *fatherEvicted << endl;
            return;
        }
    }else {                        // continue recursion
            int zeros = 0;
            word_t row_val;
            for (int i = 0; i < PAGE_SIZE; i++) {
                PMread(curr * (uint64_t) PAGE_SIZE + i, &row_val);
                if (row_val == 0) {
                    zeros++;
                } else {
                    if (*max_t < row_val) {
                        *max_t = (uint64_t) row_val;
                    }
//                  cout << "page num = " << (curr_page << OFFSET_WIDTH) + i << endl;
                    get_frame_helper(&curr, i, depth - 1, max_t, found, father, false, max_dst,
                                     pageToEvict, fatherEvicted, curr_page + i * (uint64_t)pow
                                     (PAGE_SIZE, depth-1),
                                     frame, page_to_inresrt, current);
                }
            }
            if (zeros == PAGE_SIZE && (curr != current)) {       //then maybe found
//                if(((*prev * PAGE_SIZE + row) > *father)  ) {
                    *found = (int) curr;
                    *father = *prev * PAGE_SIZE + row; //TODO - make sure deepest frame is returned
//                    cout << " --> found = " << *found << endl;
//                    cout << " --> curr = "  << current << endl;
//                }
            }
        }
    }

uint64_t getFrame(uint64_t lastFound, uint64_t pageNum, uint64_t *father, const uint64_t *curr) {
    int d = TABLES_DEPTH;
    uint64_t max_t = 0;    //TODO maybe uint64_t ?
    uint64_t prev = 0;
    int row = ROOT;
    uint64_t found = 0;
    uint64_t current = *curr / PAGE_SIZE;
    int min_dst = 0;
    uint64_t page_to_evict = 0;
    uint64_t father_to_evict = 0;
    uint64_t num_evicted = 0;
    uint64_t frame = 0;
    get_frame_helper(&prev, row, d, &max_t, &found, father, true, &min_dst, &page_to_evict,
            &father_to_evict, num_evicted, &frame, pageNum, current );
    if (found > 0) {
        cerr << "in getFrame, father = " << *father << endl;
        PMwrite(*father, 0);
        clearTable(found);
        return (uint64_t) found;
        //TODO we think it is ok but habent actually got here yet
        // TODO - also clear table / father?
    } else if (max_t < NUM_FRAMES -1) {
//        cout << " in max "<< max_t + 1 << endl;
        return max_t + 1;

    } else if (frame != 0){
        cerr << "in evict, frame = " << frame << endl;
        cerr << "in evict, father = " << father_to_evict << endl;
        PMevict(frame, page_to_evict);
        PMwrite(father_to_evict, 0);
        clearTable(frame);
        return frame;
    }
    cout << "frame = " << frame << " and max_t = " << max_t << " found = "<<found <<endl;
    cout << "got here somehow " << endl;
}


void VMinitialize() {
    clearTable(0);
}

int access(uint64_t virtualAddress, word_t value, uint64_t *curr, uint64_t *father, uint64_t *p_ref) {
    uint64_t pageNum = breakVirtualAddress(p_ref, virtualAddress);
    word_t addr_i;
    uint64_t prevFrame = 0;
    uint64_t foundFather = 0;
    for (int i = TABLES_DEPTH; i > 0; --i) {
        PMread(*curr + p_ref[i], &addr_i);
        if (!addr_i) {
            uint64_t frame = getFrame(prevFrame, pageNum, &foundFather, curr);

            if (i == 1) {
//                cout << "in access, frame = " << frame << endl;
                PMrestore(frame, virtualAddress >> OFFSET_WIDTH);
            }

            if (frame != -1) {
                *father = (uint64_t) prevFrame;
                prevFrame = frame;
//                cout << "in access2, *curr + p_ref[i] = " << *curr + p_ref[i] << endl;
                PMwrite(*curr + p_ref[i], (word_t)frame);
                *curr = (uint64_t) (frame) * PAGE_SIZE;
            } else {
                return -1;
            }
        } else {
            *curr = ((uint64_t) addr_i * PAGE_SIZE);
        }
    }
    return -1;
}


int VMread(uint64_t virtualAddress, word_t *value) {

    uint64_t curr = ROOT * PAGE_SIZE;
    uint64_t p_ref[TABLES_DEPTH + 1] = {0};
    uint64_t pageNum = breakVirtualAddress(p_ref, virtualAddress);
    uint64_t father = NUM_FRAMES + 1;

    access(virtualAddress, *value, &curr, &father, p_ref);

    uint64_t offset = p_ref[0];
//    PMrestore((curr +offset) / PAGE_SIZE , pageNum);
//    cout << "in VMwread, curr = " << curr << endl;
    PMread(curr + offset, value);
    if (father < NUM_FRAMES) {
        PagesToFrames[pageNum][0] = curr / PAGE_SIZE;
        PagesToFrames[pageNum][1] = father * PAGE_SIZE + p_ref[1];
    }
    return 1;
}


int VMwrite(uint64_t virtualAddress, word_t value) {
    uint64_t curr = ROOT * PAGE_SIZE;
    uint64_t p_ref[TABLES_DEPTH + 1] = {0};
    uint64_t pageNum = breakVirtualAddress(p_ref, virtualAddress);
    uint64_t father = NUM_FRAMES + 1;

    access(virtualAddress, value, &curr, &father, p_ref);
    uint64_t offset = p_ref[0];
//    PMrestore(curr / PAGE_SIZE, pageNum);
//    cout << "in VMwrite, curr = " << curr << endl;
    PMwrite(curr + offset, value);
    if (father < NUM_FRAMES) {
        PagesToFrames[pageNum][0] = curr / PAGE_SIZE;
        PagesToFrames[pageNum][1] = father * PAGE_SIZE + p_ref[1];
    }
    return 1;
}


void print_all_frames() {
    word_t word;
    for (int f = 0; f < NUM_FRAMES; ++f) {
        for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
            PMread(f * PAGE_SIZE + i, &word);
        }
    }
}



// TODO: delete import of ostream and all the prints
// TODO: delete print all frames