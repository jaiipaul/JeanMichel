#ifndef _SYNTHVOICE_H_
#define _SYNTHVOICE_H_

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Modules/VCO.h"
#include "Modules/ADSR.h"
#include "Modules/VCA.h"
#include "Modules/Mixer.h"
#include "Modules/LadderFilter.h"
#include "Modules/LFO.h"

class SynthVoice : public juce::SynthesiserVoice{
public:
    bool canPlaySound (juce::SynthesiserSound *sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)override;
    void stopNote (float velocity, bool allowTailOff)override;
    void pitchWheelMoved (int newPitchWheelValue)override;
    void controllerMoved (int controllerNumber, int newControllerValue)override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void update(juce::AudioProcessorValueTreeState& params);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)override;
    
private:
    juce::AudioBuffer<float> voiceBuffer;

    bool isPrepared { false };

    SynthModules::ADSR ADSR1{"ADSR1"};
    //SynthModules::ADSR ADSR2{"ADSR2"};

    SynthModules::LFO LFO1{"LFO1"};
    SynthModules::LFO LFO2{"LFO2"};

    SynthModules::VCO VCO0{"SUB_VCO"};
    SynthModules::VCO VCO1{"VCO1", LFO1};
    SynthModules::VCO VCO2{"VCO2", LFO1};

    SynthModules::MIXER MIX{"MIXER", 3};

    SynthModules::LadderFilter VCF{"VCF", ADSR1};
    
    SynthModules::VCA VCA{"VCA", ADSR1 };
};
#endif // _SYNTHVOICE_H_