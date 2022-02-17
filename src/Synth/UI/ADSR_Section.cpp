#include "ADSR_Section.h"

void ADSR_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, AttackSlider, ModuleID+"Attack", juce::Slider::SliderStyle::LinearVertical);
    AttackAttachment  = CreateAttachment(params, ModuleID+"Attack", AttackSlider);
    setSliderParams(*this, DecaySlider, ModuleID+"Decay", juce::Slider::SliderStyle::LinearVertical);
    DecayAttachment   = CreateAttachment(params, ModuleID+"Decay", DecaySlider);
    setSliderParams(*this, SustainSlider, ModuleID+"Sustain", juce::Slider::SliderStyle::LinearVertical);
    SustainAttachment = CreateAttachment(params, ModuleID+"Sustain", SustainSlider);
    setSliderParams(*this, ReleaseSlider, ModuleID+"Release", juce::Slider::SliderStyle::LinearVertical);
    ReleaseAttachment = CreateAttachment(params, ModuleID+"Release", ReleaseSlider);

    bounds = getLocalBounds();
    setBounds(bounds);
}

void ADSR_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){

    setSliderParams(*this, AttackSlider, ModuleID+"Attack", juce::Slider::SliderStyle::LinearVertical);
    AttackAttachment  = CreateAttachment(params, ModuleID+"Attack", AttackSlider);
    setSliderParams(*this, DecaySlider, ModuleID+"Decay", juce::Slider::SliderStyle::LinearVertical);
    DecayAttachment   = CreateAttachment(params, ModuleID+"Decay", DecaySlider);
    setSliderParams(*this, SustainSlider, ModuleID+"Sustain", juce::Slider::SliderStyle::LinearVertical);
    SustainAttachment = CreateAttachment(params, ModuleID+"Sustain", SustainSlider);
    setSliderParams(*this, ReleaseSlider, ModuleID+"Release", juce::Slider::SliderStyle::LinearVertical);
    ReleaseAttachment = CreateAttachment(params, ModuleID+"Release", ReleaseSlider);

    bounds = juce::Rectangle(x, y, w, h);
    setBounds(bounds);
}

void ADSR_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void ADSR_section::resized(){
    const auto slider_w = 14;
    const auto slider_h = 110;
    const auto padding = (getLocalBounds().getWidth() - 4*slider_w)/3;

    AttackSlider.setBounds(0, 0, slider_w, slider_h);
    DecaySlider.setBounds(AttackSlider.getRight() + padding, 0, slider_w, slider_h);
    SustainSlider.setBounds(DecaySlider.getRight() + padding, 0, slider_w, slider_h);
    ReleaseSlider.setBounds(SustainSlider.getRight() + padding, 0, slider_w, slider_h);
}
