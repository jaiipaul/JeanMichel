#include "WaveFunctions.h"
#include <JuceHeader.h>
#include <math.h>

float genSAW(float x){
    return( 1.f - x/juce::MathConstants<float>::pi );
}

float genTRI(float x){
    return( (x < 0.f) ? 1.f+2.f*x/juce::MathConstants<float>::pi :1.f-2.f*x/juce::MathConstants<float>::pi);
}

float genSQR(float x){
    return((x < 0.f) ? 1.f : -1.f);
}

float genSINE(float x){
    return( (float)sin(x) );
}