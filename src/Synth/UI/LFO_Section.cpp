#include "LFO_Section.h"

void LFO_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, LFO_RateSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LFO_RateAttachment = CreateAttachment(params, ModuleID + "Rate", LFO_RateSlider);
    setSliderParams(*this, LFO_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); 
    LFO_WaveAttachment = CreateAttachment(params, ModuleID + "Wave", LFO_WaveSlider);

    bounds = getLocalBounds();
    setBounds(bounds);
}

void LFO_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){

    setSliderParams(*this, LFO_RateSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LFO_RateAttachment = CreateAttachment(params, ModuleID + "Rate", LFO_RateSlider);
    setSliderParams(*this, LFO_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); 
    LFO_WaveAttachment = CreateAttachment(params, ModuleID + "Wave", LFO_WaveSlider); 

    bounds = juce::Rectangle(x, y, w, h);
    setBounds(bounds);
}

void LFO_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void LFO_section::resized(){
    int boundsX = bounds.getX();
    int boundsY = bounds.getY();

    LFO_WaveSlider.setBounds(17, 64, 45, 45);
    LFO_RateSlider.setBounds(108, 12, 75, 75);
     
}

