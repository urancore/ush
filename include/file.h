#ifndef USH_FILE_H
#define USH_FILE_H

// 0 - exists
int file_is_exists(const char *filename);

void ush_create_file(const char *filename);
void ush_fappend(const char *filename, const char *format, ...);
void ush_fwrite(const char *filename, const char *format, ...);

#endif
