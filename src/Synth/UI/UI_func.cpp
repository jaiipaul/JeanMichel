#include "UI_func.h"
#include "WaveSlider.h"

void setSliderParams(juce::Component& parent, juce::Slider& slider, std::string ID, SliderStyle style){
        slider.setComponentID(ID);
        slider.setSliderStyle(style);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
        //std::cout << ID << " : " << parent.getX() << "|" << parent.getY() << std::endl;
        parent.addAndMakeVisible(slider);
}


std::unique_ptr<SliderAttachment> CreateAttachment(juce::AudioProcessorValueTreeState& params, std::string paramID, juce::Slider& slider){
    return( std::make_unique<SliderAttachment>(params, paramID, slider));
}