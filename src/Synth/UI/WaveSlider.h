#ifndef _WAVE_SLIDER_H_
#define _WAVE_SLIDER_H_

#include <JuceHeader.h>

namespace juce{
    class WaveSlider : public Component{
    public:
        WaveSlider(){ };
        ~WaveSlider(){ };

        void initSlider(std::string WAVE_ID, juce::AudioProcessorValueTreeState& params);
        void initSlider(std::string WAVE_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h);
        void paint (Graphics& g) override;
        void UpdateWave();
        void resized() override;

    private:
        Rectangle<int> bounds;

        Slider    wSlider;
        using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
        std::unique_ptr<SliderAttachment> Wave_Attachment;

        ImageComponent WaveImg;
    };
}

#endif // _WAVE_SLIDER_H_