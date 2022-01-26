#pragma once

#include "SynthAudioProcessor.h"
#include "Synth/UI/ADSR_Section.h"

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
    
    SynthAudioProcessor& processorRef;
    ADSR_section ADSR1;
   

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthEditor)
};
