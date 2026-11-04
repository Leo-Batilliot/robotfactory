/*
** EPITECH PROJECT, 2025
** lib
** File description:
** lib
*/

#ifndef LIB_H
    #define LIB_H
    /*    EXTERNAL LIBS    */
    #include "op.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdarg.h>
    #include <signal.h>

typedef struct node {
    char *name;
    int value;
    struct node *next;
} node_t;
typedef struct list {
    struct node *head;
} list_t;

typedef struct first {
    header_t header;
    list_t *list;
    list_t *list_cmd;
    char *file_name;
    char *src_name;
    char *cur_cmd;
    int cur_size;
    int index;
    int tmp;
    int is_lab;
    int index_start;
} first_t;

typedef struct formatter {
    char *cmd;
    void (*pts)(char **array);
} formatter_t;

/*    LIB    */
char *my_strdup(char *);
char **list_to_array(list_t *);
char **split_str(char *, char *);
char *array_to_str(char **, char);
char *my_strcat(char *, char *, char *);
int my_atoi(char *);
int my_strlen(char *);
int free_node(node_t *);
int my_array_len(char **);
int total_array_len(char **);
int my_strcmp(char *, char *);
int delete_node(list_t *, char *);
int mini_printf(int, char *, ...);
int my_strncmp(char *, char *, int);
int my_strncpy(char *, char *, int);
list_t *create_list(void);
list_t *array_to_list(char **);
void free_array(char **);
void free_list(list_t *);
void print_list(list_t *);
void add_node(char *, int, list_t *);

/*    FUNCTIONS    */
unsigned int swap_end_color_4(unsigned int num);
unsigned short swap_end_color_2(unsigned short num);

int get_size_cmd(first_t *);
int do_err_label(FILE *, first_t *);
int get_size_header(first_t *, char **);
int loop_body(FILE *, FILE *, first_t *);
int main_loop(FILE *, FILE *, char *, char *);
int gest_args(int, char **, FILE *, first_t *);

FILE *opendst(char *src, char **dst_name);

#endif
