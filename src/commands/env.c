#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../include/commands/env.h"
#include "../../include/ush_types.h"
#include "../../include/shell.h"
#include "../../include/file.h"

const char *ush_getenv(const char *filename, const char *key)
{
	const int max_line_len = MAX_ENV_KEY_LEN+MAX_ENV_VALUE_LEN;
	char *value = malloc(max_line_len);
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		ush_error("getenv: error opening file\n");
		return NULL;
	}

	char line[max_line_len];
	while (fgets(line, sizeof(line), file)) {
		line[strcspn(line, "\r\n")] = '\0';

		char *equals = strchr(line, '=');
		if (!equals) continue;

		*equals = '\0';
		char *file_key = line;
		char *file_value = equals + 1;

		if (strcmp(file_key, key) == 0) {
			strncpy(value, file_value, max_line_len);
			fclose(file);
			return value;
		}
	}

	fclose(file);
	return NULL;
}


void env_call_func(USH_Command *cmd)
{
	if (cmd->argc < 2) {
		return;
	}
	char *filename = DEFAULT_ENV_FILE;

	USH_Env env = {0};
	char *arg = cmd->args[1];

	char *eq = strchr(arg, '=');
	if (!eq) {
		const char *value = ush_getenv(filename, arg);
		ush_printf("%s\n", value);
		return;
	}

	int key_len = eq - arg;
	if (key_len > MAX_ENV_KEY_LEN) {
		ush_error("env: %s\n", "name is too long");
		return;
	}
	strncat(env.key, arg, key_len);
	env.key[key_len] = '\0';
	char *value = eq + 1;
	if (strlen(value) >= MAX_ENV_VALUE_LEN) {
		ush_error("env: value is too long\n");
		return;
	}
	strncpy(env.value, value, MAX_ENV_VALUE_LEN - 1);
	env.value[MAX_ENV_VALUE_LEN - 1] = '\0';

	if (file_is_exists(filename)) {
		ush_fappend(filename, "%s=%s\n", env.key, env.value);
	} else {
		ush_fwrite(filename, "%s=%s\n", env.key, env.value);
	}

	return;
}
