#ifndef SPHERE_H
#define SPHERE_H

#include "color.h"
#include "vec.h"

typedef struct sphere {
    vec_t c;
    double r;
    color_t color;
    double ka, kd, i;
} sphere_t;


int intersecta_esfera(const sphere_t *e, vec_t o, vec_t d);
double sphere_distance(const sphere_t *e, vec_t o, vec_t d);

#endif
