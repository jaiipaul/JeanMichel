#include "SynthAudioProcessor.h"
#include "SynthEditor.h"

//==============================================================================
SynthEditor::SynthEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    //juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1024, 512);
    const auto bounds = getLocalBounds();
    VCA.initSection("ADSR1", processorRef.Params);
    addAndMakeVisible(VCA);

    VCOs.initSection(processorRef.Params);
    addAndMakeVisible(VCOs);

    MIX.initSection("MIXER", processorRef.Params);
    addAndMakeVisible(MIX);

    VCF.initSection("ADSR2", processorRef.Params);
    addAndMakeVisible(VCF);

    LFO1.initSection("LFO1", processorRef.Params);
    addAndMakeVisible(LFO1);

    LFO2.initSection("LFO2", processorRef.Params);
    addAndMakeVisible(LFO2);
    
}

SynthEditor::~SynthEditor()
{
}

//==============================================================================
void SynthEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    VCOs.paint(g);
    MIX.paint(g);
    VCA.paint(g);
    VCF.paint(g);
    LFO1.paint(g);
    LFO2.paint(g);
}

void SynthEditor::resized()
{
    VCOs.setBounds(0, 0, getWidth()/2, getHeight()/2);
    VCF.setBounds(0, getHeight()/2, getWidth()/2, getHeight()/2);
    MIX.setBounds(getWidth()/2, 0, getWidth()/6, getHeight()/2);
    LFO1.setBounds(4*getWidth()/6, 0, getWidth()/6, getHeight()/2);
    LFO2.setBounds(5*getWidth()/6, 0, getWidth()/6, getHeight()/2);
    VCA.setBounds(getWidth()/2, getHeight()/2, getWidth()/2, getHeight()/2);
}
