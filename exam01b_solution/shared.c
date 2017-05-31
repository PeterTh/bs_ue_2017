#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "shared.h"

int xerror(const char* msg) {
	perror(msg);
	return EXIT_FAILURE;
}

static void print_usage(const char* prog_name) {
	fprintf(stderr, "Usage: %s <int>\n", prog_name);
}

bool parse_int_arg(int argc, char** argv, int* out) {
	if (argc != 2) {
		print_usage(argv[0]);
		return false;
	}
	*out = atoi(argv[1]);
	return true;
}
