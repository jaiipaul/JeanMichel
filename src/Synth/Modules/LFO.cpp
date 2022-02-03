#include "LFO.h"
#include "WaveFunctions.h"

using namespace SynthModules;

LFO::LFO(std::string _ModuleID){
    ModuleID = _ModuleID;
}

LFO::~LFO(){

}

void LFO::prepare(juce::dsp::ProcessSpec& spec){
    Specs = spec;
    lfo_buffer.setSize(1, spec.maximumBlockSize, false, false, true);
    lfo_buffer.clear();
    Phase.init();
}

void LFO::Update(juce::AudioProcessorValueTreeState& params){
    auto& wave      = *params.getRawParameterValue( ModuleID +"Wave");
    auto& rate      = *params.getRawParameterValue( ModuleID +"Rate");
    Frequency = rate.load();
    switchWaveForm((int)wave.load());
}
        
        
float LFO::getValueAt(int sampleIdx){
    //std::cout << lfo_buffer.getSample(0, sampleIdx)<< std::endl;
    return(lfo_buffer.getSample(0, sampleIdx));
}

void LFO::generateBlock(){
    juce::dsp::AudioBlock<float> lfo_block { lfo_buffer };
    //std::cout << "Generating block of " << ModuleID << std::endl;
    for(int s = 0; s < (int)Specs.maximumBlockSize; s++){
        //std::cout << "Generating sample " << s << " of " << ModuleID << std::endl;
        generateSample(s, lfo_block);
    }

}   

void LFO::generateSample(int sampleIdx, juce::dsp::AudioBlock<float> lfo_block){
    float value = 0;

    switch(WaveForm){
        case 1: /*SAW*/
            value = Phase.phase*2.f-1.f;
            break;
        case 2: /*TRIANGLE*/
            value = 1.f-fabs(Phase.phase-0.5f)*4.f;
            break;
        case 3: /*SQUARE*/
            value  = (Phase.phase < 0.5f) ? 1.f : -1.f;
            break;
        case 4: /*SINE*/
            value = sin(juce::MathConstants<float>::twoPi*Phase.phase);
    }
    Phase.advance((float)Specs.sampleRate, Frequency);

    lfo_block.setSample(0, sampleIdx, value); 
}

void LFO::switchWaveForm(const int type){
    switch(type){
        case 1 :
            WaveForm = 1;
            break;
        
        case 2 :
            WaveForm = 2;
            break;

        case 3 :
            WaveForm = 3;
            break;
            
        case 4 :
            WaveForm = 4;
            break;

        default :
            jassertfalse;
            break;
    }
}