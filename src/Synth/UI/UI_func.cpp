#include "UI_func.h"


void setSliderParams(juce::Component& parent, juce::Slider& slider, SliderStyle style){
        slider.setSliderStyle(style);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
        parent.addAndMakeVisible(slider);
}

std::unique_ptr<SliderAttachment> CreateAttachment(juce::AudioProcessorValueTreeState& params, std::string paramID, juce::Slider& slider){
    return( std::make_unique<SliderAttachment>(params, paramID, slider));
}