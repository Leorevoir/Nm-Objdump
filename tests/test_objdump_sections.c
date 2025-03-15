/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** test_objdump_sections.c
*/

#include "include/unit-tests.h"
#include "../src/objdump/sections.h"

/*
 * ignored by bsearch
 */
Test(is_ignored_section, known_ignored_sections, .init = redirect_all_stdout)
{
    cr_assert_eq(is_ignored_section(".bss"), 1, "Expected '.bss' to be ignored");
    cr_assert_eq(is_ignored_section(".symtab"), 1,
        "Expected '.symtab' to be ignored");
    cr_assert_eq(is_ignored_section("__libc_freeres_ptrs"), 1,
        "Expected '__libc_freeres_ptrs' to be ignored");
}

Test(is_ignored_section, unknown_sections, .init = redirect_all_stdout)
{
    cr_assert_eq(is_ignored_section(".text"), 0,
        "Expected '.text' to NOT be ignored");
    cr_assert_eq(is_ignored_section(".data"), 0,
        "Expected '.data' to NOT be ignored");
    cr_assert_eq(is_ignored_section(".rodata"), 0,
        "Expected '.rodata' to NOT be ignored");
}

/*
 * get_section_name
 */
Test(get_section_name, valid_section, .init = redirect_all_stdout)
{
    const char section_names[] = "\0.text\0.data\0.bss\0";
    const Elf64_Shdr sections[3] = {
        {.sh_name = 1},
        {.sh_name = 7},
        {.sh_name = 13},
    };

    cr_assert_str_eq(get_section_name(section_names, sections, 0),
        ".text", "Expected '.text'");
    cr_assert_str_eq(get_section_name(section_names, sections, 1),
        ".data", "Expected '.data'");
    cr_assert_str_eq(get_section_name(section_names, sections, 2),
        ".bss", "Expected '.bss'");
}

Test(get_section_name, empty_section, .init = redirect_all_stdout)
{
    const char section_names[] = "\0";
    const Elf64_Shdr sections[1] = {
        {.sh_name = 0},
    };

    cr_assert_str_eq(get_section_name(section_names, sections, 0), "",
        "Expected empty string for section name");
}
