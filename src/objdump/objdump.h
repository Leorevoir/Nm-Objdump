/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** objdump.h
*/

#ifndef OBJDUMP_H_
    #define OBJDUMP_H_

    #include "../../include/macro.h"
    #include "../../include/flag.h"
    #include "../../include/shared.h"
    #include <stdint.h>

    #define OBJ_PRGRM "objdump"
    #define IDK 0
    #define IDK_STR ""

/*
 *
 */

typedef struct objdump_s {
    struct {
        unsigned char *buffer;
        size_t size;
    } file;
    _Bool is_64;
} objdump_t;

/*
 * calling struct ctor & run & dtor
 */
void init_objdump(const char *filename);

/*
 * ELF32
 */
void objdump_elf32(objdump_t *obj, const char *filename);
void show_elf32_sections_content(const Elf32_Shdr *sec, const objdump_t *obj);

/*
 * ELF64
 */
void objdump_elf64(objdump_t *obj, const char *filename);
void show_elf64_sections_content(const Elf64_Shdr *sec, const objdump_t *obj);

    /*
     * global methods
     */

/*
 * merci Noé et Süm pour la map d'architectures <3
 */

typedef struct archi_s {
    uint16_t key;
    char const *str;
} archi_t;

    #define ARCHI_NBR 11

static archi_t const archi[] = {
    {EM_NONE, "None"},
    {EM_M32, "WE32100"},
    {EM_SPARC, "Sparc"},
    {EM_386, "i386"},
    {EM_68K, "MC68000"},
    {EM_88K, "MC88000"},
    {EM_860, "Intel 80860"},
    {EM_MIPS, "MIPS R3000"},
    {EM_PARISC, "HPPA"},
    {EM_SPARC32PLUS, "Sparc v8+"},
    {EM_PPC, "PowerPC"},
    {EM_PPC64, "PowerPC64"},
    {EM_S390, "IBM S/390"},
    {EM_ARM, "ARM"},
    {EM_SH, "Renesas / SuperH SH"},
    {EM_SPARCV9, "Sparc v9"},
    {EM_IA_64, "Intel IA-64"},
    {EM_X86_64, "i386:x86-64"}
};

/*
 * architecture map getter
 */
const char *get_architecture(const uint16_t key);

static inline int get_flags(const Elf64_Half header)
{
    switch (header) {
        case ET_REL:
            return (HAS_RELOC | HAS_SYMS);
        case ET_EXEC:
            return (EXEC_P | HAS_SYMS | D_PAGED);
        case ET_DYN:
            return (HAS_SYMS | DYNAMIC | D_PAGED);
        default:
            return IDK;
    }
}

static inline const char *get_flags_to_str(const Elf64_Half header)
{
    switch (header) {
        case ET_REL:
            return "HAS RELOC, HAS_SYMS";
        case ET_EXEC:
            return "EXEC_P, HAS_SYMS, D_PAGED";
        case ET_DYN:
            return "HAS_SYMS, DYNAMIC, D_PAGED";
        default:
            return IDK_STR;
    }
}

#endif /* OBJDUMP_H_ */
