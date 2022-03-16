#include "VCA_Section.h"

void VCA_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);

    setSliderParams(*this, VCA_VolumeSlider, "VCAVolume", juce::Slider::SliderStyle::LinearVertical);
    VCA_VolumeAttachment        = CreateAttachment(params, "VCAVolume", VCA_VolumeSlider);
    setSliderParams(*this, VCA_ENV_intensitySlider, "VCAENV_intensity", juce::Slider::SliderStyle::LinearVertical); 
    VCA_ENV_intensityAttachment = CreateAttachment(params, "VCAENV_intensity", VCA_ENV_intensitySlider);  

    bounds = getLocalBounds( );
    setBounds(bounds);
}

void VCA_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);
    
    setSliderParams(*this, VCA_VolumeSlider, "VCAVolume", juce::Slider::SliderStyle::LinearVertical);
    VCA_VolumeAttachment        = CreateAttachment(params, "VCAVolume", VCA_VolumeSlider);
    setSliderParams(*this, VCA_ENV_intensitySlider, "VCAENV_intensity", juce::Slider::SliderStyle::LinearVertical); 
    VCA_ENV_intensityAttachment = CreateAttachment(params, "VCAENV_intensity", VCA_ENV_intensitySlider);

    bounds = juce::Rectangle<int>(x, y, w, h);
    setBounds(bounds);
}

void VCA_section::paint (juce::Graphics& g){
    //ADSR.paint(g);
}

void VCA_section::resized(){
    const auto slider_w = 14;
    const auto slider_h = 110;

    VCA_VolumeSlider.setBounds(30, 46, slider_w, slider_h);
    VCA_ENV_intensitySlider.setBounds(82, 46, slider_w, slider_h); 

    ADSR.setBounds(157, 46, 164, slider_h);
    ADSR.resized();
}

