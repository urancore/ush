#include <stdio.h>
#include <string.h>
#include "../../include/ush_api.h"

void print_help() {
	ush_printf("Usage: hello [name]\n");
	ush_printf("Prints a greeting message to the specified name.\n\n");
	ush_printf("Options:\n");
	ush_printf("  -h        Show this help message.\n");
}

int main(int argc, char **args) {
	if (argc >= 2) {
		if (strcmp(args[1], "-h") == 0) {
		print_help();
		return 0;
		}

		ush_printf("Hello, %s!\n", args[1]);
	} else {
		ush_printf("Hello, world!\n");
	}

	return 0;
}
