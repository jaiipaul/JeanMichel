#include "MIX_Section.h"

void MIX_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, Vol0Slider, ModuleID+"Volume0", juce::Slider::SliderStyle::LinearVertical);
    Vol0Attachment = CreateAttachment(params, ModuleID+"Volume0", Vol0Slider);
    setSliderParams(*this, Vol1Slider, ModuleID+"Volume1", juce::Slider::SliderStyle::LinearVertical);
    Vol1Attachment = CreateAttachment(params, ModuleID+"Volume1", Vol1Slider);
    setSliderParams(*this, Vol2Slider, ModuleID+"Volume2", juce::Slider::SliderStyle::LinearVertical);
    Vol2Attachment = CreateAttachment(params, ModuleID+"Volume2", Vol2Slider);         

    bounds = getLocalBounds();
    setBounds(bounds);
}

void MIX_section::initSection(std::string ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){

    setSliderParams(*this, Vol0Slider, ModuleID+"Volume0", juce::Slider::SliderStyle::LinearVertical);
    Vol0Attachment = CreateAttachment(params, ModuleID+"Volume0", Vol0Slider);
    setSliderParams(*this, Vol1Slider, ModuleID+"Volume1", juce::Slider::SliderStyle::LinearVertical);
    Vol1Attachment = CreateAttachment(params, ModuleID+"Volume1", Vol1Slider);
    setSliderParams(*this, Vol2Slider, ModuleID+"Volume2", juce::Slider::SliderStyle::LinearVertical);
    Vol2Attachment = CreateAttachment(params, ModuleID+"Volume2", Vol2Slider);    
    

    bounds = juce::Rectangle(x, y, w, h);
    setBounds(bounds);
}

void MIX_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void MIX_section::resized(){
    int boundsX = bounds.getX();
    int boundsY = bounds.getY();

    const auto Vslider_w = 14;
    const auto Vslider_h = 110;

    Vol0Slider.setBounds(43,  30, Vslider_w, Vslider_h);
    Vol1Slider.setBounds(93,  30, Vslider_w, Vslider_h);
    Vol2Slider.setBounds(143, 30, Vslider_w, Vslider_h);

}