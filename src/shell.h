#ifndef USH_SHELL_H
#define USH_SHELL_H

#define MAX_COMMAND_LEN 1024

typedef struct USH_Command USH_Command;

typedef void (ush_call_func)(USH_Command *cmd);
typedef void (ush_cleanup_func)(USH_Command *cmd);

typedef enum {
	USH_CMD_EXTERNAL,
	USH_CMD_BUILTIN
} USH_CommandType;


struct USH_Command {
	char *name;
	char **args;
	int argc;

	ush_call_func *call;
	ush_cleanup_func *cleanup;

	USH_CommandType is_builtin;
};


void ush_printf(const char *format, ...);
void ush_println(const char *str);

void ush_error(const char *format, ...); // func add [ush error] to error mesagges
void ush_custom_error(const char *format, ...);

char *ush_input();

void ush_prompt(const char *prompt);

void execute_command(USH_Command *cmd);

#endif
