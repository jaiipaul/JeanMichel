#include "ADSR_Section.h"

void ADSR_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    AttackAttachment  = std::make_unique<SliderAttachment>(params, ModuleID+"Attack", AttackSlider);
    DecayAttachment = std::make_unique<SliderAttachment>(params, ModuleID+"Decay", DecaySlider);
    SustainAttachment   = std::make_unique<SliderAttachment>(params, ModuleID+"Sustain", SustainSlider);
    ReleaseAttachment = std::make_unique<SliderAttachment>(params, ModuleID+"Release", ReleaseSlider);

    setSliderParams(AttackSlider);
    setSliderParams(DecaySlider);
    setSliderParams(SustainSlider);
    setSliderParams(ReleaseSlider);
}

void ADSR_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    AttackAttachment  = std::make_unique<SliderAttachment>(params, ModuleID+"Attack", AttackSlider);
    DecayAttachment = std::make_unique<SliderAttachment>(params, ModuleID+"Decay", DecaySlider);
    SustainAttachment   = std::make_unique<SliderAttachment>(params, ModuleID+"Sustain", SustainSlider);
    ReleaseAttachment = std::make_unique<SliderAttachment>(params, ModuleID+"Release", ReleaseSlider);

    setSliderParams(AttackSlider);
    setSliderParams(DecaySlider);
    setSliderParams(SustainSlider);
    setSliderParams(ReleaseSlider);
}

void ADSR_section::paint (juce::Graphics& g){
    g.fillAll(juce::Colours::black);
}

void ADSR_section::resized(){
    const auto bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 4 - padding;
    const auto slider_h = bounds.getHeight()/ 2;
    const auto slider_startX = 0;
    const auto slider_startY = (bounds.getHeight() / 2) - (slider_h / 2);

    AttackSlider.setBounds(slider_startX, slider_startY, slider_w, slider_h);
    DecaySlider.setBounds(AttackSlider.getRight() + padding, slider_startY, slider_w, slider_h);
    SustainSlider.setBounds(DecaySlider.getRight() + padding, slider_startY, slider_w, slider_h);
    ReleaseSlider.setBounds(SustainSlider.getRight() + padding, slider_startY, slider_w, slider_h);
}

void ADSR_section::setSliderParams(juce::Slider& slider){
    slider.setSliderStyle( juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle( juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}