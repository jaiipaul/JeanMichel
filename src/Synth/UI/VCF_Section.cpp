#include "VCF_Section.h"

void VCF_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    VCF_CutoffAttachment        = std::make_unique<SliderAttachment>(params, "VCFCutoff", VCF_CutoffSlider);
    VCF_ResonanceAttachment     = std::make_unique<SliderAttachment>(params, "VCFResonance", VCF_ResonanceSlider);
    VCF_DriveAttachment         = std::make_unique<SliderAttachment>(params, "VCFDrive", VCF_DriveSlider);
    VCF_LFO_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCFLFO_intensity", VCF_LFO_intensitySlider); 
    VCF_ENV_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCFENV_intensity", VCF_ENV_intensitySlider); 

    setSliderParamsV(VCF_CutoffSlider);
    setSliderParamsV(VCF_ResonanceSlider);
    setSliderParamsV(VCF_DriveSlider);
    setSliderParamsV(VCF_LFO_intensitySlider); 
    setSliderParamsV(VCF_ENV_intensitySlider); 

    bounds = getLocalBounds();
}

void VCF_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    VCF_CutoffAttachment        = std::make_unique<SliderAttachment>(params, "VCFCutoff", VCF_CutoffSlider);
    VCF_ResonanceAttachment     = std::make_unique<SliderAttachment>(params, "VCFResonance", VCF_ResonanceSlider);
    VCF_DriveAttachment         = std::make_unique<SliderAttachment>(params, "VCFDrive", VCF_DriveSlider);
    VCF_LFO_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCFLFO_intensity", VCF_LFO_intensitySlider); 
    VCF_ENV_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCFENV_intensity", VCF_ENV_intensitySlider); 

    setSliderParamsV(VCF_CutoffSlider);
    setSliderParamsV(VCF_ResonanceSlider);
    setSliderParamsV(VCF_DriveSlider);
    setSliderParamsV(VCF_LFO_intensitySlider); 
    setSliderParamsV(VCF_ENV_intensitySlider);  

    bounds = juce::Rectangle(x, y, w, h);
}

void VCF_section::paint (juce::Graphics& g){
    g.fillAll(juce::Colours::black);
    ADSR.paint(g);
}

void VCF_section::resized(){

    bounds = getLocalBounds();
    const auto padding = 10;
    const auto slider_w = bounds.getWidth() / 9 - padding;
    const auto slider_h = bounds.getHeight();
    const auto slider_startX = 0;
    const auto slider_startY = (bounds.getHeight() / 2) - (slider_h / 2);

    ADSR.setBounds(5*bounds.getWidth()/9+padding, 0, 4*bounds.getWidth()/9, bounds.getHeight());
    ADSR.resized();
    VCF_CutoffSlider.setBounds(0, 0, slider_w, slider_h);
    VCF_ResonanceSlider.setBounds(VCF_CutoffSlider.getRight()+padding, 0, slider_w, slider_h);
    VCF_DriveSlider.setBounds(VCF_ResonanceSlider.getRight()+padding, 0, slider_w, slider_h);
    VCF_ENV_intensitySlider.setBounds(VCF_DriveSlider.getRight()+padding, 0, slider_w, slider_h);
    VCF_LFO_intensitySlider.setBounds(VCF_ENV_intensitySlider.getRight()+padding, 0, slider_w, slider_h); 
}

void VCF_section::setSliderParamsV(juce::Slider& slider){
    slider.setSliderStyle( juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle( juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
