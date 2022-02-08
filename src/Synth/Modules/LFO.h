#ifndef _LFO_H_
#define _LFO_H_

#include <JuceHeader.h>
#include "Module.h"

namespace SynthModules{
    class LFO : public Module{

    public:
        LFO(std::string _ModuleID);
        ~LFO();

        void prepare(juce::dsp::ProcessSpec& spec);
        void generateBlock(int numSamples);
        void generateSample(int sampleIdx, juce::dsp::AudioBlock<float> lfo_block);

        void Update(juce::AudioProcessorValueTreeState& params);
        
        void switchWaveForm(int type);
        float getValueAt(int sampleIdx);
    private:
        juce::dsp::ProcessSpec Specs;

        juce::AudioBuffer<float> lfo_buffer;

        int WaveForm;
        struct Phase Phase;
        float Frequency;
    };
}


#endif // _LFO_H_