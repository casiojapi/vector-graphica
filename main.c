#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common/color.h"
#include "common/vec.h"
#include "common/sphere.h"
#include "common/light.h"
#include "common/define.h"

#define USAGE "wrong arguments.\nusage: ./vector-graphica [-w <N>] [-h <N>] [-f <N>] [-n <N>] [-x <N>]\n"

#define G 9.81
#define PI sqrt(G)

#define VSIZE(v) (sizeof(v) / sizeof(v[0]))

light_t lights[N_LIGHTS];
sphere_t spheres[N_SPHERES];

void init_lights(light_t* l, size_t n) {
    for (size_t i = 0; i < n; i++) {
        l[i].pos = vec_rand_init();
        l[i].pos.z += 0.5 * (ORIGIN + 1);
        l[i].color = color_rand_init();
        l[i].puntual = i % 2;
    }
}

void init_spheres(sphere_t* e, size_t n) {
    for (size_t i = 0; i < n; i++) {
        e[i].r = (drand48() * 0.35) + 0.35;
        e[i].c = vec_rand_init();
        e[i].color = color_rand_init();
        e[i].ka = drand48();
        e[i].kd = drand48();
        e[i].i = i;
        //printf("%f %f %f\n", e[i].c.x, e[i].c.y, e[i].c.z);
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

    for (size_t i = 0; i < N_SPHERES; i++) {
        double t = sphere_distance(spheres + i, o, d);
        if(t < mint) {
            mini = i;
            mint = t;
        }
    }

    if (mint == 1e20)
        return wallpaper;

    vec_t p = inter_line(o, d, mint);

    vec_t n = vec_normalize(vec_diff(p, spheres[mini].c));

    color_t color = color_sumar((color_t){0, 0, 0}, ambiente, spheres[mini].ka);

    for (size_t l = 0; l < N_LIGHTS; l++) {
        vec_t dir;
        if (lights[l].puntual)
            dir = vec_normalize(vec_diff(lights[l].pos, p));
        else
            dir = lights[l].pos;

        double nl = vec_dotprod(dir, n);
        if (nl < 0)
            continue;

        size_t i;
        for (i = 0; i < N_SPHERES; i++)
        if (i != mini && sphere_distance(&spheres[i], p, dir) < 1e20)
            break;

        if (i == N_SPHERES)
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
        sprintf(strs[i], "renders/%zd_%d.ppm", i +1, val_a );
        strs[i][strlen(strs[i])] = '\0';
    }
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    printf("starting vector-graphica.");
    uint16_t width = WIDTH;
    uint16_t height = HEIGHT;
    uint16_t fov = FOV;
    uint16_t n_files = N_FILES;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-' || strlen(argv[i]) != 2) {
            fprintf(stderr, USAGE);
            return 1;
        }
        switch (argv[i][1]) {
            case 'w':
                ++i;
                if (i >= argc) {
                    fprintf(stderr, USAGE);
                    return 1;
                }
                width = (uint16_t) atoi(argv[i]);
                break;
            case 'h':
                ++i;
                if (i >= argc) {
                    fprintf(stderr, USAGE);
                    return 1;
                }
                height = (uint16_t) atoi(argv[i]);
                break;
            case 'f':
                ++i;
                if (i >= argc) {
                    fprintf(stderr, USAGE);
                    return 1;
                }
                fov = (uint16_t) atoi(argv[i]);
                break;
            case 'n':
                ++i;
                if (i >= argc) {
                    fprintf(stderr, USAGE);
                    return 1;
                }
                n_files = (uint16_t) atoi(argv[i]);
                if (n_files < 1) {
                    fprintf(stderr, USAGE);
                    return 1;
                }
                break;
            case 'x':
                ++i;
                if (i >= argc) {
                    fprintf(stderr, USAGE);
                    return 1;
                }
                srand(atoi(argv[i]));
                break;
        }
    }


    char f_names[n_files][256];
    init_strs(f_names, n_files);
    printf("\n");

    size_t file = 0;

    for (size_t file = 0; file < n_files; file++) {
        printf("setting up file: %zd/%hu\t", file + 1, n_files);

        init_lights(lights, N_LIGHTS);

        for(size_t l = 0; l < N_LIGHTS; l++)
            if(! lights[l].puntual)
                lights[l].pos = vec_normalize(lights[l].pos);

        init_spheres(spheres, N_SPHERES);

        // SET ORIGIN
        vec_t origin = (vec_t){0,0, ORIGIN};

        FILE *f = fopen(f_names[file], "w");

        fprintf(f, "P3\n");
        fprintf(f, "%d %d\n", width, height);
        fprintf(f, "255\n");

        color_t paper = color_rand_init();

        for(int vy = height / 2; vy > - height / 2; vy--) {
            for(int vx = - width / 2; vx < width / 2; vx++) {
                vec_t d = {
                    vx,
                    vy,
                    width / 2 / tan(fov/ 2 * PI / 180)
                };

                d = vec_normalize(d);

                imprimir_rgb(computar(origin , d, paper), f);
                fprintf(f, "\n");
            }
        }
        printf("\n");

        fclose(f);
    }
    return 0;
}
