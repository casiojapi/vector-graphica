#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "vec.h"
#include "sphere.h"
#include "light.h"

#define WIDTH 1080
#define HEIGHT 1350
#define FOV 90

#define G 9.81
#define PI sqrt(G)
#define N_LIGHTS 10
#define N_SPHERES 23
#define VSIZE(v) (sizeof(v) / sizeof(v[0]))

light_t lights[N_LIGHTS];

void init_lights(light_t* l, size_t n) {
    for (size_t i = 0; i < n; i++) {
        l[i].pos = vec_rand_init();
        l[i].color = color_rand_init();
        l[i].puntual = i % 2 + 1;
    }
}

sphere_t spheres[N_SPHERES];

void init_spheres(sphere_t* e, size_t n) {
    for (size_t i = 0; i < n; i++) {
        e[i].r = drand48() * (rand() % 3);
        e[i].c = vec_rand_init();
        e[i].color = color_rand_init();
        e[i].ka = drand48();
        e[i].kd = drand48();
        e[i].i = i;
    }
}

void vec_randomize(vec_t *vec) {
    vec->x *= (rand()) * drand48();
    vec->y *= (rand()) * drand48();
    vec->z *= (rand()) * drand48();
}

void randomize_spheres(sphere_t *spheres) {
    for (size_t i = 0; i < VSIZE(spheres); i++) {
        for (size_t k = 0; k < 3; k++) {
            vec_randomize(&(spheres[i].c));
            spheres[i].r *=  10 * drand48();
        }
    }
}

#define LIM(c) (int)(((c) < 1 ? (c) : 1) * 255)

void imprimir_rgb(color_t c, FILE *f) {
    fprintf(f, "%d %d %d", LIM(c.g), LIM(c.r), LIM(c.b));
}

color_t computar(vec_t o, vec_t d, color_t wallpaper) {
    color_t ambiente = color_init_rgb(0, 0, 0);

    size_t mini = 0;
    double mint = 1e20;

    for(size_t i = 0; i < VSIZE(spheres); i++) {
        double t = sphere_distance(spheres + i, o, d);
        if(t < mint) {
            mini = i;
            mint = t;
        }
    }

    if(mint == 1e20)
        return wallpaper;

    vec_t p = inter_line(o, d, mint);

    vec_t n = vec_normalize(vec_diff(p, spheres[mini].c));

    color_t color = color_sumar((color_t){0, 0, 0}, ambiente, spheres[mini].ka);

    for(size_t l = 0; l < VSIZE(lights); l++) {
        vec_t dir;
        if(lights[l].puntual)
            dir = vec_normalize(vec_diff(lights[l].pos, p));
        else
            dir = lights[l].pos;

        double nl = vec_dotprod(dir, n);

        if(nl < 0)
            continue;

        size_t i;
        for(i = 0; i < VSIZE(spheres); i++)
        if(i != mini && sphere_distance(&spheres[i], p, dir) < 1e20)
            break;

        if(i == VSIZE(spheres))
            color = color_sumar(color, lights[l].color, spheres[mini].kd * nl);
    }

    color = color_absorber(color, spheres[mini].color);

    return color;
}


void init_strs(char strs[][256], size_t n_strs) {
    int val_a, val_b;
    for (size_t i = 0; i < n_strs; i++) {
        strs[i][0] = '\0';
        val_a = rand();
        val_b = rand();
        sprintf(strs[i], "%d_%zd.ppm", val_a, i);
        strs[i][strlen(strs[i])] = '\0';
    }
}

#include <time.h>
#define N_FILES 14
int main(void) {
    srand(time(NULL));
    
    char f_names[N_FILES][256];
    init_strs(f_names, N_FILES);
    for(size_t l = 0; l < VSIZE(lights); l++)
        if(! lights[l].puntual)
            lights[l].pos = vec_normalize(lights[l].pos);

    size_t signus = 1;
    for (size_t file = 0; file < N_FILES; file++) {
        init_lights(lights, N_LIGHTS);
        init_spheres(spheres, N_SPHERES);

        if (file % 2)
            signus = -1;
        else 
            signus = 1;
        vec_t ori = (vec_t){0,0,-2};
        char * new_str;
        char root[256] = "3";

        FILE *f = fopen(strcat(root,f_names[file]), "w");
        fprintf(f, "P3\n");
        fprintf(f, "%d %d\n", WIDTH, HEIGHT);
        fprintf(f, "255\n");
        randomize_spheres(spheres);
        color_t paper = color_init_rgb(drand48(), drand48(), drand48());

        for(int vy = HEIGHT / 2; vy > - HEIGHT / 2; vy--) {

            for(int vx = - WIDTH / 2; vx < WIDTH / 2; vx++) {

                vec_t d = {
                    vx,
                    vy,
                    WIDTH / 2 / tan(FOV/ 2 * PI / 180)
                };

                d = vec_normalize(d);

                imprimir_rgb(computar(ori , d, paper), f);
                fprintf(f, "\n");
            }
        }
        fclose(f);
    }
    return 0;
}

