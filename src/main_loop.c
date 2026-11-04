/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** main_loop
*/
#include "my.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int get_info(first_t *info, char **array, int *name_count, int *comment_count)
{
    if (!my_strncmp(".name", array[0], 5)) {
        if (!array[1] || array[2] != NULL)
            return 84;
        my_strncpy(array[1], info->header.prog_name, my_strlen(array[1]));
        (*name_count)++;
    }
    if (!my_strncmp(".comment", array[0], 8)) {
        if (!array[1] || array[2] != NULL)
            return 84;
        my_strncpy(array[1], info->header.comment, my_strlen(array[1]));
        (*comment_count)++;
    }
    return 0;
}

int check_missing(int name_count, int comment_count)
{
    if (name_count == 0 || comment_count == 0) {
        mini_printf(2, "Missing .name or .comment in [header].\n");
        return 84;
    }
    if (name_count >= 2 || comment_count >= 2) {
        mini_printf(2, "Double defintion in header.\n");
        return 84;
    }
    return 0;
}

static int check_word(char *string)
{
    if (!my_strcmp(string, ".comment") || !my_strcmp(string, ".name"))
        return 0;
    for (int i = 0; op_tab[i].code != 0; i++) {
        if (!my_strcmp(op_tab[i].mnemonique, string))
            return 0;
    }
    mini_printf(2, "Invalid instruction.\n");
    return -1;
}

int get_info_first(char *line, first_t *info,
    int *name_count, int *comment_count)
{
    char **array = split_str(line, "\t\"\n");
    char **array_size = split_str(line, " \t\"\n,");

    if (!array_size || array_size[0][0] == '#'
        || !array || array[0][0] == '#')
        return -1;
    if (get_info(info, array, name_count, comment_count) == 84)
        return 84;
    if (*comment_count > *name_count)
        return 84;
    if (get_size_header(info, array_size) == 84)
        return 84;
    if (check_word(array_size[0]) == -1)
        return 84;
    return 0;
}

int first_loop(FILE *src, first_t *info)
{
    char *line = NULL;
    int name_count = 0;
    int value = 0;
    int comment_count = 0;
    size_t len = 0;

    while (getline(&line, &len, src) != -1) {
        value = get_info_first(line, info, &name_count, &comment_count);
        if (value == -1)
            continue;
        if (value == 84)
            return 84;
    }
    if (do_err_label(src, info) == 84)
        return 84;
    return check_missing(name_count, comment_count);
}

static int fill_struct(FILE **dst, FILE **src, char **dst_name, first_t *info)
{
    *dst = opendst(info->src_name, dst_name);
    if (!dst) {
        fclose(*src);
        return 84;
    }
    info->file_name = my_strdup(*dst_name);
    if (!info->file_name)
        return 84;
    info->header.magic = COREWAR_EXEC_MAGIC;
    info->header.prog_size = swap_end_color_4(info->header.prog_size);
    fwrite(&(info->header), sizeof(header_t), 1, *dst);
    return 0;
}

static int declare_struct(first_t *info)
{
    if (!info)
        return 84;
    info->list = create_list();
    info->list_cmd = create_list();
    info->cur_cmd = NULL;
    if (!info->list)
        return 84;
    info->header.prog_size = 0;
    info->tmp = 0;
    return 0;
}

int main_loop(FILE *src, FILE *dst, char *dst_name, char *src_name)
{
    first_t *info = malloc(sizeof(first_t));

    if (declare_struct(info) == 84)
        return 84;
    if (first_loop(src, info) == 84) {
        free(info);
        return 84;
    }
    info->src_name = my_strdup(src_name);
    if (!info->src_name || fill_struct(&dst, &src, &dst_name, info) == 84)
        return 84;
    return loop_body(src, dst, info);
}
