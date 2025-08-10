#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ush_types.h"
#include "../include/shell.h"
#include "./commands/loader.h"


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

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
			cmd->call = command_list[i].call;
			cmd->cleanup = command_list[i].cleanup;
			cmd->is_builtin = USH_CMD_BUILTIN;

			cmd->call(cmd);
			return;
		}
	}

#ifdef _WIN32
	size_t cmd_len = 0;
	for (int i = 0; i < cmd->argc; ++i) {
		cmd_len += strlen(cmd->args[i]) + 3;
	}

	char *cmdline = malloc(cmd_len + 1);
	if (!cmdline) {
		ush_error("shell.execute_command malloc failed\n");
		return;
	}

	cmdline[0] = '\0';
	for (int i = 0; i < cmd->argc; ++i) {
		strcat(cmdline, "\"");
		strcat(cmdline, cmd->args[i]);
		strcat(cmdline, "\" ");
	}

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};
	si.cb = sizeof(si);

	BOOL success = CreateProcessA(
		NULL,
		cmdline,
		NULL, NULL,
		FALSE,
		0,
		NULL, NULL,
		&si, &pi
	);

	if (!success) {
		ush_error("Command not found: %s\n", cmd->name);
		free(cmdline);
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	free(cmdline);

#else
	pid_t pid = fork();

	if (pid < 0) {
		ush_error("fork failed\n");
		return;
	}

	if (pid == 0) {
		// child
		cmd->args[cmd->argc] = NULL;

		execvp(cmd->name, cmd->args);
		ush_error("Command not found: %s\n", cmd->name);
		exit(EXIT_FAILURE);
	} else {
		// parent
		int status;
		waitpid(pid, &status, 0);
	}
#endif
}


// TODO: add format for prompt (config)
void ush_prompt(const char *str)
{
	ush_printf(str);
}
