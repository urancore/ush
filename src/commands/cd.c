#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../../include/ush_types.h"
#include "../../include/shell.h"

void cd_call_func(USH_Command *cmd)
{
	if (cmd->argc < 2) {
		return;
	}

	if (chdir(cmd->args[1]) != 0) {
		ush_error("cd: no such file or directory: %s\n", cmd->args[1]);
	}
}
