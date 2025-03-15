/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** nm_sort.c
*/

#include "nm.h"

/*
 * skip firsts '_'
 */
static const char *skip_leading_underscores(const char *name)
{
    while (*name == '_')
        name++;
    return name;
}

/*
* really faster strcasecmp using xor 0x20
*/
static int compare_names(const char *name_a, const char *name_b)
{
    char lower_a = 0;
    char lower_b = 0;

    while (*name_a && *name_b) {
        lower_a = to_lower(*name_a);
        lower_b = to_lower(*name_b);
        if (lower_a != lower_b) {
            return lower_a - lower_b;
        }
        name_a++;
        name_b++;
    }
    return *name_a - *name_b;
}

/*
* qsort rules:
*   - skip all __
*   - priority: name > type
*/
int nm_compare_symbols(const void *a, const void *b)
{
    const symbol_t *sym_a = a;
    const symbol_t *sym_b = b;
    const char *name_a = skip_leading_underscores(sym_a->name);
    const char *name_b = skip_leading_underscores(sym_b->name);
    int name_cmp = compare_names(name_a, name_b);

    if (name_cmp != 0) {
        return name_cmp;
    }
    return sym_a->type - sym_b->type;
}
