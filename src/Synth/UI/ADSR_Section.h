#ifndef _ADSR_SECTION_H_
#define _ADSR_SECTION_H_

#include <JuceHeader.h>

class ADSR_section : public juce::Component{
public:

    ADSR_section(){ };
    ~ADSR_section(){ };

    void initSection(juce::AudioProcessorValueTreeState& params);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);

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