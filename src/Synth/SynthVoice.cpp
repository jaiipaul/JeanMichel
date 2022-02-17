#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition){
    VCO0.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    VCO1.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    VCO2.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    ADSR1.noteOn();
    ADSR2.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff){
    ADSR1.noteOff();
    ADSR2.noteOff();
    if( !allowTailOff || (!ADSR1.isActive() || !ADSR2.isActive())){
        clearCurrentNote();
    }
}   

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){

}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels){
    juce::dsp::ProcessSpec specs;
    specs.sampleRate       = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels      = numOutputChannels;


    ADSR1.setSampleRate(2*sampleRate);
    ADSR2.setSampleRate(2*sampleRate);
    
    LFO1.prepare(specs);
    LFO2.prepare(specs);

    VCO0.prepare(specs);
    VCO1.prepare(specs);
    VCO2.prepare(specs);
    
    MIX.prepare(specs);
    
    VCF.prepare(128000.f, specs.numChannels);
    
    VCA.prepare(specs);
    
    isPrepared = true;
}

void SynthVoice::update(juce::AudioProcessorValueTreeState& _params){
    ADSR1.Update(_params);
    ADSR2.Update(_params);
    
    LFO1.Update(_params);
    LFO2.Update(_params);

    VCO0.Update(_params);
    VCO1.Update(_params);
    VCO2.Update(_params);
    
    MIX.Update(_params);
    
    VCF.Update(_params);
    
    VCA.Update(_params);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    jassert(isPrepared);
    
    if(!isVoiceActive()) return;
    
    voiceBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    voiceBuffer.clear();

    std::vector<juce::dsp::AudioBlock<float>> VCO_blocks;
    
    juce::dsp::AudioBlock<float> audioBlock { voiceBuffer };
    LFO1.generateBlock(numSamples);
    LFO2.generateBlock(numSamples);

    VCO0.generateBlock(numSamples);
    VCO1.generateBlock(numSamples);
    VCO2.generateBlock(numSamples);

    VCO_blocks.push_back(VCO0.getBlock());
    VCO_blocks.push_back(VCO1.getBlock());
    VCO_blocks.push_back(VCO2.getBlock());

    MIX.process(audioBlock, VCO_blocks);
    
    VCF.process(audioBlock);
    
    VCA.process(audioBlock);
    
    for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++){
        outputBuffer.addFrom(channel, startSample, voiceBuffer, channel, 0, numSamples);

        if(!ADSR1.isActive() || !ADSR2.isActive()){
            clearCurrentNote();
        }
    }
}
