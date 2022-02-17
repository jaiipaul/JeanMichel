#ifndef _LFO_SECTION_H_
#define _LFO_SECTION_H_

#include <JuceHeader.h>
#include "UI_func.h"
#include "WaveSlider.h"

class LFO_section : public juce::Component{
public:

    LFO_section(){ };
    ~LFO_section(){ };

    void initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params);
    void initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
    void paint (juce::Graphics&) override;
    void resized();

private:
    std::string ModuleID;
    juce::Rectangle<int> bounds;
    
    juce::Image LFOwave;
    int waveform;

    juce::Slider LFO_RateSlider;
    juce::WaveSlider LFO_WaveSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> LFO_RateAttachment;
    //std::unique_ptr<SliderAttachment> LFO_WaveAttachment;
};
#endif // _LFO_SECTION_H_