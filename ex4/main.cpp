#include <iostream>
#include "VirtualMemory_old.h"
#include "ConstantsTest.h"
#include <cmath>

using namespace std;


int main() {
//    cout << "WORD_WIDTH = " << WORD_WIDTH << std::endl;
//    cout << "OFFSET_WIDTH = " << OFFSET_WIDTH << std::endl;
//    cout << "PAGE_SIZE = " << PAGE_SIZE << std::endl;
//    cout << "PHYSICAL_ADDRESS_WIDTH = " << PHYSICAL_ADDRESS_WIDTH << std::endl;
//    cout << "RAM_SIZE = " << RAM_SIZE << std::endl;
//    cout << "VIRTUAL_ADDRESS_WIDTH = " << VIRTUAL_ADDRESS_WIDTH << std::endl;
//    cout << "VIRTUAL_MEMORY_SIZE = " << VIRTUAL_MEMORY_SIZE << std::endl;
//    cout << "NUM_FRAMES= " << NUM_FRAMES << std::endl;
//    cout << "NUM_PAGES = " << NUM_PAGES << std::endl;
//    cout << "TABLES_DEPTH = " << TABLES_DEPTH << std::endl;
//    uint64_t x = 1302;


    print_all_frames ();
    VMwrite(13, 3);
    VMwrite(13, 3);
    print_all_frames ();
//    cout << endl;

//    word_t val;
//    VMread(13, &val);
//    cout << "val = "<< val << endl;
//
//    VMwrite(6, 22);
//    cout << endl;
//    VMread(6, &val);
//    cout << "val = "<< val << endl;
//
//    cout << endl;
//    word_t x;
//

//    cout << endl;
//    VMread (31, &x);
//    cout << endl;
//    print_all_frames();

    return 0;


}


