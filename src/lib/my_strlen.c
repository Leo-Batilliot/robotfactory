/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strlen
*/

#include "my.h"

int my_strlen(char *str)
{
    int res = 0;

    if (!str)
        return res;
    for (; str[res] != '\0'; res++);
    return res;
}
