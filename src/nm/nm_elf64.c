/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** nm_elf64.c
*/

#include "nm.h"
#include <stdlib.h>

static void nm_elf_64_show_valid(
    nm_t *nm, Elf64_Shdr *shdr, Elf64_Sym *sym64, size_t offset)
{
    const char *show = get_sym_name(nm->file.buffer, offset, sym64->st_name);

    if (strcmp("", show) != 0 && sym64->st_info != STT_FILE) {
        nm->symbols = realloc(nm->symbols, (
            nm->symbol_count + 1) * sizeof(symbol_t));
        nm->symbols[nm->symbol_count] = (symbol_t){
            .sym = sym64,
            .name = show,
            .value = sym64->st_value,
            .type = nm_types_elf64(shdr, sym64)
        };
        nm->symbol_count++;
    }
}

static void nm_elf_64_show_sym(nm_t *nm, Elf64_Shdr *shdr, size_t i)
{
    Elf64_Sym *sym64 = (Elf64_Sym *)(nm->file.buffer + shdr[i].sh_offset);
    size_t offset = ELF_OFFSET(shdr, i);
    const size_t size = ELF_SHDR_SIZE(shdr[i]);

    for (size_t unused = 0; unused < size; ++unused) {
        nm_elf_64_show_valid(nm, shdr, sym64, offset);
        sym64++;
    }
}

static void nm_elf_64_is_symtab(nm_t *nm, Elf64_Shdr *shdr, size_t i)
{
    if (shdr[i].sh_type == SHT_SYMTAB) {
        nm_elf_64_show_sym(nm, shdr, i);
    }
}

static void nm_show_symbol64(nm_t *nm, Elf64_Shdr *shdr)
{
    Elf64_Sym *sym = NULL;

    for (size_t i = 0; i < nm->symbol_count; ++i) {
        sym = nm->symbols[i].sym;
        if (sym->st_value == 0 && sym->st_shndx == SHN_UNDEF) {
            GLOBAL_SHOW_UNKNOWN();
        } else {
            GLOBAL_SHOW_SYM_VALUE(sym);
        }
        console_log("%c %s\n", nm_types_elf64(shdr, sym), nm->symbols[i].name);
    }
}

void nm_elf_64(nm_t *nm, const char *restrict filename)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)nm->file.buffer;
    Elf64_Shdr *shdr = (Elf64_Shdr *)(nm->file.buffer + elf->e_shoff);

    nm->symbols = NULL;
    nm->symbol_count = 0;
    for (size_t i = 0; i < elf->e_shnum; ++i) {
        nm_elf_64_is_symtab(nm, shdr, i);
    }
    SYMBOL_NULL(nm->symbol_count, filename);
    qsort(nm->symbols, nm->symbol_count,
        sizeof(symbol_t), nm_compare_symbols);
    nm_show_symbol64(nm, shdr);
    free(nm->symbols);
}
