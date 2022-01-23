#include "SynthAudioProcessor.h"
#include "SynthEditor.h"

//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
    Synth.addSound(new SynthSound());
    Synth.addVoice(new SynthVoice());
}

SynthAudioProcessor::~SynthAudioProcessor()
{
}

//==============================================================================
const juce::String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String SynthAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Synth.setCurrentPlaybackSampleRate(sampleRate);
    for(int i = 0; i < Synth.getNumVoices(); i++){
        if(auto voice = dynamic_cast<SynthVoice*>(Synth.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for(int i = 0; i < Synth.getNumVoices(); i++){
        if(auto voice = dynamic_cast<juce::SynthesiserVoice*>(Synth.getVoice(i))){
            // CONTROLS UPDATE
        }
    }
    Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(this);
    //return new SynthEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

// PARAMETERS ==================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SynthAudioProcessor::createParameterLayout(){
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    //"SUB_VCO"
        layout.add(std::make_unique<juce::AudioParameterInt>("SUB_VCO_OctaveDown", "SUB_VCO_OctaveDown", 1, 2, 1));               
        layout.add(std::make_unique<juce::AudioParameterBool>("SUB_VCO_Sine", "SUB_VCO_Sine", true));
        layout.add(std::make_unique<juce::AudioParameterBool>("SUB_VCO_Triangle", "SUB_VCO_Triangle", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("SUB_VCO_Saw", "SUB_VCO_Saw", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("SUB_VCO_Square", "SUB_VCO_Square", false));
    //"VCO1"
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCO1_LFO_Freq_intensity", "VCO1_LFO_Freq_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCO1_LFO_Pw_intensity", "VCO1_LFO_Pw_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO1_Sine", "VCO1_Sine", true));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO1_Triangle", "VCO1_Triangle", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO1_Saw", "VCO1_Saw", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO1_Square", "VCO1_Square", false));
    //"VCO2"
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCO2_Detune", "VCO2_Detune", 
                                       juce::NormalisableRange<float>(0.f, 12.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCO2_LFO_Freq_intensity", "VCO2_LFO_Freq_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCO2_LFO_Pw_intensity", "VCO2_LFO_Pw_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO2_Sine", "VCO2_Sine", true));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO2_Triangle", "VCO2_Triangle", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO2_Saw", "VCO2_Saw", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("VCO2_Square", "VCO2_Square", false));
    //"LFO1"
        layout.add(std::make_unique<juce::AudioParameterFloat>("LFO1_Rate", "LFO1_Rate", 
                                   juce::NormalisableRange<float>(0.5f, 20.f, 0.001f, 1.f), 1.f));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO1_Sine", "LFO1_Sine", true));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO1_Triangle", "LFO1_Triangle", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO1_Saw", "LFO1_Saw", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO1_Square", "LFO1_Square", false));
    //"LFO2"
        layout.add(std::make_unique<juce::AudioParameterFloat>("LFO2_Rate", "LFO2_Rate", 
                                   juce::NormalisableRange<float>(0.5f, 20.f, 0.001f, 1.f), 1.f));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO2_Sine", "LFO2_Sine", true));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO2_Triangle", "LFO2_Triangle", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO2_Saw", "LFO2_Saw", false));
        layout.add(std::make_unique<juce::AudioParameterBool>("LFO2_Square", "LFO2_Square", false));

    //"VCF"
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCF_Cutoff", "VCF_Cutoff", 
                                   juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20000.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCF_Resonance", "VCF_Resonance", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCF_Drive", "VCF_Drive", 
                                   juce::NormalisableRange<float>(1.f, 2.f, 0.001f, 1.f), 0.f));
        
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCF_LFO_intensity", "VCF_LFO_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCF_ENV_intensity", "VCF_ENV_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
    //"VCA"
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCA_Volume", "VCA_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("VCA_ENV_intensity", "VCA_ENV_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
    //"MIXER"
        layout.add(std::make_unique<juce::AudioParameterFloat>("MIXER_SUB_VCO_Volume", "MIXER_SUB_VCO_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));            
        layout.add(std::make_unique<juce::AudioParameterFloat>("MIXER_VCO1_Volume", "MIXER_VCO1_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f));            
        layout.add(std::make_unique<juce::AudioParameterFloat>("MIXER_VCO2_Volume", "MIXER_VCO2_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f)); 
    //"ADSR1"
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR1_Attack", "ADSR1_Attack", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR1_Decay", "ADSR1_Decay", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR1_Sustain", "ADSR1_Sustain", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR1_Release", "ADSR1_Release", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
    //"ADSR2"
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR2_Attack", "ADSR2_Attack", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR2_Decay", "ADSR2_Decay", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR2_Sustain", "ADSR2_Sustain", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>("ADSR2_Release", "ADSR2_Release", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
    return(layout);
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}
