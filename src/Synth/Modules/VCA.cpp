#include "VCA.h"

using namespace SynthModules;

SynthModules::VCA::VCA(std::string _ModuleID, SynthModules::ADSR& _adsr)
    : adsr (_adsr) {
    ModuleID = _ModuleID;
}

VCA::~VCA(){

}

void VCA::prepare(const juce::dsp::ProcessSpec &spec) noexcept {
    gain.prepare(spec);
}

void VCA::process(juce::dsp::AudioBlock<float> block){
    for(int s = 0; s < block.getNumSamples(); s++){
        float env_sample = adsr.getNextSample();
        for(int ch = 0; ch < block.getNumChannels(); ch++){
            //std::cout << env_sample << std::endl;
            auto nextSample = ENV_intensity * env_sample * gain.processSample(block.getSample(ch, s));
            block.setSample(ch, s, nextSample);
        }
    }  
}   


void VCA::Update(juce::AudioProcessorValueTreeState& params){
    auto& vol      = *params.getRawParameterValue( ModuleID +"Volume");
    auto& env_int  = *params.getRawParameterValue( ModuleID +"ENV_intensity");

    Volume  = vol.load();
    ENV_intensity  = env_int.load();

    gain.setGainLinear(Volume);
}