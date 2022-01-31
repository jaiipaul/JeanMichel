#ifndef _ADSR_H_
#define _ADSR_H_

#include <JuceHeader.h>
#include "Module.h"

namespace SynthModules{
    class cADSR : public juce::ADSR,
                 public Module{
    public:
        cADSR(std::string _ModuleID);
        ~cADSR();

        void Update(juce::AudioProcessorValueTreeState& params);

    private:
        juce::ADSR::Parameters adsrParams;
    };
}


#endif // _ADSR_H_