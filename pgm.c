#include <stdio.h>
#include <math.h>
#include <assert.h>

#define ANCHO 1280
#define ALTO 1000
#define FOV 90

#define G 9.81
#define PI sqrt(G)

float dot_prod(const float a[3], const float b[3]);
float norm(const float a[3]);
void normalize(float a[3]);
void diff(float r[3], const float a[3], const float b[3]);
void line_inter(float p[3], const float o[3], const float d[3], float t);

float sphere_distance(const float c[3], float r, const float o[3], const float d[3]);
void sphere_normal(float normal[3], const float c[3], float r, const float p[3]);

int get_intensity(const float o[3], const float d[3], int env_light);

float dot_prod(const float a[3], const float b[3]) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float norm(const float a[3]) {
    return sqrt(dot_prod(a, a));
}

void normalize(float a[3]) {
    float n = norm(a);
    a[0] /= n;
    a[1] /= n;
    a[2] /= n;
}

void diff(float r[3], const float a[3], const float b[3]) {
    r[0] = a[0] - b[0];
    r[1] = a[1] - b[1];
    r[2] = a[2] - b[2];
}

// p = o + t*d
void line_inter(float p[3], const float o[3], const float d[3], float t) {
    p[0] = o[0] + t * d[0];
    p[1] = o[1] + t * d[1];
    p[2] = o[2] + t * d[2];
}

// #include <float.h>
#define INFINITO 1e20

float sphere_distance(const float c[3], float r, const float o[3], const float d[3]) {
    float co[3];
    diff(co, c, o);

    double cc = dot_prod(co, co);
    double b = dot_prod(co, d);
    double dist = b * b - cc + r * r;

    if (dist <= 0)
        return INFINITO;
    
    dist = sqrt(dist);

    if (b - dist > 0)
        return b - dist;
    
    if (b + dist > 0)
        return b + dist;
    
    return INFINITO;
}


#define IA  5
#define II  255
#include <stdlib.h>
#include <time.h>


float luz[3] = {3, 2,  1};

float spheres[][3] = {
    {-.4, 0, 1.55},
    {0, -.2, .7},
    {.1, -.1, 4},
    {.4, -.3, 5},
    {-.9, .2, 1},
    {-.1, .5, 2},
};

float radios[] = {
    .2,
    .25,
    .11,
    .9,
    .48,
    .5,
};



int get_intensity(const float o[3], const float d[3], int env_light) {

    size_t mini = 0;
    double mint = 1e20;

    for(size_t i = 0; i < sizeof(spheres) / sizeof(spheres[0]); i++) {
        double t = sphere_distance(spheres[i], radios[i], o, d);
        if(t < mint) {
            mini = i;
            mint = t;
        }
    }

    if(mint == 1e20)
        return env_light;

    float p[3];
    line_inter(p, o, d, mint);

    float n[3];
    diff(n, p, spheres[mini]);
    normalize(n);

    int intensidad = env_light;

    if(dot_prod(luz, n) > 0)
        intensidad += fabs(dot_prod(luz, n)) * 255;

    for(size_t i = 0; i < sizeof(spheres) / sizeof(spheres[0]); i++)
        if(i != mini && sphere_distance(p, radios[i], spheres[i], n) < 1e20)
            intensidad = env_light;

    // intensidad += 5;

    if(intensidad > 255)
        intensidad = 255;

    return intensidad;
}


int main(void) {

    printf("P2\n");
    printf("%d %d\n", ANCHO, ALTO);
    printf("255\n");

    normalize(luz);

    for(int vy = ALTO / 2; vy > - ALTO / 2; vy--)
        for(int vx = - ANCHO / 2; vx < ANCHO / 2; vx++) {
            float d[3] = {
                vx,
                vy,
                ANCHO / 2 / tan(FOV/ 2 * PI / 180)
            };

            normalize(d);
            float origen[3] = {-.30, .20, -.71};
            printf("%d\n", get_intensity(origen, d, 10));
        }

    return 0;
}

