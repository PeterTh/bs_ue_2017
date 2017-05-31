
#include "shared.h"

int main(int argc, char** argv) {
	// parse student id
	int student_id = -1;
	if (!parse_int_arg(argc, argv, &student_id)) return EXIT_FAILURE;

	// open and map shared memory object
	int shmfd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0600);
	if (shmfd == -1) return xerror("shm_open");
	int shmem_length = sizeof(smem_content) + sizeof(sem_t);
	smem_content* shmem_content = (smem_content*)mmap(NULL, shmem_length, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
	if (shmem_content == MAP_FAILED) return xerror("mmap");
	sem_t* shmem_sem = (sem_t*)(shmem_content + 1);

	// open pipe
	FILE* pipe = fopen(FIFO_NAME, "w");
	if (pipe == NULL) return xerror("fopen");

	for (int i = 0; i < 5; i++) {
		sleep(2 + rand() % 4);
		// wait and decrement semaphore
		if (sem_wait(shmem_sem) == -1) return xerror("sem_wait");
		// send results
		shmem_content->student_id = student_id;
		shmem_content->student_process_id = getpid();
		fprintf(pipe, "%d\n", student_id);
		fflush(pipe);
	}

	// wait for kill
	sleep(60);
	fprintf(stderr, "should be dead now ...\n");
}
