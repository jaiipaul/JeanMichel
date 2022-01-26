#include "ADSR_Section.h"

void ADSR_section::initSection(juce::AudioProcessorValueTreeState& params){
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    AttackAttachment  = std::make_unique<SliderAttachment>(params, "ADSR1__Attack", AttackSlider);
    SustainAttachment = std::make_unique<SliderAttachment>(params, "ADSR1__Decay", DecaySlider);
    DecayAttachment   = std::make_unique<SliderAttachment>(params, "ADSR1__Sustain", SustainSlider);
    ReleaseAttachment = std::make_unique<SliderAttachment>(params, "ADSR1__Release", ReleaseSlider);

    //setSliderParams(AttackSlider);
    //setSliderParams(DecaySlider);
    //setSliderParams(SustainSlider);
    //setSliderParams(ReleaseSlider);
}

void ADSR_section::paint (juce::Graphics&){

}
void ADSR_section::resized(){

}

void ADSR_section::setSliderParams(juce::Slider& slider){
    
}