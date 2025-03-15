/*
** EPITECH PROJECT, 2025
** nn/objdump
** File description:
** macro.h
*/

#ifndef MACRO_H_
    #define MACRO_H_

    #define ERROR_CODE 84
    #define SUCCESS 0

    /*
     * when no arguments nm uses a.out
     */
    #define DEFAULT_FILE "a.out"

    /*
     * utils gobal macro for modular purposes
     */

    /*
     * get elf offset
     */
    #define ELF_OFFSET(x, y) x[x[y].sh_link].sh_offset

    /*
     * as the name says
     */
    #define ELF_SHDR_SIZE(x) (size_t)(x.sh_size / x.sh_entsize)

    /*
     * it is \t\t + 1 space !!!!!!!!!!!!!!!!!!
     */
    #define GLOBAL_SHOW_UNKNOWN() console_log("                 ")

    /*
     * as the name says
     */
    #define GLOBAL_SHOW_SYM_VALUE(x) console_log("%016lx ", (x)->st_value)


#endif /* MACRO_H_ */
