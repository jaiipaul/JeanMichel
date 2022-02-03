#include "LFO_Section.h"

void LFO_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    LFO_RateAttachment = std::make_unique<SliderAttachment>(params, ModuleID + "Rate", LFO_RateSlider);
    LFO_WaveAttachment = std::make_unique<SliderAttachment>(params, ModuleID + "Wave", LFO_WaveSlider); 

    setSliderParamsV(LFO_RateSlider);
    setSliderParamsV(LFO_WaveSlider); 

    bounds = getLocalBounds();
}

void LFO_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    LFO_RateAttachment = std::make_unique<SliderAttachment>(params, ModuleID + "Rate", LFO_RateSlider);
    LFO_WaveAttachment = std::make_unique<SliderAttachment>(params, ModuleID + "Wave", LFO_WaveSlider); 

    setSliderParamsV(LFO_RateSlider);
    setSliderParamsV(LFO_WaveSlider); 


    bounds = juce::Rectangle(x, y, w, h);
}

void LFO_section::paint (juce::Graphics& g){
    g.fillAll(juce::Colours::black);
}

void LFO_section::resized(){
    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 2 - padding;
    const auto slider_h = bounds.getHeight();
    const auto slider_startX = 0;
    const auto slider_startY = (bounds.getHeight() / 2) - (slider_h / 2);

    LFO_RateSlider.setBounds(0, 0, slider_w, slider_h);
    LFO_WaveSlider.setBounds(LFO_RateSlider.getRight()+padding, 0, slider_w, slider_h); 
}

void LFO_section::setSliderParamsV(juce::Slider& slider){
    slider.setSliderStyle( juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle( juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
