#ifndef _ADSR_H_
#define _ADSR_H_

#include <JuceHeader.h>
#include "Module.h"

namespace SynthModules{
    class ADSR : public juce::ADSR,
                 public Module{
    public:
        ADSR(std::string _ModuleID);
        ~ADSR();

        void Update(juce::AudioProcessorValueTreeState& params);

    private:
        juce::ADSR::Parameters adsrParams;
    };
}


#endif // _ADSR_H_