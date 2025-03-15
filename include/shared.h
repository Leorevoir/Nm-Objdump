/*
** EPITECH PROJECT, 2025
** shared lib
** File description:
** shared_lib.h
*/

#ifndef SHARED_LIB_H_
    #define SHARED_LIB_H_

    #include <stdio.h>
    #include <stdbool.h>
    #include <elf.h>
    #include <string.h>

/*
 * lib
 */
void console_log(const char *format, ...);
void raise_error(const char *format, ...);
char to_upper(const char c);
char to_lower(const char c);
void fast_to_lower(char *str);
void fast_to_upper(char *str);
void try_open_file(const char *, unsigned char **, size_t *);

/*
 * open
 */
void typeof_filename(const char *filename, const char *pgrm);

/*
 * error handling
 */
_Bool typeof_elf_verify(const unsigned char *buffer, const size_t size,
    const char *filename, const char *pgrm);


/*
 *
 */

static inline _Bool is_valid_elf(const unsigned char *e_ident)
{
    return !memcmp(e_ident, ELFMAG, SELFMAG);
}

static inline const char *get_sym_name(void *buf, size_t offset, size_t name)
{
    return (const char *)buf + offset + name;
}

#endif /* SHARED_LIB_H_ */
