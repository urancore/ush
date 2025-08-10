#include <stdlib.h>

#include "command_loader.h"

USH_Command command_list[] = {
	{
		.name = "echo",
		.call = &echo_call_func,
		.cleanup = &echo_cleanup_func,
	},
	{
		.name = NULL // end
	}
};

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


void echo_cleanup_func(USH_Command *cmd)
{
	int argc = cmd->argc;
	char **args = cmd->args;

	for (int i = 1; i < argc; i++) {
		free(args[i]);
	}
}
