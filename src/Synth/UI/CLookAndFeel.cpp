#include "CLookAndFeel.h"

namespace juce{

void CLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style, Slider& slider)
{ 
        auto trackWidth = 16.f;//jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

        Point<float> minPoint, maxPoint;        

        auto thumbWidth  = slider.isHorizontal() ? 5.f : trackWidth;
        auto thumbHeight = slider.isHorizontal() ? trackWidth : 5.f;

        Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y) + thumbHeight);

        Point<float> endPoint (slider.isHorizontal() ? (float) (x+width) + thumbWidth : startPoint.x,
                               slider.isHorizontal() ? startPoint.y :(float)(y));

        auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
        auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;
        minPoint = startPoint;
        maxPoint = { kx, ky };

        Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (juce::Colours::antiquewhite);
        g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::mitered, PathStrokeType::butt });

        Path valueTrack;
        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (maxPoint);
        g.setColour (juce::Colours::cornflowerblue);
        g.strokePath (valueTrack, { trackWidth, PathStrokeType::mitered, PathStrokeType::butt });

        g.setColour (juce::Colours::grey);
        g.fillRect(slider.isHorizontal() ? 
                   Rectangle<float> (maxPoint.getX(), maxPoint.getY()-thumbHeight/2.f, thumbWidth, thumbHeight) :
                   Rectangle<float> (maxPoint.getX() - thumbWidth/2.f, maxPoint.getY(), thumbWidth, thumbHeight));
        
        g.setColour(juce::Colours::black);
        g.fillRect(slider.isHorizontal() ? 
                   Rectangle<float> (maxPoint.getX() + (thumbWidth-1)/2.f, maxPoint.getY()-thumbHeight/2.f + 1, 1, thumbHeight - 2) :
                   Rectangle<float> (maxPoint.getX() - thumbWidth/2.f + 1, maxPoint.getY() + (thumbHeight-1)/2.f, thumbWidth - 2, 1));
        
}

}