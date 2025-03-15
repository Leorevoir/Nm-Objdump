/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** unit_tests-nm32.c
*/

#include "include/unit-tests.h"
#include "../src/nm/nm.h"

Test(nm_compare_symbols, basic_comparison)
{
    symbol_t sym_a = {NULL, 0, "aba", 'T'};
    symbol_t sym_b = {NULL, 0, "bcb", 'T'};

    cr_assert(nm_compare_symbols(&sym_a, &sym_b) < 0, "aba before");
    cr_assert(nm_compare_symbols(&sym_b, &sym_a) > 0, "bcb after");
}

Test(nm_compare_symbols, underscore_priority)
{
    symbol_t sym_a = {NULL, 0, "__section", 'T'};
    symbol_t sym_b = {NULL, 0, "truncate", 'T'};

    cr_assert(nm_compare_symbols(&sym_a, &sym_b) < 0, "__section before");
    cr_assert(nm_compare_symbols(&sym_b, &sym_a) > 0, "truncate after");
}

Test(nm_compare_symbols, trim_underscore)
{
    symbol_t sym_a = {NULL, 0, "__section", 'T'};
    symbol_t sym_b = {NULL, 0, "section", 'T'};

    cr_assert(nm_compare_symbols(&sym_a, &sym_b) == 0, "must be equal");
}

Test(nm_compare_symbols, case_insensitivity)
{
    symbol_t sym_a = {NULL, 0, "__section", 'T'};
    symbol_t sym_b = {NULL, 0, "__SECTION", 'T'};

    cr_assert(nm_compare_symbols(&sym_a, &sym_b) == 0, "must be equal");
}

Test(nm_compare_symbols, type_priority)
{
    symbol_t sym_a = {NULL, 0, "__section", 'T'};
    symbol_t sym_b = {NULL, 0, "section", 'D'};

    cr_assert(nm_compare_symbols(&sym_a, &sym_b) > 0, "T after D");
    cr_assert(nm_compare_symbols(&sym_b, &sym_a) < 0, "D before T");
}
