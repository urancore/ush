#include <stdlib.h>
#include <stdio.h>

#include "loader.h"
#include "../../include/ush_types.h"

// commands
#include "../../include/commands/cd.h"
#include "../../include/commands/ls.h"
#include "../../include/commands/pwd.h"
#include "../../include/commands/echo.h"
#include "../../include/commands/clear.h"
#include "../../include/commands/exit.h"
#include "../../include/commands/help.h"
#include "../../include/commands/env.h"

void ush_default_cleanup_func(USH_Command *cmd)
{
	for (int i = 1; i < cmd->argc; i++) {
		free(cmd->args[i]);
	}
}

// builtin commands
USH_Command command_list[] = {
	{
		.name = "cd",
		.call = &cd_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "env",
		.call = &env_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "ls",
		.call = &ls_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "pwd",
		.call = &pwd_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "echo",
		.call = &echo_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "exit",
		.call = &exit_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "clear",
		.call = &clear_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = "help",
		.call = &help_call_func,
		.cleanup = &ush_default_cleanup_func,
		.is_builtin = USH_CMD_BUILTIN,
	},
	{
		.name = NULL // end
	}
};
