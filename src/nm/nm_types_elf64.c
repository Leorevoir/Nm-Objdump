/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** nm_types_elf64.c
*/

#include "nm.h"

static char nm_get_special_symbols(
    const Elf64_Sym *sym64, const unsigned char bind, const unsigned char type)
{
    if (sym64->st_shndx == SHN_ABS)
        return 'A';
    if (sym64->st_shndx == SHN_COMMON)
        return 'C';
    if (bind == STB_GNU_UNIQUE)
        return 'u';
    if (bind == STB_WEAK) {
        if (type == STT_OBJECT)
            return (sym64->st_shndx == SHN_UNDEF) ? 'v' : 'V';
        return (sym64->st_shndx == SHN_UNDEF) ? 'w' : 'W';
    }
    if (sym64->st_shndx == SHN_UNDEF)
        return 'U';
    return '?';
}

static char nm_get_sec_symbol(const Elf64_Shdr *shdr, const Elf64_Sym *sym64)
{
    const Elf64_Shdr *sec = &shdr[sym64->st_shndx];

    if (sec->sh_type == SHT_NOBITS && (sec->sh_flags & SHF_ALLOC))
        return 'B';
    if (sec->sh_type == SHT_PROGBITS && (sec->sh_flags & SHF_ALLOC)) {
        if (sec->sh_flags & SHF_WRITE)
            return 'D';
        if (sec->sh_flags & SHF_EXECINSTR)
            return 'T';
        return 'R';
    }
    if (sec->sh_type == SHT_DYNAMIC)
        return 'D';
    if (sec->sh_type == SHT_NOTE)
        return 'R';
    if (sec->sh_type == SHT_INIT_ARRAY || sec->sh_type == SHT_FINI_ARRAY)
        return 'D';
    return '?';
}

char nm_types_elf64(const Elf64_Shdr *shdr, const Elf64_Sym *sym64)
{
    const unsigned char bind = ELF64_ST_BIND(sym64->st_info);
    const unsigned char type = ELF64_ST_TYPE(sym64->st_info);
    char flag = nm_get_special_symbols(sym64, bind, type);

    if (flag == '?')
        flag = nm_get_sec_symbol(shdr, sym64);
    if (bind == STB_LOCAL && flag != '?')
        flag = to_lower(flag);
    return flag;
}
