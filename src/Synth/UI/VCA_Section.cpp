#include "VCA_Section.h"

void VCA_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);

    setSliderParams(*this, VCA_VolumeSlider, juce::Slider::SliderStyle::LinearVertical);
    VCA_VolumeAttachment        = CreateAttachment(params, "VCAVolume", VCA_VolumeSlider);
    setSliderParams(*this, VCA_ENV_intensitySlider, juce::Slider::SliderStyle::LinearVertical); 
    VCA_ENV_intensityAttachment = CreateAttachment(params, "VCAENV_intensity", VCA_ENV_intensitySlider); 

    bounds = getLocalBounds();
}

void VCA_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);
    
    setSliderParams(*this, VCA_VolumeSlider, juce::Slider::SliderStyle::LinearVertical);
    VCA_VolumeAttachment        = CreateAttachment(params, "VCAVolume", VCA_VolumeSlider);
    setSliderParams(*this, VCA_ENV_intensitySlider, juce::Slider::SliderStyle::LinearVertical); 
    VCA_ENV_intensityAttachment = CreateAttachment(params, "VCAENV_intensity", VCA_ENV_intensitySlider);  

    bounds = juce::Rectangle(x, y, w, h);
}

void VCA_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
    ADSR.paint(g);
}

void VCA_section::resized(){

    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 6 - padding;
    const auto slider_h = bounds.getHeight()-2*padding;

    VCA_VolumeSlider.setBounds(padding, padding, slider_w, slider_h);
    VCA_ENV_intensitySlider.setBounds(VCA_VolumeSlider.getRight()+padding, padding, slider_w, slider_h); 

    ADSR.setBounds(VCA_ENV_intensitySlider.getRight() + 2*padding, padding, 4*bounds.getWidth()/6 - padding, slider_h);
    ADSR.resized();
}

