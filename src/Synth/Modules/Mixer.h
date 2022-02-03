#ifndef _MIXER_H_
#define _MIXER_H_

#include <JuceHeader.h>
#include "Module.h"

namespace SynthModules{
    class MIXER : public Module{
    public:
        MIXER(std::string _ModuleID, int _N_inputs);
        ~MIXER();

        void prepare(const juce::dsp::ProcessSpec &spec) noexcept;
        void process(juce::dsp::AudioBlock<float> block_out, std::vector<juce::dsp::AudioBlock<float>> blocks);
        
        void Update(juce::AudioProcessorValueTreeState& params);

    private:
        int N_inputs;
        std::vector<juce::dsp::Gain<float>> Gains;
    };
}


#endif // _MIXER_H_