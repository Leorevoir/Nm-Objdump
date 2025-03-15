/*
** EPITECH PROJECT, 2025
** NM
** File description:
** nm.h
*/

#ifndef NM_H_
    #define NM_H_

    #include "../../include/macro.h"
    #include "../../include/flag.h"
    #include "../../include/shared.h"
    #include <stdint.h>

    #define NM_PRGRM "nm"

    #define NO_SYM "my_nm: %s: no symbols"
    #define SYMBOL_NULL(x, f) symbol_not_null(x, f)

static inline void symbol_not_null(size_t n, const char *filename)
{
    if (n == 0) {
        raise_error(NO_SYM, filename);
    }
}

/*
 *
 */

typedef struct {
    Elf64_Sym *sym;
    Elf64_Addr value;
    const char *name;
    char type;
} symbol_t;

typedef struct nm_s {
    struct {
        unsigned char *buffer;
        size_t size;
    } file;
    bool is_64;
    symbol_t *symbols;
    size_t symbol_count;
} nm_t;

/*
 *
 */

void init_nm(const char *filename);
int nm_compare_symbols(const void *a, const void *b);

/*
 * elf64
 */
void nm_elf_64(nm_t *, const char *);
char nm_types_elf64(const Elf64_Shdr *, const Elf64_Sym *);

/*
 * elf32
 */
void nm_elf_32(nm_t *, const char *);
char nm_types_elf32(const Elf32_Shdr *shdr, const Elf32_Sym *sym32);

#endif /* NM_H_ */
