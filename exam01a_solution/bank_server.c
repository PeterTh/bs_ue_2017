
#include "bank.h"

int main(int argc, char**argv) {
	
	// create and map smem, create and open FIFO
	int shmfile = shm_open(ACCOUNT_SHM_NAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if(shmfile < 0) {
		perror("Failed creating SHM");
	}
	ftruncate(shmfile, ACCOUNTS_BYTES);
	int *accounts = mmap(NULL, ACCOUNTS_BYTES, PROT_READ|PROT_WRITE, MAP_SHARED, shmfile, 0);
	if(MAP_FAILED == accounts) {
		perror("Failed mapping SHM");
	}		
	int bank_fifo = create_and_open_fifo(O_RDONLY | O_NONBLOCK);

	int num_children = 0;	
	for(;;) {
		int id = -1, q = -1;
		ssize_t ret = read(bank_fifo, &id, sizeof(int));
		if(ret > 0) ret = read(bank_fifo, &q, sizeof(int));
		if(ret == -1) continue; // -1 means that pipe is currently empty -> retry
		pid_t pid = fork();
		num_children++;
		if(pid<0) perror("Failed to fork");
		// client updates
		if(pid == 0) {
			// use atomic to protect update -- slightly less code than using a semaphore
			__sync_fetch_and_add(&accounts[id], q); 
			exit(0);
		}
		// parent simply continues
		// break if EOS
		if(ret == 0) break;
	}
	
	// wait for all child processes
	for(int i=0; i<num_children; ++i) wait(NULL);
	
	// print balances
	for(int id=0; id<NUM_ACCOUNTS; ++id) {
		printf("Balance %2d: %10d\n", id, accounts[id]);
	}
	
	close(bank_fifo);
	munmap(accounts, ACCOUNTS_BYTES);
	close(shmfile);
	shm_unlink(ACCOUNT_SHM_NAME);
}
