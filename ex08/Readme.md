# Exercise Sheet 8

In this exercise sheet you will use POSIX threads and perform different types of memory management within them.


# Task 1

Create an application `membench T N S` which launches a configurable (program launch parameter `T`) number of threads. 
Each thread should perform a given number of memory allocations and deallocations (`N`) of a given size in bytes (`S`).

For example
```
./membench 8 10000 1024
```
would launch 8 threads, each of which performs 10000 allocations of 1 kiB each.


# Task 2

Implement a naive *best fit* memory allocator (see lecture slides) and use it in your application. 
The allocator should provide its own versions of the `malloc` and `free` functions.

Create 2 versions, one which uses a global allocator (which of course needs to be locked when used), and 
one which uses a local allocator for each thread. 

Compare their performance in "membench", with a few different numbers of threads and allocation sizes, 
and a number of allocations/deallocations that gives a reasonable total runtime (more than a second and less than a minute).


# Task 3

Implement a *free list* allocator (see lecture slides) which uses free lists for requests up to 2^16 Bytes 
(one separate free list for each power of 2). 
Again, create one version that uses a global set of freelists with access locks, 
and another which uses a separate allocator for each thread. Compare their performance as in task 2.

# Task 4

Use `membench` to compare all 4 of your allocators as well as the default allocator on the system and Google's *tcmalloc*.
Perform your comparisons acrosss 1, 2, 4 and 8 threads, and for allocations of 2^N Bytes for N=4...22.
