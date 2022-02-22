#pragma once

#include "SynthAudioProcessor.h"
#include "Synth/UI/VCA_Section.h"
#include "Synth/UI/VCO_Section.h"
#include "Synth/UI/MIX_Section.h"
#include "Synth/UI/VCF_Section.h"
#include "Synth/UI/LFO_section.h"
#include "Synth/UI/CLookAndFeel.h"
#include "Synth/UI/Meter.h"
#include <BinaryData.h>

//==============================================================================
class SynthEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    explicit SynthEditor (SynthAudioProcessor&);
    ~SynthEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Image BackGround;
    
    SynthAudioProcessor& processorRef;
    CLookAndFeel CustomLookAndFeel;
    
    juce::Meter leftLevelMeter;
    juce::Meter rightLevelMeter;

    VCA_section VCA;
    VCO_section VCOs;
    MIX_section MIX;
    VCF_section VCF;
    LFO_section LFO1;
    LFO_section LFO2;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthEditor)
};
