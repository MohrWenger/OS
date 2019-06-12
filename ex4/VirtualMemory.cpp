#include <cmath>
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

using namespace std;


/** Constants */
#define ROOT 0


/**
 * Breaks the virtual address to the offset and the addresses for each table in the representing tree.
 * @param p - a pointer to the array which will contain the addresses.
 * @param addr - the logical address to be handled.
 * @return the offset.
 *
 */
uint64_t breakVirtualAddress(uint64_t *p, uint64_t addr) {
    uint64_t pageNum = addr >> OFFSET_WIDTH;
    while (addr) {
        *p = (addr & (uint64_t) (pow(2, OFFSET_WIDTH) - 1));
        addr = addr >> OFFSET_WIDTH;
        p += 1;
    }
    return pageNum;
}

/**
 * clears all the rows of a frame.
 * @param frameIndex - the frame to clear.
 */
void clearTable(uint64_t frameIndex) {
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

/**
 * Calculates the distance between two pages stored in the memory table.
 * @param pageNum - the desired page to check distance from.
 * @param potential - the page to be checked.
 * @return the distance.
 */
int calcDist(uint64_t potential, uint64_t pageNum) {
    return static_cast<int>(fmin(abs((int) pageNum - (int) potential),
                                 NUM_PAGES - (abs((int) pageNum - (int) potential))));
}

/**
 * The recursive helper ment to find the frame to be used next.
 * @param prev - the previous frame sent. starts from Root.
 * @param row - the current row the recursion checks.
 * @param depth - current depth in the memory tree.
 * @param max_t - the latets frame assigned.
 * @param found - holds the address of the chosen address.
 * @param father - the father of the currently checked frame.
 * @param firstRun - a boolean. true if this is the first run of the recursion.
 * @param max_dst - the maximal distance found in case we need to evict a frame.
 * @param pageToEvict - the page to be evicted.
 * @param fatherEvicted - the father of the page to be evicted.
 * @param curr_page - the page currently being checked for distance.
 * @param frame - the frame to check in the next iteration.
 * @param page_to_insert - the page to insert in case of eviction.
 * @param current
 */
void get_frame_helper(const uint64_t *prev, int row, int depth, uint64_t *max_t, uint64_t *found,
                      uint64_t *father, bool firstRun, int *max_dst, uint64_t *pageToEvict,
                      uint64_t *fatherEvicted, uint64_t curr_page, uint64_t *frame, uint64_t
                      page_to_insert, uint64_t current) {
    uint64_t curr = 0;
    auto curr_to_read = (word_t) curr;
    if (!firstRun) {
        PMread(*prev * PAGE_SIZE + row, &curr_to_read);
        curr = (uint64_t) curr_to_read;
    }
    if (depth == 0) {               // if in leaf - check distances for possible eviction
        int d = calcDist(curr_page, page_to_insert);
        if (d > *max_dst) {
            *max_dst = d;
            *pageToEvict = curr_page;
            *fatherEvicted = *prev * PAGE_SIZE + row;
            *frame = curr;
            return;
        }
    } else {                        // else - continue recursion
        int zeros = 0;
        word_t row_val;
        for (int i = 0; i < PAGE_SIZE; i++) {
            PMread(curr * (uint64_t) PAGE_SIZE + i, &row_val);
            if (row_val == 0) {
                zeros++;
            } else {
                if (*max_t < (uint64_t)row_val) {
                    *max_t = (uint64_t) row_val;
                }
                get_frame_helper(&curr, i, depth - 1, max_t, found, father, false, max_dst,
                                 pageToEvict, fatherEvicted, curr_page + i * (uint64_t) pow
                                (PAGE_SIZE, depth - 1),
                                 frame, page_to_insert, current);
            }
        }
        if (zeros == PAGE_SIZE && (curr != current)) {       // possible available empty frame to use.
            *found = (int) curr;
            *father = *prev * PAGE_SIZE + row; //TODO - make sure deepest frame is returned
        }
    }
}

/**
 * Returns the frame to be used next - according to the given set of priorities.
 * @param lastFound - the frame found in the previouse iteration.
 * @param pageNum - the page offset.
 * @param father - the father of the current frame.
 * @param curr - the current frame.
 * @return address of the frame.
 */
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
                     &father_to_evict, num_evicted, &frame, pageNum, current);
    if (found > 0) {            // an available frame was found.
        PMwrite(*father, 0);
        clearTable(found);
        return (uint64_t) found;
    } else if (max_t < NUM_FRAMES - 1) { // there are frames which were not assigned.
        clearTable(max_t + 1);
        return max_t + 1;

    } else if (frame != 0) {            // no empty frames, evict is needed.
        PMevict(frame, page_to_evict);
        PMwrite(father_to_evict, 0);
        clearTable(frame);
        return frame;
    }
    return 0;
}

/**
 * Initializes frame 0 - the ROOT
 */
void VMinitialize() {
    clearTable(0);
}

/**
 * Traversing the tree in order to access the correct line in the correct page.
 * @param virtualAddress - the virtual address of the correct line.
 * @param value - the value to be read to / written from
 * @param curr - the current location in the tree.
 * @param father - the father of the current frame.
 * @param p_ref - the array representing the traversing path.
 */
int treeTraversing(uint64_t virtualAddress, word_t value, uint64_t *curr, uint64_t *father, uint64_t *p_ref) {
    uint64_t pageNum = breakVirtualAddress(p_ref, virtualAddress);
    word_t addr_i;
    uint64_t prevFrame = 0;
    uint64_t foundFather = 0;
    for (int i = TABLES_DEPTH; i > 0; --i) {
        PMread(*curr + p_ref[i], &addr_i);
        if (!addr_i) {
            uint64_t frame = getFrame(prevFrame, pageNum, &foundFather, curr);

            if (i == 1) {
                PMrestore(frame, virtualAddress >> OFFSET_WIDTH);
            }

            if ((int)frame != -1) {
                *father = (uint64_t) prevFrame;
                prevFrame = frame;
                PMwrite(*curr + p_ref[i], (word_t) frame);
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

/**
 * reads the word from the virtual address virtualAddress into *value. Returns 1 on success and 0 on failure.
 * @param virtualAddress - the desired virtual address
 * @param value - the desired value.
 */
int VMread(uint64_t virtualAddress, word_t *value) {
    uint64_t curr = ROOT * PAGE_SIZE;
    uint64_t p_ref[TABLES_DEPTH + 1] = {0};
    breakVirtualAddress(p_ref, virtualAddress);
    uint64_t father = NUM_FRAMES + 1;

    treeTraversing(virtualAddress, *value, &curr, &father, p_ref);

    uint64_t offset = p_ref[0];
    PMread(curr + offset, value);
    return 1;
}

/**
 * reads the word from the virtual address virtualAddress into *value. Returns 1 on success and 0 on failure.
 * @param virtualAddress - the desired virtual address
 * @param value - the desired value.
 */
int VMwrite(uint64_t virtualAddress, word_t value) {
    uint64_t curr = ROOT * PAGE_SIZE;
    uint64_t p_ref[TABLES_DEPTH + 1] = {0};
    breakVirtualAddress(p_ref, virtualAddress);
    uint64_t father = NUM_FRAMES + 1;

    treeTraversing(virtualAddress, value, &curr, &father, p_ref);
    uint64_t offset = p_ref[0];
    PMwrite(curr + offset, value);
    return 1;
}
