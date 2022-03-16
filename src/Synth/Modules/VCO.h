#ifndef _VCO_H_
#define _VCO_H_

#include <JuceHeader.h>
#include "Module.h"
#include "LFO.h"

namespace SynthModules{
    class VCO : public Module{

    public:
        VCO(std::string _ModuleID, SynthModules::LFO& _lfo);
        ~VCO();

        void prepare(juce::dsp::ProcessSpec& spec);
        void generateBlock(int numSamples);
        void generateSample(int sampleIdx, juce::dsp::AudioBlock<float> vco_block);
        juce::dsp::AudioBlock<float> getBlock();

        void Update(juce::AudioProcessorValueTreeState& params);
        
        void switchWaveForm(int type);
        void setFrequency(float freq);

    private:
        juce::dsp::ProcessSpec Specs;

        juce::AudioBuffer<float> vco_buffer;
        //juce::dsp::AudioBlock<float> vco_block;

        int WaveForm;
        struct Phase Phase;
        float Frequency;

        float Detune;
        int   Octave;

        float PulseWidth;

        SynthModules::LFO& lfo;
        bool  hasLFO;
        float LFO_Freq_intensity;
        float LFO_Pw_intensity;
        float MaxFreqMod = 1.0f;
        float MaxPwMod   = 0.04f;
    };
}


#endif // _VCO_H_