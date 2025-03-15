/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** main.c
*/

#include "objdump.h"

int usage(void)
{
    console_log("USAGE:\n\t./%s -fs <binary>\n", OBJ_PRGRM);
    return SUCCESS;
}

static void process_all_arguments(int argc, char **argv)
{
    _Bool fs = false;

    if (argc == 1) {
        init_objdump(DEFAULT_FILE);
    }
    if (argc == 2 && strcmp(argv[1], "-fs") == 0) {
        init_objdump(DEFAULT_FILE);
        return;
    }
    for (int i = 1; i < argc; ++i) {
        if (!fs && strcmp(argv[i], "-fs") == 0) {
            fs = true;
            continue;
        }
        init_objdump(argv[i]);
    }
}

int parse_arguments(int argc, char **argv)
{
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
