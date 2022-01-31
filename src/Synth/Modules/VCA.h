#ifndef _VCA_H_
#define _VCA_H_

#include <JuceHeader.h>

namespace SynthModules{
    class VCA{
    public:
        VCA();
        ~VCA();

        void prepare(const juce::dsp::ProcessSpec &spec) noexcept;
        void process(juce::dsp::AudioBlock<float> block);
        
    private:
        float Volume;
        ADSR_Env& adsr;
        juce::dsp::Gain<float> gain;
    };
}


#endif // _VCA_H_