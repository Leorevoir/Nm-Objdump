/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** show.h
*/

#ifndef OBJDUMP_SECTIONS_SHOW_H
    #define OBJDUMP_SECTIONS_SHOW_H

    #include "../../include/shared.h"

    #define ENDLINE '\n'
    #define SPACE ' '

    #define FMT_04LX 1
    #define FMT_02X 0

/*
 * substract lower bound (32) from c to start from 0
 * & 0xFF ensure we are looking at the lowest byte
 * then normalise value <= (126 - 32 -> 94)
 */
static inline void show_section_character(const unsigned char c)
{
    if (((c - 32) & 0xFF) <= (94)) {
        console_log("%c", c);
        return;
    }
    console_log(".");
}

static inline _Bool maybe_show(const size_t i, const size_t mod, const char c)
{
    if ((i & mod) == 0) {
        console_log("%c", c);
        return true;
    }
    return false;
}

static inline void show_until(size_t i, const size_t mod, const char c)
{
    while ((i & mod) != 0) {
        console_log("%c", c);
        ++i;
    }
}

static inline void show_section_hexadecimal(
    const Elf64_Addr c, const uint8_t lx)
{
    switch (lx) {
        case FMT_02X:
            console_log("%02x", c);
            break;
        case FMT_04LX:
            console_log(" %04lx ", c);
            break;
        default:
            break;
    }
}

/*
 * one extra space after every 4 bytes except after the last block group
 */
static inline void show_section_padding(size_t n)
{
    size_t printed_width = n * 2;
    size_t pad = 0;

    if (n > 0) {
        printed_width += (n - 1) / 4;
    }
    pad = (printed_width < 35) ? 35 - printed_width : 0;
    for (size_t j = 0; j < pad; j++) {
        console_log(" ");
    }
}

#endif /* OBJDUMP_SECTIONS_SHOW_H */
