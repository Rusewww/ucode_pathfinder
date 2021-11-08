#include "../inc/libmx.h"

t_bridge *mx_get_bridge(const char *string) {
    t_bridge *out = malloc(sizeof *out);
    char **distance = mx_strsplit(string, ',');
    out->distance = mx_atoi(distance[1]);
    char **islands = mx_strsplit(distance[0], '-');
    out->island1 = mx_strdup(islands[0]);
    out->island2 = mx_strdup(islands[1]);
    mx_del_strarr(&islands);
    mx_del_strarr(&distance);
    return out;
}
