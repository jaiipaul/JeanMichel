#include "Meter.h"

namespace juce {
    void Meter::paint(Graphics& g){
        auto bounds = getLocalBounds().toFloat();

        if((style == Vertical) || (style == Horizontal) ){
            g.setColour(BackColour);
            g.fillRoundedRectangle(bounds, CornerSize);
        }

        g.setColour(MeterColour);
        if(style == Horizontal || style == HorizontalNoBack){
            const auto scaledX = jmap(level, -60.f, +6.f, 0.f, static_cast<float>(getWidth()));
            g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), CornerSize);
        }else if( style == Vertical || style == VerticalNoBack){
            const auto scaledY = jmap(level, -60.f, +6.f, 0.f, static_cast<float>(getHeight()));
            g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), CornerSize);
        }
    }
}
