/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** unit_tests-shared_inlines.c
*/

#include "include/unit-tests.h"
#include "../include/shared.h"

/*
 * is_valid_elf
 */

Test(is_valid_elf, valid_elf)
{
    const unsigned char valid_header[EI_NIDENT] = {
        ELFMAG0,
        ELFMAG1,
        ELFMAG2,
        ELFMAG3};

    cr_assert(is_valid_elf(valid_header), "Expected valid ELF.");
}

Test(is_valid_elf, invalid_elf)
{
    const unsigned char invalid_header[EI_NIDENT] = { 'X', 'Y', 'Z', 'W' };

    cr_assert_not(is_valid_elf(invalid_header), "Expected invalid ELF.");
}

Test(is_valid_elf, partially_valid_elf)
{
    const unsigned char partially_valid_header[EI_NIDENT] = {
        ELFMAG0,
        ELFMAG1, 
        'X',
        'Y' };

    cr_assert_not(is_valid_elf(partially_valid_header), "Expected invalid ELF.");
}

/*
 * get_sym_name
 */

Test(get_sym_name, valid_name)
{
    char buffer[64] = "ELFHeader\x00Sym1\x00Sym2";
    size_t offset = 10;
    size_t name_offset = 0;
    const char *symbol = get_sym_name(buffer, offset, name_offset);

    cr_assert_str_eq(symbol, "Sym1", "Expected 'Sym1'");
}

Test(get_sym_name, different_offset)
{
    char buffer[64] = "ELFHeader\x00TestSymbol\x00otherSymbol";
    size_t offset = 10;
    size_t name_offset = 11;
    const char *symbol = get_sym_name(buffer, offset, name_offset);

    cr_assert_str_eq(symbol, "otherSymbol", "Expected 'otherSymbol'");
}
