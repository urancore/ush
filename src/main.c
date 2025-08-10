#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "parser.h"


int main()
{
	while (1) {
		ush_prompt("ush $ ");
		char *cmd = ush_input();
		if (!cmd) continue;

		int argc;
		char **args = ush_split(cmd, ' ', &argc);
		if (argc == 0) {
			free(cmd);
			continue;
		}

		USH_Command command = {0};
		command.name = strdup(args[0]);
		command.argc = argc;
		command.args = args;

		execute_command(&command);

		if (command.cleanup) {
			command.cleanup(&command);
		}

		free(command.name);
		free(cmd);
	}
	return 0;
}
