/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** test_show.c
*/

#include "include/unit-tests.h"
#include "../src/objdump/show.h"
#include "../src/objdump/objdump.h"

Test(maybe_show, maybe_show_fast_and_modulo, .init = redirect_all_stdout)
{
    cr_assert_eq(maybe_show(4, 7, 'T'), false);
    cr_assert_eq(maybe_show(16, 15, 'T'), true);
}

Test(get_architecture, maybe_get_architecture)
{
    cr_assert_str_eq(get_architecture(EM_SPARC32PLUS), "Sparc v8+");
    cr_assert_str_eq(get_architecture(EM_X86_64), "i386:x86-64");
    cr_assert_str_eq(get_architecture(69), "i386:x86-64");
}
