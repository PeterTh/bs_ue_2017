// this file contains the implementation of a very basic freelist allocator

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define FREELIST_MAX_POW 16

// one block in one of our freelists
// instead of storing its size, we store the index of the freelist it belongs to
// in a realistic allocator, we would allocate a larger number of these blocks at once, rather than individually
typedef struct _freelist_block {
	struct _freelist_block *next_free;
	unsigned freelist_index;
	char memory[];
} freelist_block;

// our freelist allocator
// it has one linked list of "freelist_block"s for each power of two up to and including  FREELIST_MAX_POW
typedef struct _freelist_allocator {
	freelist_block* lists[FREELIST_MAX_POW+1];
} freelist_allocator;

// initialize all lists to NULL (we have no free blocks allocated at startup)
// we don't need to do this for global allocators, since they are 0-initialized anyway
static inline void freelist_init(freelist_allocator *to_init) {
	for(int i=0; i<=FREELIST_MAX_POW; ++i) {
		to_init->lists[i] = NULL;
	}
}

// let the OS reclaim all blocks which were acquired by this allocator
static inline void freelist_destroy(freelist_allocator *to_destroy) {
	for(int i=0; i<=FREELIST_MAX_POW; ++i) {
		freelist_block* top;
		while((top = to_destroy->lists[i])) {
			to_destroy->lists[i] = top->next_free;
			free(top);
		}
	}
}

// select the index of the freelist fitting "size"
static inline int freelist_select(size_t size) {
	int v = 1;
	for(int i=0; i<FREELIST_MAX_POW; ++i) {
		if(size <= v) return i;
		v <<= 1;
	}
	return -1;
}

// allocate a block of the given size in our allocator
static inline void* freelist_malloc(freelist_allocator *allocator, size_t size) {
	int freelist_index = freelist_select(size);
	if(freelist_index >= 0) {
		freelist_block *block;
		// if we have a free block available, remove it from the list and return its memory
		if((block = allocator->lists[freelist_index])) {
			allocator->lists[freelist_index] = block->next_free;
			return &(block->memory);
		}
		// otherwise, allocate a new block 
		// with size 2^(freelist_index), plus our maintenance overhead, which is sizeof(freelist_block)
		else {
			block = (freelist_block*)malloc(sizeof(freelist_block) + (1<<freelist_index));
			block->next_free = NULL;
			block->freelist_index = freelist_index;
			// tag the pointer so we can recognize it when we free it
			return &(block->memory);
		}
	}
	// it does not fit into any of our freelists -- fail 
	// - a real allocator would fall back to another method here
	printf("Trying to allocate %lu byte on freelist_allocator - too large\n", size);
	abort();
}

// free a block and return it to its freelist on the given allocator
static inline void freelist_free(freelist_allocator *allocator, char* user_ptr) {
	// we know that the user pointer is part of one of our block structures
	freelist_block *block = (freelist_block*)(user_ptr - offsetof(freelist_block, memory));
	// return it to the correct freelist on the allocator
	block->next_free = allocator->lists[block->freelist_index];
	allocator->lists[block->freelist_index] = block->next_free;
}
