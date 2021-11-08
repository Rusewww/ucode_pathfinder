#include "../inc/libmx.h"

void mx_del_bridge_arr(t_bridge ***bridge_arr) {
    for (int i = 0; (*bridge_arr)[i] != NULL; i++) {
        mx_strdel(&(*bridge_arr)[i]->island1);
        mx_strdel(&(*bridge_arr)[i]->island2);
        free((*bridge_arr)[i]);
    }
    *bridge_arr = NULL;
}
