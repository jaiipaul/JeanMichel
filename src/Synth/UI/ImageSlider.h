#ifndef _IMAGE_SLIDER_H_
#define _IMAGE_SLIDER_H_

#include <JuceHeader.h>

namespace juce{
    class ImageSlider : public Component{
    public:
        ImageSlider(){ };
        ~ImageSlider(){ };

        void initSlider(std::string ID, juce::AudioProcessorValueTreeState& params, 
                        const char* img_name, int img_size, int img_w, int img_h, int n_values);

        void initSlider(std::string ID, juce::AudioProcessorValueTreeState& params, 
                        const char* img_name, int img_size, int img_w, int img_h, int n_values,
                        int x, int y, int w, int h);

        void paint (Graphics& g) override;
        void Update();
        void resized() override;

    private:
        Rectangle<int> bounds;
        int values;
        Slider    ImgSlider;
        using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
        std::unique_ptr<SliderAttachment> Attachment;

        ImageComponent ImgComp;
        Rectangle<int> Image_Rect;
        int img_w;
        int img_h;
        Image Img;
    };
}

#endif // _IMAGE_SLIDER_H_