#include "LadderFilter.h"

using namespace SynthModules;

SynthModules::LadderFilter::LadderFilter(std::string _ModuleID, SynthModules::ADSR& _adsr, SynthModules::LFO& _lfo)
    : adsr (_adsr), lfo(_lfo){
    ModuleID = _ModuleID;
}

LadderFilter::~LadderFilter(){

}

void LadderFilter::prepare(float _sampleRate, int channels){
    sampleRate = _sampleRate;
    StageFeedbacks = (float*)calloc(4*channels, sizeof(float));
    StageOutputs = (float*)calloc(4*channels, sizeof(float));
    StageT = (float*)calloc(4*channels, sizeof(float));
    for(int ch = 0; ch < channels; ch++){
        for(int stage = 0; stage < 4; stage++){
            StageOutputs[ch*4 + stage] = 0.f;
            StageFeedbacks[ch*4 + stage] = 0.f;
            StageT[ch*4 + stage] = 0.f;
        }
    }
}

void LadderFilter::process(juce::dsp::AudioBlock<float> block){
    for(int s = 0; s < block.getNumSamples(); s++){
        ComputeCoef(s);
        for(int ch = 0; ch < block.getNumChannels(); ch++){
            

            float X = Drive*block.getSample(ch, s) + 4*resonance*StageOutputs[ch*4+3];

            float Stage0 = -G*(tanh( X/(2*Vt)) + StageT[ch*4]);
            StageOutputs[ch*4] += (Stage0 + StageFeedbacks[ch*4]) / (2.f *  sampleRate);
            StageFeedbacks[ch*4] = Stage0;
            StageT[ch*4] = tanh(StageOutputs[ch*4]/(2*Vt));

            float Stage1 = G*(StageT[ch*4] - StageT[ch*4+1]);
            StageOutputs[ch*4+1] += (Stage1 + StageFeedbacks[ch*4+1]) / (2.f *  sampleRate);
            StageFeedbacks[ch*4+1] = Stage1;
            StageT[ch*4+1] = tanh(StageOutputs[ch*4+1]/(2*Vt));

            float Stage2 = G*(StageT[ch*4+1] - StageT[ch*4+2]);
            StageOutputs[ch*4+2] += (Stage2 + StageFeedbacks[ch*4+2]) / (2.f *  sampleRate);
            StageFeedbacks[ch*4+2] = Stage2;
            StageT[ch*4+2] = tanh(StageOutputs[ch*4+2]/(2*Vt));

            float Stage3 = G*(StageT[ch*4+2] - StageT[ch*4+3]);
            StageOutputs[ch*4+3] += (Stage3 + StageFeedbacks[ch*4+3]) / (2.f *  sampleRate);
            StageFeedbacks[ch*4+3] = Stage3;
            StageT[ch*4+3] = tanh(StageOutputs[ch*4+3]/(2*Vt));

            block.setSample(ch, s, StageOutputs[ch*4+3]);
        }
    }  
}   

void LadderFilter::Update(juce::AudioProcessorValueTreeState& params){

    auto& cut   = *params.getRawParameterValue( ModuleID +"Cutoff");
    auto& reso  = *params.getRawParameterValue( ModuleID +"Resonance");
    auto& dr    = *params.getRawParameterValue( ModuleID +"Drive");
    auto& env_int   = *params.getRawParameterValue( ModuleID +"ENV_intensity");
    auto& lfo_int   = *params.getRawParameterValue( ModuleID +"LFO_intensity");
    cutoff    = cut.load();
    resonance = reso.load();
    Drive     = dr.load();
    ENV_intensity = env_int.load();
    LFO_intensity = lfo_int.load();
}
void LadderFilter::ComputeCoef(int sampleIdx){
    //float Env = ENV_intensity * adsr.getNextSample() ;
    float Mod = LFO_intensity * 5000.f * lfo.getValueAt(sampleIdx);
    float cutMax = ENV_intensity * (25000.f - cutoff);
    float cut = (cutoff + Mod) + cutMax*adsr.getNextSample();
    
    float w0 =  (2.f * juce::MathConstants<float>::pi * cut);
    float x = (juce::MathConstants<float>::pi * cut)/sampleRate;

    G = 2.f * Vt * w0 * (1.f - x)/(1.f + x);
}