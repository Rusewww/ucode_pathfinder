#include "../inc/libmx.h"

void mx_weight_set(int **weights, char **node_arr, char *s, int weight) {
    for (int i = 0; node_arr[i] != NULL; i++) {
        if (!mx_strcmp(node_arr[i], s)) {
            if ((*weights)[i] < weight && (*weights)[i] > 0) {
                return;
            }
            (*weights)[i] = weight;
            return;
        }
    }
}
