#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#define BANK_FIFO_NAME  "BANK_FIFO"
#define ACCOUNT_SHM_NAME  "ACCOUNTS"
#define CLIENT_SEMA_NAME  "/CLIENT_SEMA"

#define NUM_ACCOUNTS 20
#define ACCOUNTS_BYTES (NUM_ACCOUNTS*sizeof(int))

#define NUM_DEPOSITS 50
#define BALANCE_EACH_DEPOSIT 2

// used to create (if not already existing) and open fifo in both client and server
// with the given flags for "open" (e.g. read/write/nonblock)
int create_and_open_fifo(int oflags);
