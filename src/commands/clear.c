#include <stdlib.h>

#include "../../include/ush_types.h"
#include "../../include/shell.h"


void clear_call_func(USH_Command *cmd)
{
	(void)cmd;
	ush_printf("\033[H\033[J");
}
