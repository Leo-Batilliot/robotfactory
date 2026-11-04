/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strcat
*/
#include "my.h"

char *my_strcat(char *str1, char *sep, char *str2)
{
    char *res;
    int count = 0;

    if (!str1)
        return my_strdup(str2);
    if (!str2)
        return my_strdup(str1);
    res = malloc(sizeof(char) * (my_strlen(str1) + my_strlen(str2) +
        my_strlen(sep) + 1));
    if (!res)
        return NULL;
    for (; str1[count] != '\0'; count++)
        res[count] = str1[count];
    for (int i = count; sep && sep[count - i] != '\0'; count++)
        res[count] = sep[count - i];
    for (int i = 0; str2[i] != '\0'; i++)
        res[count + i] = str2[i];
    res[my_strlen(str1) + my_strlen(str2) + my_strlen(sep)] = '\0';
    return res;
}
