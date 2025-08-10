#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../../include/ush_types.h"
#include "../../include/shell.h"

void pwd_call_func(USH_Command *cmd)
{
	(void)cmd;
	char cwd[_MAX_PATH];
	getcwd(cwd, sizeof(cwd));
	ush_printf("%s\n", cwd);
}
