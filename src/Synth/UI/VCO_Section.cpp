#include "VCO_Section.h"

void VCO_section::initSection(juce::AudioProcessorValueTreeState& params){
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    SUB_WaveAttachment                = std::make_unique<SliderAttachment>(params, "SUB_VCOWave", SUB_WaveSlider);
    SUB_OctaveAttachment              = std::make_unique<SliderAttachment>(params, "SUB_VCOOctaveDown", SUB_OctaveSlider); 

    VCO1_WaveAttachment                   = std::make_unique<SliderAttachment>(params, "VCO1Wave", VCO1_WaveSlider);
    VCO1_LFO_Freq_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCO1LFO_Freq_intensity", VCO1_LFO_Freq_intensitySlider);
    VCO1_LFO_Pw_intensityAttachment   = std::make_unique<SliderAttachment>(params, "VCO1LFO_Pw_intensity", VCO1_LFO_Pw_intensitySlider);

    VCO2_WaveAttachment               = std::make_unique<SliderAttachment>(params, "VCO2Wave", VCO2_WaveSlider);
    VCO2_LFO_Freq_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCO2LFO_Freq_intensity", VCO2_LFO_Freq_intensitySlider);
    VCO2_LFO_Pw_intensityAttachment   = std::make_unique<SliderAttachment>(params, "VCO2LFO_Pw_intensity", VCO2_LFO_Pw_intensitySlider);
    VCO2_DetuneAttachment             = std::make_unique<SliderAttachment>(params, "VCO2Detune", VCO2_DetuneSlider);

    setSliderParamsH(SUB_WaveSlider);
    setSliderParamsH(SUB_OctaveSlider); 

    setSliderParamsH(VCO1_WaveSlider);
    setSliderParamsV(VCO1_LFO_Freq_intensitySlider);
    setSliderParamsV(VCO1_LFO_Pw_intensitySlider);

    setSliderParamsH(VCO2_WaveSlider);
    setSliderParamsV(VCO2_LFO_Freq_intensitySlider);
    setSliderParamsV(VCO2_LFO_Pw_intensitySlider);
    setSliderParamsV(VCO2_DetuneSlider);

    bounds = getLocalBounds();
}

void VCO_section::initSection(juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    SUB_WaveAttachment                = std::make_unique<SliderAttachment>(params, "SUB_VCOWave", SUB_WaveSlider);
    SUB_OctaveAttachment              = std::make_unique<SliderAttachment>(params, "SUB_VCOOctaveDown", SUB_OctaveSlider); 

    VCO1_WaveAttachment               = std::make_unique<SliderAttachment>(params, "VCO1Wave", VCO1_WaveSlider);
    VCO1_LFO_Freq_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCO1LFO_Freq_intensity", VCO1_LFO_Freq_intensitySlider);
    VCO1_LFO_Pw_intensityAttachment   = std::make_unique<SliderAttachment>(params, "VCO1LFO_Pw_intensity", VCO1_LFO_Pw_intensitySlider);

    VCO2_WaveAttachment               = std::make_unique<SliderAttachment>(params, "VCO2Wave", VCO2_WaveSlider);
    VCO2_LFO_Freq_intensityAttachment = std::make_unique<SliderAttachment>(params, "VCO2LFO_Freq_intensity", VCO2_LFO_Freq_intensitySlider);
    VCO2_LFO_Pw_intensityAttachment   = std::make_unique<SliderAttachment>(params, "VCO2LFO_Pw_intensity", VCO2_LFO_Pw_intensitySlider);
    VCO2_DetuneAttachment             = std::make_unique<SliderAttachment>(params, "VCO2Detune", VCO2_DetuneSlider);

    setSliderParamsH(SUB_WaveSlider);
    setSliderParamsH(SUB_OctaveSlider); 

    setSliderParamsH(VCO1_WaveSlider);
    setSliderParamsV(VCO1_LFO_Freq_intensitySlider);
    setSliderParamsV(VCO1_LFO_Pw_intensitySlider);

    setSliderParamsH(VCO2_WaveSlider);
    setSliderParamsV(VCO2_LFO_Freq_intensitySlider);
    setSliderParamsV(VCO2_LFO_Pw_intensitySlider);
    setSliderParamsV(VCO2_DetuneSlider);

    bounds = juce::Rectangle(x, y, w, h);
}

void VCO_section::paint (juce::Graphics& g){
    g.fillAll(juce::Colours::black);
}

void VCO_section::resized(){

    bounds = getLocalBounds();
    const auto padding = 10;
    const auto Vslider_w = bounds.getWidth() / 6 - padding;
    const auto Vslider_h = bounds.getHeight()/ 3;

    const auto Hslider_w = bounds.getWidth()/ 5;
    const auto Hslider_h = bounds.getHeight() / 6 - padding;


    SUB_WaveSlider.setBounds(Hslider_w, 0, Hslider_w, Hslider_h);
    SUB_OctaveSlider.setBounds(SUB_WaveSlider.getRight()+Hslider_w, 0, Hslider_w, Hslider_h); 

    VCO1_LFO_Freq_intensitySlider.setBounds(0, SUB_WaveSlider.getBottom(), Vslider_w, Vslider_h);
    VCO1_LFO_Pw_intensitySlider.setBounds(VCO1_LFO_Freq_intensitySlider.getRight(), SUB_WaveSlider.getBottom(), Vslider_w, Vslider_h);

    VCO2_LFO_Freq_intensitySlider.setBounds(VCO1_LFO_Pw_intensitySlider.getRight()+Vslider_w, SUB_WaveSlider.getBottom(), Vslider_w, Vslider_h);
    VCO2_LFO_Pw_intensitySlider.setBounds(VCO2_LFO_Freq_intensitySlider.getRight(), SUB_WaveSlider.getBottom(), Vslider_w, Vslider_h);
    VCO2_DetuneSlider.setBounds(VCO2_LFO_Pw_intensitySlider.getRight(), SUB_WaveSlider.getBottom(), Vslider_w, Vslider_h);

    const auto midVCO1_X = VCO1_LFO_Pw_intensitySlider.getRight() - Hslider_w/2;
    VCO1_WaveSlider.setBounds(midVCO1_X, VCO2_DetuneSlider.getBottom(), Hslider_w, Hslider_h);
    const auto midVCO2_X = VCO2_DetuneSlider.getRight() - VCO1_LFO_Pw_intensitySlider.getRight() + Vslider_w - Hslider_w/2;
    VCO2_WaveSlider.setBounds(midVCO2_X, VCO2_DetuneSlider.getBottom(), Hslider_w, Hslider_h);
}

void VCO_section::setSliderParamsV(juce::Slider& slider){
    slider.setSliderStyle( juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle( juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

void VCO_section::setSliderParamsH(juce::Slider& slider){
    slider.setSliderStyle( juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle( juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}