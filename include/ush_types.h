#ifndef USH_TYPES_H
#define USH_TYPES_H


#define ERROR_STREAM stderr
#define INPUT_STREAM stdin
#define PRINT_STREAM stdout


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


#endif
