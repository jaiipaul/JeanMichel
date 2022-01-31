#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition){
    VCO1.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    ADSR1.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff){
    ADSR1.noteOff();
    if( !allowTailOff || !ADSR1.isActive()){
        clearCurrentNote();
    }
}   

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){

}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels){
    ADSR1.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec specs;
    specs.sampleRate       = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels      = numOutputChannels;

    VCO1.prepare(specs);
    VCO1.setFrequency(440.f);
    gain.prepare(specs);
    gain.setGainLinear(0.1f);

    juce::ADSR::Parameters initParams;
    initParams.attack = 0.f;
    initParams.decay = 0.f;
    initParams.sustain = 0.f;
    initParams.release = 0.f;
    ADSR1.setParameters(initParams);
    
    isPrepared = true;
}

void SynthVoice::update(juce::AudioProcessorValueTreeState& _params){
    ADSR1.Update(_params);
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    jassert(isPrepared);
    
    if(!isVoiceActive()) return;
    
    voiceBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    voiceBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock { voiceBuffer };
    VCO1.process(juce::dsp::ProcessContextReplacing<float> ( audioBlock ));
    gain.process(juce::dsp::ProcessContextReplacing<float> ( audioBlock ));
    ADSR1.applyEnvelopeToBuffer(voiceBuffer, 0, voiceBuffer.getNumSamples());

    for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++){
        outputBuffer.addFrom(channel, startSample, voiceBuffer, channel, 0, numSamples);

        if(!ADSR1.isActive()){
            clearCurrentNote();
        }
    }

    
}
