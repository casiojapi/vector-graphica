#define _XOPEN_SOURCE 

#include <stdio.h>
#include <math.h>

#include <time.h>
#include <stdlib.h>

#include "vec.h"
#include "define.h"

vec_t vec_normalize(vec_t a) {
    double n = vec_norm(a);
    return (vec_t){a.x/ n, a.y / n, a.z / n};
}

vec_t vec_diff(vec_t a, vec_t b) {
    return (vec_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec_t inter_line(vec_t o, vec_t d, double t) {
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
    vec.x = drand48() * ((rand() % (WIDTH / 45)) - (WIDTH / 90)) * .45;
    vec.y = drand48() * ((rand() % (HEIGHT / 45)) - (HEIGHT / 90)) * .45;
    vec.z = (rand() % 3) - 3;
    return vec;
}