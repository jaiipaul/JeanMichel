#include "WaveFunctions.h"
#include <JuceHeader.h>
#include <math.h>

float genSAW(float x){
    float t = x/juce::MathConstants<float>::pi;
    return( t*2.f-1.f );
}

float genTRI(float x){
    float t = x/juce::MathConstants<float>::pi;
    return( 1.f-fabs(t-0.5f)*4.f );
}

float genSQR(float x){
    float t = x/juce::MathConstants<float>::pi;
    return((t < 0.f) ? 1.f : -1.f);
}

float genSINE(float x){
    return( (float)sin(x) );
}