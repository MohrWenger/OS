#include <cmath>
#include <iostream>
#include <cmath>
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

#define ROOT 0

using namespace std;

uint64_t PagesToFrames[NUM_PAGES][2] = { 0 };

uint64_t breakVirtualAddress ( uint64_t *p, uint64_t addr )
{
    uint64_t pageNum = addr >> OFFSET_WIDTH;
    while ( addr )
    {
        *p = ( addr & ( uint64_t ) ( pow ( 2, OFFSET_WIDTH ) - 1 ) );
        addr = addr >> OFFSET_WIDTH;
        p += 1;
    }
    return pageNum;
}

void clearTable ( uint64_t frameIndex )
{
    for ( uint64_t i = 0; i < PAGE_SIZE; ++ i )
    {
        PMwrite ( frameIndex * PAGE_SIZE + i, 0 );
    }
}


void get_frame_helper ( const uint64_t *prev, const int row, int depth, uint64_t *max_t, int *found, uint64_t *father,
                        bool firstRun )
{
    uint64_t curr = 0;
    auto curr_to_read = ( word_t ) curr;
    if ( ! firstRun )
    {
        PMread ( *prev * PAGE_SIZE + row, &curr_to_read );
        curr = ( uint64_t ) curr_to_read;
    }
    if ( depth == 0 )
    {
        return;
    }
    else
    {
        int zeros = 0;
        word_t row_val;
        for ( int i = 0; i < PAGE_SIZE; i ++ )
        {
            PMread ( curr * ( uint64_t ) PAGE_SIZE + i, &row_val );
            if ( row_val == 0 )
            {
                zeros ++;
            }
            else
            {
                if ( *max_t < row_val )
                {
                    *max_t = ( uint64_t ) row_val;
                }
                get_frame_helper ( &curr, i, depth - 1, max_t, found, father, false );
            }
        }

        if ( zeros == PAGE_SIZE )
        { //TODO check prev != null
            *found = ( int ) curr;
            *father = *prev * PAGE_SIZE + row;
        }
    }
}

void getFrameToEvict ( uint64_t pageNum, uint64_t *frame, uint64_t *page )
{
    uint64_t best_frame = 0;
    uint64_t best_page = 0;
    int max = 0;
    for ( uint64_t i = 0; i < NUM_PAGES; ++ i )
    {
        if ( ! PagesToFrames[ i ][ 0 ] )
        {
            continue;
        }
        int dist = static_cast<int>(fmin ( abs ( ( int ) pageNum - ( int ) i ),
                                           NUM_PAGES - ( abs ( ( int ) pageNum - ( int ) i ) ) ));

        if ( dist > max )
        {
            max = dist;
            best_frame = PagesToFrames[ i ][ 0 ];
            best_page = i;
        }
    }
    *frame = best_frame;
    *page = best_page;
}

uint64_t getFrame ( uint64_t lastFound, uint64_t pageNum )
{
    int d = TABLES_DEPTH;
    uint64_t max_t = 0;    //TODO maybe uint64_t ?
    uint64_t prev = 0;
    int row = ROOT;
    int found = - 1;
    uint64_t father;
    get_frame_helper ( &prev, row, d, &max_t, &found, &father, true );

    if ( found > 0 && found != lastFound )
    {
        PMwrite ( father, 0 );
        clearTable (found);
        cout << found << endl;
        return ( uint64_t ) found;


        //TODO we think it is ok but habent actually got here yet
        // TODO - also clear table / father?
    }
    else if ( max_t < NUM_FRAMES - 1 )
    {
        return max_t + 1;
    }
    else
    {
        uint64_t frame_to_evict;
        uint64_t page_to_swap;
        getFrameToEvict ( pageNum, &frame_to_evict, &page_to_swap );
        clearTable ( page_to_swap );

        uint64_t page_father = PagesToFrames[ page_to_swap ][ 1 ];
//        print_all_frames ();
//        cout << ">>>> " << page_father << endl;
        PMwrite (page_father, 0);
//        print_all_frames ();

        return frame_to_evict;
    }
}


void VMinitialize ( )
{
    clearTable ( 0 );
}

int access ( uint64_t virtualAddress, word_t value, uint64_t *curr, uint64_t *father, uint64_t *p_ref )
{
    uint64_t pageNum = breakVirtualAddress ( p_ref, virtualAddress );
    word_t addr_i;
    uint64_t prevFrame = 0;
    for ( int i = TABLES_DEPTH; i > 0; -- i )
    {
        PMread ( *curr + p_ref[ i ], &addr_i );
        if ( ! addr_i )
        {
            uint64_t frame = getFrame ( prevFrame, pageNum );

            if ( frame != - 1 )
            {
                *father = ( uint64_t ) prevFrame;
                prevFrame = frame;
                PMwrite ( *curr + p_ref[ i ], frame );
                *curr = ( uint64_t ) ( frame ) * PAGE_SIZE;
            }
            else
            {
                return - 1;
                // TODO - handle failed
            }
        }
        else
        {
            *curr = ( ( uint64_t ) addr_i * PAGE_SIZE );
        }
    }

    return - 1;
}


int VMread ( uint64_t virtualAddress, word_t *value )
{

    uint64_t curr = ROOT * PAGE_SIZE;
    uint64_t p_ref[TABLES_DEPTH + 1] = { 0 };
    uint64_t pageNum = breakVirtualAddress ( p_ref, virtualAddress );
    uint64_t father = NUM_FRAMES + 1;

    access ( virtualAddress, *value, &curr, &father, p_ref );

    uint64_t offset = p_ref[ 0 ];
    PMread ( curr + offset, value );
    if ( father < NUM_FRAMES )
    {
        PagesToFrames[ pageNum ][ 0 ] = curr / PAGE_SIZE;
        PagesToFrames[ pageNum ][ 1 ] = father * PAGE_SIZE + p_ref[ 1 ];
        cout << "father = " << PagesToFrames[ pageNum ][ 1 ] << ", son = " << pageNum << endl;
    }
    return 1;
}


int VMwrite ( uint64_t virtualAddress, word_t value )
{
    uint64_t curr = ROOT * PAGE_SIZE;
    uint64_t p_ref[TABLES_DEPTH + 1] = { 0 };
    uint64_t pageNum = breakVirtualAddress ( p_ref, virtualAddress );
    uint64_t father = NUM_FRAMES + 1;

    access ( virtualAddress, value, &curr, &father, p_ref );

    uint64_t offset = p_ref[ 0 ];
    PMwrite ( curr + offset, value );
    if ( father < NUM_FRAMES )
    {
        PagesToFrames[ pageNum ][ 0 ] = curr / PAGE_SIZE;
        PagesToFrames[ pageNum ][ 1 ] = father * PAGE_SIZE + p_ref[ 1 ];
        cout << "father = " << PagesToFrames[ pageNum ][ 1 ] << ", son = " << pageNum << endl;
    }
//    cout << father << endl;
    return 1;
}


void print_all_frames ( )
{
    word_t word;
    for ( int f = 0; f < NUM_FRAMES; ++ f )
    {
        for ( uint64_t i = 0; i < PAGE_SIZE; ++ i )
        {
            PMread ( f * PAGE_SIZE + i, &word );
            cout << "frame number: " << f << ", row number: " << i << " has: " << word << endl;
        }
    }
}

