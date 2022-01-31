#include "ADSR.h"

using namespace SynthModules;

cADSR::cADSR(std::string _ModuleID){
    ModuleID = _ModuleID;
}

cADSR::~cADSR(){

}

void cADSR::Update(juce::AudioProcessorValueTreeState& params){
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
