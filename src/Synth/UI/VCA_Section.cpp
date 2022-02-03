#include "VCA_Section.h"

void VCA_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    VCA_VolumeAttachment        = std::make_unique<SliderAttachment>(params, "VCAVolume", VCA_VolumeSlider);
    VCA_ENV_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCAENV_intensity", VCA_ENV_intensitySlider); 

    setSliderParamsV(VCA_VolumeSlider);
    setSliderParamsV(VCA_ENV_intensitySlider); 

    bounds = getLocalBounds();
}

void VCA_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    VCA_VolumeAttachment        = std::make_unique<SliderAttachment>(params, "VCAVolume", VCA_VolumeSlider);
    VCA_ENV_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCAENV_intensity", VCA_ENV_intensitySlider); 

    setSliderParamsV(VCA_VolumeSlider);
    setSliderParamsV(VCA_ENV_intensitySlider); 

    bounds = juce::Rectangle(x, y, w, h);
}

void VCA_section::paint (juce::Graphics& g){
    g.fillAll(juce::Colours::black);
    ADSR.paint(g);
}

void VCA_section::resized(){

    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 6 - padding;
    const auto slider_h = bounds.getHeight();
    const auto slider_startX = 0;
    const auto slider_startY = (bounds.getHeight() / 2) - (slider_h / 2);

    ADSR.setBounds(2*bounds.getWidth()/6+padding, 0, 4*bounds.getWidth()/6, bounds.getHeight());
    ADSR.resized();
    VCA_VolumeSlider.setBounds(0, 0, slider_w, slider_h);
    VCA_ENV_intensitySlider.setBounds(VCA_VolumeSlider.getRight()+padding, 0, slider_w, slider_h); 
}

void VCA_section::setSliderParamsV(juce::Slider& slider){
    slider.setSliderStyle( juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle( juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
