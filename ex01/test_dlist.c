#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

int main(void) {
	DList* mylist = DList_new();
	assert(mylist != NULL);

	DList_print(mylist); printf("\n");
	printf("is mylist empty: %s\n", DList_is_empty(mylist) ? "yes" : "no");

	DList_append(mylist, 5);
	DList_print(mylist); printf("\n");
	printf("is mylist empty: %s\n", DList_is_empty(mylist) ? "yes" : "no");

	DList_append(mylist, 2);
	DList_append(mylist, 8);
	DList_prepend(mylist, 1);
	DList_prepend(mylist, 3);
	DList_append(mylist, 7);
	DList_prepend(mylist, 8);
	DList_print(mylist); printf("\n");
	printf("length of mylist: %ld\n", DList_length(mylist));

	{
		int value;
		DList_get(mylist, 3, &value); printf("%d\n", value);
		DList_get(mylist, 1, &value); printf("%d\n", value);
		DList_get(mylist, 2, &value); printf("%d\n", value);
		DList_get(mylist, 3, &value); printf("%d\n", value);
	}

	DList_insert(mylist, 0, 6);
	DList_insert(mylist, DList_length(mylist), 10);
	DList_insert(mylist, 3, 4);
	DList_print(mylist); printf("\n");;

	{
		int value;
		DList_remove(mylist, 1, &value); printf("removed value: %d\n");
		DList_remove(mylist, 7, NULL);
		DList_print(mylist); printf("\n");
	}

	DList_reverse(mylist);
	DList_print(mylist); printf("\n");

	printf("7 is %sin mylist\n", DList_contains(mylist, 7) ? "" : "not ");
	printf("8 is %sin mylist\n", DList_contains(mylist, 8) ? "" : "not ");

	DList_insert(mylist, 5, 5);
	DList_append(mylist, 10);
	DList_print(mylist); printf("\n");
	{
		size_t index;
		DList_find(mylist, 5, &index);         printf("first 5 at index %ld\n", index);
		DList_find_from(mylist, 5, 4, &index); printf("first 5 at index %ld\n", index);
		DList_find_last(mylist, 10, &index);   printf("first 5 at index %ld\n", index);
	}

	DList_sort(mylist);
	DList_print(mylist); printf("\n");

	return EXIT_SUCCESS;
}
