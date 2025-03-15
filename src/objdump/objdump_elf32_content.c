/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** objdump_elf32_content.c
*/

#include "objdump.h"
#include "show.h"

static void show_section_hex32(
    const Elf32_Shdr *sec, const unsigned char *buffer, size_t start)
{
    size_t i = start;
    size_t max_index = start + 16;

    if (max_index > sec->sh_size)
        max_index = sec->sh_size;
    while (i < max_index) {
        show_section_hexadecimal(buffer[sec->sh_offset + i], FMT_02X);
        ++i;
        if (i < max_index && ((i - start) % 4 == 0))
            console_log(" ");
    }
    show_section_padding(i - start);
    console_log("  ");
}

static void show_section_ascii32(
    const Elf32_Shdr *sec, const unsigned char *buffer,
    const size_t start_offset, const size_t count)
{
    size_t i = start_offset;
    size_t max_index = start_offset + count;

    if (max_index > sec->sh_size)
        max_index = sec->sh_size;
    for (; i < max_index; i++) {
        show_section_character(buffer[sec->sh_offset + i]);
    }
}

static void show_section_remaining32(
    const Elf32_Shdr *sec, Elf32_Addr addr, const unsigned char *buffer)
{
    const size_t remaining = sec->sh_size & 0x0F;
    size_t last_start = 0;

    if (remaining != 0) {
        last_start = sec->sh_size & ~(size_t)0x0F;
        show_section_hexadecimal(addr, FMT_04LX);
        show_section_hex32(sec, buffer, last_start);
        show_section_ascii32(sec, buffer, last_start, remaining);
        for (size_t i = remaining; i < 16; i++) {
            console_log(" ");
        }
        console_log("%c", ENDLINE);
    }
}

void show_elf32_sections_content(const Elf32_Shdr *sec, const objdump_t *obj)
{
    Elf32_Addr addr = sec->sh_addr;
    const unsigned char *buffer = obj->file.buffer;
    size_t i = 0;
    size_t full_blocks = sec->sh_size & ~(size_t)0x0F;

    while (i < full_blocks) {
        show_section_hexadecimal(addr, FMT_04LX);
        addr += 16;
        show_section_hex32(sec, buffer, i);
        show_section_ascii32(sec, buffer, i, 16);
        console_log("%c", ENDLINE);
        i += 16;
    }
    show_section_remaining32(sec, addr, buffer);
}
