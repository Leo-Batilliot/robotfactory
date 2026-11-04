/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** get_label_err
*/

#include "my.h"

int check_err_lab(char *string, first_t *info)
{
    node_t *tmp = info->list->head;

    for (; tmp; tmp = tmp->next) {
        if (!my_strcmp(tmp->name, string))
            return 0;
    }
    return 84;
}

static int check_err_i(char **array_p)
{
    if (!array_p
        || array_p[0][0] == '#'
        || !my_strcmp(".name", array_p[0])
        || !my_strcmp(".comment", array_p[0]))
        return 1;
    if (array_p[0][my_strlen(array_p[0]) - 1] == ':') {
        if (!array_p[0])
            return 84;
        array_p[0] = array_p[1];
    }
    return 0;
}

static int check_array_lab(int i, char **array_p, first_t *info)
{
    if (array_p[i][0] == '%' && array_p[i][1] == ':') {
        if (check_err_lab(array_p[i] + 2, info) == 84)
            return 84;
    }
    return 0;
}

static int loop_do_check(char **array_p, first_t *info)
{
    int res = 0;

    for (int i = 0; array_p[i] != NULL; i++) {
        res = check_array_lab(i, array_p, info);
        if (res == 84)
            return 84;
    }
    return 0;
}

int do_err_label(FILE *src, first_t *info)
{
    char *line_p = NULL;
    char **array_p = NULL;
    size_t len_p = 0;
    int res = 0;

    fseek(src, 0, SEEK_SET);
    while (getline(&line_p, &len_p, src) != -1) {
        array_p = split_str(line_p, " \t\"\n,");
        res = check_err_i(array_p);
        if (res == 1)
            continue;
        if (res == 84)
            return 84;
        res = loop_do_check(array_p, info);
        if (res == 84)
            return 84;
    }
    return 0;
}
