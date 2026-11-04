/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** return string into another
*/

#include <stddef.h>

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcpy_without_back(char *dest, char const *src, size_t max_len)
{
    size_t i = 0;

    for (; src[i] != '\0' && i < max_len; i++)
        dest[i] = src[i];
    for (; i < max_len; i++)
        dest[i] = ' ';
    dest[i] = '\0';
    return dest;
}
