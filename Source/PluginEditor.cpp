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
    
    addAndMakeVisible(delay);
    delay.setSliderStyle(Slider::RotaryVerticalDrag);
    delay.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    delay.setBounds(46,125,94,94);
    delay.setRange(0, 1,.01);
    delay.addListener(this);
    delay.setValue(getAudioProcessor()->getParameter(A_chorus_linesAudioProcessor::delayParam),dontSendNotification);
    
    addAndMakeVisible(feedback);
    feedback.setSliderStyle(Slider::RotaryVerticalDrag);
    feedback.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    feedback.setBounds(180,125,94,94);
    feedback.setRange(0, 1,.01);
    feedback.addListener(this);
    feedback.setValue(getAudioProcessor()->getParameter(A_chorus_linesAudioProcessor::feedbackParam),dontSendNotification);
    
    addAndMakeVisible(mod);
    mod.setSliderStyle(Slider::RotaryVerticalDrag);
    mod.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mod.setBounds(314,125,94,94);
    mod.setRange(0, 1,.01);
    mod.addListener(this);
    mod.setValue(getAudioProcessor()->getParameter(A_chorus_linesAudioProcessor::modParam),dontSendNotification);
    
    addAndMakeVisible(mix);
    mix.setSliderStyle(Slider::RotaryVerticalDrag);
    mix.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    mix.setBounds(448,125,94,94);
    mix.setRange(0, 1,.01);
    mix.addListener(this);
    mix.setValue(getAudioProcessor()->getParameter(A_chorus_linesAudioProcessor::mixParam),dontSendNotification);
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
    if (slider == &delay)
    {
        processor.setParameter(A_chorus_linesAudioProcessor::delayParam, slider -> getValue());
    }
    if (slider == &feedback)
    {
        processor.setParameter(A_chorus_linesAudioProcessor::feedbackParam, slider -> getValue());
    }
    if (slider == &mod)
    {
        processor.setParameter(A_chorus_linesAudioProcessor::modParam, slider -> getValue());
    }
    if (slider == &mix)
    {
        processor.setParameter(A_chorus_linesAudioProcessor::mixParam, slider -> getValue());
    }
}

void A_chorus_linesAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
