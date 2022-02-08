#include "VCO_Section.h"

void VCO_section::initSection(juce::AudioProcessorValueTreeState& params){

    setSliderParams(*this, SUB_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    SUB_WaveAttachment                = CreateAttachment(params, "SUB_VCOWave", SUB_WaveSlider);
    setSliderParams(*this, SUB_OctaveSlider,juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    SUB_OctaveAttachment              = CreateAttachment(params, "SUB_VCOOctaveDown", SUB_OctaveSlider); 

    setSliderParams(*this, VCO1_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    VCO1_WaveAttachment               = CreateAttachment(params, "VCO1Wave", VCO1_WaveSlider);
    setSliderParams(*this, VCO1_PulseWidthSlider, juce::Slider::SliderStyle::LinearVertical);
    VCO1_PulseWidthAttachment         = CreateAttachment(params, "VCO1PulseWidth", VCO1_PulseWidthSlider);
    setSliderParams(*this, VCO1_LFO_Freq_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO1LFO_Freq_intensity", VCO1_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO1_LFO_Pw_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO1LFO_Pw_intensity", VCO1_LFO_Pw_intensitySlider);

    setSliderParams(*this, VCO2_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    VCO2_WaveAttachment               = CreateAttachment(params, "VCO2Wave", VCO2_WaveSlider);
    setSliderParams(*this, VCO2_PulseWidthSlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_PulseWidthAttachment         = CreateAttachment(params, "VCO2PulseWidth", VCO2_PulseWidthSlider);
    setSliderParams(*this, VCO2_LFO_Freq_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO2LFO_Freq_intensity", VCO2_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO2_LFO_Pw_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO2LFO_Pw_intensity", VCO2_LFO_Pw_intensitySlider);
    setSliderParams(*this, VCO2_DetuneSlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_DetuneAttachment             = CreateAttachment(params, "VCO2Detune", VCO2_DetuneSlider);

    bounds = getLocalBounds();
    setBounds(bounds);
}

void VCO_section::initSection(juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    
    setSliderParams(*this, SUB_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    SUB_WaveAttachment                = CreateAttachment(params, "SUB_VCOWave", SUB_WaveSlider);
    setSliderParams(*this, SUB_OctaveSlider,juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    SUB_OctaveAttachment              = CreateAttachment(params, "SUB_VCOOctaveDown", SUB_OctaveSlider); 

    setSliderParams(*this, VCO1_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    VCO1_WaveAttachment               = CreateAttachment(params, "VCO1Wave", VCO1_WaveSlider);
    setSliderParams(*this, VCO1_PulseWidthSlider, juce::Slider::SliderStyle::LinearVertical);
    VCO1_PulseWidthAttachment         = CreateAttachment(params, "VCO1PulseWidth", VCO1_PulseWidthSlider);
    setSliderParams(*this, VCO1_LFO_Freq_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO1LFO_Freq_intensity", VCO1_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO1_LFO_Pw_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO1LFO_Pw_intensity", VCO1_LFO_Pw_intensitySlider);

    setSliderParams(*this, VCO2_WaveSlider, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    VCO2_WaveAttachment               = CreateAttachment(params, "VCO2Wave", VCO2_WaveSlider);
    setSliderParams(*this, VCO2_PulseWidthSlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_PulseWidthAttachment         = CreateAttachment(params, "VCO2PulseWidth", VCO2_PulseWidthSlider);
    setSliderParams(*this, VCO2_LFO_Freq_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO2LFO_Freq_intensity", VCO2_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO2_LFO_Pw_intensitySlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO2LFO_Pw_intensity", VCO2_LFO_Pw_intensitySlider);
    setSliderParams(*this, VCO2_DetuneSlider, juce::Slider::SliderStyle::LinearVertical);
    VCO2_DetuneAttachment             = CreateAttachment(params, "VCO2Detune", VCO2_DetuneSlider);

    bounds = juce::Rectangle(x, y, w, h);
    setBounds(bounds);
}

void VCO_section::paint (juce::Graphics& g){
    //g.fillAll(juce::Colours::black);
}

void VCO_section::resized(){
    int boundsX = bounds.getX();
    int boundsY = bounds.getY();
    std::cout << boundsX << "/" << boundsY << std::endl;

    const auto Vslider_w = 14;
    const auto Vslider_h = 110;


    SUB_WaveSlider.setBounds(58-boundsX, 110-boundsY, 45, 45);
    SUB_OctaveSlider.setBounds(191-boundsX, 110-boundsY, 45, 45); 

    VCO1_LFO_Freq_intensitySlider.setBounds(175-boundsX, 205-boundsY, Vslider_w, Vslider_h);
    VCO1_LFO_Pw_intensitySlider.setBounds(236-boundsX, 205-boundsY, Vslider_w, Vslider_h);
    VCO1_PulseWidthSlider.setBounds(105-boundsX, 205-boundsY, Vslider_w, Vslider_h);

    VCO2_LFO_Freq_intensitySlider.setBounds(206-boundsX, 372-boundsY, Vslider_w, Vslider_h);
    VCO2_LFO_Pw_intensitySlider.setBounds(243-boundsX, 372-boundsY, Vslider_w, Vslider_h);
    VCO2_PulseWidthSlider.setBounds(105-boundsX, 372-boundsY, Vslider_w, Vslider_h);
    VCO2_DetuneSlider.setBounds(168-boundsX,372-boundsY, Vslider_w, Vslider_h);

    VCO1_WaveSlider.setBounds(31-boundsX, 235-boundsY, 50, 50);
    VCO2_WaveSlider.setBounds(31-boundsX, 403-boundsY, 50, 50);
}
