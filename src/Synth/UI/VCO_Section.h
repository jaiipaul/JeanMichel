#ifndef _VCO_SECTION_H_
#define _VCO_SECTION_H_

#include <JuceHeader.h>
#include "UI_func.h"
#include "ImageSlider.h"

class VCO_section : public juce::Component{
public:

    VCO_section(){ };
    ~VCO_section(){ };

    void initSection(juce::AudioProcessorValueTreeState& params);
    void initSection(juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Rectangle<int> bounds;

    juce::ImageSlider SUB_WaveSlider;
    juce::ImageSlider SUB_OctaveSlider;

    juce::ImageSlider VCO1_WaveSlider;
    juce::Slider VCO1_PulseWidthSlider;
    juce::Slider VCO1_LFO_Freq_intensitySlider;
    juce::Slider VCO1_LFO_Pw_intensitySlider;

    juce::ImageSlider VCO2_WaveSlider;
    juce::Slider VCO2_PulseWidthSlider;
    juce::Slider VCO2_LFO_Freq_intensitySlider;
    juce::Slider VCO2_LFO_Pw_intensitySlider;
    juce::Slider VCO2_DetuneSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    //std::unique_ptr<SliderAttachment> SUB_WaveAttachment;
    //std::unique_ptr<SliderAttachment> SUB_OctaveAttachment;

    std::unique_ptr<SliderAttachment> VCO1_PulseWidthAttachment;
    std::unique_ptr<SliderAttachment> VCO1_LFO_Freq_intensityAttachment;
    std::unique_ptr<SliderAttachment> VCO1_LFO_Pw_intensityAttachment;

    std::unique_ptr<SliderAttachment> VCO2_PulseWidthAttachment;
    std::unique_ptr<SliderAttachment> VCO2_LFO_Freq_intensityAttachment;
    std::unique_ptr<SliderAttachment> VCO2_LFO_Pw_intensityAttachment;
    std::unique_ptr<SliderAttachment> VCO2_DetuneAttachment;

};
#endif // _VCO_SECTION_H_