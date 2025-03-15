/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** init.c
*/

#include "nm.h"
#include <stdlib.h>

static void nm_ctor(nm_t *nm, const char *restrict filename)
{
    typeof_filename(filename, NM_PRGRM);
    try_open_file(filename, &nm->file.buffer, &nm->file.size);
}

static void nm_dtor(nm_t *nm)
{
    free(nm->file.buffer);
}

static void nm_verify(nm_t *nm, const char *restrict filename)
{
    nm->is_64 = typeof_elf_verify(
        nm->file.buffer,
        nm->file.size,
        filename,
        NM_PRGRM);
}

void init_nm(const char *restrict filename)
{
    nm_t nm = {0};

    nm_ctor(&nm, filename);
    nm_verify(&nm, filename);
    if (nm.is_64) {
        nm_elf_64(&nm, filename);
    } else {
        nm_elf_32(&nm, filename);
    }
    nm_dtor(&nm);
}
