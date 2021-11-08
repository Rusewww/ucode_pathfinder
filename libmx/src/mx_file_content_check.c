#include "../inc/libmx.h"

void mx_file_content_check(char *content, char *name) {
    if (content == NULL) {
        mx_printerr("error: file ");
        mx_printerr(name);
        mx_printerr(" does not exist\n");
        exit(0);
    }
}
