/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** fast.c
*/

#include <unistd.h>

char to_upper(const char c)
{
    return ((c & 0xE0) == 0x60) ? (c ^ 0x20) : c;
}

char to_lower(const char c)
{
    return ((c & 0xE0) == 0x40) ? (c ^ 0x20) : c;
}

void fast_to_lower(char *restrict str)
{
    for (size_t i = 0; str[i]; ++i) {
        str[i] = to_lower(str[i]);
    }
}

void fast_to_upper(char *restrict str)
{
    for (size_t i = 0; str[i]; ++i) {
        str[i] = to_upper(str[i]);
    }
}
