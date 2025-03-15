/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** nm_elf32.c
*/

#include "nm.h"
#include <stdlib.h>

static void nm_elf_32_show_valid(
    nm_t *nm, Elf32_Shdr *shdr, Elf32_Sym *sym32, size_t offset)
{
    const char *show = get_sym_name(nm->file.buffer, offset, sym32->st_name);

    if (strcmp("", show) != 0 && sym32->st_info != STT_FILE) {
        nm->symbols = realloc(nm->symbols, (
            nm->symbol_count + 1) * sizeof(symbol_t));
        nm->symbols[nm->symbol_count] = (symbol_t){
            .sym = (Elf64_Sym *)sym32,
            .name = show,
            .value = sym32->st_value,
            .type = nm_types_elf32(shdr, sym32)
        };
        nm->symbol_count++;
    }
}

static void nm_elf_32_show_sym(nm_t *nm, Elf32_Shdr *shdr, size_t i)
{
    Elf32_Sym *sym32 = (Elf32_Sym *)(nm->file.buffer + shdr[i].sh_offset);
    size_t offset = ELF_OFFSET(shdr, i);
    const size_t size = ELF_SHDR_SIZE(shdr[i]);

    for (size_t unused = 0; unused < size; ++unused) {
        nm_elf_32_show_valid(nm, shdr, sym32, offset);
        sym32++;
    }
}

static void nm_elf_32_is_symtab(nm_t *nm, Elf32_Shdr *shdr, size_t i)
{
    if (shdr[i].sh_type == SHT_SYMTAB) {
        nm_elf_32_show_sym(nm, shdr, i);
    }
}

static void nm_show_symbol32(nm_t *nm, Elf32_Shdr *shdr)
{
    Elf32_Sym *sym = NULL;

    for (size_t i = 0; i < nm->symbol_count; ++i) {
        sym = (Elf32_Sym *)nm->symbols[i].sym;
        if (sym->st_value == 0 && sym->st_shndx == SHN_UNDEF) {
            GLOBAL_SHOW_UNKNOWN();
        } else {
            GLOBAL_SHOW_SYM_VALUE(sym);
        }
        console_log("%c %s\n", nm_types_elf32(shdr, sym), nm->symbols[i].name);
    }
}

void nm_elf_32(nm_t *nm, const char *restrict filename)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr *)nm->file.buffer;
    Elf32_Shdr *shdr = (Elf32_Shdr *)(nm->file.buffer + elf->e_shoff);

    nm->symbols = NULL;
    nm->symbol_count = 0;
    for (size_t i = 0; i < elf->e_shnum; ++i) {
        nm_elf_32_is_symtab(nm, shdr, i);
    }
    SYMBOL_NULL(nm->symbol_count, filename);
    qsort(nm->symbols, nm->symbol_count,
        sizeof(symbol_t), nm_compare_symbols);
    nm_show_symbol32(nm, shdr);
    free(nm->symbols);
}
