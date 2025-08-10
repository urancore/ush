#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include "../include/shell.h"
#include "../include/parser.h"


int main()
{
	while (1) {
		char cwd[_MAX_PATH];
		char prompt[1024];

		getcwd(cwd, sizeof(cwd));
		sprintf(prompt, "%s $ ", cwd);

		ush_prompt(prompt);
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
