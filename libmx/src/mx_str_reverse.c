#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    int length = mx_strlen(s);
    int half = length / 2;
    int i = 0;
    while (i < half) {
        mx_swap_char(&s[i], &s[length - 1 - i]);
        i++;
    }
}
