
#include "shared.h"

int main(int argc, char** argv) {
	// parse student count
	int student_count = -1;
	if (!parse_int_arg(argc, argv, &student_count)) return EXIT_FAILURE;

	// create and map shared memory object
	int shmfd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (shmfd == -1) return xerror("shm_open");
	int shmem_length = sizeof(smem_content) + sizeof(sem_t);
	if (ftruncate(shmfd, shmem_length) == -1) return xerror("ftruncate");
	smem_content* shmem_content = (smem_content*)mmap(NULL, shmem_length, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
	if (shmem_content == MAP_FAILED) return xerror("mmap");
	sem_t* shmem_sem = (sem_t*)(shmem_content + 1);

	// create semaphore
	if (sem_init(shmem_sem, true, 1) == -1) return xerror("sem_init");

	// create pipe
	if (mkfifo(FIFO_NAME, 0600) == -1) return xerror("mkfifo");
	FILE* pipe = fopen(FIFO_NAME, "r");
	if (pipe == NULL) return xerror("fopen");

	// create student result counters
	int students[student_count];
	memset(students, 0, sizeof(int) * student_count);

	while (!feof(pipe)) {
		int student_id;
		fscanf(pipe, "%d", &student_id);
		if (student_id >= student_count) return xerror("student id >= student_count\n");
		// after receiving the student_id, shmem is still locked by the semaphore
		// we can access shmem without problems because student has finished writing
		if (student_id != shmem_content->student_id) return xerror("student id mismatch\n");
		// increment counter (and grade and term/kill student)
		students[student_id]++;
		if (students[student_id] == 5) {
			int grade = 1 + rand() % 5;
			printf("student %2d: grade %d\n", student_id, grade);
			int sig = grade == 5 ? SIGKILL : SIGTERM;
			if (kill(shmem_content->student_process_id, sig) == -1) return xerror("kill");
		}
		// increment semaphore, so the next student can send his results
		if (sem_post(shmem_sem) == -1) return xerror("sem_post");
	}

	// close/remove/destroy resources
	if (fclose(pipe) != 0) return xerror("fclose");
	if (remove(FIFO_NAME) < 0) return xerror("remove");
	if (sem_destroy(shmem_sem) == -1) return xerror("sem_destroy");
	if (munmap(shmem_content, shmem_length) == -1) return xerror("munmap");
	if (close(shmfd) == -1) return xerror("close");
	if (shm_unlink(SHARED_MEMORY_NAME) == -1) return xerror("shm_unlink");
}
