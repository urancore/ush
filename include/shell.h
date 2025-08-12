#ifndef USH_SHELL_H
#define USH_SHELL_H

#include "ush_types.h"

#define MAX_COMMAND_LEN 1024


void ush_printf(const char *format, ...);
void ush_println(const char *str);

void ush_error(const char *format, ...); // func add [ush error] to error mesagges
void ush_custom_error(const char *format, ...);

char *ush_input();

void ush_prompt(const char *str);

void execute_command(USH_Command *cmd);

#endif
