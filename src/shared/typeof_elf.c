/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** typeof_elf.c
*/

#include "../../include/shared.h"
#include "elf.h"

static void typeof_filename_elf64(const unsigned char *restrict buffer,
    const size_t size,
    const char *restrict filename,
    const char *restrict pgrm)
{
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)buffer;

    if (ehdr->e_shoff > size
        || ehdr->e_shoff + (
        ehdr->e_shnum * sizeof(Elf64_Ehdr)) > size) {
        raise_error("%s: %s: file format not recognized", pgrm, filename);
    }
    if (ehdr->e_type != ET_EXEC
        && ehdr->e_type != ET_DYN
        && ehdr->e_type != ET_REL) {
        raise_error("%s: %s: unsupported file type", pgrm, filename);
    }
}

static void typeof_filename_elf32(const unsigned char *restrict buffer,
    const size_t size,
    const char *restrict filename,
    const char *restrict pgrm)
{
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *)buffer;

    if (ehdr->e_shoff > size
        || ehdr->e_shoff + (
        ehdr->e_shnum * sizeof(Elf32_Ehdr)) > size) {
        raise_error("%s: %s: file format not recognized", pgrm, filename);
    }
    if (ehdr->e_type != ET_EXEC
        && ehdr->e_type != ET_DYN
        && ehdr->e_type != ET_REL) {
        raise_error("%s: %s: unsupported file type", pgrm, filename);
    }
}

_Bool typeof_elf_verify(const unsigned char *restrict buffer,
    const size_t size,
    const char *restrict filename,
    const char *restrict pgrm)
{
    const unsigned char *e_ident = buffer;
    const _Bool is64 = (e_ident[EI_CLASS] == ELFCLASS64);

    if (!is_valid_elf(e_ident)) {
        raise_error("%s: %s: file format not recognized", pgrm, filename);
    }
    if (is64) {
        typeof_filename_elf64(buffer, size, filename, pgrm);
        return is64;
    }
    typeof_filename_elf32(buffer, size, filename, pgrm);
    return is64;
}
