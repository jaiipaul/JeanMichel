#include "ImageSlider.h"
#include "UI_func.h"
#include <BinaryData.h>

namespace juce {
    using SliderStyle = juce::Slider::SliderStyle;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    void ImageSlider::initSlider(std::string ID, juce::AudioProcessorValueTreeState& params, 
                                 const char* img_name, int img_size, int _img_w, int _img_h, int n_values){

        Img = ImageCache::getFromMemory(img_name, img_size);

        img_w = _img_w; img_h = _img_h;
        Image_Rect = Rectangle<int>(0, 0, img_w, img_h);
        ImgComp.setImage(Img.getClippedImage(Image_Rect));
        addAndMakeVisible(ImgComp);

        setSliderParams(*this, ImgSlider, ID, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        Attachment = CreateAttachment(params, ID, ImgSlider);
        
        values = n_values;
        jassert(values != ImgSlider.getMaximum());

        bounds = getLocalBounds();
        setBounds(bounds);
    }

    void ImageSlider::initSlider(std::string ID, juce::AudioProcessorValueTreeState& params, 
                                 const char* img_name, int img_size, int _img_w, int _img_h, int n_values,
                                 int x, int y, int w, int h){

        Img = ImageCache::getFromMemory(img_name, img_size);

        img_w = _img_w; img_h = _img_h;
        Image_Rect = Rectangle<int>(0, 0, img_w, img_h);
        ImgComp.setImage(Img.getClippedImage(Image_Rect));
        addAndMakeVisible(ImgComp);

        setSliderParams(*this, ImgSlider, ID, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        Attachment = CreateAttachment(params, ID, ImgSlider);
        
        values = n_values;
        jassert(values != ImgSlider.getMaximum());

        bounds = Rectangle<int>(x, y, w, h);
        setBounds(bounds);
    }

    void ImageSlider::paint (Graphics& g){

    }

    void ImageSlider::Update(){
        int val = (int)ImgSlider.getValue();
        
        Image_Rect = Rectangle<int>((val-1)*img_w, 0, img_w, img_h);
        ImgComp.setImage(Img.getClippedImage(Image_Rect));
    }

    void ImageSlider::resized(){
        ImgSlider.setBounds(getLocalBounds());
        ImgComp.setBounds(getLocalBounds());
    }
}