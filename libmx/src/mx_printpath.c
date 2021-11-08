#include "../inc/libmx.h"

void mx_printpath(int *weights, char **node_arr, t_bridge **bridge_arr, int count, char *from, int b_count) {
    int *len = (int *) malloc(count * sizeof *len);
    char **path = (char **) malloc((count + 1) * sizeof *path);
    path[count] = NULL;
    int *blacklist = (int *) malloc(b_count * sizeof *blacklist);
    int perm_blocked = 0;
    int steps = 0;
    int blocked = 0;
    for (;;) {
        steps = mx_get_path(len, weights, node_arr, bridge_arr, count, from, path, blacklist, &blocked, &perm_blocked);
        if (steps == -1) {
            break;
        }

        mx_printstr("========================================\nPath: ");
        mx_printstr(path[0]);
        mx_printstr(" -> ");
        mx_printstr(path[steps - 1]);
        mx_printstr("\nRoute: ");
        mx_print_strarr(path, " -> ");
        mx_printstr("Distance: ");
        int sum = 0;
        for (int i = 0; i < steps - 1; i++) {
            sum += len[i];
            mx_printint(len[i]);
            if (i + 1 != steps - 1){
                mx_printstr(" + ");
            }
        }
        if (sum != len[0]) {
            mx_printstr(" = ");
            mx_printint(sum);
        }

        mx_printstr("\n========================================\n");

    }
    free(len);
    free(path);
    free(blacklist);
}
