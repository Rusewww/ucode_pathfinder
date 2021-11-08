#include "../inc/libmx.h"

void mx_printint(int n) {
    if (n == -2147483648) {
        write(1, "-2147483648", 11);
        return;
    }
    if (n == 0) {
        mx_printchar('0');
    }
    int save[10];
    int length = 0;
    int minus = 0;
    if (n < 0) {
        minus = 1;
        n *= -1;
    }
    while (n) {
        save[length] = n % 10;
        n = n / 10;
        length++;
    }
    length--;
    if (minus != 0) {
        mx_printchar('-');
    }
    while (length != -1) {
        mx_printchar((char) (save[length] + 48));
        length--;
    }
}
