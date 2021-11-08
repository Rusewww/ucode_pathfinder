#include "../inc/libmx.h"

bool help_visit(char **visit_arr, int count, char *s) {
    for (int i = 0; i < count; i++) {
        if (!mx_strcmp(visit_arr[i], s)) {
            return true;
        }
    }
    return false;
}

void mx_weigh_node_arr(int *weights, char **node_arr, t_bridge **bridges, int count) {
    char **visit_arr = (char **) malloc(count * sizeof *visit_arr);
    char *tmp;
    int visits = 0;
    int min = 0;
    int weight = 0;
    for (int i = 0; i < count; i++) {
        min = 0;
        while (help_visit(visit_arr, visits, node_arr[min])) {
            min++;
        }
        if (visits == count) {
            break;
        }
        for (int j = 0; j < count; j++) {
            if (help_visit(visit_arr, visits, node_arr[j])) {
                continue;
            }
            if (weights[j] >= 0 && (weights[min] < 0 || weights[min] > weights[j])) {
                min = j;
            }
        }
        tmp = node_arr[min];
        for (int j = 0; bridges[j] != NULL; j++) {
            if (!mx_strcmp(bridges[j]->island1, tmp)) {
                if (help_visit(visit_arr, visits, bridges[j]->island2)) {
                    continue;
                }
                mx_weight_set(&weights, node_arr, bridges[j]->island2, weight + bridges[j]->distance);
                weight = mx_get_weight(node_arr, weights, tmp);
            } else if (!mx_strcmp(bridges[j]->island2, tmp)) {
                if (help_visit(visit_arr, visits, bridges[j]->island1)) {
                    continue;
                }
                mx_weight_set(&weights, node_arr, bridges[j]->island1, weight + bridges[j]->distance);
                weight = mx_get_weight(node_arr, weights, tmp);
            }
        }
        visit_arr[visits] = tmp;
        visits++;
    }
    free(visit_arr);
}
