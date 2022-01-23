#ifndef _SYNTHSOUND_H_
#define _SYNTHSOUND_H_

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound{
public:
    bool appliesToNote(int midiNoteNumber) override;
    bool appliesToChannel(int midiChannel) override; 
};
#endif // _SYNTHSOUND_H_