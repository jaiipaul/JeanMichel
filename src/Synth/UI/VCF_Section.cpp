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
    setBounds(bounds);
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
    setBounds(bounds);
}

void VCF_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
    ADSR.paint(g);
}

void VCF_section::resized(){
    int boundsX = bounds.getX();
    int boundsY = bounds.getY();

    const auto slider_w = 14;
    const auto slider_h = 110;

    VCF_CutoffSlider.setBounds(18, 48, 104, 104);
    VCF_ResonanceSlider.setBounds(147, 47, slider_w, slider_h);
    VCF_DriveSlider.setBounds(181,  47, slider_w, slider_h);

    VCF_ENV_intensitySlider.setBounds(219,  47, slider_w, slider_h);
    VCF_LFO_intensitySlider.setBounds(253,  47, slider_w, slider_h); 
    
    ADSR.setBounds(291, 47, 116, slider_h);
    ADSR.resized();    
}
