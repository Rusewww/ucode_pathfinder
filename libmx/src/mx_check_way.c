#include "../inc/libmx.h"

bool mx_check_way(const char *s) {
    int delim = mx_get_char_index(s, '-');
    if (delim <= 0) {
        return false;
    }
    char *islands = mx_strndup(s, delim);
    if (!mx_isword(islands)) {
        mx_strdel(&islands);
        return false;
    }
    char *first_island = mx_strdup(islands);
    mx_strdel(&islands);
    s += delim + 1;
    delim = mx_get_char_index(s, ',');
    if (delim <= 0) {
        mx_strdel(&first_island);
        mx_strdel(&islands);
        return false;
    }
    islands = mx_strndup(s, delim);
    if (!mx_isword(islands) || mx_strcmp(first_island, islands) == 0) {
        mx_strdel(&first_island);
        mx_strdel(&islands);
        return false;
    }
    mx_strdel(&islands);
    mx_strdel(&first_island);
    s += delim + 1;
    if (!mx_isnum(s) || mx_atoi(s) < 1) {
        return false;
    } else {
        return true;
    }
}
