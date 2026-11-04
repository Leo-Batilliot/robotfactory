/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strcmp
*/
#include "my.h"

int my_strcmp(char *str1, char *str2)
{
    if (!str1 || !str2 || my_strlen(str1) != my_strlen(str2))
        return 84;
    for (int i = 0; str1[i] != '\0'; i++)
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    return 0;
}
