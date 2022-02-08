#include "LFO_Section.h"

void LFO_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, LFO_RateSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LFO_RateAttachment = CreateAttachment(params, ModuleID + "Rate", LFO_RateSlider);
    setSliderParams(*this, LFO_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); 
    LFO_WaveAttachment = CreateAttachment(params, ModuleID + "Wave", LFO_WaveSlider);

    bounds = getLocalBounds();
}

void LFO_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){

    setSliderParams(*this, LFO_RateSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LFO_RateAttachment = CreateAttachment(params, ModuleID + "Rate", LFO_RateSlider);
    setSliderParams(*this, LFO_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); 
    LFO_WaveAttachment = CreateAttachment(params, ModuleID + "Wave", LFO_WaveSlider); 

    bounds = juce::Rectangle(x, y, w, h);
}

void LFO_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void LFO_section::resized(){
    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() - 2 * padding;
    const auto slider_h = (bounds.getHeight() - 3*padding) / 2 ;

    LFO_WaveSlider.setBounds(padding, padding, slider_w, slider_h);
    LFO_RateSlider.setBounds(padding, LFO_WaveSlider.getBottom()+padding, slider_w, slider_h);
     
}

