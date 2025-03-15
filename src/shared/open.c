/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** open.c
*/

#include "../../include/shared.h"
#include <stdlib.h>

static size_t get_file_size(FILE *file)
{
    long size = 0;

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    return (size_t)size;
}

static void try_read_file(FILE *file, unsigned char **ptr, size_t *br)
{
    size_t size = get_file_size(file);
    unsigned char *buff = malloc(size);

    if (buff == NULL) {
        fclose(file);
        raise_error("try_read_file: malloc failed");
    }
    *br = fread(buff, 1, size, file);
    if (*br != size) {
        free(buff);
        fclose(file);
        raise_error("try_read_file: br != size");
    }
    *ptr = buff;
}

void try_open_file(const char *restrict fnm, unsigned char **ptr, size_t *br)
{
    FILE *file = fopen(fnm, "rb");

    if (file == NULL) {
        raise_error("try_open_file: failed to open");
    }
    try_read_file(file, ptr, br);
    fclose(file);
}
