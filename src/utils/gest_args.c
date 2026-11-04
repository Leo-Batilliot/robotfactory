/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** gest_args
*/

#include "my.h"

static int error_message(void)
{
    mini_printf(2, "The argument given to the instruction is invalid.\n");
    return 84;
}

int gest_another(int k, char **array, FILE *dst)
{
    unsigned short bytes = (unsigned short)my_atoi(array[k]);

    for (int i = 0; array[k][i] != '\0'; i++) {
        if (array[k][i] < '0' || array[k][i] > '9')
            return error_message();
    }
    bytes = swap_end_color_2(bytes);
    fwrite(&bytes, IND_SIZE, 1, dst);
    return 0;
}

int gest_direct(int k, char **array, FILE *dst, first_t *info)
{
    unsigned int bytes = (unsigned int)my_atoi(array[k]);

    if (array[k][1] == '\0')
        return error_message();
    for (int i = 1; array[k][i] != '\0'; i++) {
        if (array[k][i] < '0' || array[k][i] > '9')
            return error_message();
    }
    if (info->cur_size == 2) {
        bytes = (unsigned short)bytes;
        bytes = swap_end_color_2(bytes);
    } else
        bytes = swap_end_color_4(bytes);
    fwrite(&bytes, info->cur_size, 1, dst);
    return 0;
}

int gest_register(int k, char **array, FILE *dst)
{
    char num = my_atoi(array[k]);

    if (num <= 0) {
        mini_printf(2, "Invalid register number.\n");
        return 84;
    }
    fwrite(&num, sizeof(char), 1, dst);
    return 0;
}

static int write_adress(node_t *tmp, FILE *dst, first_t *info, node_t *cur)
{
    int adress = tmp->value - cur->value;
    unsigned int adress_long = 0;
    unsigned short adress_short = 0;

    if (info->cur_size == 2) {
        adress_short = (unsigned short)adress;
        adress_short = swap_end_color_2(adress_short);
        fwrite(&adress_short, IND_SIZE, 1, dst);
    } else {
        adress_long = (unsigned int)adress;
        adress_long = swap_end_color_4(adress_long);
        fwrite(&adress_long, info->cur_size, 1, dst);
    }
    delete_node(info->list_cmd, cur->name);
    return 1;
}

static int gest_adress(char **array, first_t *info, FILE *dst, node_t *tmp)
{
    node_t *cur = info->list_cmd->head;

    for (; cur != NULL; cur = cur->next) {
        if (!my_strcmp(cur->name, array[0]))
            return write_adress(tmp, dst, info, cur);
    }
    return 0;
}

static int gest_list(first_t *info, node_t *tmp, char **array, FILE *dst)
{
    if (!my_strcmp(tmp->name, &array[info->tmp][2])) {
        if (gest_adress(array, info, dst, tmp) == 1)
            return 1;
    }
    return 0;
}

int gest_labels(first_t *info, int k, char **array, FILE *dst)
{
    node_t *tmp = info->list->head;

    info->tmp = k;
    for (; tmp != NULL; tmp = tmp->next) {
        if (gest_list(info, tmp, array, dst) == 1)
            return 0;
    }
    return error_message();
}

int gest_args(int k, char **array, FILE *dst, first_t *info)
{
    if (array[k][0] == LABEL_REGISTRER)
        return gest_register(k, array, dst);
    if (array[k][0] == DIRECT_CHAR && array[k][1] != ':')
        return gest_direct(k, array, dst, info);
    if (array[k][0] == '%' && array[k][1] == ':')
        return gest_labels(info, k, array, dst);
    if (array[k][0] != DIRECT_CHAR && array[k][0] != LABEL_REGISTRER) {
        return gest_another(k, array, dst);
    }
    return 0;
}
