#ifndef USH_COMMAND_LOADER_H
#define USH_COMMAND_LOADER_H

#include "shell.h"

extern USH_Command command_list[];


void echo_call_func(USH_Command *cmd);
void echo_cleanup_func(USH_Command *cmd);


#endif
