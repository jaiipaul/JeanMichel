#ifndef _C_LNF_H_
#define _C_LNF_H_

#include <JuceHeader.h>

namespace juce{

class CLookAndFeel : public LookAndFeel_V4{
public:
    void drawLinearSlider (Graphics&, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle, Slider&) override;

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
};

}
#endif // _C_LNF_H_