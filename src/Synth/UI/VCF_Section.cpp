#include "VCF_Section.h"

void VCF_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);


    setSliderParams(*this, VCF_CutoffSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    VCF_CutoffAttachment        = CreateAttachment(params, "VCFCutoff", VCF_CutoffSlider);
    setSliderParams(*this, VCF_ResonanceSlider, juce::Slider::SliderStyle::LinearVertical);
    VCF_ResonanceAttachment     = CreateAttachment(params, "VCFResonance", VCF_ResonanceSlider);
    setSliderParams(*this, VCF_DriveSlider, juce::Slider::SliderStyle::LinearVertical);
    VCF_DriveAttachment         = CreateAttachment(params, "VCFDrive", VCF_DriveSlider);
    setSliderParams(*this, VCF_LFO_intensitySlider, juce::Slider::SliderStyle::LinearVertical); 
    VCF_LFO_intensityAttachment = CreateAttachment(params, "VCFLFO_intensity", VCF_LFO_intensitySlider); 
    setSliderParams(*this, VCF_ENV_intensitySlider, juce::Slider::SliderStyle::LinearVertical); 
    VCF_ENV_intensityAttachment = CreateAttachment(params, "VCFENV_intensity", VCF_ENV_intensitySlider); 


    bounds = getLocalBounds();
}

void VCF_section::initSection(std::string ADSR_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    ADSR.initSection(ADSR_ID, params);
    addAndMakeVisible(ADSR);

    setSliderParams(*this, VCF_CutoffSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    VCF_CutoffAttachment        = CreateAttachment(params, "VCFCutoff", VCF_CutoffSlider);
    setSliderParams(*this, VCF_ResonanceSlider, juce::Slider::SliderStyle::LinearVertical);
    VCF_ResonanceAttachment     = CreateAttachment(params, "VCFResonance", VCF_ResonanceSlider);
    setSliderParams(*this, VCF_DriveSlider, juce::Slider::SliderStyle::LinearVertical);
    VCF_DriveAttachment         = CreateAttachment(params, "VCFDrive", VCF_DriveSlider);
    setSliderParams(*this, VCF_LFO_intensitySlider, juce::Slider::SliderStyle::LinearVertical); 
    VCF_LFO_intensityAttachment = CreateAttachment(params, "VCFLFO_intensity", VCF_LFO_intensitySlider); 
    setSliderParams(*this, VCF_ENV_intensitySlider, juce::Slider::SliderStyle::LinearVertical); 
    VCF_ENV_intensityAttachment = CreateAttachment(params, "VCFENV_intensity", VCF_ENV_intensitySlider);  

    bounds = juce::Rectangle(x, y, w, h);
}

void VCF_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
    ADSR.paint(g);
}

void VCF_section::resized(){

    bounds = getLocalBounds();
    const auto padding = 10;

    const auto Rslider_w = bounds.getWidth()/ 3 - 2 * padding;
    const auto Rslider_h = bounds.getHeight() - 2 * padding;

    const auto slider_w = (2*bounds.getWidth() / 3 ) / 9 - padding;
    const auto slider_h = bounds.getHeight() - 2*padding;

    VCF_CutoffSlider.setBounds(padding, padding, Rslider_w, Rslider_h);
    VCF_ResonanceSlider.setBounds(VCF_CutoffSlider.getRight()+padding, padding, slider_w, slider_h);
    VCF_DriveSlider.setBounds(VCF_ResonanceSlider.getRight()+padding, padding, slider_w, slider_h);
    
    VCF_ENV_intensitySlider.setBounds(VCF_DriveSlider.getRight()+2*padding, padding, slider_w, slider_h);
    VCF_LFO_intensitySlider.setBounds(VCF_ENV_intensitySlider.getRight()+padding, padding, slider_w, slider_h); 

    ADSR.setBounds(VCF_LFO_intensitySlider.getRight()+2*padding, padding, 4* (2*bounds.getWidth() / 3 )/9, slider_h);
    ADSR.resized();
}
