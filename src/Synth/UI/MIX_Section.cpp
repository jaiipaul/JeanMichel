#include "MIX_Section.h"

void MIX_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, Vol0Slider, juce::Slider::SliderStyle::LinearVertical);
    Vol0Attachment = CreateAttachment(params, ModuleID+"Volume0", Vol0Slider);
    setSliderParams(*this, Vol1Slider, juce::Slider::SliderStyle::LinearVertical);
    Vol1Attachment = CreateAttachment(params, ModuleID+"Volume1", Vol1Slider);
    setSliderParams(*this, Vol2Slider, juce::Slider::SliderStyle::LinearVertical);
    Vol2Attachment = CreateAttachment(params, ModuleID+"Volume2", Vol2Slider);       

    bounds = getLocalBounds();
}

void MIX_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){

    setSliderParams(*this, Vol0Slider, juce::Slider::SliderStyle::LinearVertical);
    Vol0Attachment = CreateAttachment(params, ModuleID+"Volume0", Vol0Slider);
    setSliderParams(*this, Vol1Slider, juce::Slider::SliderStyle::LinearVertical);
    Vol1Attachment = CreateAttachment(params, ModuleID+"Volume1", Vol1Slider);
    setSliderParams(*this, Vol2Slider, juce::Slider::SliderStyle::LinearVertical);
    Vol2Attachment = CreateAttachment(params, ModuleID+"Volume2", Vol2Slider);    
    

    bounds = juce::Rectangle(x, y, w, h);
}

void MIX_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void MIX_section::resized(){
    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 3 - padding;
    const auto slider_h = bounds.getHeight();
    const auto slider_startX = 0;
    const auto slider_startY = 0;//(bounds.getHeight() / 2) - (slider_h / 2);

    Vol0Slider.setBounds(slider_startX, slider_startY, slider_w, slider_h);
    Vol1Slider.setBounds(Vol0Slider.getRight()+padding, slider_startY, slider_w, slider_h);
    Vol2Slider.setBounds(Vol1Slider.getRight()+padding, slider_startY, slider_w, slider_h);

}