#include "VCO_Section.h"
#include <BinaryData.h>

void VCO_section::initSection(juce::AudioProcessorValueTreeState& params){
    SUB_WaveSlider.initSlider("SUB_VCOWave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);
    addAndMakeVisible(SUB_WaveSlider);

    SUB_OctaveSlider.initSlider("SUB_VCOOctaveDown", params, assets::octaves_png, assets::octaves_pngSize, 256, 256, 2);
    addAndMakeVisible(SUB_OctaveSlider); 

    VCO1_WaveSlider.initSlider("VCO1Wave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);
    addAndMakeVisible(VCO1_WaveSlider);

    setSliderParams(*this, VCO1_PulseWidthSlider, "VCO1PulseWidth", juce::Slider::SliderStyle::LinearVertical);
    VCO1_PulseWidthAttachment         = CreateAttachment(params, "VCO1PulseWidth", VCO1_PulseWidthSlider);
    setSliderParams(*this, VCO1_LFO_Freq_intensitySlider, "VCO1LFO_Freq_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO1LFO_Freq_intensity", VCO1_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO1_LFO_Pw_intensitySlider, "VCO1LFO_Pw_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO1LFO_Pw_intensity", VCO1_LFO_Pw_intensitySlider);

    VCO2_WaveSlider.initSlider("VCO2Wave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);
    addAndMakeVisible(VCO2_WaveSlider);

    setSliderParams(*this, VCO2_PulseWidthSlider, "VCO2PulseWidth", juce::Slider::SliderStyle::LinearVertical);
    VCO2_PulseWidthAttachment         = CreateAttachment(params, "VCO2PulseWidth", VCO2_PulseWidthSlider);
    setSliderParams(*this, VCO2_LFO_Freq_intensitySlider, "VCO2LFO_Freq_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO2LFO_Freq_intensity", VCO2_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO2_LFO_Pw_intensitySlider, "VCO2LFO_Pw_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO2LFO_Pw_intensity", VCO2_LFO_Pw_intensitySlider);
    setSliderParams(*this, VCO2_DetuneSlider, "VCO2Detune", juce::Slider::SliderStyle::LinearVertical);
    VCO2_DetuneAttachment             = CreateAttachment(params, "VCO2Detune", VCO2_DetuneSlider);

    bounds = getLocalBounds();
    setBounds(bounds);
}

void VCO_section::initSection(juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
    SUB_WaveSlider.initSlider("SUB_VCOWave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);
    addAndMakeVisible(SUB_WaveSlider);

    SUB_OctaveSlider.initSlider("SUB_VCOOctaveDown", params, assets::octaves_png, assets::octaves_pngSize, 256, 256, 2);
    addAndMakeVisible(SUB_OctaveSlider); 

    VCO1_WaveSlider.initSlider("VCO1Wave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);
    addAndMakeVisible(VCO1_WaveSlider);

    setSliderParams(*this, VCO1_PulseWidthSlider, "VCO1PulseWidth", juce::Slider::SliderStyle::LinearVertical);
    VCO1_PulseWidthAttachment         = CreateAttachment(params, "VCO1PulseWidth", VCO1_PulseWidthSlider);
    setSliderParams(*this, VCO1_LFO_Freq_intensitySlider, "VCO1LFO_Freq_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO1LFO_Freq_intensity", VCO1_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO1_LFO_Pw_intensitySlider, "VCO1LFO_Pw_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO1_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO1LFO_Pw_intensity", VCO1_LFO_Pw_intensitySlider);

    VCO2_WaveSlider.initSlider("VCO2Wave", params, assets::waves_png, assets::waves_pngSize, 256, 256, 4);
    addAndMakeVisible(VCO2_WaveSlider);

    setSliderParams(*this, VCO2_PulseWidthSlider, "VCO2PulseWidth", juce::Slider::SliderStyle::LinearVertical);
    VCO2_PulseWidthAttachment         = CreateAttachment(params, "VCO2PulseWidth", VCO2_PulseWidthSlider);
    setSliderParams(*this, VCO2_LFO_Freq_intensitySlider, "VCO2LFO_Freq_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Freq_intensityAttachment = CreateAttachment(params, "VCO2LFO_Freq_intensity", VCO2_LFO_Freq_intensitySlider);
    setSliderParams(*this, VCO2_LFO_Pw_intensitySlider, "VCO2LFO_Pw_intensity", juce::Slider::SliderStyle::LinearVertical);
    VCO2_LFO_Pw_intensityAttachment   = CreateAttachment(params, "VCO2LFO_Pw_intensity", VCO2_LFO_Pw_intensitySlider);
    setSliderParams(*this, VCO2_DetuneSlider, "VCO2Detune", juce::Slider::SliderStyle::LinearVertical);
    VCO2_DetuneAttachment             = CreateAttachment(params, "VCO2Detune", VCO2_DetuneSlider);

    bounds = juce::Rectangle(x, y, w, h);
    setBounds(bounds);
}

void VCO_section::paint (juce::Graphics& g){
    SUB_WaveSlider.Update();
    SUB_OctaveSlider.Update();
    VCO1_WaveSlider.Update();
    VCO2_WaveSlider.Update();
}

void VCO_section::resized(){
    int boundsX = bounds.getX();
    int boundsY = bounds.getY();

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

    SUB_WaveSlider.resized();
    VCO1_WaveSlider.resized();
    VCO2_WaveSlider.resized();
}
