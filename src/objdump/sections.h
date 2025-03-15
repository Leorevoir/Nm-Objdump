/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** sections.h
*/

#ifndef OBJDUMP_SECTIONS_H_
    #define OBJDUMP_SECTIONS_H_

    #include "../../include/shared.h"
    #include <string.h>
    #include <stdlib.h>

/*
 * bsearch need a sorted array
 */
static const char *ignored_sections[] = {
    "",
    ".bss",
    ".rela.debug_aranges",
    ".rela.debug_info",
    ".rela.debug_line",
    ".rela.eh_frame",
    ".rela.text",
    ".shstrtab",
    ".strtab",
    ".symtab",
    ".tbss",
    "__libc_freeres_ptrs"
};

static inline int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

/*
 * faster check
 */
static inline int is_ignored_section(const char *name)
{
    return bsearch(
        &name, ignored_sections,
        sizeof(ignored_sections) / sizeof(char *),
        sizeof(char *), compare_strings) != NULL;
}

static inline const char *get_section_name(
    const char *sections, const Elf64_Shdr *sec, const size_t i)
{
    return sections + sec[i].sh_name;
}

static inline void show_sections_name(const char *name)
{
    console_log("Contents of section %s:\n", name);
}

#endif /* OBJDUMP_SECTIONS_H_ */
