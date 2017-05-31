# Exam 1b solution

Running `./test.sh` builds both programs, runs the test case, and cleans up after itself.

**Notes:**

 * Shared functionality is provided in `shared.h` and `shared.c` 
 * For synchronization, a combination of a blocking pipe and a single semaphore is used
 * The process works like this: 
    1. Peter runs up to `fscanf`
    2. Some student acquires the semaphore
    3. The student writes first to shared memory and then to the pipe
    4. Peter reads from the pipe and from shared memory and does its processing
    5. Then Peter frees up the sema, allowing a new student to submit their work (continuing from 2)
    
This program is adapted from the solution submitted by Dominik Egretzberger with only minor changes.