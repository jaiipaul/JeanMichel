#ifndef _UI_FUNC_H_
#define _UI_FUNC_H_

#include <JuceHeader.h>

using SliderStyle = juce::Slider::SliderStyle;
using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void setSliderParams(juce::Component& parent, juce::Slider& slider, SliderStyle style);

std::unique_ptr<SliderAttachment> CreateAttachment(juce::AudioProcessorValueTreeState& params, std::string paramID, juce::Slider& slider);


#endif // _UI_FUNC_H_