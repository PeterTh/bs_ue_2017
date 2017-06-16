// this file implements a version of malloc based on a global freelist allocator protected by a lock 

#include "freelist.h"

#include <pthread.h> 

pthread_mutex_t _global_freelist_mutex = PTHREAD_MUTEX_INITIALIZER; 

freelist_allocator _global_freelist_allocator;

// simply use the global freelist with global locking

static inline void* my_malloc(size_t size) {
	pthread_mutex_lock(&_global_freelist_mutex);
	void * ret = freelist_malloc(&_global_freelist_allocator, size);
	pthread_mutex_unlock(&_global_freelist_mutex);
	return ret;
}

static inline void my_free(void *mem) {
	pthread_mutex_lock(&_global_freelist_mutex);
	freelist_free(&_global_freelist_allocator, mem);
	pthread_mutex_unlock(&_global_freelist_mutex);
}
