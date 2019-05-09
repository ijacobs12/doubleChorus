/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
*/
class DoubleChorusAudioProcessorEditor  : public AudioProcessorEditor
{
public:
     DoubleChorusAudioProcessorEditor (DoubleChorusAudioProcessor&, AudioProcessorValueTreeState&);
    ~DoubleChorusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    CustomLookAndFeel lookAndFeel;
    void refreshSliders(float feedback, float rate, float width, float mix);

private:
    Slider mixSlider, widthSlider, rateSlider, feedbackSlider;
    std::unique_ptr<SliderAttachment> mixAttachment, rateAttachment, feedbackAttachment, widthAttachment;
    AudioProcessorValueTreeState& valueTreeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DoubleChorusAudioProcessorEditor)
};
