#include "../inc/libmx.h"

int mx_get_index_node(char **node_arr, char *node) {
    for (int i = 0; node_arr[i] != NULL; i++) {
        if (!mx_strcmp(node_arr[i], node)) {
            return i;
        }
    }
    return -1;
}
