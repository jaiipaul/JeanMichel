#include "VCO.h"
#include "WaveFunctions.h"

using namespace SynthModules;

VCO::VCO(std::string _ModuleID)
    : lfo(SynthModules::LFO("dump")){
    ModuleID = _ModuleID;
    hasLFO = false;
}

VCO::VCO(std::string _ModuleID, SynthModules::LFO& _lfo)
    : lfo(_lfo) {
    ModuleID = _ModuleID;
    hasLFO = true;
}

VCO::~VCO(){

}
void VCO::prepare(juce::dsp::ProcessSpec& spec){
    Specs = spec;
    vco_buffer.setSize(spec.numChannels, spec.maximumBlockSize, false, false, true);
    vco_buffer.clear();

    Phase.init();
    PulseWidth = 0.5f;
}

void VCO::generateBlock(){
    juce::dsp::AudioBlock<float> vco_block { vco_buffer };
    //std::cout << "Generating block of " << ModuleID << std::endl;
    for(int s = 0; s < (int)Specs.maximumBlockSize; s++){
        //std::cout << "Generating sample " << s << " of " << ModuleID << std::endl;
        generateSample(s, vco_block);
    }

}

void VCO::generateSample(int sampleIdx, juce::dsp::AudioBlock<float> vco_block){
    float value = 0;
    float FrequencyMod = hasLFO ? LFO_Freq_intensity*MaxFreqMod*lfo.getValueAt(sampleIdx) + Frequency*std::pow(2.f, Detune/12.f)  : Frequency*std::pow(2.f, Detune/12.f) ;
    float PulseWidthMod = hasLFO ? (LFO_Pw_intensity*MaxPwMod*lfo.getValueAt(sampleIdx) + PulseWidth) : PulseWidth;

    //std::cout << ModuleID << " : " << FrequencyMod << " / " << PulseWidthMod << std::endl;
    switch(WaveForm){
        case 1: /*SAW*/
            value = Phase.phase*2.f-1.f;
            break;
        case 2: /*TRIANGLE*/
            value = 1.f-fabs(Phase.phase-0.5f)*4.f;
            break;
        case 3: /*SQUARE*/
            value  = (Phase.phase < PulseWidthMod) ? 1.f : -1.f;
            break;
        case 4: /*SINE*/
            value = sin(juce::MathConstants<float>::twoPi*Phase.phase);
    }
    Phase.advance((float)Specs.sampleRate, FrequencyMod);
    
    for(int ch = 0; ch < (int)Specs.numChannels; ch++)
        vco_block.setSample(ch, sampleIdx, value); 
    
    //std::cout << Phase.phase << std::endl;
}

juce::dsp::AudioBlock<float> VCO::getBlock(){
    juce::dsp::AudioBlock<float> vco_block { vco_buffer };
    //std::cout << vco_block.getSample(0, 0) << std::endl;
    return(vco_block);
}

void VCO::Update(juce::AudioProcessorValueTreeState& params){
    auto& wave      = *params.getRawParameterValue( ModuleID +"Wave");
    switchWaveForm((int)wave.load());

    if( params.getParameter( ModuleID +"LFO_Freq_intensity") != nullptr){
        auto& lfo_freq_int      = *params.getRawParameterValue( ModuleID +"LFO_Freq_intensity");
        LFO_Freq_intensity = lfo_freq_int.load();
    }else{
        LFO_Freq_intensity = 0.0f;
    }
    
    if( params.getParameter( ModuleID +"LFO_Pw_intensity") != nullptr){
        auto& lfo_pw_int      = *params.getRawParameterValue( ModuleID +"LFO_Pw_intensity");
        LFO_Pw_intensity = lfo_pw_int.load();
    }else{
        LFO_Pw_intensity = 0.0f;
    }

    if( params.getParameter( ModuleID +"OctaveDown") != nullptr){
        auto& oct      = *params.getRawParameterValue( ModuleID +"OctaveDown");
        Octave = -(int)oct.load();
    }else if( params.getParameter( ModuleID +"OctaveUp") != nullptr){
        auto& oct      = *params.getRawParameterValue( ModuleID +"OctaveUp");
        Octave = (int)oct.load();
    }else{
        Octave = 0;
    }

    if( params.getParameter( ModuleID +"Detune") != nullptr){
        auto& det      = *params.getRawParameterValue( ModuleID +"Detune");
        Detune = det.load();
    }else{
        Detune = 0.f;
    }   
}

void VCO::switchWaveForm(const int type){
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

void VCO::setFrequency(float freq){
    Frequency = freq* std::pow(2.f, Octave);
    //std::cout << Frequency << std::endl;
}