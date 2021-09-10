#include <math.h>
#include <stdlib.h>

#include "sphere.h"
#include "vec.h"
#include "color.h"

int intersecta_esfera(const sphere_t *e, vec_t o, vec_t d) {
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

// typedef struct esfera {
//     vec_t c;
//     double r;
//     color_t color;
//     double ka, kd, i;
// } sphere_t;

// sphere_t* spheres_init(size_t n) {
//     sphere_t es[n];
//     for (size_t i = 0; i < n; i++) {
//         es[0].r = (rand() % 10000) *
//     }
// }

// sphere_t spheres[] = {
//     {{0, 4, 2.4}, .3, {1, 1, 1}, 1, 1},
//     {{1, -.4, 3}, 1, {1, 121, 1}, 1, 1},
//     {{-2, -.26, 3}, .3, {1, 2, 0}, 1, .8},
//     {{-1.71333, -3.6, 22}, .3, {.91, 1, 0}, 1, 1},
//     {{-2.1, -2.6, 1.26}, .3, {.40, 3, 0}, 1, 1},
//     {{0, -6, 1}, 3, {1, 35, 1}, 1, 8},
//     {{.5, -.3, 1.26}, .63, {2, 1, 1}, 1, 1},
//     {{2.73, -.2, 2}, .83, {4, 0, 1}, 2, 1},
//     {{1, -.6, 3}, .3, {9, 2, 1}, 1, 1},
//     {{-3, 1.5, 4.3}, .13, {1, 21, 1}, 1, 0},
//     {{-2, -2.5, 4.3}, .93, {1, 1, 1}, 1, .16},
//     {{-1, 0.5, 4.3}, .2, {1, 12, 1}, 1, .33},
//     {{2, 3.5, -4.3}, 1, {12, 1, 1}, 1, .5},
//     {{21, -12.5, 2.3},1, {1, 1, 1}, 1, .66},
//     {{2, -22.5, 1.3}, .24, {1, 1, 1}, 1, .83},
//     {{3, 2.5, -4.3}, .3, {1, 1, 1}, 1, 1},
//     {{-3, -2.5, 4}, .13, {1, 1, 1}, 0, 1},
//     {{-2, 3.5, 4}, .33, {1, 1, 1}, .16, 1},
//     {{-1, 1.5, 4}, .3, {1, 1, 1}, .33, 1},
//     {{0, 1.15, 4}, .53, {1, 1, 1}, .5, 1},
//     {{1, 5, 4}, .563, {1, 1, 1}, .66, 1},
//     {{.2, 1.5, 4}, .93, {1, 1, 1}, .83, 1},
//     {{3, 1.5, 4}, .13, {1, 1, 1}, 1, 1},
// };