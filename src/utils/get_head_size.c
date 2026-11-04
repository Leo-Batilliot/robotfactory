/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** get_head_size
*/

#include "my.h"

int calcul_size(char param_type, int size)
{
    if (param_type == 'r')
        return 1;
    if (param_type == '%')
        return (size == 2) ? 2 : 4;
    if (param_type != '%' && param_type != 'r')
        return 2;
    return 0;
}

int loop_size(int i, char **array, first_t *info, int *is_label)
{
    char type = '\0';
    int size = 0;
    int index = 0;
    int j = 1;

    if (*is_label == 1)
        j = 2;
    for (; array[j] != NULL; j++) {
        if (!array[j])
            return 84;
        type = array[j][0];
        size = get_size_cmd(info);
        info->header.prog_size += calcul_size(type, size);
        if (index > op_tab[i].nbr_args)
            return 84;
        index++;
    }
    *is_label = 0;
    return 0;
}

static int process_size(first_t *info, int i, char **array, int *is_label)
{
    if (!my_strcmp(op_tab[i].mnemonique, array[0])) {
    info->cur_cmd = my_strdup(op_tab[i].mnemonique);
    info->header.prog_size += 1;
    if (op_tab[i].nbr_args > 1)
        info->header.prog_size += 1;
    if (loop_size(i, array, info, is_label) == 84)
            return 84;
    add_node(array[0], info->header.prog_size, info->list_cmd);
    }
    return 0;
}

int process_label(char **array, int i, first_t *info, int *is_label)
{
    int local_is = 0;
    char *label = NULL;

    if (array[0][my_strlen(array[0]) - 1] == ':') {
        label = my_strdup(array[0]);
        if (!array[1])
            return 84;
        array[0] = array[1];
        *is_label = 1;
        local_is = 1;
    }
    if (process_size(info, i, array, is_label) == 84)
        return 84;
    if (*is_label == 1 || local_is == 1) {
        label[my_strlen(label) - 1] = '\0';
        add_node(label, info->header.prog_size, info->list);
    }
    return 0;
}

int get_inside_size(char **array, first_t *info, int i, int *is_label)
{
    if (!my_strcmp(op_tab[i].mnemonique, array[0]) ||
        array[0][my_strlen(array[0]) - 1] == ':')
        return process_label(array, i, info, is_label);
    return 0;
}

int get_size_header(first_t *info, char **array)
{
    int value = 0;
    int is_label = 0;

    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        value = get_inside_size(array, info, i, &is_label);
        if (value != 0)
            return (value == 84) ? 84 : 1;
    }
    return 0;
}
