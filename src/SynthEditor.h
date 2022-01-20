#pragma once

#include "SynthAudioProcessor.h"

//==============================================================================
class SynthEditor  : public juce::AudioProcessorEditor
{
public:
    explicit SynthEditor (SynthAudioProcessor&);
    ~SynthEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthEditor)
};
