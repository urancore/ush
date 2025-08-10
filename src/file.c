#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "../include/file.h"
#include "../include/shell.h"

int file_is_exists(const char *filename) // 0 - exists
{
	if (access(filename, F_OK) != 0) {
		return 0;
	}
	return 1;
}

void ush_create_file(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (file_is_exists(filename) == 0) {
		fp = fopen(filename, "w");
		fclose(fp);
		return;
	}

	fclose(fp);
	return;
}

void ush_fappend(const char *filename, const char *format, ...)
{
	FILE *fp;

	fp = fopen(filename, "a");
	if (fp == NULL) {
		ush_error("file.ush_fappend error opening file");
		return;
	}

	va_list args;
	va_start(args, format);
	vfprintf(fp, format, args);
	va_end(args);

	fclose(fp);
	return;
}

void ush_fwrite(const char *filename, const char *format, ...)
{
	FILE *fp;

	fp = fopen(filename, "w");
	if (fp == NULL) {
		ush_error("file.ush_fwrite error opening file");
		return;
	}

	va_list args;
	va_start(args, format);
	vfprintf(fp, format, args);
	va_end(args);

	fclose(fp);
	return;
}
