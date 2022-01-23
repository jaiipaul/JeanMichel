#include "WaveFunctions.h"
#include <math.h>

float genSAW(float x){
    return( x*2.f-1.f );
}

float genTRI(float x){
    return( 1.f-fabs(x-0.5f)*4.f );
}

float genSQR(float x){
    return((x < 0.f) ? 1.f : -1.f);
}

float genSINE(float x){
    return( (float)sin(x) );
}