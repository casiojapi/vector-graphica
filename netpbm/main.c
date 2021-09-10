#include <stdio.h>

#include "netpbm.h"

// ej-1 defines

#define WIDTH 1000
#define HEIGHT 600
#define MAXIMO 255

#define X0 (WIDTH / 2)
#define Y0 (HEIGHT / 2)

#define FRECUENCIA 0.000000134
        
// ej-1 defines

int main(int argc, char const *argv[]){
    if (argc != 2){
        fprintf(stderr, "ARGUMENTS\n");
        return 1;
    }
    FILE *image = fopen(argv[1], "w");
    if (image == NULL){
        fprintf(stderr, "error opening file\n");
        return 1;
    }
    fprintf(image, "P3\n");
    fprintf(image, "%d %d\n %d\n", WIDTH, HEIGHT, MAXIMO);
    for (size_t i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            double val = scaled_sin(distance(i, j , X0, Y0), FRECUENCIA, MAXIMO);
            fprintf(image, "%d\t %d %d\n", (int)(val * .3), (int)(val *.2), (int)(val * .5));
        }
    }
    return 0;
}