#include <stdio.h>

#define HEIGHT 720
#define WIDTH 1280


int main(void) {
    printf("P1\n%d %d\n", WIDTH, HEIGHT);
    for (size_t i = 0; i < WIDTH; i++)
        for (size_t j = 0; j < HEIGHT; j++)
            printf("%d\t", !((j + i)%3) || (j == i) || (j + !(i % 11)));
    return 0;
}
