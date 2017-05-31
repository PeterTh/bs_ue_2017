
#include "bank.h"

int main(int argc, char**argv) {
	if(argc != 2) {
		printf("Usage: ./bank_client [id]\n");
		return -1;
	}
	
	int id = atoi(argv[1]); // we assume correct format for the parameter
	printf("Client id %d starting...\n", id);
	
	int bank_fifo = create_and_open_fifo(O_WRONLY);
	
	// open semaphore
	sem_t* sema = sem_open(CLIENT_SEMA_NAME, O_CREAT, 0666, 1);
	if(sema == SEM_FAILED) {
		perror("Client: failed to open semaphore");
	}
	
	for(int i=0; i<NUM_DEPOSITS; ++i) {
		sem_wait(sema);
		write(bank_fifo, &id, sizeof(int));
		int balance = BALANCE_EACH_DEPOSIT;
		write(bank_fifo, &balance, sizeof(int));
		sem_post(sema);
	}
	
	close(bank_fifo);
	sem_close(sema);
}
