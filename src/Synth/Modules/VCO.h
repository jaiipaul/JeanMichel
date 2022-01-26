#ifndef _VCO_H_
#define _VCO_H_

#include <JuceHeader.h>

namespace SynthModules{
    class VCO : public juce::dsp::Oscillator<float>{
    public:
        VCO();
        ~VCO();

        void switchWaveForm(const int type);

    private:

    };
}


#endif // _VCO_H_