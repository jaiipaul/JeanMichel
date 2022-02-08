#ifndef _VCA_SECTION_H_
#define _VCA_SECTION_H_

#include <JuceHeader.h>
#include "ADSR_Section.h"

class VCA_section : public juce::Component{
public:

    VCA_section(){ };
    ~VCA_section(){ };

    void initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params);
    void initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ADSR_section ADSR;
    juce::Rectangle<int> bounds;
    
    juce::Slider VCA_VolumeSlider;
    juce::Slider VCA_ENV_intensitySlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> VCA_VolumeAttachment;
    std::unique_ptr<SliderAttachment> VCA_ENV_intensityAttachment;
};
#endif // _VCA_SECTION_H_