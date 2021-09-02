#ifndef NETPBM_H
#define NETPBM_H

#define PI 3.14159265359

//returns the distance between two points.
double distance(float x0, float y0, float x1, float y1);

//returns a scaled sine in t - f(t)= (m/2)(sin(2πft)+1)
int scaled_sin(double t, float f, int max);

#endif