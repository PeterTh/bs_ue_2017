// this file implements a version of malloc based on local freelist allocators for each thread

#include "freelist.h"

// use __thread (for older GCC) or C11 _Thread_local
// since I'm too lazy to implement it using pthread_setspecific and pthread_getspecific
__thread freelist_allocator _local_freelist_allocator;

// everything else is easy since the compiler takes care of directly using our threadlocal instance

static inline void* my_malloc(size_t size) {
	return freelist_malloc(&_local_freelist_allocator, size);
}

static inline void my_free(void *mem) {
	freelist_free(&_local_freelist_allocator, mem);
}