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
    ADSR1.initSection("ADSR1", processorRef.Params);
    addAndMakeVisible(ADSR1);
}

SynthEditor::~SynthEditor()
{
}

//==============================================================================
void SynthEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    ADSR1.paint(g);
}

void SynthEditor::resized()
{
    ADSR1.setBounds(getWidth()/2, getHeight()/2, getWidth()/2, getHeight()/2);
}
