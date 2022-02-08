#include "MIXER.h"

using namespace SynthModules;

SynthModules::MIXER::MIXER(std::string _ModuleID, int _N_inputs){
    ModuleID = _ModuleID;
    N_inputs = _N_inputs;
}

MIXER::~MIXER(){

}

void MIXER::prepare(const juce::dsp::ProcessSpec &spec) noexcept {
    for(int input = 0; input < N_inputs; input++){
        juce::dsp::Gain<float> gain_i;
        gain_i.prepare(spec);
        Gains.push_back(gain_i);
    }
}

void MIXER::process(juce::dsp::AudioBlock<float> block_out, std::vector<juce::dsp::AudioBlock<float>> blocks_in){
    for(int ch = 0; ch < block_out.getNumChannels(); ch++){
        for(int s = 0; s < block_out.getNumSamples(); s++){
            float nextSample = 0.f;
            float gainSum = 0.f;
            for(int input = 0; input < N_inputs; input++){
                gainSum += Gains[input].getGainLinear();
                nextSample += Gains[input].processSample(blocks_in[input].getSample(ch, s));
            }
            nextSample = nextSample / N_inputs;
            block_out.setSample(ch, s, nextSample);
        }
    }  
}   


void MIXER::Update(juce::AudioProcessorValueTreeState& params){
    for(int input = 0; input < N_inputs; input++){
        auto& vol      = *params.getRawParameterValue( ModuleID +"Volume"+std::to_string(input) );
        Gains[input].setGainLinear(vol.load());
    }    
}