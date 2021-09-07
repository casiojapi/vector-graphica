
#include <stdlib.h>
#include "color.h"
#include "vector.h"


color_t color_init_rgb(double r, double g, double b) {
    color_t c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

color_t color_random_init() {
    color_t c;
    c.r = drand48();
    c.g = drand48();
    c.b = drand48();
    return c;
}

color_t color_sumar(color_t c, color_t m, double p) {
    return (color_t){c.r + p * m.r, c.g + p * m.g, c.b + p * m.b};
}

color_t color_absorber(color_t b, color_t c) {
    return (color_t){b.r  * c.r, b.g * c.g, b.b * c.b};
}

