#include <stdlib.h>

#include "../../include/ush_types.h"
#include "../../include/shell.h"


void echo_call_func(USH_Command *cmd)
{
	int argc = cmd->argc;
	char **args = cmd->args;

	for (int i = 1; i < argc; i++) {
		ush_printf("%s", args[i]);
		if (i < argc - 1) {
			ush_printf(" ");
		}
	}
	ush_printf("\n");
}
