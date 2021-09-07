#ifndef ESFERA_H
#define ESFERA_H

#include "color.h"
#include "vector.h"

typedef struct esfera {
    vec_t c;
    double r;
    color_t color;
    double ka, kd, i;
} esfera_t;


int intersecta_esfera(const esfera_t *e, vec_t o, vec_t d);
double distancia_esfera(const esfera_t *e, vec_t o, vec_t d);

#endif
