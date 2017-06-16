// this is a simple test of our freelist allocators
// it doesn't match "membench" exactly -- but no one had an issue with that exercise anyway

#define NUM_T 8
#define NUM_ALLOCS 1000000
#define MAX_ALLOC_SIZE 1024

#ifdef LOCAL
#include "freelist_threadlocal.h" 
#endif
#ifdef GLOBAL
#include "freelist_global.h" 
#endif

#include <pthread.h> 
#include <stdlib.h> 

void* bench(void* p) {
	unsigned seed = 42;
	for(int i=0; i<NUM_ALLOCS; ++i) {
		void *mem = my_malloc(rand_r(&seed)%(MAX_ALLOC_SIZE-1) + 1);
		my_free(mem);
	}
	return NULL;
}

int main() {
	pthread_t threads[NUM_T];
	for(int i=0; i<NUM_T; ++i) {
		pthread_create(&threads[i], NULL, &bench, NULL);
	}
		
	for(int i=0; i<NUM_T; ++i) {
		pthread_join(threads[i], NULL);
	}		
}