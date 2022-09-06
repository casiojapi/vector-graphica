#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"
#include "color.h"

typedef struct {
    vec_t pos;
    color_t color;
    bool puntual;
} light_t;

#endif