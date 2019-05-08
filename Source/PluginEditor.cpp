/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
A_chorus_linesAudioProcessorEditor::A_chorus_linesAudioProcessorEditor (A_chorus_linesAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (331, 546);
    
    addAndMakeVisible(mixSlider);
    mixSlider.setLookAndFeel(&lookAndFeel);
    mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mixSlider.setBounds(30,53,94,94);
    mixSlider.setRange(0, 1,.01);
    mixSlider.addListener(this);
    mixSlider.setValue(*processor.mixParam);
    
    
    addAndMakeVisible(widthSlider);
    widthSlider.setLookAndFeel(&lookAndFeel);
    widthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    widthSlider.setBounds(120,120,94,94);
    widthSlider.setRange(0.1, 1,.01);
    widthSlider.addListener(this);
    widthSlider.setValue(*processor.widthParam);

    
    addAndMakeVisible(rateSlider);
    rateSlider.setLookAndFeel(&lookAndFeel);
    rateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    rateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    rateSlider.setBounds(213,55,94,94);
    rateSlider.setRange(.1, 4,.01);
    rateSlider.setSkewFactorFromMidPoint(.8);
    rateSlider.addListener(this);
    rateSlider.setValue(*processor.rateParam);
    
    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setLookAndFeel(&lookAndFeel);
    feedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    feedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    feedbackSlider.setBounds(123,332,94,94);
    feedbackSlider.setRange(.2, 1,.01);
    feedbackSlider.addListener(this);
    feedbackSlider.setValue(*processor.feedbackParam);

}

A_chorus_linesAudioProcessorEditor::~A_chorus_linesAudioProcessorEditor()
{
}

void A_chorus_linesAudioProcessorEditor::refreshSliders(float feedback, float rate, float width, float mix)
{
    feedbackSlider.setValue(feedback);
    rateSlider.setValue(rate);
    widthSlider.setValue(width);
    mixSlider.setValue(mix);
    
}
//==============================================================================
void A_chorus_linesAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    Image bg = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImage(bg, 0, 0, 331, 546, 0, 0, 501, 828); //this method will be useful for resizing
}
void A_chorus_linesAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &mixSlider)
    {
        *processor.mixParam = slider -> getValue();
    }
    if (slider == &widthSlider)
    {
        *processor.widthParam = slider -> getValue();
    }
    if (slider == &rateSlider)
    {
        *processor.rateParam = slider -> getValue();
    }
    if (slider == &feedbackSlider)
    {
        *processor.feedbackParam = slider -> getValue();
    }
}

void A_chorus_linesAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

