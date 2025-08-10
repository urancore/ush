#include <stdlib.h>

#include "../../include/ush_types.h"


void exit_call_func(USH_Command *cmd)
{
	if (cmd->cleanup) {
		cmd->cleanup(cmd);
	}
	free(cmd->name);

	exit(0);
}
