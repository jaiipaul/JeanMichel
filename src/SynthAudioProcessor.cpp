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
    //juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for(int i = 0; i < Synth.getNumVoices(); i++){
        if(auto voice = dynamic_cast<SynthVoice*>(Synth.getVoice(i))){
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
    //std::cout << Params.getRawParameterValue("ADSR1__Attack") << std::endl;
    //return new juce::GenericAudioProcessorEditor(*this);
    return new SynthEditor (*this);
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
        std::unique_ptr<juce::AudioProcessorParameterGroup> Sub_Vco_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("SUB_VCO", "SUB_VCO", "__");
        Sub_Vco_params->addChild(std::make_unique<juce::AudioParameterInt>("OctaveDown", "OctaveDown", 1, 2, 1));               
        Sub_Vco_params->addChild(std::make_unique<juce::AudioParameterInt>("Wave", "Wave", 1, 4, 1));
  
    //"VCO1"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vco1_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("VCO1", "VCO1", "__");
        Vco1_params->addChild(std::make_unique<juce::AudioParameterFloat>("LFO_Freq_intensity", "LFO_Freq_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco1_params->addChild(std::make_unique<juce::AudioParameterFloat>("LFO_Pw_intensity", "LFO_Pw_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco1_params->addChild(std::make_unique<juce::AudioParameterInt>("Wave", "Wave", 1, 4, 1));
    //"VCO2"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vco2_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("VCO2", "VCO2", "__");
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>("Detune", "Detune", 
                                       juce::NormalisableRange<float>(0.f, 12.f, 0.001f, 1.f), 0.f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>("LFO_Freq_intensity", "LFO_Freq_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>("LFO_Pw_intensity", "LFO_Pw_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterInt>("Wave", "Wave", 1, 4, 1));
    //"LFO1"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Lfo1_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("LFO1", "LFO1", "__");
        Lfo1_params->addChild(std::make_unique<juce::AudioParameterFloat>("Rate", "Rate", 
                                   juce::NormalisableRange<float>(0.5f, 20.f, 0.001f, 1.f), 1.f));
        Lfo1_params->addChild(std::make_unique<juce::AudioParameterInt>("Wave", "Wave", 1, 4, 1));

    //"LFO2"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Lfo2_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("LFO2", "LFO2", "__");
        Lfo2_params->addChild(std::make_unique<juce::AudioParameterFloat>("Rate", "Rate", 
                                   juce::NormalisableRange<float>(0.5f, 20.f, 0.001f, 1.f), 1.f));
        Lfo2_params->addChild(std::make_unique<juce::AudioParameterInt>("Wave", "Wave", 1, 4, 1));

    //"VCF"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vcf_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("VCF", "VCF", "__");
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>("Cutoff", "Cutoff", 
                                   juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20000.f));
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>("Resonance", "Resonance", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>("Drive", "Drive", 
                                   juce::NormalisableRange<float>(1.f, 2.f, 0.001f, 1.f), 0.f));
        
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>("LFO_intensity", "LFO_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>("ENV_intensity", "ENV_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
    //"VCA"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vca_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("VCA", "VCA", "__");
        Vca_params->addChild(std::make_unique<juce::AudioParameterFloat>("Volume", "Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f));
        Vca_params->addChild(std::make_unique<juce::AudioParameterFloat>("ENV_intensity", "ENV_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
    //"MIXER"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Mixer_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("MIXER", "MIXER", "__");
        Mixer_params->addChild(std::make_unique<juce::AudioParameterFloat>("SUB_VCO_Volume", "SUB_VCO_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));            
        Mixer_params->addChild(std::make_unique<juce::AudioParameterFloat>("VCO1_Volume", "VCO1_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f));            
        Mixer_params->addChild(std::make_unique<juce::AudioParameterFloat>("VCO2_Volume", "VCO2_Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f)); 
    //"ADSR1"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Adsr1_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("ADSR1", "ADSR1", "__");
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>("Attack", "Attack", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.7f));
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>("Decay", "Decay", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>("Sustain", "Sustain", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>("Release", "Release", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
    //"ADSR2"
        std::unique_ptr<juce::AudioProcessorParameterGroup> Adsr2_params =
            std::make_unique<juce::AudioProcessorParameterGroup>("ADSR2", "ADSR2", "__");
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>("Attack", "Attack", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>("Decay", "Decay", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>("Sustain", "Sustain", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>("Release", "Release", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));

    layout.add(std::move(Sub_Vco_params));
    layout.add(std::move(Vco1_params));
    layout.add(std::move(Vco2_params));
    layout.add(std::move(Lfo1_params));
    layout.add(std::move(Lfo2_params));
    layout.add(std::move(Vcf_params));
    layout.add(std::move(Vca_params));
    layout.add(std::move(Mixer_params));
    layout.add(std::move(Adsr1_params));
    layout.add(std::move(Adsr2_params));
    return(layout);
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}
