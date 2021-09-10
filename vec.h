#ifndef VEC_H
#define VEC_H

typedef struct {
    double x, y, z;
} vec_t;


vec_t vec_rand_init();

vec_t vec_normalize(vec_t a);
vec_t vec_diff(vec_t a, vec_t b);
vec_t inter_line(vec_t o, vec_t d, double t);

void vec_print(const vec_t v, const char *s);
double vec_dotprod(vec_t a, vec_t b);
double vec_norm(vec_t a);

#endif