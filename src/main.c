#include "../inc/pathfinder.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    char *name = argv[1];
    char *content = mx_file_to_str(name);
    mx_file_content_check(content, name);
    char **line_arr = mx_strsplit(content, '\n');
    int line_num = mx_atoi(line_arr[0]);
    mx_strdel(&content);
    if (!mx_isnum(line_arr[0]) || line_num <= 0) {
        mx_del_strarr(&line_arr);
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    int count_lines = 0;
    for (int i = 1; line_arr[i] != NULL; i++) {
        count_lines++;
    }
    int bridge_sum = 0;
    t_bridge **bridge_arr = (t_bridge **) malloc((count_lines + 1) * sizeof *bridge_arr);
    bridge_arr[count_lines] = NULL;
    char **nodes = malloc((line_num + 1) * sizeof(char **));
    nodes[line_num] = NULL;
    count_lines = 0;
    int count_nodes = 0;

    for (int i = 1; line_arr[i] != NULL; i++) {
        if (!mx_check_way(line_arr[i])) {
            mx_del_bridge_arr(&bridge_arr);
            mx_del_strarr(&line_arr);
            mx_del_strarr(&nodes);
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        bridge_arr[count_lines] = mx_get_bridge(line_arr[i]);
        bridge_sum += bridge_arr[count_lines]->distance;

        for (int j = 0; j < count_lines; j++) {
            if ((!mx_strcmp(bridge_arr[j]->island1, bridge_arr[count_lines]->island1) &&
                 !mx_strcmp(bridge_arr[j]->island2, bridge_arr[count_lines]->island2)) ||
                (!mx_strcmp(bridge_arr[j]->island1, bridge_arr[count_lines]->island2) &&
                 !mx_strcmp(bridge_arr[j]->island2, bridge_arr[count_lines]->island1))) {
                mx_del_bridge_arr(&bridge_arr);
                mx_del_strarr(&line_arr);
                mx_del_strarr(&nodes);
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
        }
        if (bridge_sum < 0) {
            mx_del_bridge_arr(&bridge_arr);
            mx_del_strarr(&line_arr);
            mx_del_strarr(&nodes);
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(0);
        }
        for (int j = 0; j <= count_nodes; j++) {
            if (j == count_nodes) {
                nodes[j] = mx_strdup(bridge_arr[count_lines]->island1);
                count_nodes++;
                break;
            }
            if (!mx_strcmp(nodes[j], bridge_arr[count_lines]->island1)) {
                break;
            }
        }
        for (int j = 0; j <= count_nodes; j++) {
            if (j == count_nodes) {
                nodes[count_nodes] = mx_strdup(bridge_arr[count_lines]->island2);
                count_nodes++;
                break;
            }
            if (!mx_strcmp(nodes[j], bridge_arr[count_lines]->island2)) {
                break;
            }
        }
        if (count_nodes > line_num) break;
        count_lines++;
    }
    if (count_nodes != line_num) {
        mx_del_bridge_arr(&bridge_arr);
        mx_del_strarr(&nodes);
        mx_del_strarr(&line_arr);
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }

    t_bridge *tmp;

    for (int i = 0; bridge_arr[i] != NULL; i++) {
        for (int j = i + 1; bridge_arr[j] != NULL; j++) {
            if (mx_get_index_node(nodes, bridge_arr[i]->island1) +
                mx_get_index_node(nodes, bridge_arr[i]->island2) >
                mx_get_index_node(nodes, bridge_arr[j]->island1) +
                mx_get_index_node(nodes, bridge_arr[j]->island2)) {
                tmp = bridge_arr[i];
                bridge_arr[i] = bridge_arr[j];
                bridge_arr[j] = tmp;
            }
        }
    }

    int *weights = malloc((count_nodes + 1) * sizeof(int));
    for (int i = 0; i < count_nodes - 1; i++) {
        for (int j = i + 1; j < count_nodes; j++) {
            for (int z = 0; z < count_nodes; z++) {
                weights[z] = -1;
            }
            mx_weight_set(&weights, nodes, nodes[j], 0);
            mx_weigh_node_arr(weights, nodes, bridge_arr, count_nodes);
            mx_printpath(weights, nodes, bridge_arr, count_nodes, nodes[i], count_lines);
        }
    }

    mx_del_bridge_arr(&bridge_arr);
    mx_del_strarr(&line_arr);
    mx_del_strarr(&nodes);
    return 0;
}
