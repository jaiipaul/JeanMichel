#ifndef _METER_H_
#define _METER_H_

#include <JuceHeader.h>

namespace juce{
    class Meter : public Component{
    public:
        enum MeterStyle{
            VerticalNoBack, Vertical, HorizontalNoBack, Horizontal
        };

        Meter(){ };
        ~Meter(){ };

        void paint (Graphics& g) override;
        void setLevel( const float value ) { level = value; };
        void setStyle( MeterStyle _style ) { style = _style; }
        void setMeterColour( Colour _MeterColour ){ MeterColour = _MeterColour; };
        void setBackColour( Colour _BackColour ){ BackColour = _BackColour; };
        void setCornerSize( float _CornerSize ){ CornerSize = _CornerSize; };
        //void resized() override;

    private:
        Colour BackColour  = Colours::white.withBrightness(0.4f);
        Colour MeterColour = Colours::white;
        float CornerSize = 0.f;
        MeterStyle style;
        float level = -60.f;
    };
}

#endif // _METER_H_