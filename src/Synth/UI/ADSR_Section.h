#ifndef _ADSR_SECTION_H_
#define _ADSR_SECTION_H_

#include <JuceHeader.h>
#include "UI_func.h"

class ADSR_section : public juce::Component{
public:

    ADSR_section(){ };
    ~ADSR_section(){ };

    void initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params);
    void initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Rectangle<int> bounds;
    
    juce::Slider AttackSlider;
    juce::Slider DecaySlider;
    juce::Slider SustainSlider;
    juce::Slider ReleaseSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> AttackAttachment;
    std::unique_ptr<SliderAttachment> SustainAttachment;
    std::unique_ptr<SliderAttachment> DecayAttachment;
    std::unique_ptr<SliderAttachment> ReleaseAttachment;

};
#endif // _ADSR_SECTION_H_