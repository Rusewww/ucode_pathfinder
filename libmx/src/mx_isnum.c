#include "../inc/libmx.h"

bool mx_isnum(const char *string) {
    if (*string == '-') {
        string++;
    }
    while (*string != '\0') {
        if (!mx_isdigit(*string)) {
            return false;
        }
        string++;
    }
    return true;
}
