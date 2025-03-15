/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** unit_tests-shared.c
*/

#include "include/unit-tests.h"
#include "../include/shared.h"

/*
 * faster
 */

Test(to_upper, converts_lowercase_to_uppercase)
{
    cr_assert_eq(to_upper('a'), 'A', "");
    cr_assert_eq(to_upper('z'), 'Z', "");
    cr_assert_eq(to_upper('A'), 'A', "");
    cr_assert_eq(to_upper('Z'), 'Z', "");
    cr_assert_eq(to_upper('1'), '1', "");
}

Test(to_lower, converts_uppercase_to_lowercase)
{
    cr_assert_eq(to_lower('A'), 'a', "");
    cr_assert_eq(to_lower('Z'), 'z', "");
    cr_assert_eq(to_lower('a'), 'a', "");
    cr_assert_eq(to_lower('z'), 'z', "");
    cr_assert_eq(to_lower('1'), '1', "");
}

Test(fast_to_lower, converts_string_to_lowercase)
{
    char str[] = "HeLLo WoRLd!";

    fast_to_lower(str);
    cr_assert_str_eq(str, "hello world!", "");
}

Test(fast_to_upper, converts_string_to_uppercase)
{
    char str[] = "HeLLo WoRLd!";

    fast_to_upper(str);
    cr_assert_str_eq(str, "HELLO WORLD!", "");
}

/*
* shared unit tests lib lol
*/

/*
 * elf32
 */

Test(create_mock_sym32, create_mock_sym32_test)
{
    const uint16_t shndx = 5;
    const uint8_t bind = 4;
    const uint8_t type = 3;
    const Elf32_Sym ref = {
        .st_shndx = shndx,
        .st_info = (unsigned char) ELF32_ST_INFO(bind, type)};
    const Elf32_Sym got = create_mock_sym32(shndx, bind, type);

    cr_assert_eq(ref.st_shndx, got.st_shndx, "");
    cr_assert_eq(ref.st_info, got.st_info, "");
}

Test(create_mock_section32, create_mock_section32_test)
{
    const uint32_t type = 5;
    const uint32_t flags = 4;
    const Elf32_Shdr ref = {
        .sh_type = type,
        .sh_flags = flags};
    const Elf32_Shdr got = create_mock_section32(type, flags);

    cr_assert_eq(ref.sh_type, got.sh_type, "");
    cr_assert_eq(ref.sh_flags, got.sh_flags, "");
}

/*
* elf64
*/

Test(create_mock_section64, create_mock_section64_test)
{
    const uint32_t type = 5;
    const uint32_t flags = 4;
    const Elf64_Shdr ref = {
        .sh_type = type,
        .sh_flags = flags};
    const Elf64_Shdr got = create_mock_section64(type, flags);

    cr_assert_eq(ref.sh_type, got.sh_type, "");
    cr_assert_eq(ref.sh_flags, got.sh_flags, "");
}

Test(create_mock_sym64, create_mock_sym64_test)
{
    const uint16_t shndx = 5;
    const uint8_t bind = 4;
    const uint8_t type = 3;
    const Elf64_Sym ref = {
        .st_shndx = shndx,
        .st_info = (unsigned char) ELF32_ST_INFO(bind, type)};
    const Elf64_Sym got = create_mock_sym64(shndx, bind, type);

    cr_assert_eq(ref.st_shndx, got.st_shndx, "");
    cr_assert_eq(ref.st_info, got.st_info, "");
}
