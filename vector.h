#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double x, y, z;
} vec_t;


vec_t vec_rand_init();

vec_t normalizar(vec_t a);
vec_t resta(vec_t a, vec_t b);
vec_t interpolar_recta(vec_t o, vec_t d, double t);

void pvec(const vec_t v, const char *s);
double producto_interno(vec_t a, vec_t b);
double norma(vec_t a);

#endif