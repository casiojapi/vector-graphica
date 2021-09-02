#include <stdio.h>
#include <math.h>
#include "netpbm.h"

//pixel = picture element
//PBM = Portable Bit Map
//PGM = Portable Grey Map
//PPM = Portable Pixel Map

// ASCII for PGB = "P2", width, height, max different pixels, and... pixels. 

double distance(float x0, float y0, float x1, float y1){
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
}

int scaled_sin(double t, float f, int max){
    return (max/(double)2) * (sin(2 * PI * f * t) + 1);
}
