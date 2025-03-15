/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** init.c
*/

#include "objdump.h"
#include <stdlib.h>

static void objdump_ctor(objdump_t *obj, const char *restrict filename)
{
    typeof_filename(filename, OBJ_PRGRM);
    try_open_file(filename, &obj->file.buffer, &obj->file.size);
}

static void objdump_dtor(objdump_t *obj)
{
    free(obj->file.buffer);
}

static void objdump_verify(objdump_t *obj, const char *restrict filename)
{
    obj->is_64 = typeof_elf_verify(
        obj->file.buffer,
        obj->file.size,
        filename,
        OBJ_PRGRM);
}

void init_objdump(const char *restrict filename)
{
    objdump_t obj = {0};

    objdump_ctor(&obj, filename);
    objdump_verify(&obj, filename);
    if (obj.is_64) {
        objdump_elf64(&obj, filename);
    } else {
        objdump_elf32(&obj, filename);
    }
    objdump_dtor(&obj);
}
