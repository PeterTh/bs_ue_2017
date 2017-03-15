#ifndef _BTREE_H_GUARD_
#define _BTREE_H_GUARD_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/// Stores a binary, sorted tree of integers, in which each element may only occur once
struct btree;
typedef struct btree btree;

/// A single node in the binary tree
struct btree_node;
typedef struct btree_node btree_node;

/// Creates and returns a new binary tree
/// must be deallocated by btree_destroy
btree* btree_create();
/// Destroys and deallocates all memory for the given tree 't'
void btree_destroy(btree* t);

/// Inserts the given number 'd' into tree 't'
/// if the number is already in 't', no changes are made
void btree_insert(btree* t, int d);
/// Removes the given number 'd' from tree 't' 
void btree_remove(btree* t, int d);

/// Returns the smallest number in tree 't'
int btree_minimum(const btree* t);
/// Returns the largest number in tree 't'
int btree_maximum(const btree* t);

/// Returns true if the given tree 't' contains 'd', false otherwise
bool btree_contains(const btree* t, int d);

/// Returns the number of elements of the given btree 't'
/// NOTE: should complete in O(1) time
size_t btree_size(const btree* t);

/// Prints the given btree 't' to the supplied output stream 'out'
/// output format: ([LEFT], VAL, [RIGHT]) : [SIZE]
/// example empty: ( NIL ) : 0
/// example 3,4,7 in a balanced tree: ((3), 4, (7)) : 3
void btree_print(const btree* t, FILE* out);

#endif // _BTREE_H_GUARD_
