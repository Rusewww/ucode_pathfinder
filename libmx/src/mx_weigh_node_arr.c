#include "../inc/libmx.h"

bool mx_visited(char **visit, char *s, int visit_count);

void mx_weigh_node_arr(int *weights, char **node_arr, t_bridge **bridge_arr, int count) {
    char **visit = (char **) malloc(count * sizeof *visit);
    char *curr;
    int visit_count = 0;
    int min = 0;
    int weight = 0;
    for (int i = 0; i < count; i++) {
        min = 0;
        while (mx_visited(visit, node_arr[min], visit_count)) {
            min++;
        }
        if (visit_count == count) break;
        for (int j = 0; j < count; j++) {
            if (mx_visited(visit, node_arr[j], visit_count)) {
                continue;
            }
            if (weights[j] >= 0 && (weights[min] < 0 || weights[min] > weights[j])) {
                min = j;
            }
        }
        curr = node_arr[min];
        for (int j = 0; bridge_arr[j] != NULL; j++) {
            if (!mx_strcmp(bridge_arr[j]->island1, curr)) {
                if (mx_visited(visit, bridge_arr[j]->island2, visit_count)) {
                    continue;
                }
                weight = mx_get_weight(node_arr, weights, curr);
                mx_weight_set(&weights, node_arr, bridge_arr[j]->island2, weight + bridge_arr[j]->distance);
            } else if (!mx_strcmp(bridge_arr[j]->island2, curr)) {
                if (mx_visited(visit, bridge_arr[j]->island1, visit_count)) {
                    continue;
                }
                weight = mx_get_weight(node_arr, weights, curr);
                mx_weight_set(&weights, node_arr, bridge_arr[j]->island1, weight + bridge_arr[j]->distance);
            }
        }
        visit[visit_count] = curr;
        visit_count++;
    }
    free(visit);
}

bool mx_visited(char **visit, char *s, int visit_count) {
    for (int i = 0; i < visit_count; i++) {
        if (!mx_strcmp(visit[i], s)){
            return true;
        }

    }
    return false;
}

