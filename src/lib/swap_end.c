/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** swap_end
*/

#include "my.h"

unsigned short swap_end_color_2(unsigned short num)
{
    num = (num >> 8) | (num << 8);
    return num;
}

unsigned int swap_end_color_4(unsigned int num)
{
    num = ((num >> 24) & 0x000000FF) |
        ((num >> 8) & 0x0000FF00) |
        ((num << 8) & 0x00FF0000) |
        ((num << 24) & 0xFF000000);
    return num;
}
