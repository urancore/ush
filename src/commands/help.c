#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#include "loader.h"
#include "../../include/ush_types.h"

void help_call_func(USH_Command *cmd)
{
	(void)cmd;
	for (int i = 0; command_list[i].name != NULL; i++) {
		ush_printf("%s\n", command_list[i].name);
	}
	return;
}
