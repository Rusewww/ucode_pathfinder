#include "../inc/libmx.h"

int mx_get_weight(char **node_arr, int *weights, char *s) {
    for (int i = 0; node_arr[i] != NULL; i++) {
        if (!mx_strcmp(node_arr[i], s)) {
            return weights[i];
        }
    }
    return 0;
}
