/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** main.c
*/

#include "nm.h"
#include <string.h>

int usage(void)
{
    console_log("USAGE:\n\t./%s <binary>\n", NM_PRGRM);
    return SUCCESS;
}

static void process_all_arguments(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        init_nm(argv[i]);
    }
}

int parse_arguments(int argc, char **argv)
{
    if (argc == 1) {
        init_nm(DEFAULT_FILE);
        return SUCCESS;
    }
    if (argc == 2 && (strcmp(argv[1], "-h") == 0
    || strcmp(argv[1], "--help") == 0)) {
        return usage();
    }
    process_all_arguments(argc, argv);
    return SUCCESS;
}

int main(int argc, char **argv)
{
    return parse_arguments(argc, argv);
}
