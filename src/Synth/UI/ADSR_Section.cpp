#include "ADSR_Section.h"

void ADSR_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, AttackSlider, juce::Slider::SliderStyle::LinearVertical);
    AttackAttachment  = CreateAttachment(params, ModuleID+"Attack", AttackSlider);
    setSliderParams(*this, DecaySlider, juce::Slider::SliderStyle::LinearVertical);
    DecayAttachment   = CreateAttachment(params, ModuleID+"Decay", DecaySlider);
    setSliderParams(*this, SustainSlider, juce::Slider::SliderStyle::LinearVertical);
    SustainAttachment = CreateAttachment(params, ModuleID+"Sustain", SustainSlider);
    setSliderParams(*this, ReleaseSlider, juce::Slider::SliderStyle::LinearVertical);
    ReleaseAttachment = CreateAttachment(params, ModuleID+"Release", ReleaseSlider);

    bounds = getLocalBounds();
}

void ADSR_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){

    setSliderParams(*this, AttackSlider, juce::Slider::SliderStyle::LinearVertical);
    AttackAttachment  = CreateAttachment(params, ModuleID+"Attack", AttackSlider);
    setSliderParams(*this, DecaySlider, juce::Slider::SliderStyle::LinearVertical);
    DecayAttachment   = CreateAttachment(params, ModuleID+"Decay", DecaySlider);
    setSliderParams(*this, SustainSlider, juce::Slider::SliderStyle::LinearVertical);
    SustainAttachment = CreateAttachment(params, ModuleID+"Sustain", SustainSlider);
    setSliderParams(*this, ReleaseSlider, juce::Slider::SliderStyle::LinearVertical);
    ReleaseAttachment = CreateAttachment(params, ModuleID+"Release", ReleaseSlider);

    bounds = juce::Rectangle(x, y, w, h);
}

void ADSR_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void ADSR_section::resized(){
    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 4 - padding;
    const auto slider_h = bounds.getHeight();
    const auto slider_startX = 0;
    const auto slider_startY = 0;//(bounds.getHeight() / 2) - (slider_h / 2);

    AttackSlider.setBounds(slider_startX, slider_startY, slider_w, slider_h);
    DecaySlider.setBounds(AttackSlider.getRight() + padding, slider_startY, slider_w, slider_h);
    SustainSlider.setBounds(DecaySlider.getRight() + padding, slider_startY, slider_w, slider_h);
    ReleaseSlider.setBounds(SustainSlider.getRight() + padding, slider_startY, slider_w, slider_h);
}
