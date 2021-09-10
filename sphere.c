#include <math.h>
#include <stdlib.h>

#include "sphere.h"
#include "vec.h"
#include "color.h"

int sphere_intersect(const sphere_t *e, vec_t o, vec_t d) {
    vec_t co = vec_diff(e->c, o);
    double cc = vec_dotprod(co, co);
    double cd = vec_dotprod(co, d);
    return cd * cd - cc + e->r * e->r >= 0;
}

double sphere_distance(const sphere_t *e, vec_t o, vec_t d) {
    vec_t co = vec_diff(e->c, o);

    double cc = vec_dotprod(co, co);
    double b = vec_dotprod(co, d);
    double disc = b * b - cc + e->r * e->r;

    if (disc <= 0)
        return 1e20;

    disc = sqrt(disc);

    if (b - disc > 0)
        return b - disc;
    if (b + disc > 0)
        return b + disc;

    return 1e20;
}