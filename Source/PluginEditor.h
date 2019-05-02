/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class A_chorus_linesAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    A_chorus_linesAudioProcessorEditor (A_chorus_linesAudioProcessor&);
    ~A_chorus_linesAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider);


private:
        Slider mixSlider, widthSlider, rateSlider;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    A_chorus_linesAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A_chorus_linesAudioProcessorEditor)
};
