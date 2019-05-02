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
    setSize (590, 300);
    
    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mixSlider.setBounds(46,125,94,94);
    mixSlider.setRange(0, 1,.01);
    mixSlider.addListener(this);
    mixSlider.setValue(0);
    
    
    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    widthSlider.setBounds(180,125,94,94);
    widthSlider.setRange(0, 1,.01);
    widthSlider.addListener(this);
    widthSlider.setValue(0);

    
    addAndMakeVisible(rateSlider);
    rateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    rateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    rateSlider.setBounds(314,125,94,94);
    rateSlider.setRange(0, 500,.1);
    rateSlider.addListener(this);
    rateSlider.setValue(1);

}

A_chorus_linesAudioProcessorEditor::~A_chorus_linesAudioProcessorEditor()
{
}

//==============================================================================
void A_chorus_linesAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}
void A_chorus_linesAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &mixSlider)
    {
        processor.set_Parameter(A_chorus_linesAudioProcessor::mixParam, slider -> getValue());
    }
    if (slider == &widthSlider)
    {
        processor.set_Parameter(A_chorus_linesAudioProcessor::widthParam, slider -> getValue());
    }
    if (slider == &rateSlider)
    {
        processor.set_Parameter(A_chorus_linesAudioProcessor::rateParam, slider -> getValue());
    }
}

void A_chorus_linesAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
