#ifndef LUZ_H
#define LUZ_H

#include "vector.h"
#include "color.h"

typedef struct {
    vec_t pos;
    color_t color;
    bool puntual;
} luz_t;

#endif