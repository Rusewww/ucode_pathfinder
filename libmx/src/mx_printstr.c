#include "../inc/libmx.h"

void mx_printstr(const char *s) {
    int a = 0;
    while (a < mx_strlen(s)) {
        write(1, &s[a], 1);
        a++;
    }
}
