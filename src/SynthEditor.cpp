#include "SynthAudioProcessor.h"
#include "SynthEditor.h"

//==============================================================================
SynthEditor::SynthEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    //juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    juce::LookAndFeel::setDefaultLookAndFeel(&CustomLookAndFeel);

    setSize (931, 512);
    const auto bounds = getLocalBounds();
    VCA.initSection("ADSR1", processorRef.Params, 494, 327, 337, 170);
    addAndMakeVisible(VCA);

    VCOs.initSection(processorRef.Params, 12, 82, 270, 480);
    addAndMakeVisible(VCOs);

    MIX.initSection("MIXER", processorRef.Params, 288, 82, 200, 151);
    addAndMakeVisible(MIX);

    VCF.initSection("ADSR2", processorRef.Params, 494, 82, 425, 170);
    addAndMakeVisible(VCF);

    LFO1.initSection("LFO1", processorRef.Params, 288, 239, 200, 126);
    addAndMakeVisible(LFO1);
    //std::cout << LFO1.getBounds().getX()<< "|" << LFO1.getBounds().getY() << std::endl;
    
    LFO2.initSection("LFO2", processorRef.Params, 288, 371, 200, 126);
    addAndMakeVisible(LFO2);
    
    BackGround = juce::ImageCache::getFromMemory(assets::jeanmichel_png, assets::jeanmichel_pngSize);
}

SynthEditor::~SynthEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void SynthEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.drawImage(BackGround, 0, 0, 931, 512, 0, 0, BackGround.getWidth(), BackGround.getHeight());
    VCOs.paint(g);
    MIX.paint(g);
    VCA.paint(g);
    VCF.paint(g);
    LFO1.paint(g);
    LFO2.paint(g);
}

void SynthEditor::resized()
{
    //VCOs.setBounds(12, 82, 270, 480);
    //VCF.setBounds(0, getHeight()/2, getWidth()/2, getHeight()/2);
    //MIX.setBounds(getWidth()/2, 0, getWidth()/6, getHeight()/2);
    //LFO1.setBounds(4*getWidth()/6, 0, getWidth()/6, getHeight()/2);
    //LFO2.setBounds(5*getWidth()/6, 0, getWidth()/6, getHeight()/2);
    //VCA.setBounds(getWidth()/2, getHeight()/2, getWidth()/2, getHeight()/2);
}
