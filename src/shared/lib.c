/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** lib.c
*/

#include "../../include/shared.h"
#include <sys/stat.h>
#include <stdarg.h>

void console_log(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}

void typeof_filename(const char *restrict filename, const char *pgrm)
{
    struct stat file_stat;

    if (stat(filename, &file_stat) == -1) {
        raise_error("%s: '%s': No such file", pgrm, filename);
    }
    if (S_ISDIR(file_stat.st_mode)) {
        raise_error("%s: Warning: '%s' is a directory", pgrm, filename);
    }
    if (S_ISREG(file_stat.st_mode)) {
        return;
    }
    raise_error("%s: %s file format no recognized", pgrm, filename);
}
