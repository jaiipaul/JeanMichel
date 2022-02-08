#ifndef _MIX_SECTION_H_
#define _MIX_SECTION_H_

#include <JuceHeader.h>
#include "UI_func.h"

class MIX_section : public juce::Component{
public:

    MIX_section(){ };
    ~MIX_section(){ };

    void initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params);
    void initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Rectangle<int> bounds;

    juce::Slider Vol0Slider;
    juce::Slider Vol1Slider;
    juce::Slider Vol2Slider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
//
    std::unique_ptr<SliderAttachment> Vol0Attachment;
    std::unique_ptr<SliderAttachment> Vol1Attachment;
    std::unique_ptr<SliderAttachment> Vol2Attachment;
};
#endif // _MIX_SECTION_H_