//
// Created by Ihor Zozulia on 11/3/21.
//

#ifndef UCODE_PATHFINDER_PATHFINDER_H
#define UCODE_PATHFINDER_PATHFINDER_H

#include "../libmx/inc/libmx.h"

typedef struct s_bridge
{
    char *A;
    char *B;
    int length;
} t_bridge;


bool mx_isnum(const char *s);
bool mx_isword(const char *s);
void mx_printerr(const char *s);
void mx_del_bridges(t_bridge ***bridges);
bool mx_isvalid_line(const char *s);
t_bridge *mx_get_bridge(const char *s);
void mx_print_path(int *weights, char **nodes, t_bridge **bridges, int count, char *from, int bridge_count);
void mx_set_weight(int **weights, char **nodes,
                   char *s, int waight);
void mx_weigh_nodes(int *weights, char **nodes,
                    t_bridge **bridges, int count);
int mx_set_path(char ***path, int *weights,
                char **nodes, char *to,
                char *from, t_bridge **bridges);
int mx_get_weight(char **nodes, int *weights, char *s);
int get_node_index(char **nodes, char *node);

#endif //UCODE_PATHFINDER_PATHFINDER_H
