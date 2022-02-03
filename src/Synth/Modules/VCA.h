#ifndef _VCA_H_
#define _VCA_H_

#include <JuceHeader.h>
#include "Module.h"
#include "ADSR.h"

namespace SynthModules{
    class VCA : public Module{
    public:
        VCA(std::string _ModuleID, SynthModules::ADSR& _adsr);
        ~VCA();

        void prepare(const juce::dsp::ProcessSpec &spec) noexcept;
        void process(juce::dsp::AudioBlock<float> block);
        
        void Update(juce::AudioProcessorValueTreeState& params);

    private:

        float Volume;
        SynthModules::ADSR& adsr;
        float ENV_intensity;
        juce::dsp::Gain<float> gain;
    };
}


#endif // _VCA_H_