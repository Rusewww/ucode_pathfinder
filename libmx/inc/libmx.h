#ifndef LIBMX_LIBMX_H
#define LIBMX_LIBMX_H

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <malloc/malloc.h>

/*
 * Lib function;
 */

int mx_atoi(const char *str);

char **mx_strsplit(const char *s, char c);

int mx_strlen(const char *s);

char *mx_strdup(const char *str);

void mx_strdel(char **str);

void mx_del_strarr(char ***arr);

int mx_strcmp(const char *s1, const char *s2);

char *mx_itoa(int number);

bool mx_isdigit(const char c);

char *mx_file_to_str(const char *file);

char *mx_strnew(const int size);

char *mx_strncpy(char *dst, const char *src, int len);

int mx_strcmp(const char *s1, const char *s2);

char *mx_strcpy(char *dst, const char *src);

char *mx_strndup(const char *s1, size_t n);

int mx_get_char_index(const char *str, char c);

bool mx_isword(const char *s);

bool mx_isalpha(const char c);

void mx_print_strarr(char **arr, const char *delim);

void mx_printchar(const char c);

void mx_printerr(const char *s);

void mx_printstr(const char *s);

void mx_printint(int n);

void mx_str_reverse(char *s);

void mx_swap_char(char *s1, char *s2);

bool mx_isnum(const char *s);

/*
 * Pathfinder function;
 */

typedef struct s_bridge {
    char *island1;
    char *island2;
    int distance;
} t_bridge;

int mx_get_index_node(char **node_arr, char *node);

void mx_del_bridge_arr(t_bridge ***bridge_arr);

t_bridge *mx_get_bridge(const char *string);

int mx_get_weight(char **node_arr, int *weights, char *s);

void mx_weigh_node_arr(int *weights, char **nodes, t_bridge **bridges, int count);

void mx_weight_set(int **weights, char **node_arr, char *s, int weight);

bool mx_check_way(const char *s);

int mx_get_path(int *lenght, int *weights, char **node_arr, t_bridge **bridge_arr, int count, char *way, char **path,
                int *ban, int *banned, int *blacklist);

void mx_printpath(int *weights, char **node_arr, t_bridge **bridge_arr, int count, char *from, int b_count);

void mx_file_content_check(char *content, char *name);

#endif
