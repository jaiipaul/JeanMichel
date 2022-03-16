#include "LFO_Section.h"
#include <BinaryData.h>

void LFO_section::initSection(std::string _ModuleID, juce::AudioProcessorValueTreeState& params){
    ModuleID = _ModuleID;

    setSliderParams(*this, LFO_RateSlider, ModuleID + "Rate", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LFO_RateAttachment = CreateAttachment(params, ModuleID + "Rate", LFO_RateSlider);
    LFO_WaveSlider.initSlider(ModuleID + "Wave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);  
    addAndMakeVisible(LFO_WaveSlider);
    //LFO_WaveAttachment = CreateAttachment(params, ModuleID + "Wave", LFO_WaveSlider.getSlider());
    bounds = getLocalBounds();
    setBounds(bounds);
}

void LFO_section::initSection(std::string _ModuleID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    ModuleID = _ModuleID;

    setSliderParams(*this, LFO_RateSlider, ModuleID + "Rate", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    LFO_RateAttachment = CreateAttachment(params, ModuleID + "Rate", LFO_RateSlider);
    LFO_WaveSlider.initSlider(ModuleID + "Wave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4); 
    addAndMakeVisible(LFO_WaveSlider);
    //LFO_WaveAttachment = CreateAttachment(params, ModuleID + "Wave", LFO_WaveSlider.getSlider());

    bounds = juce::Rectangle<int>(x, y, w, h);
    setBounds(bounds);
}

void LFO_section::paint (juce::Graphics& g){
    LFO_WaveSlider.Update();
}

void LFO_section::resized(){
    int boundsX = bounds.getX();
    int boundsY = bounds.getY();

    LFO_WaveSlider.setBounds(17, 64, 45, 45);
    LFO_WaveSlider.resized();
    LFO_RateSlider.setBounds(108, 12, 75, 75);
     
}

