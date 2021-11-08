#include "../inc/libmx.h"

bool help_ban(int c, int *ban, int size) {
    for (int i = 0; i < size; i++) {
        if (ban[i] == c) {
            return true;
        }
    }
    return false;
}

int mx_get_path(int *lenght, int *weights, char **node_arr, t_bridge **bridge_arr, int count, char *way, char **path,
                int *ban, int *banned, int *blacklist) {
    int weight_t = -1;
    int bridge_prev = -1;
    int nbridge = -1;
    int weight_out = 0;
    int len_t = 0;
    int step = 1;
    bool run = true;
    bool atrue = true;
    char *node_t = way;
    path[0] = way;
    for (int j = 0; j < count + 1 && run; j++) {
        atrue = true;
        weight_out = mx_get_weight(node_arr, weights, way);
        for (int i = 0; bridge_arr[i] != NULL; i++) {
            if (help_ban(i, ban, *banned)) {
                continue;
            }
            if (!mx_strcmp(bridge_arr[i]->island1, way)) {
                node_t = bridge_arr[i]->island2;
                weight_t = mx_get_weight(node_arr, weights, bridge_arr[i]->island2);
                len_t = bridge_arr[i]->distance;
            } else if (!mx_strcmp(bridge_arr[i]->island2, way)) {
                node_t = bridge_arr[i]->island1;
                weight_t = mx_get_weight(node_arr, weights, bridge_arr[i]->island1);
                len_t = bridge_arr[i]->distance;
            } else {
                continue;
            }
            if (weight_out < len_t) {
                continue;
            }
            if (weight_t == 0) {
                ban[*banned] = i;
                *banned += 1;
                path[step] = node_t;
                lenght[step - 1] = len_t;
                step++;
                run = false;
                atrue = false;
                nbridge = i;
                break;
            }
            if (weight_out - len_t == weight_t) {
                bridge_prev = i;
                lenght[step - 1] = len_t;
                way = node_t;
                path[step] = way;
                step++;
                atrue = false;
                break;
            }
        }
        if (atrue) {
            if (!mx_strcmp(way, path[0])) {
                return -1;
            }
            j = 0;
            way = path[0];
            step = 1;
            ban[*banned] = bridge_prev;
            *banned += 1;
            if (!mx_strcmp(bridge_arr[bridge_prev]->island1, path[0])
                || !mx_strcmp(bridge_arr[bridge_prev]->island2, path[0])) {
                ban[*blacklist] = bridge_prev;
                *blacklist += 1;
                *banned = *blacklist;
            }
        }
        if (!run && (!mx_strcmp(bridge_arr[nbridge]->island1, path[0])
                     || !mx_strcmp(bridge_arr[nbridge]->island2, path[0]))) {
            ban[*blacklist] = nbridge;
            *blacklist += 1;
            *banned = *blacklist;
        }
    }
    path[step] = NULL;
    return step;
}
