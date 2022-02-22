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
            voice->update(Params);
        }
    }
    
    Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    leftRMSlvl  = Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    rightRMSlvl = Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
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


float SynthAudioProcessor::getRMSvalue(const int channel){
    jassert(channel == 0 || channel == 1);
    if(channel == 0){
        return leftRMSlvl;
    }else if(channel == 1){
        return rightRMSlvl;
    }
}

// PARAMETERS ==================================================================
juce::AudioProcessorValueTreeState::ParameterLayout SynthAudioProcessor::createParameterLayout(){
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    //"SUB_VCO"
        std::string ID = "SUB_VCO";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Sub_Vco_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Sub_Vco_params->addChild(std::make_unique<juce::AudioParameterInt>(ID+"OctaveDown", ID+"OctaveDown", 1, 2, 1));               
        Sub_Vco_params->addChild(std::make_unique<juce::AudioParameterInt>(ID+"Wave", ID+"Wave", 1, 4, 1));
  
    //"VCO1"
        ID = "VCO1";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vco1_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Vco1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"PulseWidth", ID+"PulseWidth", 
                                   juce::NormalisableRange<float>(0.05f, 0.9f, 0.001f, 1.f), 0.5f));
        Vco1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"LFO_Freq_intensity", ID+"LFO_Freq_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"LFO_Pw_intensity", ID+"LFO_Pw_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco1_params->addChild(std::make_unique<juce::AudioParameterInt>(ID+"Wave", ID+"Wave", 1, 4, 1));
    //"VCO2"
        ID = "VCO2";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vco2_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Detune", ID+"Detune", 
                                       juce::NormalisableRange<float>(0.f, 12.f, 0.001f, 1.f), 0.f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"PulseWidth", ID+"PulseWidth", 
                                       juce::NormalisableRange<float>(0.05f, 0.9f, 0.001f, 1.f), 0.5f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"LFO_Freq_intensity", ID+"LFO_Freq_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"LFO_Pw_intensity", ID+"LFO_Pw_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vco2_params->addChild(std::make_unique<juce::AudioParameterInt>(ID+"Wave", ID+"Wave", 1, 4, 1));
    //"LFO1"
        ID = "LFO1";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Lfo1_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Lfo1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Rate", ID+"Rate", 
                                   juce::NormalisableRange<float>(0.5f, 20.f, 0.001f, 1.f), 1.f));
        Lfo1_params->addChild(std::make_unique<juce::AudioParameterInt>(ID+"Wave", ID+"Wave", 1, 4, 1));

    //"LFO2"
        ID = "LFO2";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Lfo2_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Lfo2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Rate", ID+"Rate", 
                                   juce::NormalisableRange<float>(0.5f, 20.f, 0.001f, 1.f), 1.f));
        Lfo2_params->addChild(std::make_unique<juce::AudioParameterInt>(ID+"Wave", ID+"Wave", 1, 4, 1));

    //"VCF"
        ID = "VCF";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vcf_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Cutoff", ID+"Cutoff", 
                                   juce::NormalisableRange<float>(20.f, 25000.f, 1.f, 1.f), 25000.f));
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Resonance", ID+"Resonance", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Drive", ID+"Drive", 
                                   juce::NormalisableRange<float>(1.f, 2.f, 0.001f, 1.f), 0.f));
        
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"LFO_intensity", ID+"LFO_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
        Vcf_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"ENV_intensity", ID+"ENV_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));
    //"VCA"
        ID = "VCA";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Vca_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Vca_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Volume", ID+"Volume", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f));
        Vca_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"ENV_intensity", ID+"ENV_intensity", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 1.f));
    //"MIXER"
        ID = "MIXER";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Mixer_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Mixer_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Volume0", ID+"Volume0", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.f));            
        Mixer_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Volume1", ID+"Volume1", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f));            
        Mixer_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Volume2", ID+"Volume2", 
                                   juce::NormalisableRange<float>(0.f, 1.f, 0.001f, 1.f), 0.95f)); 
    //"ADSR1"
        ID = "ADSR1";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Adsr1_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Attack", ID+"Attack", 
                                   juce::NormalisableRange<float>(0.001f, 3.f, 0.001f, 1.f), 0.001f));
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Decay", ID+"Decay", 
                                   juce::NormalisableRange<float>(0.001f, 1.f, 0.001f, 1.f), 0.001f));
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Sustain", ID+"Sustain", 
                                   juce::NormalisableRange<float>(0.001f, 1.f, 0.001f, 1.f), 1.f));
        Adsr1_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Release", ID+"Release", 
                                   juce::NormalisableRange<float>(0.001f, 5.f, 0.001f, 1.f), 0.001f));
    //"ADSR2"
        ID = "ADSR2";
        std::unique_ptr<juce::AudioProcessorParameterGroup> Adsr2_params =
            std::make_unique<juce::AudioProcessorParameterGroup>(ID, ID, "__");
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Attack", ID+"Attack", 
                                   juce::NormalisableRange<float>(0.001f, 3.f, 0.001f, 1.f), 0.001f));
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Decay", ID+"Decay", 
                                   juce::NormalisableRange<float>(0.001f, 1.f, 0.001f, 1.f), 0.001f));
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Sustain", ID+"Sustain", 
                                   juce::NormalisableRange<float>(0.001f, 1.f, 0.001f, 1.f), 1.f));
        Adsr2_params->addChild(std::make_unique<juce::AudioParameterFloat>(ID+"Release", ID+"Release", 
                                   juce::NormalisableRange<float>(0.001f, 5.f, 0.001f, 1.f), 0.001f));

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
