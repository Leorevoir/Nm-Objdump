/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** unit_tests-shared.c
*/

#include <elf.h>
#include <criterion/redirect.h>

/*
 * 32
 */

Elf32_Sym create_mock_sym32(uint16_t shndx, uint8_t bind, uint8_t type)
{
    Elf32_Sym sym = {0};

    sym.st_shndx = shndx;
    sym.st_info = (unsigned char) ELF32_ST_INFO(bind, type);
    return sym;
}

Elf32_Shdr create_mock_section32(uint32_t type, uint32_t flags)
{
    Elf32_Shdr sec = {0};

    sec.sh_type = type;
    sec.sh_flags = flags;
    return sec;
}

/*
* 64
*/

Elf64_Sym create_mock_sym64(uint16_t shndx, uint8_t bind, uint8_t type)
{
    Elf64_Sym sym = {0};

    sym.st_shndx = shndx;
    sym.st_info = (unsigned char) ELF64_ST_INFO(bind, type);
    return sym;
}

Elf64_Shdr create_mock_section64(uint32_t type, uint32_t flags)
{
    Elf64_Shdr sec = {0};

    sec.sh_type = type;
    sec.sh_flags = flags;
    return sec;
}

/*
* redirect
*/

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}
