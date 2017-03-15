#include "btree.h"

#include <assert.h>

int main() {
	btree *ta = btree_create();

	assert(btree_size(ta) == 0);
	assert(btree_contains(ta, 4) == false);
	btree_print(ta, stdout);

	btree_insert(ta, 4);
	btree_insert(ta, 7);
	btree_insert(ta, 3);

	assert(btree_size(ta) == 3);
	assert(btree_contains(ta, 4) == true);
	assert(btree_minimum(ta) == 3);
	assert(btree_maximum(ta) == 7);
	btree_print(ta, stdout);

	btree_remove(ta, 4);

	assert(btree_size(ta) == 2);
	assert(btree_contains(ta, 4) == false);
	assert(btree_minimum(ta) == 3);
	assert(btree_maximum(ta) == 7);
	btree_print(ta, stdout);

	btree_insert(ta, 2);
	btree_insert(ta, -3);
	btree_insert(ta, 6);
	btree_insert(ta, 9);

	assert(btree_size(ta) == 6);
	btree_print(ta, stdout);

	btree_remove(ta, 6);

	assert(btree_size(ta) == 5);
	assert(btree_contains(ta, 6) == false);
	btree_print(ta, stdout);

	btree_insert(ta, 5);
	btree_insert(ta, 5);

	assert(btree_size(ta) == 6);
	assert(btree_contains(ta, 5) == true);
	btree_print(ta, stdout);

	btree_insert(ta, 6);
	btree_insert(ta, 4);
	btree_remove(ta, 7);
	btree_remove(ta, 7);

	assert(btree_size(ta) == 7);
	assert(btree_contains(ta, 7) == false);
	btree_print(ta, stdout);

	btree_destroy(ta);
}