/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** error.c
*/

#include "../../include/macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void raise_error(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    fflush(stderr);
    exit(ERROR_CODE);
}
