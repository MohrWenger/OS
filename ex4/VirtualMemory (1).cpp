#include "VirtualMemory.h"
#include "PhysicalMemory.h"
#include <stdlib.h>
#include <math.h>


/* Pre-Declaration of functions */
uint64_t searchTable(uint64_t virtualAddress);
void handleMissingTable(uint64_t forbiddenNumber, uint64_t virtualAddress, uint64_t*
	  pageNumber, uint64_t* nextPage, uint64_t offset);
void dfs(uint64_t frameNumber, uint64_t offset, uint64_t* max, int depthCounter,
		 uint64_t* emptyFrame, uint64_t* emptyParent, uint64_t* frameEvict, uint64_t*
		 virtualPageEvict, uint64_t* evictParent, uint64_t virtualPage, uint64_t forbiddenNumber,
		 uint64_t parent, uint64_t p, uint64_t* currMinEvict);
uint64_t evictingMinimum(uint64_t page_swapped_in, uint64_t p);
int countDigits(uint64_t num);

/**
 * clears a specific frame
 * @param frameIndex frame to clean
 */
void clearTable(uint64_t frameIndex)
{
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
		PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

/**
 * initializes virtual memory by putting zeros in all of frame 0
 */
void VMinitialize()
{
    clearTable(0);
}

/**
 * reads from virtual memory
 * @param virtualAddress to write to
 * @param value to write
 * @return 1 upon success 0 therwise
 */
int VMread(uint64_t virtualAddress, word_t* value)
{
	if(countDigits(virtualAddress) > VIRTUAL_ADDRESS_WIDTH)
	{
		return 0;
	}
	uint64_t frameNumber = searchTable(virtualAddress);
	uint64_t offset = virtualAddress % PAGE_SIZE;
	PMrestore(frameNumber, virtualAddress >> OFFSET_WIDTH);
	frameNumber = frameNumber<< OFFSET_WIDTH;
	frameNumber = frameNumber + offset;
	PMread(frameNumber, value);
	return 1;
}

/**
 * writes to virtual memory
 * @param virtualAddress to write to
 * @param value to write
 * @return 1 upon success 0 otherwise
 */
int VMwrite(uint64_t virtualAddress, word_t value)
{
	if(countDigits(virtualAddress) > VIRTUAL_ADDRESS_WIDTH)
	{
		return 0;
	}
    uint64_t frameNumber = searchTable(virtualAddress);
    uint64_t offset = virtualAddress % PAGE_SIZE;
	PMrestore(frameNumber, virtualAddress >> OFFSET_WIDTH);
    frameNumber = frameNumber << OFFSET_WIDTH;
	frameNumber = frameNumber + offset;
	PMwrite(frameNumber, value);
	return 1;
}

/**
 * Searchs through the tables to find the correct location in which to write
 * @param virtualAddress to look for physically
 * @return address to write/read
 */
uint64_t searchTable(uint64_t virtualAddress)
{
	uint64_t frameNumber = 0;
	word_t nextWord = 0;
	uint64_t nextFrame = 0;
	uint64_t firstOffsetWidth = VIRTUAL_ADDRESS_WIDTH % OFFSET_WIDTH;
	if(firstOffsetWidth == 0){
		firstOffsetWidth = OFFSET_WIDTH;
	}
	int unUsedBits = VIRTUAL_ADDRESS_WIDTH - firstOffsetWidth;
	uint64_t offset = virtualAddress >> (VIRTUAL_ADDRESS_WIDTH - firstOffsetWidth);
	for(int i = 0; i < TABLES_DEPTH; ++i)
	{
		PMread((frameNumber * PAGE_SIZE) + offset, &nextWord);
		nextFrame = (uint64_t)nextWord;
		if(nextFrame == 0)
		{
			handleMissingTable(frameNumber, virtualAddress, &frameNumber, &nextFrame, offset);
			clearTable(nextFrame);
		}
		frameNumber = nextFrame;
		offset = virtualAddress % (1LL << unUsedBits); // cutting off the left side of the number
		offset = offset >> (unUsedBits - OFFSET_WIDTH); // cutting off the right side of the number
		unUsedBits = unUsedBits - OFFSET_WIDTH; // going to be used in next iteration
	}
	return frameNumber;
}

/**
 * handles missing tables with three options of finding an alternative:
 * 1 - frame of zeros
 * 2 - not all pages in use
 * 3 - we are evicting a frame
 */
void handleMissingTable(uint64_t forbiddenNumber, uint64_t virtualAddress, uint64_t*
	pageNumber, uint64_t* nextPage, uint64_t offset)
{

	uint64_t max = 0;
	uint64_t emptyFrame = NUM_FRAMES +1;
	uint64_t emptyParent = 0;
	uint64_t virtualPageEvict = 0;
	uint64_t evictParent = 0;
	uint64_t frameEvict = 0;
	uint64_t currMinEvict = 0;
	dfs(0, 0,&max, 0, &emptyFrame, &emptyParent, &frameEvict, &virtualPageEvict, &evictParent,
			virtualAddress >> PAGE_SIZE, forbiddenNumber, 0, 0, &currMinEvict);
	if (emptyFrame != NUM_FRAMES +1)
	{
		PMwrite(emptyParent, 0); // deleting previous parent
		PMwrite((*pageNumber) * PAGE_SIZE + offset, (word_t)emptyFrame); // updating tree
		*nextPage = emptyFrame;
	}
	else if(max < NUM_FRAMES - 1)
	{
		PMwrite((*pageNumber) * PAGE_SIZE + offset, (word_t)max+1); //updating tree
		*nextPage = max+1;
	}
	else
	{
		PMwrite((*pageNumber) * PAGE_SIZE + offset, (word_t)frameEvict); //updating tree
		PMevict(frameEvict, virtualPageEvict); //evicting
		PMwrite(evictParent, 0); // deleting previous parent
		*nextPage = frameEvict;
	}
}

/**
 * runs a DFS search on the tree and finds 3 parameters: empty frame, maximal used frame, page
 * with minimal cyclic distance for eviction
 * @param frameNumber
 * @param offset
 * @param max
 * @param depthCounter
 * @param emptyFrame
 * @param emptyParent parent of node that was found empty
 * @param frameEvict
 * @param virtualPageEvict
 * @param evictParent parent of node we want to evactually evict
 * @param virtualPage
 * @param forbiddenNumber page from which we started
 * @param parent constantly updated
 * @param p
 */
void dfs(uint64_t frameNumber, uint64_t offset, uint64_t* max, int depthCounter,
		uint64_t* emptyFrame, uint64_t* emptyParent, uint64_t* frameEvict, uint64_t*
		virtualPageEvict, uint64_t* evictParent, uint64_t virtualPage, uint64_t forbiddenNumber,
		uint64_t parent, uint64_t p, uint64_t* currMinEvict)
{
	int zeros = 0;
	word_t word;
	for(uint64_t i = 0; i < PAGE_SIZE; ++i)
	{
		PMread(frameNumber * PAGE_SIZE + i, &word);
		if(word != 0 && depthCounter < TABLES_DEPTH) //going down the tree
		{
			dfs((uint64_t)word, i, max, depthCounter + 1, emptyFrame, emptyParent, frameEvict,
					virtualPageEvict, evictParent, virtualPage, forbiddenNumber, frameNumber, p +
					i * (uint64_t)pow(PAGE_SIZE, TABLES_DEPTH - depthCounter - 1), currMinEvict);
		}
		if(word == 0) //counting if the frame is all zeros
		{
			zeros++;
		}
	}
	if(frameNumber > *max) //updating maximum
	{
		*max = frameNumber;
	}
	//calculations for empty page of zeros
	if((zeros == PAGE_SIZE) && (*emptyFrame > frameNumber) && (frameNumber != forbiddenNumber)
		&& depthCounter != TABLES_DEPTH)
	{
		*emptyParent = parent * PAGE_SIZE + offset;
		*emptyFrame = frameNumber;
	}
	//calculations for evicting
	if(depthCounter == TABLES_DEPTH && (frameNumber != forbiddenNumber))
	{
		uint64_t evictingMin = evictingMinimum(virtualPage >> PAGE_SIZE, p);
		if(*currMinEvict < evictingMin)
		{
			*currMinEvict = evictingMin;
			*evictParent = parent * PAGE_SIZE + offset;
			*virtualPageEvict = p;
			*frameEvict = frameNumber;
		}
	}
}


/**
 * calculates the cyclic distance from current page
 * @param page_swapped_in the page we are trying to insert
 * @param p the page taking the spot we are trying to insert to
 * @return minimal cyclic distance
 */
uint64_t evictingMinimum(uint64_t page_swapped_in, uint64_t p)
{
	uint64_t min;
	if(page_swapped_in > p)
	{
		min = page_swapped_in - p;
	}
	else
	{
		min = p - page_swapped_in;
	}
	if(NUM_PAGES - min > min)
	{
		return min;
	}
	return NUM_PAGES - min;
}

/**
 * function to count digits
 */
int countDigits(uint64_t num)
{
	int count=0;
	while(num>0)
	{
		count++;
		num/=10;
	}
	return count;
}