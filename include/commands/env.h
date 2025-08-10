#ifndef USH_BUILTIN_CMD_ENV_H
#define USH_BUILTIN_CMD_ENV_H

#include "../../include/ush_types.h"

#define DEFAULT_ENV_FILE ".env"

#define MAX_ENV_KEY_LEN 256
#define MAX_ENV_VALUE_LEN 256

typedef struct
{
	char key[MAX_ENV_KEY_LEN];
	char value[MAX_ENV_VALUE_LEN];
} USH_Env;


void env_call_func(USH_Command *cmd);

#endif
