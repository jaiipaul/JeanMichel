#include "WaveSlider.h"
#include "UI_func.h"
#include <BinaryData.h>

namespace juce {
    using SliderStyle = juce::Slider::SliderStyle;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    void WaveSlider::initSlider(std::string WAVE_ID, juce::AudioProcessorValueTreeState& params){
        WaveImg.setImage(ImageCache::getFromMemory(assets::saw_wave_png, assets::saw_wave_pngSize));
        addAndMakeVisible(WaveImg);
        setSliderParams(*this, wSlider, WAVE_ID, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        Wave_Attachment = CreateAttachment(params, WAVE_ID, wSlider);
        
        bounds = getLocalBounds();
        setBounds(bounds);
    }

    void WaveSlider::initSlider(std::string WAVE_ID, juce::AudioProcessorValueTreeState& params, int x, int y, int w, int h){
        WaveImg.setImage(ImageCache::getFromMemory(assets::saw_wave_png, assets::saw_wave_pngSize));
        addAndMakeVisible(WaveImg);        
        setSliderParams(*this, wSlider, WAVE_ID, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        Wave_Attachment = CreateAttachment(params, WAVE_ID, wSlider);

        bounds = Rectangle<int>(x, y, w, h);
        setBounds(bounds);
    }

    void WaveSlider::paint (Graphics& g){

    }

    void WaveSlider::UpdateWave(){
        int wave = (int)wSlider.getValue();
        //std::cout << wave << std::endl;
        switch(wave){
            case 1: 
                WaveImg.setImage(ImageCache::getFromMemory(assets::saw_wave_png, assets::saw_wave_pngSize));
                //std::cout << "SAW" << std::endl;
                break;
            case 2: 
                WaveImg.setImage(ImageCache::getFromMemory(assets::triangle_wave_png, assets::triangle_wave_pngSize));
                //std::cout << "TRI" << std::endl;
                break;
            case 3: 
                WaveImg.setImage(ImageCache::getFromMemory(assets::square_wave_png, assets::square_wave_pngSize));
                // std::cout << "SQR" << std::endl;
                break;
            case 4: 
                WaveImg.setImage(ImageCache::getFromMemory(assets::sine_wave_png, assets::sine_wave_pngSize));
                // std::cout << "SINE" << std::endl;
                break;     
            default:
                break;  
        }
    }

    void WaveSlider::resized(){
        wSlider.setBounds(getLocalBounds());
        WaveImg.setBounds(getLocalBounds());
    }
}