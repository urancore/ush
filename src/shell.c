#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "ush_types.h"
#include "shell.h"
#include "command_loader.h"

void ush_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void ush_println(const char *str)
{
	fprintf(PRINT_STREAM, "%s\n", str);
}

void ush_error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	fprintf(stderr, "[ush error] ");
	vfprintf(stderr, format, args);
	va_end(args);
}

void ush_custom_error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}

char *ush_input(void)
{

	char *buf = malloc(MAX_COMMAND_LEN);

	if (buf == NULL) {
		ush_error("src/shell.ush_input malloc");
		exit(EXIT_FAILURE);
	}

	if (fgets(buf, MAX_COMMAND_LEN, INPUT_STREAM) == NULL) {
		free(buf);
		return NULL;
	}

	size_t len = strlen(buf);
	if (len > 0 && buf[len - 1] == '\n') {
		buf[len - 1] = '\0';
	}

	return buf;
}

void execute_command(USH_Command *cmd)
{
	for (int i = 0; command_list[i].name != NULL; i++) {
		if (strcmp(command_list[i].name, cmd->name) == 0) {
			// Заполняем поля из command_list
			cmd->call = command_list[i].call;
			cmd->cleanup = command_list[i].cleanup;
			cmd->is_builtin = USH_CMD_BUILTIN;

			cmd->call(cmd);
			return;
		}
	}

	ush_error("Unknown command: %s\n", cmd->name);
}
// TODO: add format for prompt (config)
void ush_prompt(const char *prompt)
{
	ush_printf(prompt);
}
