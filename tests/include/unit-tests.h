/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** unit_tests.h
*/

#ifndef UNIT_TESTS_CRITERION_H_
    #define UNIT_TESTS_CRITERION_H_

    #include <criterion/criterion.h>
    #include "criterion/redirect.h"
    #include <elf.h>

Elf32_Shdr create_mock_section32(uint32_t type, uint32_t flags);
Elf32_Sym create_mock_sym32(uint16_t shndx, uint8_t bind, uint8_t type);

Elf64_Shdr create_mock_section64(uint32_t type, uint32_t flags);
Elf64_Sym create_mock_sym64(uint16_t shndx, uint8_t bind, uint8_t type);

void redirect_all_stdout(void);

#endif /* UNIT_TESTS_CRITERION_H_ */
