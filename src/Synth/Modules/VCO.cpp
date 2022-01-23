#include "VCO.h"
#include "WaveFunctions.h"

VCO::VCO(){
    SawOsc.initialise(&genSAW);
    TriOsc.initialise(&genTRI);
    SqrOsc.initialise(&genSQR);
    SinOsc.initialise(&genSINE);
}

VCO::~VCO(){

}

void VCO::prepare(const juce::dsp::ProcessSpec &spec) noexcept {
    SawOsc.prepare(spec);
    TriOsc.prepare(spec);
    SqrOsc.prepare(spec);
    SinOsc.prepare(spec);
}

void VCO::process(juce::dsp::AudioBlock<float> block){
    SawOsc.process(juce::dsp::ProcessContextReplacing<float> (block));
    //TriOsc.process(juce::dsp::ProcessContextReplacing<_sType> (block));
    //SqrOsc.process(juce::dsp::ProcessContextReplacing<_sType> (block));
    //SinOsc.process(juce::dsp::ProcessContextReplacing<_sType> (block));
}   

void VCO::setFrequency(float freq){
    SawOsc.setFrequency(freq);
    TriOsc.setFrequency(freq);
    SqrOsc.setFrequency(freq);
    SinOsc.setFrequency(freq);
}