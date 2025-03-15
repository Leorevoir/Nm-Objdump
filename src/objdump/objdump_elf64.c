/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** objdump_elf64.c
*/

#include "objdump.h"
#include "sections.h"

static void objdump_elf64_header(
    const Elf64_Ehdr *header, const char *restrict filename)
{
    console_log("\n%s:     file format elf64-x86-64\n", filename);
    console_log("architecture: %s, ", get_architecture(header->e_machine));
    console_log("flags 0x%08x:\n", get_flags(header->e_type));
    console_log("%s\n", get_flags_to_str(header->e_type));
    console_log("start address 0x%016lx\n\n", header->e_entry);
}

static void objdump_show_elf64sections(const char *sections,
    const Elf64_Shdr *sec, const size_t i, const objdump_t *obj)
{
    const char *name = get_section_name(sections, sec, i);

    if (!is_ignored_section(name)) {
        show_sections_name(name);
        show_elf64_sections_content(&sec[i], obj);
    }
}

static void objdump_elf64_sections(
    const objdump_t *obj, const Elf64_Ehdr *ehdr, const Elf64_Shdr *sec)
{
    const Elf64_Shdr *shdr = &sec[ehdr->e_shstrndx];
    const char *sections = (char *)(obj->file.buffer + shdr->sh_offset);

    for (size_t i = 1; i < ehdr->e_shnum; ++i) {
        objdump_show_elf64sections(sections, sec, i, obj);
    }
}

void objdump_elf64(objdump_t *obj, const char *restrict filename)
{
    const Elf64_Ehdr *ehdr = (Elf64_Ehdr *)obj->file.buffer;
    const Elf64_Shdr *sec = (Elf64_Shdr *)(obj->file.buffer + ehdr->e_shoff);

    objdump_elf64_header(ehdr, filename);
    objdump_elf64_sections(obj, ehdr, sec);
}
