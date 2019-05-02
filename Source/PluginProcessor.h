/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
#include "FractionalDelayBuffer.h"

//==============================================================================
/**
*/
class A_chorus_linesAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    A_chorus_linesAudioProcessor();
    ~A_chorus_linesAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    float getParameter(int index);
    void setParameter(int index, float newValue);
    enum Parameters
    {
        delayParam = 0,
        feedbackParam,
        modParam,
        mixParam,
        totalNumParams
    };
private:
    Oscillator leftOsc, rightOsc;
    FractionalDelayBuffer leftBuffer, rightBuffer;
    float leftDelayTime, rightDelayTime;
    float parameters[4];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (A_chorus_linesAudioProcessor)
};
