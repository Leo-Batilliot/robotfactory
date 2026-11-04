/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** main
*/
#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int help(void)
{
    mini_printf(1, "USAGE\n./asm file_name[.s]\nDESCRIPTION\n");
    mini_printf(1, "file_name file in assembly language to be converted int");
    mini_printf(1, "o file_name.cor, an executable in the Virtual Machine.\n");
    return 0;
}

FILE *opensrc(char *src)
{
    FILE *file = NULL;
    struct stat stat_file;

    if (!src || my_strlen(src) < 2 ||
        src[my_strlen(src) - 2] != '.' || src[my_strlen(src) - 1] != 's') {
        mini_printf(2, "Invalid file name: [%s]\n", src);
        return NULL;
    }
    if (stat(src, &stat_file) == -1)
        return file;
    if (stat_file.st_size <= 0) {
        mini_printf(2, "The file is empty.\n");
        return file;
    }
    file = fopen(src, "r");
    if (!file)
        mini_printf(2, "Could not open [%s]\n", src);
    return file;
}

FILE *opendst(char *src, char **dst_name)
{
    FILE *file = NULL;

    src[my_strlen(src) - 1] = '\0';
    (*dst_name) = my_strcat(src, NULL, "cor");
    if (!(*dst_name))
        return NULL;
    file = fopen((*dst_name), "w");
    if (!file)
        mini_printf(2, "Could not open [%s]\n", (*dst_name));
    return file;
}

int main(int ac, char **av)
{
    FILE *src = NULL;
    FILE *dst = NULL;
    char *dst_name = NULL;
    int res = 0;

    if (ac != 2)
        return 84;
    if (!my_strcmp(av[1], "-h"))
        return help();
    src = opensrc(av[1]);
    if (!src)
        return 84;
    res = main_loop(src, dst, dst_name, av[1]);
    free(dst_name);
    return res;
}
