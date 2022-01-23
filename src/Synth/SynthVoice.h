#ifndef _SYNTHVOICE_H_
#define _SYNTHVOICE_H_

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Modules/VCO.h"

class SynthVoice : public juce::SynthesiserVoice{
public:
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)override;
    void stopNote (float velocity, bool allowTailOff)override;
    void pitchWheelMoved (int newPitchWheelValue)override;
    void controllerMoved (int controllerNumber, int newControllerValue)override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)override;
    
private:
    juce::AudioBuffer<float> voiceBuffer;
    bool isPrepared { false };

    VCO VCO1;
    juce::dsp::Gain<float> gain;
};
#endif // _SYNTHVOICE_H_