/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** unit_tests-nm64.c
*/

#include "include/unit-tests.h"
#include "../src/nm/nm.h"

Test(nm_types_elf64, test_special_symbols)
{
    Elf64_Shdr dummy_shdr[1] = {0};
    Elf64_Sym sym = create_mock_sym64(SHN_ABS, STB_GLOBAL, 0);

    cr_assert_eq(nm_types_elf64(dummy_shdr, &sym), 'A');
    sym = create_mock_sym64(SHN_COMMON, STB_GLOBAL, 0);
    cr_assert_eq(nm_types_elf64(dummy_shdr, &sym), 'C');
    sym = create_mock_sym64(SHN_UNDEF, STB_GLOBAL, 0);
    cr_assert_eq(nm_types_elf64(dummy_shdr, &sym), 'U');
    sym = create_mock_sym64(SHN_UNDEF, STB_WEAK, STT_FUNC);
    cr_assert_eq(nm_types_elf64(dummy_shdr, &sym), 'w');
    sym = create_mock_sym64(1, STB_WEAK, STT_FUNC);
    cr_assert_eq(nm_types_elf64(dummy_shdr, &sym), 'W');
}

Test(nm_types_elf64, test_section_symbols)
{
    Elf64_Shdr sections[2] = {0};
    Elf64_Sym sym = {0};
    
    sections[1] = create_mock_section64(SHT_NOBITS, SHF_ALLOC);
    sym.st_shndx = 1;
    cr_assert_eq(nm_types_elf64(sections, &sym), 'b');
    sections[1] = create_mock_section64(SHT_PROGBITS, SHF_ALLOC | SHF_WRITE);
    cr_assert_eq(nm_types_elf64(sections, &sym), 'd');
    sections[1] = create_mock_section64(SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR);
    cr_assert_eq(nm_types_elf64(sections, &sym), 't');
    sections[1] = create_mock_section64(SHT_PROGBITS, SHF_ALLOC);
    cr_assert_eq(nm_types_elf64(sections, &sym), 'r');
    sections[1] = create_mock_section64(SHT_DYNAMIC, 0);
    cr_assert_eq(nm_types_elf64(sections, &sym), 'd');
    sections[1] = create_mock_section64(SHT_NOTE, 0);
    cr_assert_eq(nm_types_elf64(sections, &sym), 'r');
}

Test(nm_types_elf64, test_local_symbols)
{
    Elf64_Shdr sections[2] = {0};
    Elf64_Sym sym = create_mock_sym64(1, STB_LOCAL, STT_FUNC);

    sections[1] = create_mock_section64(SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR);
    cr_assert_eq(nm_types_elf64(sections, &sym), 't');
    sections[1] = create_mock_section64(SHT_PROGBITS, SHF_ALLOC | SHF_WRITE);
    cr_assert_eq(nm_types_elf64(sections, &sym), 'd');
}
