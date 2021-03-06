//
// Created by mohrw on 08/06/2019.
//

#ifndef EX4_VIRTUALMEMORY_H
#pragma once

#include "MemoryConstants.h"

/*
 * Initialize the virtual memory
 */
void VMinitialize();

/* reads a word from the given virtual address
 * and puts its content in *value.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMread(uint64_t virtualAddress, word_t* value);

/* writes a word to the given virtual address
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */

int VMwrite(uint64_t virtualAddress, word_t value);


void print_all_frames();
#define EX4_VIRTUALMEMORY_H

#endif //EX4_VIRTUALMEMORY_H
