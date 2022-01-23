#ifndef _VCO_H_
#define _VCO_H_

#include <JuceHeader.h>

class VCO{
public:
    VCO();
    ~VCO();

    void prepare(const juce::dsp::ProcessSpec &spec) noexcept;
    void process(juce::dsp::AudioBlock<float> block);
    void setFrequency(float freq);
private:
    juce::dsp::Oscillator<float> SawOsc;
    juce::dsp::Oscillator<float> TriOsc;
    juce::dsp::Oscillator<float> SqrOsc;
    juce::dsp::Oscillator<float> SinOsc;
};

#endif // _VCO_H_