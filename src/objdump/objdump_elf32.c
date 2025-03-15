/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** objdump_elf32.c
*/

#include "objdump.h"
#include "sections.h"

static void objdump_elf32_header(
    const Elf32_Ehdr *header, const char *restrict filename)
{
    console_log("\n%s:     file format elf32-i386\n", filename);
    console_log("architecture: %s, ", get_architecture(header->e_machine));
    console_log("flags 0x%08x:\n", get_flags(header->e_type));
    console_log("%s\n", get_flags_to_str(header->e_type));
    console_log("start address 0x%016lx\n\n", header->e_entry);
}

static void objdump_show_elf32sections(const char *sections,
    const Elf32_Shdr *sec, const size_t i, const objdump_t *obj)
{
    const char *name = get_section_name(sections, (const Elf64_Shdr *)sec, i);

    if (!is_ignored_section(name)) {
        show_sections_name(name);
        show_elf32_sections_content(&sec[i], obj);
    }
}

static void objdump_elf32_sections(
    const objdump_t *obj, const Elf32_Ehdr *ehdr, const Elf32_Shdr *sec)
{
    const Elf32_Shdr *shdr = &sec[ehdr->e_shstrndx];
    const char *sections = (char *)(obj->file.buffer + shdr->sh_offset);

    for (size_t i = 1; i < ehdr->e_shnum; ++i) {
        objdump_show_elf32sections(sections, sec, i, obj);
    }
}

void objdump_elf32(objdump_t *obj, const char *restrict filename)
{
    const Elf32_Ehdr *ehdr = (Elf32_Ehdr *)obj->file.buffer;
    const Elf32_Shdr *sec = (Elf32_Shdr *)(obj->file.buffer + ehdr->e_shoff);

    objdump_elf32_header(ehdr, filename);
    objdump_elf32_sections(obj, ehdr, sec);
}
