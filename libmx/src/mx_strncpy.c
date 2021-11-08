#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int length = mx_strlen(src);
    if (length < len) len = length;
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
    return dst;
}
