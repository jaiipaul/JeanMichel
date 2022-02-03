#include "ADSR.h"

//using namespace SynthModules;

SynthModules::ADSR::ADSR(std::string _ModuleID){
    ModuleID = _ModuleID;
}

SynthModules::ADSR::~ADSR(){

}

void SynthModules::ADSR::Update(juce::AudioProcessorValueTreeState& params){
    auto& attack  = *params.getRawParameterValue( ModuleID +"Attack");
    auto& decay   = *params.getRawParameterValue( ModuleID +"Decay");
    auto& sustain = *params.getRawParameterValue( ModuleID +"Sustain");
    auto& release = *params.getRawParameterValue( ModuleID +"Release");

    adsrParams.attack  = attack.load();
    adsrParams.decay   = decay.load();
    adsrParams.sustain = sustain.load();
    adsrParams.release = release.load();

    setParameters(adsrParams);
}
