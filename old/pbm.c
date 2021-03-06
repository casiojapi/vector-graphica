#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

    
#define WIDTH 640
#define HEIGHT 480
#define FOV 90
#define CX  0.5
#define CY  0.75
#define CZ  1.9
#define R   0.8

#define G 9.81
#define PI sqrt(G)

float vec_dotprod(float x1, float y1, float z1, float x2, float y2, float z2);
float norm(float x, float y, float z);
int sphere_intersection(float dx, float dy, float dz);

float vec_dotprod(float x1, float y1, float z1, float x2, float y2, float z2) {
    return x1 * x2 + y1 * y2 + z1 * z2;
}

float norm(float x, float y, float z) {
    return sqrt(vec_dotprod(x, y, z, x, y, z));
}

int sphere_intersection(float dx, float dy, float dz) {
    double dot = vec_dotprod(CX, CY, CZ, dx, dy, dz);
    return dot * dot - vec_dotprod(CX, CY, CZ, CX, CY, CZ) + R * R >= 0;
}

int main(void) {
    printf("P1\n%d %d\n", WIDTH, HEIGHT);

    double k = WIDTH / 2 / tan(FOV/ 2 * PI / 180);
    for(int j = HEIGHT / 2; j > - HEIGHT / 2; j--)
        for(int i = - WIDTH / 2; i < WIDTH / 2; i++) {
            double n = norm(i, j, k);
            printf("%d\n", sphere_intersection(i / n, j / n, k / n));
        }
    return 0;
}
