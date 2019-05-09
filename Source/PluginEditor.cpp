/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DoubleChorusAudioProcessorEditor::DoubleChorusAudioProcessorEditor (DoubleChorusAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (331, 546);
    
    addAndMakeVisible(mixSlider);
    mixSlider.setLookAndFeel(&lookAndFeel);
    mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mixSlider.setBounds(30,53,94,94);
    mixAttachment = std::make_unique<SliderAttachment>(valueTreeState, "mix", mixSlider);
    
    addAndMakeVisible(widthSlider);
    widthSlider.setLookAndFeel(&lookAndFeel);
    widthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    widthSlider.setBounds(120,120,94,94);
    widthAttachment = std::make_unique<SliderAttachment>(valueTreeState, "width", widthSlider);
    
    addAndMakeVisible(rateSlider);
    rateSlider.setLookAndFeel(&lookAndFeel);
    rateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    rateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    rateSlider.setBounds(213,55,94,94);
    rateAttachment = std::make_unique<SliderAttachment>(valueTreeState, "rate", rateSlider);
    
    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setLookAndFeel(&lookAndFeel);
    feedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    feedbackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    feedbackSlider.setBounds(123,332,94,94);
    feedbackAttachment = std::make_unique<SliderAttachment>(valueTreeState, "feedback", feedbackSlider);
    

}

DoubleChorusAudioProcessorEditor::~DoubleChorusAudioProcessorEditor()
{
}

void DoubleChorusAudioProcessorEditor::refreshSliders(float feedback, float rate, float width, float mix)
{
    feedbackSlider.setValue(feedback);
    rateSlider.setValue(rate);
    widthSlider.setValue(width);
    mixSlider.setValue(mix);
    
}
//==============================================================================
void DoubleChorusAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    Image bg = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImage(bg, 0, 0, 331, 546, 0, 0, 501, 828); //this method will be useful for resizing
}


void DoubleChorusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

