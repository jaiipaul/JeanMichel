#include "CLookAndFeel.h"

namespace juce{

void CLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style, Slider& slider)
{ 
        auto trackWidth = (float)width;//jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

        Point<float> minPoint, maxPoint;        

        //auto thumbWidth  = slider.isHorizontal() ? 5.f : trackWidth;
        //auto thumbHeight = slider.isHorizontal() ? trackWidth : 5.f;

        Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                 slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

        Point<float> endPoint (slider.isHorizontal() ? (float) (x+width) : startPoint.x,
                               slider.isHorizontal() ? startPoint.y :(float)(y));

        auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
        auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;
        minPoint = startPoint;
        maxPoint = { kx, ky };

        Path backgroundTrack;
        backgroundTrack.startNewSubPath (startPoint);
        backgroundTrack.lineTo (endPoint);
        g.setColour (juce::Colours::antiquewhite);
        g.strokePath (backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        Path valueTrack;
        valueTrack.startNewSubPath (minPoint);
        valueTrack.lineTo (maxPoint);
        g.setColour (juce::Colours::cornflowerblue);
        g.strokePath (valueTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

        //g.setColour (juce::Colours::grey);
        //g.fillRect(slider.isHorizontal() ? 
        //           Rectangle<float> (maxPoint.getX(), maxPoint.getY()-thumbHeight/2.f, thumbWidth, thumbHeight) :
        //           Rectangle<float> (maxPoint.getX() - thumbWidth/2.f, maxPoint.getY(), thumbWidth, thumbHeight));
        //
        //g.setColour(juce::Colours::black);
        //g.fillRect(slider.isHorizontal() ? 
        //           Rectangle<float> (maxPoint.getX() + (thumbWidth-1)/2.f, maxPoint.getY()-thumbHeight/2.f + 1, 1, thumbHeight - 2) :
        //           Rectangle<float> (maxPoint.getX() - thumbWidth/2.f + 1, maxPoint.getY() + (thumbHeight-1)/2.f, thumbWidth - 2, 1));
        
        
}

void CLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int> (x, y, width, height).toFloat();//.reduced (10);

    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (juce::Colours::antiquewhite);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);

        g.setColour (juce::Colours::cornflowerblue);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

    //auto thumbWidth = lineW * 2.0f;
    //Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
    //                         bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));

    //g.setColour (slider.findColour (Slider::thumbColourId));
    //g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
}

}