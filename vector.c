#include <stdio.h>
#include <math.h>

#include "vector.h"

vec_t normalizar(vec_t a) {
    double n = norma(a);
    return (vec_t){a.x/ n, a.y / n, a.z / n};
}

vec_t resta(vec_t a, vec_t b) {
    return (vec_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec_t interpolar_recta(vec_t o, vec_t d, double t) {
    return (vec_t){o.x + t * d.x, o.y + t * d.y, o.z + t * d.z};
}

void pvec(const vec_t v, const char *s) {
    printf("%s: %f %f %f\n", s, v.x, v.y, v.z);
}

double producto_interno(vec_t a, vec_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double norma(vec_t a) {
    return sqrt(producto_interno(a, a));
}