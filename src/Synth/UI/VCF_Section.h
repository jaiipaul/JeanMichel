#ifndef _VCF_SECTION_H_
#define _VCF_SECTION_H_

#include <JuceHeader.h>
#include "ADSR_Section.h"

class VCF_section : public juce::Component{
public:

    VCF_section(){ };
    ~VCF_section(){ };

    void initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params);
    void initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ADSR_section ADSR;
    juce::Rectangle<int> bounds;
    
    juce::Slider VCF_CutoffSlider;
    juce::Slider VCF_ResonanceSlider;
    juce::Slider VCF_DriveSlider;
    juce::Slider VCF_LFO_intensitySlider;
    juce::Slider VCF_ENV_intensitySlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> VCF_CutoffAttachment;
    std::unique_ptr<SliderAttachment> VCF_ResonanceAttachment;
    std::unique_ptr<SliderAttachment> VCF_DriveAttachment;
    std::unique_ptr<SliderAttachment> VCF_LFO_intensityAttachment;
    std::unique_ptr<SliderAttachment> VCF_ENV_intensityAttachment;
};
#endif // _VCF_SECTION_H_