#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "../../include/ush_types.h"
#include "../../include/shell.h"


void ls_call_func(USH_Command *cmd)
{
	(void)cmd;

	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");

	if (dir == NULL) {
		ush_error("ls: error opening dir\n");
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		printf("%15s\n", entry->d_name);
	}

	closedir(dir);
}
