CFLAGS = -Wall -Werror -Wextra -std=gnu99 -lrt -pthread 

.PHONY: all clean

all: peter.out student.out

shared.o: shared.c shared.h
	gcc $(CFLAGS) -c -o shared.o shared.c

peter.out: peter.c shared.h shared.o
	gcc $(CFLAGS) peter.c shared.o -o peter.out

student.out: student.c shared.h shared.o
	gcc $(CFLAGS) student.c shared.o -o student.out

clean:
	rm -f peter.out
	rm -f student.out
	rm -f shared.o
