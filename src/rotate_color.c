#include <rotate_color.h>
#include <stdio.h>

void rotate_color() {
    static int a = 1;
    printf("\033[0;3%dm", a);
    a = (a % 6) + 1;
}
