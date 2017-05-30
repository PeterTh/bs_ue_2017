# Exercise Sheet 7

In this exercise sheet you will use POSIX threads and test out different methods for mutual exclusion and synchronization.
The deadline for this exercise is June 7th.


# Task 1

Write a program which spawns 10 threads. 

* Each thread waits for a random time between 0 and 2 seconds, then creates a file called `threadN.txt` (where `N` is the thread number between 0 and 9) and writes its thread id (returned by `gettid`) to this file. Ensure that the file is closed in case a thread opens it and is subsequently interrupted (study the `pthread_cleanup` family of functions).
* After spawning all threads, for each thread the main program decides whether to randomly cancel the thread, with a chance of cancellation of 50%.
* Afterwards, the main program waits for all threads to exit.

# Task 2

In this exercise you will implement a single producer multiple consumer pattern. 

Your program should spawn 4 threads, the *consumers*, which all try to read elements from a queue (you can use e.g. the C++ `std::queue`). Queued elements are of type `unsigned`.

* When a consumer thread successfully reads an element, it adds it to its local `sum`. When the element is 0, it prints out the sum and exits.

* The main thread acts as the *producer*. After spawning all 4 consumers, it feeds 100000 `1` entries into the queue, followed by 4 `0`.

Access to the queue should be protected by using the `pthread_mutex` facilities. 

# Task 3

Create two additional versions of the program implemented in Task 2, one which uses `pthread_spinlock` to protect queue access, and one which uses pthread condition variables to signal the availability of new elements.

# Task 4

Compare the three versions of the program developed in Task 2 and Task 3. What are the advantages and disadvantages of each method?
Use `/usr/bin/time -v` to evaluate the performance of each version and interpret the results.
