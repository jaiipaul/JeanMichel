#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound *sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition){
    VCO1.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff){
    adsr.noteOff();
    if( !allowTailOff || !adsr.isActive()){
        clearCurrentNote();
    }
}   

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){

}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels){
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec specs;
    specs.sampleRate       = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels      = numOutputChannels;

    VCO1.prepare(specs);
    VCO1.setFrequency(440.f);
    gain.prepare(specs);
    gain.setGainLinear(0.1f);

    adsrParams.attack = 0.01f;
    adsrParams.decay = 0.01f;
    adsrParams.attack = 1.f;
    adsrParams.release = 1.f;

    adsr.setParameters(adsrParams);
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    jassert(isPrepared);
    
    if(!isVoiceActive()) return;
    
    voiceBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    voiceBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock { voiceBuffer };
    VCO1.process(juce::dsp::ProcessContextReplacing<float> ( audioBlock ));
    gain.process(juce::dsp::ProcessContextReplacing<float> ( audioBlock ));
    adsr.applyEnvelopeToBuffer(voiceBuffer, 0, voiceBuffer.getNumSamples());

    for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++){
        outputBuffer.addFrom(channel, startSample, voiceBuffer, channel, 0, numSamples);

        if(!adsr.isActive()){
            clearCurrentNote();
        }
    }

    
}
