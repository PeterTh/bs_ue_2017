#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>

#define SHARED_MEMORY_NAME "/os_test_shm"
#define SEMAPHORE_NAME "/os_test_sem"
#define FIFO_NAME "REQUEST_FIFO"

typedef struct {
	int student_id;			// id, from 0 to N-1
	pid_t student_process_id;	// process id of the process for this student
	char result[30];		// result (unused)
} smem_content;

int xerror(const char* msg);
bool parse_int_arg(int argc, char** argv, int* out);

#endif
