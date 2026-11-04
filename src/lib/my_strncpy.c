/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** my_strncpy
*/

int my_strncpy(char *str, char *dst, int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = str[i];
    return 0;
}
