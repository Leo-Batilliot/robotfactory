/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** linked_lists
*/

#include "my.h"

list_t *create_list(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    return list;
}

int free_node(node_t *node)
{
    if (!node)
        return 84;
    if (node->name)
        free(node->name);
    free(node);
    return 0;
}

void free_list(list_t *list)
{
    node_t *current;
    node_t *next;

    if (!list)
        return;
    current = list->head;
    while (current) {
        next = current->next;
        free_node(current);
        current = next;
    }
    free(list);
}

void add_node(char *name, int value, list_t *list)
{
    node_t *node = NULL;
    node_t *current = NULL;

    if (!list)
        return;
    node = malloc(sizeof(node_t));
    if (!node) {
        free(list);
        return;
    }
    node->name = name;
    node->value = value;
    node->next = NULL;
    if (list->head == NULL)
        list->head = node;
    else {
        current = list->head;
        for (; current->next != NULL; current = current->next);
        current->next = node;
    }
}

int delete_node(list_t *list, char *name)
{
    node_t *current;
    node_t *previous;
    node_t *next;

    current = list->head;
    if (!my_strcmp(current->name, name)) {
        list->head = current->next;
        return free_node(current);
    }
    for (; current; current = next) {
        next = current->next;
        if (!my_strcmp(current->name, name)) {
            previous->next = next;
            return free_node(current);
        }
        previous = current;
    }
    return 84;
}
