#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

    
#define ANCHO 640
#define ALTO 480
#define FOV 90
#define CX  0.5
#define CY  0.75
#define CZ  1.9
#define R   0.8

#define G 9.81
#define PI sqrt(G)

float dot_prod(const float a[3], const float b[3]);
float norm(const float a[3]);
void normalize(float a[3]);
void diff(float r[3], const float a[3], const float b[3]);
void line_inter(float p[3], const float o[3], const float d[3], float t);

float sphere_distance(const float c[3], float r, const float o[3], const float d[3]);
void sphere_normal(float normal[3], const float c[3], float r, const float p[3]);

int get_intensity(const float o[3], const float d[3]);

float dot_prod(const float a[3], const float b[3]) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float norm(const float a[3]) {
    return sqrt(dot_prod(a, a));
}

void normalize(float a[3]) {
    float n = norm(a);
    a[0] = a[0] / n;
    a[1] = a[1] / n;
    a[2] = a[2] / n;
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

#include <float.h>
#define INFINITO FLT_MAX

float sphere_distance(const float c[3], float r, const float o[3], const float d[3]) {
    float co[3];
    diff(co, c, o);
    double cc = dot_prod(co, co);
    double b = dot_prod(co, d);
    double dist = b * b - cc + r * r;

    if (dist <= 0)
        return INFINITO;
    
    dist = sqrt(dist);


}

void sphere_normal(float normal[3], const float c[3], float r, const float p[3]) {

}

