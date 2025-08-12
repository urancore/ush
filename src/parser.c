#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/parser.h"
#include "../include/shell.h"



char **ush_split(char *str, char delim, int *argc)
{
	int capacity = 2;
	char **array = malloc(capacity * sizeof(char *));
	if (array == NULL) {
		ush_error("src/parser.split malloc");
		return NULL;
	}

	int len = strlen(str);
	char word[len + 1];
	int j = 0;
	*argc = 0;

	for (int i = 0; i <= len; i++) {
		if (str[i] != delim && str[i] != '\0') {
			word[j++] = str[i];
		} else if  (j > 0) {
			word[j] = '\0';
			if (*argc >= capacity) {
				capacity *= 2;
				array = realloc(array, capacity * sizeof(char *));
				if (array == NULL) {
					ush_error("src/parser.split realloc failed");
					return NULL;
				}
			}
			array[*argc] = word;
			(*argc)++;
			j = 0;
		}
	}
	return array;
}
