/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** objdump_elf64_content.c
*/

#include "objdump.h"

/*
* not sure about the default value but works for me
*/
const char *get_architecture(const uint16_t key)
{
    for (uint16_t i = 0; i < ARCHI_NBR; ++i) {
        if (key == archi[i].key) {
            return archi[i].str;
        }
    }
    return "i386:x86-64";
}
