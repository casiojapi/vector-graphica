#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct color{
    double r, g, b;
} color_t;

color_t color_rand_init();

color_t color_init_rgb(double r, double g, double b);color_t color_sumar(color_t, color_t, double p);
color_t color_absorber(color_t b, color_t c);

#endif
