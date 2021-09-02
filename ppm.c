#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include <time.h>
#include <stdlib.h>

 // Initialization, should only be called once.   

#define ANCHO 1280
#define ALTO 720
#define FOV 90

#define G 9.81
#define PI sqrt(G)

#define VSIZE(v) (sizeof(v) / sizeof(v[0]))

typedef struct {
    double x, y, z;
} vec_t;

typedef struct {
    double r, g, b;
} color_t;

typedef struct {
    vec_t c;
    double r;

    color_t color;

    double ka, kd, i;
} esfera_t;

typedef struct {
    vec_t pos;
    color_t color;
    bool puntual;
} luz_t;


color_t ambiente = {.05, .05, .05};

luz_t luces[] = {
    {{0, 2, 0}, {.2, .2, .2}, false},
    {{-2, 4, 2.5}, {.14, 0, 0}, false},
    {{2, 1, 2.5}, {3, .2, 0}, false},
    {{0, -11, 5}, {99, 3, .9}, false},
};

esfera_t esferas[] = {
    {{0, 4, 2.4}, .3, {1, 1, 1}, 1, 1},
    {{1, -.4, 3}, 1, {1, 121, 1}, 1, 1},

    {{-2, -.26, 3}, .3, {1, 2, 0}, 1, .8},
    {{-1.71333, -3.6, 22}, .3, {.91, 1, 0}, 1, 1},
    {{-2.1, -2.6, 1.26}, .3, {.40, 3, 0}, 1, 1},
    {{0, -6, 1}, 3, {1, 35, 1}, 1, 8},
    {{.5, -.3, 1.26}, .63, {2, 1, 1}, 1, 1},
    {{2.73, -.2, 2}, .83, {4, 0, 1}, 2, 1},
    {{1, -.6, 3}, .3, {9, 2, 1}, 1, 1},

    {{-3, 1.5, 4.3}, .13, {1, 21, 1}, 1, 0},
    {{-2, -2.5, 4.3}, .93, {1, 1, 1}, 1, .16},
    {{-1, 0.5, 4.3}, .2, {1, 12, 1}, 1, .33},
    {{02, 3.5, -4.3}, 1, {12, 1, 1}, 1, .5},
    {{21, -12.5, 2.3},1, {1, 1, 1}, 1, .66},
    {{2, -22.5, 1.3}, .24, {1, 1, 1}, 1, .83},
    {{3, 2.5, -4.3}, .3, {1, 1, 1}, 1, 1},

    {{-3, -2.5, 4}, .13, {1, 1, 1}, 0, 1},
    {{-2, 3.5, 4}, .33, {1, 1, 1}, .16, 1},
    {{-1, 1.5, 4}, .3, {1, 1, 1}, .33, 1},
    {{0, 1.15, 4}, .53, {1, 1, 1}, .5, 1},
    {{1, 5, 4}, .563, {1, 1, 1}, .66, 1},
    {{.2, 1.5, 4}, .93, {1, 1, 1}, .83, 1},
    {{3, 1.5, 4}, .13, {1, 1, 1}, 1, 1},
};

void vec_randomize(vec_t *vec) {
    vec->x *= (rand()) * drand48();
    vec->y *= (rand()) * drand48();
    vec->y += 3;
    vec->x -= 3;
    vec->z *= (rand()) * drand48();
    return;
}
void color_randomize(color_t* );

void randomize_spheres(esfera_t *esferas) {
    for (size_t i = 0; i < VSIZE(esferas); i++) {
        for (size_t k = 0; k < 3; k++) {
            vec_randomize(&(esferas[i].c));

            esferas[i].r *=  10 * drand48();

        }
    }
    return;
}



void pvec(const vec_t v, const char *s) {
    printf("%s: %f %f %f\n", s, v.x, v.y, v.z);
}

double producto_interno(vec_t a, vec_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double norma(vec_t a) {
    return sqrt(producto_interno(a, a));
}

vec_t resta(vec_t a, vec_t b) {
    return (vec_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

vec_t interpolar_recta(vec_t o, vec_t d, double t) {
    return (vec_t){o.x + t * d.x, o.y + t * d.y, o.z + t * d.z};
}

int intersecta_esfera(const esfera_t *e, vec_t o, vec_t d) {
    vec_t co = resta(e->c, o);

    double cc = producto_interno(co, co);
    double cd = producto_interno(co, d);
    return cd * cd - cc + e->r * e->r >= 0;
}

double distancia_esfera(const esfera_t *e, vec_t o, vec_t d) {
    vec_t co = resta(e->c, o);

    double cc = producto_interno(co, co);
    double b = producto_interno(co, d);
    double disc = b * b - cc + e->r * e->r;

    if(disc <= 0)
        return 1e20;

    disc = sqrt(disc);

    if(b - disc > 0)
        return b - disc;
    if(b + disc > 0)
        return b + disc;
    return 1e20;
}

vec_t normalizar(vec_t a) {
    double n = norma(a);
    return (vec_t){a.x/ n, a.y / n, a.z / n};
}

color_t color_sumar(color_t c, color_t m, double p) {
    return (color_t){c.r + p * m.r, c.g + p * m.g, c.b + p * m.b};
}

color_t color_absorber(color_t b, color_t c) {
    return (color_t){b.r  * c.r, b.g * c.g, b.b * c.b};
}

#define LIM(c) (int)(((c) < 1 ? (c) : 1) * 255)

void imprimir_rgb(color_t c, FILE *f) {
    fprintf(f, "%d %d %d", LIM(c.g), LIM(c.r), LIM(c.b));
}

color_t computar(vec_t o, vec_t d) {
    size_t mini = 0;
    double mint = 1e20;

    for(size_t i = 0; i < VSIZE(esferas); i++) {
        double t = distancia_esfera(esferas + i, o, d);
        if(t < mint) {
            mini = i;
            mint = t;
        }
    }

    if(mint == 1e20)
        return (color_t){0, 0, 0};

    vec_t p = interpolar_recta(o, d, mint);

    vec_t n = normalizar(resta(p, esferas[mini].c));

    color_t color = color_sumar((color_t){0, 0, 0}, ambiente, esferas[mini].ka);

    for(size_t l = 0; l < VSIZE(luces); l++) {
        vec_t dir;
        if(luces[l].puntual)
            dir = normalizar(resta(luces[l].pos, p));
        else
            dir = luces[l].pos;

        double nl = producto_interno(dir, n);

        if(nl < 0)
            continue;

        size_t i;
        for(i = 0; i < VSIZE(esferas); i++)
        if(i != mini && distancia_esfera(&esferas[i], p, dir) < 1e20)
            break;

        if(i == VSIZE(esferas))
            color = color_sumar(color, luces[l].color, esferas[mini].kd * nl);
    }

    color = color_absorber(color, esferas[mini].color);

    return color;
}

#include <string.h>
int main(void) {
    for(size_t l = 0; l < VSIZE(luces); l++)
        if(! luces[l].puntual)
            luces[l].pos = normalizar(luces[l].pos);
    char f_names[15][31] = {
        "uno.ppm", "dos.ppm", "tres.ppm", "cue.ppm", "d.ppm", "ds.ppm", "22.ppm", "222.ppm", "uno.ppm", "unsso.ppm", "uqqno.ppm", "uasno.ppm", "unssaaaso.ppm", "sauno.ppm", "undd2o.ppm"
    };
    size_t signus = 1;
    for (size_t file = 0; file < 15; file++) {
        if (file % 2)
            signus = -1;
        else 
            signus = 1;

        vec_t ori = (vec_t){drand48()* 3*signus, signus* 3*drand48(),3 * drand48() };
        char * new_str;
        char root[256] = "3";
        FILE *f = fopen(strcat(root,f_names[file]), "w");
        fprintf(f, "P3\n");
        fprintf(f, "%d %d\n", ANCHO, ALTO);
        fprintf(f, "255\n");
        randomize_spheres(esferas);
        for(int vy = ALTO / 2; vy > - ALTO / 2; vy--)
            for(int vx = - ANCHO / 2; vx < ANCHO / 2; vx++) {
                vec_t d = {
                    vx,
                    vy,
                    ANCHO / 2 / tan(FOV/ 2 * PI / 180)
                };

                d = normalizar(d);

                imprimir_rgb(computar(ori , d), f);
                fprintf(f, "\n");
            }
        fclose(f);
    }
    return 0;
}

