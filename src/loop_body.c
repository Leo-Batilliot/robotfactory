/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** loop_body
*/

#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int args(char **array, FILE *dst, first_t *info)
{
    if (op_tab[info->index].nbr_args != my_array_len(array) - 1) {
        mini_printf(2, "The number of arguments its not correct.\n");
        return 84;
    }
    for (int k = 1; array[k] != NULL; k++) {
        if (gest_args(k, array, dst, info) == 84)
            return 84;
    }
    return 0;
}

void fill_bin(char **array, int k, int *count, unsigned char *bit)
{
    switch (array[k][0]) {
        case LABEL_REGISTRER:
            bit[*count] = 0b01;
            break;
        case DIRECT_CHAR:
            bit[*count] = 0b10;
            break;
        case LABEL_CHAR:
            bit[*count] = 0b11;
            break;
        default:
            bit[*count] = 0b11;
            break;
    }
    (*count)++;
}

int coding_byte(int *count, char **array, FILE *dst, first_t *info)
{
    unsigned char *bit = NULL;
    unsigned char bit_end = '\0';
    int shift_pos = 6;
    int k = 1;

    if (info->is_lab == 1)
        k = 2;
    *count = 0;
    bit = malloc(sizeof(unsigned char) * op_tab[info->index].nbr_args);
    for (; array[k] != NULL; k++)
        fill_bin(array, k, count, bit);
    for (int j = 0; j < op_tab[info->index].nbr_args; j++) {
        bit_end |= (bit[j] << shift_pos);
        shift_pos -= 2;
    }
    fwrite(&bit_end, sizeof(unsigned char), 1, dst);
    free(bit);
    return 0;
}

static void op_code(FILE *dst, char **array, int *count, first_t *info)
{
    int byte_start = 0;

    fwrite(&op_tab[info->index].code, sizeof(char), 1, dst);
    if (op_tab[info->index].nbr_args > 1)
        byte_start = 1;
    if (byte_start == 1)
        coding_byte(count, array, dst, info);
}

int get_size_cmd(first_t *info)
{
    int size = 0;

    if (!my_strcmp(info->cur_cmd, "zjmp") ||
        !my_strcmp(info->cur_cmd, "ldi") ||
        !my_strcmp(info->cur_cmd, "sti") ||
        !my_strcmp(info->cur_cmd, "fork") ||
        !my_strcmp(info->cur_cmd, "lfork"))
        size = IND_SIZE;
    else
        size = DIR_SIZE;
    return size;
}

static int inside_body(char **array, first_t *info, FILE *dst, int *count)
{
    info->cur_size = 0;
    if (array[0][my_strlen(array[0]) - 1] == ':') {
        array[0][my_strlen(array[0]) - 1] = '\0';
        info->index_start = 1;
        info->is_lab = 1;
    }
    if (!my_strcmp(op_tab[info->index].mnemonique, array[info->index_start])) {
        op_code(dst, array, count, info);
        info->cur_cmd = my_strdup(op_tab[info->index].mnemonique);
        if (!info->cur_cmd)
            return 84;
        info->cur_size = get_size_cmd(info);
        if (args(&array[info->index_start], dst, info) == 84)
            return 84;
    }
    return 0;
}

static int fill_body(char **array, FILE *dst, int *count, first_t *info)
{
    info->index_start = 0;
    for (info->index = 0; op_tab[info->index].code != 0; info->index++) {
        if (inside_body(array, info, dst, count) == 84)
            return 84;
    }
    return 0;
}

int loop_body(FILE *src, FILE *dst, first_t *info)
{
    size_t len = 0;
    char *line = NULL;
    char **array = NULL;
    int count = 0;

    fseek(src, 0, SEEK_SET);
    while (getline(&line, &len, src) != -1) {
        info->is_lab = 0;
        array = split_str(line, "\t\"\n ,");
        if (!array || array[0][0] == '#')
            continue;
        if (fill_body(array, dst, &count, info) == 84)
            return 84;
    }
    free(info);
    free(line);
    return 0;
}
