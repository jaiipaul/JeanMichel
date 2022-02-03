#ifndef _LadderFilter_H_
#define _LadderFilter_H_

#include <JuceHeader.h>
#include "Module.h"
#include "ADSR.h"

#define Vt 0.312F

namespace SynthModules{
    class LadderFilter : public Module{
    public:
        LadderFilter(std::string _ModuleID, SynthModules::ADSR& _adsr);
        ~LadderFilter();

        void prepare(float _sampleRate, int channels);
        void process(juce::dsp::AudioBlock<float> block);
        
        void Update(juce::AudioProcessorValueTreeState& params);
        void ComputeCoef();
        
    private:
        float sampleRate;

        float cutoff;
        float resonance;
        float G;
        float Drive;        

        float* StageOutputs;
        float* StageFeedbacks;
        float* StageT;

        SynthModules::ADSR& adsr;
        float ENV_intensity;
    };
}


#endif // _LadderFilter_H_