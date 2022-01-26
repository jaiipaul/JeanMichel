#include "VCA.h"
#include "WaveFunctions.h"

using namespace SynthModules;

VCA::VCA(){
}

VCA::~VCA(){

}

void VCA::prepare(const juce::dsp::ProcessSpec &spec) noexcept {
    gain.prepare(spec);
}

void VCA::process(juce::dsp::AudioBlock<float> block){
    gain.process(juce::dsp::ProcessContextReplacing<float> ( audioBlock ))
}   
