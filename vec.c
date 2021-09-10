#include <stdio.h>
#include <math.h>

#include <time.h>
#include <stdlib.h>

#include "vec.h"

vec_t vec_normalize(vec_t a) {
    double n = vec_norm(a);
    return (vec_t){a.x/ n, a.y / n, a.z / n};
}

vec_t vec_diff(vec_t a, vec_t b) {
    return (vec_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec_t interpolar_recta(vec_t o, vec_t d, double t) {
    return (vec_t){o.x + t * d.x, o.y + t * d.y, o.z + t * d.z};
}

void vec_print(const vec_t v, const char *s) {
    printf("%s: %f %f %f\n", s, v.x, v.y, v.z);
}

double vec_dotprod(vec_t a, vec_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vec_norm(vec_t a) {
    return sqrt(vec_dotprod(a, a));
}

vec_t vec_rand_init() {
    vec_t vec;
    vec.x = drand48() * 15 * ((rand() % 10) - 5);
    vec.y = drand48() * 15 *((rand() % 10) - 5);
    vec.z = 2;
    return vec;
}