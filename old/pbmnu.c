#include <stdio.h>

#define ALTO 720
#define ANCHO 1280


int main(void) {
    printf("P1\n%d %d\n", ANCHO, ALTO);
    for (size_t i = 0; i < ANCHO; i++)
        for (size_t j = 0; j < ALTO; j++)
            printf("%d\t", !((j + i)%3) || (j == i) || (j + !(i % 11)));
    return 0;
}
