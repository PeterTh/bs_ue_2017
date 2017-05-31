
#include "bank.h"

inline int create_and_open_fifo(int oflags) {
	int status = mkfifo(BANK_FIFO_NAME, 0666);
	if(status != 0) {
		if(errno != EEXIST) {
			perror("Failed creating FIFO");
		}
	}
	
	int bank_fifo = open(BANK_FIFO_NAME, oflags);
	if(bank_fifo < 0) {
		perror("Failed to open FIFO");
	}
	
	return bank_fifo;
}
